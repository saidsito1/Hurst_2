/******************************************************************************
 * watchdog_timer.h
 *
 * DESCRIPTION
 * -----------
 * Defines Renesas A/D Converter
 * VERSION
 * -------
 * $Revision: 1 $
 * $Author: Said.Zandian$
 * $Date: 2024-02_10 $
 *
 ******************************************************************************/
#pragma once

#include "bit_types.h"
#include "dmac_module.h"
//    b7      b6      b5      b4      b3      b2      b1      b0       
// —————————————————————————————————————————————————————————————————
// | ————— | ————— | ————— | ————— | ————— | ————— | ————— | ————— |
// —————————————————————————————————————————————————————————————————
//    0        0       0       00       0       0       0        value after reset

//    b15     b14     b13     b12     b11     b10      b9     b8       b7      b6      b5      b4      b3      b2      b1     b0
// ————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————
// | ————— | ————— | ————— | ————— | ————— | ————— | ————— | ————— | ————— | ————— | ————— | ————— | ————— | ————— | ————— |————— |
// ————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————
//    0        0       0       0       0       0       0       0       0       0       0       0       0       0       0      0     value after reset




// 30.2.1 A/D Data Register y (ADDRy: y = 0 to 7),
// A/D Data Duplication Register (ADDBLDR),
// A/D Data Duplication Register A (ADDBLDRA),
// A/D Data Duplication Register B (ADDBLDRB)
// The ADDRy registers (y = 0 to 7) are 16-bit read-only registers for storing the result of A/D conversion. Register
// ADDBLDR is a 16-bit read-only register for storing the result of A/D conversion in response to the second trigger in
// double trigger mode. Registers ADDBLDRA and ADDBLDRB are 16-bit read-only registers for storing the result of
// A/D conversion during extended operation in double trigger mode.
// The formats for data in the ADDRy, ADDBLDR, ADDBLDRA, and ADDBLDRB registers vary according to the
// following conditions.
// • The setting of the A/D data register format select bit (determining whether the data are flush-left or flush-right in the
// registers)
// • The setting of the A/D conversion-accuracy selection bits (8-, 10-, or 12-bit)
// • The setting of the A/D-Converted Value Addition/Average Count Select Register (A/D conversion count, A/D
// converted value average mode is selected or not selected)
// The data formats (section 30.2.23, Data Format, (1) to (9)) for each given condition are shown below.

typedef union 
{
    UINT16              data_16_bits;
     
    UINT16_8_BITS       data_8_bits_R;              // 8 bits data Right justified

    UINT16_8_BITS_L     data_8_bits_L;              // 8 bits data Left justified
    
    UINT16_10_BITS      data_10_bits_R;             // 10 bits data Right justified

    UINT16_10_BITS_L    data_10_bits_L;             // 10 bits data Left justified
 
    UINT16_12_BITS      data_12_bits_R;             // 12 bits data Right justified

    UINT16_12_BITS_L    data_12_bits_L;             // 12 bits data Left justified

    UINT16_14_BITS      data_14_bits_R;             // 14 bits data Right justified

    UINT16_14_BITS_L    data_14_bits_L;             // 14 bits data Left justified

} A2D_DATA_REG ,A2D_DATA_DUPLICATION_REG, A2D_DATA_DUPLICATION_REG_A, A2D_DATA_DUPLICATION_REG_B; //


// 30.2.2 A/D Self-Diagnosis Data Register (ADRD)
// ADRD is a 16-bit read-only register that holds the A/D conversion results based on the A/D converter’s self-diagnosis. In
// addition to the AD bit indicating A/D-converted value, the self-diagnosis status bit (DIAGST) is included in. In the
// ADRD register, the following different formats are used depending on the conditions below.
// • The setting of the A/D data register format select bit (determining whether the data are flush-left or flush-right in the
// registers)
// • The setting of the A/D conversion-accuracy selection bits (ADCER.ADPRC[1:0]) (8-, 10-, or 12-bit)
// The A/D-converted value addition mode and A/D-converted value average mode cannot be applied to the A/D selfdiagnosis
// function. For details of self-diagnosis, see section 30.2.9, A/D Control Extended Register (ADCER).
// The settings for flush-right data
// DIAGST[1:0] is allocated to the upper two bits (b15, b14). The A/D conversion result is allocated to the bit position b13
// to b0 depending on the setting of the A/D conversion accuracy specify bits.

typedef union
{
    UINT16                  data;

    USHORT_BITS_14_15       DIAGST_L;       // Self-        b15 b14
                                            // Diagnosis    0   0: Self-diagnosis has never been executed since power-on.
                                            // Status       0   1: Self-diagnosis using the voltage of 0 V has been executed.
                                            //              1   0: Self-diagnosis using the voltage of reference power supply × 1/2 has been executed.
                                            //              1   1: Self-diagnosis using the voltage of reference power supply has been executed. 
    UINT16_8_BITS           data_8_bits_R;              // 8 bits data Right justified

    UINT16_10_BITS          data_10_bits_R;             // 10 bits data Right justified

    UINT16_12_BITS          data_12_bits_R;             // 12 bits data Right justified
                                            
    USHORT_BITS_0_1         DIAGST_R;       // Self-        b1  b0
                                            // Diagnosis    0   0: Self-diagnosis has never been executed since power-on.
                                            // Status       0   1: Self-diagnosis using the voltage of 0 V has been executed.
                                            //              1   0: Self-diagnosis using the voltage of reference power supply × 1/2 has been executed.
                                            //              1   1: Self-diagnosis using the voltage of reference power supply has been executed.   

    UINT16_8_BITS_L         data_8_bits_L;              // 8 bits data Left justified

    UINT16_10_BITS_L        data_10_bits_L;             // 10 bits data Left justified

    UINT16_12_BITS_L        data_12_bits_L;             // 12 bits data Left justified

} A2D_SELF_DIAGNOSIS_DATA_REG;       // ADRD


