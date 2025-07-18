/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

/*
 * NOTE: This file is not a modification of ecdsa.c; it contains SCE specific implementations for sign and verify only.
 * There is no need to update this file when mbedtls versions are updated.
 */
#include "common.h"

#if defined(MBEDTLS_ECDSA_C)

 #include "mbedtls/ecdsa.h"
 #include "mbedtls/asn1write.h"

 #include <string.h>
 #include <stdbool.h>

 #if defined(MBEDTLS_ECDSA_DETERMINISTIC)
  #include "mbedtls/hmac_drbg.h"
 #endif

 #include "mbedtls/platform.h"

 #include "mbedtls/platform_util.h"
 #include "mbedtls/error.h"
 #include "psa/crypto.h"
 #include "hw_sce_private.h"

uint32_t ecp_load_key_size(bool wrapped_mode_ctx, mbedtls_ecp_group * grp);

 #if (defined(MBEDTLS_ECDSA_SIGN_ALT) || defined(MBEDTLS_ECDSA_VERIFY_ALT) || defined(MBEDTLS_ECP_ALT))

  #include "hw_sce_ecc_private.h"

static void ecp_mpi_load(mbedtls_mpi * X, const mbedtls_mpi_uint * p, size_t len) __attribute__((unused));
int         ecp_load_parameters_sce(const mbedtls_ecp_group * grp, uint8_t * p_curve_params_buff);
int         ecp_can_do_sce(mbedtls_ecp_group_id gid);
int         ecp_load_curve_attributes_sce(const mbedtls_ecp_group * grp,
                                          uint32_t                * p_curve_type,
                                          uint32_t                * p_cmd,
                                          sce_oem_cmd_t           * oem_priv_cmd,
                                          uint32_t               ** pp_domain_param);

static const hw_sce_ecc_generatesign_t g_ecdsa_generate_sign_lookup[][2] =
{
  #if defined(MBEDTLS_ECP_DP_SECP256R1_ENABLED) || defined(MBEDTLS_ECP_DP_SECP256K1_ENABLED) || \
    defined(MBEDTLS_ECP_DP_BP256R1_ENABLED)
   #if PSA_CRYPTO_IS_PLAINTEXT_SUPPORT_REQUIRED(PSA_CRYPTO_CFG_ECC_FORMAT)
    [RM_PSA_CRYPTO_ECP_LOOKUP_INDEX(ECC_256_PRIVATE_KEY_LENGTH_BITS)][RM_PSA_CRYPTO_ECC_KEY_PLAINTEXT] =
        HW_SCE_ECC_256GenerateSign,
   #endif
   #if PSA_CRYPTO_IS_WRAPPED_SUPPORT_REQUIRED(PSA_CRYPTO_CFG_ECC_FORMAT)
    [RM_PSA_CRYPTO_ECP_LOOKUP_INDEX(ECC_256_PRIVATE_KEY_LENGTH_BITS)][RM_PSA_CRYPTO_ECC_KEY_WRAPPED] =
        HW_SCE_ECC_256HrkGenerateSign,
   #endif
  #endif
  #if defined(MBEDTLS_ECP_DP_SECP384R1_ENABLED) || defined(MBEDTLS_ECP_DP_BP384R1_ENABLED)
   #if PSA_CRYPTO_IS_PLAINTEXT_SUPPORT_REQUIRED(PSA_CRYPTO_CFG_ECC_FORMAT)
    [RM_PSA_CRYPTO_ECP_LOOKUP_INDEX(ECC_384_PRIVATE_KEY_LENGTH_BITS)][RM_PSA_CRYPTO_ECC_KEY_PLAINTEXT] =
        HW_SCE_ECC_384GenerateSign,
   #endif
   #if PSA_CRYPTO_IS_WRAPPED_SUPPORT_REQUIRED(PSA_CRYPTO_CFG_ECC_FORMAT)
    [RM_PSA_CRYPTO_ECP_LOOKUP_INDEX(ECC_384_PRIVATE_KEY_LENGTH_BITS)][RM_PSA_CRYPTO_ECC_KEY_WRAPPED] =
        HW_SCE_ECC_384HrkGenerateSign,
   #endif
  #endif
  #if defined(MBEDTLS_ECP_DP_SECP521R1_ENABLED)
   #if PSA_CRYPTO_IS_PLAINTEXT_SUPPORT_REQUIRED(PSA_CRYPTO_CFG_ECC_FORMAT)
    [RM_PSA_CRYPTO_ECP_LOOKUP_INDEX(ECC_521_PRIVATE_KEY_LENGTH_BITS)][RM_PSA_CRYPTO_ECC_KEY_PLAINTEXT] =
        HW_SCE_ECC_521GenerateSign,
   #endif
   #if PSA_CRYPTO_IS_WRAPPED_SUPPORT_REQUIRED(PSA_CRYPTO_CFG_ECC_FORMAT)
    [RM_PSA_CRYPTO_ECP_LOOKUP_INDEX(ECC_521_PRIVATE_KEY_LENGTH_BITS)][RM_PSA_CRYPTO_ECC_KEY_WRAPPED] =
        HW_SCE_ECC_521HrkGenerateSign,
   #endif
  #endif
};

