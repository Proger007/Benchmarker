/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

/*******************************************************************************************************************//**
 * @ingroup RENESAS_MOTOR_INTERFACES
 * @defgroup MOTOR_DRIVER_API Motor driver Interface
 * @brief Interface for motor driver functions.
 *
 * @section MOTOR_DRIVER_API_Summary Summary
 * The Motor driver interface for setting the PWM modulation duty
 *
 *
 * @{
 **********************************************************************************************************************/

#ifndef RM_MOTOR_DRIVER_API_H
#define RM_MOTOR_DRIVER_API_H

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/

/* Register definitions, common services and error codes. */
#include "bsp_api.h"
#include "r_adc_api.h"
#include "r_three_phase_api.h"
#include "r_elc_api.h"

/* Common macro for FSP header files. There is also a corresponding FSP_FOOTER macro at the end of this file. */
FSP_HEADER

/**********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

/**********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/** Events that can trigger a callback function */
typedef enum e_motor_driver_event
{
    MOTOR_DRIVER_EVENT_FORWARD = 1,    ///< Event before Motor Driver Process (before Current Control timing)
    MOTOR_DRIVER_EVENT_CURRENT,        ///< Event Current Control timing
    MOTOR_DRIVER_EVENT_BACKWARD,       ///< Event after Motor Driver Process (after PWM duty setting)
} motor_driver_event_t;

/** Selection of shunt type */
typedef enum e_motor_driver_shunt_type
{
    MOTOR_DRIVER_SHUNT_TYPE_1_SHUNT = 1, ///< Only use U phase current
    MOTOR_DRIVER_SHUNT_TYPE_2_SHUNT,     ///< Use U and W phase current
    MOTOR_DRIVER_SHUNT_TYPE_3_SHUNT      ///< Use all phase current
} motor_driver_shunt_type_t;

/** Callback function parameter data */
typedef struct st_motor_driver_callback_args
{
    motor_driver_event_t event;        ///< Event trigger
    void               * p_context;    ///< Placeholder for user data.
} motor_driver_callback_args_t;

/** Current Data Get Structure */
typedef struct st_motor_driver_current_get
{
    float iu;                          ///< U phase current [A]
    float iv;                          ///< V phase current [A]
    float iw;                          ///< W phase current [A]
    float vdc;                         ///< Main Line Voltage [V]
    float va_max;                      ///< maximum magnitude of voltage vector

    float sin_ad;                      ///< Induction sensor sin signal
    float cos_ad;                      ///< Induction sensor cos signal
} motor_driver_current_get_t;

/** Control block.  Allocate an instance specific control block to pass into the API calls.
 */
typedef void motor_driver_ctrl_t;

/** Configuration parameters. */
typedef struct st_motor_driver_cfg
{
    /* ADC Module */
    adc_instance_t const * p_adc_instance;
    adc_channel_t          iu_ad_ch;   ///< A/D Channel for U Phase Current
    adc_channel_t          iv_ad_ch;   ///< A/D Channel for V Phase Current
    adc_channel_t          iw_ad_ch;   ///< A/D Channel for W Phase Current
    adc_channel_t          vdc_ad_ch;  ///< A/D Channel for Main Line Voltage

    adc_channel_t sin_ad_ch;           ///< A/D Channel for induction sensor sin signal
    adc_channel_t cos_ad_ch;           ///< A/D Channel for induction sensor cos signal

    adc_instance_t const * p_adc2_instance;

    /* Shunt Type */
    motor_driver_shunt_type_t shunt;   ///< Selection of shunt type

    /* PWM Output Module (GPT THREE PHASE) */
    three_phase_instance_t const * p_three_phase_instance;

    void (* p_callback)(motor_driver_callback_args_t * p_args);
    void * p_context;                  ///< Placeholder for user data.

    void const * p_extend;
} motor_driver_cfg_t;

/** Functions implemented at the HAL layer will follow these APIs. */
typedef struct st_motor_driver_api
{
    /** Initialize the Motor Driver Module.
     *
     * @param[in]  p_ctrl       Pointer to control structure.
     * @param[in]  p_cfg        Pointer to configuration structure.
     */
    fsp_err_t (* open)(motor_driver_ctrl_t * const p_ctrl, motor_driver_cfg_t const * const p_cfg);

    /** Close the Motor Driver Module
     *
     * @param[in]  p_ctrl       Pointer to control structure.
     */
    fsp_err_t (* close)(motor_driver_ctrl_t * const p_ctrl);

    /** Reset variables of the Motor Driver Module
     *
     * @param[in]  p_ctrl       Pointer to control structure.
     */
    fsp_err_t (* reset)(motor_driver_ctrl_t * const p_ctrl);

    /** Set (Input) Phase Voltage data into the Motor Driver Module
     *
     * @param[in]  p_ctrl       Pointer to control structure.
     * @param[in]  u_voltage    U phase voltage [V]
     * @param[in]  v_voltage    V phase voltage [V]
     * @param[in]  w_voltage    W phase voltage [V]
     */
    fsp_err_t (* phaseVoltageSet)(motor_driver_ctrl_t * const p_ctrl, float const u_voltage, float const v_voltage,
                                  float const w_voltage);

    /** Get Phase current, Vdc and Va_max data from the Motor Driver Module
     *
     * @param[in]  p_ctrl           Pointer to control structure.
     * @param[out] p_current_get    Pointer to get data structure.
     */
    fsp_err_t (* currentGet)(motor_driver_ctrl_t * const p_ctrl, motor_driver_current_get_t * const p_current_get);

    /** Get the flag of finish current offset detection from the Motor Driver Module
     *
     * @param[in]  p_ctrl       Pointer to control structure.
     * @param[out] p_flag_offset   Flag of finish current offset detection
     */
    fsp_err_t (* flagCurrentOffsetGet)(motor_driver_ctrl_t * const p_ctrl, uint8_t * const p_flag_offset);

    /** Restart current offset detection
     *
     * @param[in]  p_ctrl       Pointer to control structure.
     */
    fsp_err_t (* currentOffsetRestart)(motor_driver_ctrl_t * const p_ctrl);

    /** Update Configuration Parameters for the calculation in the Motor Driver Module
     *
     * @param[in]  p_ctrl       Pointer to control structure.
     * @param[in]  p_cfg        Pointer to configuration structure include update parameters.
     */
    fsp_err_t (* parameterUpdate)(motor_driver_ctrl_t * const p_ctrl, motor_driver_cfg_t const * const p_cfg);
} motor_driver_api_t;

/** This structure encompasses everything that is needed to use an instance of this interface. */
typedef struct st_motor_driver_instance
{
    motor_driver_ctrl_t      * p_ctrl; ///< Pointer to the control structure for this instance
    motor_driver_cfg_t const * p_cfg;  ///< Pointer to the configuration structure for this instance
    motor_driver_api_t const * p_api;  ///< Pointer to the API structure for this instance
} motor_driver_instance_t;

/*******************************************************************************************************************//**
 * @} (end addtogroup MOTOR_DRIVER_API)
 **********************************************************************************************************************/

/* Common macro for FSP header files. There is also a corresponding FSP_HEADER macro at the top of this file. */
FSP_FOOTER

#endif                                 /* RM_MOTOR_DRIVER_API_H */
