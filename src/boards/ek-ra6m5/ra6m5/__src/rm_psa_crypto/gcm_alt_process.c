/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "common.h"

#if defined(MBEDTLS_GCM_C)

 #include "mbedtls/gcm.h"
 #include "mbedtls/platform_util.h"
 #include "mbedtls/error.h"

 #include <string.h>

 #if defined(MBEDTLS_AESNI_C)
  #include "mbedtls/aesni.h"
 #endif

 #if defined(MBEDTLS_SELF_TEST) && defined(MBEDTLS_AES_C)
  #include "mbedtls/aes.h"
  #include "mbedtls/platform.h"
  #if !defined(MBEDTLS_PLATFORM_C)
   #include <stdio.h>
   #define mbedtls_printf    printf
  #endif                               /* MBEDTLS_PLATFORM_C */
 #endif                                /* MBEDTLS_SELF_TEST && MBEDTLS_AES_C */

 #if defined(MBEDTLS_GCM_ALT)
  #include "hw_sce_private.h"
  #include "hw_sce_aes_private.h"
  #include "hw_sce_ra_private.h"
  #include "aes_alt.h"
  #include "platform_alt.h"

  #define SCE9_AES_GCM_KEY_TYPE_GENERAL    (0)

/* Prepare GCM IV for encryption/decryption
 * Ref: https://nvlpubs.nist.gov/nistpubs/Legacy/SP/nistspecialpublication800-38d.pdf
 * */
static fsp_err_t prepare_gcm_iv(uint8_t  * ivec,
                                uint32_t   ivec_len,
                                uint32_t * key_index,
                                uint32_t   key_index_word_size,
                                uint32_t * hashed_ivec);

