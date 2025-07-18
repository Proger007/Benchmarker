/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#ifndef R_COMPARATOR_API_H
#define R_COMPARATOR_API_H

/*******************************************************************************************************************//**
 * @defgroup COMPARATOR_API Comparator Interface
 * @ingroup RENESAS_ANALOG_INTERFACES
 * @brief Interface for comparators.
 *
 * @section COMPARATOR_API_SUMMARY Summary
 * The comparator interface provides standard comparator functionality, including generating an event when the
 * comparator result changes.
 *
 *
 * @{
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/

/** Includes board and MCU related header files. */
#include "bsp_api.h"

/* Common macro for FSP header files. There is also a corresponding FSP_FOOTER macro at the end of this file. */
FSP_HEADER

/**********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

/*****************************************************************************
 * Typedef definitions
 ******************************************************************************/

/** Comparator control block.  Allocate an instance specific control block to pass into the comparator API calls.
 */
typedef void comparator_ctrl_t;

/** Select whether to invert the polarity of the comparator output. */
typedef enum e_comparator_mode
{
    COMPARATOR_MODE_NORMAL = 0,        ///< Normal mode
    COMPARATOR_MODE_WINDOW = 1,        ///< Window mode, not supported by all implementations
} comparator_mode_t;

/** Trigger type: rising edge, falling edge, both edges, low level. */
typedef enum e_comparator_trigger
{
    COMPARATOR_TRIGGER_RISING    = 1,  ///< Rising edge trigger
    COMPARATOR_TRIGGER_FALLING   = 2,  ///< Falling edge trigger
    COMPARATOR_TRIGGER_BOTH_EDGE = 3,  ///< Both edges trigger
} comparator_trigger_t;

/** Select whether to invert the polarity of the comparator output. */
typedef enum e_comparator_polarity_invert
{
    COMPARATOR_POLARITY_INVERT_OFF = 0, ///< Do not invert polarity
    COMPARATOR_POLARITY_INVERT_ON  = 1, ///< Invert polarity
} comparator_polarity_invert_t;

/** Select whether to include the comparator output on the output pin. */
typedef enum e_comparator_pin_output
{
    COMPARATOR_PIN_OUTPUT_OFF = 0,     ///< Do not include comparator output on output pin
    COMPARATOR_PIN_OUTPUT_ON  = 1,     ///< Include comparator output on output pin
} comparator_pin_output_t;

/** Comparator digital filtering sample clock divisor settings. */
typedef enum e_comparator_filter
{
    COMPARATOR_FILTER_OFF = 0,         ///< Disable debounce filter
    COMPARATOR_FILTER_1   = 4,         ///< Filter using PCLK divided by 1, not supported by all implementations
    COMPARATOR_FILTER_8   = 1,         ///< Filter using PCLK divided by 8
    COMPARATOR_FILTER_16  = 2,         ///< Filter using PCLK divided by 16, not supported by all implementations
    COMPARATOR_FILTER_32  = 3,         ///< Filter using PCLK divided by 32
} comparator_filter_t;

/** Current comparator state. */
typedef enum e_comparator_state
{
    COMPARATOR_STATE_OUTPUT_LOW      = 0, ///< VCMP < VREF if polarity is not inverted, VCMP > VREF if inverted
    COMPARATOR_STATE_OUTPUT_HIGH     = 1, ///< VCMP > VREF if polarity is not inverted, VCMP < VREF if inverted
    COMPARATOR_STATE_OUTPUT_DISABLED = 2, ///< @ref comparator_api_t::outputEnable() has not been called
} comparator_state_t;

/** Comparator information. */
typedef struct st_comparator_info
{
    uint32_t min_stabilization_wait_us; ///< Minimum stabilization wait time in microseconds
} comparator_info_t;

/** Comparator status. */
typedef struct st_comparator_status
{
    comparator_state_t state;          ///< Current comparator state
} comparator_status_t;

/** Callback function parameter data */
typedef struct st_comparator_callback_args
{
    /** Placeholder for user data. Set in @ref comparator_api_t::open function in @ref comparator_cfg_t. */
    void   * p_context;
    uint32_t channel;                  ///< The physical hardware channel that caused the interrupt.
} comparator_callback_args_t;

/** User configuration structure, used in open function */
typedef struct st_comparator_cfg
{
    uint8_t                      channel;     ///< Hardware channel used.
    comparator_mode_t            mode;        ///< Normal or window mode
    comparator_trigger_t         trigger;     ///< Trigger setting.
    comparator_filter_t          filter;      ///< Digital filter clock divisor setting.
    comparator_polarity_invert_t invert;      ///< Whether to invert output
    comparator_pin_output_t      pin_output;  ///< Whether to include output on output pin
    uint8_t                      vref_select; ///< Internal Vref Select
    uint8_t                      ipl;         ///< Interrupt priority
    IRQn_Type                    irq;         ///< NVIC interrupt number

    /** Callback called when comparator event occurs. */
    void (* p_callback)(comparator_callback_args_t * p_args);

    /** Placeholder for user data.  Passed to the user callback in @ref comparator_callback_args_t. */
    void       * p_context;
    void const * p_extend;             ///< Comparator hardware dependent configuration.
} comparator_cfg_t;

/** Comparator functions implemented at the HAL layer will follow this API. */
typedef struct st_comparator_api
{
    /** Initialize the comparator.
     *
     * @param[in]  p_ctrl  Pointer to instance control block
     * @param[in]  p_cfg   Pointer to configuration
     */
    fsp_err_t (* open)(comparator_ctrl_t * const p_ctrl, comparator_cfg_t const * const p_cfg);

    /** Start the comparator.
     *
     * @param[in]  p_ctrl         Pointer to instance control block
     */
    fsp_err_t (* outputEnable)(comparator_ctrl_t * const p_ctrl);

    /** Provide information such as the recommended minimum stabilization wait time.
     *
     * @param[in]   p_ctrl       Pointer to instance control block
     * @param[out]  p_info       Comparator information stored here
     */
    fsp_err_t (* infoGet)(comparator_ctrl_t * const p_ctrl, comparator_info_t * const p_info);

    /** Provide current comparator status.
     *
     * @param[in]   p_ctrl       Pointer to instance control block
     * @param[out]  p_status     Status stored here
     */
    fsp_err_t (* statusGet)(comparator_ctrl_t * const p_ctrl, comparator_status_t * const p_status);

    /** Stop the comparator.
     *
     * @param[in]  p_ctrl   Pointer to instance control block
     */
    fsp_err_t (* close)(comparator_ctrl_t * const p_ctrl);
} comparator_api_t;

/** This structure encompasses everything that is needed to use an instance of this interface. */
typedef struct st_comparator_instance
{
    comparator_ctrl_t      * p_ctrl;   ///< Pointer to the control structure for this instance
    comparator_cfg_t const * p_cfg;    ///< Pointer to the configuration structure for this instance
    comparator_api_t const * p_api;    ///< Pointer to the API structure for this instance
} comparator_instance_t;

/* Common macro for FSP header files. There is also a corresponding FSP_HEADER macro at the top of this file. */
FSP_FOOTER

/*******************************************************************************************************************//**
 * @} (end defgroup COMPARATOR_API)
 **********************************************************************************************************************/
#endif
