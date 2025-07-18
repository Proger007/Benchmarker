/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#ifndef R_SCI_B_SPI_H
#define R_SCI_B_SPI_H

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/
#include "r_spi_api.h"

/* Common macro for FSP header files. There is also a corresponding FSP_FOOTER macro at the end of this file. */
FSP_HEADER

/*****************************************************************************************************************//**
 * @ingroup SCI_B_SPI
 * @{
 ********************************************************************************************************************/

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/** Settings for adjusting the SPI CLK. */
typedef struct
{
    uint8_t brr;
    uint8_t cks  : 2;
    uint8_t bgdm : 1;
} sci_b_spi_div_setting_t;

/** Source clock selection options for SCI. */
typedef enum e_sci_b_spi_clock_source
{
    SCI_B_SPI_SOURCE_CLOCK_SCISPICLK = 0,
    SCI_B_SPI_SOURCE_CLOCK_PCLK      = 1,
} sci_b_spi_clock_source_t;

/** SCI SPI extended configuration */
typedef struct st_sci_b_spi_extended_cfg
{
    sci_b_spi_div_setting_t clk_div;

    /** Clock source to generate SCK can either be selected as PCLK or SCISPICLK. */
    sci_b_spi_clock_source_t clock_source;
} sci_b_spi_extended_cfg_t;

/** SPI instance control block. DO NOT INITIALIZE. */
typedef struct st_sci_b_spi_instance_ctrl
{
    uint32_t          open;
    spi_cfg_t const * p_cfg;
    R_SCI_B0_Type   * p_reg;
    uint8_t         * p_src;
    uint8_t         * p_dest;
    uint32_t          tx_count;
    uint32_t          rx_count;
    uint32_t          count;

    /* Pointer to callback and optional working memory */
    void (* p_callback)(spi_callback_args_t *);
    spi_callback_args_t * p_callback_memory;

    /* Pointer to context to be passed into callback function */
    void * p_context;
} sci_b_spi_instance_ctrl_t;

/**********************************************************************************************************************
 * Exported global variables
 **********************************************************************************************************************/

/** @cond INC_HEADER_DEFS_SEC */
/** Filled in Interface API structure for this Instance. */
extern const spi_api_t g_spi_on_sci_b;

/** @endcond */

/**********************************************************************************************************************
 * Public Function Prototypes
 **********************************************************************************************************************/
fsp_err_t R_SCI_B_SPI_Open(spi_ctrl_t * p_api_ctrl, spi_cfg_t const * const p_cfg);
fsp_err_t R_SCI_B_SPI_Read(spi_ctrl_t * const    p_api_ctrl,
                           void                * p_dest,
                           uint32_t const        length,
                           spi_bit_width_t const bit_width);
fsp_err_t R_SCI_B_SPI_Write(spi_ctrl_t * const    p_api_ctrl,
                            void const          * p_src,
                            uint32_t const        length,
                            spi_bit_width_t const bit_width);
fsp_err_t R_SCI_B_SPI_WriteRead(spi_ctrl_t * const    p_api_ctrl,
                                void const          * p_src,
                                void                * p_dest,
                                uint32_t const        length,
                                spi_bit_width_t const bit_width);
fsp_err_t R_SCI_B_SPI_Close(spi_ctrl_t * const p_api_ctrl);
fsp_err_t R_SCI_B_SPI_CalculateBitrate(uint32_t                  bitrate,
                                       sci_b_spi_clock_source_t  clock_source,
                                       sci_b_spi_div_setting_t * sclk_div);
fsp_err_t R_SCI_B_SPI_CallbackSet(spi_ctrl_t * const          p_api_ctrl,
                                  void (                    * p_callback)(spi_callback_args_t *),
                                  void * const                p_context,
                                  spi_callback_args_t * const p_callback_memory);

/* Common macro for FSP header files. There is also a corresponding FSP_HEADER macro at the top of this file. */
FSP_FOOTER

#endif

/*******************************************************************************************************************//**
 * @} (end ingroup SCI_B_SPI)
 **********************************************************************************************************************/
