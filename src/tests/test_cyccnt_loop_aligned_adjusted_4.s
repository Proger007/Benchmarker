.global  test_cyccnt_loop_aligned_adjusted_4
.text
.syntax unified
.align 4

// *************************************************************************************************
/// @fn
// *************************************************************************************************
test_cyccnt_loop_aligned_adjusted_4:
    .include "prologue.s"
    // Aligned to 128-bit line

    MOV R4, R4
    MOV R4, R4
	.include "meas_cyccnt_start_adjusted.s"
	.include "rcs_loop.s"
	.include "meas_cyccnt_stop.s"

    .include "epilogue.s"

.end
