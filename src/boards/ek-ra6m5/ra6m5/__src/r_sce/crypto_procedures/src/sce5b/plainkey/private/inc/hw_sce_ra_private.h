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
 Includes   <System Includes> , "Project Includes"
 *********************************************************************************************************************/
#include "r_sce_if.h"
#include "SCE_ProcCommon.h"

#ifndef HW_SCE_RA_PRIVATE_HEADER_FILE
#define HW_SCE_RA_PRIVATE_HEADER_FILE

/**********************************************************************************************************************
 Macro definitions
 *********************************************************************************************************************/
#if SCE_SECURE_BOOT != 0
/* Required for each variable definition with no initial value to be placed in the SECURE_BOOT section. */
#define SCE_PRV_SEC_B_SECURE_BOOT  R_BSP_ATTRIB_SECTION_CHANGE(B, SECURE_BOOT, 4)
/* Required for each function definition to be placed in the SECURE_BOOT section. */
#define SCE_PRV_SEC_P_SECURE_BOOT  R_BSP_ATTRIB_SECTION_CHANGE(P, SECURE_BOOT)
/* Revert to default section. */
#define SCE_PRV_SEC_DEFAULT        R_BSP_ATTRIB_SECTION_CHANGE_END
#else
/* Required for each variable definition with no initial value to be placed in the SECURE_BOOT section.(dummy) */
#define SCE_PRV_SEC_B_SECURE_BOOT
/* Required for each function definition to be placed in the SECURE_BOOT section.(dummy) */
#define SCE_PRV_SEC_P_SECURE_BOOT
/* Revert to default section.(dummy) */
#define SCE_PRV_SEC_DEFAULT
#endif  /* SCE_SECURE_BOOT != 0 */

#define SIZE_AES_128BIT_KEYLEN_BITS_WRAPPED              (288)
#define SIZE_AES_128BIT_KEYLEN_BYTES_WRAPPED             ((SIZE_AES_128BIT_KEYLEN_BITS_WRAPPED) / 8)
#define SIZE_AES_128BIT_KEYLEN_WORDS_WRAPPED             ((SIZE_AES_128BIT_KEYLEN_BITS_WRAPPED) / 32)

#define SIZE_AES_192BIT_KEYLEN_BITS_WRAPPED              (448) /* Added 32 bits here to differentiate 192 wrapped key from 256 wrapped key in the psa_crypto stack. */
#define SIZE_AES_192BIT_KEYLEN_BYTES_WRAPPED             ((SIZE_AES_192BIT_KEYLEN_BITS_WRAPPED) / 8)
#define SIZE_AES_192BIT_KEYLEN_WORDS_WRAPPED             ((SIZE_AES_192BIT_KEYLEN_BITS_WRAPPED) / 32)

#define SIZE_AES_256BIT_KEYLEN_BITS_WRAPPED              (416)
#define SIZE_AES_256BIT_KEYLEN_BYTES_WRAPPED             ((SIZE_AES_256BIT_KEYLEN_BITS_WRAPPED) / 8)
#define SIZE_AES_256BIT_KEYLEN_WORDS_WRAPPED             ((SIZE_AES_256BIT_KEYLEN_BITS_WRAPPED) / 32)

 #define SIZE_AES_XTS_128BIT_KEYLEN_BITS_WRAPPED     (416)
 #define SIZE_AES_XTS_128BIT_KEYLEN_BYTES_WRAPPED    ((SIZE_AES_XTS_128BIT_KEYLEN_BITS_WRAPPED) / 8)
 #define SIZE_AES_XTS_128BIT_KEYLEN_WORDS_WRAPPED    ((SIZE_AES_XTS_128BIT_KEYLEN_BITS_WRAPPED) / 32)

 #define SIZE_AES_XTS_256BIT_KEYLEN_BITS_WRAPPED     (672)
 #define SIZE_AES_XTS_256BIT_KEYLEN_BYTES_WRAPPED    ((SIZE_AES_XTS_256BIT_KEYLEN_BITS_WRAPPED) / 8)
 #define SIZE_AES_XTS_256BIT_KEYLEN_WORDS_WRAPPED    ((SIZE_AES_XTS_256BIT_KEYLEN_BITS_WRAPPED) / 32)

/**********************************************************************************************************************
 Global Typedef definitions
 *********************************************************************************************************************/

/**********************************************************************************************************************
 External global variables
 *********************************************************************************************************************/

extern uint32_t const S_FLASH2[];

extern uint32_t S_RAM[HW_SCE_SRAM_WORD_SIZE];
extern uint32_t S_HEAP[HW_SCE_SHEAP_WORD_SIZE];
extern uint32_t S_INST[HW_SCE_SINST_WORD_SIZE];
extern uint32_t S_INST2[HW_SCE_SINST2_WORD_SIZE];

extern SCE_GEN_MAC_CB_FUNC_T SCE_GEN_MAC_CB_FUNC;

extern uint32_t INST_DATA_SIZE;
extern const uint32_t sce_oem_key_size[SCE_OEM_CMD_NUM];

/**********************************************************************************************************************
 Exported global functions
 *********************************************************************************************************************/
/* --------------------- SCE driver wrapper layer ---------------------- */

fsp_err_t HW_SCE_Aes128EcbEncryptInitPrivate(sce_aes_key_index_t *key_index);
fsp_err_t HW_SCE_Aes128EcbEncryptUpdatePrivate(uint32_t *InData_Text, uint32_t *OutData_Text, uint32_t MAX_CNT);
fsp_err_t HW_SCE_Aes128EcbEncryptFinalPrivate(uint32_t *OutData_Text, uint32_t *OutData_length);
fsp_err_t HW_SCE_Aes128EcbDecryptInitPrivate(sce_aes_key_index_t *key_index);
fsp_err_t HW_SCE_Aes128EcbDecryptUpdatePrivate(uint32_t *InData_Text, uint32_t *OutData_Text, uint32_t MAX_CNT);
fsp_err_t HW_SCE_Aes128EcbDecryptFinalPrivate(uint32_t *OutData_Text, uint32_t *OutData_length);
fsp_err_t HW_SCE_Aes128CbcEncryptInitPrivate(sce_aes_key_index_t *key_index, uint32_t *InData_IV);
fsp_err_t HW_SCE_Aes128CbcEncryptUpdatePrivate(uint32_t *InData_Text, uint32_t *OutData_Text, uint32_t MAX_CNT);
fsp_err_t HW_SCE_Aes128CbcEncryptFinalPrivate(uint32_t *OutData_Text, uint32_t *OutData_length);
fsp_err_t HW_SCE_Aes128CbcDecryptInitPrivate(sce_aes_key_index_t *key_index, uint32_t *InData_IV);
fsp_err_t HW_SCE_Aes128CbcDecryptUpdatePrivate(uint32_t *InData_Text, uint32_t *OutData_Text, uint32_t MAX_CNT);
fsp_err_t HW_SCE_Aes128CbcDecryptFinalPrivate(uint32_t *OutData_Text, uint32_t *OutData_length);

fsp_err_t HW_SCE_Aes192EcbEncryptInitPrivate(sce_aes_key_index_t *key_index);
fsp_err_t HW_SCE_Aes192EcbEncryptUpdatePrivate(uint32_t *InData_Text, uint32_t *OutData_Text, uint32_t MAX_CNT);
fsp_err_t HW_SCE_Aes192EcbEncryptFinalPrivate(uint32_t *OutData_Text, uint32_t *OutData_length);
fsp_err_t HW_SCE_Aes192EcbDecryptInitPrivate(sce_aes_key_index_t *key_index);
fsp_err_t HW_SCE_Aes192EcbDecryptUpdatePrivate(uint32_t *InData_Text, uint32_t *OutData_Text, uint32_t MAX_CNT);
fsp_err_t HW_SCE_Aes192EcbDecryptFinalPrivate(uint32_t *OutData_Text, uint32_t *OutData_length);
fsp_err_t HW_SCE_Aes192CbcEncryptInitPrivate(sce_aes_key_index_t *key_index, uint32_t *InData_IV);
fsp_err_t HW_SCE_Aes192CbcEncryptUpdatePrivate(uint32_t *InData_Text, uint32_t *OutData_Text, uint32_t MAX_CNT);
fsp_err_t HW_SCE_Aes192CbcEncryptFinalPrivate(uint32_t *OutData_Text, uint32_t *OutData_length);
fsp_err_t HW_SCE_Aes192CbcDecryptInitPrivate(sce_aes_key_index_t *key_index, uint32_t *InData_IV);
fsp_err_t HW_SCE_Aes192CbcDecryptUpdatePrivate(uint32_t *InData_Text, uint32_t *OutData_Text, uint32_t MAX_CNT);
fsp_err_t HW_SCE_Aes192CbcDecryptFinalPrivate(uint32_t *OutData_Text, uint32_t *OutData_length);

fsp_err_t HW_SCE_Aes256EcbEncryptInitPrivate(sce_aes_key_index_t *key_index);
fsp_err_t HW_SCE_Aes256EcbEncryptUpdatePrivate(uint32_t *InData_Text, uint32_t *OutData_Text, uint32_t MAX_CNT);
fsp_err_t HW_SCE_Aes256EcbEncryptFinalPrivate(uint32_t *OutData_Text, uint32_t *OutData_length);
fsp_err_t HW_SCE_Aes256EcbDecryptInitPrivate(sce_aes_key_index_t *key_index);
fsp_err_t HW_SCE_Aes256EcbDecryptUpdatePrivate(uint32_t *InData_Text, uint32_t *OutData_Text, uint32_t MAX_CNT);
fsp_err_t HW_SCE_Aes256EcbDecryptFinalPrivate(uint32_t *OutData_Text, uint32_t *OutData_length);
fsp_err_t HW_SCE_Aes256CbcEncryptInitPrivate(sce_aes_key_index_t *key_index, uint32_t *InData_IV);
fsp_err_t HW_SCE_Aes256CbcEncryptUpdatePrivate(uint32_t *InData_Text, uint32_t *OutData_Text, uint32_t MAX_CNT);
fsp_err_t HW_SCE_Aes256CbcEncryptFinalPrivate(uint32_t *OutData_Text, uint32_t *OutData_length);
fsp_err_t HW_SCE_Aes256CbcDecryptInitPrivate(sce_aes_key_index_t *key_index, uint32_t *InData_IV);
fsp_err_t HW_SCE_Aes256CbcDecryptUpdatePrivate(uint32_t *InData_Text, uint32_t *OutData_Text, uint32_t MAX_CNT);
fsp_err_t HW_SCE_Aes256CbcDecryptFinalPrivate(uint32_t *OutData_Text, uint32_t *OutData_length);

