PUSH {R4, R7}
SUB SP, SP, #8
ADD R7, SP, #4
MOV R4, #0x55AA
// start measure
STR R4, [R7]
STR R4, [R7]
// stop measure
ADD SP, SP, #8
POP {R4, R7}