static fsp_err_t prepare_gcm_iv (uint8_t  * ivec,
                                 uint32_t   ivec_len,
                                 uint32_t * key_index,
                                 uint32_t   key_index_word_size,
                                 uint32_t * hashed_ivec)
{
    uint32_t  hash_subkey[4]     = {0};
    uint32_t  hashed_ivec_tmp[4] = {0};
    uint32_t  zero[4]            = {0};
    uint32_t  ivec_length_rest   = 0;
    uint32_t  ivec_bit_len[4]    = {0};
    uint32_t  ivec_tmp[4]        = {0};
    fsp_err_t ret                = FSP_SUCCESS;
    uint32_t  dummy_iv[4]        = {0};
    uint32_t  indata_cmd         = change_endian_long(SCE_AES_IN_DATA_CMD_ECB_ENCRYPTION);
    uint32_t  indata_key_type    = 0;
    fsp_err_t err                = FSP_SUCCESS;

    /* when iv_len is 12 (96 bit), aad 0x00000001 padding */
    if (12U == ivec_len)
    {
        /* If len(IV) = 96 then, hashed_ivec = (IV|| 31 bit 0 padding|| 1) */
        memcpy(hashed_ivec, ivec, 12U);
        hashed_ivec[3] = change_endian_long(0x00000001U);
    }
    /* when iv_len is not 12 (96 bit), aad ghash padding */
    else
    {
        /* Encrypt 4 words (128 bit) zeros with the AES key. The generated cipher is the hash subkey used by GHASH HW API. */
        if (key_index_word_size == 0U)
        {
            err = HW_SCE_Aes128EncryptDecryptInitSubAdaptor(&indata_key_type, &indata_cmd, key_index, NULL, dummy_iv);

            if (err == FSP_SUCCESS)
            {
                HW_SCE_Aes128EncryptDecryptUpdateSub((uint32_t *) &zero[0],
                                                     (uint32_t *) &hash_subkey[0],
                                                     BYTES_TO_WORDS(MBEDTLS_MAX_BLOCK_LENGTH));
            }

            ret = HW_SCE_Aes128EncryptDecryptFinalSub();
        }

  #ifndef MBEDTLS_AES_ONLY_128_BIT_KEY_LENGTH
        else if (key_index_word_size == 1U)
        {
            err = HW_SCE_Aes192EncryptDecryptInitSubAdaptor(&indata_key_type, &indata_cmd, key_index, NULL, dummy_iv);

            if (err == FSP_SUCCESS)
            {
                HW_SCE_Aes192EncryptDecryptUpdateSub((uint32_t *) &zero[0],
                                                     (uint32_t *) &hash_subkey[0],
                                                     BYTES_TO_WORDS(MBEDTLS_MAX_BLOCK_LENGTH));
            }

            ret = HW_SCE_Aes192EncryptDecryptFinalSub();
        }
        else if (key_index_word_size == 2U)
        {
            err = HW_SCE_Aes256EncryptDecryptInitSubAdaptor(&indata_key_type, &indata_cmd, key_index, NULL, dummy_iv);

            if (err == FSP_SUCCESS)
            {
                HW_SCE_Aes256EncryptDecryptUpdateSub((uint32_t *) &zero[0],
                                                     (uint32_t *) &hash_subkey[0],
                                                     BYTES_TO_WORDS(MBEDTLS_MAX_BLOCK_LENGTH));
            }

            ret = HW_SCE_Aes256EncryptDecryptFinalSub();
        }
  #endif
        else
        {
            ret = FSP_ERR_UNSUPPORTED;
        }

        if (FSP_SUCCESS == ret)
        {
            if (MBEDTLS_MAX_BLOCK_LENGTH <= ivec_len)
            {
                /* Generate GHASH for all complete IV blocks within ivec_len */
                ret =
                    HW_SCE_GhashSub(hash_subkey, zero, (uint32_t *) ivec, hashed_ivec_tmp,
                                    (ivec_len / MBEDTLS_MAX_BLOCK_LENGTH) * BYTES_TO_WORDS(MBEDTLS_MAX_BLOCK_LENGTH));
                if (FSP_SUCCESS == ret)
                {
                    ivec_length_rest = ivec_len % MBEDTLS_MAX_BLOCK_LENGTH;

                    /* Generate GHASH for all remaining partial IV block. Pad with 0 to create complete block. */
                    if (0U != ivec_length_rest)
                    {
                        memcpy(ivec_tmp, ivec + (ivec_len - ivec_length_rest), ivec_length_rest);
                        ret =
                            HW_SCE_GhashSub(hash_subkey, hashed_ivec_tmp, ivec_tmp, hashed_ivec_tmp,
                                            BYTES_TO_WORDS(MBEDTLS_MAX_BLOCK_LENGTH));
                    }
                }
            }
            else
            {
                ret =
                    HW_SCE_GhashSub(hash_subkey, zero, (uint32_t *) ivec, hashed_ivec_tmp,
                                    BYTES_TO_WORDS(MBEDTLS_MAX_BLOCK_LENGTH));
            }

            /* Create 64bit IV length and perform GHASH using previously computed hashed_ivec_tmp */
            if (FSP_SUCCESS == ret)
            {
                /* calculate ivec bit length */
                ivec_bit_len[0] = 0U;
                ivec_bit_len[1] = 0U;

                /* Store carry in word 0 if the ivec_len is larger than 2^29 */
                ivec_bit_len[2] = change_endian_long(ivec_len >> 29U);
                ivec_bit_len[3] = change_endian_long(ivec_len << 3U);

                /* Compute GHASH(IV||0 padding||64bit IV length)*/
                ret =
                    HW_SCE_GhashSub(hash_subkey, hashed_ivec_tmp, ivec_bit_len, hashed_ivec,
                                    BYTES_TO_WORDS(MBEDTLS_MAX_BLOCK_LENGTH));
            }
        }
    }

    return ret;
}

/* AES-GCM Encryption/Decryption Init HW call table based on key size */
static const hw_sce_aes_gcm_crypt_init_t g_sce_aes_gcm_crypt_init[][2U] =
{
    [RM_PSA_CRYPTO_AES_LOOKUP_INDEX(SIZE_AES_128BIT_KEYLEN_BITS)][MBEDTLS_GCM_ENCRYPT] =
        HW_SCE_Aes128GcmEncryptInitSubGeneral,
    [RM_PSA_CRYPTO_AES_LOOKUP_INDEX(SIZE_AES_128BIT_KEYLEN_BITS)][MBEDTLS_GCM_DECRYPT] =
        HW_SCE_Aes128GcmDecryptInitSubGeneral,
  #ifndef MBEDTLS_AES_ONLY_128_BIT_KEY_LENGTH
    [RM_PSA_CRYPTO_AES_LOOKUP_INDEX(SIZE_AES_192BIT_KEYLEN_BITS)][MBEDTLS_GCM_ENCRYPT] =
        HW_SCE_Aes192GcmEncryptInitSubGeneral,
    [RM_PSA_CRYPTO_AES_LOOKUP_INDEX(SIZE_AES_192BIT_KEYLEN_BITS)][MBEDTLS_GCM_DECRYPT] =
        HW_SCE_Aes192GcmDecryptInitSubGeneral,
    [RM_PSA_CRYPTO_AES_LOOKUP_INDEX(SIZE_AES_256BIT_KEYLEN_BITS)][MBEDTLS_GCM_ENCRYPT] =
        HW_SCE_Aes256GcmEncryptInitSubGeneral,
    [RM_PSA_CRYPTO_AES_LOOKUP_INDEX(SIZE_AES_256BIT_KEYLEN_BITS)][MBEDTLS_GCM_DECRYPT] =
        HW_SCE_Aes256GcmDecryptInitSubGeneral,
  #endif
};