fsp_err_t HW_SCE_Aes128CtrEncryptInitPrivate(sce_aes_key_index_t *key_index, uint32_t *InData_ICOUNTER);
fsp_err_t HW_SCE_Aes128CtrEncryptUpdatePrivate(uint32_t *InData_Text, uint32_t *OutData_Text, uint32_t MAX_CNT);
fsp_err_t HW_SCE_Aes128CtrEncryptFinalPrivate(uint32_t *OutData_Text, uint32_t *OutData_length);
fsp_err_t HW_SCE_Aes128CtrDecryptInitPrivate(sce_aes_key_index_t *key_index, uint32_t *InData_ICOUNTER);
fsp_err_t HW_SCE_Aes128CtrDecryptUpdatePrivate(uint32_t *InData_Text, uint32_t *OutData_Text, uint32_t MAX_CNT);
fsp_err_t HW_SCE_Aes128CtrDecryptFinalPrivate(uint32_t *OutData_Text, uint32_t *OutData_length);

fsp_err_t HW_SCE_Aes192CtrEncryptInitPrivate(sce_aes_key_index_t *key_index, uint32_t *InData_ICOUNTER);
fsp_err_t HW_SCE_Aes192CtrEncryptUpdatePrivate(uint32_t *InData_Text, uint32_t *OutData_Text, uint32_t MAX_CNT);
fsp_err_t HW_SCE_Aes192CtrEncryptFinalPrivate(uint32_t *OutData_Text, uint32_t *OutData_length);
fsp_err_t HW_SCE_Aes192CtrDecryptInitPrivate(sce_aes_key_index_t *key_index, uint32_t *InData_ICOUNTER);
fsp_err_t HW_SCE_Aes192CtrDecryptUpdatePrivate(uint32_t *InData_Text, uint32_t *OutData_Text, uint32_t MAX_CNT);
fsp_err_t HW_SCE_Aes192CtrDecryptFinalPrivate(uint32_t *OutData_Text, uint32_t *OutData_length);

fsp_err_t HW_SCE_Aes256CtrEncryptInitPrivate(sce_aes_key_index_t *key_index, uint32_t *InData_ICOUNTER);
fsp_err_t HW_SCE_Aes256CtrEncryptUpdatePrivate(uint32_t *InData_Text, uint32_t *OutData_Text, uint32_t MAX_CNT);
fsp_err_t HW_SCE_Aes256CtrEncryptFinalPrivate(uint32_t *OutData_Text, uint32_t *OutData_length);
fsp_err_t HW_SCE_Aes256CtrDecryptInitPrivate(sce_aes_key_index_t *key_index, uint32_t *InData_ICOUNTER);
fsp_err_t HW_SCE_Aes256CtrDecryptUpdatePrivate(uint32_t *InData_Text, uint32_t *OutData_Text, uint32_t MAX_CNT);
fsp_err_t HW_SCE_Aes256CtrDecryptFinalPrivate(uint32_t *OutData_Text, uint32_t *OutData_length);

fsp_err_t HW_SCE_Aes128XtsEncryptInitPrivate(sce_aes_key_index_t *key_index, uint32_t *InData_IV);
fsp_err_t HW_SCE_Aes128XtsEncryptUpdatePrivate(uint32_t *InData_Text, uint32_t *OutData_Text, uint32_t MAX_CNT);
fsp_err_t HW_SCE_Aes128XtsEncryptFinalPrivate(uint32_t *InData_TextBitLen, uint32_t *InData_Text, uint32_t *OutData_Text);
fsp_err_t HW_SCE_Aes128XtsDecryptInitPrivate(sce_aes_key_index_t *key_index, uint32_t *InData_IV);
fsp_err_t HW_SCE_Aes128XtsDecryptUpdatePrivate(uint32_t *InData_Text, uint32_t *OutData_Text, uint32_t MAX_CNT);
fsp_err_t HW_SCE_Aes128XtsDecryptFinalPrivate(uint32_t *InData_TextBitLen, uint32_t *InData_Text, uint32_t *OutData_Text);
fsp_err_t HW_SCE_Aes256XtsEncryptInitPrivate(sce_aes_key_index_t *key_index, uint32_t *InData_IV);
fsp_err_t HW_SCE_Aes256XtsEncryptUpdatePrivate(uint32_t *InData_Text, uint32_t *OutData_Text, uint32_t MAX_CNT);
fsp_err_t HW_SCE_Aes256XtsEncryptFinalPrivate(uint32_t *InData_TextBitLen, uint32_t *InData_Text, uint32_t *OutData_Text);
fsp_err_t HW_SCE_Aes256XtsDecryptInitPrivate(sce_aes_key_index_t *key_index, uint32_t *InData_IV);
fsp_err_t HW_SCE_Aes256XtsDecryptUpdatePrivate(uint32_t *InData_Text, uint32_t *OutData_Text, uint32_t MAX_CNT);
fsp_err_t HW_SCE_Aes256XtsDecryptFinalPrivate(uint32_t *InData_TextBitLen, uint32_t *InData_Text, uint32_t *OutData_Text);

fsp_err_t HW_SCE_Aes128GcmEncryptInitPrivate(sce_aes_key_index_t *key_index, uint32_t *InData_IV);
fsp_err_t HW_SCE_Aes128GcmEncryptUpdateAadPrivate(uint32_t *InData_DataA, uint32_t MAX_CNT);
fsp_err_t HW_SCE_Aes128GcmEncryptUpdatePrivate(uint32_t *InData_Text, uint32_t MAX_CNT, uint32_t *OutData_Text);
fsp_err_t HW_SCE_Aes128GcmEncryptFinalPrivate(uint32_t *InData_Text, uint32_t *InData_DataALen,
        uint32_t *InData_TextLen, uint32_t *OutData_Text, uint32_t *OutData_DataT);
fsp_err_t HW_SCE_Aes128GcmDecryptInitPrivate(sce_aes_key_index_t *key_index, uint32_t *InData_IV);
fsp_err_t HW_SCE_Aes128GcmDecryptUpdateAadPrivate(uint32_t *InData_DataA, uint32_t MAX_CNT);
fsp_err_t HW_SCE_Aes128GcmDecryptUpdatePrivate(uint32_t *InData_Text, uint32_t MAX_CNT, uint32_t *OutData_Text);
fsp_err_t HW_SCE_Aes128GcmDecryptFinalPrivate(uint32_t *InData_Text, uint32_t *InData_DataT,
        uint32_t *InData_DataALen, uint32_t *InData_TextLen, uint32_t *InData_DataTLen, uint32_t *OutData_Text);

fsp_err_t HW_SCE_Aes192GcmEncryptInitPrivate(sce_aes_key_index_t *key_index, uint32_t *InData_IV);
fsp_err_t HW_SCE_Aes192GcmEncryptUpdateAadPrivate(uint32_t *InData_DataA, uint32_t MAX_CNT);
fsp_err_t HW_SCE_Aes192GcmEncryptUpdatePrivate(uint32_t *InData_Text, uint32_t MAX_CNT, uint32_t *OutData_Text);
fsp_err_t HW_SCE_Aes192GcmEncryptFinalPrivate(uint32_t *InData_Text, uint32_t *InData_DataALen,
        uint32_t *InData_TextLen, uint32_t *OutData_Text, uint32_t *OutData_DataT);
fsp_err_t HW_SCE_Aes192GcmDecryptInitPrivate(sce_aes_key_index_t *key_index, uint32_t *InData_IV);
fsp_err_t HW_SCE_Aes192GcmDecryptUpdateAadPrivate(uint32_t *InData_DataA, uint32_t MAX_CNT);
fsp_err_t HW_SCE_Aes192GcmDecryptUpdatePrivate(uint32_t *InData_Text, uint32_t MAX_CNT, uint32_t *OutData_Text);
fsp_err_t HW_SCE_Aes192GcmDecryptFinalPrivate(uint32_t *InData_Text, uint32_t *InData_DataT,
        uint32_t *InData_DataALen, uint32_t *InData_TextLen, uint32_t *InData_DataTLen, uint32_t *OutData_Text);

fsp_err_t HW_SCE_Aes256GcmEncryptInitPrivate(sce_aes_key_index_t *key_index, uint32_t *InData_IV);
fsp_err_t HW_SCE_Aes256GcmEncryptUpdateAadPrivate(uint32_t *InData_DataA, uint32_t MAX_CNT);
fsp_err_t HW_SCE_Aes256GcmEncryptUpdatePrivate(uint32_t *InData_Text, uint32_t MAX_CNT, uint32_t *OutData_Text);
fsp_err_t HW_SCE_Aes256GcmEncryptFinalPrivate(uint32_t *InData_Text, uint32_t *InData_DataALen,
        uint32_t *InData_TextLen, uint32_t *OutData_Text, uint32_t *OutData_DataT);
fsp_err_t HW_SCE_Aes256GcmDecryptInitPrivate(sce_aes_key_index_t *key_index, uint32_t *InData_IV);
fsp_err_t HW_SCE_Aes256GcmDecryptUpdateAadPrivate(uint32_t *InData_DataA, uint32_t MAX_CNT);
fsp_err_t HW_SCE_Aes256GcmDecryptUpdatePrivate(uint32_t *InData_Text, uint32_t MAX_CNT, uint32_t *OutData_Text);
fsp_err_t HW_SCE_Aes256GcmDecryptFinalPrivate(uint32_t *InData_Text, uint32_t *InData_DataT,
        uint32_t *InData_DataALen, uint32_t *InData_TextLen, uint32_t *InData_DataTLen, uint32_t *OutData_Text);

void         HW_SCE_Aes128GcmEncryptUpdateTransitionPrivate(void);
void         HW_SCE_Aes128GcmDecryptUpdateTransitionPrivate(void);
void         HW_SCE_Aes192GcmEncryptUpdateTransitionPrivate(void);
void         HW_SCE_Aes192GcmDecryptUpdateTransitionPrivate(void);
void         HW_SCE_Aes256GcmEncryptUpdateTransitionPrivate(void);
void         HW_SCE_Aes256GcmDecryptUpdateTransitionPrivate(void);

fsp_err_t HW_SCE_Aes128CcmEncryptInitPrivate(sce_aes_key_index_t *KeyIndex, uint32_t *InData_IV,
        uint32_t *InData_Header, uint32_t Header_Len);
fsp_err_t HW_SCE_Aes128CcmEncryptUpdatePrivate(uint32_t *InData_Text, uint32_t *OutData_Text, uint32_t MAX_CNT);
fsp_err_t HW_SCE_Aes128CcmEncryptFinalPrivate(const uint32_t *InData_TextLen, const uint32_t *InData_Text,
        uint32_t *OutData_Text, uint32_t *OutData_MAC);
fsp_err_t HW_SCE_Aes128CcmDecryptInitPrivate(sce_aes_key_index_t *KeyIndex, uint32_t *InData_IV,
        uint32_t *InData_Header, uint32_t Header_Len);
fsp_err_t HW_SCE_Aes128CcmDecryptUpdatePrivate(uint32_t *InData_Text, uint32_t *OutData_Text, uint32_t MAX_CNT);
fsp_err_t HW_SCE_Aes128CcmDecryptFinalPrivate(const uint32_t *InData_Text, const uint32_t *InData_TextLen, const uint32_t *InData_MAC,
        const uint32_t *InData_MACLength, uint32_t *OutData_Text);

