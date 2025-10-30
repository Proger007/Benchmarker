// Start cycle count measurement using DWT->CYCCNT
LDR r3, =0xE0001000
LDR r2, [r3, #4]
