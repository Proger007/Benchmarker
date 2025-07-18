/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "hw_sce_ra_private.h"

fsp_err_t HW_SCE_EcdsaSignatureVerificationSub (const uint32_t InData_CurveType[],
                                                const uint32_t InData_Key[],
                                                const uint32_t InData_MsgDgst[],
                                                const uint32_t InData_Signature[],
                                                const uint32_t InData_DomainParam[])
{
    if (RD1_MASK(REG_6CH, 0x00000017U) != 0)
    {
        return FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT;
    }

    WR1_PROG(REG_70H, 0x00f10001U);
    WR1_PROG(REG_4CH, 0x00000000U);

    WR1_PROG(REG_14H, 0x000000c7U);
    WR1_PROG(REG_9CH, 0x80010000U);
    WAIT_STS(REG_14H, 31, 1);
    WR1_PROG(REG_2CH, InData_CurveType[0]);
    WR1_PROG(REG_24H, 0x00000000U);

    WR1_PROG(REG_94H, 0x3420a800U);
    WR1_PROG(REG_94H, 0x00000003U);
    WR1_PROG(REG_94H, 0x2000b400U);
    WR1_PROG(REG_94H, 0x00000002U);

    WR1_PROG(REG_A0H, 0x20010000U);
    WR1_PROG(REG_14H, 0x00000fc5U);
    WR1_PROG(REG_B0H, 0x00001469U);
    WAIT_STS(REG_14H, 31, 1);
    WR8_ADDR(REG_2CH, &InData_Signature[0]);

    WR1_PROG(REG_B0H, 0x0000146eU);
    WAIT_STS(REG_14H, 31, 1);
    WR8_ADDR(REG_2CH, &InData_Signature[8]);

    WR1_PROG(REG_14H, 0x000007c5U);
    WR1_PROG(REG_B0H, 0x00001472U);
    WAIT_STS(REG_14H, 31, 1);
    WR8_ADDR(REG_2CH, &InData_MsgDgst[0]);

    WR1_PROG(REG_14H, 0x00000fc5U);
    WR1_PROG(REG_B0H, 0x0000347aU);
    WAIT_STS(REG_14H, 31, 1);
    WR16_ADDR(REG_2CH, &InData_Key[0]);

    WR1_PROG(REG_14H, 0x000000a7U);
    WR1_PROG(REG_9CH, 0x800100e0U);
    WAIT_STS(REG_14H, 31, 1);
    WR1_PROG(REG_2CH, change_endian_long(0x000000f1U));
    WR1_PROG(REG_24H, 0x00000000U);

    HW_SCE_p_func101(0x469f1975U, 0x2f2c9075U, 0x02f4c461U, 0x88338e77U);
    HW_SCE_p_func073_r1(InData_DomainParam);

    HW_SCE_p_func100(0x749dea76U, 0x6dd8bc9fU, 0x9bc7dc61U, 0x0d10e1edU);
    WR1_PROG(REG_40H, 0x00400000U);
    WR1_PROG(REG_24H, 0x00000000U);

    if (CHCK_STS(REG_40H, 22, 1))
    {
        HW_SCE_p_func102(0x95ee8092U, 0x0652b63dU, 0x2f5889d3U, 0xa339c87aU);
        WR1_PROG(REG_6CH, 0x00000040U);
        WAIT_STS(REG_20H, 12, 0);

        return FSP_ERR_CRYPTO_SCE_FAIL;
    }
    else
    {
        HW_SCE_p_func102(0x503b44dbU, 0x5473c356U, 0xe59db169U, 0xa579f328U);
        WR1_PROG(REG_6CH, 0x00000040U);
        WAIT_STS(REG_20H, 12, 0);

        return FSP_SUCCESS;
    }
}