fsp_err_t HW_SCE_Aes192CcmEncryptInitPrivate(sce_aes_key_index_t *KeyIndex, uint32_t *InData_IV,
        uint32_t *InData_Header, uint32_t Header_Len);
fsp_err_t HW_SCE_Aes192CcmEncryptUpdatePrivate(uint32_t *InData_Text, uint32_t *OutData_Text, uint32_t MAX_CNT);
fsp_err_t HW_SCE_Aes192CcmEncryptFinalPrivate(uint32_t *InData_TextLen, uint32_t *InData_Text,
        uint32_t *OutData_Text, uint32_t *OutData_MAC);
fsp_err_t HW_SCE_Aes192CcmDecryptInitPrivate(sce_aes_key_index_t *KeyIndex, uint32_t *InData_IV,
        uint32_t *InData_Header, uint32_t Header_Len);
fsp_err_t HW_SCE_Aes192CcmDecryptUpdatePrivate(uint32_t *InData_Text, uint32_t *OutData_Text, uint32_t MAX_CNT);
fsp_err_t HW_SCE_Aes192CcmDecryptFinalPrivate(uint32_t *InData_Text, uint32_t *InData_TextLen, uint32_t *InData_MAC,
        uint32_t *InData_MACLength, uint32_t *OutData_Text);

fsp_err_t HW_SCE_Aes256CcmEncryptInitPrivate(sce_aes_key_index_t *KeyIndex, uint32_t *InData_IV,
        uint32_t *InData_Header, uint32_t Header_Len);
fsp_err_t HW_SCE_Aes256CcmEncryptUpdatePrivate(uint32_t *InData_Text, uint32_t *OutData_Text, uint32_t MAX_CNT);
fsp_err_t HW_SCE_Aes256CcmEncryptFinalPrivate(uint32_t *InData_TextLen, uint32_t *InData_Text,
        uint32_t *OutData_Text, uint32_t *OutData_MAC);
fsp_err_t HW_SCE_Aes256CcmDecryptInitPrivate(sce_aes_key_index_t *KeyIndex, uint32_t *InData_IV,
        uint32_t *InData_Header, uint32_t Header_Len);
fsp_err_t HW_SCE_Aes256CcmDecryptUpdatePrivate(uint32_t *InData_Text, uint32_t *OutData_Text, uint32_t MAX_CNT);
fsp_err_t HW_SCE_Aes256CcmDecryptFinalPrivate(uint32_t *InData_Text, uint32_t *InData_TextLen, uint32_t *InData_MAC,
        uint32_t *InData_MACLength, uint32_t *OutData_Text);

fsp_err_t HW_SCE_Aes128CmacGenerateInitPrivate(sce_aes_key_index_t *key_index);
fsp_err_t HW_SCE_Aes128CmacGenerateUpdatePrivate(uint32_t *InData_Text, uint32_t MAX_CNT);
fsp_err_t HW_SCE_Aes128CmacGenerateFinalPrivate(uint32_t All_Msg_Len, uint32_t *InData_Text,
        uint32_t *OutData_DataT);
fsp_err_t HW_SCE_Aes128CmacVerifyInitPrivate(sce_aes_key_index_t *key_index);
fsp_err_t HW_SCE_Aes128CmacVerifyUpdatePrivate(uint32_t *InData_Text, uint32_t MAX_CNT);
fsp_err_t HW_SCE_Aes128CmacVerifyFinalPrivate(uint32_t All_Msg_Len, uint32_t *InData_Text, uint32_t *InData_DataT,
        uint32_t *InData_DataTLen);

fsp_err_t HW_SCE_Aes256CmacGenerateInitPrivate(sce_aes_key_index_t *key_index);
fsp_err_t HW_SCE_Aes256CmacGenerateUpdatePrivate(uint32_t *InData_Text, uint32_t MAX_CNT);
fsp_err_t HW_SCE_Aes256CmacGenerateFinalPrivate(uint32_t All_Msg_Len, uint32_t *InData_Text,
        uint32_t *OutData_DataT);
fsp_err_t HW_SCE_Aes256CmacVerifyInitPrivate(sce_aes_key_index_t *key_index);
fsp_err_t HW_SCE_Aes256CmacVerifyUpdatePrivate(uint32_t *InData_Text, uint32_t MAX_CNT);
fsp_err_t HW_SCE_Aes256CmacVerifyFinalPrivate(uint32_t All_Msg_Len, uint32_t *InData_Text, uint32_t *InData_DataT,
        uint32_t *InData_DataTLen);

fsp_err_t HW_SCE_Sha1InitPrivate(sce_sha_md5_handle_t *handle);
fsp_err_t HW_SCE_Sha1UpdatePrivate(sce_sha_md5_handle_t *handle, uint32_t *InData_PaddedMsg, uint32_t MAX_CNT);
fsp_err_t HW_SCE_Sha1FinalPrivate(sce_sha_md5_handle_t *handle, uint32_t *InData_PaddedMsg, uint32_t MAX_CNT,
        uint32_t *OutData_MsgDigest, uint32_t *OutData_Length);
fsp_err_t HW_SCE_Sha256InitPrivate(sce_sha_md5_handle_t *handle);
fsp_err_t HW_SCE_Sha256UpdatePrivate(sce_sha_md5_handle_t *handle, uint32_t *InData_PaddedMsg, uint32_t MAX_CNT);
fsp_err_t HW_SCE_Sha256FinalPrivate(sce_sha_md5_handle_t *handle, uint32_t *InData_PaddedMsg, uint32_t MAX_CNT,
        uint32_t *OutData_MsgDigest, uint32_t *OutData_Length);
fsp_err_t HW_SCE_Md5InitPrivate(sce_sha_md5_handle_t *handle);
fsp_err_t HW_SCE_Md5UpdatePrivate(sce_sha_md5_handle_t *handle, uint32_t *InData_PaddedMsg, uint32_t MAX_CNT);
fsp_err_t HW_SCE_Md5FinalPrivate(sce_sha_md5_handle_t *handle, uint32_t *InData_PaddedMsg, uint32_t MAX_CNT,
        uint32_t *OutData_MsgDigest, uint32_t *OutData_Length);

fsp_err_t HW_SCE_Sha1HmacGenerateInitPrivate(sce_hmac_sha_handle_t *handle, sce_hmac_sha_key_index_t *key_index);
fsp_err_t HW_SCE_Sha1HmacGenerateUpdatePrivate(sce_hmac_sha_handle_t *handle, uint32_t *InData_PaddedMsg,
        uint32_t MAX_CNT);
fsp_err_t HW_SCE_Sha1HmacGenerateFinalPrivate(sce_hmac_sha_handle_t *handle, uint32_t *OutData_Mac);
fsp_err_t HW_SCE_Sha1HmacVerifyInitPrivate(sce_hmac_sha_handle_t *handle, sce_hmac_sha_key_index_t *key_index);
fsp_err_t HW_SCE_Sha1HmacVerifyUpdatePrivate(sce_hmac_sha_handle_t *handle, uint32_t *InData_PaddedMsg,
        uint32_t MAX_CNT);
fsp_err_t HW_SCE_Sha1HmacVerifyFinalPrivate(sce_hmac_sha_handle_t *handle, uint32_t *InData_Mac,
        uint32_t *InData_length);
fsp_err_t HW_SCE_Sha256HmacGenerateInitPrivate(sce_hmac_sha_handle_t *handle,
        sce_hmac_sha_key_index_t *key_index);
fsp_err_t HW_SCE_Sha256HmacGenerateUpdatePrivate(sce_hmac_sha_handle_t *handle, uint32_t *InData_PaddedMsg,
        uint32_t MAX_CNT);
fsp_err_t HW_SCE_Sha256HmacGenerateFinalPrivate(sce_hmac_sha_handle_t *handle, uint32_t *OutData_Mac);
fsp_err_t HW_SCE_Sha256HmacVerifyInitPrivate(sce_hmac_sha_handle_t *handle, sce_hmac_sha_key_index_t *key_index);
fsp_err_t HW_SCE_Sha256HmacVerifyUpdatePrivate(sce_hmac_sha_handle_t *handle, uint32_t *InData_PaddedMsg,
        uint32_t MAX_CNT);
fsp_err_t HW_SCE_Sha256HmacVerifyFinalPrivate(sce_hmac_sha_handle_t *handle, uint32_t *InData_Mac,
        uint32_t *InData_length);

fsp_err_t HW_SCE_Rsa1024ModularExponentEncryptPrivate(uint32_t *InData_KeyIndex, uint32_t *InData_Text,
        uint32_t *OutData_Text);
fsp_err_t HW_SCE_Rsa1024ModularExponentDecryptPrivate(uint32_t *InData_KeyIndex, uint32_t *InData_Text,
        uint32_t *OutData_Text);
fsp_err_t HW_SCE_Rsa2048ModularExponentEncryptPrivate(uint32_t *InData_KeyIndex, uint32_t *InData_Text,
        uint32_t *OutData_Text);
fsp_err_t HW_SCE_Rsa2048ModularExponentDecryptPrivate(uint32_t *InData_KeyIndex, uint32_t *InData_Text,
        uint32_t *OutData_Text);
fsp_err_t HW_SCE_Rsa3072ModularExponentEncryptPrivate(uint32_t *InData_KeyIndex, uint32_t *InData_Text,
        uint32_t *OutData_Text);
fsp_err_t HW_SCE_Rsa3072ModularExponentDecryptPrivate(uint32_t *InData_KeyIndex, uint32_t *InData_Text,
        uint32_t *OutData_Text);
fsp_err_t HW_SCE_Rsa4096ModularExponentEncryptPrivate(uint32_t *InData_KeyIndex, uint32_t *InData_Text,
        uint32_t *OutData_Text);
fsp_err_t HW_SCE_Rsa4096ModularExponentDecryptPrivate(uint32_t *InData_KeyIndex, uint32_t *InData_Text,
        uint32_t *OutData_Text);

fsp_err_t HW_SCE_Ecc256ScalarMultiplicationPrivate(uint32_t *InData_CurveType, uint32_t *InData_Cmd, 
        uint32_t *InData_KeyIndex, uint32_t *InData_PubKey, uint32_t *OutData_R);
fsp_err_t HW_SCE_Ecc256ScalarMultiplicationSub(const uint32_t *InData_CurveType, const uint32_t *InData_Cmd,
        const uint32_t *InData_KeyIndex, const uint32_t *InData_PubKey, uint32_t *OutData_R);
fsp_err_t HW_SCE_Ecc256ScalarMultiplicationSubAdaptor(const uint32_t InData_CurveType[], const uint32_t InData_Cmd[], 
        const uint32_t InData_KeyIndex[], const uint32_t InData_PubKey[], const uint32_t InData_DomainParam[], uint32_t OutData_R[]);
fsp_err_t HW_SCE_Ecc384ScalarMultiplicationPrivate(uint32_t *InData_CurveType,
        uint32_t *InData_KeyIndex, uint32_t *InData_PubKey, uint32_t *OutData_R);
