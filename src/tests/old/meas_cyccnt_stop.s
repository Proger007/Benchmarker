// Stop cycle count measurement using DWT->CYCCNT and subtract the overhead
LDR r1, [r3, #4]
SUB r1, r1, r2
SUB r1, r1, #2
