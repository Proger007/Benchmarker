.global  test_loop_aligned_0
.text
.syntax unified
.align 4

// *************************************************************************************************
/// @fn
// *************************************************************************************************
test_loop_aligned_0:
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

	.include "rcs_loop.s"

    POP {R4-R7}

    MOV r0, r1

    BX LR

.end