fsp_err_t HW_SCE_Ecc384ScalarMultiplicationSub(const uint32_t *InData_CurveType,
        const uint32_t *InData_KeyIndex, const uint32_t *InData_PubKey, uint32_t *OutData_R);

fsp_err_t HW_SCE_TdesEcbEncryptInitPrivate(sce_tdes_key_index_t *key_index);
fsp_err_t HW_SCE_TdesEcbEncryptUpdatePrivate(uint32_t *InData_Text, uint32_t *OutData_Text, uint32_t MAX_CNT);
fsp_err_t HW_SCE_TdesEcbEncryptFinalPrivate(void);
fsp_err_t HW_SCE_TdesEcbDecryptInitPrivate(sce_tdes_key_index_t *key_index);
fsp_err_t HW_SCE_TdesEcbDecryptUpdatePrivate(uint32_t *InData_Text, uint32_t *OutData_Text, uint32_t MAX_CNT);
fsp_err_t HW_SCE_TdesEcbDecryptFinalPrivate(void);
fsp_err_t HW_SCE_TdesCbcEncryptInitPrivate(sce_tdes_key_index_t *key_index, uint32_t *InData_IV);
fsp_err_t HW_SCE_TdesCbcEncryptUpdatePrivate(uint32_t *InData_Text, uint32_t *OutData_Text, uint32_t MAX_CNT);
fsp_err_t HW_SCE_TdesCbcEncryptFinalPrivate(void);
fsp_err_t HW_SCE_TdesCbcDecryptInitPrivate(sce_tdes_key_index_t *key_index, uint32_t *InData_IV);
fsp_err_t HW_SCE_TdesCbcDecryptUpdatePrivate(uint32_t *InData_Text, uint32_t *OutData_Text, uint32_t MAX_CNT);
fsp_err_t HW_SCE_TdesCbcDecryptFinalPrivate(void);

fsp_err_t HW_SCE_EcdhReadPublicKeyPrivate(uint32_t *InData_Cmd, uint32_t *InData_KeyIndex, uint32_t *InData_data,
        uint32_t *InData_Signature, uint32_t *OutData_KeyIndex);
fsp_err_t HW_SCE_EcdhMakePublicKeyPrivate(uint32_t *InData_Cmd, uint32_t *InData_KeyType,
        uint32_t *InData_PubKeyIndex, uint32_t *InData_PrivKeyIndex, uint32_t *InData_key_id, uint32_t *OutData_data,
        uint32_t *OutData_Signature, uint32_t *OutData_KeyIndex);
fsp_err_t HW_SCE_EcdhCalculateSharedSecretIndexPrivate(uint32_t *InData_KeyType, uint32_t *InData_PubKeyIndex,
        uint32_t *InData_PrivKeyIndex, uint32_t *OutData_KeyIndex);
fsp_err_t HW_SCE_EcdhKeyDerivationPrivate(uint32_t *InData_KeyIndex, uint32_t *InData_PaddedMsg, uint32_t MAX_CNT,
        uint32_t *OutData_KeyIndex);

fsp_err_t HW_SCE_DlmsCosemP384QeuSignatureVerificationPrivate(uint32_t *InData_KeyIndex, uint32_t *InData_MsgDgst, uint32_t *InData_Signature, uint32_t *InData_QeU, uint32_t *OutData_KeyIndex);
fsp_err_t HW_SCE_DlmsCosemP384QevSignatureGenerationPrivate(uint32_t *InData_Cmd, uint32_t *InData_PrivKeyIndex, uint32_t *InData_key_id, uint32_t *InData_MsgDgst, uint32_t *OutData_data, uint32_t *OutData_Signature, uint32_t *OutData_KeyIndex);
fsp_err_t HW_SCE_DlmsCosemP384QevOutputPrivate(uint32_t *InData_KeyType, uint32_t *InData_PubKeyIndex, uint32_t *OutData_PubKey);
fsp_err_t HW_SCE_DlmsCosemP384CalculateZPrivate(uint32_t *InData_KeyType, uint32_t *InData_PubKeyIndex, uint32_t *InData_PrivKeyIndex, uint32_t *OutData_KeyIndex);
fsp_err_t HW_SCE_DlmsCosemP384CalculateKekPrivate(uint32_t *InData_KEK, uint32_t *OutData_KeyIndex);
fsp_err_t HW_SCE_DlmsCosemP384OutputZPrivate(uint32_t *InData_KeyIndex, uint32_t *InData_AlgorithmID, uint32_t *OutData_Z);
fsp_err_t HW_SCE_DlmsCosemP384KeyUnwrapPrivate(uint32_t *InData_KeyIndex, uint32_t *InData_Text, uint32_t *OutData_KeyIndex);

fsp_err_t HW_SCE_Aes128KeyWrapPrivate(uint32_t *InData_KeyIndex, uint32_t *InData_WrappedKeyType,
        uint32_t *InData_WrappedKeyIndex, uint32_t *OutData_Text);
fsp_err_t HW_SCE_Aes256KeyWrapPrivate(uint32_t *InData_KeyIndex, uint32_t *InData_WrappedKeyType,
        uint32_t *InData_WrappedKeyIndex, uint32_t *OutData_Text);
fsp_err_t HW_SCE_Aes128KeyUnWrapPrivate(uint32_t *InData_KeyIndex, uint32_t *InData_WrappedKeyType,
        uint32_t *InData_Text, uint32_t *OutData_KeyIndex);
fsp_err_t HW_SCE_Aes256KeyUnWrapPrivate(uint32_t *InData_KeyIndex, uint32_t *InData_WrappedKeyType,
        uint32_t *InData_Text, uint32_t *OutData_KeyIndex);
fsp_err_t HW_SCE_KeyUnwrapPrivate(uint32_t *InData_KeyIndex, uint32_t *InData_Text, uint32_t *OutData_KeyIndex);


/* --------------------- SCE control procedure related ---------------------- */

void      HW_SCE_SoftwareResetSub(void);
fsp_err_t HW_SCE_SelfCheck1Sub(void);
fsp_err_t HW_SCE_SelfCheck2Sub(void);

fsp_err_t HW_SCE_GenerateUpdateKeyRingKeyIndexSub(uint32_t *InData_LC, uint32_t *InData_SharedKeyIndex, uint32_t *InData_SessionKey, uint32_t *InData_IV, uint32_t *InData_InstData, uint32_t *OutData_InstData);
fsp_err_t HW_SCE_UpdateOemKeyIndexSub(uint32_t *InData_LC, uint32_t *InData_Cmd, uint32_t *InData_IV, uint32_t *InData_InstData, uint32_t *OutData_KeyIndex);
fsp_err_t HW_SCE_GenerateOemKeyIndexSub(uint32_t *InData_KeyType, uint32_t *InData_Cmd, uint32_t *InData_SharedKeyIndex, uint32_t *InData_SessionKey, uint32_t *InData_IV, uint32_t *InData_InstData, uint32_t *OutData_KeyIndex);
fsp_err_t HW_SCE_OemKeyValidationForPlainKeySub(uint32_t *InData_Cmd, uint32_t *InData_KeyIndex, uint32_t KEY_INDEX_SIZE);
fsp_err_t HW_SCE_GenerateAes128KeyIndexSub(uint32_t *InData_SharedKeyIndex, uint32_t *InData_SessionKey,
        uint32_t *InData_IV, uint32_t *InData_InstData, uint32_t *OutData_KeyIndex);
fsp_err_t HW_SCE_GenerateAes192KeyIndexSub(uint32_t *InData_SharedKeyIndex, uint32_t *InData_SessionKey,
        uint32_t *InData_IV, uint32_t *InData_InstData, uint32_t *OutData_KeyIndex);
fsp_err_t HW_SCE_GenerateAes256KeyIndexSub(uint32_t *InData_SharedKeyIndex, uint32_t *InData_SessionKey,
        uint32_t *InData_IV, uint32_t *InData_InstData, uint32_t *OutData_KeyIndex);
fsp_err_t HW_SCE_GenerateAes128RandomKeyIndexSub(uint32_t *OutData_KeyIndex);
fsp_err_t HW_SCE_GenerateAes192RandomKeyIndexSub(uint32_t *OutData_KeyIndex);
fsp_err_t HW_SCE_GenerateAes256RandomKeyIndexSub(uint32_t *OutData_KeyIndex);
fsp_err_t HW_SCE_GenerateTdesKeyIndexSub(uint32_t *InData_SharedKeyIndex, uint32_t *InData_SessionKey,
        uint32_t *InData_IV, uint32_t *InData_InstData, uint32_t *OutData_KeyIndex);
fsp_err_t HW_SCE_GenerateTdesRandomKeyIndexSub(uint32_t *OutData_KeyIndex);
fsp_err_t HW_SCE_GenerateRsa1024PublicKeyIndexSub(uint32_t *InData_SharedKeyIndex, uint32_t *InData_SessionKey,
        uint32_t *InData_IV, uint32_t *InData_InstData, uint32_t *OutData_KeyIndex);
fsp_err_t HW_SCE_GenerateRsa1024PrivateKeyIndexSub(uint32_t *InData_SharedKeyIndex, uint32_t *InData_SessionKey,
        uint32_t *InData_IV, uint32_t *InData_InstData, uint32_t *OutData_KeyIndex);
fsp_err_t HW_SCE_GenerateRsa2048PublicKeyIndexSub(uint32_t *InData_KeyType, uint32_t *InData_SharedKeyIndex,
        uint32_t *InData_SessionKey, uint32_t *InData_IV, uint32_t *InData_InstData, uint32_t *OutData_KeyIndex);
fsp_err_t HW_SCE_GenerateRsa2048PrivateKeyIndexSub(uint32_t *InData_KeyType, uint32_t *InData_SharedKeyIndex,
        uint32_t *InData_SessionKey, uint32_t *InData_IV, uint32_t *InData_InstData, uint32_t *OutData_KeyIndex);
fsp_err_t HW_SCE_GenerateRsa3072PublicKeyIndexSub(uint32_t *InData_SharedKeyIndex, uint32_t *InData_SessionKey,
        uint32_t *InData_IV, uint32_t *InData_InstData, uint32_t *OutData_KeyIndex);
fsp_err_t HW_SCE_GenerateRsa3072PrivateKeyIndexSub(uint32_t *InData_SharedKeyIndex, uint32_t *InData_SessionKey,
        uint32_t *InData_IV, uint32_t *InData_InstData, uint32_t *OutData_KeyIndex);
fsp_err_t HW_SCE_GenerateRsa4096PublicKeyIndexSub(uint32_t *InData_SharedKeyIndex, uint32_t *InData_SessionKey,
        uint32_t *InData_IV, uint32_t *InData_InstData, uint32_t *OutData_KeyIndex);
fsp_err_t HW_SCE_GenerateRsa4096PrivateKeyIndexSub(uint32_t *InData_SharedKeyIndex, uint32_t *InData_SessionKey,
        uint32_t *InData_IV, uint32_t *InData_InstData, uint32_t *OutData_KeyIndex);