// 30.2.3 A/D Control Register (ADCSR)
// ADCSR sets A/D conversion control, mode/trigger/interrupt.

// b15    b14 b13      b12  b11 b10   b9     b8      b7      b6   b5   b4 b3 b2 b1 b0
//____________________________________________________________________________________
//| ADST| ADCS[1:0] | ADIE | — | — | TRGE | EXTRG | DBLE | GBADIE| — |  DBLANS[4:0]  |
//------------------------------------------------------------------------------------
//   0     0   0       0     0   0     0      0      0       0     0    0  0  0  0  0     value after reset

typedef union 
{
    UINT16                  data;

    UINT16_BIT_15           ADST;           // A/D Conversion Start 0: Stops A/D conversion process
                                            //                      1: Starts A/D conversion process

    UINT16_BITS_13_14       ADCS;           // Scan Mode Select 00: Single scan mode
                                            //                  01: Group scan mode
                                            //                  10: Continuous scan mode
                                            //                  11: Setting prohibited

    UINT16_BIT_12           ADIE;           // Scan End Interrupt Enable    0: Disables S12ADI0 interrupt generation upon scan completion.
                                            //                              1: Enables S12ADI0 interrupt generation upon scan completion.

    UINT16_BIT_9            TRGE;           // Trigger Start Enable 0: Disables A/D conversion to be started by the synchronous or
                                            //                         asynchronous trigger.
                                            //                      1: Enables A/D conversion to be started by the synchronous or
                                            //                         asynchronous trigger.

    UINT16_BIT_8            EXTRG;          // Trigger Select*1 0: A/D conversion is started by a synchronous trigger (MTU, GPT).
                                            //                  1: A/D conversion is started by the asynchronous trigger (ADTRG#).

    UINT16_BIT_7            DBLE;           // Double Trigger Mode Select   0: Deselects double trigger mode.
                                            //                              1: Selects double trigger mode.

    UINT16_BIT_6            GBADIE;         // Group B Scan End Interrupt   0: Disables S12GBADI0 interrupt generation upon group B scan
                                            // Enable                          completion.
                                            //                              1: Enables S12GBADI0 interrupt generation upon group B scan
                                            //                                 completion.

    USHORT_BITS_0_4         DBLANS;         // A/D Conversion Data              These bits select one analog input channel for which to duplicate A/D
                                            // Duplication Channel Select       conversion data. The setting is only effective while double trigger mode
                                            // Double Trigger Channel           is selected.
                                            // Select                           These bits select one analog input channel for double triggered
                                            //                                  operation. The setting is only effective while double trigger mode is
                                            //                                  selected.

} A2D_CONTROL_REG; // ADCSR

// Note 1. Starting A/D conversion using an external pin (asynchronous trigger)
// After a high-level signal is input to the external pin (ADTRG#), write 1 to both the TRGE and EXTRG bits in ADCSR and change
// the signals of ADTRG# to the low level. Thus the falling edge of ADTRG# are detected and the scan conversion process is
// started. In this case, the pulse width of the low-level input must be at least 1.5 clock cycles of PCLK.
// Note 2. See the following description of the ADST bit. 


// 30.2.4 A/D Channel Select Register A0 (ADANSA0)
// ADANSA0 selects analog input channels for A/D conversion among AN000 to AN007. In group scan mode, this register
// selects group A channels.

// 30.2.5 A/D Channel Select Register B0 (ADANSB0)
// ADANSB0 selects analog input channels for A/D conversion among AN000 to AN007 in group B when group scan
// mode is selected. The ADANSB0 register is not used in any scan mode other than group scan mode.

// 30.2.6 A/D Channel Select Register C0 (ADANSC0)
// ADANSC0 selects analog input channels for A/D conversion among AN000 to AN007 in group C when group scan
// mode is selected. The ADANSC0 register is not used in any scan mode other than group scan mode.


// b15  b14 b13 b12 b11 b10  b9  b8  b7 b6 b5 b4 b3 b2 b1 b0
// __________________________________________________________
// | — | — | — | — | — | — | — | — |       ANSA0[7:0]       |
// ----------------------------------------------------------
//   0   0   0   0   0   0   0   0   0  0  0  0  0  0  0  0     value after reset

typedef union 
{
    UINT16                  data;

    UINT16_8_BITS           ANSA0;      // A/D Conversion Channels Select 0: AN000 to AN007 are not subjected to conversion.
                                        //                                1: AN000 to AN007 are subjected to conversion.
} A2D_CHANNEL_SELECT_REG;