/* AES-GCM Encryption/Decryption Update AAD HW call table based on key size */
static const hw_sce_aes_gcm_update_aad_t g_sce_aes_gcm_update_aad[][2U] =
{
    [RM_PSA_CRYPTO_AES_LOOKUP_INDEX(SIZE_AES_128BIT_KEYLEN_BITS)][MBEDTLS_GCM_ENCRYPT] =
        HW_SCE_Aes128GcmEncryptUpdateAADSub,
    [RM_PSA_CRYPTO_AES_LOOKUP_INDEX(SIZE_AES_128BIT_KEYLEN_BITS)][MBEDTLS_GCM_DECRYPT] =
        HW_SCE_Aes128GcmDecryptUpdateAADSub,
  #ifndef MBEDTLS_AES_ONLY_128_BIT_KEY_LENGTH
    [RM_PSA_CRYPTO_AES_LOOKUP_INDEX(SIZE_AES_192BIT_KEYLEN_BITS)][MBEDTLS_GCM_ENCRYPT] =
        HW_SCE_Aes192GcmEncryptUpdateAADSub,
    [RM_PSA_CRYPTO_AES_LOOKUP_INDEX(SIZE_AES_192BIT_KEYLEN_BITS)][MBEDTLS_GCM_DECRYPT] =
        HW_SCE_Aes192GcmDecryptUpdateAADSub,
    [RM_PSA_CRYPTO_AES_LOOKUP_INDEX(SIZE_AES_256BIT_KEYLEN_BITS)][MBEDTLS_GCM_ENCRYPT] =
        HW_SCE_Aes256GcmEncryptUpdateAADSub,
    [RM_PSA_CRYPTO_AES_LOOKUP_INDEX(SIZE_AES_256BIT_KEYLEN_BITS)][MBEDTLS_GCM_DECRYPT] =
        HW_SCE_Aes256GcmDecryptUpdateAADSub,
  #endif
};

/* AES-GCM Encryption/Decryption Update Transition HW call table based on key size */
static const hw_sce_aes_gcm_crypt_update_transition_t g_sce_aes_gcm_crypt_update_transition[][2U] =
{
    [RM_PSA_CRYPTO_AES_LOOKUP_INDEX(SIZE_AES_128BIT_KEYLEN_BITS)][MBEDTLS_GCM_ENCRYPT] =
        HW_SCE_Aes128GcmEncryptUpdateTransitionSub,
    [RM_PSA_CRYPTO_AES_LOOKUP_INDEX(SIZE_AES_128BIT_KEYLEN_BITS)][MBEDTLS_GCM_DECRYPT] =
        HW_SCE_Aes128GcmDecryptUpdateTransitionSub,
  #ifndef MBEDTLS_AES_ONLY_128_BIT_KEY_LENGTH
    [RM_PSA_CRYPTO_AES_LOOKUP_INDEX(SIZE_AES_192BIT_KEYLEN_BITS)][MBEDTLS_GCM_ENCRYPT] =
        HW_SCE_Aes192GcmEncryptUpdateTransitionSub,
    [RM_PSA_CRYPTO_AES_LOOKUP_INDEX(SIZE_AES_192BIT_KEYLEN_BITS)][MBEDTLS_GCM_DECRYPT] =
        HW_SCE_Aes192GcmDecryptUpdateTransitionSub,
    [RM_PSA_CRYPTO_AES_LOOKUP_INDEX(SIZE_AES_256BIT_KEYLEN_BITS)][MBEDTLS_GCM_ENCRYPT] =
        HW_SCE_Aes256GcmEncryptUpdateTransitionSub,
    [RM_PSA_CRYPTO_AES_LOOKUP_INDEX(SIZE_AES_256BIT_KEYLEN_BITS)][MBEDTLS_GCM_DECRYPT] =
        HW_SCE_Aes256GcmDecryptUpdateTransitionSub,
  #endif
};

