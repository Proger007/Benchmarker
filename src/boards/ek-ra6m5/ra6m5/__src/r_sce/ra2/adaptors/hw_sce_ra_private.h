/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

/**********************************************************************************************************************
 * File Name    : hw_sce_ra_private.h
 * Version      : 1.09
 * Description  : SCE function private header file.
 *********************************************************************************************************************/

/**********************************************************************************************************************
 * Includes   <System Includes> , "Project Includes"
 *********************************************************************************************************************/
#ifndef HW_SCE_RA_PRIVATE_HEADER_FILE
#define HW_SCE_RA_PRIVATE_HEADER_FILE

#include "hw_sce_aes_private.h"

/**********************************************************************************************************************
 * Macro definitions
 *********************************************************************************************************************/
#define SCE_AES_IN_DATA_CMD_ECB_ENCRYPTION               (0x00000000U)
#define SCE_AES_IN_DATA_CMD_ECB_DECRYPTION               (0x00000001U)
#define SCE_AES_IN_DATA_CMD_CBC_ENCRYPTION               (0x00000002U)
#define SCE_AES_IN_DATA_CMD_CBC_DECRYPTION               (0x00000003U)
#define SCE_AES_IN_DATA_CMD_CTR_ENCRYPTION_DECRYPTION    (0x00000004U)

/* Wrapped keys not supported on RA2; these definitions are added to let the code compile. */
#define SIZE_AES_128BIT_KEYLEN_BITS_WRAPPED              (1)
#define SIZE_AES_128BIT_KEYLEN_BYTES_WRAPPED             ((SIZE_AES_128BIT_KEYLEN_BITS_WRAPPED) / 8)
#define SIZE_AES_128BIT_KEYLEN_WORDS_WRAPPED             ((SIZE_AES_128BIT_KEYLEN_BITS_WRAPPED) / 32)

#define SIZE_AES_192BIT_KEYLEN_BITS_WRAPPED              (2) /* 192 not supported on SCE5 */
#define SIZE_AES_192BIT_KEYLEN_BYTES_WRAPPED             ((SIZE_AES_192BIT_KEYLEN_BITS_WRAPPED) / 8)
#define SIZE_AES_192BIT_KEYLEN_WORDS_WRAPPED             ((SIZE_AES_192BIT_KEYLEN_BITS_WRAPPED) / 32)

#define SIZE_AES_256BIT_KEYLEN_BITS_WRAPPED              (3)
#define SIZE_AES_256BIT_KEYLEN_BYTES_WRAPPED             ((SIZE_AES_256BIT_KEYLEN_BITS_WRAPPED) / 8)
#define SIZE_AES_256BIT_KEYLEN_WORDS_WRAPPED             ((SIZE_AES_256BIT_KEYLEN_BITS_WRAPPED) / 32)

/**********************************************************************************************************************
 * Global Typedef definitions
 *********************************************************************************************************************/

/**********************************************************************************************************************
 * External global variables
 *********************************************************************************************************************/

/**********************************************************************************************************************
 * Exported global functions
 *********************************************************************************************************************/

/***********************************************************************************************************************
 * Private global variables and functions
 ***********************************************************************************************************************/
uint32_t change_endian_long(uint32_t data);

fsp_err_t HW_SCE_Aes128EncryptDecryptInitSub(const uint32_t * InData_KeyType,
                                             const uint32_t * InData_Cmd,
                                             const uint32_t * InData_KeyIndex,
                                             const uint32_t * InData_IV);
void HW_SCE_Aes128EncryptDecryptUpdateSub(const uint32_t * InData_Text,
                                          uint32_t       * OutData_Text,
                                          const uint32_t   MAX_CNT);
fsp_err_t HW_SCE_Aes128EncryptDecryptFinalSub(void);

fsp_err_t HW_SCE_Aes128EncryptDecryptInitSubAdaptor(const uint32_t InData_KeyMode[],
                                                    const uint32_t InData_Cmd[],
                                                    const uint32_t InData_KeyIndex[],
                                                    const uint32_t InData_Key[],
                                                    const uint32_t InData_IV[]);

fsp_err_t HW_SCE_Aes192EncryptDecryptInitSubAdaptor(const uint32_t InData_KeyMode[],
                                                    const uint32_t InData_Cmd[],
                                                    const uint32_t InData_KeyIndex[],
                                                    const uint32_t InData_Key[],
                                                    const uint32_t InData_IV[]);

fsp_err_t HW_SCE_Aes256EncryptDecryptInitSubAdaptor(const uint32_t InData_KeyMode[],
                                                    const uint32_t InData_Cmd[],
                                                    const uint32_t InData_KeyIndex[],
                                                    const uint32_t InData_Key[],
                                                    const uint32_t InData_IV[]);

fsp_err_t HW_SCE_Aes192EncryptDecryptInitSub(const uint32_t * InData_Cmd,
                                             const uint32_t * InData_KeyIndex,
                                             const uint32_t * InData_IV);
void HW_SCE_Aes192EncryptDecryptUpdateSub(const uint32_t * InData_Text,
                                          uint32_t       * OutData_Text,
                                          const uint32_t   MAX_CNT);
fsp_err_t HW_SCE_Aes192EncryptDecryptFinalSub(void);
fsp_err_t HW_SCE_Aes256EncryptDecryptInitSub(const uint32_t * InData_KeyType,
                                             const uint32_t * InData_Cmd,
                                             const uint32_t * InData_KeyIndex,
                                             const uint32_t * InData_IV);
void HW_SCE_Aes256EncryptDecryptUpdateSub(const uint32_t * InData_Text,
                                          uint32_t       * OutData_Text,
                                          const uint32_t   MAX_CNT);
fsp_err_t HW_SCE_Aes256EncryptDecryptFinalSub(void);

#endif                                 /* HW_SCE_RA_PRIVATE_HEADER_FILE */
