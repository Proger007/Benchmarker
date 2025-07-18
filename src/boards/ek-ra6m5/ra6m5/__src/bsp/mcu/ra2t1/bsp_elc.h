/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#ifndef BSP_ELC_H
#define BSP_ELC_H

/*******************************************************************************************************************//**
 * @addtogroup BSP_MCU_RA2T1
 * @{
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Exported global variables
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Exported global functions (to be accessed by other files)
 **********************************************************************************************************************/

/* UNCRUSTIFY-OFF */

/** Sources of event signals to be linked to other peripherals or the CPU
 * @note This list is device specific.
 * */
typedef enum e_elc_event_ra2t1
{
    ELC_EVENT_NONE                          = (0x0),   // Link disabled
    ELC_EVENT_ICU_IRQ0                      = (0x001), // External pin interrupt 0
    ELC_EVENT_ICU_IRQ1                      = (0x002), // External pin interrupt 1
    ELC_EVENT_ICU_IRQ2                      = (0x003), // External pin interrupt 2
    ELC_EVENT_ICU_IRQ3                      = (0x004), // External pin interrupt 3
    ELC_EVENT_ICU_IRQ4                      = (0x005), // External pin interrupt 4
    ELC_EVENT_ICU_IRQ5                      = (0x006), // External pin interrupt 5
    ELC_EVENT_ICU_IRQ6                      = (0x007), // External pin interrupt 6
    ELC_EVENT_ICU_IRQ7                      = (0x008), // External pin interrupt 7
    ELC_EVENT_DTC_COMPLETE                  = (0x009), // DTC transfer complete
    ELC_EVENT_DTC_END                       = (0x00A), // DTC transfer end
    ELC_EVENT_ICU_SNOOZE_CANCEL             = (0x00B), // Canceling from Snooze mode
    ELC_EVENT_FCU_FRDYI                     = (0x00C), // Flash ready interrupt
    ELC_EVENT_LVD_LVD1                      = (0x00D), // Voltage monitor 1 interrupt
    ELC_EVENT_LVD_LVD2                      = (0x00E), // Voltage monitor 2 interrupt
    ELC_EVENT_CGC_MOSC_STOP                 = (0x00F), // Main Clock oscillation stop
    ELC_EVENT_LPM_SNOOZE_REQUEST            = (0x010), // Snooze entry
    ELC_EVENT_AGT0_INT                      = (0x011), // AGT interrupt
    ELC_EVENT_AGT0_COMPARE_A                = (0x012), // Compare match A
    ELC_EVENT_AGT0_COMPARE_B                = (0x013), // Compare match B
    ELC_EVENT_AGT1_INT                      = (0x014), // AGT interrupt
    ELC_EVENT_AGT1_COMPARE_A                = (0x015), // Compare match A
    ELC_EVENT_AGT1_COMPARE_B                = (0x016), // Compare match B
    ELC_EVENT_IWDT_UNDERFLOW                = (0x017), // IWDT underflow
    ELC_EVENT_WDT_UNDERFLOW                 = (0x018), // WDT underflow
    ELC_EVENT_ADC0_SCAN_END                 = (0x01C), // End of A/D scanning operation
    ELC_EVENT_ADC0_SCAN_END_B               = (0x01D), // A/D scan end interrupt for group B
    ELC_EVENT_ADC0_WINDOW_A                 = (0x01E), // Window A Compare match interrupt
    ELC_EVENT_ADC0_WINDOW_B                 = (0x01F), // Window B Compare match interrupt
    ELC_EVENT_ADC0_COMPARE_MATCH            = (0x020), // Compare match
    ELC_EVENT_ADC0_COMPARE_MISMATCH         = (0x021), // Compare mismatch
    ELC_EVENT_ACMPHS0_INT                   = (0x022), // High Speed Comparator channel 0 interrupt
    ELC_EVENT_ACMPHS1_INT                   = (0x023), // High Speed Comparator channel 1 interrupt
    ELC_EVENT_IIC0_RXI                      = (0x027), // Receive data full
    ELC_EVENT_IIC0_TXI                      = (0x028), // Transmit data empty
    ELC_EVENT_IIC0_TEI                      = (0x029), // Transmit end
    ELC_EVENT_IIC0_ERI                      = (0x02A), // Transfer error
    ELC_EVENT_IIC0_WUI                      = (0x02B), // Wakeup interrupt
    ELC_EVENT_KEY_INT                       = (0x033), // Key interrupt
    ELC_EVENT_DOC_INT                       = (0x034), // Data operation circuit interrupt
    ELC_EVENT_CAC_FREQUENCY_ERROR           = (0x035), // Frequency error interrupt
    ELC_EVENT_CAC_MEASUREMENT_END           = (0x036), // Measurement end interrupt
    ELC_EVENT_CAC_OVERFLOW                  = (0x037), // Overflow interrupt
    ELC_EVENT_IOPORT_EVENT_1                = (0x03D), // Port 1 event
    ELC_EVENT_IOPORT_EVENT_2                = (0x03E), // Port 2 event
    ELC_EVENT_ELC_SOFTWARE_EVENT_0          = (0x03F), // Software event 0
    ELC_EVENT_ELC_SOFTWARE_EVENT_1          = (0x040), // Software event 1
    ELC_EVENT_POEG0_EVENT                   = (0x041), // Port Output disable 0 interrupt
    ELC_EVENT_POEG1_EVENT                   = (0x042), // Port Output disable 1 interrupt
    ELC_EVENT_GPT0_CAPTURE_COMPARE_A        = (0x046), // Capture/Compare match A
    ELC_EVENT_GPT0_CAPTURE_COMPARE_B        = (0x047), // Capture/Compare match B
    ELC_EVENT_GPT0_COMPARE_C                = (0x048), // Compare match C
    ELC_EVENT_GPT0_COMPARE_D                = (0x049), // Compare match D
    ELC_EVENT_GPT0_COMPARE_E                = (0x04A), // Compare match E
    ELC_EVENT_GPT0_COMPARE_F                = (0x04B), // Compare match F
    ELC_EVENT_GPT0_COUNTER_OVERFLOW         = (0x04C), // Overflow
    ELC_EVENT_GPT0_COUNTER_UNDERFLOW        = (0x04D), // Underflow
    ELC_EVENT_GPT0_PC                       = (0x04E), // Period count function finish
    ELC_EVENT_GPT0_AD_TRIG_A                = (0x04F), // A/D converter start request A
    ELC_EVENT_GPT0_AD_TRIG_B                = (0x050), // A/D converter start request B
    ELC_EVENT_GPT1_CAPTURE_COMPARE_A        = (0x051), // Capture/Compare match A
    ELC_EVENT_GPT1_CAPTURE_COMPARE_B        = (0x052), // Capture/Compare match B
    ELC_EVENT_GPT1_COMPARE_C                = (0x053), // Compare match C
    ELC_EVENT_GPT1_COMPARE_D                = (0x054), // Compare match D
    ELC_EVENT_GPT1_COMPARE_E                = (0x055), // Compare match E
    ELC_EVENT_GPT1_COMPARE_F                = (0x056), // Compare match F
    ELC_EVENT_GPT1_COUNTER_OVERFLOW         = (0x057), // Overflow
    ELC_EVENT_GPT1_COUNTER_UNDERFLOW        = (0x058), // Underflow
    ELC_EVENT_GPT1_PC                       = (0x059), // Period count function finish
    ELC_EVENT_GPT1_AD_TRIG_A                = (0x05A), // A/D converter start request A
    ELC_EVENT_GPT1_AD_TRIG_B                = (0x05B), // A/D converter start request B
    ELC_EVENT_GPT2_CAPTURE_COMPARE_A        = (0x05C), // Capture/Compare match A
    ELC_EVENT_GPT2_CAPTURE_COMPARE_B        = (0x05D), // Capture/Compare match B
    ELC_EVENT_GPT2_COMPARE_C                = (0x05E), // Compare match C
    ELC_EVENT_GPT2_COMPARE_D                = (0x05F), // Compare match D
    ELC_EVENT_GPT2_COMPARE_E                = (0x060), // Compare match E
    ELC_EVENT_GPT2_COMPARE_F                = (0x061), // Compare match F
    ELC_EVENT_GPT2_COUNTER_OVERFLOW         = (0x062), // Overflow
    ELC_EVENT_GPT2_COUNTER_UNDERFLOW        = (0x063), // Underflow
    ELC_EVENT_GPT2_PC                       = (0x064), // Period count function finish
    ELC_EVENT_GPT2_AD_TRIG_A                = (0x065), // A/D converter start request A
    ELC_EVENT_GPT2_AD_TRIG_B                = (0x066), // A/D converter start request B
    ELC_EVENT_GPT_UVWEDGE                   = (0x070), // UVW edge event
    ELC_EVENT_SCI0_RXI                      = (0x071), // Receive data full
    ELC_EVENT_SCI0_TXI                      = (0x072), // Transmit data empty
    ELC_EVENT_SCI0_TEI                      = (0x073), // Transmit end
    ELC_EVENT_SCI0_ERI                      = (0x074), // Receive error
    ELC_EVENT_SCI0_AM                       = (0x075), // Address match event
    ELC_EVENT_SCI0_RXI_OR_ERI               = (0x076), // Receive data full/Receive error
    ELC_EVENT_SCI1_RXI                      = (0x077), // Receive data full
    ELC_EVENT_SCI1_TXI                      = (0x078), // Transmit data empty
    ELC_EVENT_SCI1_TEI                      = (0x079), // Transmit end
    ELC_EVENT_SCI1_ERI                      = (0x07A), // Receive error
    ELC_EVENT_SCI1_AM                       = (0x07B), // Address match event
    ELC_EVENT_SCI9_RXI                      = (0x07C), // Receive data full
    ELC_EVENT_SCI9_TXI                      = (0x07D), // Transmit data empty
    ELC_EVENT_SCI9_TEI                      = (0x07E), // Transmit end
    ELC_EVENT_SCI9_ERI                      = (0x07F), // Receive error
    ELC_EVENT_SCI9_AM                       = (0x080), // Address match event
    ELC_EVENT_SPI0_RXI                      = (0x081), // Receive buffer full
    ELC_EVENT_SPI0_TXI                      = (0x082), // Transmit buffer empty
    ELC_EVENT_SPI0_IDLE                     = (0x083), // Idle
    ELC_EVENT_SPI0_ERI                      = (0x084), // Error
    ELC_EVENT_SPI0_TEI                      = (0x085), // Transmission complete event
    ELC_EVENT_SCI2_RXI                      = (0x08E), // Receive data full
    ELC_EVENT_SCI2_TXI                      = (0x08F), // Transmit data empty
    ELC_EVENT_SCI2_TEI                      = (0x090), // Transmit end
    ELC_EVENT_SCI2_ERI                      = (0x091), // Receive error
    ELC_EVENT_SCI2_AM                       = (0x092), // Address match event
    ELC_EVENT_GPT3_CAPTURE_COMPARE_A        = (0x098), // Capture/Compare match A
    ELC_EVENT_GPT3_CAPTURE_COMPARE_B        = (0x099), // Capture/Compare match B
    ELC_EVENT_GPT3_COMPARE_C                = (0x09A), // Compare match C
    ELC_EVENT_GPT3_COMPARE_D                = (0x09B), // Compare match D
    ELC_EVENT_GPT3_COMPARE_E                = (0x09C), // Compare match E
    ELC_EVENT_GPT3_COMPARE_F                = (0x09D), // Compare match F
    ELC_EVENT_GPT3_COUNTER_OVERFLOW         = (0x09E), // Overflow
    ELC_EVENT_GPT3_COUNTER_UNDERFLOW        = (0x09F), // Underflow
    ELC_EVENT_GPT3_PC                       = (0x0A0), // Period count function finish
    ELC_EVENT_GPT3_AD_TRIG_A                = (0x0A1), // A/D converter start request A
    ELC_EVENT_GPT3_AD_TRIG_B                = (0x0A2)  // A/D converter start request B
} elc_event_t;

