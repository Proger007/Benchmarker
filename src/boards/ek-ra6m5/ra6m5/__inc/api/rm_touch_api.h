/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

/*******************************************************************************************************************//**
 * @ingroup RENESAS_CAPTOUCH_INTERFACES
 * @defgroup TOUCH_API Touch Middleware Interface
 * @brief Interface for Touch Middleware functions.
 *
 * @section TOUCH_API_Summary Summary
 * The TOUCH interface provides TOUCH functionality.
 *
 *
 * @{
 **********************************************************************************************************************/

#ifndef RM_TOUCH_API_H
#define RM_TOUCH_API_H

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/

/* Register definitions, common services and error codes. */
#include "bsp_api.h"
#include "r_ctsu_api.h"
#include "r_uart_api.h"

/* Common macro for FSP header files. There is also a corresponding FSP_FOOTER macro at the end of this file. */
FSP_HEADER

/**********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

#define TOUCH_COUNT_MAX    CTSU_COUNT_MAX ///< Value of Maximum count
#define TOUCH_OFF_VALUE    (0xFFFF)       ///< Value of Non-touch

/**********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/** Control block.  Allocate an instance specific control block to pass into the API calls.
 */
typedef void touch_ctrl_t;

/** Configuration of each button */
typedef struct st_touch_button_cfg
{
    uint8_t  elem_index;               ///< Element number used by this button.
    uint16_t threshold;                ///< Touch/non-touch judgment threshold
    uint16_t hysteresis;               ///< Threshold hysteresis for chattering prevention.
} touch_button_cfg_t;

/** Configuration of each slider */
typedef struct st_touch_slider_cfg
{
    uint8_t const * p_elem_index;      ///< Element number array used by this slider.
    uint8_t         num_elements;      ///< Number of elements used by this slider.
    uint16_t        threshold;         ///< Position calculation start threshold value.
} touch_slider_cfg_t;

/** Configuration of each wheel */
typedef struct st_touch_wheel_cfg_t
{
    uint8_t const * p_elem_index;      ///< Element number array used by this wheel.
    uint8_t         num_elements;      ///< Number of elements used by this wheel.
    uint16_t        threshold;         ///< Position calculation start threshold value.
} touch_wheel_cfg_t;

/** Configuration of each pads */
typedef struct st_touch_pad_cfg_t
{
    uint8_t const * p_elem_index_rx;   ///< RX of element number arrays used by this pad.
    uint8_t const * p_elem_index_tx;   ///< TX of element number arrays used by this pad.
    uint8_t         num_elements;      ///< Number of elements used by this pad.
    uint16_t        threshold;         ///< Coordinate calculation threshold value.
    uint16_t        rx_pixel;          ///< rx coordinate resolution
    uint16_t        tx_pixel;          ///< tx coordinate resolution
    uint8_t         max_touch;         ///< Maximum number of touch judgments used by the pad.
    uint8_t         num_drift;         ///< Number of pad drift.
} touch_pad_cfg_t;

/** Callback function parameter data */
typedef struct st_ctsu_callback_args touch_callback_args_t;

/** User configuration structure, used in open function */
typedef struct st_touch_cfg
{
    touch_button_cfg_t const * p_buttons;    ///< Pointer to array of button configuration.
    touch_slider_cfg_t const * p_sliders;    ///< Pointer to array of slider configuration.
    touch_wheel_cfg_t const  * p_wheels;     ///< Pointer to array of wheel configuration.
    touch_pad_cfg_t const    * p_pad;        ///< Pointer of pad configuration.
    uint8_t                 num_buttons;     ///< Number of buttons.
    uint8_t                 num_sliders;     ///< Number of sliders.
    uint8_t                 num_wheels;      ///< Number of wheels.
    uint8_t                 on_freq;         ///< The cumulative number of determinations of ON.
    uint8_t                 off_freq;        ///< The cumulative number of determinations of OFF.
    uint16_t                drift_freq;      ///< Base value drift frequency. [0 : no use]
    uint16_t                cancel_freq;     ///< Maximum continuous ON. [0 : no use]
    uint8_t                 number;          ///< Configuration number for QE monitor.
    ctsu_instance_t const * p_ctsu_instance; ///< Pointer to CTSU instance.
    uart_instance_t const * p_uart_instance; ///< Pointer to UART instance.
    void       * p_context;                  ///< User defined context passed into callback function.
    void const * p_extend;                   ///< Pointer to extended configuration by instance of interface.
} touch_cfg_t;

