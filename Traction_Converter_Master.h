/**********************************************************************
* File: Self Defined.h
  Self Defined Header File

**********************************************************************/
#include "f28x_project.h"
#ifndef LAB_H
#define LAB_H

#include "f2838x_cla_typedefs.h"        // CLA type definitions
#include "f2838x_device.h"              // F2838xD header file peripheral address definitions
#include "f2838x_adc_defines.h"         // ADC definitions
#include "f2838x_defaultisr.h"          // ISR definitions
#include "f2838x_pie_defines.h"         // PIE definitions




//#include "F2838x_Adc.h" // Or F28x_Project.h which includes it

extern void InitAdc(void);
extern void InitOutputGpios(void);
extern void InitEPwm(void);



//---------------------------------------------------------------------------
// Constant Definitions

//
#define PWM_PERIOD_RECTIFIER  9999                  // 9999 = 5 kHz switching frequency w/ 100 MHz ePWM clock (Triangular)
#define SAMPLING_FREQUENCY_NUMBER 2499                // 3333=15kHZ ;2499 = 20 kHz switching frequency w/ 100 MHz ePWM clock (Triangular)


#define pi 3.14159265   // pi value

#define REFERENCE       REFERENCE_VDAC


//Fault Clear Definition Complete
//---------------------------------------------------------------------------
// Include Standard C Language Header Files
// (Header file <string.h> not supported by CLA compiler)
//


// Variable related to teststate
extern Uint16 Pre_Charger_Contactor_Command;
extern Uint16 Main_Contactor_Command;
extern Uint16 Flow_Pump_Control_Contactor_Command;
extern Uint16 Line_Trip_Output_1_Command;
extern Uint16 Line_Trip_Output_2_Command;
extern Uint16 Contactor_Filter_On_OFF_Command;
extern Uint16 Contactor_Filter_Adaption_Command;
extern Uint16 Contactor_Discharge_Resistor_Command;

extern Uint16 Pre_Charge_Contactor_NOpen_test;
extern Uint16 Pre_Charge_Contactor_NClose_test;
extern Uint16 Main_Contactor_1_NOpen_test;
extern Uint16 Main_Contactor_1_NClose_test;
extern Uint16 Main_Contactor_2_NOpen_test;
extern Uint16 Main_Contactor_2_NClose_test;
extern Uint16 System_ON_OFF_test;
extern Uint16 System_Reset_Command_test;
extern Uint16 Coolent_Level_Command_test;
extern Uint16 Heat_Sink_Temprature_LSC1_LSC_2_test;
extern Uint16 Pressure_DC_Link_Capacitor_1_2_3_test;
extern Uint16 Pressure_DC_Link_Capacitor_4_5_6_test;
extern Uint16 Pressure_DC_Link_Capacitor_7_8_9_test;
extern Uint16 Line_Trip_Input_1_test;
extern Uint16  Line_Trip_Input_2_test;
extern Uint16 LCB_Fast_Open_1_test;
extern Uint16 LCB_Fast_Open_2_test;
extern Uint16 Contactor_Filter_ON_OFF_Feedback_test;
extern Uint16 Contactor_Filter_Adaption_Feedback_test;
extern Uint16 Contactor_Discharge_Resistor_Feedback_test;
extern Uint16 Grid_Input_Current_Command_test;

//Unipolar PWM Variables

extern float32 mi;
extern float32 Finv;
extern int32 sampleInstant;
extern float32 ThetaA ;
extern float32 ma_a;
extern float32 ma_b;
extern float32 ma_c;
extern float32 ma_d;
extern float32 ma_e;
extern Uint16 a;
extern Uint16 b;
extern Uint16 c;
extern Uint16 d;
extern Uint16 e;
extern float32 Ts;

//Variables for ADC sensing
extern Uint16 offsetSettingDone;
extern  float32 Vdc_sense;
extern  float32 Vdc_measADC;
extern  float32 VdcCalFactor;

