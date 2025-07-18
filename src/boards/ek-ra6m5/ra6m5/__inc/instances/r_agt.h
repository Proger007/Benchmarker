/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#ifndef R_AGT_H
#define R_AGT_H

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/
#include "bsp_api.h"
#include "r_agt_cfg.h"
#include "r_timer_api.h"

/* Common macro for FSP header files. There is also a corresponding FSP_FOOTER macro at the end of this file. */
FSP_HEADER

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

/* Leading zeroes removed to avoid coding standards violation. */

/** Maximum number of clock counts for standard AGT peripheral. */
#define AGT_MAX_CLOCK_COUNTS_16BIT    (UINT16_MAX)

/** Maximum number of clock counts for AGTW peripheral. */
#define AGT_MAX_CLOCK_COUNTS_32BIT    (UINT32_MAX)

/** Maximum period value allowed for standard AGT peripheral. */
#define AGT_MAX_PERIOD_16BIT          (UINT16_MAX + 1U)

/** Maximum period valud allowed for AGTW peripheral. */
#define AGT_MAX_PERIOD_32BIT          (UINT32_MAX)

/*******************************************************************************************************************//**
 * @addtogroup AGT
 * @{
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/** Count source */
typedef enum e_agt_clock
{
    AGT_CLOCK_PCLKB         = 0x00,    ///< PCLKB count source, division by 1, 2, or 8 allowed
    AGT_CLOCK_LOCO          = 0x40,    ///< LOCO count source, division by 1, 2, 4, 8, 16, 32, 64, or 128 allowed
    AGT_CLOCK_AGT_UNDERFLOW = 0x50,    ///< Underflow event signal from next lowest AGT channel, division must be 1
    AGT_CLOCK_SUBCLOCK      = 0x60,    ///< Subclock count source, division by 1, 2, 4, 8, 16, 32, 64, or 128 allowed
    AGT_CLOCK_P402          = 0x92,    ///< Counts events on P402, events are counted in deep software standby mode
    AGT_CLOCK_P403          = 0x93,    ///< Counts events on P403, events are counted in deep software standby mode
    AGT_CLOCK_P404          = 0x91,    ///< Counts events on P404, events are counted in deep software standby mode
    AGT_CLOCK_AGTIO         = 0x80,    ///< Counts events on AGTIOn, events are not counted in software standby modes
} agt_clock_t;

/** Enable pin for event counting mode. */
typedef enum e_agt_measure
{
    AGT_MEASURE_DISABLED               = 1U,    ///< AGT used as a counter
    AGT_MEASURE_PULSE_WIDTH_LOW_LEVEL  = 3U,    ///< AGT used to measure low level pulse width
    AGT_MEASURE_PULSE_WIDTH_HIGH_LEVEL = 0x13U, ///< AGT used to measure high level pulse width
    AGT_MEASURE_PULSE_PERIOD           = 4U,    ///< AGT used to measure pulse period
} agt_measure_t;

/** Input filter, applies AGTIO in pulse period measurement, pulse width measurement, or event counter mode. The filter
 * requires the signal to be at the same level for 3 successive reads at the specified filter frequency. */
typedef enum e_agt_agtio_filter
{
    AGT_AGTIO_FILTER_NONE         = 0x00U, ///< No filter
    AGT_AGTIO_FILTER_PCLKB        = 0x10U, ///< Filter at PCLKB
    AGT_AGTIO_FILTER_PCLKB_DIV_8  = 0x20U, ///< Filter at PCLKB / 8
    AGT_AGTIO_FILTER_PCLKB_DIV_32 = 0x30U, ///< Filter at PCLKB / 32
} agt_agtio_filter_t;

/** Enable pin for event counting mode. */
typedef enum e_agt_enable_pin
{
    AGT_ENABLE_PIN_NOT_USED    = 0U,    ///< AGTEE/AGTWEE is not used
    AGT_ENABLE_PIN_ACTIVE_LOW  = 0x40U, ///< Events are only counted when AGTEE/AGTWEE is low
    AGT_ENABLE_PIN_ACTIVE_HIGH = 0x44U, ///< Events are only counted when AGTEE/AGTWEE is high
} agt_enable_pin_t;

/** Trigger edge for pulse period measurement mode and event counting mode. */
typedef enum e_agt_trigger_edge
{
    AGT_TRIGGER_EDGE_RISING  = 0U,     ///< Measurement starts or events are counted on rising edge
    AGT_TRIGGER_EDGE_FALLING = 1U,     ///< Measurement starts or events are counted on falling edge
    AGT_TRIGGER_EDGE_BOTH    = 8U,     ///< Events are counted on both edges (n/a for pulse period mode)
} agt_trigger_edge_t;

/** Output pins, used to select which duty cycle to update in R_AGT_DutyCycleSet(). */
typedef enum e_agt_output_pin
{
    AGT_OUTPUT_PIN_AGTOA = 0,          ///< AGTOA
    AGT_OUTPUT_PIN_AGTOB = 1,          ///< AGTOB
} agt_output_pin_t;