fsp_err_t HW_SCE_GenerateRsa1024RandomKeyIndexSub(uint32_t MAX_CNT, uint32_t *OutData_PubKeyIndex,
        uint32_t *OutData_PrivKeyIndex);
fsp_err_t HW_SCE_GenerateRsa2048RandomKeyIndexSub(uint32_t MAX_CNT, uint32_t *InData_KeyType, uint32_t *OutData_PubKeyIndex,
        uint32_t *OutData_PubKey, uint32_t *OutData_PrivKeyIndex, uint32_t *OutData_PrivKey);
fsp_err_t HW_SCE_GenerateRsa3072RandomKeyIndexSub(const uint32_t InData_KeyMode[], const uint32_t MAX_CNT,
        uint32_t OutData_PubKeyIndex[], uint32_t OutData_PubKey[], uint32_t OutData_PrivKeyIndex[], uint32_t OutData_PrivKey[]);
fsp_err_t HW_SCE_GenerateRsa4096RandomKeyIndexSub(uint32_t MAX_CNT, uint32_t *OutData_PubKeyIndex,
        uint32_t *OutData_PrivKeyIndex);
fsp_err_t HW_SCE_GenerateTlsRsaInstallDataSub(uint32_t *InData_SharedKeyIndex, uint32_t *InData_SessionKey,
        uint32_t *InData_IV, uint32_t *InData_InstData, uint32_t *OutData_InstData);
fsp_err_t HW_SCE_GenerateTlsP256EccKeyIndexSub(uint32_t *OutData_KeyIndex, uint32_t *OutData_PubKey);
fsp_err_t HW_SCE_GenerateEccPrivateKeyIndexSub(uint32_t *InData_KeyType, uint32_t *InData_SharedKeyIndex,
        uint32_t *InData_SessionKey, uint32_t *InData_CurveType, uint32_t *InData_Cmd, uint32_t *InData_IV, uint32_t *InData_InstData, uint32_t *OutData_KeyIndex);
fsp_err_t HW_SCE_GenerateEccP384PrivateKeyIndexSub(uint32_t *InData_KeyType, uint32_t *InData_SharedKeyIndex,
        uint32_t *InData_SessionKey, uint32_t *InData_IV, uint32_t *InData_InstData, uint32_t *OutData_KeyIndex);
fsp_err_t HW_SCE_GenerateEccPublicKeyIndexSub(uint32_t *InData_KeyType, uint32_t *InData_SharedKeyIndex, uint32_t *InData_SessionKey, uint32_t *InData_CurveType, uint32_t *InData_Cmd, uint32_t *InData_IV, uint32_t *InData_InstData, uint32_t *OutData_KeyIndex);
fsp_err_t HW_SCE_GenerateEccP384PublicKeyIndexSub(uint32_t *InData_KeyType, uint32_t *InData_SharedKeyIndex, uint32_t *InData_SessionKey, uint32_t *InData_IV, uint32_t *InData_InstData, uint32_t *OutData_KeyIndex);
fsp_err_t HW_SCE_GenerateEccRandomKeyIndexSub(const uint32_t *InData_CurveType, const uint32_t *InData_Cmd, const uint32_t *InData_KeyType, uint32_t *OutData_PubKeyIndex, uint32_t *OutData_PubKey, uint32_t *OutData_PrivKeyIndex, uint32_t *OutData_PrivKey);
fsp_err_t HW_SCE_GenerateEccP384RandomKeyIndexSub(const uint32_t *InData_CurveType, const uint32_t *InData_KeyType, uint32_t *OutData_PubKeyIndex, uint32_t *OutData_PubKey, uint32_t *OutData_PrivKeyIndex, uint32_t *OutData_PrivKey);
fsp_err_t HW_SCE_GenerateShaHmacKeyIndexSub(uint32_t *InData_KeyType, uint32_t *InData_SharedKeyIndex, uint32_t *InData_SessionKey,
        uint32_t *InData_Cmd, uint32_t *InData_IV, uint32_t *InData_InstData, uint32_t *OutData_KeyIndex);
fsp_err_t HW_SCE_GenerateRandomNumberSub(uint32_t *OutData_Text);

fsp_err_t HW_SCE_UpdateAes128KeyIndexSub(uint32_t *InData_IV, uint32_t *InData_InstData, uint32_t *OutData_KeyIndex);
fsp_err_t HW_SCE_UpdateAes192KeyIndexSub(uint32_t *InData_IV, uint32_t *InData_InstData, uint32_t *OutData_KeyIndex);
fsp_err_t HW_SCE_UpdateAes256KeyIndexSub(uint32_t *InData_IV, uint32_t *InData_InstData, uint32_t *OutData_KeyIndex);
fsp_err_t HW_SCE_UpdateTdesKeyIndexSub(uint32_t *InData_IV, uint32_t *InData_InstData, uint32_t *OutData_KeyIndex);
fsp_err_t HW_SCE_UpdateRsa1024PublicKeyIndexSub(uint32_t *InData_IV, uint32_t *InData_InstData,
        uint32_t *OutData_KeyIndex);
fsp_err_t HW_SCE_UpdateRsa1024PrivateKeyIndexSub(uint32_t *InData_IV, uint32_t *InData_InstData,
        uint32_t *OutData_KeyIndex);
fsp_err_t HW_SCE_UpdateRsa2048PublicKeyIndexSub(uint32_t *InData_IV, uint32_t *InData_InstData,
        uint32_t *OutData_KeyIndex);
fsp_err_t HW_SCE_UpdateRsa2048PrivateKeyIndexSub(uint32_t *InData_IV, uint32_t *InData_InstData,
        uint32_t *OutData_KeyIndex);
fsp_err_t HW_SCE_UpdateRsa3072PublicKeyIndexSub(uint32_t *InData_IV, uint32_t *InData_InstData,
        uint32_t *OutData_KeyIndex);
fsp_err_t HW_SCE_UpdateRsa3072PrivateKeyIndexSub(uint32_t *InData_IV, uint32_t *InData_InstData,
        uint32_t *OutData_KeyIndex);
fsp_err_t HW_SCE_UpdateRsa4096PublicKeyIndexSub(uint32_t *InData_IV, uint32_t *InData_InstData,
        uint32_t *OutData_KeyIndex);
fsp_err_t HW_SCE_UpdateRsa4096PrivateKeyIndexSub(uint32_t *InData_IV, uint32_t *InData_InstData,
        uint32_t *OutData_KeyIndex);
fsp_err_t HW_SCE_UpdateTlsRsaDataSub(uint32_t *InData_IV, uint32_t *InData_InstData, uint32_t *OutData_InstData);
fsp_err_t HW_SCE_UpdateEccPrivateKeyIndexSub(uint32_t *InData_Cmd, uint32_t *InData_IV,
        uint32_t *InData_InstData, uint32_t *OutData_KeyIndex);
fsp_err_t HW_SCE_UpdateEccPublicKeyIndexSub(uint32_t *InData_Cmd, uint32_t *InData_IV,
        uint32_t *InData_InstData, uint32_t *OutData_KeyIndex);
fsp_err_t HW_SCE_UpdateEccP384PrivateKeyIndexSub(uint32_t *InData_IV,
        uint32_t *InData_InstData, uint32_t *OutData_KeyIndex);
fsp_err_t HW_SCE_UpdateEccP384PublicKeyIndexSub(uint32_t *InData_IV,
        uint32_t *InData_InstData, uint32_t *OutData_KeyIndex);
fsp_err_t HW_SCE_UpdateShaHmacKeyIndexSub(uint32_t *InData_Cmd, uint32_t *InData_IV, uint32_t *InData_InstData,
        uint32_t *OutData_KeyIndex);

fsp_err_t HW_SCE_StartUpdateFirmwareSub(void);
fsp_err_t HW_SCE_GenerateFirmwareMacSub(uint32_t *InData_KeyIndex, uint32_t *InData_SessionKey,
        uint32_t *InData_UpProgram, uint32_t *InData_IV, uint32_t *OutData_Program, uint32_t MAX_CNT,
        sce_firmware_generate_mac_resume_handle_t *sce_firmware_generate_mac_resume_handle);
fsp_err_t HW_SCE_VerifyFirmwareMacSub(uint32_t *InData_Program, uint32_t MAX_CNT);

fsp_err_t HW_SCE_Aes128EncryptDecryptInitSub(const uint32_t *InData_KeyType, const uint32_t *InData_Cmd, const uint32_t *InData_KeyIndex, const uint32_t *InData_IV);
fsp_err_t HW_SCE_Aes128EncryptDecryptInitSubAdaptor (const uint32_t InData_KeyMode[],
                                              const uint32_t InData_Cmd[],
                                              const uint32_t InData_KeyIndex[],
                                              const uint32_t InData_Key[],
                                              const uint32_t InData_IV[]);
fsp_err_t HW_SCE_Aes192EncryptDecryptInitSubAdaptor (const uint32_t InData_KeyMode[],
		                                     const uint32_t InData_Cmd[],
                                                     const uint32_t InData_KeyIndex[],
                                                     const uint32_t InData_Key[],
                                                     const uint32_t InData_IV[]);
fsp_err_t HW_SCE_Aes256EncryptDecryptInitSubAdaptor (const uint32_t InData_KeyMode[], const uint32_t InData_Cmd[], const uint32_t InData_KeyIndex[], const uint32_t InData_Key[], const uint32_t InData_IV[]);
void         HW_SCE_Aes128EncryptDecryptUpdateSub(const uint32_t *InData_Text, uint32_t *OutData_Text, const uint32_t MAX_CNT);
fsp_err_t HW_SCE_Aes128EncryptDecryptFinalSub(void);
fsp_err_t HW_SCE_Aes192EncryptDecryptInitSub(const uint32_t *InData_Cmd, const uint32_t *InData_KeyIndex, const uint32_t *InData_IV);
void         HW_SCE_Aes192EncryptDecryptUpdateSub(const uint32_t *InData_Text, uint32_t *OutData_Text, const uint32_t MAX_CNT);
fsp_err_t HW_SCE_Aes192EncryptDecryptFinalSub(void);
fsp_err_t HW_SCE_Aes256EncryptDecryptInitSub(const uint32_t *InData_KeyType, const uint32_t *InData_Cmd, const uint32_t *InData_KeyIndex, const uint32_t *InData_IV);
void         HW_SCE_Aes256EncryptDecryptUpdateSub(const uint32_t *InData_Text, uint32_t *OutData_Text, const uint32_t MAX_CNT);
fsp_err_t HW_SCE_Aes256EncryptDecryptFinalSub(void);

