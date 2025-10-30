    MOV R5, R0           // T16, 1 cycle
loop:
    .include "shifts.s"
    SUBS R5, #1          // T16, 1 cycle
    BNE loop             // T16, 1 cycle if the branch is not taken, 2 in case the branch is taken
                         // Total execution time should be 6 + (n - 1) * 7 + 1