static const hw_sce_ecc_generatesign_t g_ed_ecdsa_generate_sign_lookup[][2] =
{
  #if defined(MBEDTLS_ECP_DP_CURVE25519_ENABLED)
   #if PSA_CRYPTO_IS_PLAINTEXT_SUPPORT_REQUIRED(PSA_CRYPTO_CFG_ECC_FORMAT)
    [RM_PSA_CRYPTO_ECP_LOOKUP_INDEX(ECC_25519_PRIVATE_KEY_LENGTH_BITS)][RM_PSA_CRYPTO_ECC_KEY_PLAINTEXT] =
        HW_SCE_ECC_255GenerateSign,
    [RM_PSA_CRYPTO_ECP_LOOKUP_INDEX((ECC_25519_PRIVATE_KEY_LENGTH_BITS - 1))][RM_PSA_CRYPTO_ECC_KEY_PLAINTEXT] =
        HW_SCE_ECC_255GenerateSign,
   #endif
   #if PSA_CRYPTO_IS_WRAPPED_SUPPORT_REQUIRED(PSA_CRYPTO_CFG_ECC_FORMAT)
    [RM_PSA_CRYPTO_ECP_LOOKUP_INDEX(ECC_25519_PRIVATE_KEY_LENGTH_BITS)][RM_PSA_CRYPTO_ECC_KEY_WRAPPED] =
        HW_SCE_ECC_255HrkGenerateSign,
    [RM_PSA_CRYPTO_ECP_LOOKUP_INDEX((ECC_25519_PRIVATE_KEY_LENGTH_BITS - 1))][RM_PSA_CRYPTO_ECC_KEY_WRAPPED] =
        HW_SCE_ECC_255HrkGenerateSign,
   #endif
  #endif
};

static const hw_sce_ecc_verifysign_t g_ecdsa_verify_sign_lookup[] =
{
  #if defined(MBEDTLS_ECP_DP_SECP256R1_ENABLED) || defined(MBEDTLS_ECP_DP_SECP256K1_ENABLED) || \
    defined(MBEDTLS_ECP_DP_BP256R1_ENABLED)
    [RM_PSA_CRYPTO_ECP_LOOKUP_INDEX(ECC_256_PRIVATE_KEY_LENGTH_BITS)] = HW_SCE_ECC_256VerifySign,
  #endif
  #if defined(MBEDTLS_ECP_DP_SECP384R1_ENABLED) || defined(MBEDTLS_ECP_DP_BP384R1_ENABLED)
    [RM_PSA_CRYPTO_ECP_LOOKUP_INDEX(ECC_384_PRIVATE_KEY_LENGTH_BITS)] = HW_SCE_ECC_384VerifySign,
  #endif
  #if defined(MBEDTLS_ECP_DP_SECP521R1_ENABLED)
    [RM_PSA_CRYPTO_ECP_LOOKUP_INDEX(ECC_521_PRIVATE_KEY_LENGTH_BITS)] = HW_SCE_ECC_521VerifySign,
  #endif
};

