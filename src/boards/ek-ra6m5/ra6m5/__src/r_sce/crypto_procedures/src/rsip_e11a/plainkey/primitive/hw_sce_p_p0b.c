/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "hw_sce_ra_private.h"

fsp_err_t HW_SCE_GenerateSha256HmacRandomKeyIndexSub (uint32_t OutData_KeyIndex[])
{
    if (RD1_MASK(REG_6CH, 0x00000017U) != 0)
    {
        return FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT;
    }

    WR1_PROG(REG_70H, 0x000b0001U);
    WR1_PROG(REG_4CH, 0x00000000U);

    HW_SCE_p_func100(0xb2ff2993U, 0x35eaaae5U, 0xf4edb773U, 0x515f2cbeU);
    HW_SCE_p_func103();
    WR1_PROG(REG_14H, 0x000000a1U);
    WR1_PROG(REG_D0H, 0x0c200104U);
    WAIT_STS(REG_14H, 31, 1);
    WR1_PROG(REG_2CH, change_endian_long(0x00000000U));

    WR1_PROG(REG_9CH, 0x80010000U);
    WR1_PROG(REG_00H, 0x03410005U);
    WAIT_STS(REG_04H, 30, 0);
    WR1_PROG(REG_40H, 0x00001800U);
    WR1_PROG(REG_00H, 0x0001000dU);
    WAIT_STS(REG_04H, 30, 0);
    WR1_PROG(REG_40H, 0x00001800U);

    WR1_PROG(REG_94H, 0x000034c0U);

    WR1_PROG(REG_14H, 0x000000a7U);
    WR1_PROG(REG_9CH, 0x800100e0U);
    WAIT_STS(REG_14H, 31, 1);
    WR1_PROG(REG_2CH, change_endian_long(0x0000000bU));
    WR1_PROG(REG_24H, 0x00000000U);

    HW_SCE_p_func101(0x2ae8fa9fU, 0x8f3d71cfU, 0xd8d1d12dU, 0x257c2c13U);
    HW_SCE_p_func043();

    WR1_PROG(REG_94H, 0x0000b4c0U);
    WR1_PROG(REG_94H, 0x0000001bU);

    WR1_PROG(REG_14H, 0x000000a7U);
    WR1_PROG(REG_9CH, 0x800100e0U);
    WAIT_STS(REG_14H, 31, 1);
    WR1_PROG(REG_2CH, change_endian_long(0x0000000bU));
    WR1_PROG(REG_24H, 0x00000000U);

    HW_SCE_p_func101(0x4934e5f7U, 0x32327d28U, 0xd91b7844U, 0xed9b7e85U);
    HW_SCE_p_func044();

    HW_SCE_p_func100(0xfd74a9caU, 0x5c8b629aU, 0xdbca744aU, 0xfed5278cU);
    HW_SCE_p_func103();

    HW_SCE_p_func100(0x5830c41bU, 0x18120532U, 0x4e8497cdU, 0x4bf82543U);
    WR1_PROG(REG_14H, 0x000000a1U);
    WR1_PROG(REG_D0H, 0x0c200104U);
    WAIT_STS(REG_14H, 31, 1);
    WR1_PROG(REG_2CH, change_endian_long(0x00000000U));
    WR1_PROG(REG_94H, 0x00000821U);
    WR1_PROG(REG_9CH, 0x80840001U);
    WR1_PROG(REG_00H, 0x03410011U);
    WAIT_STS(REG_04H, 30, 0);
    WR1_PROG(REG_40H, 0x00001800U);

    HW_SCE_p_func103();

    WR1_PROG(REG_14H, 0x000000a1U);
    WR1_PROG(REG_D0H, 0x0c200104U);
    WAIT_STS(REG_14H, 31, 1);
    WR1_PROG(REG_2CH, change_endian_long(0x00000000U));
    WR1_PROG(REG_94H, 0x0000b420U);
    WR1_PROG(REG_94H, 0x00000010U);
    WR1_PROG(REG_9CH, 0x80840001U);
    WR1_PROG(REG_00H, 0x03410011U);
    WAIT_STS(REG_04H, 30, 0);
    WR1_PROG(REG_40H, 0x00001800U);

    HW_SCE_p_func100(0x2fbe90caU, 0x0be9c19bU, 0x1ee37c1cU, 0x941e4e5dU);
    WR1_PROG(REG_D4H, 0x40000100U);
    WR1_PROG(REG_D0H, 0xe7009d07U);
    WR1_PROG(REG_94H, 0x00000821U);
    WR1_PROG(REG_9CH, 0x81880001U);
    WR1_PROG(REG_00H, 0x00490021U);
    WAIT_STS(REG_04H, 30, 0);
    WR1_PROG(REG_40H, 0x00001800U);

    WR1_PROG(REG_08H, 0x00001022U);
    WAIT_STS(REG_08H, 30, 1);
    RD4_ADDR(REG_2CH, &OutData_KeyIndex[1]);
    WAIT_STS(REG_08H, 30, 1);
    RD4_ADDR(REG_2CH, &OutData_KeyIndex[5]);

    HW_SCE_p_func100(0xe2895ea7U, 0xe532fcf7U, 0x962a836dU, 0xf53bb6adU);
    WR1_PROG(REG_14H, 0x000000a1U);
    WR1_PROG(REG_D0H, 0x0c000104U);
    WAIT_STS(REG_14H, 31, 1);
    WR1_PROG(REG_2CH, change_endian_long(0x00000000U));

    WR1_PROG(REG_D4H, 0x40000000U);
    WR1_PROG(REG_D0H, 0x09108105U);
    WR1_PROG(REG_00H, 0x00410011U);
    WAIT_STS(REG_04H, 30, 0);
    WR1_PROG(REG_40H, 0x00001800U);

    WR1_PROG(REG_08H, 0x00001012U);
    WAIT_STS(REG_08H, 30, 1);
    RD4_ADDR(REG_2CH, &OutData_KeyIndex[9]);

    HW_SCE_p_func100(0x4416d9e2U, 0x7849ca00U, 0x00f8d7f5U, 0x4758751cU);
    WR1_PROG(REG_9CH, 0x81010000U);
    WR1_PROG(REG_08H, 0x00005006U);
    WAIT_STS(REG_08H, 30, 1);
    RD1_ADDR(REG_2CH, &OutData_KeyIndex[0]);

    HW_SCE_p_func102(0x178e0545U, 0x399e4496U, 0x8052180fU, 0xa952c998U);
    WR1_PROG(REG_6CH, 0x00000040U);
    WAIT_STS(REG_20H, 12, 0);

    return FSP_SUCCESS;
}
