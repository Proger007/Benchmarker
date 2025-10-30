.global  test_cyccnt_bl_nop_2
.text

// *************************************************************************************************
/// @fn
// *************************************************************************************************
test_cyccnt_bl_nop_2:
    PUSH {R4, LR}
	.include "meas_cyccnt_start.s"
	BL bl_nop_2
	.include "meas_cyccnt_stop.s"
    MOV r0, r1

    POP {R4, PC}

.end
