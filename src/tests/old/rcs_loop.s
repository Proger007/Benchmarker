loop:
    LDR R4, [R7, #4]        // 2 cycles
    ROR R4, R4, R5      // 1 cycle
    ADD R4, R4, #7      // 1 cycle
    STR R4, [R7, #4]        // 2 cycles by default, but load-store is optimized here to 1 cycle
    SUB R6, R6, R5      // 1 cycle
    BNE loop            // 1 cycle if the branch is not taken, 2 in case the branch is taken
                        // Total execution time should be 8 + (n - 1) * 9, actual 7 + (n - 1) * 8
