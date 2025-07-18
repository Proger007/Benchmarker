/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

/*******************************************************************************************************************//**
 *
 * @addtogroup RM_BLE_MESH_PROVISION RM_BLE_MESH_PROVISION
 * @{
 **********************************************************************************************************************/

#ifndef RM_BLE_MESH_PROVISION_H
#define RM_BLE_MESH_PROVISION_H

#include "bsp_api.h"

#include "rm_ble_mesh_provision_api.h"

/* Common macro for FSP header files. There is also a corresponding FSP_FOOTER macro at the end of this file. */
FSP_HEADER

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/** RM_BLE_MESH_PROVISION private control block. DO NOT MODIFY. Initialization occurs when RM_BLE_MESH_PROVISION_Open() is called. */
typedef struct st_rm_ble_mesh_provision_instance_ctrl
{
    uint32_t open;                             // Indicates whether the open() API has been successfully called.
    rm_ble_mesh_provision_cfg_t const * p_cfg; // Pointer to initial configurations.
    void * p_context;                          // Placeholder for user data.
} rm_ble_mesh_provision_instance_ctrl_t;

/**********************************************************************************************************************
 * Exported global variables
 **********************************************************************************************************************/

/** @cond INC_HEADER_DEFS_SEC */
/** Filled in Interface API structure for this Instance. */
extern const rm_ble_mesh_provision_api_t g_rm_ble_mesh_provision_on_rm_ble_mesh_provision;

/** @endcond */

/**********************************************************************************************************************
 * Public Function Prototypes
 **********************************************************************************************************************/
fsp_err_t RM_BLE_MESH_PROVISION_Open(rm_ble_mesh_provision_ctrl_t * const      p_ctrl,
                                     rm_ble_mesh_provision_cfg_t const * const p_cfg);
fsp_err_t RM_BLE_MESH_PROVISION_Close(rm_ble_mesh_provision_ctrl_t * const p_ctrl);
fsp_err_t RM_BLE_MESH_PROVISION_Setup(rm_ble_mesh_provision_ctrl_t * const p_ctrl,
                                      rm_ble_mesh_provision_role_t         role,
                                      rm_ble_mesh_provision_device_info_t  info,
                                      uint16_t                             timeout);
fsp_err_t RM_BLE_MESH_PROVISION_Bind(rm_ble_mesh_provision_ctrl_t * const   p_ctrl,
                                     rm_ble_mesh_provision_device_info_t    info,
                                     uint8_t                                attention,
                                     rm_ble_mesh_provision_handle_t * const p_handle);
fsp_err_t RM_BLE_MESH_PROVISION_SendPdu(rm_ble_mesh_provision_ctrl_t * const         p_ctrl,
                                        rm_ble_mesh_provision_handle_t const * const p_handle,
                                        rm_ble_mesh_provision_pdu_type_t             type,
                                        rm_ble_mesh_buffer_t                         pdu_data);
fsp_err_t RM_BLE_MESH_PROVISION_SetAuthVal(rm_ble_mesh_provision_ctrl_t * const         p_ctrl,
                                           rm_ble_mesh_provision_handle_t const * const p_handle,
                                           rm_ble_mesh_buffer_t                         auth_value);
fsp_err_t RM_BLE_MESH_PROVISION_Abort(rm_ble_mesh_provision_ctrl_t * const         p_ctrl,
                                      rm_ble_mesh_provision_handle_t const * const p_handle,
                                      rm_ble_mesh_provision_link_close_reason_t    reason);
fsp_err_t RM_BLE_MESH_PROVISION_GetLocalPublicKey(rm_ble_mesh_provision_ctrl_t * const p_ctrl,
                                                  uint8_t * const                      public_key);
fsp_err_t RM_BLE_MESH_PROVISION_SetLocalPublicKey(rm_ble_mesh_provision_ctrl_t * const p_ctrl,
                                                  uint8_t const * const                public_key);
fsp_err_t RM_BLE_MESH_PROVISION_GenerateRandomizedNumber(rm_ble_mesh_provision_ctrl_t * const p_ctrl,
                                                         uint8_t * const                      p_key);
fsp_err_t RM_BLE_MESH_PROVISION_SetOobPublicKey(rm_ble_mesh_provision_ctrl_t * const p_ctrl,
                                                uint8_t const * const                p_key,
                                                uint8_t                              size);
fsp_err_t RM_BLE_MESH_PROVISION_SetOobAuthInfo(rm_ble_mesh_provision_ctrl_t * const p_ctrl,
                                               uint8_t const * const                p_auth_info,
                                               uint8_t                              size);
fsp_err_t RM_BLE_MESH_PROVISION_GenerateEcdhKey(rm_ble_mesh_provision_ctrl_t * const p_ctrl,
                                                uint8_t * const                      p_public_key);

/* Common macro for FSP header files. There is also a corresponding FSP_HEADER macro at the top of this file. */
FSP_FOOTER

#endif                                 // RM_BLE_MESH_PROVISION_H

/*******************************************************************************************************************//**
 * @} (end addtogroup RM_BLE_MESH_PROVISION)
 **********************************************************************************************************************/