extern  float32 Vg_measADC ;
extern float32 Vg_measADCSum;
extern float32  VgOffset;
extern  float32 Vg_sense;
extern float32 OVgCalFactor;
extern float32 OIgCalFactor;
extern  float32 Ig_sense;
extern  float32 Vg_meas;
extern float Vg_meas_avg[12];
extern float Vg_meas_mavg;
extern float VgSum;
extern float VgRms;
extern float32 Ig_measADC;
extern float32 IgOffset;
extern  float IgSum;
extern float IgRms;
extern Uint16 avgi ;
extern Uint16 buffNumData;



extern Uint32 offsetSettingCount;
extern int32 averagingWindowCounter;
extern int32 averagingWindow;
extern float32 averagingWindowFloat;

extern float32 waveform1[10000];
extern float32 waveform2[10000];

extern Uint16 DAC3, DAC1;
extern Uint16 display;
extern int32 buffNum;



//Sensor Multiplier
// Sensor Multipliers
#define Voltage_Multiplier 341.496 //57.126
#define Current_Multiplier 53.74//30.74





#define Pre_Charge_Contactor_NOpen_Command                                      GpioDataRegs.GPDDAT.bit.GPIO96
#define Pre_charger_Contactor_NClose_Command                                    GpioDataRegs.GPDDAT.bit.GPIO99
#define Main_Contactor_1_NOpen_Command                                          GpioDataRegs.GPDDAT.bit.GPIO97
#define Main_Contactor_1_NClose_Command                                         GpioDataRegs.GPDDAT.bit.GPIO100
#define Main_Contactor_2_NOpen_Command                                          GpioDataRegs.GPDDAT.bit.GPIO98
#define Main_Contactor_2_NClose_Command                                         GpioDataRegs.GPDDAT.bit.GPIO101
#define System_ON_OFF_Command                                                   GpioDataRegs.GPDDAT.bit.GPIO102
#define System_Reset_Command                                                    GpioDataRegs.GPDDAT.bit.GPIO103
#define Coolent_Level_Command                                                   GpioDataRegs.GPDDAT.bit.GPIO104
#define Heat_Sink_Temprature_LSC1_LSC_2_Command                                 GpioDataRegs.GPEDAT.bit.GPIO143
#define Pressure_DC_Link_Capacitor_1_2_3_Command                                GpioDataRegs.GPEDAT.bit.GPIO136
#define Pressure_DC_Link_Capacitor_4_5_6_Command                                GpioDataRegs.GPEDAT.bit.GPIO137
#define Pressure_DC_Link_Capacitor_7_8_9_Command                                GpioDataRegs.GPEDAT.bit.GPIO138
#define Line_Trip_Input_1_Command                                               GpioDataRegs.GPFDAT.bit.GPIO165
#define Line_Trip_Input_2_Command                                               GpioDataRegs.GPFDAT.bit.GPIO167
#define LCB_Fast_Open_1_Command                                                 GpioDataRegs.GPEDAT.bit.GPIO146
#define LCB_Fast_Open_2_Command                                                 GpioDataRegs.GPEDAT.bit.GPIO147
#define Contactor_Filter_ON_OFF_Feedback_Command                                GpioDataRegs.GPCDAT.bit.GPIO76
#define Contactor_Filter_Adaption_Feedback_Command                              GpioDataRegs.GPEDAT.bit.GPIO141
#define Contactor_Discharge_Resistor_Feedback_Command                           GpioDataRegs.GPEDAT.bit.GPIO142
#define Grid_Input_Current_Command                                              GpioDataRegs.GPEDAT.bit.GPIO148