fsp_err_t HW_SCE_GenerateAes128XtsRandomKeyIndexSub(uint32_t *OutData_KeyIndex);
fsp_err_t HW_SCE_GenerateAes256XtsRandomKeyIndexSub(uint32_t *OutData_KeyIndex);
fsp_err_t HW_SCE_Aes128XtsEncryptInitSub(uint32_t *InData_KeyIndex, uint32_t *InData_IV);
void HW_SCE_Aes128XtsEncryptUpdateSub(uint32_t *InData_Text, uint32_t *OutData_Text, uint32_t MAX_CNT);
fsp_err_t HW_SCE_Aes128XtsEncryptFinalSub(uint32_t *InData_TextBitLen, uint32_t *InData_Text, uint32_t *OutData_Text);
fsp_err_t HW_SCE_Aes128XtsDecryptInitSub(uint32_t *InData_KeyIndex, uint32_t *InData_IV);
void HW_SCE_Aes128XtsDecryptUpdateSub(uint32_t *InData_Text, uint32_t *OutData_Text, uint32_t MAX_CNT);
fsp_err_t HW_SCE_Aes128XtsDecryptFinalSub(uint32_t *InData_TextBitLen, uint32_t *InData_Text, uint32_t *OutData_Text);
fsp_err_t HW_SCE_Aes256XtsEncryptInitSub(uint32_t *InData_KeyIndex, uint32_t *InData_IV);
void HW_SCE_Aes256XtsEncryptUpdateSub(uint32_t *InData_Text, uint32_t *OutData_Text, uint32_t MAX_CNT);
fsp_err_t HW_SCE_Aes256XtsEncryptFinalSub(uint32_t *InData_TextBitLen, uint32_t *InData_Text, uint32_t *OutData_Text);
fsp_err_t HW_SCE_Aes256XtsDecryptInitSub(uint32_t *InData_KeyIndex, uint32_t *InData_IV);
void HW_SCE_Aes256XtsDecryptUpdateSub(uint32_t *InData_Text, uint32_t *OutData_Text, uint32_t MAX_CNT);
fsp_err_t HW_SCE_Aes256XtsDecryptFinalSub(uint32_t *InData_TextBitLen, uint32_t *InData_Text, uint32_t *OutData_Text);

fsp_err_t HW_SCE_Ghash(uint32_t *InData_HV, uint32_t *InData_IV, uint32_t *InData_Text, uint32_t *OutData_DataT,
        uint32_t MAX_CNT);

fsp_err_t HW_SCE_Aes128GcmEncryptInitSub(uint32_t *InData_KeyType, uint32_t *InData_KeyIndex, uint32_t *InData_IV);
void         HW_SCE_Aes128GcmEncryptUpdateSub(const uint32_t *InData_Text, uint32_t *OutData_Text, const uint32_t MAX_CNT);
fsp_err_t HW_SCE_Aes128GcmEncryptFinalSub(const uint32_t *InData_Text, const uint32_t *InData_TextLen, 
        const uint32_t *InData_DataALen, uint32_t *OutData_Text, uint32_t *OutData_DataT);
fsp_err_t HW_SCE_Aes128GcmDecryptInitSub(uint32_t *InData_KeyType, uint32_t *InData_KeyIndex, uint32_t *InData_IV);
void         HW_SCE_Aes128GcmDecryptUpdateSub(const uint32_t *InData_Text, uint32_t *OutData_Text, const uint32_t MAX_CNT);
fsp_err_t HW_SCE_Aes128GcmDecryptFinalSub(const uint32_t *InData_Text, const uint32_t *InData_TextLen, const uint32_t *InData_DataALen,
        const uint32_t *InData_DataT, const uint32_t *InData_DataTLen, uint32_t *OutData_Text);

fsp_err_t HW_SCE_Aes192GcmEncryptInitSub(uint32_t *InData_KeyIndex, uint32_t *InData_IV);
void         HW_SCE_Aes192GcmEncryptUpdateSub(const uint32_t *InData_Text, uint32_t *OutData_Text, const uint32_t MAX_CNT);
fsp_err_t HW_SCE_Aes192GcmEncryptFinalSub(const uint32_t *InData_Text, const uint32_t *InData_TextLen, 
        const uint32_t *InData_DataALen, uint32_t *OutData_Text, uint32_t *OutData_DataT);
fsp_err_t HW_SCE_Aes192GcmDecryptInitSub(uint32_t *InData_KeyIndex, uint32_t *InData_IV);
void         HW_SCE_Aes192GcmDecryptUpdateSub(const uint32_t *InData_Text, uint32_t *OutData_Text, const uint32_t MAX_CNT);
fsp_err_t HW_SCE_Aes192GcmDecryptFinalSub(const uint32_t *InData_Text, const uint32_t *InData_TextLen, const uint32_t *InData_DataALen,
        const uint32_t *InData_DataT, const uint32_t *InData_DataTLen, uint32_t *OutData_Text);

fsp_err_t HW_SCE_Aes256GcmEncryptInitSub(uint32_t *InData_KeyType, uint32_t *InData_KeyIndex, uint32_t *InData_IV);
void         HW_SCE_Aes256GcmEncryptUpdateSub(const uint32_t *InData_Text, uint32_t *OutData_Text, const uint32_t MAX_CNT);
fsp_err_t HW_SCE_Aes256GcmEncryptFinalSub(const uint32_t *InData_Text, const uint32_t *InData_TextLen,
        const uint32_t *InData_DataALen,uint32_t *OutData_Text, uint32_t *OutData_DataT);
fsp_err_t HW_SCE_Aes256GcmDecryptInitSub(uint32_t *InData_KeyType, uint32_t *InData_KeyIndex, uint32_t *InData_IV);
void         HW_SCE_Aes256GcmDecryptUpdateSub(const uint32_t *InData_Text, uint32_t *OutData_Text, const uint32_t MAX_CNT);
fsp_err_t HW_SCE_Aes256GcmDecryptFinalSub(const uint32_t *InData_Text, const uint32_t *InData_TextLen, const uint32_t *InData_DataALen,
        const uint32_t *InData_DataT, const uint32_t *InData_DataTLen, uint32_t *OutData_Text);

void         HW_SCE_Aes128GcmDecryptUpdateTransitionSub(void);
void         HW_SCE_Aes128GcmEncryptUpdateTransitionSub(void);
void         HW_SCE_Aes192GcmDecryptUpdateTransitionSub(void);
void         HW_SCE_Aes192GcmEncryptUpdateTransitionSub(void);
void         HW_SCE_Aes256GcmDecryptUpdateTransitionSub(void);
void         HW_SCE_Aes256GcmEncryptUpdateTransitionSub(void);
void         HW_SCE_Aes128GcmEncryptUpdateAADSub(const uint32_t *InData_DataA, const uint32_t MAX_CNT);
void         HW_SCE_Aes128GcmDecryptUpdateAADSub(const uint32_t *InData_DataA, const uint32_t MAX_CNT);
void         HW_SCE_Aes192GcmEncryptUpdateAADSub(const uint32_t *InData_DataA, const uint32_t MAX_CNT);
void         HW_SCE_Aes192GcmDecryptUpdateAADSub(const uint32_t *InData_DataA, const uint32_t MAX_CNT);
void         HW_SCE_Aes256GcmEncryptUpdateAADSub(const uint32_t *InData_DataA, const uint32_t MAX_CNT);
void         HW_SCE_Aes256GcmDecryptUpdateAADSub(const uint32_t *InData_DataA, const uint32_t MAX_CNT);

fsp_err_t HW_SCE_Aes128CcmEncryptInitSub(uint32_t *InData_KeyIndex, uint32_t *InData_IV, uint32_t *InData_Header,
        uint32_t Header_Len);
void HW_SCE_Aes128CcmEncryptUpdateSub(const uint32_t *InData_Text, uint32_t *OutData_Text, const uint32_t MAX_CNT);
fsp_err_t HW_SCE_Aes128CcmEncryptFinalSub(const uint32_t *InData_TextLen, const uint32_t *InData_Text, uint32_t *OutData_Text,
        uint32_t *OutData_MAC);
fsp_err_t HW_SCE_Aes128CcmDecryptInitSub(uint32_t *InData_KeyIndex, uint32_t *InData_IV, uint32_t *InData_Header,
        uint32_t Header_Len);
void HW_SCE_Aes128CcmDecryptUpdateSub(const uint32_t *InData_Text, uint32_t *OutData_Text, const uint32_t MAX_CNT);
fsp_err_t HW_SCE_Aes128CcmDecryptFinalSub(const uint32_t *InData_Text, const uint32_t *InData_TextLen, const uint32_t *InData_MAC,
        const uint32_t *InData_MACLength, uint32_t *OutData_Text);

fsp_err_t HW_SCE_Aes192CcmEncryptInitSub(uint32_t *InData_KeyIndex, uint32_t *InData_IV, uint32_t *InData_Header,
        uint32_t Header_Len);
void HW_SCE_Aes192CcmEncryptUpdateSub(const uint32_t *InData_Text, uint32_t *OutData_Text, const uint32_t MAX_CNT);
fsp_err_t HW_SCE_Aes192CcmEncryptFinalSub(const uint32_t *InData_Text, const uint32_t *InData_TextLen, uint32_t *OutData_Text,
        uint32_t *OutData_MAC);
fsp_err_t HW_SCE_Aes192CcmDecryptInitSub(uint32_t *InData_KeyIndex, uint32_t *InData_IV, uint32_t *InData_Header,
        uint32_t Header_Len);
void HW_SCE_Aes192CcmDecryptUpdateSub(const uint32_t *InData_Text, uint32_t *OutData_Text, const uint32_t MAX_CNT);
fsp_err_t HW_SCE_Aes192CcmDecryptFinalSub(const uint32_t *InData_Text, const uint32_t *InData_TextLen, const uint32_t *InData_MAC,
        const uint32_t *InData_MACLength, uint32_t *OutData_Text);

fsp_err_t HW_SCE_Aes256CcmEncryptInitSub(uint32_t *InData_KeyIndex, uint32_t *InData_IV, uint32_t *InData_Header,
        uint32_t Header_Len);
void HW_SCE_Aes256CcmEncryptUpdateSub(const uint32_t *InData_Text, uint32_t *OutData_Text, const uint32_t MAX_CNT);
fsp_err_t HW_SCE_Aes256CcmEncryptFinalSub(const uint32_t *InData_Text, const uint32_t *InData_TextLen, uint32_t *OutData_Text,
        uint32_t *OutData_MAC);
fsp_err_t HW_SCE_Aes256CcmDecryptInitSub(uint32_t *InData_KeyIndex, uint32_t *InData_IV, uint32_t *InData_Header,
        uint32_t Header_Len);
void HW_SCE_Aes256CcmDecryptUpdateSub(const uint32_t *InData_Text, uint32_t *OutData_Text, const uint32_t MAX_CNT);
fsp_err_t HW_SCE_Aes256CcmDecryptFinalSub(const uint32_t *InData_Text, const uint32_t *InData_TextLen, const uint32_t *InData_MAC,
        const uint32_t *InData_MACLength, uint32_t *OutData_Text);