/** Configuration of each touch sensitivity information */
typedef struct st_touch_sensitivity_info
{
    uint16_t * p_touch_sensitivity_ratio; ///< Pointer to sensitivity ratio array.
    uint16_t   old_threshold_ratio;       ///< Old threshold ratio.
    uint16_t   new_threshold_ratio;       ///< New threshold ratio.
    uint8_t    new_hysteresis_ratio;      ///< New hysteresis ratio.
} touch_sensitivity_info_t;

/** Functions implemented at the HAL layer will follow this API. */
typedef struct st_touch_api
{
    /** Open driver.
     *
     * @param[in]  p_ctrl       Pointer to control structure.
     * @param[in]  p_cfg        Pointer to pin configuration structure.
     */
    fsp_err_t (* open)(touch_ctrl_t * const p_ctrl, touch_cfg_t const * const p_cfg);

    /** Scan start.
     *
     * @param[in]  p_ctrl       Pointer to control structure.
     */
    fsp_err_t (* scanStart)(touch_ctrl_t * const p_ctrl);

    /** Data get.
     *
     * @param[in]  p_ctrl       Pointer to control structure.
     * @param[out] p_button_status    Pointer to get data bitmap.
     * @param[out] p_slider_position  Pointer to get data array.
     * @param[out] p_wheel_position   Pointer to get data array.
     */
    fsp_err_t (* dataGet)(touch_ctrl_t * const p_ctrl, uint64_t * p_button_status, uint16_t * p_slider_position,
                          uint16_t * p_wheel_position);

    /** ScanStop.
     *
     * @param[in]  p_ctrl       Pointer to control structure.
     */
    fsp_err_t (* scanStop)(ctsu_ctrl_t * const p_ctrl);

    /** pad data get.
     *
     * @param[in]  p_ctrl               Pointer to control structure.
     * @param[out] p_pad_rx_coordinate  Pointer to get coordinate of receiver side.
     * @param[out] p_pad_tx_coordinate  Pointer to get coordinate of transmitter side.
     * @param[out] p_pad_num_touch      Pointer to get touch count.
     */
    fsp_err_t (* padDataGet)(touch_ctrl_t * const p_ctrl, uint16_t * p_pad_rx_coordinate,
                             uint16_t * p_pad_tx_coordinate, uint8_t * p_pad_num_touch);

    /** Specify callback function and optional context pointer and working memory pointer.
     *
     * @param[in]   p_ctrl                   Pointer to the CTSU control block.
     * @param[in]   p_callback               Callback function
     * @param[in]   p_context                Pointer to send to callback function
     * @param[in]   p_working_memory         Pointer to volatile memory where callback structure can be allocated.
     *                                       Callback arguments allocated here are only valid during the callback.
     */
    fsp_err_t (* callbackSet)(touch_ctrl_t * const p_ctrl, void (* p_callback)(touch_callback_args_t *),
                              void * const p_context, touch_callback_args_t * const p_callback_memory);

    /** Close driver.
     *
     * @param[in]  p_ctrl       Pointer to control structure.
     */
    fsp_err_t (* close)(touch_ctrl_t * const p_ctrl);

    /** Sensitivity ratio get.
     *
     * @param[in]      p_ctrl       Pointer to control structure.
     * @param[in,out]  p_touch_sensitivity_info    Pointer to touch sensitivity structure.
     */
    fsp_err_t (* sensitivityRatioGet)(touch_ctrl_t * const p_ctrl, touch_sensitivity_info_t * p_touch_sensitivity_info);

    /** Threshold adjust.
     *
     * @param[in]  p_ctrl       Pointer to control structure.
     * @param[in]  p_touch_sensitivity_info    Pointer to touch sensitivity structure.
     */
    fsp_err_t (* thresholdAdjust)(touch_ctrl_t * const p_ctrl, touch_sensitivity_info_t * p_touch_sensitivity_info);

    /** Drift control.
     *
     * @param[in]  p_ctrl       Pointer to control structure.
     * @param[in]  input_drift_freq    Drift frequency value.
     */
    fsp_err_t (* driftControl)(touch_ctrl_t * const p_ctrl, uint16_t input_drift_freq);
} touch_api_t;

/** This structure encompasses everything that is needed to use an instance of this interface. */
typedef struct st_touch_instance
{
    touch_ctrl_t      * p_ctrl;        ///< Pointer to the control structure for this instance
    touch_cfg_t const * p_cfg;         ///< Pointer to the configuration structure for this instance
    touch_api_t const * p_api;         ///< Pointer to the API structure for this instance
} touch_instance_t;

/* Common macro for FSP header files. There is also a corresponding FSP_HEADER macro at the top of this file. */
FSP_FOOTER

#endif                                 /* RM_TOUCH_API_H */

/*******************************************************************************************************************//**
 * @} (end addtogroup TOUCH_API)
 **********************************************************************************************************************/