// 30.2.7 A/D-Converted Value Addition/Average Mode Select Register 0 (ADADS0)
// ADADS0 selects the channels AN000 to AN007 on which A/D conversion is performed successively for the specified
// number of times (The possible addition count depends on the conversion accuracy to be used. See Table 30.5 in section
// 30.2.1.) and then converted values are added (integrated) or averaged.

// b15  b14 b13 b12 b11 b10  b9  b8  b7 b6 b5 b4 b3 b2 b1 b0
// __________________________________________________________
// | — | — | — | — | — | — | — | — |       ADS0[7:0]        |
// ----------------------------------------------------------
//   0   0   0   0   0   0   0   0   0  0  0  0  0  0  0  0     value after reset

typedef union 
{
    UINT16                  data;

    UINT16_8_BITS           ADS0;       // A/D-Converted Value Addition/    0: A/D-converted value addition/average mode for AN000 to AN007
                                        // Average Channel Select              is not selected.
                                        //                                  1: A/D-converted value addition/average mode for AN000 to AN007
                                        //                                     is selected.

} A2D_CONVERTED_ADDITION_AVERAGE_MODE_SEL_REG_0;    // ADADS0


// 30.2.8 A/D-Converted Value Addition/Average Count Select Register (ADADC)
// ADADC sets the addition count and average count for A/D conversion of the channel for which A/D-converted value
// addition/average mode is selected, and selects either addition or average mode.
//   b8     b7 b6 b5 b4 b3  b2 b1 b0
// ___________________________________
// | AVEE | — | — | — | — | ADC[2:0] |
// -----------------------------------
//    0     0   0   0   0   0   0   0      value after reset


typedef union
{
    UINT8                   data;

    UINT8_BIT_7             AVEE;       // Average Mode Enable      0: Addition mode is selected.*1
                                        //                          1: Average mode is selected.*1

    UINT8_BITS_0_2          ADC;        // Addition Count Select    b2 b1 b0
                                        //                          0  0  0: 1-time conversion (no addition; same as normal conversion)
                                        //                          0  0  1: 2-time conversion (addition once)
                                        //                          0  1  0: 3-time conversion (addition twice)*1
                                        //                          0  1  1: 4-time conversion (addition three times)
                                        //                          1  0  1: 16-time conversion (addition 15 times)
                                        //                        
                                        //                          Other settings are prohibited.
} A2D_CONVERTED_ADDITION_AVERAGE_COUNT_SEL_REG;     // ADADC



// 30.2.9 A/D Control Extended Register (ADCER)
// The ADCER register sets the A/D data register, A/D conversion accuracy, and self-diagnosis conversion.

//    b15    b14 b13 b12  b11      b10       b9  b8      b7  b6   b5   b4  b3     b2 b1     b0
// —————————————————————————————————————————————————————————————————————————————————————————————
// | ADRFMT | — | — | — | DIAGM | DIAGLD | DIAGVAL[1:0] | — | — | ACE | — | — | ADPRC[1:0] | — |
// —————————————————————————————————————————————————————————————————————————————————————————————
//     0      0   0   0     0       0        0   0        0   0    0    0   0     0  0       0     value after reset

typedef union 
{
    UINT16                  data;

    UINT16_BIT_15           ADRFMT;     // A/D Data Register            0: Right-alignment is selected for the A/D data register format.
                                        // Format Select                1: Left-alignment is selected for the A/D data register format.

    UINT16_BIT_11           DIAGM;      // Self-Diagnosis Enable        0: Disables self-diagnosis of A/D converter.
                                        //                              1: Enables self-diagnosis of A/D converter.

    UINT16_BIT_10           DIAGLD;     // Self-Diagnosis Mode Select   0: Rotation mode for self-diagnosis voltage
                                        //                              1: Fixed mode for self-diagnosis voltage

    UINT16_BITS_8_9         DIAGVAL;    // Self-Diagnosis Conversion    b9 b8
                                        // Voltage Select               0  0: Setting prohibited when self-diagnosis is enabled
                                        //                              0  1: Uses the voltage of 0 V for self-diagnosis.
                                        //                              1  0: Uses the voltage of reference power supply × 1/2 for selfdiagnosis.
                                        //                              1  1: Uses the voltage of reference power supply for selfdiagnosis.

    UINT16_BIT_5            ACE;        // A/D Data Register            0: Disables automatic clearing.
                                        // Automatic Clearing Enable    1: Enables automatic clearing.

    UINT16_BITS_1_2         ADPRC;      // A/D Conversion               b2 b1
                                        // Accuracy Specify             0  0: A/D conversion is performed with 12-bit accuracy.
                                        //                              0  1: A/D conversion is performed with 10-bit accuracy.
                                        //                              1  0: A/D conversion is performed with 8-bit accuracy.
                                        //                              1  1: Setting is prohibited.

} A2D_CONTROL_EXTENDED_REG;     // ADCER

// 30.2.10 A/D Start Trigger Select Register (ADSTRGR)
// ADSTRGR selects the A/D conversion start trigger.

//  b15 b14  b13  b12  b11  b10  b9  b8  b7  b6  b5  b4  b3  b2  b1  b0
// ——————————————————————————————————————————————————————————————————————
// | — | — |        TRSA[5:0]           | — | — |       TRSB[5:0]       |
// ——————————————————————————————————————————————————————————————————————
//   0   0    0    0   0    0    0   0    0   0   0   0   0  0   0   0     value after reset