/*
 * Conversion macros for embedded constants:
 * build lists of mbedtls_mpi_uint's from lists of unsigned char's grouped by 8, 4 or 2
 */
  #if defined(MBEDTLS_HAVE_INT32)

   #define BYTES_TO_T_UINT_4(a, b, c, d) \
    ((mbedtls_mpi_uint) (a) << 0) |      \
    ((mbedtls_mpi_uint) (b) << 8) |      \
    ((mbedtls_mpi_uint) (c) << 16) |     \
    ((mbedtls_mpi_uint) (d) << 24)

   #define BYTES_TO_T_UINT_2(a, b) \
    BYTES_TO_T_UINT_4(a, b, 0, 0)

   #define BYTES_TO_T_UINT_8(a, b, c, d, e, f, g, h) \
    BYTES_TO_T_UINT_4(a, b, c, d),                   \
    BYTES_TO_T_UINT_4(e, f, g, h)

  #else                                /* 64-bits */

   #define BYTES_TO_T_UINT_8(a, b, c, d, e, f, g, h) \
    ((mbedtls_mpi_uint) (a) << 0) |                  \
    ((mbedtls_mpi_uint) (b) << 8) |                  \
    ((mbedtls_mpi_uint) (c) << 16) |                 \
    ((mbedtls_mpi_uint) (d) << 24) |                 \
    ((mbedtls_mpi_uint) (e) << 32) |                 \
    ((mbedtls_mpi_uint) (f) << 40) |                 \
    ((mbedtls_mpi_uint) (g) << 48) |                 \
    ((mbedtls_mpi_uint) (h) << 56)

   #define BYTES_TO_T_UINT_4(a, b, c, d) \
    BYTES_TO_T_UINT_8(a, b, c, d, 0, 0, 0, 0)

   #define BYTES_TO_T_UINT_2(a, b) \
    BYTES_TO_T_UINT_8(a, b, 0, 0, 0, 0, 0, 0)

  #endif                               /* bits in mbedtls_mpi_uint */

  #ifdef MBEDTLS_ECP_DP_SECP256R1_ENABLED

/* secp256r1 A value */
static const mbedtls_mpi_uint secp256r1_a[] =
{
    BYTES_TO_T_UINT_8(0xFC, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF),
    BYTES_TO_T_UINT_8(0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00),
    BYTES_TO_T_UINT_8(0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00),
    BYTES_TO_T_UINT_8(0x01, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF),
};
  #endif

  #ifdef MBEDTLS_ECP_DP_SECP384R1_ENABLED

/* secp384r1 A value */
static const mbedtls_mpi_uint secp384r1_a[] =
{
    BYTES_TO_T_UINT_8(0xFC, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00),
    BYTES_TO_T_UINT_8(0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF),
    BYTES_TO_T_UINT_8(0xFE, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF),
    BYTES_TO_T_UINT_8(0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF),
    BYTES_TO_T_UINT_8(0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF),
    BYTES_TO_T_UINT_8(0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF),
};
  #endif

  #ifdef MBEDTLS_ECP_DP_SECP521R1_ENABLED

/* secp384r1 A value */
static const mbedtls_mpi_uint secp521r1_a[] =
{
    BYTES_TO_T_UINT_8(0xFC, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF),
    BYTES_TO_T_UINT_8(0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF),
    BYTES_TO_T_UINT_8(0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF),
    BYTES_TO_T_UINT_8(0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF),
    BYTES_TO_T_UINT_8(0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF),
    BYTES_TO_T_UINT_8(0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF),
    BYTES_TO_T_UINT_8(0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF),
    BYTES_TO_T_UINT_8(0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF),
    BYTES_TO_T_UINT_8(0xFF, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00),
};
  #endif

static mbedtls_mpi         local_mpi_a;
static mbedtls_mpi const * p_mpi_a;

  #define LOAD_GROUP_A_ONLY(G)    ecp_mpi_load(&local_mpi_a, G ## _a, sizeof(G ## _a))

/*
 * Create an MPI from embedded constants
 * (assumes len is an exact multiple of sizeof mbedtls_mpi_uint)
 */
static void ecp_mpi_load (mbedtls_mpi * X, const mbedtls_mpi_uint * p, size_t len)
{
    X->s = 1;
    X->n = len / sizeof(mbedtls_mpi_uint);
    X->p = (mbedtls_mpi_uint *) p;
}

