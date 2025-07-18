/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/
#include <string.h>
#include "r_sci_b_spi.h"
#include "r_sci_b_spi_cfg.h"

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

#define SCI_B_SPI_PRV_DTC_RX_TRANSFER_SETTINGS    ((TRANSFER_MODE_NORMAL << 30U) | (TRANSFER_SIZE_1_BYTE << 28U) | \
                                                   (TRANSFER_ADDR_MODE_FIXED << 26U) | (TRANSFER_IRQ_END << 21U) | \
                                                   (TRANSFER_ADDR_MODE_INCREMENTED << 18U))

#define SCI_B_SPI_PRV_DTC_TX_TRANSFER_SETTINGS    ((TRANSFER_MODE_NORMAL << 30U) | (TRANSFER_SIZE_1_BYTE << 28U) |       \
                                                   (TRANSFER_ADDR_MODE_INCREMENTED << 26U) | (TRANSFER_IRQ_END << 21U) | \
                                                   (TRANSFER_ADDR_MODE_FIXED << 18U))

#define SCI_B_SPI_PRV_CLK_MAX_N                   (0xFFU)
#define SCI_B_SPI_PRV_CLK_MAX_n                   (3U)
#define SCI_B_SPI_PRV_CLK_MAX_DIV                 ((SCI_B_SPI_PRV_CLK_MAX_N + 1) * 8 * \
                                                   (1 << (2 * SCI_B_SPI_PRV_CLK_MAX_n - 1)))
#define SCI_B_SPI_PRV_CHR_RST_VALUE               (0x0200U)
#define SCI_B_SPI_PRV_DATA_REG_MASK               (0xFFFFFF00)
#define SCI_B_SPI_PRV_RDAT_MASK                   (0xFFU)

/** "SCIBS" in ASCII, used to determine if channel is open. */
#define SCI_B_SPI_OPEN                            (0x53434953ULL)

/***********************************************************************************************************************
 * Private global variables.
 **********************************************************************************************************************/

const spi_api_t g_spi_on_sci_b =
{
    .open        = R_SCI_B_SPI_Open,
    .read        = R_SCI_B_SPI_Read,
    .write       = R_SCI_B_SPI_Write,
    .writeRead   = R_SCI_B_SPI_WriteRead,
    .close       = R_SCI_B_SPI_Close,
    .callbackSet = R_SCI_B_SPI_CallbackSet
};

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

#if defined(__ARMCC_VERSION) || defined(__ICCARM__)
typedef void (BSP_CMSE_NONSECURE_CALL * sci_b_spi_prv_ns_callback)(spi_callback_args_t * p_args);
#elif defined(__GNUC__)
typedef BSP_CMSE_NONSECURE_CALL void (*volatile sci_b_spi_prv_ns_callback)(spi_callback_args_t * p_args);
#endif

/***********************************************************************************************************************
 * Private function declarations.
 **********************************************************************************************************************/

static void r_sci_b_spi_hw_config(sci_b_spi_instance_ctrl_t * const p_ctrl);

#if SCI_B_SPI_DTC_SUPPORT_ENABLE == 1
static fsp_err_t r_sci_b_spi_transfer_config(sci_b_spi_instance_ctrl_t * const p_ctrl);

#endif
static fsp_err_t r_sci_b_spi_write_read_common(sci_b_spi_instance_ctrl_t * const p_ctrl,
                                               void const                      * p_src,
                                               void                            * p_dest,
                                               uint32_t const                    length);
static void r_sci_b_spi_start_transfer(sci_b_spi_instance_ctrl_t * const p_ctrl);
static void r_sci_b_spi_transmit(sci_b_spi_instance_ctrl_t * p_ctrl);
static void r_sci_b_spi_call_callback(sci_b_spi_instance_ctrl_t * p_ctrl, spi_event_t event);

void sci_b_spi_txi_isr(void);
void sci_b_spi_rxi_isr(void);
void sci_b_spi_tei_isr(void);
void sci_b_spi_eri_isr(void);

/***********************************************************************************************************************
 * Functions
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * @addtogroup SCI_B_SPI
 * @{
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * Initialize a channel for SPI communication mode. Implements @ref spi_api_t::open.
 *
 * This function performs the following tasks:
 *   - Performs parameter checking and processes error conditions.
 *   - Enables the clock for the SCI channel.
 *   - Initializes the associated registers with default value and the user-configurable options.
 *   - Provides the channel handle for use with other API functions.
 *
 * @param      p_api_ctrl                      Pointer to the control structure.
 * @param      p_cfg                           Pointer to a configuration structure.
 *
 * @retval     FSP_SUCCESS                     Channel initialized successfully.
 * @retval     FSP_ERR_ASSERTION               An input parameter is invalid or NULL.
 * @retval     FSP_ERR_ALREADY_OPEN            The instance has already been opened.
 * @retval     FSP_ERR_IP_CHANNEL_NOT_PRESENT  The channel number is invalid.
 **********************************************************************************************************************/
fsp_err_t R_SCI_B_SPI_Open (spi_ctrl_t * p_api_ctrl, spi_cfg_t const * const p_cfg)
{
    sci_b_spi_instance_ctrl_t * p_ctrl = (sci_b_spi_instance_ctrl_t *) p_api_ctrl;
    fsp_err_t err = FSP_SUCCESS;

#if SCI_B_SPI_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_ctrl);
    FSP_ERROR_RETURN(SCI_B_SPI_OPEN != p_ctrl->open, FSP_ERR_ALREADY_OPEN);
    FSP_ASSERT(NULL != p_cfg);
    FSP_ASSERT(NULL != p_cfg->p_extend);
    FSP_ASSERT(NULL != p_cfg->p_callback);
    FSP_ERROR_RETURN(BSP_FEATURE_SCI_CHANNELS & (1U << p_cfg->channel), FSP_ERR_IP_CHANNEL_NOT_PRESENT);
    FSP_ASSERT(p_cfg->rxi_irq >= 0);
    FSP_ASSERT(p_cfg->txi_irq >= 0);
    FSP_ASSERT(p_cfg->tei_irq >= 0);
    FSP_ASSERT(p_cfg->eri_irq >= 0);
#endif

    p_ctrl->p_reg = (R_SCI_B0_Type *) ((R_SCI1_BASE - R_SCI0_BASE) * p_cfg->channel + R_SCI0_BASE);
    p_ctrl->p_cfg = p_cfg;

    p_ctrl->p_callback        = p_cfg->p_callback;
    p_ctrl->p_context         = p_cfg->p_context;
    p_ctrl->p_callback_memory = NULL;

#if SCI_B_SPI_DTC_SUPPORT_ENABLE == 1

    /* Open the SCI_B_SPI transfer interface if available. */
    err = r_sci_b_spi_transfer_config(p_ctrl);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);
