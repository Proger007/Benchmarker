/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

/**********************************************************************************************************************
 * Includes   <System Includes> , "Project Includes"
 *********************************************************************************************************************/
#if defined(__CCRX__) || defined(__ICCRX__) || defined(__RX__)
 #include "r_zmod4xxx_if.h"
#elif defined(__CCRL__) || defined(__ICCRL78__) || defined(__RL78__)
 #include "r_zmod4xxx_if.h"
#else
 #define RM_ZMOD4410_SULFUR_ODOR_CFG_LIB_ENABLE    (1)
#endif

#if RM_ZMOD4410_SULFUR_ODOR_CFG_LIB_ENABLE
 #include "rm_zmod4xxx.h"
 #include "../zmod4xxx_types.h"
 #include "sulfur_odor.h"
 #include "zmod4410_config_sulfur_odor.h"

/**********************************************************************************************************************
 * Macro definitions
 *********************************************************************************************************************/

/**********************************************************************************************************************
 * Local Typedef definitions
 *********************************************************************************************************************/

/**********************************************************************************************************************
 * Exported global functions
 *********************************************************************************************************************/

/**********************************************************************************************************************
 * Private (static) variables and functions
 *********************************************************************************************************************/

static fsp_err_t rm_zmod4410_sulfur_odor_open(rm_zmod4xxx_ctrl_t * const      p_api_ctrl,
                                              rm_zmod4xxx_cfg_t const * const p_cfg);
static fsp_err_t rm_zmod4410_sulfur_odor_measurement_start(rm_zmod4xxx_ctrl_t * const p_api_ctrl);
static fsp_err_t rm_zmod4410_sulfur_odor_measurement_stop(rm_zmod4xxx_ctrl_t * const p_api_ctrl);
static fsp_err_t rm_zmod4410_sulfur_odor_status_check(rm_zmod4xxx_ctrl_t * const p_api_ctrl);
static fsp_err_t rm_zmod4410_sulfur_odor_read(rm_zmod4xxx_ctrl_t * const     p_api_ctrl,
                                              rm_zmod4xxx_raw_data_t * const p_raw_data);
static fsp_err_t rm_zmod4410_sulfur_odor_temperature_and_humidity_set(rm_zmod4xxx_ctrl_t * const p_api_ctrl,
                                                                      float                      temperature,
                                                                      float                      humidity);
static fsp_err_t rm_zmod4410_sulfur_odor_iaq_1st_gen_data_calculate(rm_zmod4xxx_ctrl_t * const         p_api_ctrl,
                                                                    rm_zmod4xxx_raw_data_t * const     p_raw_data,
                                                                    rm_zmod4xxx_iaq_1st_data_t * const p_zmod4xxx_data);
static fsp_err_t rm_zmod4410_sulfur_odor_iaq_2nd_gen_data_calculate(rm_zmod4xxx_ctrl_t * const         p_api_ctrl,
                                                                    rm_zmod4xxx_raw_data_t * const     p_raw_data,
                                                                    rm_zmod4xxx_iaq_2nd_data_t * const p_zmod4xxx_data);
static fsp_err_t rm_zmod4410_sulfur_odor_data_calculate(rm_zmod4xxx_ctrl_t * const             p_api_ctrl,
                                                        rm_zmod4xxx_raw_data_t * const         p_raw_data,
                                                        rm_zmod4xxx_sulfur_odor_data_t * const p_zmod4xxx_data);
static fsp_err_t rm_zmod4410_sulfur_odor_oaq_2nd_gen_data_calculate(rm_zmod4xxx_ctrl_t * const         p_api_ctrl,
                                                                    rm_zmod4xxx_raw_data_t * const     p_raw_data,
                                                                    rm_zmod4xxx_oaq_2nd_data_t * const p_zmod4xxx_data);
static fsp_err_t rm_zmod4410_sulfur_odor_raq_data_calculate(rm_zmod4xxx_ctrl_t * const     p_api_ctrl,
                                                            rm_zmod4xxx_raw_data_t * const p_raw_data,
                                                            rm_zmod4xxx_raq_data_t * const p_zmod4xxx_data);