static int ecp_group_load_a_only (mbedtls_ecp_group_id gid)
{
    switch (gid)
    {
  #ifdef MBEDTLS_ECP_DP_SECP256R1_ENABLED
        case MBEDTLS_ECP_DP_SECP256R1:
        {
            LOAD_GROUP_A_ONLY(secp256r1);

            return 1;
        }
  #endif
  #ifdef MBEDTLS_ECP_DP_BP256R1_ENABLED
        case MBEDTLS_ECP_DP_BP256R1:
        {
            LOAD_GROUP_A_ONLY(secp256r1);

            return 1;
        }
  #endif
  #ifdef MBEDTLS_ECP_DP_SECP384R1_ENABLED
        case MBEDTLS_ECP_DP_SECP384R1:
        {
            LOAD_GROUP_A_ONLY(secp384r1);

            return 1;
        }
  #endif
  #ifdef MBEDTLS_ECP_DP_BP384R1_ENABLED
        case MBEDTLS_ECP_DP_BP384R1:
        {
            LOAD_GROUP_A_ONLY(secp384r1);

            return 1;
        }
  #endif
  #ifdef MBEDTLS_ECP_DP_SECP521R1_ENABLED
        case MBEDTLS_ECP_DP_SECP521R1:
        {
            LOAD_GROUP_A_ONLY(secp521r1);

            return 1;
        }
  #endif
        default:

            return 0;
    }
}

/* This function will load the curve parameters in the format expected by the hardware
 * p_curve_params_buff: pointer to zeroised memory to store reoriented curve parameters */
int ecp_load_parameters_sce (const mbedtls_ecp_group * grp, uint8_t * p_curve_params_buff)
{
    size_t curve_bytes = PSA_BITS_TO_BYTES(grp->pbits);
    int    ret         = 0;

    /* ARM do not define the A field (set to NULL) for R1 curves because they calculate portions of it on the fly to optimize their math.
     * But the SCE requires the "a" field passed to it.
     * Load the locally defined A field mpi to use for signing/verify
     */
    if (grp->A.p == NULL)
    {
        if (!ecp_group_load_a_only(grp->id))
        {
            return MBEDTLS_ERR_ECP_BAD_INPUT_DATA;
        }

        p_mpi_a = &local_mpi_a;
    }
    else
    {
        p_mpi_a = &grp->A;
    }

    /* The arrays for a, b, p, n, Gx, Gy will be added in that order after reversing each individually. p, n, Gx, Gy fields are of size curve_bytes = PSA_BITS_TO_BYTES( ecp->grp.pbits )
     * For "a" and "b", ARM has provided different sized values depending on the curve even though the sizes are same just that the undefined values are all 0s.
     * The provided memory is assumed to be zeroised. */

    if (0 !=
        mbedtls_mpi_write_binary(p_mpi_a,
                                 (p_curve_params_buff + (curve_bytes - (sizeof(mbedtls_mpi_uint) * p_mpi_a->n))),
                                 (sizeof(mbedtls_mpi_uint) * p_mpi_a->n)))
    {
        ret = MBEDTLS_ERR_MPI_BUFFER_TOO_SMALL;
    }
    else if (0 !=
             mbedtls_mpi_write_binary(&grp->B,
                                      (p_curve_params_buff +
                                       ((curve_bytes * 2) - (sizeof(mbedtls_mpi_uint) * grp->B.n))),
                                      (sizeof(mbedtls_mpi_uint) * grp->B.n)))
    {
        ret = MBEDTLS_ERR_MPI_BUFFER_TOO_SMALL;
    }
    else if (0 != mbedtls_mpi_write_binary(&grp->P, (p_curve_params_buff + (curve_bytes * 2)), curve_bytes))
    {
        ret = MBEDTLS_ERR_MPI_BUFFER_TOO_SMALL;
    }
    else if (0 != mbedtls_mpi_write_binary(&grp->N, (p_curve_params_buff + (curve_bytes * 3)), curve_bytes))
    {
        ret = MBEDTLS_ERR_MPI_BUFFER_TOO_SMALL;
    }
    else if (0 != mbedtls_mpi_write_binary(&grp->G.X, (p_curve_params_buff + (curve_bytes * 4)), curve_bytes))
    {
        ret = MBEDTLS_ERR_MPI_BUFFER_TOO_SMALL;
    }
    else if (0 != mbedtls_mpi_write_binary(&grp->G.Y, (p_curve_params_buff + (curve_bytes * 5)), curve_bytes))
    {
        ret = MBEDTLS_ERR_MPI_BUFFER_TOO_SMALL;
    }
    else
    {
        ret = 0;
    }

    return ret;
}