#endif

    /* Write user configuration to registers. */
    r_sci_b_spi_hw_config(p_ctrl);

    /* Enable required interrupts. */
    R_BSP_IrqCfgEnable(p_cfg->rxi_irq, p_cfg->rxi_ipl, p_ctrl);
    R_BSP_IrqCfgEnable(p_cfg->txi_irq, p_cfg->txi_ipl, p_ctrl);
    R_BSP_IrqCfgEnable(p_cfg->tei_irq, p_cfg->tei_ipl, p_ctrl);
    R_BSP_IrqCfgEnable(p_cfg->eri_irq, p_cfg->eri_ipl, p_ctrl);

    p_ctrl->open = SCI_B_SPI_OPEN;

    return err;
}

/*******************************************************************************************************************//**
 * Receive data from an SPI device. Implements @ref spi_api_t::read.
 *
 * The function performs the following tasks:
 *   - Performs parameter checking and processes error conditions.
 *   - Enable transmitter.
 *   - Enable receiver.
 *   - Enable interrupts.
 *   - Start data transmission by writing data to the TXD register.
 *   - Receive data from receive buffer full interrupt occurs and copy data to the buffer of destination.
 *   - Complete data reception via receive buffer full interrupt and transmitting dummy data.
 *   - Disable transmitter.
 *   - Disable receiver.
 *   - Disable interrupts.
 *
 * @param      p_api_ctrl           Pointer to the control structure.
 * @param      p_dest               Pointer to the destination buffer.
 * @param[in]  length               The number of bytes to transfer.
 * @param[in]  bit_width            Invalid for SCI_B_SPI (Set to SPI_BIT_WIDTH_8_BITS).
 *
 * @retval     FSP_SUCCESS          Read operation successfully completed.
 * @retval     FSP_ERR_ASSERTION    One of the following invalid parameters passed:
 *                                  - Pointer p_api_ctrl is NULL
 *                                  - Bit width is not 8 bits
 *                                  - Length is equal to 0
 *                                  - Pointer to destination is NULL
 * @retval     FSP_ERR_NOT_OPEN     The channel has not been opened. Open the channel first.
 * @retval     FSP_ERR_UNSUPPORTED  The given bit_width is not supported.
 * @retval     FSP_ERR_IN_USE       A transfer is already in progress.
 *
 * @return     See @ref RENESAS_ERROR_CODES or functions called by this function for other possible return codes. This
 *             function calls:
 *               - @ref transfer_api_t::reconfigure
 **********************************************************************************************************************/
fsp_err_t R_SCI_B_SPI_Read (spi_ctrl_t * const    p_api_ctrl,
                            void                * p_dest,
                            uint32_t const        length,
                            spi_bit_width_t const bit_width)
{
    sci_b_spi_instance_ctrl_t * p_ctrl = (sci_b_spi_instance_ctrl_t *) p_api_ctrl;

#if SCI_B_SPI_CFG_PARAM_CHECKING_ENABLE

    /* Check bit_width parameter, in simple SPI, only 8 bits operation is allowed. */
    FSP_ERROR_RETURN(SPI_BIT_WIDTH_8_BITS == bit_width, FSP_ERR_UNSUPPORTED);

    /* Check the destination, should not be NULL. */
    FSP_ASSERT(NULL != p_dest);
#else
    FSP_PARAMETER_NOT_USED(bit_width);
#endif

    return r_sci_b_spi_write_read_common(p_ctrl, NULL, p_dest, length);
}

/*******************************************************************************************************************//**
 * Transmit data to a SPI  device. Implements @ref spi_api_t::write.
 *
 * The function performs the following tasks:
 *   - Performs parameter checking and processes error conditions.
 *   - Enable transmitter.
 *   - Enable interrupts.
 *   - Start data transmission with data via transmit buffer empty interrupt.
 *   - Copy data from source buffer to the SPI data register for transmission.
 *   - Complete data transmission via transmit buffer empty interrupt.
 *   - Disable transmitter.
 *   - Disable receiver.
 *   - Disable interrupts.
 *
 * @param      p_api_ctrl           Pointer to the control structure.
 * @param      p_src                Pointer to the source buffer.
 * @param[in]  length               The number of bytes to transfer.
 * @param[in]  bit_width            Invalid for SCI_B_SPI (Set to SPI_BIT_WIDTH_8_BITS).
 *
 * @retval     FSP_SUCCESS          Write operation successfully completed.
 * @retval     FSP_ERR_ASSERTION    One of the following invalid parameters passed:
 *                                  - Pointer p_api_ctrl is NULL
 *                                  - Pointer to source is NULL
 *                                  - Length is equal to 0
 *                                  - Bit width is not equal to 8 bits
 * @retval     FSP_ERR_NOT_OPEN     The channel has not been opened. Open the channel first.
 * @retval     FSP_ERR_UNSUPPORTED  The given bit_width is not supported.
 * @retval     FSP_ERR_IN_USE       A transfer is already in progress.
 *
 * @return     See @ref RENESAS_ERROR_CODES or functions called by this function for other possible return codes. This
 *             function calls:
 *               - @ref transfer_api_t::reconfigure
 **********************************************************************************************************************/
