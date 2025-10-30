.global  test_cyccnt_unrolled_1_aligned_6
.text
.syntax unified
.align 4

// *************************************************************************************************
/// @fn
// *************************************************************************************************
test_cyccnt_unrolled_1_aligned_6:
    PUSH {R4-R7}
    MOVW R4, #0x55AA
    MOVT R4, #0x55AA
    MOVW R6, #0x1824
    MOVT R6, #0x1824
    MOVW R7, #0x4281
    MOVT R7, #0x4281

    MOV R4, R4
    MOV R4, R4
    MOV R4, R4
    // Aligned to 128-bit line

    MOV R4, R4
    MOV R4, R4
    MOV R4, R4
	.include "meas_cyccnt_start.s"
	.include "rcs_unrolled_1.s"
	.include "meas_cyccnt_stop.s"

    POP {R4-R7}

    MOV r0, r1

    BX LR

.end
