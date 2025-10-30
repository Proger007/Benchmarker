// Start cycle count measurement using DWT->CYCCNT
// All dummy instructions result in 128-bit aligned set of instructions
ADD R7, R7, #0
ADD R7, R7, #0
ADD R7, R7, #0
ADD R7, R7, #0
ADD R7, R7, #0
ADD R7, R7, #0
LDR r3, =0xE0001000
LDR r2, [r3, #4]