int ecp_can_do_sce (mbedtls_ecp_group_id gid)
{
    switch (gid)
    {
  #ifdef MBEDTLS_ECP_DP_SECP256R1_ENABLED
        case MBEDTLS_ECP_DP_SECP256R1:
        {
            return 1;
        }
  #endif
  #ifdef MBEDTLS_ECP_DP_SECP256K1_ENABLED
        case MBEDTLS_ECP_DP_SECP256K1:
        {
            return 1;
        }
  #endif
  #ifdef MBEDTLS_ECP_DP_BP256R1_ENABLED
        case MBEDTLS_ECP_DP_BP256R1:
        {
            return 1;
        }
  #endif
  #ifdef MBEDTLS_ECP_DP_SECP384R1_ENABLED
        case MBEDTLS_ECP_DP_SECP384R1:
        {
            return 1;
        }
  #endif
  #ifdef MBEDTLS_ECP_DP_BP384R1_ENABLED
        case MBEDTLS_ECP_DP_BP384R1:
        {
            return 1;
        }
  #endif
  #if BSP_FEATURE_RSIP_RSIP_E51A_SUPPORTED || BSP_FEATURE_RSIP_RSIP_E50D_SUPPORTED
   #ifdef MBEDTLS_ECP_DP_SECP521R1_ENABLED
        case MBEDTLS_ECP_DP_SECP521R1:
        {
            return 1;
        }
   #endif
   #ifdef MBEDTLS_ECP_DP_CURVE25519_ENABLED
        case MBEDTLS_ECP_DP_CURVE25519:
        {
            return 1;
        }
   #endif
  #endif
        default:

            return 0;
    }
}

int ecp_load_curve_attributes_sce (const mbedtls_ecp_group * grp,
                                   uint32_t                * p_curve_type,
                                   uint32_t                * p_cmd,
                                   sce_oem_cmd_t           * oem_priv_cmd,
                                   uint32_t               ** pp_domain_param)
{
    int           ret              = 0;
    sce_oem_cmd_t priv_key_command = SCE_OEM_CMD_NUM;
    switch (grp->id)
    {
        case MBEDTLS_ECP_DP_SECP256R1:
        {
            *p_curve_type    = SCE_ECC_CURVE_TYPE_NIST;
            *p_cmd           = 0x0;
            priv_key_command = SCE_OEM_CMD_ECC_P256_PRIVATE;
            *pp_domain_param = (uint32_t *) &DomainParam_NIST_P256[0];
            break;
        }

        case MBEDTLS_ECP_DP_SECP384R1:
        {
            *p_curve_type    = SCE_ECC_CURVE_TYPE_NIST;
            *p_cmd           = 0x0;
            priv_key_command = SCE_OEM_CMD_ECC_P384_PRIVATE;
            *pp_domain_param = (uint32_t *) &DomainParam_NIST_P384[0];
            break;
        }

  #if BSP_FEATURE_RSIP_RSIP_E51A_SUPPORTED || BSP_FEATURE_RSIP_RSIP_E50D_SUPPORTED
        case MBEDTLS_ECP_DP_SECP521R1:
        {
            *p_curve_type    = SCE_ECC_CURVE_TYPE_NIST;
            *p_cmd           = 0x0;
            priv_key_command = SCE_OEM_CMD_ECC_P521_PRIVATE;
            *pp_domain_param = (uint32_t *) &DomainParam_NIST_P521[0];
            break;
        }

        case MBEDTLS_ECP_DP_CURVE25519:
        {
            *p_curve_type    = SCE_ECC_CURVE_TYPE_NIST;
            *p_cmd           = 0x0;
            priv_key_command = SCE_OEM_CMD_ED25519_PRIVATE;
            *pp_domain_param = (uint32_t *) &DomainParam_NIST_Ed25519[0];
            break;
        }
  #endif

        case MBEDTLS_ECP_DP_SECP256K1:
        {
            *p_curve_type    = SCE_ECC_CURVE_TYPE_KOBLITZ;
            *p_cmd           = 0x0;
            priv_key_command = SCE_OEM_CMD_ECC_SECP256K1_PRIVATE;
            *pp_domain_param = (uint32_t *) &DomainParam_Koblitz_secp256k1[0];
            break;
        }

        case MBEDTLS_ECP_DP_BP256R1:
        {
            *p_curve_type    = SCE_ECC_CURVE_TYPE_BRAINPOOL;
            *p_cmd           = 0x0;
            priv_key_command = SCE_OEM_CMD_ECC_P256R1_PRIVATE;
            *pp_domain_param = (uint32_t *) &DomainParam_Brainpool_256r1[0];
            break;
        }

        case MBEDTLS_ECP_DP_BP384R1:
        {
            *p_curve_type    = SCE_ECC_CURVE_TYPE_BRAINPOOL;
            *p_cmd           = 0x0;
            priv_key_command = SCE_OEM_CMD_ECC_P384R1_PRIVATE;
            *pp_domain_param = (uint32_t *) &DomainParam_Brainpool_384r1[0];
            break;
        }

        default:
        {
            ret = -1;
        }
    }

    if (NULL != oem_priv_cmd)
    {
        *oem_priv_cmd = priv_key_command;
    }

    return ret;
}

 #endif                                // (defined(MBEDTLS_ECDSA_SIGN_ALT) || defined(MBEDTLS_ECDSA_VERIFY_ALT) || defined(MBEDTLS_ECP_ALT))

 #if defined(MBEDTLS_ECDSA_SIGN_ALT)