typedef union 
{
    UINT16                  data;

    UINT16_BITS_8_13        TRSA;       // A/D Conversion Start Trigger     Select the A/D conversion start trigger in single scan mode and
                                        // Select                           continuous mode. In group scan mode, the A/D conversion start
                                        //                                  trigger for group A is selected.

    UINT16_BITS_0_5         TRSB;       // A/D Conversion Start Trigger     Select the A/D conversion start trigger for group B in group scan
                                        // Select for Group B               mode.

} A2D_START_TRIGGER_SEL_REG;    // ADSTRGR


// 30.2.11 A/D Group C Trigger Select Register (ADGCTRGR)
// The ADGCTRGR register enables the operation of group C and selects the A/D conversion start trigger. For details about
// the setting of group priority control, see section 30.3.4.3, Group Priority Control.

//   b7       b6    b5  b4  b3  b2  b1  b0
// —————————————————————————————————————————
// | GRCE | GCADIE |       TRSC[5:0]       |
// —————————————————————————————————————————
//    0       0      0   0   0  0   0   0        value after reset

typedef union 
{
    UINT8                   data;

    UINT8_BIT_7             GRCE;       // Group C Dedicated A/D            Sets whether to enable A/D conversion operation of group C.
                                        // Conversion Operation             0: Do not use group C.
                                        // Enable                           1: Use group C.

    UINT8_BIT_6             GCADIE;     // Group C Scan End                 0: Disables S12GCADI0 interrupt generation upon group C scan completion.
                                        // Interrupt Enable                 1: Enables S12GCADI0 interrupt generation upon group C scan completion.

    UINT8_BITS_0_5          TRSC;       // A/D Conversion Start             Select the A/D conversion start trigger for group C in group scan mode.
                                        // Trigger Select for Group C

} A2D_GROUP_C_TRIGGER_SELECT_REG;      // ADGCTRGR


// 30.2.12 A/D Sampling State Register n (ADSSTRn) (n = 0 to 7)
// The ADSSTRn register sets the sampling time for analog input.

//   b7  b6  b5  b4  b3  b2  b1  b0
// —————————————————————————————————
// |            SST[7:0]           |
// —————————————————————————————————
//   0   0   0   0   0   0   0   0        value after reset

typedef union 
{
    UINT8                   data;

    UINT8                   SST;        // Sampling Time Setting            These bits set the sampling time in the range from 5 to 255 states.

} A2D_SAMPLING_STATE_REG;      // ADSSTRn


// 30.2.13 A/D Disconnection Detection Control Register (ADDISCR)
// ADDISCR sets the disconnection detection assist function.

//   b7  b6  b5  b4  b3  b2  b1  b0
// —————————————————————————————————
// | — | — | — |   ADNDIS[4:0]     |
// —————————————————————————————————
//   0   0   0   0   0   0   0   0        value after reset

typedef union 
{
    UINT8                   data;

    UINT8_BITS_0_4          ADNDIS;     // Disconnection Detection Assist   Disconnection detection assist function is set.
                                        // Setting                          b4 ADNDIS[4]: Setting precharge or discharge
                                        //                                  0: discharge
                                        //                                  1: precharge
                                        //                                  b3 to b0 ADNDIS[3:0]: Setting the period of precharge or discharge

} A2D_DISCONNECTION_DETECTION_CONTROL_REG;      // ADDISCR


// 30.2.14 A/D Group Scan Priority Control Register (ADGSPCR)
// The ADGSPCR register sets priority control to interrupt scanning for a low priority group in group scan mode and
// execute scan for a priority group.
// For details about the setting of group priority control, see section 30.3.4.3, Group Priority Control.

//  b15      b14   b13 b12 b11 b10 b9  b8  b7  b6  b5  b4  b3  b2    b1      b0
// ———————————————————————————————————————————————————————————————————————————————
// | GBRP | LGRRS | — | — | — | — | — | — | — | — | — | — | — | — | GBRSCN | PGS |
// ———————————————————————————————————————————————————————————————————————————————
//    0       0     0   0   0   0   0   0   0   0   0   0   0   0     0       0     value after reset

typedef union 
{
    UINT16                  data;

    UINT16_BIT_15           GBRP;       // Single Scan Continuous       (Enabled only when PGS = 1. Reserved when PGS = 0.)
                                        // Start*2                      0: Single scan is not continuously activated.
                                        //                              1: Single scan for the lowest priority group is continuously activated.

    UINT16_BIT_14           LGRRS;      // Restart Channel              (Enabled only when PGS = 1 and GBRSCN = 1. Reserved when PGS = 0
                                        // Select                       or GBRSCN = 0.)
                                        //                              0: Rescan is performed from the first channel of the scan.
                                        //                              1: Rescan is performed from the channel on which A/D conversion has not
                                        //                                 completed.

    UINT16_BIT_1            GBRSCN;     // Low Priority Group           (Enabled only when PGS = 1. Reserved when PGS = 0.)
                                        // Restart                      0: Scanning for group is not restarted after having been discontinued due
                                        // Setting                         to group priority control.
                                        //                              1: Scanning for group is restarted after having been discontinued due to
                                        //                                 group priority control. 

    UINT16_BIT_0            PGS;        // Group Priority Control       0: Operation is without group A priority control
                                        // Setting*1                    1: Operation is with group A priority contro

} A2D_GROUP_SCAN_PRIORITY_CONTROL_REG;  // ADGSPCR


