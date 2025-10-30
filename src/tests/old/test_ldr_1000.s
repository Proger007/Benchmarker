.global  test_ldr_1000
.text

// *************************************************************************************************
/// @fn
// *************************************************************************************************
test_ldr_1000:
    PUSH {R4-R7}
    SUB SP, SP, #8
    ADD R7, SP, #0
    MOVW R4, #0x55AA
    MOVT R4, #0x55AA
    MOVW R5, #0xAA55
    MOVT R5, #0xAA55
    STR R4, [R7]
    STR R5, [R7, #4]
    EOR R4, R4, R4
    MOV R5, R4

	//.include "rcs_ldr_1000.s"

    ADD SP, SP, #8
    POP {R4-R7}

    BX LR

.end