//Line Side Converter :: GPIO Output Definitions
#define Pre_Charge_Contactor_OFF         GpioDataRegs.GPCCLEAR.bit.GPIO94
#define Pre_Charge_Contactor_ON          GpioDataRegs.GPCSET.bit.GPIO94
#define Main_Contactor_OFF               GpioDataRegs.GPCCLEAR.bit.GPIO95
#define Main_Contactor_ON                GpioDataRegs.GPCSET.bit.GPIO95
#define Flow_Pump_Contactor_OFF          GpioDataRegs.GPECLEAR.bit.GPIO133
#define Flow_Pump_Contactor_ON           GpioDataRegs.GPESET.bit.GPIO133
#define Line_Trip_Output1_OFF            GpioDataRegs.GPFCLEAR.bit.GPIO166
#define Line_Trip_Output1_ON             GpioDataRegs.GPFSET.bit.GPIO166
#define Line_Trip_Output2_OFF            GpioDataRegs.GPFCLEAR.bit.GPIO168
#define Line_Trip_Output2_ON             GpioDataRegs.GPFSET.bit.GPIO168
#define Contactor_Filter_OFF             GpioDataRegs.GPCCLEAR.bit.GPIO74
#define Contactor_Filter_ON              GpioDataRegs.GPCSET.bit.GPIO74
#define Contactor_Filter_Adaption_OFF    GpioDataRegs.GPECLEAR.bit.GPIO139
#define Contactor_Filter_Adaption_ON     GpioDataRegs.GPESET.bit.GPIO139
#define Contactor_Discharge_Resistor_OFF GpioDataRegs.GPECLEAR.bit.GPIO140
#define Contactor_Discharge_Resistor_ON GpioDataRegs.GPESET.bit.GPIO140


//Line Side Converter ::PWM Pulse Control GPIO OutPut Definition

#define SW1_CC_Channel_ON                 GpioDataRegs.GPCSET.bit.GPIO73
#define SW1_CC_Channel_OFF                GpioDataRegs.GPCCLEAR.bit.GPIO73
/*#define L1_Run_Signal_ON                GpioDataRegs.GPDSET.bit.GPIO127
#define L1_Run_Signal_OFF                 GpioDataRegs.GPCCLEAR.bit.GPIO127*/

//Line Side Converter:: PWM Pulse Control GPIO INPUT Definition
#define SW1



//Line Side Converter ::PWM Pulse Control GPIO OutPut Definitions
#define  L1GDU_F1T                        GpioDataRegs.GPEDAT.bit.GPIO149   //Line Side 1 Leg 1 Top GDU Fault
#define  L1GDU_F1B                        GpioDataRegs.GPEDAT.bit.GPIO150   //Line Side 1 Leg 1 Bottom GDU Fault
#define  L1GDU_F2T                        GpioDataRegs.GPEDAT.bit.GPIO151   //Line Side 1 Leg 2 Top GDU Fault
#define  L1GDU_F2B                        GpioDataRegs.GPEDAT.bit.GPIO152   //Line Side 1 Leg 2 Bottom GDU Fault
#define  L2GDU_F1T                        GpioDataRegs.GPEDAT.bit.GPIO153   //Line Side 2 Leg 1 Top GDU Fault
#define  L2GDU_F1B                        GpioDataRegs.GPEDAT.bit.GPIO154   //Line Side 2 Leg 1 Bottom GDU Fault
#define  L2GDU_F2T                        GpioDataRegs.GPEDAT.bit.GPIO155   //Line Side 2 Leg 2 Top GDU Fault
#define  L2GDU_F2B                        GpioDataRegs.GPEDAT.bit.GPIO156   //Line Side 2 Leg 2 Bottom GDU Fault
#define  CHGDU_FT                         GpioDataRegs.GPEDAT.bit.GPIO157   //Chopper Top GDU Fault
#define  CHGDU_FB                         GpioDataRegs.GPEDAT.bit.GPIO158   //Chopper Bottom GDU Fault




#define    SW1_CC                                       73
#define    CC_SEL1                                      70
#define    CC_SEL2                                      71
#define    CC_SEL3                                      32








//---------------------------------------------------------------------------
#endif  // end of LAB_H definition


//--- end of file -----------------------------------------------------