// 30.2.15 A/D Compare Control Register (ADCMPCR)
// ADCMPCR is used to set compare window A/B operation.

//     b15    b14       b13   b12   b11   b10    b9   b8  b7  b6  b5  b4  b3  b2  b1  b0
// ———————————————————————————————————————————————————————————————————————————————————————
// | CMPAIE | WCMPE | CMPBIE | — | CMPAE | — | CMPBE | — | — | — | — | — | — | — | — | — |
// ———————————————————————————————————————————————————————————————————————————————————————
//    0         0       0      0     0     0     0     0   0   0   0   0   0   0   0   0     value after reset

typedef union
{
    ushort                  data;
    
    UINT16_BIT_15           CMPAIE;     // Compare A                    0: Generation of an S12ADCMPAI0 interrupt in response to matches with a
                                        // Interrupt Enable                condition for comparison (Window A) is disabled.
                                        //                              1: Generation of an S12ADCMPAI0 interrupt in response to matches with a
                                        //                                 condition for comparison (Window A) is enabled.

    UINT16_BIT_14           WCMPE;      // Window Function              0: Window function disabled
                                        // Setting                         Window A and B operate as a comparator to compare the single value on
                                        //                                 the lower side with the A/D conversion result.
                                        //                              1: Window function enabled
                                        //                                 Window A and B operate as a window comparator to compare the two
                                        //                                 values on the upper and lower sides with the A/D conversion result.

    UINT16_BIT_13           CMPBIE;     // Compare B 
                                        // Interrupt Enable             0: Generation of an S12ADCMPBI0 interrupt in response to matches with a
                                        //                                 condition for comparison (Window B) is disabled.
                                        //                              1: Generation of an S12ADCMPBI0 interrupt in response to matches with a
                                        //                                 condition for comparison (Window B) is enabled.

    UINT16_BIT_11           CMPAE;      // Compare Window A 
                                        // Operation Enable             0: Compare Window A disabled
                                        //                              1: Compare Window A enabled

    UINT16_BIT_9            CMPBE;      // Compare Window B             0: Compare Window B disabled
                                        // Operation Enable             1: Compare Window B enabled

} A2D_COMPARE_CONTROL_REG;      // (ADCMPCR)


// 30.2.16 A/D Compare Function Window-A Channel Selection Register 0 (ADCMPANSR0)
// ADCMPANSR0 selects analog input channels for comparison from among AN000 to AN007 in the compare window A
// condition.

//    b15     b14     b13     b12     b11     b10      b9     b8       b7     b6     b5     b4     b3     b2     b1    b0
// —————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————
// | ————— | ————— | ————— | ————— | ————— | ————— | ————— | ————— |                   CMPCHA0[7:0]                         |
// ——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————
//    0        0       0       0       0       0       0       0       0      0       0      0      0      0      0     0     value after reset

typedef union
{
    ushort                  data;

    UINT16_8_BITS           CMPCHA0;    // Compare Window A             0: The corresponding channel from among AN000 to AN007 is not a
                                        // Channel Select                  target for the compare Window A.
                                        //                              1: The corresponding channel from among AN000 to AN007 is a target
                                        //                                 for the compare Window A.

} A2D_COMPARE_FUNCTION_WINDOW_A_CHANNEL_SEL_REG;    // ADCMPANSR0


// 30.2.17 A/D Compare Function Window-A Comparison Condition Setting Register 0 (ADCMPLR0)
// The ADCMPLR0 register sets the condition for use in comparing the values of the ADCMPDR0 and ADCMPDR1
// registers with results of A/D conversion.
// Set the ADCMPLR0 register while ADCSR.ADST is 0.

//    b15     b14     b13     b12     b11     b10      b9     b8       b7     b6     b5     b4     b3     b2     b1    b0
// —————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————
// | ————— | ————— | ————— | ————— | ————— | ————— | ————— | ————— |                   CMPLCHA0[7:0]                       |
// —————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————
//    0        0       0       0       0       0       0       0       0      0       0      0      0      0      0     0     value after reset

typedef union
{
    ushort                  data;

    UINT16_8_BITS           CMPLCHA0;   // Compare window A             Set the condition for comparison with the selected channels from among
                                        // Compare Level Select         AN000 to AN007 under the compare window A condition.
                                        //                              Compare conditions are shown in Table 30.11.
                                        //                              When Window function is disabled (ADCMPCR.WCMPE = 0):
                                        //                              0: ADCMPDR0 register value > A/D-converted value
                                        //                              1: ADCMPDR0 register value < A/D-converted value
        
                                        //                              When Window function is enabled (ADCMPCR.WCMPE = 1):
                                        //                              0: AD-converted value < ADCMPDR0 register value or A/D-converted
                                        //                                 value > ADCMPDR1 register value
                                        //                              1: ADCMPDR0 register value < A/D-converted value < ADCMPDR1
                                        //                                 register value

} A2D_COMPARE_FUNCTION_WINDOW_A_COMPARISON_CONDITION_SETTING_REG_0; // ADCMPLR0


