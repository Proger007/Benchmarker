.global  test_cyccnt_dummy_2
.text

// *************************************************************************************************
/// @fn
// *************************************************************************************************
test_cyccnt_dummy_2:
	.include "meas_cyccnt_start.s"
	.include "rcs_dummy_2.s"
	.include "meas_cyccnt_stop.s"
    MOV r0, r1

    BX LR

.end

