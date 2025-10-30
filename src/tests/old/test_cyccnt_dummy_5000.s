.global  test_cyccnt_dummy_5000
.text

// *************************************************************************************************
/// @fn
// *************************************************************************************************
test_cyccnt_dummy_5000:
	// Start cycle count measurement using DWT->CYCCNT
	MOVW r3, 0x1000
	MOVT r3, 0xE000
    LDR r2, [r3, #4]
	.include "rcs_dummy_5000.s"
	.include "meas_cyccnt_stop.s"
    MOV r0, r1

    BX LR

.end