/* AES-GCM Encryption/Decryption Update HW call table based on key size */
static const hw_sce_aes_gcm_crypt_update_t g_sce_aes_gcm_crypt_update[][2U] =
{
    [RM_PSA_CRYPTO_AES_LOOKUP_INDEX(SIZE_AES_128BIT_KEYLEN_BITS)][MBEDTLS_GCM_ENCRYPT] =
        HW_SCE_Aes128GcmEncryptUpdateSub,
    [RM_PSA_CRYPTO_AES_LOOKUP_INDEX(SIZE_AES_128BIT_KEYLEN_BITS)][MBEDTLS_GCM_DECRYPT] =
        HW_SCE_Aes128GcmDecryptUpdateSub,
  #ifndef MBEDTLS_AES_ONLY_128_BIT_KEY_LENGTH
    [RM_PSA_CRYPTO_AES_LOOKUP_INDEX(SIZE_AES_192BIT_KEYLEN_BITS)][MBEDTLS_GCM_ENCRYPT] =
        HW_SCE_Aes192GcmEncryptUpdateSub,
    [RM_PSA_CRYPTO_AES_LOOKUP_INDEX(SIZE_AES_192BIT_KEYLEN_BITS)][MBEDTLS_GCM_DECRYPT] =
        HW_SCE_Aes192GcmDecryptUpdateSub,
    [RM_PSA_CRYPTO_AES_LOOKUP_INDEX(SIZE_AES_256BIT_KEYLEN_BITS)][MBEDTLS_GCM_ENCRYPT] =
        HW_SCE_Aes256GcmEncryptUpdateSub,
    [RM_PSA_CRYPTO_AES_LOOKUP_INDEX(SIZE_AES_256BIT_KEYLEN_BITS)][MBEDTLS_GCM_DECRYPT] =
        HW_SCE_Aes256GcmDecryptUpdateSub,
  #endif
};

/* AES-GCM Encryption Final HW call table based on key size */
static const hw_sce_aes_gcm_encrypt_final_t g_sce_aes_gcm_encrypt_final[] =
{
    [RM_PSA_CRYPTO_AES_LOOKUP_INDEX(SIZE_AES_128BIT_KEYLEN_BITS)] =
        HW_SCE_Aes128GcmEncryptFinalSub,
  #ifndef MBEDTLS_AES_ONLY_128_BIT_KEY_LENGTH
    [RM_PSA_CRYPTO_AES_LOOKUP_INDEX(SIZE_AES_192BIT_KEYLEN_BITS)] =
        HW_SCE_Aes192GcmEncryptFinalSub,
    [RM_PSA_CRYPTO_AES_LOOKUP_INDEX(SIZE_AES_256BIT_KEYLEN_BITS)] =
        HW_SCE_Aes256GcmEncryptFinalSub,
  #endif
};

/* AES-GCM Decryption Final HW call table based on key size */
static const hw_sce_aes_gcm_decrypt_final_t g_sce_aes_gcm_decrypt_final[] =
{
    [RM_PSA_CRYPTO_AES_LOOKUP_INDEX(SIZE_AES_128BIT_KEYLEN_BITS)] =
        HW_SCE_Aes128GcmDecryptFinalSub,
  #ifndef MBEDTLS_AES_ONLY_128_BIT_KEY_LENGTH
    [RM_PSA_CRYPTO_AES_LOOKUP_INDEX(SIZE_AES_192BIT_KEYLEN_BITS)] =
        HW_SCE_Aes192GcmDecryptFinalSub,
    [RM_PSA_CRYPTO_AES_LOOKUP_INDEX(SIZE_AES_256BIT_KEYLEN_BITS)] =
        HW_SCE_Aes256GcmDecryptFinalSub,
  #endif
};