/** Events to be used with the IELSR register to link interrupt events to the NVIC
 * @note This list is device specific.
 * */
typedef enum e_icu_event_ra2t1
{
    ICU_EVENT_ACMPHS0_INT_GROUP0            = (0x09), // group0 (IELSR[0, 8, 16, 24])
    ICU_EVENT_ACMPHS0_INT_GROUP4            = (0x09), // group4 (IELSR[4, 12, 20, 28])
    ICU_EVENT_ACMPHS1_INT_GROUP1            = (0x07), // group1 (IELSR[1, 9, 17, 25])
    ICU_EVENT_ACMPHS1_INT_GROUP5            = (0x07), // group5 (IELSR[5, 13, 21, 29])
    ICU_EVENT_ADC0_COMPARE_MATCH_GROUP0     = (0x08), // group0 (IELSR[0, 8, 16, 24])
    ICU_EVENT_ADC0_COMPARE_MATCH_GROUP4     = (0x08), // group4 (IELSR[4, 12, 20, 28])
    ICU_EVENT_ADC0_COMPARE_MISMATCH_GROUP1  = (0x06), // group1 (IELSR[1, 9, 17, 25])
    ICU_EVENT_ADC0_COMPARE_MISMATCH_GROUP5  = (0x06), // group5 (IELSR[5, 13, 21, 29])
    ICU_EVENT_ADC0_SCAN_END_GROUP0          = (0x07), // group0 (IELSR[0, 8, 16, 24])
    ICU_EVENT_ADC0_SCAN_END_GROUP4          = (0x07), // group4 (IELSR[4, 12, 20, 28])
    ICU_EVENT_ADC0_SCAN_END_B_GROUP1        = (0x05), // group1 (IELSR[1, 9, 17, 25])
    ICU_EVENT_ADC0_SCAN_END_B_GROUP5        = (0x05), // group5 (IELSR[5, 13, 21, 29])
    ICU_EVENT_ADC0_WINDOW_A_GROUP2          = (0x05), // group2 (IELSR[2, 10, 18, 26])
    ICU_EVENT_ADC0_WINDOW_A_GROUP6          = (0x05), // group6 (IELSR[6, 14, 22, 30])
    ICU_EVENT_ADC0_WINDOW_B_GROUP3          = (0x05), // group3 (IELSR[3, 11, 19, 27])
    ICU_EVENT_ADC0_WINDOW_B_GROUP7          = (0x05), // group7 (IELSR[7, 15, 23, 31])
    ICU_EVENT_AGT0_COMPARE_A_GROUP0         = (0x16), // group0 (IELSR[0, 8, 16, 24])
    ICU_EVENT_AGT0_COMPARE_B_GROUP1         = (0x13), // group1 (IELSR[1, 9, 17, 25])
    ICU_EVENT_AGT0_INT_GROUP3               = (0x11), // group3 (IELSR[3, 11, 19, 27])
    ICU_EVENT_AGT1_COMPARE_A_GROUP1         = (0x03), // group1 (IELSR[1, 9, 17, 25])
    ICU_EVENT_AGT1_COMPARE_A_GROUP5         = (0x03), // group5 (IELSR[5, 13, 21, 29])
    ICU_EVENT_AGT1_COMPARE_B_GROUP2         = (0x03), // group2 (IELSR[2, 10, 18, 26])
    ICU_EVENT_AGT1_COMPARE_B_GROUP6         = (0x03), // group6 (IELSR[6, 14, 22, 30])
    ICU_EVENT_AGT1_INT_GROUP0               = (0x05), // group0 (IELSR[0, 8, 16, 24])
    ICU_EVENT_AGT1_INT_GROUP4               = (0x05), // group4 (IELSR[4, 12, 20, 28])
    ICU_EVENT_CAC_FREQUENCY_ERROR_GROUP1    = (0x0B), // group1 (IELSR[1, 9, 17, 25])
    ICU_EVENT_CAC_FREQUENCY_ERROR_GROUP5    = (0x0B), // group5 (IELSR[5, 13, 21, 29])
    ICU_EVENT_CAC_MEASUREMENT_END_GROUP2    = (0x08), // group2 (IELSR[2, 10, 18, 26])
    ICU_EVENT_CAC_MEASUREMENT_END_GROUP6    = (0x08), // group6 (IELSR[6, 14, 22, 30])
    ICU_EVENT_CAC_OVERFLOW_GROUP3           = (0x08), // group3 (IELSR[3, 11, 19, 27])
    ICU_EVENT_CAC_OVERFLOW_GROUP7           = (0x08), // group7 (IELSR[7, 15, 23, 31])
    ICU_EVENT_CGC_MOSC_STOP_GROUP6          = (0x14), // group6 (IELSR[6, 14, 22, 30])
    ICU_EVENT_DOC_INT_GROUP1                = (0x0A), // group1 (IELSR[1, 9, 17, 25])
    ICU_EVENT_DOC_INT_GROUP5                = (0x0A), // group5 (IELSR[5, 13, 21, 29])
    ICU_EVENT_DTC_COMPLETE_GROUP0           = (0x02), // group0 (IELSR[0, 8, 16, 24])
    ICU_EVENT_DTC_COMPLETE_GROUP4           = (0x02), // group4 (IELSR[4, 12, 20, 28])
    ICU_EVENT_ELC_SOFTWARE_EVENT_0_GROUP2   = (0x0A), // group2 (IELSR[2, 10, 18, 26])
    ICU_EVENT_ELC_SOFTWARE_EVENT_0_GROUP6   = (0x0A), // group6 (IELSR[6, 14, 22, 30])
    ICU_EVENT_ELC_SOFTWARE_EVENT_1_GROUP3   = (0x0A), // group3 (IELSR[3, 11, 19, 27])
    ICU_EVENT_ELC_SOFTWARE_EVENT_1_GROUP7   = (0x0A), // group7 (IELSR[7, 15, 23, 31])
    ICU_EVENT_FCU_FRDYI_GROUP2              = (0x02), // group2 (IELSR[2, 10, 18, 26])
    ICU_EVENT_FCU_FRDYI_GROUP6              = (0x02), // group6 (IELSR[6, 14, 22, 30])
    ICU_EVENT_GPT0_AD_TRIG_A_GROUP0         = (0x20), // group0 (IELSR[0, 8, 16, 24])
    ICU_EVENT_GPT0_AD_TRIG_A_GROUP4         = (0x20), // group4 (IELSR[4, 12, 20, 28])
    ICU_EVENT_GPT0_AD_TRIG_B_GROUP1         = (0x20), // group1 (IELSR[1, 9, 17, 25])
    ICU_EVENT_GPT0_AD_TRIG_B_GROUP5         = (0x20), // group5 (IELSR[5, 13, 21, 29])
    ICU_EVENT_GPT0_CAPTURE_COMPARE_A_GROUP0 = (0x0E), // group0 (IELSR[0, 8, 16, 24])
    ICU_EVENT_GPT0_CAPTURE_COMPARE_A_GROUP4 = (0x0E), // group4 (IELSR[4, 12, 20, 28])
    ICU_EVENT_GPT0_CAPTURE_COMPARE_B_GROUP1 = (0x0D), // group1 (IELSR[1, 9, 17, 25])
    ICU_EVENT_GPT0_CAPTURE_COMPARE_B_GROUP5 = (0x0D), // group5 (IELSR[5, 13, 21, 29])
    ICU_EVENT_GPT0_COMPARE_C_GROUP2         = (0x0C), // group2 (IELSR[2, 10, 18, 26])
    ICU_EVENT_GPT0_COMPARE_C_GROUP6         = (0x0C), // group6 (IELSR[6, 14, 22, 30])
    ICU_EVENT_GPT0_COMPARE_D_GROUP3         = (0x0C), // group3 (IELSR[3, 11, 19, 27])
    ICU_EVENT_GPT0_COMPARE_D_GROUP7         = (0x0C), // group7 (IELSR[7, 15, 23, 31])
    ICU_EVENT_GPT0_COMPARE_E_GROUP2         = (0x20), // group2 (IELSR[2, 10, 18, 26])
    ICU_EVENT_GPT0_COMPARE_E_GROUP6         = (0x20), // group6 (IELSR[6, 14, 22, 30])
    ICU_EVENT_GPT0_COMPARE_F_GROUP3         = (0x20), // group3 (IELSR[3, 11, 19, 27])
    ICU_EVENT_GPT0_COMPARE_F_GROUP7         = (0x20), // group7 (IELSR[7, 15, 23, 31])
    ICU_EVENT_GPT0_COUNTER_OVERFLOW_GROUP0  = (0x0F), // group0 (IELSR[0, 8, 16, 24])
    ICU_EVENT_GPT0_COUNTER_OVERFLOW_GROUP4  = (0x0F), // group4 (IELSR[4, 12, 20, 28])
    ICU_EVENT_GPT0_COUNTER_UNDERFLOW_GROUP1 = (0x0E), // group1 (IELSR[1, 9, 17, 25])
    ICU_EVENT_GPT0_COUNTER_UNDERFLOW_GROUP5 = (0x0E), // group5 (IELSR[5, 13, 21, 29])
    ICU_EVENT_GPT0_PC_GROUP2                = (0x21), // group2 (IELSR[2, 10, 18, 26])
    ICU_EVENT_GPT0_PC_GROUP6                = (0x21), // group6 (IELSR[6, 14, 22, 30])
    ICU_EVENT_GPT1_AD_TRIG_A_GROUP0         = (0x21), // group0 (IELSR[0, 8, 16, 24])
    ICU_EVENT_GPT1_AD_TRIG_B_GROUP1         = (0x21), // group1 (IELSR[1, 9, 17, 25])
    ICU_EVENT_GPT1_CAPTURE_COMPARE_A_GROUP0 = (0x19), // group0 (IELSR[0, 8, 16, 24])
    ICU_EVENT_GPT1_CAPTURE_COMPARE_B_GROUP1 = (0x16), // group1 (IELSR[1, 9, 17, 25])
    ICU_EVENT_GPT1_COMPARE_C_GROUP2         = (0x14), // group2 (IELSR[2, 10, 18, 26])
    ICU_EVENT_GPT1_COMPARE_D_GROUP3         = (0x12), // group3 (IELSR[3, 11, 19, 27])
    ICU_EVENT_GPT1_COMPARE_E_GROUP6         = (0x22), // group6 (IELSR[6, 14, 22, 30])
    ICU_EVENT_GPT1_COMPARE_F_GROUP7         = (0x22), // group7 (IELSR[7, 15, 23, 31])
    ICU_EVENT_GPT1_COUNTER_OVERFLOW_GROUP4  = (0x18), // group4 (IELSR[4, 12, 20, 28])
    ICU_EVENT_GPT1_COUNTER_UNDERFLOW_GROUP5 = (0x15), // group5 (IELSR[5, 13, 21, 29])
    ICU_EVENT_GPT1_PC_GROUP2                = (0x22), // group2 (IELSR[2, 10, 18, 26])
    ICU_EVENT_GPT2_AD_TRIG_A_GROUP2         = (0x23), // group2 (IELSR[2, 10, 18, 26])
    ICU_EVENT_GPT2_AD_TRIG_A_GROUP6         = (0x23), // group6 (IELSR[6, 14, 22, 30])
    ICU_EVENT_GPT2_AD_TRIG_B_GROUP3         = (0x23), // group3 (IELSR[3, 11, 19, 27])
    ICU_EVENT_GPT2_AD_TRIG_B_GROUP7         = (0x23), // group7 (IELSR[7, 15, 23, 31])
    ICU_EVENT_GPT2_CAPTURE_COMPARE_A_GROUP0 = (0x10), // group0 (IELSR[0, 8, 16, 24])
    ICU_EVENT_GPT2_CAPTURE_COMPARE_A_GROUP4 = (0x10), // group4 (IELSR[4, 12, 20, 28])
    ICU_EVENT_GPT2_CAPTURE_COMPARE_B_GROUP1 = (0x0F), // group1 (IELSR[1, 9, 17, 25])
    ICU_EVENT_GPT2_CAPTURE_COMPARE_B_GROUP5 = (0x0F), // group5 (IELSR[5, 13, 21, 29])
    ICU_EVENT_GPT2_COMPARE_C_GROUP2         = (0x0D), // group2 (IELSR[2, 10, 18, 26])
    ICU_EVENT_GPT2_COMPARE_C_GROUP6         = (0x0D), // group6 (IELSR[6, 14, 22, 30])
    ICU_EVENT_GPT2_COMPARE_D_GROUP3         = (0x0D), // group3 (IELSR[3, 11, 19, 27])
    ICU_EVENT_GPT2_COMPARE_D_GROUP7         = (0x0D), // group7 (IELSR[7, 15, 23, 31])
    ICU_EVENT_GPT2_COMPARE_E_GROUP0         = (0x22), // group0 (IELSR[0, 8, 16, 24])
    ICU_EVENT_GPT2_COMPARE_E_GROUP4         = (0x22), // group4 (IELSR[4, 12, 20, 28])
    ICU_EVENT_GPT2_COMPARE_F_GROUP1         = (0x22), // group1 (IELSR[1, 9, 17, 25])
    ICU_EVENT_GPT2_COMPARE_F_GROUP5         = (0x22), // group5 (IELSR[5, 13, 21, 29])
    ICU_EVENT_GPT2_COUNTER_OVERFLOW_GROUP2  = (0x0E), // group2 (IELSR[2, 10, 18, 26])
    ICU_EVENT_GPT2_COUNTER_OVERFLOW_GROUP6  = (0x0E), // group6 (IELSR[6, 14, 22, 30])
    ICU_EVENT_GPT2_COUNTER_UNDERFLOW_GROUP3 = (0x0E), // group3 (IELSR[3, 11, 19, 27])
    ICU_EVENT_GPT2_COUNTER_UNDERFLOW_GROUP7 = (0x0E), // group7 (IELSR[7, 15, 23, 31])
    ICU_EVENT_GPT2_PC_GROUP0                = (0x23), // group0 (IELSR[0, 8, 16, 24])
    ICU_EVENT_GPT2_PC_GROUP4                = (0x23), // group4 (IELSR[4, 12, 20, 28])
    ICU_EVENT_GPT3_AD_TRIG_A_GROUP4         = (0x21), // group4 (IELSR[4, 12, 20, 28])
    ICU_EVENT_GPT3_AD_TRIG_B_GROUP5         = (0x21), // group5 (IELSR[5, 13, 21, 29])
    ICU_EVENT_GPT3_CAPTURE_COMPARE_A_GROUP4 = (0x19), // group4 (IELSR[4, 12, 20, 28])
    ICU_EVENT_GPT3_CAPTURE_COMPARE_B_GROUP5 = (0x16), // group5 (IELSR[5, 13, 21, 29])
    ICU_EVENT_GPT3_COMPARE_C_GROUP6         = (0x15), // group6 (IELSR[6, 14, 22, 30])
    ICU_EVENT_GPT3_COMPARE_D_GROUP7         = (0x12), // group7 (IELSR[7, 15, 23, 31])
    ICU_EVENT_GPT3_COMPARE_E_GROUP2         = (0x24), // group2 (IELSR[2, 10, 18, 26])
    ICU_EVENT_GPT3_COMPARE_F_GROUP3         = (0x24), // group3 (IELSR[3, 11, 19, 27])
    ICU_EVENT_GPT3_COUNTER_OVERFLOW_GROUP0  = (0x1A), // group0 (IELSR[0, 8, 16, 24])
    ICU_EVENT_GPT3_COUNTER_UNDERFLOW_GROUP1 = (0x17), // group1 (IELSR[1, 9, 17, 25])
    ICU_EVENT_GPT3_PC_GROUP6                = (0x24), // group6 (IELSR[6, 14, 22, 30])
    ICU_EVENT_GPT_UVWEDGE_GROUP0            = (0x11), // group0 (IELSR[0, 8, 16, 24])
    ICU_EVENT_GPT_UVWEDGE_GROUP4            = (0x11), // group4 (IELSR[4, 12, 20, 28])
    ICU_EVENT_ICU_IRQ0_GROUP0               = (0x01), // group0 (IELSR[0, 8, 16, 24])
    ICU_EVENT_ICU_IRQ0_GROUP4               = (0x01), // group4 (IELSR[4, 12, 20, 28])
    ICU_EVENT_ICU_IRQ1_GROUP1               = (0x01), // group1 (IELSR[1, 9, 17, 25])
    ICU_EVENT_ICU_IRQ1_GROUP5               = (0x01), // group5 (IELSR[5, 13, 21, 29])
    ICU_EVENT_ICU_IRQ2_GROUP2               = (0x01), // group2 (IELSR[2, 10, 18, 26])
    ICU_EVENT_ICU_IRQ2_GROUP6               = (0x01), // group6 (IELSR[6, 14, 22, 30])
    ICU_EVENT_ICU_IRQ3_GROUP3               = (0x01), // group3 (IELSR[3, 11, 19, 27])
    ICU_EVENT_ICU_IRQ3_GROUP7               = (0x01), // group7 (IELSR[7, 15, 23, 31])
    ICU_EVENT_ICU_IRQ4_GROUP4               = (0x16), // group4 (IELSR[4, 12, 20, 28])
    ICU_EVENT_ICU_IRQ5_GROUP5               = (0x13), // group5 (IELSR[5, 13, 21, 29])
    ICU_EVENT_ICU_IRQ6_GROUP6               = (0x13), // group6 (IELSR[6, 14, 22, 30])
    ICU_EVENT_ICU_IRQ7_GROUP7               = (0x11), // group7 (IELSR[7, 15, 23, 31])
    ICU_EVENT_ICU_SNOOZE_CANCEL_GROUP0      = (0x03), // group0 (IELSR[0, 8, 16, 24])
    ICU_EVENT_ICU_SNOOZE_CANCEL_GROUP4      = (0x03), // group4 (IELSR[4, 12, 20, 28])
    ICU_EVENT_IIC0_ERI_GROUP3               = (0x06), // group3 (IELSR[3, 11, 19, 27])
    ICU_EVENT_IIC0_ERI_GROUP7               = (0x06), // group7 (IELSR[7, 15, 23, 31])
    ICU_EVENT_IIC0_RXI_GROUP0               = (0x0A), // group0 (IELSR[0, 8, 16, 24])
    ICU_EVENT_IIC0_RXI_GROUP4               = (0x0A), // group4 (IELSR[4, 12, 20, 28])
    ICU_EVENT_IIC0_TEI_GROUP2               = (0x06), // group2 (IELSR[2, 10, 18, 26])
    ICU_EVENT_IIC0_TEI_GROUP6               = (0x06), // group6 (IELSR[6, 14, 22, 30])
    ICU_EVENT_IIC0_TXI_GROUP1               = (0x08), // group1 (IELSR[1, 9, 17, 25])
    ICU_EVENT_IIC0_TXI_GROUP5               = (0x08), // group5 (IELSR[5, 13, 21, 29])
    ICU_EVENT_IIC0_WUI_GROUP0               = (0x0B), // group0 (IELSR[0, 8, 16, 24])
    ICU_EVENT_IIC0_WUI_GROUP4               = (0x0B), // group4 (IELSR[4, 12, 20, 28])
    ICU_EVENT_IOPORT_EVENT_1_GROUP1         = (0x15), // group1 (IELSR[1, 9, 17, 25])
    ICU_EVENT_IOPORT_EVENT_2_GROUP2         = (0x13), // group2 (IELSR[2, 10, 18, 26])
    ICU_EVENT_IWDT_UNDERFLOW_GROUP3         = (0x03), // group3 (IELSR[3, 11, 19, 27])
    ICU_EVENT_IWDT_UNDERFLOW_GROUP7         = (0x03), // group7 (IELSR[7, 15, 23, 31])
    ICU_EVENT_KEY_INT_GROUP0                = (0x18), // group0 (IELSR[0, 8, 16, 24])
    ICU_EVENT_LPM_SNOOZE_REQUEST_GROUP3     = (0x02), // group3 (IELSR[3, 11, 19, 27])
    ICU_EVENT_LPM_SNOOZE_REQUEST_GROUP7     = (0x02), // group7 (IELSR[7, 15, 23, 31])
    ICU_EVENT_LVD_LVD1_GROUP0               = (0x04), // group0 (IELSR[0, 8, 16, 24])
    ICU_EVENT_LVD_LVD1_GROUP4               = (0x04), // group4 (IELSR[4, 12, 20, 28])
    ICU_EVENT_LVD_LVD2_GROUP1               = (0x02), // group1 (IELSR[1, 9, 17, 25])
    ICU_EVENT_LVD_LVD2_GROUP5               = (0x02), // group5 (IELSR[5, 13, 21, 29])
    ICU_EVENT_POEG0_EVENT_GROUP2            = (0x0B), // group2 (IELSR[2, 10, 18, 26])
    ICU_EVENT_POEG0_EVENT_GROUP6            = (0x0B), // group6 (IELSR[6, 14, 22, 30])
    ICU_EVENT_POEG1_EVENT_GROUP3            = (0x0B), // group3 (IELSR[3, 11, 19, 27])
    ICU_EVENT_POEG1_EVENT_GROUP7            = (0x0B), // group7 (IELSR[7, 15, 23, 31])
    ICU_EVENT_SCI0_AM_GROUP0                = (0x13), // group0 (IELSR[0, 8, 16, 24])
    ICU_EVENT_SCI0_AM_GROUP4                = (0x13), // group4 (IELSR[4, 12, 20, 28])
    ICU_EVENT_SCI0_ERI_GROUP3               = (0x0F), // group3 (IELSR[3, 11, 19, 27])
    ICU_EVENT_SCI0_ERI_GROUP7               = (0x0F), // group7 (IELSR[7, 15, 23, 31])
    ICU_EVENT_SCI0_RXI_GROUP0               = (0x12), // group0 (IELSR[0, 8, 16, 24])
    ICU_EVENT_SCI0_RXI_GROUP4               = (0x12), // group4 (IELSR[4, 12, 20, 28])
    ICU_EVENT_SCI0_TEI_GROUP2               = (0x0F), // group2 (IELSR[2, 10, 18, 26])
    ICU_EVENT_SCI0_TEI_GROUP6               = (0x0F), // group6 (IELSR[6, 14, 22, 30])
    ICU_EVENT_SCI0_TXI_GROUP1               = (0x10), // group1 (IELSR[1, 9, 17, 25])
    ICU_EVENT_SCI0_TXI_GROUP5               = (0x10), // group5 (IELSR[5, 13, 21, 29])
    ICU_EVENT_SCI1_AM_GROUP5                = (0x1A), // group5 (IELSR[5, 13, 21, 29])
    ICU_EVENT_SCI1_ERI_GROUP3               = (0x19), // group3 (IELSR[3, 11, 19, 27])
    ICU_EVENT_SCI1_RXI_GROUP0               = (0x1E), // group0 (IELSR[0, 8, 16, 24])
    ICU_EVENT_SCI1_TEI_GROUP2               = (0x1B), // group2 (IELSR[2, 10, 18, 26])
    ICU_EVENT_SCI1_TXI_GROUP1               = (0x1B), // group1 (IELSR[1, 9, 17, 25])
    ICU_EVENT_SCI2_AM_GROUP1                = (0x1C), // group1 (IELSR[1, 9, 17, 25])
    ICU_EVENT_SCI2_ERI_GROUP7               = (0x19), // group7 (IELSR[7, 15, 23, 31])
    ICU_EVENT_SCI2_RXI_GROUP4               = (0x1D), // group4 (IELSR[4, 12, 20, 28])
    ICU_EVENT_SCI2_TEI_GROUP6               = (0x1C), // group6 (IELSR[6, 14, 22, 30])
    ICU_EVENT_SCI2_TXI_GROUP5               = (0x1B), // group5 (IELSR[5, 13, 21, 29])
    ICU_EVENT_SCI9_AM_GROUP3                = (0x1B), // group3 (IELSR[3, 11, 19, 27])
    ICU_EVENT_SCI9_ERI_GROUP7               = (0x1A), // group7 (IELSR[7, 15, 23, 31])
    ICU_EVENT_SCI9_RXI_GROUP4               = (0x1E), // group4 (IELSR[4, 12, 20, 28])
    ICU_EVENT_SCI9_TEI_GROUP6               = (0x1E), // group6 (IELSR[6, 14, 22, 30])
    ICU_EVENT_SCI9_TXI_GROUP5               = (0x1C), // group5 (IELSR[5, 13, 21, 29])
    ICU_EVENT_SPI0_ERI_GROUP3               = (0x10), // group3 (IELSR[3, 11, 19, 27])
    ICU_EVENT_SPI0_ERI_GROUP7               = (0x10), // group7 (IELSR[7, 15, 23, 31])
    ICU_EVENT_SPI0_IDLE_GROUP2              = (0x10), // group2 (IELSR[2, 10, 18, 26])
    ICU_EVENT_SPI0_IDLE_GROUP6              = (0x10), // group6 (IELSR[6, 14, 22, 30])
    ICU_EVENT_SPI0_RXI_GROUP0               = (0x14), // group0 (IELSR[0, 8, 16, 24])
    ICU_EVENT_SPI0_RXI_GROUP4               = (0x14), // group4 (IELSR[4, 12, 20, 28])
    ICU_EVENT_SPI0_TEI_GROUP2               = (0x11), // group2 (IELSR[2, 10, 18, 26])
    ICU_EVENT_SPI0_TEI_GROUP6               = (0x11), // group6 (IELSR[6, 14, 22, 30])
    ICU_EVENT_SPI0_TXI_GROUP1               = (0x11), // group1 (IELSR[1, 9, 17, 25])
    ICU_EVENT_SPI0_TXI_GROUP5               = (0x11), // group5 (IELSR[5, 13, 21, 29])
    ICU_EVENT_WDT_UNDERFLOW_GROUP0          = (0x06), // group0 (IELSR[0, 8, 16, 24])
    ICU_EVENT_WDT_UNDERFLOW_GROUP4          = (0x06), // group4 (IELSR[4, 12, 20, 28])
    ICU_EVENT_ACMPHS0_INT                   = (0x09), // DEPRECATED, do not use
    ICU_EVENT_ACMPHS1_INT                   = (0x07), // DEPRECATED, do not use
    ICU_EVENT_ADC0_COMPARE_MATCH            = (0x08), // DEPRECATED, do not use
    ICU_EVENT_ADC0_COMPARE_MISMATCH         = (0x06), // DEPRECATED, do not use
    ICU_EVENT_ADC0_SCAN_END                 = (0x07), // DEPRECATED, do not use
    ICU_EVENT_ADC0_SCAN_END_B               = (0x05), // DEPRECATED, do not use
    ICU_EVENT_ADC0_WINDOW_A                 = (0x05), // DEPRECATED, do not use
    ICU_EVENT_ADC0_WINDOW_B                 = (0x05), // DEPRECATED, do not use
    ICU_EVENT_AGT0_COMPARE_A                = (0x16), // DEPRECATED, do not use
    ICU_EVENT_AGT0_COMPARE_B                = (0x13), // DEPRECATED, do not use
    ICU_EVENT_AGT0_INT                      = (0x11), // DEPRECATED, do not use
    ICU_EVENT_AGT1_COMPARE_A                = (0x03), // DEPRECATED, do not use
    ICU_EVENT_AGT1_COMPARE_B                = (0x03), // DEPRECATED, do not use
    ICU_EVENT_AGT1_INT                      = (0x05), // DEPRECATED, do not use
    ICU_EVENT_CAC_FREQUENCY_ERROR           = (0x0B), // DEPRECATED, do not use
    ICU_EVENT_CAC_MEASUREMENT_END           = (0x08), // DEPRECATED, do not use
    ICU_EVENT_CAC_OVERFLOW                  = (0x08), // DEPRECATED, do not use
    ICU_EVENT_CGC_MOSC_STOP                 = (0x14), // DEPRECATED, do not use
    ICU_EVENT_DOC_INT                       = (0x0A), // DEPRECATED, do not use
    ICU_EVENT_DTC_COMPLETE                  = (0x02), // DEPRECATED, do not use
    ICU_EVENT_ELC_SOFTWARE_EVENT_0          = (0x0A), // DEPRECATED, do not use
    ICU_EVENT_ELC_SOFTWARE_EVENT_1          = (0x0A), // DEPRECATED, do not use
    ICU_EVENT_FCU_FRDYI                     = (0x02), // DEPRECATED, do not use
    ICU_EVENT_GPT0_AD_TRIG_A                = (0x20), // DEPRECATED, do not use
    ICU_EVENT_GPT0_AD_TRIG_B                = (0x20), // DEPRECATED, do not use
    ICU_EVENT_GPT0_CAPTURE_COMPARE_A        = (0x0E), // DEPRECATED, do not use
    ICU_EVENT_GPT0_CAPTURE_COMPARE_B        = (0x0D), // DEPRECATED, do not use
    ICU_EVENT_GPT0_COMPARE_C                = (0x0C), // DEPRECATED, do not use
    ICU_EVENT_GPT0_COMPARE_D                = (0x0C), // DEPRECATED, do not use
    ICU_EVENT_GPT0_COMPARE_E                = (0x20), // DEPRECATED, do not use
    ICU_EVENT_GPT0_COMPARE_F                = (0x20), // DEPRECATED, do not use
    ICU_EVENT_GPT0_COUNTER_OVERFLOW         = (0x0F), // DEPRECATED, do not use
    ICU_EVENT_GPT0_COUNTER_UNDERFLOW        = (0x0E), // DEPRECATED, do not use
    ICU_EVENT_GPT0_PC                       = (0x21), // DEPRECATED, do not use
    ICU_EVENT_GPT1_AD_TRIG_A                = (0x21), // DEPRECATED, do not use
    ICU_EVENT_GPT1_AD_TRIG_B                = (0x21), // DEPRECATED, do not use
    ICU_EVENT_GPT1_CAPTURE_COMPARE_A        = (0x19), // DEPRECATED, do not use
    ICU_EVENT_GPT1_CAPTURE_COMPARE_B        = (0x16), // DEPRECATED, do not use
    ICU_EVENT_GPT1_COMPARE_C                = (0x14), // DEPRECATED, do not use
    ICU_EVENT_GPT1_COMPARE_D                = (0x12), // DEPRECATED, do not use
    ICU_EVENT_GPT1_COMPARE_E                = (0x22), // DEPRECATED, do not use
    ICU_EVENT_GPT1_COMPARE_F                = (0x22), // DEPRECATED, do not use
    ICU_EVENT_GPT1_COUNTER_OVERFLOW         = (0x18), // DEPRECATED, do not use
    ICU_EVENT_GPT1_COUNTER_UNDERFLOW        = (0x15), // DEPRECATED, do not use
    ICU_EVENT_GPT1_PC                       = (0x22), // DEPRECATED, do not use
    ICU_EVENT_GPT2_AD_TRIG_A                = (0x23), // DEPRECATED, do not use
    ICU_EVENT_GPT2_AD_TRIG_B                = (0x23), // DEPRECATED, do not use
    ICU_EVENT_GPT2_CAPTURE_COMPARE_A        = (0x10), // DEPRECATED, do not use
    ICU_EVENT_GPT2_CAPTURE_COMPARE_B        = (0x0F), // DEPRECATED, do not use
    ICU_EVENT_GPT2_COMPARE_C                = (0x0D), // DEPRECATED, do not use
    ICU_EVENT_GPT2_COMPARE_D                = (0x0D), // DEPRECATED, do not use
    ICU_EVENT_GPT2_COMPARE_E                = (0x22), // DEPRECATED, do not use
    ICU_EVENT_GPT2_COMPARE_F                = (0x22), // DEPRECATED, do not use
    ICU_EVENT_GPT2_COUNTER_OVERFLOW         = (0x0E), // DEPRECATED, do not use
    ICU_EVENT_GPT2_COUNTER_UNDERFLOW        = (0x0E), // DEPRECATED, do not use
    ICU_EVENT_GPT2_PC                       = (0x23), // DEPRECATED, do not use
    ICU_EVENT_GPT3_AD_TRIG_A                = (0x21), // DEPRECATED, do not use
    ICU_EVENT_GPT3_AD_TRIG_B                = (0x21), // DEPRECATED, do not use
    ICU_EVENT_GPT3_CAPTURE_COMPARE_A        = (0x19), // DEPRECATED, do not use
    ICU_EVENT_GPT3_CAPTURE_COMPARE_B        = (0x16), // DEPRECATED, do not use
    ICU_EVENT_GPT3_COMPARE_C                = (0x15), // DEPRECATED, do not use
    ICU_EVENT_GPT3_COMPARE_D                = (0x12), // DEPRECATED, do not use
    ICU_EVENT_GPT3_COMPARE_E                = (0x24), // DEPRECATED, do not use
    ICU_EVENT_GPT3_COMPARE_F                = (0x24), // DEPRECATED, do not use
    ICU_EVENT_GPT3_COUNTER_OVERFLOW         = (0x1A), // DEPRECATED, do not use
    ICU_EVENT_GPT3_COUNTER_UNDERFLOW        = (0x17), // DEPRECATED, do not use
    ICU_EVENT_GPT3_PC                       = (0x24), // DEPRECATED, do not use
    ICU_EVENT_GPT_UVWEDGE                   = (0x11), // DEPRECATED, do not use
    ICU_EVENT_ICU_IRQ0                      = (0x01), // DEPRECATED, do not use
    ICU_EVENT_ICU_IRQ1                      = (0x01), // DEPRECATED, do not use
    ICU_EVENT_ICU_IRQ2                      = (0x01), // DEPRECATED, do not use
    ICU_EVENT_ICU_IRQ3                      = (0x01), // DEPRECATED, do not use
    ICU_EVENT_ICU_IRQ4                      = (0x16), // DEPRECATED, do not use
    ICU_EVENT_ICU_IRQ5                      = (0x13), // DEPRECATED, do not use
    ICU_EVENT_ICU_IRQ6                      = (0x13), // DEPRECATED, do not use
    ICU_EVENT_ICU_IRQ7                      = (0x11), // DEPRECATED, do not use
    ICU_EVENT_ICU_SNOOZE_CANCEL             = (0x03), // DEPRECATED, do not use
    ICU_EVENT_IIC0_ERI                      = (0x06), // DEPRECATED, do not use
    ICU_EVENT_IIC0_RXI                      = (0x0A), // DEPRECATED, do not use
    ICU_EVENT_IIC0_TEI                      = (0x06), // DEPRECATED, do not use
    ICU_EVENT_IIC0_TXI                      = (0x08), // DEPRECATED, do not use
    ICU_EVENT_IIC0_WUI                      = (0x0B), // DEPRECATED, do not use
    ICU_EVENT_IOPORT_EVENT_1                = (0x15), // DEPRECATED, do not use
    ICU_EVENT_IOPORT_EVENT_2                = (0x13), // DEPRECATED, do not use
    ICU_EVENT_IWDT_UNDERFLOW                = (0x03), // DEPRECATED, do not use
    ICU_EVENT_KEY_INT                       = (0x18), // DEPRECATED, do not use
    ICU_EVENT_LPM_SNOOZE_REQUEST            = (0x02), // DEPRECATED, do not use
    ICU_EVENT_LVD_LVD1                      = (0x04), // DEPRECATED, do not use
    ICU_EVENT_LVD_LVD2                      = (0x02), // DEPRECATED, do not use
    ICU_EVENT_POEG0_EVENT                   = (0x0B), // DEPRECATED, do not use
    ICU_EVENT_POEG1_EVENT                   = (0x0B), // DEPRECATED, do not use
    ICU_EVENT_SCI0_AM                       = (0x13), // DEPRECATED, do not use
    ICU_EVENT_SCI0_ERI                      = (0x0F), // DEPRECATED, do not use
    ICU_EVENT_SCI0_RXI                      = (0x12), // DEPRECATED, do not use
    ICU_EVENT_SCI0_TEI                      = (0x0F), // DEPRECATED, do not use
    ICU_EVENT_SCI0_TXI                      = (0x10), // DEPRECATED, do not use
    ICU_EVENT_SCI1_AM                       = (0x1A), // DEPRECATED, do not use
    ICU_EVENT_SCI1_ERI                      = (0x19), // DEPRECATED, do not use
    ICU_EVENT_SCI1_RXI                      = (0x1E), // DEPRECATED, do not use
    ICU_EVENT_SCI1_TEI                      = (0x1B), // DEPRECATED, do not use
    ICU_EVENT_SCI1_TXI                      = (0x1B), // DEPRECATED, do not use
    ICU_EVENT_SCI2_AM                       = (0x1C), // DEPRECATED, do not use
    ICU_EVENT_SCI2_ERI                      = (0x19), // DEPRECATED, do not use
    ICU_EVENT_SCI2_RXI                      = (0x1D), // DEPRECATED, do not use
    ICU_EVENT_SCI2_TEI                      = (0x1C), // DEPRECATED, do not use
    ICU_EVENT_SCI2_TXI                      = (0x1B), // DEPRECATED, do not use
    ICU_EVENT_SCI9_AM                       = (0x1B), // DEPRECATED, do not use
    ICU_EVENT_SCI9_ERI                      = (0x1A), // DEPRECATED, do not use
    ICU_EVENT_SCI9_RXI                      = (0x1E), // DEPRECATED, do not use
    ICU_EVENT_SCI9_TEI                      = (0x1E), // DEPRECATED, do not use
    ICU_EVENT_SCI9_TXI                      = (0x1C), // DEPRECATED, do not use
    ICU_EVENT_SPI0_ERI                      = (0x10), // DEPRECATED, do not use
    ICU_EVENT_SPI0_IDLE                     = (0x10), // DEPRECATED, do not use
    ICU_EVENT_SPI0_RXI                      = (0x14), // DEPRECATED, do not use
    ICU_EVENT_SPI0_TEI                      = (0x11), // DEPRECATED, do not use
    ICU_EVENT_SPI0_TXI                      = (0x11), // DEPRECATED, do not use
    ICU_EVENT_WDT_UNDERFLOW                 = (0x06), // DEPRECATED, do not use
} icu_event_t;

