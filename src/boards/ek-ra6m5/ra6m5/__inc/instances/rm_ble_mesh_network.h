/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

/*******************************************************************************************************************//**
 *
 * @addtogroup RM_BLE_MESH_NETWORK RM_BLE_MESH_NETWORK
 * @{
 **********************************************************************************************************************/

#ifndef RM_BLE_MESH_NETWORK_H
#define RM_BLE_MESH_NETWORK_H

#include "bsp_api.h"

#include "rm_ble_mesh_network_api.h"

/* Common macro for FSP header files. There is also a corresponding FSP_FOOTER macro at the end of this file. */
FSP_HEADER

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/** RM_BLE_MESH_NETWORK private control block. DO NOT MODIFY. Initialization occurs when RM_BLE_MESH_NETWORK_Open() is called. */
typedef struct st_rm_ble_mesh_network_instance_ctrl
{
    uint32_t open;                           // Indicates whether the open() API has been successfully called.
    rm_ble_mesh_network_cfg_t const * p_cfg; // Pointer to initial configurations.
    void * p_context;                        // Placeholder for user data.
} rm_ble_mesh_network_instance_ctrl_t;

/**********************************************************************************************************************
 * Exported global variables
 **********************************************************************************************************************/

/** @cond INC_HEADER_DEFS_SEC */
/** Filled in Interface API structure for this Instance. */
extern const rm_ble_mesh_network_api_t g_rm_ble_mesh_network_on_rm_ble_mesh_network;

/** @endcond */

/**********************************************************************************************************************
 * Public Function Prototypes
 **********************************************************************************************************************/
fsp_err_t RM_BLE_MESH_NETWORK_Open(rm_ble_mesh_network_ctrl_t * const      p_ctrl,
                                   rm_ble_mesh_network_cfg_t const * const p_cfg);
fsp_err_t RM_BLE_MESH_NETWORK_Close(rm_ble_mesh_network_ctrl_t * const p_ctrl);
fsp_err_t RM_BLE_MESH_NETWORK_BroadcastSecureBeacon(rm_ble_mesh_network_ctrl_t * const  p_ctrl,
                                                    rm_ble_mesh_network_subnet_handle_t subnet_handle);
fsp_err_t RM_BLE_MESH_NETWORK_SendPduOnInterface(rm_ble_mesh_network_ctrl_t * const             p_ctrl,
                                                 rm_ble_mesh_network_route_info_t const * const p_route_info,
                                                 rm_ble_mesh_network_header_t const * const     p_header,
                                                 rm_ble_mesh_buffer_t const * const             p_buffer);
fsp_err_t RM_BLE_MESH_NETWORK_GetAddressType(rm_ble_mesh_network_ctrl_t * const         p_ctrl,
                                             rm_ble_mesh_network_address_t              addr,
                                             rm_ble_mesh_network_address_type_t * const p_type);
fsp_err_t RM_BLE_MESH_NETWORK_FetchProxyState(rm_ble_mesh_network_ctrl_t * const             p_ctrl,
                                              rm_ble_mesh_network_gatt_proxy_state_t * const p_proxy_state);
fsp_err_t RM_BLE_MESH_NETWORK_SetProxyFilter(rm_ble_mesh_network_ctrl_t * const             p_ctrl,
                                             rm_ble_mesh_network_route_info_t const * const p_route_info,
                                             rm_ble_mesh_proxy_filter_type_t                type);
fsp_err_t RM_BLE_MESH_NETWORK_ConfigProxyFilter(rm_ble_mesh_network_ctrl_t * const               p_ctrl,
                                                rm_ble_mesh_network_route_info_t const * const   p_route_info,
                                                rm_ble_mesh_proxy_config_opcode_t                opcode,
                                                rm_ble_mesh_network_proxy_address_list_t * const p_addr_list);
fsp_err_t RM_BLE_MESH_NETWORK_StartProxyServerAdv(rm_ble_mesh_network_ctrl_t * const        p_ctrl,
                                                  rm_ble_mesh_network_subnet_handle_t       subnet_handle,
                                                  rm_ble_mesh_network_gatt_proxy_adv_mode_t proxy_adv_mode);
fsp_err_t RM_BLE_MESH_NETWORK_StopProxyServerAdv(rm_ble_mesh_network_ctrl_t * const p_ctrl);
fsp_err_t RM_BLE_MESH_NETWORK_AllocateSeqNumber(rm_ble_mesh_network_ctrl_t * const p_ctrl, uint32_t * const p_seq_num);
fsp_err_t RM_BLE_MESH_NETWORK_GetSeqNumberState(rm_ble_mesh_network_ctrl_t * const             p_ctrl,
                                                rm_ble_mesh_network_seq_number_state_t * const p_seq_num_state);
fsp_err_t RM_BLE_MESH_NETWORK_SetSeqNumberState(rm_ble_mesh_network_ctrl_t * const                   p_ctrl,
                                                rm_ble_mesh_network_seq_number_state_t const * const p_seq_num_state);
fsp_err_t RM_BLE_MESH_NETWORK_ResetNetCache(rm_ble_mesh_network_ctrl_t * const p_ctrl);

/* Common macro for FSP header files. There is also a corresponding FSP_HEADER macro at the top of this file. */
FSP_FOOTER

#endif                                 // RM_BLE_MESH_NETWORK_H

/*******************************************************************************************************************//**
 * @} (end addtogroup RM_BLE_MESH_NETWORK)
 **********************************************************************************************************************/
