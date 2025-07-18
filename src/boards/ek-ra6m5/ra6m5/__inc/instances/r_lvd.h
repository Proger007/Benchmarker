/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

/*******************************************************************************************************************//**
 * @addtogroup LVD-PVD
 * @{
 **********************************************************************************************************************/

#ifndef R_LVD_H
#define R_LVD_H

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/
#include "bsp_api.h"
#include "r_lvd_cfg.h"
#include "r_lvd_api.h"

/* Common macro for FSP header files. There is also a corresponding FSP_FOOTER macro at the end of this file. */
FSP_HEADER

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/** LVD instance control structure */
typedef struct st_lvd_instance_ctrl
{
    uint32_t          open;
    lvd_cfg_t const * p_cfg;

    void (* p_callback)(lvd_callback_args_t *); // Pointer to callback that is called when lvd_current_state_t changes.
    lvd_callback_args_t * p_callback_memory;    // Pointer to non-secure memory that can be used to pass arguments to a callback in non-secure memory.

    /* Pointer to context to be passed into callback function */
    void * p_context;
} lvd_instance_ctrl_t;

/**********************************************************************************************************************
 * Exported global variables
 **********************************************************************************************************************/

/** @cond INC_HEADER_DEFS_SEC */
/** Filled in Interface API structure for this Instance. */
extern const lvd_api_t g_lvd_on_lvd;

/** @endcond */

/***********************************************************************************************************************
 * Public APIs
 **********************************************************************************************************************/
fsp_err_t R_LVD_Open(lvd_ctrl_t * const p_api_ctrl, lvd_cfg_t const * const p_cfg);
fsp_err_t R_LVD_Close(lvd_ctrl_t * const p_api_ctrl);
fsp_err_t R_LVD_StatusGet(lvd_ctrl_t * const p_api_ctrl, lvd_status_t * p_lvd_status);
fsp_err_t R_LVD_StatusClear(lvd_ctrl_t * const p_api_ctrl);
fsp_err_t R_LVD_CallbackSet(lvd_ctrl_t * const          p_api_ctrl,
                            void (                    * p_callback)(lvd_callback_args_t *),
                            void * const                p_context,
                            lvd_callback_args_t * const p_callback_memory);

/* Common macro for FSP header files. There is also a corresponding FSP_HEADER macro at the top of this file. */
FSP_FOOTER

#endif

/*******************************************************************************************************************//**
 * @} (end defgroup LVD-PVD)
 **********************************************************************************************************************/