/** Level of AGT pin */
typedef enum e_agt_pin_cfg
{
    AGT_PIN_CFG_DISABLED         = 0,  ///< Not used as output pin
    AGT_PIN_CFG_START_LEVEL_LOW  = 3,  ///< Pin level low
    AGT_PIN_CFG_START_LEVEL_HIGH = 7,  ///< Pin level high
} agt_pin_cfg_t;

/** Counter type to determine regsiter size */
typedef enum e_agt_counter_bit_width
{
    AGT_COUNTER_BIT_WIDTH_DEFAULT = 0, ///< Legacy
    AGT_COUNTER_BIT_WIDTH_16      = 1, ///< AGT
    AGT_COUNTER_BIT_WIDTH_32      = 2, ///< AGTW
} agt_counter_bit_width_t;

/** Channel control block. DO NOT INITIALIZE.  Initialization occurs when @ref timer_api_t::open is called. */
typedef struct st_agt_instance_ctrl
{
    uint32_t            open;                     // Whether or not channel is open
    const timer_cfg_t * p_cfg;                    // Pointer to initial configurations
    R_AGTX0_Type      * p_reg;                    // Base register for this channel
    bool                is_agtw;                  // Whether or not this channel is agtw, otherwise it is agt
    uint32_t            period;                   // Current timer period (counts)

    void (* p_callback)(timer_callback_args_t *); // Pointer to callback that is called when a timer_event_t occurs.
    timer_callback_args_t * p_callback_memory;    // Pointer to non-secure memory that can be used to pass arguments to a callback in non-secure memory.
    void * p_context;                             // Pointer to context to be passed into callback function
} agt_instance_ctrl_t;

/** Optional AGT extension data structure.*/
typedef struct st_agt_extended_cfg
{
    agt_clock_t count_source;          ///< AGT channel clock source. Valid values are: AGT_CLOCK_PCLKB, AGT_CLOCK_LOCO, AGT_CLOCK_FSUB

    /* Output pin settings. */
    union
    {
        uint8_t agtoab_settings;

        struct
        {
            agt_pin_cfg_t agtoa : 3;           ///< Configure AGTOA/AGTWOA pin
            uint8_t             : 1;
            agt_pin_cfg_t agtob : 3;           ///< Configure AGTOB/AGTWOB pin
        } agtoab_settings_b;
    };
    agt_pin_cfg_t agto : 3;                    ///< Configure AGTO pin @note AGTIO polarity is opposite AGTO

    /* Input pin settings. */
    agt_measure_t           measurement_mode;  ///< Measurement mode
    agt_agtio_filter_t      agtio_filter;      ///< Input filter for AGTIO
    agt_enable_pin_t        enable_pin;        ///< Enable pin (event counting only)
    agt_trigger_edge_t      trigger_edge;      ///< Trigger edge to start pulse period measurement or count external event
    agt_counter_bit_width_t counter_bit_width; ///< Counter bit width
} agt_extended_cfg_t;

/**********************************************************************************************************************
 * Exported global variables
 **********************************************************************************************************************/

/** @cond INC_HEADER_DEFS_SEC */
/** Filled in Interface API structure for this Instance. */
extern const timer_api_t g_timer_on_agt;

/** @endcond */

fsp_err_t R_AGT_Close(timer_ctrl_t * const p_ctrl);
fsp_err_t R_AGT_PeriodSet(timer_ctrl_t * const p_ctrl, uint32_t const period_counts);
fsp_err_t R_AGT_DutyCycleSet(timer_ctrl_t * const p_ctrl, uint32_t const duty_cycle_counts, uint32_t const pin);
fsp_err_t R_AGT_Reset(timer_ctrl_t * const p_ctrl);
fsp_err_t R_AGT_Start(timer_ctrl_t * const p_ctrl);
fsp_err_t R_AGT_Enable(timer_ctrl_t * const p_ctrl);
fsp_err_t R_AGT_Disable(timer_ctrl_t * const p_ctrl);
fsp_err_t R_AGT_InfoGet(timer_ctrl_t * const p_ctrl, timer_info_t * const p_info);
fsp_err_t R_AGT_StatusGet(timer_ctrl_t * const p_ctrl, timer_status_t * const p_status);
fsp_err_t R_AGT_Stop(timer_ctrl_t * const p_ctrl);
fsp_err_t R_AGT_Open(timer_ctrl_t * const p_ctrl, timer_cfg_t const * const p_cfg);
fsp_err_t R_AGT_CallbackSet(timer_ctrl_t * const          p_api_ctrl,
                            void (                      * p_callback)(timer_callback_args_t *),
                            void * const                  p_context,
                            timer_callback_args_t * const p_callback_memory);
fsp_err_t R_AGT_CompareMatchSet(timer_ctrl_t * const        p_ctrl,
                                uint32_t const              compare_match_value,
                                timer_compare_match_t const match_channel);

/*******************************************************************************************************************//**
 * @} (end defgroup AGT)
 **********************************************************************************************************************/

/* Common macro for FSP header files. There is also a corresponding FSP_HEADER macro at the top of this file. */

FSP_FOOTER

#endif                                 // R_AGT_H
