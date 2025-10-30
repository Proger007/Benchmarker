#pragma once

#include <cstdint>

#ifdef __cplusplus
extern "C"
{
#endif

uint32_t test_cyccnt_bl_0(void);
uint32_t test_cyccnt_bl_nop_2(void);
uint32_t test_cyccnt_bl_dummy_2(void);
uint32_t test_cyccnt_dummy_2(void);
uint32_t test_cyccnt_dummy_5000(void);
uint32_t test_cyccnt_loop(uint32_t cycles);

uint32_t test_cyccnt_loop_aligned_0(uint32_t cycles);
uint32_t test_cyccnt_loop_aligned_2(uint32_t cycles);
uint32_t test_cyccnt_loop_aligned_4(uint32_t cycles);
uint32_t test_cyccnt_loop_aligned_6(uint32_t cycles);
uint32_t test_cyccnt_loop_aligned_8(uint32_t cycles);
uint32_t test_cyccnt_loop_aligned_A(uint32_t cycles);
uint32_t test_cyccnt_loop_aligned_C(uint32_t cycles);
uint32_t test_cyccnt_loop_aligned_E(uint32_t cycles);

void test_loop_aligned_0(uint32_t cycles);
void test_loop_aligned_2(uint32_t cycles);
void test_loop_aligned_4(uint32_t cycles);
void test_loop_aligned_6(uint32_t cycles);
void test_loop_aligned_8(uint32_t cycles);
void test_loop_aligned_A(uint32_t cycles);
void test_loop_aligned_C(uint32_t cycles);
void test_loop_aligned_E(uint32_t cycles);

uint32_t test_cyccnt128_loop_aligned_0(uint32_t cycles);
uint32_t test_cyccnt128_loop_aligned_2(uint32_t cycles);
uint32_t test_cyccnt128_loop_aligned_4(uint32_t cycles);
uint32_t test_cyccnt128_loop_aligned_6(uint32_t cycles);
uint32_t test_cyccnt128_loop_aligned_8(uint32_t cycles);
uint32_t test_cyccnt128_loop_aligned_A(uint32_t cycles);
uint32_t test_cyccnt128_loop_aligned_C(uint32_t cycles);
uint32_t test_cyccnt128_loop_aligned_E(uint32_t cycles);

void test_dummy_2(void);
void test_dummy_10(void);
void test_dummy_100(void);
void test_dummy_5000(void);
void test_ldr_1000(void);
void test_ldr_5000(void);
void test_str_1000(void);
void test_str_5000(void);
void test_loop(uint32_t cycles);


#ifdef __cplusplus
}
#endif
