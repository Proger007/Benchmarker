/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#ifndef RM_BLE_MESH_SCENE_SERVER_API_H
#define RM_BLE_MESH_SCENE_SERVER_API_H

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/

/* Register definitions, common services and error codes. */
#include "bsp_api.h"
#include "rm_ble_mesh_access_api.h"

/* Common macro for FSP header files. There is also a corresponding FSP_FOOTER macro at the end of this file. */
FSP_HEADER

/*******************************************************************************************************************//**
 * @ingroup  RENESAS_BLE_MESH_INTERFACES
 * @defgroup RM_BLE_MESH_SCENE_SERVER_API BLE Mesh Scene Server Interface
 * @brief    Interface for BLE Mesh Model Scene Server functions.
 *
 * @section RM_BLE_MESH_SCENE_SERVER_API_Summary Summary
 * The BLE Mesh interface for the BLE Mesh Model Scene Server (BLE MESH HEALTH SERVER) middleware provides BLE Mesh Model Scene Server functionality.
 *
 *
 * @{
 **********************************************************************************************************************/

/**********************************************************************************************************************
 * Macro definitions
 *********************************************************************************************************************/

/*********************************************************************************************************************
 * Typedef definitions
 *********************************************************************************************************************/

/** Scene Event Types */
typedef enum e_rm_ble_mesh_scene_srv_event
{
    /** Scene Event - Store */
    RM_BLE_MESH_SCENE_SRV_EVENT_STORE = 0x01,

    /** Scene Event - Delete */
    RM_BLE_MESH_SCENE_SRV_EVENT_DELETE = 0x02,

    /** Scene Event - Recall Start */
    RM_BLE_MESH_SCENE_SRV_EVENT_RECALL_START = 0x03,

    /** Scene Event - Recall Complete */
    RM_BLE_MESH_SCENE_SRV_EVENT_RECALL_COMPLETE = 0x04,

    /** Scene Event - Recall Immediate */
    RM_BLE_MESH_SCENE_SRV_EVENT_RECALL_IMMEDIATE = 0x05,
} rm_ble_mesh_scene_srv_event_t;

/** Mesh model scene server callback parameter definition */
typedef struct st_rm_ble_mesh_scene_server_callback_args
{
    void * p_context;                               ///< Placeholder for user data.
    rm_ble_mesh_access_model_handle_t * p_handle;   ///< Access Model handle.
    rm_ble_mesh_scene_srv_event_t       event_type; ///< Scene event types.
    uint8_t * p_event_data;                         ///< Pointer to event data.
    uint16_t  event_data_length;                    ///< Event data length.
} rm_ble_mesh_scene_server_callback_args_t;

/**
 * Mesh model scene server publication timeout callback.
 *
 * Access Layer calls the registered callback to indicate Publication Timeout
 * for the associated model.
 *
 * \param p_context       User data.
 * \param p_handle        Model Handle.
 * \param p_blob          Blob if any or NULL.
 */
typedef struct st_rm_ble_mesh_scene_server_timeout_callback_args
{
    void * p_context;                             ///< Placeholder for user data.
    rm_ble_mesh_access_model_handle_t * p_handle; ///< Access Model handle.
    void * p_blob;                                ///< Binary Large Object.
} rm_ble_mesh_scene_server_timeout_callback_args_t;

/** BLE MESH SCENE SERVER control block.  Allocate an instance specific control block to pass into the BLE mesh model scene server API calls.
 */
typedef void rm_ble_mesh_scene_server_ctrl_t;

/** BLE mesh model scene server configuration parameters. */
typedef struct st_rm_ble_mesh_scene_server_cfg
{
    /** the parameters for initialization. */
    rm_ble_mesh_access_instance_t const * p_access_instance;                                ///< Access Layer instance structure.
    rm_ble_mesh_access_model_handle_t     model_handle;                                     ///< Access Model handle.
    rm_ble_mesh_access_model_handle_t     setup_server_handle;                              ///< Access Model handle for setup server.

    /* Pointer to callback and optional working memory */
    void (* p_callback)(rm_ble_mesh_scene_server_callback_args_t * p_args);                 ///< Mesh model scene server callback.
    void (* p_timeout_callback)(rm_ble_mesh_scene_server_timeout_callback_args_t * p_args); ///< Mesh model scene server publication timeout callback.
    void       * p_context;                                                                 ///< Placeholder for user data.
    void const * p_extend;                                                                  ///< Placeholder for user extension.
} rm_ble_mesh_scene_server_cfg_t;

/** Shared Interface definition for BLE MESH */
typedef struct st_rm_ble_mesh_scene_server_api
{
    /** API to open scene server model.
     *
     * @param[in]  p_ctrl       Pointer to control structure.
     * @param[in]  p_cfg        Pointer to configuration structure.
     */
    fsp_err_t (* open)(rm_ble_mesh_scene_server_ctrl_t * const      p_ctrl,
                       rm_ble_mesh_scene_server_cfg_t const * const p_cfg);

    /** API to close scene server model.
     *
     * @param[in]  p_ctrl       Pointer to control structure.
     */
    fsp_err_t (* close)(rm_ble_mesh_scene_server_ctrl_t * const p_ctrl);

    /** API to send reply or to update state change.
     *
     * @param[in]  p_ctrl       Pointer to control structure.
     * @param[in]  p_state      Pointer to model specific current/target state parameters.
     */
    fsp_err_t (* stateUpdate)(rm_ble_mesh_access_ctrl_t * const               p_ctrl,
                              rm_ble_mesh_access_server_state_t const * const p_state);
} rm_ble_mesh_scene_server_api_t;

/** This structure encompasses everything that is needed to use an instance of this interface. */
typedef struct st_rm_ble_mesh_scene_server_instance
{
    rm_ble_mesh_scene_server_ctrl_t      * p_ctrl; ///< Pointer to the control structure for this instance
    rm_ble_mesh_scene_server_cfg_t const * p_cfg;  ///< Pointer to the configuration structure for this instance
    rm_ble_mesh_scene_server_api_t const * p_api;  ///< Pointer to the API structure for this instance
} rm_ble_mesh_scene_server_instance_t;

/* Common macro for FSP header files. There is also a corresponding FSP_HEADER macro at the top of this file. */
FSP_FOOTER

#endif                                 // RM_BLE_MESH_SCENE_SERVER_API_H

/*******************************************************************************************************************//**
 * @} (end defgroup RM_BLE_MESH_SCENE_SERVER_API)
 **********************************************************************************************************************/
