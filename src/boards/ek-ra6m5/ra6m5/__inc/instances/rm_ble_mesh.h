/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

/*******************************************************************************************************************//**
 *
 * @addtogroup RM_BLE_MESH RM_BLE_MESH
 * @{
 **********************************************************************************************************************/

#ifndef RM_BLE_MESH_H
#define RM_BLE_MESH_H

#include "bsp_api.h"

#include "rm_ble_mesh_cfg.h"
#include "rm_ble_mesh_api.h"

#include "r_ble_api.h"
#include "r_timer_api.h"
#include "r_flash_api.h"
#include <stdarg.h>

/* Common macro for FSP header files. There is also a corresponding FSP_FOOTER macro at the end of this file. */
FSP_HEADER

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/
typedef enum e_rm_ble_mesh_logging_target_mask
{
    RM_BLE_MESH_LOGGING_TARGET_MASK_NETWORK     = (1 << 0),
    RM_BLE_MESH_LOGGING_TARGET_MASK_LOWER_TRANS = (1 << 1),
    RM_BLE_MESH_LOGGING_TARGET_MASK_UPPER_TRANS = (1 << 2),
    RM_BLE_MESH_LOGGING_TARGET_MASK_ACCESS      = (1 << 3),
} rm_ble_mesh_logging_target_mask_t;

typedef struct st_rm_ble_mesh_logging_args
{
    const char * restrict p_format;
    va_list               list;
} rm_ble_mesh_logging_args_t;

/** RM_BLE_MESH_BEARER private control block. DO NOT MODIFY. Initialization occurs when RM_BLE_MESH_BEARER_Open() is called. */
typedef struct st_rm_ble_mesh_instance_ctrl
{
    uint32_t            open;          // Indicates whether the open() API has been successfully called.
    rm_ble_mesh_cfg_t * p_cfg;         // Pointer to initial configurations.
    void              * p_context;     // Placeholder for user data.
} rm_ble_mesh_instance_ctrl_t;

typedef struct st_rm_ble_mesh_platform_system_time_cfg
{
    timer_instance_t const * p_timer_instance;
} rm_ble_mesh_platform_system_time_cfg_t;

typedef struct st_rm_ble_mesh_platform_storage_cfg
{
    uint32_t                 block_num;
    flash_instance_t const * p_flash_instance;
} rm_ble_mesh_platform_storage_cfg_t;

typedef struct st_rm_ble_mesh_platform_memory_pool_cfg
{
    uint8_t * p_base_address;
    uint32_t  memory_size;
} rm_ble_mesh_platform_memory_pool_cfg_t;

typedef struct st_rm_ble_mesh_platform_logging_cfg
{
    uint8_t packet_bitfield;
    uint8_t module_info_bitfield;
    uint8_t generic_log_bitfield;
    void (* p_logging_func)(rm_ble_mesh_logging_args_t * p_args);
} rm_ble_mesh_platform_logging_cfg_t;

typedef struct st_rm_ble_mesh_platform_cfg
{
    rm_ble_mesh_platform_system_time_cfg_t const * p_system_time_cfg;
    rm_ble_mesh_platform_storage_cfg_t const     * p_storage_cfg;
    rm_ble_mesh_platform_memory_pool_cfg_t const * p_memory_pool_cfg;
    rm_ble_mesh_platform_logging_cfg_t const     * p_logging_cfg;
} rm_ble_mesh_platform_cfg_t;

typedef struct st_rm_ble_mesh_extended_cfg
{
    rm_ble_mesh_platform_cfg_t * p_platform_cfg; // Placeholder for user data.
} rm_ble_mesh_extended_cfg_t;

/**********************************************************************************************************************
 * Exported global variables
 **********************************************************************************************************************/

/** @cond INC_HEADER_DEFS_SEC */
/** Filled in Interface API structure for this Instance. */
extern const rm_ble_mesh_api_t g_rm_ble_mesh_on_rm_ble_mesh;

/** @endcond */

/**********************************************************************************************************************
 * Public Function Prototypes
 **********************************************************************************************************************/
fsp_err_t RM_BLE_MESH_Open(rm_ble_mesh_ctrl_t * const p_ctrl, rm_ble_mesh_cfg_t const * const p_cfg);;
fsp_err_t RM_BLE_MESH_Close(rm_ble_mesh_ctrl_t * const p_ctrl);
fsp_err_t RM_BLE_MESH_StartTransitionTimer(rm_ble_mesh_ctrl_t * const                          p_ctrl,
                                           rm_ble_mesh_access_state_transition_t const * const p_transition,
                                           uint16_t * const                                    p_transition_time_handle);
fsp_err_t RM_BLE_MESH_StopTransitionTimer(rm_ble_mesh_ctrl_t * const p_ctrl, uint16_t transition_time_handle);
fsp_err_t RM_BLE_MESH_GetRemainingTransitionTime(rm_ble_mesh_ctrl_t * const p_ctrl,
                                                 uint16_t                   transition_time_handle,
                                                 uint8_t * const            p_remaining_transition_time);
fsp_err_t RM_BLE_MESH_GetRemainingTransitionTimeWithOffset(rm_ble_mesh_ctrl_t * const p_ctrl,
                                                           uint16_t                   transition_time_handle,
                                                           uint32_t                   offset_in_ms,
                                                           uint8_t * const            p_remaining_transition_time);
fsp_err_t RM_BLE_MESH_ConvertTransitionTimeFromMs(rm_ble_mesh_ctrl_t * const p_ctrl,
                                                  uint32_t                   transition_time_in_ms,
                                                  uint8_t * const            p_transition_time);
fsp_err_t RM_BLE_MESH_ConvertTransitionTimeToMs(rm_ble_mesh_ctrl_t * const p_ctrl,
                                                uint8_t                    transition_time,
                                                uint32_t * const           p_transition_time_in_ms);

/* Common macro for FSP header files. There is also a corresponding FSP_HEADER macro at the top of this file. */
FSP_FOOTER

#endif                                 // RM_BLE_MESH_H

/*******************************************************************************************************************//**
 * @} (end addtogroup RM_BLE_MESH)
 **********************************************************************************************************************/
