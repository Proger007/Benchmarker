.global  bl_nop_2
.text

// *************************************************************************************************
/// @fn          bl_nop_2
///
/// @brief       Executes empty commands
// *************************************************************************************************
bl_nop_2:

    // 0xBF00 - canonical NOP instruction
    // Using NOP mnemonic command doesn't guarantee translating into canonical NOP op-code
    // Dummy MOV command is often used instead
    .hword 0xBF00
    .hword 0xBF00
    BX LR

.end
