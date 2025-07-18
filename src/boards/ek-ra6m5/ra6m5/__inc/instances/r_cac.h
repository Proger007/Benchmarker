/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#ifndef R_CAC_H
#define R_CAC_H

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/

#include "r_cac_cfg.h"
#include "r_cac_api.h"

/* Common macro for FSP header files. There is also a corresponding FSP_FOOTER macro at the end of this file. */
FSP_HEADER

/*******************************************************************************************************************//**
 * @addtogroup CAC
 * @{
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/** CAC instance control block.  DO NOT INITIALIZE. */
typedef struct st_cac_instance_ctrl
{
    uint32_t          open;            // Set to "CAC" once API has been successfully opened.
    cac_cfg_t const * p_cfg;

    /* Pointer to callback and optional working memory */
    void (* p_callback)(cac_callback_args_t *);
    cac_callback_args_t * p_callback_memory;

    /* Pointer to context to be passed into callback function */
    void * p_context;
} cac_instance_ctrl_t;

/**********************************************************************************************************************
 * Exported global variables
 **********************************************************************************************************************/

/** @cond INC_HEADER_DEFS_SEC */
/** Filled in Interface API structure for this Instance. */
extern const cac_api_t g_cac_on_cac;

/** @endcond */

/***********************************************************************************************************************
 * Public APIs
 **********************************************************************************************************************/
fsp_err_t R_CAC_Open(cac_ctrl_t * const p_ctrl, cac_cfg_t const * const p_cfg);
fsp_err_t R_CAC_StartMeasurement(cac_ctrl_t * const p_ctrl);
fsp_err_t R_CAC_StopMeasurement(cac_ctrl_t * const p_ctrl);
fsp_err_t R_CAC_Read(cac_ctrl_t * const p_ctrl, uint32_t * const p_counter);
fsp_err_t R_CAC_Close(cac_ctrl_t * const p_ctrl);
fsp_err_t R_CAC_CallbackSet(cac_ctrl_t * const          p_ctrl,
                            void (                    * p_callback)(cac_callback_args_t *),
                            void * const                p_context,
                            cac_callback_args_t * const p_callback_memory);

/*******************************************************************************************************************//**
 * @} (end addtogroup CAC)
 **********************************************************************************************************************/

/* Common macro for FSP header files. There is also a corresponding FSP_HEADER macro at the top of this file. */
FSP_FOOTER

#endif