/*
 * Compute ECDSA signature of a hashed message
 */
int mbedtls_ecdsa_sign (mbedtls_ecp_group * grp,
                        mbedtls_mpi * r,
                        mbedtls_mpi * s,
                        const mbedtls_mpi * d,
                        const unsigned char * buf,
                        size_t blen,
                        int (* f_rng)(void *, unsigned char *, size_t),
                        void * p_rng)
{
    (void) blen;
    (void) f_rng;
    (void) p_rng;

    int ret = 0;
    hw_sce_ecc_generatesign_t p_hw_sce_ecc_generatesign = NULL;

    uint32_t * p_private_key_buff_32;
    uint32_t * p_signature_buff_32;
    uint32_t * p_common_buff_32;
    uint32_t   private_key_size_words = 0;
    size_t     curve_bytes            = PSA_BITS_TO_BYTES(grp->pbits);
    size_t     temp_curve_bytes       = curve_bytes;
    uint8_t  * p_buf_8;

    /* Fail cleanly on curves that HW doesn't support */
    if (!ecp_can_do_sce(grp->id) || (grp->N.p == NULL))
    {
        return MBEDTLS_ERR_ECP_FEATURE_UNAVAILABLE;
    }

    if (MBEDTLS_ECP_DP_CURVE25519 == grp->id)
    {
        p_hw_sce_ecc_generatesign =
            g_ed_ecdsa_generate_sign_lookup[RM_PSA_CRYPTO_ECP_LOOKUP_INDEX(grp->pbits)][(bool) grp->vendor_ctx];
    }
    else
    {
        p_hw_sce_ecc_generatesign =
            g_ecdsa_generate_sign_lookup[RM_PSA_CRYPTO_ECP_LOOKUP_INDEX(grp->pbits)][(bool) grp->vendor_ctx];
    }

    if (NULL == p_hw_sce_ecc_generatesign)
    {
        return MBEDTLS_ERR_PLATFORM_FEATURE_UNSUPPORTED;
    }

    private_key_size_words = ecp_load_key_size((bool) grp->vendor_ctx, grp);
    if (0 == private_key_size_words)
    {
        return MBEDTLS_ERR_ECP_FEATURE_UNAVAILABLE;
    }

    /* Obtain a common 32-bit aligned buffer. It will be used for all the following items in this order:
     * Private Key (D) of size private_key_size_words
     * Signature (rs) of size curve_bytes * 2
     * Padded/truncated 32-bit aligned copy of input hash of size curve_bytes */
    p_common_buff_32 = mbedtls_calloc((curve_bytes * 3) + (private_key_size_words * 4), sizeof(uint8_t));

    if (NULL == p_common_buff_32)
    {
        return MBEDTLS_ERR_ECP_ALLOC_FAILED;
    }

    p_private_key_buff_32 = p_common_buff_32;
    p_signature_buff_32   = (uint32_t *) (((uint8_t *) p_private_key_buff_32) + (private_key_size_words * 4U));

    /* The hash input (buf) should have a length of at least the curve size:
     * nist.fips.186-4: " A hash function that provides a lower security strength than
     * the security strength associated with the bit length of 'n' ordinarily should not be used, since this
     * would reduce the security strength of the digital signature process to a level no greater than that
     * provided by the hash function."
     * However, the SCE HW functions only parse hash of exactly curve_bytes length so
     * *-Any larger hash data will be truncated.
     * *-Any smaller data will be 0-padded to the LEFT.
     *
     * Even if the hash input is the same size as the curve, we will still do a copy because the user input
     * is an 8-bit pointer whereas the SCE HW expects a 32-bit pointer and there could possibly be
     * an alignment issue. */
    p_buf_8 = (uint8_t *) (((uint8_t *) p_signature_buff_32) + ((curve_bytes) * 2));

    if ((curve_bytes == PSA_BITS_TO_BYTES(ECC_521_PRIVATE_KEY_LENGTH_BITS)) &&
        (ECC_521_PRIVATE_KEY_LENGTH_BITS == grp->pbits))
    {
        temp_curve_bytes = curve_bytes - 2U; /* HW supports 64bytes*/
    }

    uint32_t bytes_to_copy = blen > temp_curve_bytes ? temp_curve_bytes : blen;

    memcpy(p_buf_8 + (temp_curve_bytes - bytes_to_copy), buf, bytes_to_copy);

    uint32_t   curve_type;
    uint32_t   cmd;
    uint32_t * p_domain_param = NULL;
    ret = ecp_load_curve_attributes_sce(grp, &curve_type, &cmd, NULL, &p_domain_param);
    if (ret)
    {
    }
    else if (0 != mbedtls_mpi_write_binary(d, (uint8_t *) p_private_key_buff_32, private_key_size_words * 4))
    {
        ret = MBEDTLS_ERR_MPI_BUFFER_TOO_SMALL;
    }
    else if (FSP_SUCCESS !=
             p_hw_sce_ecc_generatesign(&curve_type, &cmd, p_private_key_buff_32, (uint32_t *) p_buf_8,
                                       p_signature_buff_32,
                                       (uint32_t *) (((uint8_t *) p_signature_buff_32) + curve_bytes)))
    {
        ret = MBEDTLS_ERR_ECP_BAD_INPUT_DATA;
    }
    /* Import the generated signature into the r and s mpis */
    else if (0 != mbedtls_mpi_read_binary(r, (uint8_t *) p_signature_buff_32, curve_bytes))
    {
        ret = MBEDTLS_ERR_MPI_ALLOC_FAILED;
    }
    else if (0 != mbedtls_mpi_read_binary(s, ((uint8_t *) p_signature_buff_32) + curve_bytes, curve_bytes))
    {
        ret = MBEDTLS_ERR_MPI_ALLOC_FAILED;
    }
    else
    {
        ret = 0;
    }

    mbedtls_free(p_common_buff_32);

    return ret;
}

 #endif                                /* MBEDTLS_ECDSA_SIGN_ALT */

 #if defined(MBEDTLS_ECDSA_VERIFY_ALT)