fsp_err_t R_SCI_B_SPI_Write (spi_ctrl_t * const    p_api_ctrl,
                             void const          * p_src,
                             uint32_t const        length,
                             spi_bit_width_t const bit_width)
{
    sci_b_spi_instance_ctrl_t * p_ctrl = (sci_b_spi_instance_ctrl_t *) p_api_ctrl;

#if SCI_B_SPI_CFG_PARAM_CHECKING_ENABLE
    FSP_ERROR_RETURN(SPI_BIT_WIDTH_8_BITS == bit_width, FSP_ERR_UNSUPPORTED);
    FSP_ASSERT(NULL != p_src);
#else
    FSP_PARAMETER_NOT_USED(bit_width);
#endif

    return r_sci_b_spi_write_read_common(p_ctrl, p_src, NULL, length);
}

/*******************************************************************************************************************//**
 * Simultaneously transmit data to SPI device while receiving data from SPI device (full duplex).
 * Implements @ref spi_api_t::writeRead.
 *
 * The function performs the following tasks:
 *   - Performs parameter checking and processes error conditions.
 *   - Enable transmitter.
 *   - Enable receiver.
 *   - Enable interrupts.
 *   - Start data transmission using transmit buffer empty interrupt (or by writing to the TDR register).
 *   - Copy data from source buffer to the SPI data register for transmission.
 *   - Receive data from receive buffer full interrupt and copy data to the destination buffer.
 *   - Complete data transmission and reception via transmit end interrupt.
 *   - Disable transmitter.
 *   - Disable receiver.
 *   - Disable interrupts.
 *
 * @param      p_api_ctrl           Pointer to the control structure.
 * @param      p_src                Pointer to the source buffer.
 * @param      p_dest               Pointer to the destination buffer.
 * @param[in]  length               The number of bytes to transfer.
 * @param[in]  bit_width            Invalid for SCI_B_SPI (Set to SPI_BIT_WIDTH_8_BITS).
 *
 * @retval     FSP_SUCCESS          Write operation successfully completed.
 * @retval     FSP_ERR_ASSERTION    One of the following invalid parameters passed:
 *                                  - Pointer p_api_ctrl is NULL
 *                                  - Pointer to source is NULL
 *                                  - Pointer to destination is NULL
 *                                  - Length is equal to 0
 *                                  - Bit width is not equal to 8 bits
 * @retval     FSP_ERR_NOT_OPEN     The channel has not been opened. Open the channel first.
 * @retval     FSP_ERR_UNSUPPORTED  The given bit_width is not supported.
 * @retval     FSP_ERR_IN_USE       A transfer is already in progress.
 *
 * @return     See @ref RENESAS_ERROR_CODES or functions called by this function for other possible return codes. This
 *             function calls:
 *               - @ref transfer_api_t::reconfigure
 **********************************************************************************************************************/
fsp_err_t R_SCI_B_SPI_WriteRead (spi_ctrl_t * const    p_api_ctrl,
                                 void const          * p_src,
                                 void                * p_dest,
                                 uint32_t const        length,
                                 spi_bit_width_t const bit_width)
{
    sci_b_spi_instance_ctrl_t * p_ctrl = (sci_b_spi_instance_ctrl_t *) p_api_ctrl;

#if SCI_B_SPI_CFG_PARAM_CHECKING_ENABLE
    FSP_ERROR_RETURN(SPI_BIT_WIDTH_8_BITS == bit_width, FSP_ERR_UNSUPPORTED);
    FSP_ASSERT(NULL != p_src);
    FSP_ASSERT(NULL != p_dest);
#else
    FSP_PARAMETER_NOT_USED(bit_width);
#endif

    return r_sci_b_spi_write_read_common(p_ctrl, p_src, p_dest, length);
}

/*******************************************************************************************************************//**
 * Updates the user callback and has option of providing memory for callback structure.
 * Implements spi_api_t::callbackSet
 *
 * @retval  FSP_SUCCESS                  Callback updated successfully.
 * @retval  FSP_ERR_ASSERTION            A required pointer is NULL.
 * @retval  FSP_ERR_NOT_OPEN             The control block has not been opened.
 * @retval  FSP_ERR_NO_CALLBACK_MEMORY   p_callback is non-secure and p_callback_memory is either secure or NULL.
 **********************************************************************************************************************/