// 30.2.19 A/D Compare Function Window-A Channel Status Register 0 (ADCMPSR0)
// The ADCMPSR0 register sets the compare window A function.

//    b15     b14     b13     b12     b11     b10      b9     b8       b7     b6     b5     b4     b3     b2     b1    b0
// —————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————
// | ————— | ————— | ————— | ————— | ————— | ————— | ————— | ————— |                   CMPSTCHA0[7:0]                      |
// —————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————
//    0        0       0       0       0       0       0       0       0      0       0      0      0      0      0     0     value after reset

typedef union
{
    ushort                  data;

    UINT16_8_BITS           CMPSTCHA0;  // Compare Window-A             Indicates compare results of CH(AN000 to AN007) when window A is
                                        // Flag                         active (ADCMPCR.CMPAE = 1b).
                                        //                              0: Condition for comparison was not met.
                                        //                              1: Condition for comparison was met.
    
} A2D_COMPARE_FUNCTION_WINDOW_A_CHANNEL_STATUS_REG_0;   // ADCMPSR0


// 30.2.20 A/D Compare Function Window-B Channel Selection Register (ADCMPBNSR)
// The ADCMPBNSR register sets the compare window B function.

//    b7      b6      b5      b4      b3      b2      b1      b0  
// ————————————————————————————————————————————————————————————————
// | CMPLB | ————— |                 CMPSTCHA0[7:0]               |
// ————————————————————————————————————————————————————————————————
//    0        0       0       0       0       0       0       0        value after reset


typedef union
{
    UINT8                   data;

    UINT8_BIT_7             CMPLB;      // Compare Window B             Sets comparison conditions for channels for window B.
                                        // Compare Condition            Table 30.12 shows the compare conditions.
                                        // Setting                      When Window function is disabled (ADCMPCR.WCMPE bit = 0):
                                        //                              0: CMPLLB register value > A/D-converted value
                                        //                              1: CMPLLB register value < A/D-converted value
                            
                                        //                              When Window function is enabled (ADCMPCR.WCMPE bit = 1):
                                        //                              0: A/D-converted value < CMPLLB register value
                                        //                              or
                                        //                              CMPULB register value < A/D-converted value
                                        //                              1: CMPLLB register value < A/D-converted value < CMPULB register value

    UINT8_BITS_0_5          CMPCHB;     // Compare Window B             Selects a channel to be compared with the compare window B conditions.
                                        // Channel Select               6’b000000: AN000
                                        //                              6’b000001: AN001
                                        //                              6’b000010: AN002
                                        //                              to
                                        //                              6’b111111: Not selected
                                                // Note: Setting any value from 6’b001000 to 6’b111110 is prohibited.

} A2D_COMPARE_FUNCTION_WINDOW_B_CHANNEL_SEL_REG;    // (ADCMPBNSR)


// 30.2.21 A/D Compare Function Window-B Status Register (ADCMPBSR)
// The ADCMPBSR register stores the result of comparison by the compare window B function.

//    b7      b6      b5      b4      b3      b2      b1      b0       
// —————————————————————————————————————————————————————————————————
// | ————— | ————— | ————— | ————— | ————— | ————— | ————— | CMPSTB |
// —————————————————————————————————————————————————————————————————
//    0        0       0       0       0       0       0       0        value after reset

typedef union
{
    UINT8                   data;

    UINT8_BIT_0             CMPSTB;     // Compare Window-b             Indicates compare results of CH(AN000 to AN007) when window B is
                                        // Flag                         active (ADCMPCR.CMPBE = 1b).
                                        //                              0: Condition for comparison was not met.
                                        //                              1: Condition for comparison was met.
    
} A2D_COMPARE_FUNCTION_WINDOW_B_CHANNEL_STATUS_REG;   // ADCMPBSR


// 30.2.22 A/D Compare Function AB Status Monitor Register (ADWINMON)
// The ADWINMON register can be used to monitor comparison results and combination results.

//    b7      b6       b5        b4        b3      b2      b1      b0       
// ———————————————————————————————————————————————————————————————————————
// | ————— | ————— | MONCMPB | MONCMPA | ————— | ————— | ————— | MONCOMB |
// ———————————————————————————————————————————————————————————————————————
//    0        0         0        0        0       0       0       0        value after reset
typedef union
{
    UINT8                   data;

    UINT8_BIT_5             MONCMPB;    // Comparison Result            0: Window B comparison conditions are not met.
                                        // Monitor B                    1: Window B comparison conditions are met.

    UINT8_BIT_4             MONCMPA;    // Comparison Result            0: Window A comparison conditions are not met.
                                        // Monitor A                    1: Window A comparison conditions are met.

    UINT8_BIT_0             MONCOMB;    // Combination Result           Indicates the combination result.
                                        // Monitor                      This bit is valid while both window A and B are active.
                                        //                              0: Window A/B composite conditions are not met. 
                                        //                              1: Window A/B composite conditions are met.

} A2D_COMPARE_FUNCTION_AB_STATUS_MONITOR_REG;   // ADWINMON