fsp_err_t HW_SCE_Aes128CcmEncryptInitSubGeneral (uint32_t InData_KeyType[], uint32_t InData_DataType[],
        uint32_t InData_Cmd[], uint32_t InData_TextLen[], uint32_t InData_KeyIndex[], uint32_t InData_IV[],
        uint32_t InData_Header[], uint32_t InData_SeqNum[], uint32_t Header_Len);
fsp_err_t HW_SCE_Aes192CcmEncryptInitSubGeneral (uint32_t InData_KeyType[], uint32_t InData_DataType[],
        uint32_t InData_Cmd[],uint32_t InData_TextLen[], uint32_t InData_KeyIndex[],uint32_t InData_IV[],
        uint32_t InData_Header[], uint32_t InData_SeqNum[],uint32_t Header_Len);
fsp_err_t HW_SCE_Aes256CcmEncryptInitSubGeneral (uint32_t InData_KeyType[], uint32_t InData_DataType[],
        uint32_t InData_Cmd[],uint32_t InData_TextLen[], uint32_t InData_KeyIndex[],uint32_t InData_IV[],
        uint32_t InData_Header[], uint32_t InData_SeqNum[],uint32_t Header_Len);
fsp_err_t HW_SCE_Aes128CcmDecryptInitSubGeneral (uint32_t InData_KeyType[], uint32_t InData_DataType[],
        uint32_t InData_Cmd[], uint32_t InData_TextLen[], uint32_t InData_MACLength[], uint32_t InData_KeyIndex[],
        uint32_t InData_IV[], uint32_t InData_Header[], uint32_t InData_SeqNum[], uint32_t Header_Len);
fsp_err_t HW_SCE_Aes192CcmDecryptInitSubGeneral (uint32_t InData_KeyType[], uint32_t InData_DataType[],
        uint32_t InData_Cmd[], uint32_t InData_TextLen[], uint32_t InData_MACLength[], uint32_t InData_KeyIndex[],
        uint32_t InData_IV[], uint32_t InData_Header[], uint32_t InData_SeqNum[], uint32_t Header_Len);
fsp_err_t HW_SCE_Aes256CcmDecryptInitSubGeneral (uint32_t InData_KeyType[],uint32_t InData_DataType[],
        uint32_t InData_Cmd[],uint32_t InData_TextLen[],uint32_t InData_MACLength[],uint32_t InData_KeyIndex[],
        uint32_t InData_IV[],uint32_t InData_Header[],uint32_t InData_SeqNum[],uint32_t Header_Len);
fsp_err_t HW_SCE_Aes128CcmEncryptFinalSubGeneral (const uint32_t *InData_Text, const uint32_t *InData_TextLen,
        uint32_t *OutData_Text, uint32_t *OutData_MAC);
fsp_err_t HW_SCE_Aes128CcmDecryptFinalSubGeneral(const uint32_t *InData_Text, const uint32_t *InData_TextLen, 
        const uint32_t *InData_MAC, const uint32_t *InData_MACLength, uint32_t *OutData_Text);
fsp_err_t HW_SCE_Aes128GcmEncryptInitSubGeneral (uint32_t *InData_KeyType, uint32_t *InData_DataType, 
        uint32_t *InData_Cmd, uint32_t *InData_KeyIndex, uint32_t *InData_IV, uint32_t *InData_SeqNum);
fsp_err_t HW_SCE_Aes128GcmDecryptInitSubGeneral (uint32_t *InData_KeyType, uint32_t *InData_DataType, 
        uint32_t *InData_Cmd, uint32_t *InData_KeyIndex, uint32_t *InData_IV, uint32_t *InData_SeqNum);
fsp_err_t HW_SCE_Aes192GcmDecryptInitSubGeneral (uint32_t *InData_KeyType, uint32_t *InData_DataType,
        uint32_t *InData_Cmd, uint32_t *InData_KeyIndex, uint32_t *InData_IV, uint32_t *InData_SeqNum);
fsp_err_t HW_SCE_Aes192GcmEncryptInitSubGeneral (uint32_t *InData_KeyType, uint32_t *InData_DataType,
        uint32_t *InData_Cmd, uint32_t *InData_KeyIndex, uint32_t *InData_IV, uint32_t *InData_SeqNum);
fsp_err_t HW_SCE_Aes256GcmDecryptInitSubGeneral (uint32_t *InData_KeyType, uint32_t *InData_DataType,
        uint32_t *InData_Cmd, uint32_t *InData_KeyIndex, uint32_t *InData_IV, uint32_t *InData_SeqNum);
fsp_err_t HW_SCE_Aes256GcmEncryptInitSubGeneral (uint32_t *InData_KeyType, uint32_t *InData_DataType,
        uint32_t *InData_Cmd, uint32_t *InData_KeyIndex, uint32_t *InData_IV, uint32_t *InData_SeqNum);

fsp_err_t HW_SCE_Aes128CmacInitSub(uint32_t *InData_KeyIndex);
void         HW_SCE_Aes128CmacUpdateSub(uint32_t *InData_Text, uint32_t MAX_CNT);
fsp_err_t HW_SCE_Aes128CmacFinalSub(uint32_t *InData_Cmd, uint32_t *InData_Text, uint32_t *InData_DataT,
        uint32_t *InData_DataTLen, uint32_t *OutData_DataT);
fsp_err_t HW_SCE_Aes192CmacInitSub(uint32_t *InData_KeyIndex);
void         HW_SCE_Aes192CmacUpdateSub(uint32_t *InData_Text, uint32_t MAX_CNT);
fsp_err_t HW_SCE_Aes192CmacFinalSub(uint32_t *InData_Cmd, uint32_t *InData_Text, uint32_t *InData_DataT,
        uint32_t *InData_DataTLen, uint32_t *OutData_DataT);
fsp_err_t HW_SCE_Aes256CmacInitSub(uint32_t *InData_KeyIndex);
void         HW_SCE_Aes256CmacUpdateSub(uint32_t *InData_Text, uint32_t MAX_CNT);
fsp_err_t HW_SCE_Aes256CmacFinalSub(uint32_t *InData_Cmd, uint32_t *InData_Text, uint32_t *InData_DataT,
        uint32_t *InData_DataTLen, uint32_t *OutData_DataT);

fsp_err_t HW_SCE_Sha1GenerateMessageDigestSub(uint32_t *InData_SHA1InitVal, uint32_t *InData_PaddedMsg,
        uint32_t MAX_CNT, uint32_t *OutData_MsgDigest);
fsp_err_t HW_SCE_Sha224256GenerateMessageDigestSub(const uint32_t *InData_SHAInitVal, const uint32_t *InData_PaddedMsg,
        const uint32_t MAX_CNT, uint32_t *OutData_MsgDigest);
fsp_err_t HW_SCE_GhashSub (uint32_t *InData_HV, uint32_t *InData_IV, uint32_t *InData_Text, uint32_t *OutData_DataT, 
        uint32_t MAX_CNT);
fsp_err_t HW_SCE_Md5GenerateMessageDigestSub(uint32_t *InData_MD5InitVal, uint32_t *InData_PaddedMsg,
        uint32_t MAX_CNT, uint32_t *OutData_MsgDigest);

fsp_err_t HW_SCE_Sha1HmacInitSub(uint32_t *InData_KeyType, uint32_t *InData_KeyIndex, uint32_t LEN);
void         HW_SCE_Sha1HmacUpdateSub(uint32_t *InData_PaddedMsg, uint32_t MAX_CNT);
fsp_err_t HW_SCE_Sha1HmacFinalSub(uint32_t *InData_Cmd, uint32_t *InData_MAC, uint32_t *InData_length,
        uint32_t *OutData_MAC);
fsp_err_t HW_SCE_Sha256HmacInitSub(uint32_t *InData_KeyType, uint32_t *InData_KeyIndex, uint32_t LEN);
void         HW_SCE_Sha256HmacUpdateSub(uint32_t *InData_PaddedMsg, uint32_t MAX_CNT);
fsp_err_t HW_SCE_Sha256HmacFinalSub(uint32_t *InData_Cmd, uint32_t *InData_MAC, uint32_t *InData_length,
        uint32_t *OutData_MAC);

fsp_err_t HW_SCE_TdesEncryptDecryptInitSub(uint32_t *InData_Cmd, uint32_t *InData_KeyIndex, uint32_t *InData_IV);
void HW_SCE_TdesEncryptDecryptUpdateSub(uint32_t *InData_Text, uint32_t *OutData_Text, uint32_t MAX_CNT);
fsp_err_t HW_SCE_TdesEncryptDecryptFinalSub(void);

fsp_err_t HW_SCE_TlsRootCertificateVerificationSub(uint32_t *InData_Sel_PubKeyType, uint32_t *InData_Certificates,
        uint32_t *InData_CertificatesLength, uint32_t *InData_Signature, uint32_t *InData_CertificatesInfo,
        uint32_t length, uint32_t *OutData_PubKey);
fsp_err_t HW_SCE_TlsCertificateVerificationSub(uint32_t *InData_Sel_PubKeyType, uint32_t *InData_PubKey,
        uint32_t *InData_TBSCertificate, uint32_t *InData_TBSCertificateLength, uint32_t *InData_Signature,
        uint32_t *InData_TBSCertificateInfo, uint32_t length, uint32_t *OutData_PubKey);
fsp_err_t HW_SCE_TlsEncryptPreMasterSecretSub(uint32_t *InData_PubKey, uint32_t *InData_PreMasterSecret,
        uint32_t *OutData_PreMasterSecret);
fsp_err_t HW_SCE_TlsGeneratePreMasterSecretSub(uint32_t *OutData_PreMasterSecret);
fsp_err_t HW_SCE_TlsGenerateMasterSecretSub(uint32_t *InData_Sel_CipherSuite, uint32_t *InData_PreMasterSecret,
        uint32_t *InData_ClientRandom, uint32_t *InData_ServerRandom, uint32_t *OutData_MasterSecret);
fsp_err_t HW_SCE_TlsGenerateSessionKeySub(uint32_t *InData_Sel_CipherSuite, uint32_t *InData_MasterSecret,
        uint32_t *InData_ClientRandom, uint32_t *InData_ServerRandom, uint32_t *InData_NonceExplicit,
        uint32_t *OutData_ClientMACKeyOperationCode, uint32_t *OutData_ServerMACKeyOperationCode,
        uint32_t *OutData_ClientEncKeyOperationCode, uint32_t *OutData_ServerEncKeyOperationCode, uint32_t OutLen);
fsp_err_t HW_SCE_TlsGenerateVerifyDataSub(uint32_t *InData_Sel_VerifyData, uint32_t *InData_MasterSecret,
        uint32_t *InData_HandShakeHash, uint32_t *OutData_VerifyData);

fsp_err_t HW_SCE_TlsGeneratePreMasterSecretWithEccP256KeySub(uint32_t *InData_PubKey, uint32_t *InData_KeyIndex,
        uint32_t *OutData_PreMasterSecretIndex);
