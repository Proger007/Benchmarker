//
// Created by altaero on 5/8/25.
//

#include "board.h"

#include "tests.h"

#include <cstdint>

[[noreturn]]
int main()
{
    board::init();
    board::enableCache();
    // board::disableCache();

    [[maybe_unused]] volatile uint32_t cycles[128] {};
    [[maybe_unused]] auto idx {0u};
    constexpr uint32_t iter_count {100};


    cycles[idx++] = test_cyccnt_loop_aligned_0(iter_count);
    cycles[idx++] = test_cyccnt_loop_aligned_0(iter_count);
    cycles[idx++] = test_cyccnt_loop_aligned_2(iter_count);
    cycles[idx++] = test_cyccnt_loop_aligned_2(iter_count);
    cycles[idx++] = test_cyccnt_loop_aligned_4(iter_count);
    cycles[idx++] = test_cyccnt_loop_aligned_4(iter_count);
    cycles[idx++] = test_cyccnt_loop_aligned_6(iter_count);
    cycles[idx++] = test_cyccnt_loop_aligned_6(iter_count);
    cycles[idx++] = test_cyccnt_loop_aligned_8(iter_count);
    cycles[idx++] = test_cyccnt_loop_aligned_8(iter_count);
    cycles[idx++] = test_cyccnt_loop_aligned_A(iter_count);
    cycles[idx++] = test_cyccnt_loop_aligned_A(iter_count);
    cycles[idx++] = test_cyccnt_loop_aligned_C(iter_count);
    cycles[idx++] = test_cyccnt_loop_aligned_C(iter_count);
    cycles[idx++] = test_cyccnt_loop_aligned_E(iter_count);
    cycles[idx++] = test_cyccnt_loop_aligned_E(iter_count);

    cycles[idx++] = test_cyccnt_loop_aligned_adjusted_0(iter_count);
    cycles[idx++] = test_cyccnt_loop_aligned_adjusted_0(iter_count);
    cycles[idx++] = test_cyccnt_loop_aligned_adjusted_2(iter_count);
    cycles[idx++] = test_cyccnt_loop_aligned_adjusted_2(iter_count);
    cycles[idx++] = test_cyccnt_loop_aligned_adjusted_4(iter_count);
    cycles[idx++] = test_cyccnt_loop_aligned_adjusted_4(iter_count);
    cycles[idx++] = test_cyccnt_loop_aligned_adjusted_6(iter_count);
    cycles[idx++] = test_cyccnt_loop_aligned_adjusted_6(iter_count);
    cycles[idx++] = test_cyccnt_loop_aligned_adjusted_8(iter_count);
    cycles[idx++] = test_cyccnt_loop_aligned_adjusted_8(iter_count);
    cycles[idx++] = test_cyccnt_loop_aligned_adjusted_A(iter_count);
    cycles[idx++] = test_cyccnt_loop_aligned_adjusted_A(iter_count);
    cycles[idx++] = test_cyccnt_loop_aligned_adjusted_C(iter_count);
    cycles[idx++] = test_cyccnt_loop_aligned_adjusted_C(iter_count);
    cycles[idx++] = test_cyccnt_loop_aligned_adjusted_E(iter_count);
    cycles[idx++] = test_cyccnt_loop_aligned_adjusted_E(iter_count);

    if constexpr (false)
    {
        cycles[idx++] = test_cyccnt_unrolled_1_aligned_0();
        cycles[idx++] = test_cyccnt_unrolled_1_aligned_0();
        cycles[idx++] = test_cyccnt_unrolled_1_aligned_2();
        cycles[idx++] = test_cyccnt_unrolled_1_aligned_2();
        cycles[idx++] = test_cyccnt_unrolled_1_aligned_4();
        cycles[idx++] = test_cyccnt_unrolled_1_aligned_4();
        cycles[idx++] = test_cyccnt_unrolled_1_aligned_6();
        cycles[idx++] = test_cyccnt_unrolled_1_aligned_6();
        cycles[idx++] = test_cyccnt_unrolled_1_aligned_8();
        cycles[idx++] = test_cyccnt_unrolled_1_aligned_8();
        cycles[idx++] = test_cyccnt_unrolled_1_aligned_A();
        cycles[idx++] = test_cyccnt_unrolled_1_aligned_A();
        cycles[idx++] = test_cyccnt_unrolled_1_aligned_C();
        cycles[idx++] = test_cyccnt_unrolled_1_aligned_C();
        cycles[idx++] = test_cyccnt_unrolled_1_aligned_E();
        cycles[idx++] = test_cyccnt_unrolled_1_aligned_E();

        cycles[idx++] = test_cyccnt_unrolled_2_aligned_0();
        cycles[idx++] = test_cyccnt_unrolled_2_aligned_0();
        cycles[idx++] = test_cyccnt_unrolled_2_aligned_2();
        cycles[idx++] = test_cyccnt_unrolled_2_aligned_2();
        cycles[idx++] = test_cyccnt_unrolled_2_aligned_4();
        cycles[idx++] = test_cyccnt_unrolled_2_aligned_4();
        cycles[idx++] = test_cyccnt_unrolled_2_aligned_6();
        cycles[idx++] = test_cyccnt_unrolled_2_aligned_6();
        cycles[idx++] = test_cyccnt_unrolled_2_aligned_8();
        cycles[idx++] = test_cyccnt_unrolled_2_aligned_8();
        cycles[idx++] = test_cyccnt_unrolled_2_aligned_A();
        cycles[idx++] = test_cyccnt_unrolled_2_aligned_A();
        cycles[idx++] = test_cyccnt_unrolled_2_aligned_C();
        cycles[idx++] = test_cyccnt_unrolled_2_aligned_C();
        cycles[idx++] = test_cyccnt_unrolled_2_aligned_E();
        cycles[idx++] = test_cyccnt_unrolled_2_aligned_E();

        cycles[idx++] = test_cyccnt_unrolled_3_aligned_0();
        cycles[idx++] = test_cyccnt_unrolled_3_aligned_0();
        cycles[idx++] = test_cyccnt_unrolled_3_aligned_2();
        cycles[idx++] = test_cyccnt_unrolled_3_aligned_2();
        cycles[idx++] = test_cyccnt_unrolled_3_aligned_4();
        cycles[idx++] = test_cyccnt_unrolled_3_aligned_4();
        cycles[idx++] = test_cyccnt_unrolled_3_aligned_6();
        cycles[idx++] = test_cyccnt_unrolled_3_aligned_6();
        cycles[idx++] = test_cyccnt_unrolled_3_aligned_8();
        cycles[idx++] = test_cyccnt_unrolled_3_aligned_8();
        cycles[idx++] = test_cyccnt_unrolled_3_aligned_A();
        cycles[idx++] = test_cyccnt_unrolled_3_aligned_A();
        cycles[idx++] = test_cyccnt_unrolled_3_aligned_C();
        cycles[idx++] = test_cyccnt_unrolled_3_aligned_C();
        cycles[idx++] = test_cyccnt_unrolled_3_aligned_E();
        cycles[idx++] = test_cyccnt_unrolled_3_aligned_E();

        cycles[idx++] = test_cyccnt_unrolled_100_aligned_0();
        cycles[idx++] = test_cyccnt_unrolled_100_aligned_0();
        cycles[idx++] = test_cyccnt_unrolled_100_aligned_2();
        cycles[idx++] = test_cyccnt_unrolled_100_aligned_2();
        cycles[idx++] = test_cyccnt_unrolled_100_aligned_4();
        cycles[idx++] = test_cyccnt_unrolled_100_aligned_4();
        cycles[idx++] = test_cyccnt_unrolled_100_aligned_6();
        cycles[idx++] = test_cyccnt_unrolled_100_aligned_6();
        cycles[idx++] = test_cyccnt_unrolled_100_aligned_8();
        cycles[idx++] = test_cyccnt_unrolled_100_aligned_8();
        cycles[idx++] = test_cyccnt_unrolled_100_aligned_A();
        cycles[idx++] = test_cyccnt_unrolled_100_aligned_A();
        cycles[idx++] = test_cyccnt_unrolled_100_aligned_C();
        cycles[idx++] = test_cyccnt_unrolled_100_aligned_C();
        cycles[idx++] = test_cyccnt_unrolled_100_aligned_E();
        cycles[idx++] = test_cyccnt_unrolled_100_aligned_E();


        test_loop_aligned_0(iter_count);
        test_loop_aligned_0(iter_count);
        test_loop_aligned_2(iter_count);
        test_loop_aligned_2(iter_count);
        test_loop_aligned_4(iter_count);
        test_loop_aligned_4(iter_count);
        test_loop_aligned_6(iter_count);
        test_loop_aligned_6(iter_count);
        test_loop_aligned_8(iter_count);
        test_loop_aligned_8(iter_count);
        test_loop_aligned_A(iter_count);
        test_loop_aligned_A(iter_count);
        test_loop_aligned_C(iter_count);
        test_loop_aligned_C(iter_count);
        test_loop_aligned_E(iter_count);
        test_loop_aligned_E(iter_count);

        test_unrolled_1_aligned_0();
        test_unrolled_1_aligned_0();
        test_unrolled_1_aligned_2();
        test_unrolled_1_aligned_2();
        test_unrolled_1_aligned_4();
        test_unrolled_1_aligned_4();
        test_unrolled_1_aligned_6();
        test_unrolled_1_aligned_6();
        test_unrolled_1_aligned_8();
        test_unrolled_1_aligned_8();
        test_unrolled_1_aligned_A();
        test_unrolled_1_aligned_A();
        test_unrolled_1_aligned_C();
        test_unrolled_1_aligned_C();
        test_unrolled_1_aligned_E();
        test_unrolled_1_aligned_E();

        test_unrolled_2_aligned_0();
        test_unrolled_2_aligned_0();
        test_unrolled_2_aligned_2();
        test_unrolled_2_aligned_2();
        test_unrolled_2_aligned_4();
        test_unrolled_2_aligned_4();
        test_unrolled_2_aligned_6();
        test_unrolled_2_aligned_6();
        test_unrolled_2_aligned_8();
        test_unrolled_2_aligned_8();
        test_unrolled_2_aligned_A();
        test_unrolled_2_aligned_A();
        test_unrolled_2_aligned_C();
        test_unrolled_2_aligned_C();
        test_unrolled_2_aligned_E();
        test_unrolled_2_aligned_E();

        test_unrolled_3_aligned_0();
        test_unrolled_3_aligned_0();
        test_unrolled_3_aligned_2();
        test_unrolled_3_aligned_2();
        test_unrolled_3_aligned_4();
        test_unrolled_3_aligned_4();
        test_unrolled_3_aligned_6();
        test_unrolled_3_aligned_6();
        test_unrolled_3_aligned_8();
        test_unrolled_3_aligned_8();
        test_unrolled_3_aligned_A();
        test_unrolled_3_aligned_A();
        test_unrolled_3_aligned_C();
        test_unrolled_3_aligned_C();
        test_unrolled_3_aligned_E();
        test_unrolled_3_aligned_E();

        test_unrolled_100_aligned_0();
        test_unrolled_100_aligned_0();
        test_unrolled_100_aligned_2();
        test_unrolled_100_aligned_2();
        test_unrolled_100_aligned_4();
        test_unrolled_100_aligned_4();
        test_unrolled_100_aligned_6();
        test_unrolled_100_aligned_6();
        test_unrolled_100_aligned_8();
        test_unrolled_100_aligned_8();
        test_unrolled_100_aligned_A();
        test_unrolled_100_aligned_A();
        test_unrolled_100_aligned_C();
        test_unrolled_100_aligned_C();
        test_unrolled_100_aligned_E();
        test_unrolled_100_aligned_E();
    }

    while (true)
    {

    }
}
