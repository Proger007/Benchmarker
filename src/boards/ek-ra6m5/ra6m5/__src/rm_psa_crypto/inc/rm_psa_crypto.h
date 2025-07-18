/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#ifndef RM_PSA_CRYPTO_H
 #define RM_PSA_CRYPTO_H

 #define PSA_KEY_TYPE_AES_WRAPPED                  (PSA_KEY_TYPE_VENDOR_FLAG | PSA_KEY_TYPE_AES)
 #define PSA_KEY_TYPE_RSA_KEY_PAIR_WRAPPED         (PSA_KEY_TYPE_VENDOR_FLAG | PSA_KEY_TYPE_RSA_KEY_PAIR)
 #define PSA_KEY_TYPE_ECC_KEY_PAIR_BASE_WRAPPED    (PSA_KEY_TYPE_VENDOR_FLAG | PSA_KEY_TYPE_ECC_KEY_PAIR_BASE)

/** Elliptic curve key pair.
 *
 * \param curve     A value that identifies the  ECC curve to be used.
 */
 #define PSA_KEY_TYPE_ECC_KEY_PAIR_WRAPPED(curve)      (PSA_KEY_TYPE_ECC_KEY_PAIR_BASE_WRAPPED | (curve))

/** Whether a key type is a wrapped RSA key pair. */
 #define PSA_KEY_TYPE_IS_RSA_KEY_PAIR_WRAPPED(type)    (type == (PSA_KEY_TYPE_RSA_KEY_PAIR | PSA_KEY_TYPE_VENDOR_FLAG))

/** Whether a key type is wrapped elliptic curve key pair. */
 #define PSA_KEY_TYPE_IS_ECC_KEY_PAIR_WRAPPED(type)    (((type) & ~PSA_KEY_TYPE_ECC_CURVE_MASK) == \
                                                        PSA_KEY_TYPE_ECC_KEY_PAIR_BASE_WRAPPED)

 #if defined(MBEDTLS_PLATFORM_SETUP_TEARDOWN_ALT)

  #include <string.h>
  #include "bsp_api.h"
  #include "hw_sce_private.h"
  #include "hw_sce_trng_private.h"

// Define the maximum number of attempts by the TRNG to generate dissimilar data
  #define RM_PSA_CRYPTO_TRNG_MAX_ATTEMPTS    2

/*******************************************************************************************************************/ /**
 * @addtogroup RM_PSA_CRYPTO
 * @{
 **********************************************************************************************************************/
fsp_err_t RM_PSA_CRYPTO_TRNG_Read(uint8_t * const p_rngbuf, uint32_t num_req_bytes, uint32_t * p_num_gen_bytes);

  #ifdef __cplusplus
extern "C"
{
  #endif

  #ifdef __cplusplus
}
  #endif
 #endif                                /* MBEDTLS_PLATFORM_SETUP_TEARDOWN_ALT */

/*
 * The MBEDTLS_PLATFORM_SETBUF_MACRO was introduced in mbedTLS 3.2.1 to prevent stdio read/write functions from buffering stream data to reduce the likelihood of key leakage by setting the buffer argument in setbuf() to NULL.
 * The dummy_setbuf function below was created to prevent build errors; since FSP uses LittleFS by default (where the usage of a buffer is mandatory) this function does not perform any action. Setting the cache since in LittleFS to the minimum supported by the Data Flash (4) can minimize but not remove the likelihood of key data leakage.
 * The dummy function can be replaced by defining a different value for MBEDTLS_PLATFORM_SETBUF_MACRO value in the FSP configurator.
 */
 #if defined(MBEDTLS_PLATFORM_SETBUF_MACRO)
void dummy_setbuf(void * stream, char * buf);

 #endif                                /* MBEDTLS_PLATFORM_SETBUF_MACRO */

/*******************************************************************************************************************/ /**
 * @} (end addtogroup PSA_CRYPTO)
 **********************************************************************************************************************/
#endif                                 /* RM_PSA_CRYPTO_H */