fsp_err_t HW_SCE_TlsServersEphemeralEcdhPublicKeyRetrievesSub(uint32_t *InData_Sel_PubKeyType,
        uint32_t *InData_ClientRandom, uint32_t *InData_ServerRandom, uint32_t *InData_Sel_CompressType,
        uint32_t *InData_SKE_Message, uint32_t *InData_SKE_Signature, uint32_t *InData_PubKey,
        uint32_t *OutData_EphemeralPubKey);

fsp_err_t HW_SCE_Rsa1024ModularExponentEncryptSub(const uint32_t *InData_KeyIndex, const uint32_t *InData_Text,
        uint32_t *OutData_Text);
fsp_err_t HW_SCE_Rsa1024ModularExponentDecryptSub(uint32_t *InData_KeyIndex, const uint32_t *InData_Text,
        uint32_t *OutData_Text);
fsp_err_t HW_SCE_Rsa2048ModularExponentEncryptSub(const uint32_t *InData_KeyIndex, const uint32_t *InData_Text,
        uint32_t *OutData_Text);
fsp_err_t HW_SCE_Rsa2048ModularExponentDecryptSub(uint32_t *InData_KeyIndex, const uint32_t *InData_Text,
        uint32_t *OutData_Text);
fsp_err_t HW_SCE_Rsa3072ModularExponentEncryptSub(const uint32_t *InData_KeyIndex, const uint32_t *InData_Text,
        uint32_t *OutData_Text);
fsp_err_t HW_SCE_Rsa3072ModularExponentDecryptSub(uint32_t *InData_KeyIndex, uint32_t *InData_Text,
        uint32_t *OutData_Text);
fsp_err_t HW_SCE_Rsa4096ModularExponentEncryptSub(const uint32_t *InData_KeyIndex, const uint32_t *InData_Text,
        uint32_t *OutData_Text);
fsp_err_t HW_SCE_Rsa4096ModularExponentDecryptSub(uint32_t *InData_KeyIndex, uint32_t *InData_Text,
        uint32_t *OutData_Text);

fsp_err_t HW_SCE_EcdsaSignatureGenerateSub(const uint32_t *InData_CurveType, const uint32_t *InData_Cmd, const uint32_t *InData_KeyIndex,
        const uint32_t *InData_MsgDgst, uint32_t *OutData_Signature);
fsp_err_t HW_SCE_EcdsaSignatureGenerateSubAdaptor(const uint32_t InData_CurveType[], const uint32_t InData_Cmd[], const uint32_t InData_KeyIndex[], 
        const uint32_t InData_MsgDgst[], const uint32_t InData_DomainParam[], uint32_t OutData_Signature[]);
fsp_err_t HW_SCE_EcdsaP384SignatureGenerateSub(const uint32_t *InData_CurveType, const uint32_t *InData_KeyIndex,
        const uint32_t *InData_MsgDgst, uint32_t *OutData_Signature);
fsp_err_t HW_SCE_EcdsaP384SignatureGenerateSubAdaptor(const uint32_t InData_CurveType[], const uint32_t InData_KeyIndex[], const uint32_t InData_MsgDgst[], 
        const uint32_t InData_DomainParam[], uint32_t OutData_Signature[]);
fsp_err_t HW_SCE_EcdsaSignatureVerificationSub(const uint32_t *InData_CurveType, const uint32_t *InData_Cmd, const uint32_t *InData_KeyIndex,
        const uint32_t *InData_MsgDgst, const uint32_t *InData_Signature);
fsp_err_t HW_SCE_EcdsaP384SignatureVerificationSub(const uint32_t *InData_CurveType, const uint32_t *InData_KeyIndex,
        const uint32_t *InData_MsgDgst, const uint32_t *InData_Signature);

fsp_err_t HW_SCE_DlmsCosemQeuSignatureVerificationSub(uint32_t *InData_Cmd, uint32_t *InData_KeyIndex,
        uint32_t *InData_data, uint32_t *InData_Signature, uint32_t *OutData_KeyIndex);
fsp_err_t HW_SCE_DlmsCosemQevSignatureGenerationSub(uint32_t *InData_Cmd, uint32_t *InData_KeyType,
        uint32_t *InData_PubKeyIndex, uint32_t *InData_PrivKeyIndex, uint32_t *InData_key_id, uint32_t *OutData_data,
        uint32_t *OutData_Signature, uint32_t *OutData_KeyIndex);
fsp_err_t HW_SCE_DlmsCosemCalculateZSub(uint32_t *InData_KeyType, uint32_t *InData_PubKeyIndex,
        uint32_t *InData_PrivKeyIndex, uint32_t *OutData_KeyIndex);
fsp_err_t HW_SCE_DlmsCosemCalculateKekSub(uint32_t *InData_KeyIndex, uint32_t *InData_PaddedMsg, uint32_t MAX_CNT,
        uint32_t *OutData_KeyIndex);
fsp_err_t HW_SCE_DlmsCosemKeyUnwrapSub(uint32_t *InData_KeyIndex, uint32_t *InData_Text, uint32_t *OutData_KeyIndex);

fsp_err_t HW_SCE_DlmsCosemP384QeuSignatureVerificationSub(uint32_t *InData_KeyIndex, uint32_t *InData_MsgDgst, uint32_t *InData_Signature, uint32_t *InData_QeU, uint32_t *OutData_KeyIndex);
fsp_err_t HW_SCE_DlmsCosemP384QevSignatureGenerationSub(uint32_t *InData_Cmd, uint32_t *InData_PrivKeyIndex, uint32_t *InData_key_id, uint32_t *InData_MsgDgst, uint32_t *OutData_data, uint32_t *OutData_Signature, uint32_t *OutData_KeyIndex);
fsp_err_t HW_SCE_DlmsCosemP384QevOutputSub(uint32_t *InData_KeyType, uint32_t *InData_PubKeyIndex, uint32_t *OutData_PubKey);
fsp_err_t HW_SCE_DlmsCosemP384CalculateZSub(uint32_t *InData_KeyType, uint32_t *InData_PubKeyIndex, uint32_t *InData_PrivKeyIndex, uint32_t *OutData_KeyIndex);
fsp_err_t HW_SCE_DlmsCosemP384CalculateKekSub(uint32_t *InData_KEK, uint32_t *OutData_KeyIndex);
fsp_err_t HW_SCE_DlmsCosemP384OutputZSub(uint32_t *InData_KeyIndex, uint32_t *InData_AlgorithmID, uint32_t *OutData_Z);
fsp_err_t HW_SCE_DlmsCosemP384KeyUnwrapSub(uint32_t *InData_KeyIndex, uint32_t *InData_Text, uint32_t *OutData_KeyIndex);

fsp_err_t HW_SCE_AESKeyWrapSub(uint32_t *InData_Cmd, uint32_t *InData_KeyIndex, uint32_t KEY_INDEX_SIZE, uint32_t
        *InData_WrappedKeyType, uint32_t *InData_WrappedKeyIndex, uint32_t WRAPPED_KEY_SIZE, uint32_t *OutData_Text);
fsp_err_t HW_SCE_AESKeyUnwrapSub(uint32_t *InData_Cmd, uint32_t *InData_KeyIndex, uint32_t KEY_INDEX_SIZE, uint32_t
        *InData_WrappedKeyType, uint32_t *InData_Text, uint32_t WRAPPED_KEY_SIZE, uint32_t *OutData_KeyIndex);

fsp_err_t HW_SCE_SelectStateTransitionCryptgraphicSub(void);

fsp_err_t HW_SCE_LoadHukSub(uint32_t *InData_LC, uint32_t *InData_KeyIndex);

fsp_err_t R_SCE_UpdateOemKeyIndexSub(uint32_t *InData_LC, uint32_t *InData_Cmd, uint32_t *InData_IV, uint32_t *InData_InstData, uint32_t *OutData_KeyIndex);

void HW_SCE_TlsRootCertificateVerificationSubSub(void);
void HW_SCE_TlsGenerateSubSub(void);

void HW_SCE_SelfCheck1SubSub(void);

void HW_SCE_func040(void);
void HW_SCE_func043(void);
void HW_SCE_func044(void);
void HW_SCE_func048(uint32_t* ARG1);
void HW_SCE_func049(uint32_t* ARG1);
void HW_SCE_func069(uint32_t* ARG1, uint32_t ARG2);
void HW_SCE_func100(uint32_t ARG1, uint32_t ARG2, uint32_t ARG3, uint32_t ARG4);
void HW_SCE_func101(uint32_t ARG1, uint32_t ARG2, uint32_t ARG3, uint32_t ARG4);
void HW_SCE_func102(uint32_t ARG1, uint32_t ARG2, uint32_t ARG3, uint32_t ARG4);
void HW_SCE_func103(void);
void HW_SCE_func205(void);
void HW_SCE_func206(void);
void HW_SCE_func207(void);

void firm_mac_read(uint32_t *InData_Program);

uint32_t change_endian_long(uint32_t data);

fsp_err_t HW_SCE_Aes128CmacInit(const uint32_t InData_KeyType[], const uint32_t InData_KeyIndex[]);
fsp_err_t HW_SCE_Aes192CmacInit(const uint32_t InData_KeyType[], const uint32_t InData_KeyIndex[]);
fsp_err_t HW_SCE_Aes256CmacInit(const uint32_t InData_KeyType[], const uint32_t InData_KeyIndex[]);
void HW_SCE_Aes128CmacUpdate(const uint32_t InData_Text[], const uint32_t MAX_CNT);
void HW_SCE_Aes192CmacUpdate(const uint32_t InData_Text[], const uint32_t MAX_CNT);
void HW_SCE_Aes256CmacUpdate(const uint32_t InData_Text[], const uint32_t MAX_CNT);
fsp_err_t HW_SCE_Aes128CmacFinal(const uint32_t InData_Cmd[],
                                 const uint32_t InData_Text[],
                                 const uint32_t InData_DataT[],
                                 const uint32_t InData_DataTLen[],
                                 uint32_t       OutData_DataT[]);
fsp_err_t HW_SCE_Aes192CmacFinal(const uint32_t InData_Cmd[],
                                 const uint32_t InData_Text[],
                                 const uint32_t InData_DataT[],
                                 const uint32_t InData_DataTLen[],
                                 uint32_t       OutData_DataT[]);
fsp_err_t HW_SCE_Aes256CmacFinal(const uint32_t InData_Cmd[],
                                 const uint32_t InData_Text[],
                                 const uint32_t InData_DataT[],
                                 const uint32_t InData_DataTLen[],
                                 uint32_t       OutData_DataT[]);
fsp_err_t HW_SCE_Aes128XtsEncryptInitSubGeneral (uint32_t InData_KeyMode[],
                                                 uint32_t InData_KeyIndex[],
                                                 uint32_t InData_Key[],
                                                 uint32_t InData_IV[]);
fsp_err_t HW_SCE_Aes128XtsDecryptInitSubGeneral (uint32_t InData_KeyMode[],
                                                 uint32_t InData_KeyIndex[],
                                                 uint32_t InData_Key[],
                                                 uint32_t InData_IV[]);
#endif /* HW_SCE_RA_PRIVATE_HEADER_FILE */