/*
 * Verify ECDSA signature of hashed message
 */
int mbedtls_ecdsa_verify (mbedtls_ecp_group       * grp,
                          const unsigned char     * buf,
                          size_t                    blen,
                          const mbedtls_ecp_point * Q,
                          const mbedtls_mpi       * r,
                          const mbedtls_mpi       * s)
{
    (void) blen;

    int        ret;
    uint32_t * p_public_key_buff_32;
    uint32_t * p_signature_buff_32;
    uint32_t * p_common_buff_32;
    uint8_t  * p_buf_8;

    size_t curve_bytes = PSA_BITS_TO_BYTES(grp->pbits);

    size_t temp_curve_bytes = curve_bytes;

  #if defined(MBEDTLS_CHECK_PARAMS)
    if (curve_bytes == 0)
    {
        return MBEDTLS_ERR_ECP_BAD_INPUT_DATA;
    }
  #endif

    /* Fail cleanly on curves that HW doesn't support */
    if (!ecp_can_do_sce(grp->id) || (grp->N.p == NULL))
    {
        return MBEDTLS_ERR_ECP_FEATURE_UNAVAILABLE;
    }

    hw_sce_ecc_verifysign_t p_hw_sce_ecc_verifysign =
        g_ecdsa_verify_sign_lookup[RM_PSA_CRYPTO_ECP_LOOKUP_INDEX(grp->pbits)]
    ;
    if (NULL == p_hw_sce_ecc_verifysign)
    {
        return MBEDTLS_ERR_PLATFORM_FEATURE_UNSUPPORTED;
    }

    /* Obtain a 32-bit aligned block of memory. It will be used for all the following items in this order:
     * Public Key (Q) of size curve_bytes * 2
     * Signature (rs) of size curve_bytes * 2
     * Padded/truncated 32-bit aligned copy of input hash of size curve_bytes  */
    p_common_buff_32 = mbedtls_calloc((curve_bytes * 5), sizeof(uint8_t));

    if (NULL == p_common_buff_32)
    {
        return MBEDTLS_ERR_ECP_ALLOC_FAILED;
    }

    p_public_key_buff_32 = p_common_buff_32;
    p_signature_buff_32  = (uint32_t *) (((uint8_t *) p_public_key_buff_32) + (curve_bytes * 2));

    /* The hash input (buf) should have a length of at least the curve size:
     * nist.fips.186-4: " A hash function that provides a lower security strength than
     * the security strength associated with the bit length of 'n' ordinarily should not be used, since this
     * would reduce the security strength of the digital signature process to a level no greater than that
     * provided by the hash function."
     * However, the SCE HW functions only parse hash of exactly curve_bytes length so
     * *-Any larger hash data will be truncated.
     * *-Any smaller data will be 0-padded to the LEFT.
     *
     * Even if the hash input is the same size as the curve, we will still do a copy because the user input
     * is an 8-bit pointer whereas the SCE HW expects a 32-bit pointer and there could possibly be
     * an alignment issue. */
    p_buf_8 = (uint8_t *) (((uint8_t *) p_signature_buff_32) + (curve_bytes * 2));

    if ((curve_bytes == PSA_BITS_TO_BYTES(ECC_521_PRIVATE_KEY_LENGTH_BITS)) &&
        (ECC_521_PRIVATE_KEY_LENGTH_BITS == grp->pbits))
    {
        temp_curve_bytes = curve_bytes - 2U; /* HW supports 64bytes*/
    }

    uint32_t bytes_to_copy = blen > temp_curve_bytes ? temp_curve_bytes : blen;

    memcpy(p_buf_8 + (temp_curve_bytes - bytes_to_copy), buf, bytes_to_copy);

    uint32_t   curve_type;
    uint32_t   cmd;
    uint32_t * p_domain_param = NULL;
    ret = ecp_load_curve_attributes_sce(grp, &curve_type, &cmd, NULL, &p_domain_param);
    if (ret)
    {
    }
    else if (0 != mbedtls_mpi_write_binary(&Q->X, (uint8_t *) p_public_key_buff_32, curve_bytes))
    {
        ret = MBEDTLS_ERR_MPI_BUFFER_TOO_SMALL;
    }
    else if (0 != mbedtls_mpi_write_binary(&Q->Y, (((uint8_t *) p_public_key_buff_32) + curve_bytes), curve_bytes))
    {
        ret = MBEDTLS_ERR_MPI_BUFFER_TOO_SMALL;
    }
    else if (0 != mbedtls_mpi_write_binary(r, (uint8_t *) p_signature_buff_32, curve_bytes))
    {
        ret = MBEDTLS_ERR_MPI_BUFFER_TOO_SMALL;
    }
    else if (0 != mbedtls_mpi_write_binary(s, ((uint8_t *) p_signature_buff_32) + curve_bytes, curve_bytes))
    {
        ret = MBEDTLS_ERR_MPI_BUFFER_TOO_SMALL;
    }
    else
    {
        if (FSP_SUCCESS !=
            p_hw_sce_ecc_verifysign(&curve_type, &cmd, p_public_key_buff_32, (uint32_t *) p_buf_8, p_signature_buff_32,
                                    (uint32_t *) (((uint8_t *) p_signature_buff_32) + curve_bytes)))
        {
            ret = MBEDTLS_ERR_ECP_VERIFY_FAILED;
        }
    }

    mbedtls_free(p_common_buff_32);

    return ret;
}

 #endif                                /* !MBEDTLS_ECDSA_VERIFY_ALT */

#endif                                 /* MBEDTLS_ECDSA_C */
