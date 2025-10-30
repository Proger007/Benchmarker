.global  test_loop_aligned_0
.text
.align 4
// *************************************************************************************************
/// @fn
// *************************************************************************************************
test_loop_aligned_0:
    PUSH {R4-R7}
    SUB SP, #8
    MOV R7, SP
    MOV R6, R0
    MOVW R4, #0x55AA
    MOVT R4, #0x55AA
    STR R4, [R7, #4]
    MOV R5, #1

    ADD R7, R7, #0
    ADD R7, R7, #0
    ADD R7, R7, #0
    ADD R7, R7, #0
    ADD R7, R7, #0
    ADD R7, R7, #0
    // Aligned to 128-bit line

	.include "rcs_loop.s"

    ADD SP, SP, #8
    POP {R4-R7}

    BX LR

.end
