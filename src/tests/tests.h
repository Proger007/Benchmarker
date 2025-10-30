#pragma once

#include <cstdint>

#ifdef __cplusplus
extern "C"
{
#endif

uint32_t test_cyccnt_loop_aligned_0(uint32_t cycles);
uint32_t test_cyccnt_loop_aligned_2(uint32_t cycles);
uint32_t test_cyccnt_loop_aligned_4(uint32_t cycles);
uint32_t test_cyccnt_loop_aligned_6(uint32_t cycles);
uint32_t test_cyccnt_loop_aligned_8(uint32_t cycles);
uint32_t test_cyccnt_loop_aligned_A(uint32_t cycles);
uint32_t test_cyccnt_loop_aligned_C(uint32_t cycles);
uint32_t test_cyccnt_loop_aligned_E(uint32_t cycles);

uint32_t test_cyccnt_loop_aligned_adjusted_0(uint32_t cycles);
uint32_t test_cyccnt_loop_aligned_adjusted_2(uint32_t cycles);
uint32_t test_cyccnt_loop_aligned_adjusted_4(uint32_t cycles);
uint32_t test_cyccnt_loop_aligned_adjusted_6(uint32_t cycles);
uint32_t test_cyccnt_loop_aligned_adjusted_8(uint32_t cycles);
uint32_t test_cyccnt_loop_aligned_adjusted_A(uint32_t cycles);
uint32_t test_cyccnt_loop_aligned_adjusted_C(uint32_t cycles);
uint32_t test_cyccnt_loop_aligned_adjusted_E(uint32_t cycles);

uint32_t test_cyccnt_unrolled_1_aligned_0(void);
uint32_t test_cyccnt_unrolled_1_aligned_2(void);
uint32_t test_cyccnt_unrolled_1_aligned_4(void);
uint32_t test_cyccnt_unrolled_1_aligned_6(void);
uint32_t test_cyccnt_unrolled_1_aligned_8(void);
uint32_t test_cyccnt_unrolled_1_aligned_A(void);
uint32_t test_cyccnt_unrolled_1_aligned_C(void);
uint32_t test_cyccnt_unrolled_1_aligned_E(void);

uint32_t test_cyccnt_unrolled_2_aligned_0(void);
uint32_t test_cyccnt_unrolled_2_aligned_2(void);
uint32_t test_cyccnt_unrolled_2_aligned_4(void);
uint32_t test_cyccnt_unrolled_2_aligned_6(void);
uint32_t test_cyccnt_unrolled_2_aligned_8(void);
uint32_t test_cyccnt_unrolled_2_aligned_A(void);
uint32_t test_cyccnt_unrolled_2_aligned_C(void);
uint32_t test_cyccnt_unrolled_2_aligned_E(void);

uint32_t test_cyccnt_unrolled_3_aligned_0(void);
uint32_t test_cyccnt_unrolled_3_aligned_2(void);
uint32_t test_cyccnt_unrolled_3_aligned_4(void);
uint32_t test_cyccnt_unrolled_3_aligned_6(void);
uint32_t test_cyccnt_unrolled_3_aligned_8(void);
uint32_t test_cyccnt_unrolled_3_aligned_A(void);
uint32_t test_cyccnt_unrolled_3_aligned_C(void);
uint32_t test_cyccnt_unrolled_3_aligned_E(void);

uint32_t test_cyccnt_unrolled_100_aligned_0(void);
uint32_t test_cyccnt_unrolled_100_aligned_2(void);
uint32_t test_cyccnt_unrolled_100_aligned_4(void);
uint32_t test_cyccnt_unrolled_100_aligned_6(void);
uint32_t test_cyccnt_unrolled_100_aligned_8(void);
uint32_t test_cyccnt_unrolled_100_aligned_A(void);
uint32_t test_cyccnt_unrolled_100_aligned_C(void);
uint32_t test_cyccnt_unrolled_100_aligned_E(void);

void test_loop_aligned_0(uint32_t cycles);
void test_loop_aligned_2(uint32_t cycles);
void test_loop_aligned_4(uint32_t cycles);
void test_loop_aligned_6(uint32_t cycles);
void test_loop_aligned_8(uint32_t cycles);
void test_loop_aligned_A(uint32_t cycles);
void test_loop_aligned_C(uint32_t cycles);
void test_loop_aligned_E(uint32_t cycles);

void test_unrolled_1_aligned_0(void);
void test_unrolled_1_aligned_2(void);
void test_unrolled_1_aligned_4(void);
void test_unrolled_1_aligned_6(void);
void test_unrolled_1_aligned_8(void);
void test_unrolled_1_aligned_A(void);
void test_unrolled_1_aligned_C(void);
void test_unrolled_1_aligned_E(void);

void test_unrolled_2_aligned_0(void);
void test_unrolled_2_aligned_2(void);
void test_unrolled_2_aligned_4(void);
void test_unrolled_2_aligned_6(void);
void test_unrolled_2_aligned_8(void);
void test_unrolled_2_aligned_A(void);
void test_unrolled_2_aligned_C(void);
void test_unrolled_2_aligned_E(void);

void test_unrolled_3_aligned_0(void);
void test_unrolled_3_aligned_2(void);
void test_unrolled_3_aligned_4(void);
void test_unrolled_3_aligned_6(void);
void test_unrolled_3_aligned_8(void);
void test_unrolled_3_aligned_A(void);
void test_unrolled_3_aligned_C(void);
void test_unrolled_3_aligned_E(void);

void test_unrolled_100_aligned_0(void);
void test_unrolled_100_aligned_2(void);
void test_unrolled_100_aligned_4(void);
void test_unrolled_100_aligned_6(void);
void test_unrolled_100_aligned_8(void);
void test_unrolled_100_aligned_A(void);
void test_unrolled_100_aligned_C(void);
void test_unrolled_100_aligned_E(void);

#ifdef __cplusplus
}
#endif