#define BSP_PRV_VECT_ENUM(event, group)  (ICU_ ## event ## _ ## group)

#define ELC_PERIPHERAL_NUM    (16U)
#define BSP_OVERRIDE_ELC_PERIPHERAL_T
/** Possible peripherals to be linked to event signals
 * @note This list is device specific.
 * */
typedef enum e_elc_peripheral
{
    ELC_PERIPHERAL_GPT_A         = (0),
    ELC_PERIPHERAL_GPT_B         = (1),
    ELC_PERIPHERAL_GPT_C         = (2),
    ELC_PERIPHERAL_GPT_D         = (3),
    ELC_PERIPHERAL_GPT_E         = (4),
    ELC_PERIPHERAL_GPT_F         = (5),
    ELC_PERIPHERAL_GPT_G         = (6),
    ELC_PERIPHERAL_GPT_H         = (7),
    ELC_PERIPHERAL_ADC0          = (8),
    ELC_PERIPHERAL_ADC0_B        = (9),
    ELC_PERIPHERAL_IOPORT1       = (14),
    ELC_PERIPHERAL_IOPORT2       = (15)
} elc_peripheral_t;

/** Positions of event link set registers (ELSRs) available on this MCU */
#define BSP_ELC_PERIPHERAL_MASK  (0x0000C3FFU)

/* UNCRUSTIFY-ON */
/** @} (end addtogroup BSP_MCU_RA2T1) */

#endif