/* AES-GCM operation using SCE9 HW procedures */
int sce_gcm_crypt_and_tag (mbedtls_gcm_context * ctx,
                           int                   mode,
                           size_t                length,
                           const unsigned char * iv,
                           size_t                iv_len,
                           const unsigned char * aad,
                           size_t                aad_len,
                           const unsigned char * input,
                           unsigned char       * output,
                           size_t                tag_len,
                           unsigned char       * tag)
{
    uint32_t              key_len_idx      = (uint32_t) RM_PSA_CRYPTO_AES_LOOKUP_INDEX(ctx->cipher_ctx.key_bitlen);
    mbedtls_aes_context * aes_ctx          = (mbedtls_aes_context *) ctx->cipher_ctx.cipher_ctx;
    fsp_err_t             err              = FSP_SUCCESS;
    uint32_t              aad_bit_size[2]  = {0};
    uint32_t              data_bit_size[2] = {0};
    uint32_t              hashed_ivec[4]   = {0};
    uint8_t               work_buffer[MBEDTLS_MAX_BLOCK_LENGTH] = {0};
    uint32_t              length_remaining = 0;
    uint32_t              input_length     = aad_len;
    uint32_t              key_type[1]      = {SCE9_AES_GCM_KEY_TYPE_GENERAL};
    uint8_t             * gcm_buffer;
    uint32_t              dummy_val[1] = {0};

    /* Get the hashed IV for AES-GCM operations */
    prepare_gcm_iv((uint8_t *) iv, iv_len, aes_ctx->buf, key_len_idx, hashed_ivec);

    /* Encryption/Decryption Init */
    err = g_sce_aes_gcm_crypt_init[key_len_idx][mode](key_type, dummy_val, dummy_val, (uint32_t *) (aes_ctx->buf),
                                                      (uint32_t *) hashed_ivec, dummy_val);
    if (FSP_SUCCESS == err)
    {
        length_remaining = aad_len % MBEDTLS_MAX_BLOCK_LENGTH;
        input_length    -= length_remaining;

        g_sce_aes_gcm_update_aad[key_len_idx][mode]((uint32_t *) aad, BYTES_TO_WORDS(input_length));

        if (length_remaining)
        {
            /* Pad the last inclomplte block of aad data with zeroes to create a complete block */
            memcpy(work_buffer, &aad[input_length], length_remaining);
            g_sce_aes_gcm_update_aad[key_len_idx][mode]((uint32_t *) work_buffer,
                                                        BYTES_TO_WORDS(MBEDTLS_MAX_BLOCK_LENGTH));
        }

        g_sce_aes_gcm_crypt_update_transition[key_len_idx][mode]();

        input_length     = length;
        length_remaining = length % MBEDTLS_MAX_BLOCK_LENGTH;
        input_length    -= length_remaining;

        if (input_length)
        {
            g_sce_aes_gcm_crypt_update[key_len_idx][mode]((uint32_t *) input, (uint32_t *) output,
                                                          BYTES_TO_WORDS(input_length));
        }

        if (length_remaining)
        {
            memset(work_buffer, 0, sizeof(work_buffer));

            /* Pad the last inclomplte block of plaintext/cipher data with zeroes to create a complete block */
            memcpy(work_buffer, &input[input_length], length_remaining);
            gcm_buffer = work_buffer;
        }
        else
        {
            gcm_buffer = (uint8_t *) input;
        }

        /* Set up bit sizes for AAD and plaintext/ciphertext */
        /* Store carry in word 0 if the aad_len is larger than 2^29 */
        aad_bit_size[0] = change_endian_long((aad_len & 0xe000000U) >> 29U);
        aad_bit_size[1] = change_endian_long(aad_len << 3U);

        /* Store carry in word 0 if the length is larger than 2^29 */
        data_bit_size[0] = change_endian_long((length & 0xe000000U) >> 29U);
        data_bit_size[1] = change_endian_long(length << 3U);
        if (mode == MBEDTLS_GCM_ENCRYPT)
        {
            err =
                g_sce_aes_gcm_encrypt_final[key_len_idx]((uint32_t *) gcm_buffer, data_bit_size, aad_bit_size,
                                                         (uint32_t *) &output[input_length], (uint32_t *) tag);
        }
        else
        {
            uint32_t tag_bit_size[1] = {0};
            uint32_t padded_tag[4]   = {0};
            tag_bit_size[0] = change_endian_long(tag_len);

            /* Zero pad the tag if tag length is less than 16 bytes */
            memcpy(padded_tag, tag, tag_len);
            err =
                g_sce_aes_gcm_decrypt_final[key_len_idx]((uint32_t *) gcm_buffer, data_bit_size,
                                                         aad_bit_size, (uint32_t *) padded_tag,
                                                         tag_bit_size, (uint32_t *) &output[input_length]);
        }
    }

    if (FSP_SUCCESS != err)
    {
        return MBEDTLS_ERR_PLATFORM_HW_ACCEL_FAILED;
    }
    else
    {
        return 0U;
    }
}

 #endif                                /* !MBEDTLS_GCM_ALT */

#endif                                 /* MBEDTLS_GCM_C */