fsp_err_t R_SCI_B_SPI_CallbackSet (spi_ctrl_t * const          p_api_ctrl,
                                   void (                    * p_callback)(spi_callback_args_t *),
                                   void * const                p_context,
                                   spi_callback_args_t * const p_callback_memory)
{
    sci_b_spi_instance_ctrl_t * p_ctrl = (sci_b_spi_instance_ctrl_t *) p_api_ctrl;

#if (SCI_B_SPI_CFG_PARAM_CHECKING_ENABLE)
    FSP_ASSERT(p_ctrl);
    FSP_ASSERT(p_callback);
    FSP_ERROR_RETURN(SCI_B_SPI_OPEN == p_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

#if BSP_TZ_SECURE_BUILD

    /* Get security state of p_callback */
    bool callback_is_secure =
        (NULL == cmse_check_address_range((void *) p_callback, sizeof(void *), CMSE_AU_NONSECURE));

 #if SCI_B_SPI_CFG_PARAM_CHECKING_ENABLE

    /* In secure projects, p_callback_memory must be provided in non-secure space if p_callback is non-secure */
    spi_callback_args_t * const p_callback_memory_checked = cmse_check_pointed_object(p_callback_memory,
                                                                                      CMSE_AU_NONSECURE);
    FSP_ERROR_RETURN(callback_is_secure || (NULL != p_callback_memory_checked), FSP_ERR_NO_CALLBACK_MEMORY);
 #endif
#endif

    /* Store callback and context */
#if BSP_TZ_SECURE_BUILD
    p_ctrl->p_callback = callback_is_secure ? p_callback :
                         (void (*)(spi_callback_args_t *))cmse_nsfptr_create(p_callback);
#else
    p_ctrl->p_callback = p_callback;
#endif
    p_ctrl->p_context         = p_context;
    p_ctrl->p_callback_memory = p_callback_memory;

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Disable the SCI channel and set the instance as not open. Implements @ref spi_api_t::close.
 *
 * @param      p_api_ctrl         Pointer to an opened instance.
 *
 * @retval     FSP_SUCCESS        Channel successfully closed.
 * @retval     FSP_ERR_ASSERTION  The parameter p_api_ctrl is NULL.
 * @retval     FSP_ERR_NOT_OPEN   The channel has not been opened. Open the channel first.
 **********************************************************************************************************************/
fsp_err_t R_SCI_B_SPI_Close (spi_ctrl_t * const p_api_ctrl)
{
    sci_b_spi_instance_ctrl_t * p_ctrl = (sci_b_spi_instance_ctrl_t *) p_api_ctrl;

#if SCI_B_SPI_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_ctrl);
    FSP_ERROR_RETURN(SCI_B_SPI_OPEN == p_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    /* Clear the RE and TE bits in CCR0. */
    p_ctrl->p_reg->CCR0 = 0;

    R_BSP_IrqDisable(p_ctrl->p_cfg->txi_irq);
    R_BSP_IrqDisable(p_ctrl->p_cfg->rxi_irq);
    R_BSP_IrqDisable(p_ctrl->p_cfg->eri_irq);
    R_BSP_IrqDisable(p_ctrl->p_cfg->tei_irq);

    /* Disable the clock to the SCI channel. */
    R_BSP_MODULE_STOP(FSP_IP_SCI, p_ctrl->p_cfg->channel);

    if (NULL != p_ctrl->p_cfg->p_transfer_rx)
    {
        p_ctrl->p_cfg->p_transfer_rx->p_api->close(p_ctrl->p_cfg->p_transfer_rx->p_ctrl);
    }

    if (NULL != p_ctrl->p_cfg->p_transfer_tx)
    {
        p_ctrl->p_cfg->p_transfer_tx->p_api->close(p_ctrl->p_cfg->p_transfer_tx->p_ctrl);
    }

    p_ctrl->open = 0U;

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Calculate the register settings required to achieve the desired bitrate.
 *
 * @param[in]  bitrate            bitrate [bps]. For example, 250,000; 500,00; 2,500,000 (max), etc.
 * @param      clock_source       clock source (PCLKA or SCISPICLK) used for bit rate calculation.
 * @param      sclk_div           Pointer to sci_b_spi_div_setting_t used to configure baudrate settings.
 * @retval     FSP_SUCCESS        Baud rate is set successfully.
 * @retval     FSP_ERR_ASSERTION  Baud rate is not achievable.
 * @note       The application must pause for 1 bit time after the BRR register is loaded before transmitting/receiving
 *             to allow time for the clock to settle.
 **********************************************************************************************************************/
fsp_err_t R_SCI_B_SPI_CalculateBitrate (uint32_t                  bitrate,
                                        sci_b_spi_clock_source_t  clock_source,
                                        sci_b_spi_div_setting_t * sclk_div)
{
    uint32_t peripheral_clock;
    if (SCI_B_SPI_SOURCE_CLOCK_PCLK == clock_source)
    {
        peripheral_clock = R_FSP_SystemClockHzGet(BSP_FEATURE_SCI_CLOCK);
    }
    else
    {
#if BSP_FEATURE_BSP_HAS_SCISPI_CLOCK
        peripheral_clock = R_FSP_SciSpiClockHzGet();
#elif BSP_FEATURE_BSP_HAS_SCI_CLOCK
        peripheral_clock = R_FSP_SciClockHzGet();
#endif
    }

#if SCI_B_SPI_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != sclk_div);
    FSP_ASSERT(bitrate);
    FSP_ASSERT(bitrate >= (peripheral_clock + SCI_B_SPI_PRV_CLK_MAX_DIV - 1U) / SCI_B_SPI_PRV_CLK_MAX_DIV);
#endif

    uint32_t divisor = 0;
    uint32_t brr     = 0;

    for (uint8_t cks = 0; cks <= 3; cks++)
    {
        for (int8_t bgdm = 1; bgdm >= 0; bgdm--)
        {
            divisor = (1 << (2 * (cks + 1) - bgdm)) * bitrate;

            /* Calculate BRR so that the bit rate is the largest possible value less than or equal to the desired
             * bitrate. */
            brr = (peripheral_clock + divisor - 1) / divisor - 1;

            if (brr <= UINT8_MAX)
            {
                sclk_div->brr  = (uint8_t) brr;
                sclk_div->cks  = (uint8_t) (cks & 3);
                sclk_div->bgdm = (uint8_t) (bgdm & 1);

                return FSP_SUCCESS;
            }
        }
    }

    return FSP_ERR_INVALID_ARGUMENT;
}

/*******************************************************************************************************************//**
 * @} (end addtogroup SCI_B_SPI)
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * Configures SCI registers based on the user configuration.
 * @param      p_ctrl          Pointer to control structure.
 **********************************************************************************************************************/
static void r_sci_b_spi_hw_config (sci_b_spi_instance_ctrl_t * const p_ctrl)
{
    spi_cfg_t const          * p_cfg    = p_ctrl->p_cfg;
    sci_b_spi_extended_cfg_t * p_extend = (sci_b_spi_extended_cfg_t *) p_cfg->p_extend;

    /* Initialize registers to their reset values. */
    uint32_t ccr0 = 0U;
    uint32_t ccr1 = R_SCI_B0_CCR1_SPB2DT_Msk;
    uint32_t ccr2 = 0U;
    uint32_t ccr3 = R_SCI_B0_CCR3_CPHA_Msk | R_SCI_B0_CCR3_CPOL_Msk | R_SCI_B0_CCR3_LSBF_Msk |
                    SCI_B_SPI_PRV_CHR_RST_VALUE;

    /* CCR4.SCKSEL selects the master receive clock used in simple spi mode on supported MCUs. */
    uint32_t ccr4  = (BSP_FEATURE_SCI_SPI_SCKSEL_VALUE << R_SCI_B0_CCR4_SCKSEL_Pos);
    uint32_t cfclr = 0U;
    uint32_t ffclr = 0U;

    /* SCI Initialization in Simple SPI Mode (See Section 26.9.5 and 26.6.3 in RA6T2 manual R01UH0951EJ0100). */

    /* Write settings to CCR3:
     * - Set Bypass Synchronizer circuit between bus clock and operation clock.
     * - Set Character Length to 8-Bit.
     * - Set MSB first.
     * - set CPHA and CPOL.
     * - Set Simple SPI Mode.
     */
    if (SPI_BIT_ORDER_MSB_FIRST == p_cfg->bit_order)
    {
        /* Configure MSB first (Default is LSB). */
        ccr3 &= ~R_SCI_B0_CCR3_LSBF_Msk;
    }

    if (SPI_MODE_SLAVE == p_cfg->operating_mode)
    {
        /* Select slave mode. */
        ccr3 |= 2U << R_SCI_B0_CCR3_CKE_Pos;

        /* Select to use SSLn input pin */
        ccr0 |= R_SCI_B0_CCR0_SSE_Msk;
    }

    /* Apply CPOL and CPHA settings as required. By default CCR2.CPHA=1, CCR2.CPOL=1. */
    if (SPI_CLK_PHASE_EDGE_ODD == p_cfg->clk_phase)
    {
        /* In order to get sampling on the ODD edge set CCR3.CPHA = 0. */
        ccr3 &= ~R_SCI_B0_CCR3_CPHA_Msk;
    }

    /* In order to get sampling on the even clock edge set CCR3.CPHA = 1. */
    if (SPI_CLK_POLARITY_LOW == p_cfg->clk_polarity)
    {
        /* set CCR3.CPOL = 0 for clock polarity as low during idle. (See Figure 26.97 in RA6T2 manual R01UH0951EJ0100). */
        ccr3 &= ~R_SCI_B0_CCR3_CPOL_Msk;
    }

    /* Apply the synchronization bypass settings. */
    ccr3 |= (uint32_t) ((p_extend->clock_source) << R_SCI_B0_CCR3_BPEN_Pos);

    /* Set Simple SPI mode. */
    ccr3 |= 3U << R_SCI_B0_CCR3_MOD_Pos;

    /* Write settings to CCR2:
     * - Write the BRR setting.
     * - Write the clock divider setting.
     * - Write the Baud Rate Generator Double-Speed Mode setting.
     */
    if (SPI_MODE_MASTER == p_cfg->operating_mode)
    {
        ccr2 |= (uint32_t) (p_extend->clk_div.cks << R_SCI_B0_CCR2_CKS_Pos);
        ccr2 |= (uint32_t) ((p_extend->clk_div.brr) << R_SCI_B0_CCR2_BRR_Pos);
        ccr2 |= (uint32_t) ((p_extend->clk_div.bgdm) << R_SCI_B0_CCR2_BGDM_Pos);
    }

    /* Enable Clock for the SCI Channel. */
    R_BSP_MODULE_START(FSP_IP_SCI, p_cfg->channel);

    /* Set TEIE, TIE, RIE, TE, and RE to 0. */
    p_ctrl->p_reg->CCR0 = 0;

    /* If TCLK is slower than the bus clock, then wait for the internal state to be updated (See Section 26.20.15 in the RA6T2 user manual r01uh0951ej0100-ra6t2). */
    FSP_HARDWARE_REGISTER_WAIT(p_ctrl->p_reg->CESR, 0U);

    /* Clear status flags. */
    cfclr = R_SCI_B0_CFCLR_RDRFC_Msk | R_SCI_B0_CFCLR_FERC_Msk | R_SCI_B0_CFCLR_PERC_Msk | R_SCI_B0_CFCLR_MFFC_Msk |
            R_SCI_B0_CFCLR_ORERC_Msk | R_SCI_B0_CFCLR_DFERC_Msk | R_SCI_B0_CFCLR_DPERC_Msk | R_SCI_B0_CFCLR_DCMFC_Msk |
            R_SCI_B0_CFCLR_ERSC_Msk;
    ffclr = R_SCI_B0_FFCLR_DRC_Msk;

    /* Set FCR. Reset FIFO/data registers. */
    p_ctrl->p_reg->FCR = R_SCI_B0_FCR_TFRST_Msk | R_SCI_B0_FCR_RFRST_Msk;

    /* Write all settings except MOD[2:0] to CCR3 (See Table 26.36 in RA6T2 manual R01UH0951EJ0130). */
    p_ctrl->p_reg->CCR3 = ccr3 & ~(R_SCI_B0_CCR3_MOD_Msk);

    /* Write settings to registers. */
    p_ctrl->p_reg->CCR3  = ccr3;
    p_ctrl->p_reg->CCR2  = ccr2;
    p_ctrl->p_reg->CCR1  = ccr1;
    p_ctrl->p_reg->CCR4  = ccr4;
    p_ctrl->p_reg->CFCLR = cfclr;
    p_ctrl->p_reg->FFCLR = ffclr;
    p_ctrl->p_reg->CCR0  = ccr0;
}

#if SCI_B_SPI_DTC_SUPPORT_ENABLE == 1

/*******************************************************************************************************************//**
 * Configures SCI SPI related transfer drivers (if enabled).
 *
 * @param[in]     p_cfg                     Pointer to SCI SPI specific configuration structure.
 * @param[in]     p_fsp_feature             FSP feature.
 *
 * @retval        FSP_SUCCESS               Operation successfully completed.
 * @retval        FSP_ERR_ASSERTION         One of the following invalid parameters passed:
 *                                          - Pointer p_cfg is NULL
 *                                          - Interrupt is not enabled
 * @retval        FSP_ERR_INVALID_ARGUMENT  DTC is used for data transmission but not used for data reception or
 *                                          vice versa.
 **********************************************************************************************************************/
static fsp_err_t r_sci_b_spi_transfer_config (sci_b_spi_instance_ctrl_t * const p_ctrl)
{
    fsp_err_t               err   = FSP_SUCCESS;
    spi_cfg_t const * const p_cfg = p_ctrl->p_cfg;

    if (NULL != p_cfg->p_transfer_rx)
    {
        /* Set the initial configuration for the rx transfer instance. */
        transfer_instance_t const * p_transfer = p_cfg->p_transfer_rx;
        p_transfer->p_cfg->p_info->transfer_settings_word = SCI_B_SPI_PRV_DTC_RX_TRANSFER_SETTINGS;
        p_transfer->p_cfg->p_info->p_src = (void *) &p_ctrl->p_reg->RDR;

        /* Open the transfer instance. */
        err = p_transfer->p_api->open(p_transfer->p_ctrl, p_transfer->p_cfg);
        FSP_ERROR_RETURN(FSP_SUCCESS == err, err);
    }

    if (NULL != p_cfg->p_transfer_tx)
    {
        /* Set the initial configuration for the tx transfer instance. */
        transfer_instance_t const * p_transfer = p_cfg->p_transfer_tx;
        p_transfer->p_cfg->p_info->transfer_settings_word = SCI_B_SPI_PRV_DTC_TX_TRANSFER_SETTINGS;
        p_transfer->p_cfg->p_info->p_dest                 = (void *) &p_ctrl->p_reg->TDR;

        /* Open the transfer instance. */
        err = p_transfer->p_api->open(p_transfer->p_ctrl, p_transfer->p_cfg);
        if (FSP_SUCCESS != err)
        {
            if (NULL != p_cfg->p_transfer_rx)
            {
                /* If the tx transfer instance could not be opened, close the rx transfer instance. */
                p_cfg->p_transfer_rx->p_api->close(p_cfg->p_transfer_rx->p_ctrl);
            }

            return err;
        }
    }

    return err;
}

#endif

/*******************************************************************************************************************//**
 * Initiates writ or read process. Common routine used by SPI API write or read functions.
 *
 * @param[in]  p_ctrl             Pointer to the control block.
 * @param[in]  p_src              Pointer to data buffer which need to be sent.
 * @param[out] p_dest             Pointer to buffer where received data will be stored.
 * @param[in]  length             Number of data transactions to be performed.
 *
 * @retval     FSP_SUCCESS        Operation successfully completed.
 * @retval     FSP_ERR_NOT_OPEN   The channel has not been opened. Open the channel first.
 * @retval     FSP_ERR_ASSERTION  One of the following invalid parameters passed:
 *                                  - Pointer p_ctrl is NULL
 *                                  - length == 0
 *                                  - if DTC is used and length > UINT16_MAX
 * @retval     FSP_ERR_IN_USE     A transfer is already in progress.
 *
 * @return     See @ref RENESAS_ERROR_CODES or functions called by this function for other possible return codes. This
 *             function calls:
 *               - @ref transfer_api_t::reconfigure
 **********************************************************************************************************************/
static fsp_err_t r_sci_b_spi_write_read_common (sci_b_spi_instance_ctrl_t * const p_ctrl,
                                                void const                      * p_src,
                                                void                            * p_dest,
                                                uint32_t const                    length)
{
#if SCI_B_SPI_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_ctrl);
    FSP_ERROR_RETURN(SCI_B_SPI_OPEN == p_ctrl->open, FSP_ERR_NOT_OPEN);
    FSP_ASSERT(0 != length);
    if ((NULL != p_ctrl->p_cfg->p_transfer_tx) || (NULL != p_ctrl->p_cfg->p_transfer_rx))
    {
        /* The DTC is only capable of a max of 64K transfers. */
        FSP_ASSERT(length <= UINT16_MAX);
    }
#endif

    /* TE and RE must be zero in order to write one to TE or RE (TE and RE will only be set if there is a transfer in
     * progress. Reference section 26.2.5 Serial Control Register (SCR) in the RA6T2 manual r01uh0951ej0100-ra6t2. */
    FSP_ERROR_RETURN(0 == (p_ctrl->p_reg->CCR0 & (R_SCI_B0_CCR0_RE_Msk | R_SCI_B0_CCR0_TE_Msk)), FSP_ERR_IN_USE);

    /* Setup the control block. */
    p_ctrl->count    = length;
    p_ctrl->tx_count = 0U;
    p_ctrl->rx_count = 0U;
    p_ctrl->p_src    = (uint8_t *) p_src;
    p_ctrl->p_dest   = (uint8_t *) p_dest;

#if SCI_B_SPI_DTC_SUPPORT_ENABLE == 1
    if (p_ctrl->p_cfg->p_transfer_tx)
    {
        /* Configure the tx transfer instance. */
        p_ctrl->tx_count = length;
        transfer_instance_t const * p_transfer = p_ctrl->p_cfg->p_transfer_tx;
        p_transfer->p_cfg->p_info->length = (uint16_t) length;

        if (NULL == p_src)
        {
            /* If the source is NULL transmit using a dummy value using FIXED mode. */
            static uint8_t tx_dummy = 0;
            p_transfer->p_cfg->p_info->transfer_settings_word_b.src_addr_mode = TRANSFER_ADDR_MODE_FIXED;
            p_transfer->p_cfg->p_info->p_src = &tx_dummy;
        }
        else
        {
            p_transfer->p_cfg->p_info->transfer_settings_word_b.src_addr_mode = TRANSFER_ADDR_MODE_INCREMENTED;
            p_transfer->p_cfg->p_info->p_src = p_src;
        }

        /* Enable the transfer instance. */
        fsp_err_t err = p_transfer->p_api->reconfigure(p_transfer->p_ctrl, p_transfer->p_cfg->p_info);
        FSP_ERROR_RETURN(FSP_SUCCESS == err, err);
    }

    /* The rx transfer instance is not used if p_dest is NULL. */
    if ((NULL != p_ctrl->p_cfg->p_transfer_rx) && (NULL != p_dest))
    {
        /* Configure the rx transfer instance. */
        p_ctrl->rx_count = length;
        transfer_instance_t const * p_transfer = p_ctrl->p_cfg->p_transfer_rx;

        /* Enable the transfer instance. */
        fsp_err_t err = p_transfer->p_api->reset(p_transfer->p_ctrl, NULL, p_dest, (uint16_t) length);
        FSP_ERROR_RETURN(FSP_SUCCESS == err, err);
    }
#endif

    /* Enable transmit and receive interrupts. */
    r_sci_b_spi_start_transfer(p_ctrl);

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Enables and disables Receive and Transmit mode based on the current configuration.
 *
 * @param      p_ctrl          Pointer to control structure.
 **********************************************************************************************************************/
static void r_sci_b_spi_start_transfer (sci_b_spi_instance_ctrl_t * const p_ctrl)
{
    /* TE must always be enabled even when receiving data. When RE is enabled without also enabling TE, the SCI will
     * continue transferring data until the RE bit is cleared. At high bitrates, it is not possible to clear the RE bit
     * fast enough and there will be additional clock pulses at the end of the transfer. */
    uint32_t interrupt_settings = R_SCI_B0_CCR0_TE_Msk;

    if ((NULL == p_ctrl->p_dest) || (NULL != p_ctrl->p_cfg->p_transfer_tx) || (NULL != p_ctrl->p_cfg->p_transfer_rx))
    {
        /* Enable the transmit IRQ. */
        interrupt_settings |= R_SCI_B0_CCR0_TIE_Msk;
    }

    if (NULL != p_ctrl->p_dest)
    {
        /* Enable Receive mode and the Receive buffer full IRQ. */
        interrupt_settings |= (R_SCI_B0_CCR0_RE_Msk | R_SCI_B0_CCR0_RIE_Msk);
    }

    /* Write the transfer settings. */
    p_ctrl->p_reg->CCR0 |= interrupt_settings;

    /* Transmit from RXI interrupt. */
    if ((NULL == p_ctrl->p_cfg->p_transfer_tx) && (NULL == p_ctrl->p_cfg->p_transfer_rx) && (NULL != p_ctrl->p_dest))
    {
        /* The rxi interrupt must be disabled so that r_sci_b_spi_transmit is not interrupted before it updates the
         * tx_count. */
        R_BSP_IrqDisable(p_ctrl->p_cfg->rxi_irq);

        /* When transmitting from the RXI interrupt, the first byte must be written here because the transmit buffer
         * empty IRQ is disabled. */
        r_sci_b_spi_transmit(p_ctrl);

        if ((SPI_MODE_SLAVE == p_ctrl->p_cfg->operating_mode) && (1 < p_ctrl->count))
        {
            /* First call writes directly to the TSR register. The second call writes to the TDR register. */
            r_sci_b_spi_transmit(p_ctrl);
        }

        /* In master mode the rxi interrupt will fire as soon as it is enabled. */
        R_BSP_IrqEnableNoClear(p_ctrl->p_cfg->rxi_irq);
    }
}

/*******************************************************************************************************************//**
 * Transmit a single byte of data.
 * @param      p_ctrl          Pointer to the control structure.
 **********************************************************************************************************************/
static void r_sci_b_spi_transmit (sci_b_spi_instance_ctrl_t * p_ctrl)
{
    if (p_ctrl->tx_count < p_ctrl->count)
    {
        if (p_ctrl->p_src)
        {
            p_ctrl->p_reg->TDR = (SCI_B_SPI_PRV_DATA_REG_MASK | (p_ctrl->p_src[p_ctrl->tx_count]));
        }
        else
        {
            /* Do a dummy write if there is no tx buffer. */
            p_ctrl->p_reg->TDR = (SCI_B_SPI_PRV_DATA_REG_MASK | 0U);
        }

        p_ctrl->tx_count++;
    }
}

/*******************************************************************************************************************//**
 * Calls user callback.
 *
 * @param[in]     p_ctrl     Pointer to SPI instance control block
 * @param[in]     event      Event code
 **********************************************************************************************************************/
static void r_sci_b_spi_call_callback (sci_b_spi_instance_ctrl_t * p_ctrl, spi_event_t event)
{
    spi_callback_args_t args;

    /* Store callback arguments in memory provided by user if available.  This allows callback arguments to be
     * stored in non-secure memory so they can be accessed by a non-secure callback function. */
    spi_callback_args_t * p_args = p_ctrl->p_callback_memory;
    if (NULL == p_args)
    {
        /* Store on stack */
        p_args = &args;
    }
    else
    {
        /* Save current arguments on the stack in case this is a nested interrupt. */
        args = *p_args;
    }

    p_args->channel   = p_ctrl->p_cfg->channel;
    p_args->event     = event;
    p_args->p_context = p_ctrl->p_context;

#if BSP_TZ_SECURE_BUILD

    /* p_callback can point to a secure function or a non-secure function. */
    if (!cmse_is_nsfptr(p_ctrl->p_callback))
    {
        /* If p_callback is secure, then the project does not need to change security state. */
        p_ctrl->p_callback(p_args);
    }
    else
    {
        /* If p_callback is Non-secure, then the project must change to Non-secure state in order to call the callback. */
        sci_b_spi_prv_ns_callback p_callback = (sci_b_spi_prv_ns_callback) (p_ctrl->p_callback);
        p_callback(p_args);
    }

#else

    /* If the project is not Trustzone Secure, then it will never need to change security state in order to call the callback. */
    p_ctrl->p_callback(p_args);
#endif
    if (NULL != p_ctrl->p_callback_memory)
    {
        /* Restore callback memory in case this is a nested interrupt. */
        *p_ctrl->p_callback_memory = args;
    }
}

/*******************************************************************************************************************//**
 * This function is the ISR handler for R_SCI_B_SPI Transmit Buffer Empty IRQ.
 *
 * The Transmit Buffer Empty IRQ is enabled in the following conditions:
 *   - The transfer is started using R_SCI_B_SPI_Write API (There is no data to receive).
 *   - The rxi IRQ is serviced using a DTC instance.
 *   - The txi IRQ is serviced using a DTC instance (The interrupt will fire on the last byte transferred).
 *
 **********************************************************************************************************************/
void sci_b_spi_txi_isr (void)
{
    /* Save context if RTOS is used. */
    FSP_CONTEXT_SAVE
    IRQn_Type irq = R_FSP_CurrentIrqGet();
    R_BSP_IrqStatusClear(irq);
    sci_b_spi_instance_ctrl_t * p_ctrl = (sci_b_spi_instance_ctrl_t *) R_FSP_IsrContextGet(irq);

    /* Write the next byte to the TDR register. */
    r_sci_b_spi_transmit(p_ctrl);

    if ((p_ctrl->tx_count == p_ctrl->count) && (NULL == p_ctrl->p_dest))
    {
        /* If the last byte is transmitted and there is no data to receive then enable the transmit end IRQ and disable
         * the transmit IRQ. */

        /* After all data has been transmitted, disable transmit interrupts and enable the transmit end interrupt. */
        uint32_t ccr0_temp = p_ctrl->p_reg->CCR0;
        ccr0_temp          |= R_SCI_B0_CCR0_TEIE_Msk;
        ccr0_temp          &= (uint32_t) ~(R_SCI_B0_CCR0_TIE_Msk);
        p_ctrl->p_reg->CCR0 = ccr0_temp;
    }

    /* Restore context if RTOS is used. */
    FSP_CONTEXT_RESTORE
}

/*******************************************************************************************************************//**
 * This function is the ISR handler for R_SCI_B_SPI Receive Buffer Full IRQ.
 * This handler also handles Transmit Buffer Empty IRQs.
 *
 * The Receive Buffer Full IRQ is enabled in the following conditions:
 *   - The transfer is started using either the R_SCI_B_SPI_Read or R_SCI_B_SPI_WriteRead API.
 *
 **********************************************************************************************************************/
void sci_b_spi_rxi_isr (void)
{
    /* Save context if RTOS is used. */
    FSP_CONTEXT_SAVE

    IRQn_Type irq = R_FSP_CurrentIrqGet();
    R_BSP_IrqStatusClear(irq);
    sci_b_spi_instance_ctrl_t * p_ctrl = (sci_b_spi_instance_ctrl_t *) R_FSP_IsrContextGet(irq);

    /* Write the next byte to the TDR register
     * (Whenever the rxi isr is enabled, the transmit isr is disabled and transmit is handled here). */
    r_sci_b_spi_transmit(p_ctrl);

    /* Read the next byte from the RDR register. */
    if (p_ctrl->rx_count < p_ctrl->count)
    {
        p_ctrl->p_dest[p_ctrl->rx_count++] = (uint8_t) (p_ctrl->p_reg->RDR & SCI_B_SPI_PRV_RDAT_MASK);
    }

    if (p_ctrl->rx_count == p_ctrl->count)
    {
        /* If the last byte is received then enable the transmit end IRQ and disable the receive and transmit IRQs. */

        uint32_t ccr0_temp = p_ctrl->p_reg->CCR0;
        ccr0_temp          |= R_SCI_B0_CCR0_TEIE_Msk;
        ccr0_temp          &= (uint32_t) ~(R_SCI_B0_CCR0_TIE_Msk | R_SCI_B0_CCR0_RIE_Msk);
        p_ctrl->p_reg->CCR0 = ccr0_temp;
    }

    /* Restore context if RTOS is used. */
    FSP_CONTEXT_RESTORE
}

/*******************************************************************************************************************//**
 * This function is the ISR handler for R_SCI_SPI Transmit End IRQ.
 *
 * The Transmit End IRQ is enabled after the last byte of data has been transferred.
 *
 **********************************************************************************************************************/
void sci_b_spi_tei_isr (void)
{
    /* Save context if RTOS is used. */
    FSP_CONTEXT_SAVE

    IRQn_Type irq = R_FSP_CurrentIrqGet();
    sci_b_spi_instance_ctrl_t * p_ctrl = (sci_b_spi_instance_ctrl_t *) R_FSP_IsrContextGet(irq);

    /* Disables receiver, transmitter and transmit end IRQ. */

    uint32_t ccr0_temp = p_ctrl->p_reg->CCR0;
    ccr0_temp &=
        (uint32_t) ~(R_SCI_B0_CCR0_TIE_Msk | R_SCI_B0_CCR0_TE_Msk | R_SCI_B0_CCR0_RE_Msk | R_SCI_B0_CCR0_TEIE_Msk);
    p_ctrl->p_reg->CCR0 = ccr0_temp;

    /* Notify the user that the transfer has completed. */
    r_sci_b_spi_call_callback(p_ctrl, SPI_EVENT_TRANSFER_COMPLETE);

    R_BSP_IrqStatusClear(irq);

    /* Restore context if RTOS is used. */
    FSP_CONTEXT_RESTORE
}

/*******************************************************************************************************************//**
 * This function is the ISR handler for  R_SCI_B_SPI Error IRQs.
 *
 * This handler is only enabled if the user passes in a valid IRQ number in Pointer to a configuration structure.
 * structure.
 **********************************************************************************************************************/
void sci_b_spi_eri_isr (void)
{
    /* Save context if RTOS is used. */
    FSP_CONTEXT_SAVE

    IRQn_Type irq = R_FSP_CurrentIrqGet();
    sci_b_spi_instance_ctrl_t * p_ctrl = (sci_b_spi_instance_ctrl_t *) R_FSP_IsrContextGet(irq);

    /* Disables receiver, transmitter and transmit end IRQ. */
    p_ctrl->p_reg->CCR0 &= (uint32_t) ~(R_SCI_B0_CCR0_TIE_Msk | R_SCI_B0_CCR0_RIE_Msk | R_SCI_B0_CCR0_TEIE_Msk);

    /* Clear the error status flags (The only possible error is an RX overflow). */

    p_ctrl->p_reg->CFCLR = R_SCI_B0_CFCLR_ORERC_Msk;

    /* Notify the user that an error occurred. */
    r_sci_b_spi_call_callback(p_ctrl, SPI_EVENT_ERR_READ_OVERFLOW);

    /* Clear pending IRQ to make sure it doesn't fire again after exiting. */
    R_BSP_IrqStatusClear(irq);

    /* Restore context if RTOS is used. */
    FSP_CONTEXT_RESTORE
}
