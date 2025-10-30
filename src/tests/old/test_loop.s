.global  test_loop
.text
.align 16

// *************************************************************************************************
/// @fn
// *************************************************************************************************
test_loop:
    PUSH {R4-R7}
    SUB SP, SP, #8
    ADD R7, SP, #0
    MOV R6, R0
    MOVW R4, #0x55AA
    MOVT R4, #0x55AA
    STR R4, [R7]
    MOV R5, #1

	.include "rcs_loop.s"

    ADD SP, SP, #8
    POP {R4-R7}

    BX LR

.end