typedef struct                                                          //             Address          Access size
{
    A2D_CONTROL_REG                                                     ADCSR;      // E800_5800h           16
    RSVD_UINT16(0);           
    A2D_CHANNEL_SELECT_REG                                              ADANSA0;    // E800_5804h           16
    RSVD_UINT16(1);
    A2D_CONVERTED_ADDITION_AVERAGE_MODE_SEL_REG_0                       ADADS0;     // E800_5808h           16
    RSVD_UINT16(2);           
    A2D_CONVERTED_ADDITION_AVERAGE_COUNT_SEL_REG                        ADADC;      // E800_580Ch           8
    A2D_CONTROL_EXTENDED_REG                                            ADCER;      // E800_580Eh           16
    A2D_START_TRIGGER_SEL_REG                                           ADSTRGR;    // E800_5810h           16
    RSVD_UINT16(3);
    A2D_CHANNEL_SELECT_REG                                              ADANSB0;    // E800_5814h           16
    RSVD_UINT16(4);
    A2D_DATA_DUPLICATION_REG                                            ADDBLDR;    // E800_5818h           16
    RSVD_UINT16_ARR(5, 2);
    A2D_SELF_DIAGNOSIS_DATA_REG                                         ADRD;       // E800_581Eh           16
    A2D_DATA_REG                                                        ADDR0;      // E800_5820h           16
    A2D_DATA_REG                                                        ADDR1;      // E800_5822h           16
    A2D_DATA_REG                                                        ADDR2;      // E800_5824h           16
    A2D_DATA_REG                                                        ADDR3;      // E800_5826h           16
    A2D_DATA_REG                                                        ADDR4;      // E800_5828h           16
    A2D_DATA_REG                                                        ADDR5;      // E800_582Ah           16
    A2D_DATA_REG                                                        ADDR6;      // E800_582Ch           16
    A2D_DATA_REG                                                        ADDR7;      // E800_582Eh           16
    RSVD_UINT8_ARR(6, 0x4A);
    A2D_DISCONNECTION_DETECTION_CONTROL_REG                             ADDISCR;    // E800_587Ah           8
    RSVD_UINT8_ARR(7, 0x5);
    A2D_GROUP_SCAN_PRIORITY_CONTROL_REG                                 ADGSPCR;    // E800_5880h           16
    RSVD_UINT16(8);
    A2D_DATA_DUPLICATION_REG_A                                          ADDBLDRA;   // E800_5884h           16
    A2D_DATA_DUPLICATION_REG_B                                          ADDBLDRB;   // E800_5886h           16
    RSVD_UINT8_ARR(9,4);
    A2D_COMPARE_FUNCTION_AB_STATUS_MONITOR_REG                          ADWINMON;   // E800_588Ch           8
    RSVD_UINT8_ARR(A,3);
    A2D_COMPARE_CONTROL_REG                                             ADCMPCR;    // E800_5890h           16
    RSVD_UINT16(B);
    A2D_COMPARE_FUNCTION_WINDOW_A_CHANNEL_SEL_REG                       ADCMPANSR0; // E800_5894h           16
    RSVD_UINT16(C);
    A2D_COMPARE_FUNCTION_WINDOW_A_COMPARISON_CONDITION_SETTING_REG_0    ADCMPLR0;       // E800_5898h       16
    RSVD_UINT16(D);
    A2D_COMPARE_FUNCTION_WINDOW_A_COMPARISON_CONDITION_SETTING_REG_0    ADCMPDR0;       // E800_589Ch       16
    A2D_COMPARE_FUNCTION_WINDOW_A_COMPARISON_CONDITION_SETTING_REG_0    ADCMPDR1;       // E800_589Eh       16
    A2D_COMPARE_FUNCTION_WINDOW_A_CHANNEL_STATUS_REG_0                  ADCMPSR0;       // E800_58A0h       16
    RSVD_UINT16_ARR(E,2);
    A2D_COMPARE_FUNCTION_WINDOW_B_CHANNEL_SEL_REG                       ADCMPBNSR;      // E800_58A6h       8
    RSVD_UINT8(F);
    A2D_COMPARE_FUNCTION_WINDOW_A_COMPARISON_CONDITION_SETTING_REG_0    ADWINLLB;       // E800_58A8h       16
    A2D_COMPARE_FUNCTION_WINDOW_A_COMPARISON_CONDITION_SETTING_REG_0    ADWINULB;       // E800_58AAh       16
    A2D_COMPARE_FUNCTION_WINDOW_B_CHANNEL_STATUS_REG                    ADCMPBSR;       // E800_58ACh       8
    RSVD_UINT8_ARR(G,0x27);
    A2D_CHANNEL_SELECT_REG                                              ADANSC0;        // E800_58D4h       16
    RSVD_UINT8_ARR(H,3);
    A2D_GROUP_C_TRIGGER_SELECT_REG                                      ADGCTRGR;       // E800_58D9h       8
    RSVD_UINT8_ARR(I,6);
    A2D_SAMPLING_STATE_REG                                              ADSSTR0;        // E800_58E0h       8
    A2D_SAMPLING_STATE_REG                                              ADSSTR1;        // E800_58E1h       8
    A2D_SAMPLING_STATE_REG                                              ADSSTR2;        // E800_58E2h       8
    A2D_SAMPLING_STATE_REG                                              ADSSTR3;        // E800_58E3h       8
    A2D_SAMPLING_STATE_REG                                              ADSSTR4;        // E800_58E4h       8
    A2D_SAMPLING_STATE_REG                                              ADSSTR5;        // E800_58E5h       8
    A2D_SAMPLING_STATE_REG                                              ADSSTR6;        // E800_58E6h       8
    A2D_SAMPLING_STATE_REG                                              ADSSTR7;        // E800_58E7h       8
} A2D_MODULE;



