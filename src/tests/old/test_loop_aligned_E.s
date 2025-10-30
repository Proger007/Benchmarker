.global  test_loop_aligned_E
.text
.align 4
// *************************************************************************************************
/// @fn
// *************************************************************************************************
test_loop_aligned_E:
    PUSH {R4-R7}
    SUB SP, SP, #8
    ADD R7, SP, #0
    MOV R6, R0
    MOVW R4, #0x55AA
    MOVT R4, #0x55AA
    STR R4, [R7]
    MOV R5, #1

    ADD R7, R7, #0
    ADD R7, R7, #0
    ADD R7, R7, #0
    ADD R7, R7, #0
    ADD R7, R7, #0
    ADD R7, R7, #0
    // Aligned to 128-bit line
    ADD R7, R7, #0
    ADD R7, R7, #0
    ADD R7, R7, #0
    ADD R7, R7, #0
    ADD R7, R7, #0
    ADD R7, R7, #0
    ADD R7, R7, #0

	.include "rcs_loop.s"

    ADD SP, SP, #8
    POP {R4-R7}

    BX LR

.end