static fsp_err_t rm_zmod4410_sulfur_odor_rel_iaq_data_calculate(rm_zmod4xxx_ctrl_t * const         p_api_ctrl,
                                                                rm_zmod4xxx_raw_data_t * const     p_raw_data,
                                                                rm_zmod4xxx_rel_iaq_data_t * const p_zmod4xxx_data);
static fsp_err_t rm_zmod4410_sulfur_odor_pbaq_data_calculate(rm_zmod4xxx_ctrl_t * const      p_api_ctrl,
                                                             rm_zmod4xxx_raw_data_t * const  p_raw_data,
                                                             rm_zmod4xxx_pbaq_data_t * const p_zmod4xxx_data);
static fsp_err_t rm_zmod4410_sulfur_odor_no2_o3_data_calculate(rm_zmod4xxx_ctrl_t * const        p_api_ctrl,
                                                               rm_zmod4xxx_raw_data_t * const    p_raw_data,
                                                               rm_zmod4xxx_no2_o3_data_t * const p_zmod4xxx_data);
static fsp_err_t rm_zmod4410_sulfur_odor_close(rm_zmod4xxx_ctrl_t * const p_api_ctrl);
static fsp_err_t rm_zmod4410_sulfur_odor_device_error_check(rm_zmod4xxx_ctrl_t * const p_api_ctrl);

/**********************************************************************************************************************
 * Exported global variables
 *********************************************************************************************************************/
rm_zmod4xxx_api_t const g_zmod4xxx_on_zmod4410_sulfur_odor =
{
    .open                      = rm_zmod4410_sulfur_odor_open,
    .close                     = rm_zmod4410_sulfur_odor_close,
    .measurementStart          = rm_zmod4410_sulfur_odor_measurement_start,
    .measurementStop           = rm_zmod4410_sulfur_odor_measurement_stop,
    .statusCheck               = rm_zmod4410_sulfur_odor_status_check,
    .read                      = rm_zmod4410_sulfur_odor_read,
    .iaq1stGenDataCalculate    = rm_zmod4410_sulfur_odor_iaq_1st_gen_data_calculate,
    .iaq2ndGenDataCalculate    = rm_zmod4410_sulfur_odor_iaq_2nd_gen_data_calculate,
    .sulfurOdorDataCalculate   = rm_zmod4410_sulfur_odor_data_calculate,
    .oaq2ndGenDataCalculate    = rm_zmod4410_sulfur_odor_oaq_2nd_gen_data_calculate,
    .raqDataCalculate          = rm_zmod4410_sulfur_odor_raq_data_calculate,
    .relIaqDataCalculate       = rm_zmod4410_sulfur_odor_rel_iaq_data_calculate,
    .pbaqDataCalculate         = rm_zmod4410_sulfur_odor_pbaq_data_calculate,
    .no2O3DataCalculate        = rm_zmod4410_sulfur_odor_no2_o3_data_calculate,
    .temperatureAndHumiditySet = rm_zmod4410_sulfur_odor_temperature_and_humidity_set,
    .deviceErrorCheck          = rm_zmod4410_sulfur_odor_device_error_check,
};

/***********************************************************************************************************************
 * Functions
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * @brief Initialize the Sulfur Odor library
 *
 * @retval FSP_SUCCESS              Successfully started.
 * @retval FSP_ERR_ASSERTION        Null pointer passed as a parameter.
 **********************************************************************************************************************/