typedef enum
{
    Single_Scan = 0,
    Group_scan,
    Continuous_Scan
} SCAN_MODE;

typedef struct {
   UINT16   EdgeDetectAd;
   UINT16   MinLoopAd;            
   UINT16   Vdd_Ad;                   // Measures the 24VDC
   UINT16   Term_Ad;                  // Uses TempConversionTable[]
   UINT16   MaxLoopAd;
   UINT16   HeadResAd;
   UINT16   TakeupTnsnAd;
   UINT16   PLowAd;
}  A2D_READOUT;

class A2D_MODULE_CLASS
{
    public:
    
        A2D_MODULE_CLASS() {};
        ~A2D_MODULE_CLASS(){};

        void Initialize();
        
        void SelfDiagnostic_ZeroVoltage(UINT8 enable);
        void SetAverageOrAdditionMode(UINT8 Mode);
        void SetAdditionCount(UINT8 Count);
        void SetAdditionAverageSelection4AChannel(UINT8 NumChannels, ...);
        void ConversionSelection4AChannel(UINT8 NumChannels, ...);
        void SetScanMode(SCAN_MODE Mode);
        void StartStopConversion(UINT8 OnOff);
        void SetScanEndInterruptEnable(UINT8 EnDis);

        UINT16  Max_Loop_State();
        UINT16  TakeUp_Tension_State();
        

        A2D_READOUT                 a2dReadout;

    protected:
    
    private:
        volatile A2D_MODULE         *a2d_module;
        UINT8                       ChannelsEnabled;
        DMA_CNTL                    dma_ch; 

        
};

/*******************************************************************************
 * A2D_MODULE_CLASS::SetScanMode()
 *
 * Description
 * -----------
 *  Initialization 
 *
 * Parameters
 * ----------
 * IN:    Mode      00: Single scan mode
 *                  01: Group scan mode
 *                  10: Continuous scan mode
 *                  11: Setting prohibited
 * Returns
 * -------
 *  
 *
 ******************************************************************************/
inline void A2D_MODULE_CLASS::SetScanMode(SCAN_MODE Mode)
{
    wr_nbits(a2d_module->ADCSR.ADCS, Mode);             // Set Mode 
}

/*******************************************************************************
 * A2D_MODULE_CLASS::StartStopConversion()
 *
 * Description
 * -----------
 *  Set Scan Mode 
 *
 * Parameters
 * ----------
 * IN:    On_Off    0: Stop a2d conversion process
 *                  1: Start a2d converstion process
 * 
 * OUT:
 * 
 * Returns
 * -------
 *  
 *
 ******************************************************************************/
inline void A2D_MODULE_CLASS::StartStopConversion(UINT8 OnOff)
{
    wr_nbits(a2d_module->ADCSR.ADST, OnOff);             // Set Mode 
}

/*******************************************************************************
 * A2D_MODULE_CLASS::SetScanEndInterruptEnable()
 *
 * Description
 * -----------
 *  Set Scan Mode 
 *
 * Parameters
 * ----------
 * IN:    EnDis     0: Disables S12ADI0 interrupt generation upon scan completion.
 *                  1: Enables S12ADI0 interrupt generation upon scan completion
 * 
 * OUT:
 * 
 * Returns
 * -------
 *  
 *
 ******************************************************************************/
inline void A2D_MODULE_CLASS::SetScanEndInterruptEnable(UINT8 EnDis)
{
    wr_nbits(a2d_module->ADCSR.ADIE, EnDis);             // Set Mode 
}

/*******************************************************************************
 * A2D_MODULE_CLASS::SetAdditionCount()
 *
 * Description
 * -----------
 *  Initialization 
 *
 * Parameters
 * ----------
 * IN:    Count     0 0 0: 1-time conversion (no addition; same as normal conversion)
 *                  0 0 1: 2-time conversion (addition once)
 *                  0 1 0: 3-time conversion (addition twice)*1
 *                  0 1 1: 4-time conversion (addition three times)
 *                  1 0 1: 16-time conversion (addition 15 times)
 * Returns
 * -------
 *  
 *
 ******************************************************************************/
inline void A2D_MODULE_CLASS::SetAdditionCount(UINT8 Count)
{
    wr_nbits(a2d_module->ADADC.ADC, Count);             // Set Mode
}

/*******************************************************************************
 * A2D_MODULE_CLASS::SetAverageOrAdditionMode()
 *
 * Description
 * -----------
 *  Initialization 
 *
 * Parameters
 * ----------
 * IN:    Mode      0: Addition Mode Selected
 *                  1: Average Mode Selected
 * Returns
 * -------
 *  
 *
 ******************************************************************************/
inline void A2D_MODULE_CLASS::SetAverageOrAdditionMode(UINT8 Mode)
{
    wr_nbits(a2d_module->ADADC.AVEE, Mode);             // Set Mode 
}


