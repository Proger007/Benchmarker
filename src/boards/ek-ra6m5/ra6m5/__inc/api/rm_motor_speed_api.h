/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

/*******************************************************************************************************************//**
 * @ingroup RENESAS_MOTOR_INTERFACES
 * @defgroup MOTOR_SPEED_API Motor speed Interface
 * @brief Interface for motor speed functions.
 *
 * @section MOTOR_SPEED_API_Summary Summary
 * The Motor speed interface for getting the current references from electric current and rotational speed
 *
 *
 * @{
 **********************************************************************************************************************/

#ifndef RM_MOTOR_SPEED_API_H
#define RM_MOTOR_SPEED_API_H

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/

/* Register definitions, common services and error codes. */
#include "bsp_api.h"
#include "r_timer_api.h"
#include "rm_motor_position_api.h"

/* Common macro for FSP header files. There is also a corresponding FSP_FOOTER macro at the end of this file. */
FSP_HEADER

/**********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

/**********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/** Events that can trigger a callback function */
typedef enum e_motor_speed_event
{
    MOTOR_SPEED_EVENT_FORWARD = 1,     ///< Event forward speed control
    MOTOR_SPEED_EVENT_BACKWARD,        ///< Event backward speed control
    MOTOR_SPEED_EVENT_ENCODER_CYCLIC,  ///< Event encoder cyclic
    MOTOR_SPEED_EVENT_ENCODER_ADJUST,  ///< Event encoder adjust
} motor_speed_event_t;

/** Callback function parameter data */
typedef struct st_rm_motor_speed_callback_args
{
    void              * p_context;     ///< Placeholder for user data.
    motor_speed_event_t event;
} motor_speed_callback_args_t;

/* Structure of input parameters */
typedef struct st_motor_speed_input
{
    float f_id;                        ///< D-axis current [A]
    float f_iq;                        ///< Q-axis current [A]
    float f_vamax;
    float f_speed_rad;                 ///< Speed value [rad/s]
    float f_position_rad;              ///< Rotor position [radian]

    float f_ed;                        ///< Estimated d-axis component[V] of flux due to the permanent magnet
    float f_eq;                        ///< Estimated q-axis component[V] of flux due to the permanent magnet
    float f_phase_err_rad;             ///< Phase error [rad]

    uint8_t u1_flag_get_iref;          ///< Flag to set d/q-axis current reference

    /* Interface with Encoder */
    uint8_t u1_adjust_status;          ///< Angle adjustment satatus
    uint8_t u1_adjust_mode;            ///< Angle adjustment mode
    uint8_t u1_adjust_count_full;      ///< Angle adjustment count full

    /* Interface with induction sensor */
    uint8_t u1_openloop_status;        ///< Openloop status
    float   f_openloop_speed;          ///< Openloop speed
    float   f_openloop_id_ref;         ///< Openloop d-axis current
} motor_speed_input_t;

/* Structure of output parameters */
typedef struct st_motor_speed_output
{
    float f_id_ref;                    ///< D-axis current reference [A] for calculation
    float f_iq_ref;                    ///< Q-axis current reference [A] for calculation

    float f_ref_speed_rad_ctrl;        ///< Command speed value for speed PI control[rad/s]
    float f_damp_comp_speed;           ///< The speed for open-loop damping

    uint8_t u1_flag_pi;                ///< PI output started flag
} motor_speed_output_t;

/* Interface to Position Control */
typedef enum  e_motor_speed_loop_mode
{
    MOTOR_SPEED_LOOP_MODE_SPEED    = 0, ///< Speed control mode
    MOTOR_SPEED_LOOP_MODE_POSITION = 1  ///< Position control mode
} motor_speed_loop_mode_t;

typedef enum  e_motor_speed_step
{
    MOTOR_SPEED_STEP_DISABLE = 0,      ///< Position control works without step mode
    MOTOR_SPEED_STEP_ENABLE            ///< Position control works with step mode
} motor_speed_step_t;

/** Motor speed and position structure */
typedef struct st_motor_speed_position_data
{
    motor_speed_step_t      e_step_mode;               ///< Select step mode
    motor_speed_loop_mode_t e_loop_mode;               ///< Select control mode
    int16_t                 position_reference_degree; ///< Position reference [degree]
} motor_speed_position_data_t;

/** Control block.  Allocate an instance specific control block to pass into the API calls.
 */
typedef void motor_speed_ctrl_t;