static fsp_err_t rm_zmod4410_sulfur_odor_open (rm_zmod4xxx_ctrl_t * const      p_api_ctrl,
                                               rm_zmod4xxx_cfg_t const * const p_cfg)
{
    rm_zmod4xxx_instance_ctrl_t * p_ctrl = (rm_zmod4xxx_instance_ctrl_t *) p_api_ctrl;
    int8_t lib_err = 0;
    rm_zmod4xxx_lib_extended_cfg_t * p_lib    = p_ctrl->p_zmod4xxx_lib;
    sulfur_odor_handle_t           * p_handle = (sulfur_odor_handle_t *) p_lib->p_handle;

    FSP_PARAMETER_NOT_USED(p_cfg);

/* Initialize the library */
    lib_err = init_sulfur_odor(p_handle);
    FSP_ERROR_RETURN(0 == lib_err, FSP_ERR_ASSERTION);

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * @brief  Calculate the Sulfur Odor data with the library API.
 *
 * @retval FSP_SUCCESS                            Successfully results are read.
 * @retval FSP_ERR_ASSERTION                      Null pointer passed as a parameter.
 * @retval FSP_ERR_SENSOR_IN_STABILIZATION        Module is stabilizing.
 **********************************************************************************************************************/
static fsp_err_t rm_zmod4410_sulfur_odor_data_calculate (rm_zmod4xxx_ctrl_t * const             p_api_ctrl,
                                                         rm_zmod4xxx_raw_data_t * const         p_raw_data,
                                                         rm_zmod4xxx_sulfur_odor_data_t * const p_zmod4xxx_data)
{
    rm_zmod4xxx_instance_ctrl_t    * p_ctrl    = (rm_zmod4xxx_instance_ctrl_t *) p_api_ctrl;
    rm_zmod4xxx_lib_extended_cfg_t * p_lib     = p_ctrl->p_zmod4xxx_lib;
    sulfur_odor_handle_t           * p_handle  = (sulfur_odor_handle_t *) p_lib->p_handle;
    sulfur_odor_results_t          * p_results = (sulfur_odor_results_t *) p_lib->p_results;
    zmod4xxx_dev_t                 * p_device  = (zmod4xxx_dev_t *) p_lib->p_device;
    uint16_t             i;
    int8_t               lib_err = 0;
    sulfur_odor_inputs_t algorithm_input;

    /* Calculate Sulfur odor data form ADC data */
    algorithm_input.adc_result = &p_raw_data->adc_data[0];
    lib_err = calc_sulfur_odor(p_handle, p_device, &algorithm_input, p_results);
    FSP_ERROR_RETURN(0 <= lib_err, FSP_ERR_ASSERTION);

    /* Set Data */
    for (i = 0; i < 9; i++)
    {
        p_zmod4xxx_data->rmox[i] = p_results->rmox[i];
    }

    p_zmod4xxx_data->intensity = p_results->intensity;
    if (SULFUR_ODOR_ACCEPTABLE == p_results->odor)
    {
        p_zmod4xxx_data->odor = RM_ZMOD4XXX_SULFUR_ODOR_ACCEPTABLE;
    }
    else
    {
        p_zmod4xxx_data->odor = RM_ZMOD4XXX_SULFUR_ODOR_UNACCEPTABLE;
    }

    FSP_ERROR_RETURN(SULFUR_ODOR_STABILIZATION != lib_err, FSP_ERR_SENSOR_IN_STABILIZATION);

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * @brief  Unsupported API.
 *
 * @retval FSP_ERR_UNSUPPORTED                    Operation mode is not supported.
 **********************************************************************************************************************/
static fsp_err_t rm_zmod4410_sulfur_odor_close (rm_zmod4xxx_ctrl_t * const p_api_ctrl)
{
    FSP_PARAMETER_NOT_USED(p_api_ctrl);

    return FSP_ERR_UNSUPPORTED;
}

/*******************************************************************************************************************//**
 * @brief  Unsupported API.
 *
 * @retval FSP_ERR_UNSUPPORTED                    Operation mode is not supported.
 **********************************************************************************************************************/
static fsp_err_t rm_zmod4410_sulfur_odor_measurement_start (rm_zmod4xxx_ctrl_t * const p_api_ctrl)
{
    FSP_PARAMETER_NOT_USED(p_api_ctrl);

    return FSP_ERR_UNSUPPORTED;
}

/*******************************************************************************************************************//**
 * @brief  Unsupported API.
 *
 * @retval FSP_ERR_UNSUPPORTED                    Operation mode is not supported.
 **********************************************************************************************************************/
static fsp_err_t rm_zmod4410_sulfur_odor_measurement_stop (rm_zmod4xxx_ctrl_t * const p_api_ctrl)
{
    FSP_PARAMETER_NOT_USED(p_api_ctrl);

    return FSP_ERR_UNSUPPORTED;
}

/*******************************************************************************************************************//**
 * @brief  Unsupported API.
 *
 * @retval FSP_ERR_UNSUPPORTED                    Operation mode is not supported.
 **********************************************************************************************************************/
static fsp_err_t rm_zmod4410_sulfur_odor_status_check (rm_zmod4xxx_ctrl_t * const p_api_ctrl)
{
    FSP_PARAMETER_NOT_USED(p_api_ctrl);

    return FSP_ERR_UNSUPPORTED;
}

/*******************************************************************************************************************//**
 * @brief  Unsupported API.
 *
 * @retval FSP_ERR_UNSUPPORTED                    Operation mode is not supported.
 **********************************************************************************************************************/
static fsp_err_t rm_zmod4410_sulfur_odor_read (rm_zmod4xxx_ctrl_t * const     p_api_ctrl,
                                               rm_zmod4xxx_raw_data_t * const p_raw_data)
{
    FSP_PARAMETER_NOT_USED(p_api_ctrl);
    FSP_PARAMETER_NOT_USED(p_raw_data);

    return FSP_ERR_UNSUPPORTED;
}

/*******************************************************************************************************************//**
 * @brief  Unsupported API.
 *
 * @retval FSP_ERR_UNSUPPORTED                    Operation mode is not supported.
 **********************************************************************************************************************/
static fsp_err_t rm_zmod4410_sulfur_odor_temperature_and_humidity_set (rm_zmod4xxx_ctrl_t * const p_api_ctrl,
                                                                       float                      temperature,
                                                                       float                      humidity)
{
    FSP_PARAMETER_NOT_USED(p_api_ctrl);
    FSP_PARAMETER_NOT_USED(temperature);
    FSP_PARAMETER_NOT_USED(humidity);

    return FSP_ERR_UNSUPPORTED;
}

/*******************************************************************************************************************//**
 * @brief  Unsupported API.
 *
 * @retval FSP_ERR_UNSUPPORTED                    Operation mode is not supported.
 **********************************************************************************************************************/
static fsp_err_t rm_zmod4410_sulfur_odor_iaq_1st_gen_data_calculate (rm_zmod4xxx_ctrl_t * const         p_api_ctrl,
                                                                     rm_zmod4xxx_raw_data_t * const     p_raw_data,
                                                                     rm_zmod4xxx_iaq_1st_data_t * const p_zmod4xxx_data)
{
    FSP_PARAMETER_NOT_USED(p_api_ctrl);
    FSP_PARAMETER_NOT_USED(p_raw_data);
    FSP_PARAMETER_NOT_USED(p_zmod4xxx_data);

    return FSP_ERR_UNSUPPORTED;
}

/*******************************************************************************************************************//**
 * @brief  Unsupported API.
 *
 * @retval FSP_ERR_UNSUPPORTED                    Operation mode is not supported.
 **********************************************************************************************************************/
static fsp_err_t rm_zmod4410_sulfur_odor_iaq_2nd_gen_data_calculate (rm_zmod4xxx_ctrl_t * const         p_api_ctrl,
                                                                     rm_zmod4xxx_raw_data_t * const     p_raw_data,
                                                                     rm_zmod4xxx_iaq_2nd_data_t * const p_zmod4xxx_data)
{
    FSP_PARAMETER_NOT_USED(p_api_ctrl);
    FSP_PARAMETER_NOT_USED(p_raw_data);
    FSP_PARAMETER_NOT_USED(p_zmod4xxx_data);

    return FSP_ERR_UNSUPPORTED;
}

/*******************************************************************************************************************//**
 * @brief  Unsupported API.
 *
 * @retval FSP_ERR_UNSUPPORTED                    Operation mode is not supported.
 **********************************************************************************************************************/
static fsp_err_t rm_zmod4410_sulfur_odor_oaq_2nd_gen_data_calculate (rm_zmod4xxx_ctrl_t * const         p_api_ctrl,
                                                                     rm_zmod4xxx_raw_data_t * const     p_raw_data,
                                                                     rm_zmod4xxx_oaq_2nd_data_t * const p_zmod4xxx_data)
{
    FSP_PARAMETER_NOT_USED(p_api_ctrl);
    FSP_PARAMETER_NOT_USED(p_raw_data);
    FSP_PARAMETER_NOT_USED(p_zmod4xxx_data);

    return FSP_ERR_UNSUPPORTED;
}

/*******************************************************************************************************************//**
 * @brief  Unsupported API.
 *
 * @retval FSP_ERR_UNSUPPORTED                    Operation mode is not supported.
 **********************************************************************************************************************/
static fsp_err_t rm_zmod4410_sulfur_odor_raq_data_calculate (rm_zmod4xxx_ctrl_t * const     p_api_ctrl,
                                                             rm_zmod4xxx_raw_data_t * const p_raw_data,
                                                             rm_zmod4xxx_raq_data_t * const p_zmod4xxx_data)
{
    FSP_PARAMETER_NOT_USED(p_api_ctrl);
    FSP_PARAMETER_NOT_USED(p_raw_data);
    FSP_PARAMETER_NOT_USED(p_zmod4xxx_data);

    return FSP_ERR_UNSUPPORTED;
}

/*******************************************************************************************************************//**
 * @brief  Unsupported API.
 *
 * @retval FSP_ERR_UNSUPPORTED                    Operation mode is not supported.
 **********************************************************************************************************************/
static fsp_err_t rm_zmod4410_sulfur_odor_rel_iaq_data_calculate (rm_zmod4xxx_ctrl_t * const         p_api_ctrl,
                                                                 rm_zmod4xxx_raw_data_t * const     p_raw_data,
                                                                 rm_zmod4xxx_rel_iaq_data_t * const p_zmod4xxx_data)
{
    FSP_PARAMETER_NOT_USED(p_api_ctrl);
    FSP_PARAMETER_NOT_USED(p_raw_data);
    FSP_PARAMETER_NOT_USED(p_zmod4xxx_data);

    return FSP_ERR_UNSUPPORTED;
}

/*******************************************************************************************************************//**
 * @brief  Unsupported API.
 *
 * @retval FSP_ERR_UNSUPPORTED                    Operation mode is not supported.
 **********************************************************************************************************************/
static fsp_err_t rm_zmod4410_sulfur_odor_pbaq_data_calculate (rm_zmod4xxx_ctrl_t * const      p_api_ctrl,
                                                              rm_zmod4xxx_raw_data_t * const  p_raw_data,
                                                              rm_zmod4xxx_pbaq_data_t * const p_zmod4xxx_data)
{
    FSP_PARAMETER_NOT_USED(p_api_ctrl);
    FSP_PARAMETER_NOT_USED(p_raw_data);
    FSP_PARAMETER_NOT_USED(p_zmod4xxx_data);

    return FSP_ERR_UNSUPPORTED;
}

/*******************************************************************************************************************//**
 * @brief  Unsupported API.
 *
 * @retval FSP_ERR_UNSUPPORTED                    Operation mode is not supported.
 **********************************************************************************************************************/
static fsp_err_t rm_zmod4410_sulfur_odor_no2_o3_data_calculate (rm_zmod4xxx_ctrl_t * const        p_api_ctrl,
                                                                rm_zmod4xxx_raw_data_t * const    p_raw_data,
                                                                rm_zmod4xxx_no2_o3_data_t * const p_zmod4xxx_data)
{
    FSP_PARAMETER_NOT_USED(p_api_ctrl);
    FSP_PARAMETER_NOT_USED(p_raw_data);
    FSP_PARAMETER_NOT_USED(p_zmod4xxx_data);

    return FSP_ERR_UNSUPPORTED;
}

/*******************************************************************************************************************//**
 * @brief  Unsupported API.
 *
 * @retval FSP_ERR_UNSUPPORTED                    Operation mode is not supported.
 **********************************************************************************************************************/
static fsp_err_t rm_zmod4410_sulfur_odor_device_error_check (rm_zmod4xxx_ctrl_t * const p_api_ctrl)
{
    FSP_PARAMETER_NOT_USED(p_api_ctrl);

    return FSP_ERR_UNSUPPORTED;
}

#endif
