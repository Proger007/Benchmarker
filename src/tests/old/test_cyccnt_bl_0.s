.global  test_cyccnt_bl_0
.text

// *************************************************************************************************
/// @fn
// *************************************************************************************************
test_cyccnt_bl_0:
    PUSH {R4, LR} // Stack must be 8-bytes aligned, so pushing 2 registers, not only LR
	.include "meas_cyccnt_start.s"
	BL bl_0
	.include "meas_cyccnt_stop.s"
    MOV r0, r1

    POP {R4, PC}

.end