/** Configuration parameters. */
typedef struct st_motor_speed_cfg
{
    motor_speed_input_t  * st_input;                       ///< Input data structure for automatic set
    motor_speed_output_t * st_output;                      ///< Output data structure for automatic receive

    timer_instance_t const * p_timer_instance;

    motor_position_instance_t const * p_position_instance; ///< Position module instance

    /* Callback function to perform at cyclic timer interrupt */
    void (* p_callback)(motor_speed_callback_args_t * p_args);
    void * p_context;                                      ///< Placeholder for user data.

    void const * p_extend;
} motor_speed_cfg_t;

/** Functions implemented at the HAL layer will follow these APIs. */
typedef struct st_motor_speed_api
{
    /** Initialize the motor speed module.
     *
     * @param[in]  p_ctrl       Pointer to control structure.
     * @param[in]  p_cfg        Pointer to configuration structure.
     */
    fsp_err_t (* open)(motor_speed_ctrl_t * const p_ctrl, motor_speed_cfg_t const * const p_cfg);

    /** Close (Finish) the motor speed module.
     *
     * @param[in]  p_ctrl       Pointer to control structure.
     */
    fsp_err_t (* close)(motor_speed_ctrl_t * const p_ctrl);

    /** Reset(Stop) the motor speed module.
     *
     * @param[in]  p_ctrl       Pointer to control structure.
     */
    fsp_err_t (* reset)(motor_speed_ctrl_t * const p_ctrl);

    /** Activate the motor speed control.
     *
     * @param[in]  p_ctrl       Pointer to control structure.
     */
    fsp_err_t (* run)(motor_speed_ctrl_t * const p_ctrl);

    /** Set (Input) speed reference into the motor speed module.
     *
     * @param[in]  p_ctrl              Pointer to control structure.
     * @param[in]  speed_reference_rpm  Speed reference [rpm]
     */
    fsp_err_t (* speedReferenceSet)(motor_speed_ctrl_t * const p_ctrl, float const speed_reference_rpm);

    /** Set (Input) position reference and control mode
     *
     * @param[in]  p_ctrl           Pointer to control structure.
     * @param[in]  p_position_data    Pointer to structure position data
     */
    fsp_err_t (* positionReferenceSet)(motor_speed_ctrl_t * const                p_ctrl,
                                       motor_speed_position_data_t const * const p_position_data);

    /** Set (Input) speed parameters into the motor speed module.
     *
     * @param[in]  p_ctrl         Pointer to control structure.
     * @param[in]  p_st_input     Pointer to structure to input parameters.
     */
    fsp_err_t (* parameterSet)(motor_speed_ctrl_t * const p_ctrl, motor_speed_input_t const * const p_st_input);

    /** Calculate current reference
     *
     * @param[in]  p_ctrl       Pointer to control structure.
     */
    fsp_err_t (* speedControl)(motor_speed_ctrl_t * const p_ctrl);

    /** Get speed control output parameters
     *
     * @param[in]  p_ctrl         Pointer to control structure.
     * @param[out] p_st_output    Pointer to get speed control parameters
     */
    fsp_err_t (* parameterGet)(motor_speed_ctrl_t * const p_ctrl, motor_speed_output_t * const p_st_output);

    /** Update Parameters for the calculation in the motor speed module.
     *
     * @param[in]  p_ctrl       Pointer to control structure.
     * @param[in]  p_cfg        Pointer to configuration structure include update parameters.
     */
    fsp_err_t (* parameterUpdate)(motor_speed_ctrl_t * const p_ctrl, motor_speed_cfg_t const * const p_cfg);
} motor_speed_api_t;

/** This structure encompasses everything that is needed to use an instance of this interface. */
typedef struct st_motor_speed_instance
{
    motor_speed_ctrl_t      * p_ctrl;  ///< Pointer to the control structure for this instance
    motor_speed_cfg_t const * p_cfg;   ///< Pointer to the configuration structure for this instance
    motor_speed_api_t const * p_api;   ///< Pointer to the API structure for this instance
} motor_speed_instance_t;

/*******************************************************************************************************************//**
 * @} (end addtogroup MOTOR_SPEED_API)
 **********************************************************************************************************************/

/* Common macro for FSP header files. There is also a corresponding FSP_HEADER macro at the top of this file. */
FSP_FOOTER

#endif                                 /* RM_MOTOR_SPEED_API_H */
