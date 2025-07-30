//###########################################################################
//
// FILE:   f2838x_defaultisr.c
//
// TITLE:  f2838x Device Default Interrupt Service Routines
//
//###########################################################################
// 
// C2000Ware v5.04.00.00
//
// Copyright (C) 2024 Texas Instruments Incorporated - http://www.ti.com
//
// Redistribution and use in source and binary forms, with or without 
// modification, are permitted provided that the following conditions 
// are met:
// 
//   Redistributions of source code must retain the above copyright 
//   notice, this list of conditions and the following disclaimer.
// 
//   Redistributions in binary form must reproduce the above copyright
//   notice, this list of conditions and the following disclaimer in the 
//   documentation and/or other materials provided with the   
//   distribution.
// 
// Author: Dr. Aryadip Sen
//###########################################################################
//Hello 123
//
// Included Files
//
#include "f2838x_device.h"       // f2838x Header File Include File
#include "f2838x_examples.h"     // f2838x Examples Include File
#include "Traction_Converter_Master.h"
#include <math.h>



//
// CPU Timer 1 Interrupt
//
interrupt void TIMER1_ISR(void)
{

    asm ("      ESTOP0");
    for(;;);
}

//
// CPU Timer 2 Interrupt
//
interrupt void TIMER2_ISR(void)
{

    asm ("      ESTOP0");
    for(;;);
}

//
// Datalogging Interrupt
//
interrupt void DATALOG_ISR(void)
{

    asm ("      ESTOP0");
    for(;;);
}

//
// RTOS Interrupt
//
interrupt void RTOS_ISR(void)
{

    asm ("      ESTOP0");
    for(;;);
}

//
// Emulation Interrupt
//
interrupt void EMU_ISR(void)
{

    asm ("      ESTOP0");
    for(;;);
}

//
// Non-Maskable Interrupt
//
interrupt void NMI_ISR(void)
{

    asm ("      ESTOP0");
    for(;;);
}

//
// Illegal Operation Trap
//
interrupt void ILLEGAL_ISR(void)
{

    asm ("      ESTOP0");
    for(;;);
}

//
// User Defined Trap 1
//
interrupt void USER1_ISR(void)
{

    asm ("      ESTOP0");
    for(;;);
}

//
// User Defined Trap 2
//
interrupt void USER2_ISR(void)
{

    asm ("      ESTOP0");
    for(;;);
}

//
// User Defined Trap 3
//
interrupt void USER3_ISR(void)
{

    asm ("      ESTOP0");
    for(;;);
}

//
// User Defined Trap 4
//
interrupt void USER4_ISR(void)
{

    asm ("      ESTOP0");
    for(;;);
}

//
// User Defined Trap 5
//
interrupt void USER5_ISR(void)
{

    asm ("      ESTOP0");
    for(;;);
}

//
// User Defined Trap 6
//
interrupt void USER6_ISR(void)
{
    asm ("      ESTOP0");
    for(;;);
}

//
// User Defined Trap 7
//
interrupt void USER7_ISR(void)
{

    asm ("      ESTOP0");
    for(;;);
}

//
// User Defined Trap 8
//
interrupt void USER8_ISR(void)
{

    asm ("      ESTOP0");
    for(;;);
}

//
// User Defined Trap 9
//
interrupt void USER9_ISR(void)
{

    asm ("      ESTOP0");
    for(;;);
}

//
// User Defined Trap 10
//
interrupt void USER10_ISR(void)
{
    asm ("      ESTOP0");
    for(;;);
}

//
// User Defined Trap 11
//
interrupt void USER11_ISR(void)
{

    asm ("      ESTOP0");
    for(;;);
}

//
// User Defined Trap 12
//
interrupt void USER12_ISR(void)
{

    asm ("      ESTOP0");
    for(;;);
}

//
// 1.1 - ADCA Interrupt 1
//
__interrupt void ADCA1_ISR(void)
{


                                               //Testing Digital Outputs//

    if (Pre_Charger_Contactor_Command == 1)
                                    {
                                        Pre_Charge_Contactor_ON= 1;
                                    }
                                     else
                                    {
                                         Pre_Charge_Contactor_OFF= 1;
                                    }

   if (Main_Contactor_Command == 1)
                                    {

                                        Main_Contactor_ON=1;
                                   }
                                    else
                                   {
                                        Main_Contactor_OFF = 1;
                                   }


   if (Flow_Pump_Control_Contactor_Command == 1)
                                           {

                                              Flow_Pump_Contactor_ON =1;
                                          }
                                           else
                                          {
                                               Flow_Pump_Contactor_OFF= 1;
                                          }

   if (Line_Trip_Output_1_Command== 1)
                                                  {

                                                      Line_Trip_Output1_ON= 1;
                                                 }
                                                  else
                                                 {
                                                      Line_Trip_Output1_OFF=1;
                                                 }


   if (Line_Trip_Output_2_Command== 1)
                                                        {

                                                               Line_Trip_Output2_ON =1;
                                                        }
                                                         else
                                                        {
                                                             Line_Trip_Output2_OFF= 1;
                                                        }


   if (Contactor_Filter_On_OFF_Command== 1)
                                                               {

                                                                    Contactor_Filter_ON = 1;
                                                               }
                                                                else
                                                               {
                                                                    Contactor_Filter_OFF= 1;
                                                               }


   if (Contactor_Filter_Adaption_Command== 1)
                                                               {

                                                                     Contactor_Filter_Adaption_ON=1;
                                                                 }
                                                                  else
                                                                  {
                                                                      Contactor_Filter_Adaption_OFF= 1;
                                                                   }

   if (Contactor_Discharge_Resistor_Command== 1)
                                                                  {

                                                                       Contactor_Discharge_Resistor_ON =1;
                                                                   }
                                                                   else
                                                                    {
                                                                       Contactor_Discharge_Resistor_OFF= 1;
                                                                     }


                                          // Testing Digital Inputs//

   if (Pre_Charge_Contactor_NOpen_Command == 1)
                                   {
                                       Pre_Charge_Contactor_NOpen_test =1;

                                   }
                                    else
                                   {
                                        Pre_Charge_Contactor_NOpen_test =0;

                                   }

   if ( Pre_charger_Contactor_NClose_Command == 1)
                                     {
                                         Pre_Charge_Contactor_NClose_test =1;

                                     }
                                      else
                                     {
                                          Pre_Charge_Contactor_NClose_test =0;

                                     }

   if (  Main_Contactor_1_NOpen_Command  == 1)
                                        {
                                               Main_Contactor_1_NOpen_test =1;

                                        }
                                         else
                                        {
                                                 Main_Contactor_1_NOpen_test =0;

                                        }


   if (  Main_Contactor_1_NClose_Command  == 1)
                                           {
                                                   Main_Contactor_1_NClose_test =1;

                                           }
                                            else
                                           {
                                                  Main_Contactor_1_NClose_test =0;

                                           }
   if (  Main_Contactor_2_NOpen_Command  == 1)
                                              {
                                                  Main_Contactor_2_NOpen_test =1;

                                              }
                                               else
                                              {
                                                   Main_Contactor_2_NOpen_test =0;

                                              }

   if ( Main_Contactor_2_NClose_Command  == 1)
                                                 {
                                                       Main_Contactor_2_NClose_test =1;

                                                 }
                                                  else
                                                 {
                                                      Main_Contactor_2_NClose_test =0;

                                                 }


   if (System_ON_OFF_Command  == 1)
                                                    {
                                                         System_ON_OFF_test =1;

                                                    }
                                                     else
                                                    {
                                                         System_ON_OFF_test =0;

                                                    }

   if (System_Reset_Command  == 1)
                                                       {
                                                           System_Reset_Command_test =1;

                                                       }
                                                        else
                                                       {
                                                            System_Reset_Command_test =0;

                                                       }
   if (Coolent_Level_Command  == 1)
                                                         {
                                                              Coolent_Level_Command_test =1;

                                                         }
                                                          else
                                                         {
                                                              Coolent_Level_Command_test =0;

                                                         }

   if (Heat_Sink_Temprature_LSC1_LSC_2_Command  == 1)
                                                            {
                                                               Heat_Sink_Temprature_LSC1_LSC_2_test =1;

                                                            }
                                                             else
                                                            {
                                                                 Heat_Sink_Temprature_LSC1_LSC_2_test =0;

                                                            }
   if (Pressure_DC_Link_Capacitor_1_2_3_Command   == 1)
                                                               {
                                                                     Pressure_DC_Link_Capacitor_1_2_3_test =1;

                                                               }
                                                                else
                                                               {
                                                                    Pressure_DC_Link_Capacitor_1_2_3_test =0;

                                                               }

   if (Pressure_DC_Link_Capacitor_4_5_6_Command    == 1)
                                                                  {
                                                                       Pressure_DC_Link_Capacitor_4_5_6_test =1;

                                                                  }
                                                                   else
                                                                  {
                                                                       Pressure_DC_Link_Capacitor_4_5_6_test =0;


                                                                  }
   if (Pressure_DC_Link_Capacitor_7_8_9_Command    == 1)
                                                                     {
                                                                          Pressure_DC_Link_Capacitor_7_8_9_test =1;

                                                                     }
                                                                      else
                                                                     {
                                                                          Pressure_DC_Link_Capacitor_7_8_9_test =0;

                                                                     }
   if (Line_Trip_Input_1_Command    == 1)
                                                                        {
                                                                           Line_Trip_Input_1_test =1;

                                                                        }
                                                                         else
                                                                        {
                                                                             Line_Trip_Input_1_test =0;
                                                                        }

 if (Line_Trip_Input_2_Command     == 1)
                                                                         {
                                                                         Line_Trip_Input_2_test =1;

                                                                           }
                                                                           else
                                                                             {
                                                                            Line_Trip_Input_2_test =0;

                                                                              }
 if (LCB_Fast_Open_1_Command     == 1)
                                                                          {
                                                                              LCB_Fast_Open_1_test =1;

                                                                            }
                                                                            else
                                                                              {
                                                                                LCB_Fast_Open_1_test =0;

                                                                               }
 if (LCB_Fast_Open_2_Command       == 1)
                                                                           {
                                                                                 LCB_Fast_Open_2_test =1;

                                                                             }
                                                                             else
                                                                               {
                                                                                 LCB_Fast_Open_2_test =0;

                                                                                }

 if (Contactor_Filter_ON_OFF_Feedback_Command      == 1)
                                                                            {
                                                                                 Contactor_Filter_ON_OFF_Feedback_test =1;

                                                                              }
                                                                              else
                                                                                {
                                                                                  Contactor_Filter_ON_OFF_Feedback_test =0;

                                                                                 }
 if (Contactor_Filter_Adaption_Feedback_Command       == 1)
                                                                             {
                                                                                Contactor_Filter_Adaption_Feedback_test =1;

                                                                               }
                                                                               else
                                                                                 {
                                                                                   Contactor_Filter_Adaption_Feedback_test =0;

                                                                                  }
 if (Contactor_Discharge_Resistor_Feedback_Command       == 1)
                                                                              {
                                                                                    Contactor_Discharge_Resistor_Feedback_test =1;

                                                                                }
                                                                                else
                                                                                  {
                                                                                    Contactor_Discharge_Resistor_Feedback_test =0;

                                                                                   }

 if (Grid_Input_Current_Command       == 1)
                                                                              {
                                                                                         Grid_Input_Current_Command_test =1;

                                                                                }
                                                                                else
                                                                                  {
                                                                                         Grid_Input_Current_Command_test =0;

                                                                                   }






                        // UNIPOLAR PWM TEST CODE: START
                      /*  if (SW1_CC_Channel_ON ==1 && L1_Run_Signal_ON ==1)
                        {*/

                        mi = 0.9;
                        Finv = 50.0;

                        EPwm1Regs.DBRED.bit.DBRED    = 1000;   // 10 microsecond deadtime
                        EPwm1Regs.DBFED.bit.DBFED    = 1000;   // for rising and falling edge
                        EPwm1Regs.DBCTL.bit.OUT_MODE = 3;      // ePWM1A = RED
                        EPwm1Regs.DBCTL.bit.POLSEL   = 2;      // S3=1 inverted signal at ePWM1B
                        EPwm1Regs.DBCTL.bit.IN_MODE  = 0;      // ePWM1A = source for RED & FED


                        EPwm2Regs.DBRED.bit.DBRED    = 1000;   // 10 microsecond deadtime
                        EPwm2Regs.DBFED.bit.DBFED    = 1000;   // for rising and falling edge
                        EPwm2Regs.DBCTL.bit.OUT_MODE = 3;      // ePWM1A = RED
                        EPwm2Regs.DBCTL.bit.POLSEL   = 2;      // S3=1 inverted signal at ePWM2B
                        EPwm2Regs.DBCTL.bit.IN_MODE  = 0;      // ePWM2A = source for RED & FED

                        EPwm3Regs.DBRED.bit.DBRED    = 1000;   // 10 microsecond deadtime
                        EPwm3Regs.DBFED.bit.DBFED    = 1000;   // for rising and falling edge
                        EPwm3Regs.DBCTL.bit.OUT_MODE = 3;      // ePWM3A = RED
                        EPwm3Regs.DBCTL.bit.POLSEL   = 2;      // S3=1 inverted signal at ePWM3B
                        EPwm3Regs.DBCTL.bit.IN_MODE  = 0;      // ePWM2A = source for RED & FED

                        EPwm4Regs.DBRED.bit.DBRED    = 1000;   // 10 microsecond deadtime
                        EPwm4Regs.DBFED.bit.DBFED    = 1000;   // for rising and falling edge
                        EPwm4Regs.DBCTL.bit.OUT_MODE = 3;      // ePWM4A = RED
                        EPwm4Regs.DBCTL.bit.POLSEL   = 2;      // S3=1 inverted signal at ePWM4B
                        EPwm4Regs.DBCTL.bit.IN_MODE  = 0;      // ePWM2A = source for RED & FED

                        EPwm5Regs.DBRED.bit.DBRED    = 1000;   // 10 microsecond deadtime
                        EPwm5Regs.DBFED.bit.DBFED    = 1000;   // for rising and falling edge
                        EPwm5Regs.DBCTL.bit.OUT_MODE = 3;      // ePWM5A = RED
                        EPwm5Regs.DBCTL.bit.POLSEL   = 2;      // S3=1 inverted signal at ePWM5B
                        EPwm5Regs.DBCTL.bit.IN_MODE  = 0;      // ePWM2A = source for RED & FED


                        sampleInstant = sampleInstant + 1;
                        if (sampleInstant == 40)
                        {
                            sampleInstant = 0;
                        }
                        ThetaA = 2.0*pi*Finv*Ts*sampleInstant;      // phase A Theta

                        ma_a = 0.5+((mi/2.0)*sin(ThetaA));
                        ma_b = 0.5-((mi/2.0)*sin(ThetaA));            // modulation index setting
                        ma_c = 0.5+((mi/2.0)*sin(ThetaA));
                        ma_d = 0.5-((mi/2.0)*sin(ThetaA));
                        ma_e = 0.5-((mi/2.0)*sin(ThetaA));

                        ma_a = ma_a*EPwm1Regs.TBPRD;
                        ma_b = ma_b*EPwm2Regs.TBPRD;
                        ma_c = ma_c*EPwm3Regs.TBPRD;
                        ma_d = ma_d*EPwm4Regs.TBPRD;
                        ma_e=  ma_e*EPwm4Regs.TBPRD;

                        a = ma_a;
                        b = ma_b;
                        c = ma_c;
                        d = ma_d;
                        e = ma_e;
                        EPwm1Regs.CMPA.bit.CMPA = a ;
                        EPwm2Regs.CMPA.bit.CMPA = b ;
                        EPwm3Regs.CMPA.bit.CMPA = c ;
                        EPwm4Regs.CMPA.bit.CMPA = d ;
                        EPwm5Regs.CMPA.bit.CMPA = e ;

//Scaling the Sensed Parameter to the Actual Magnitude//

         if (offsetSettingDone == 1)
         {
             // DC voltages sensing
          Vdc_sense = 3*AdcbResultRegs.ADCRESULT0;            // DC link Voltage V_dc1
          Vdc_sense = Vdc_sense/4095;
          Vdc_measADC  = (Vdc_sense*400*VdcCalFactor); //400//189.72//203

          Vg_sense = 3.3*AdcbResultRegs.ADCRESULT1;           // Grid Voltage Sensing
          Vg_sense = Vg_sense/4095;
          Vg_measADC =(Vg_sense*Voltage_Multiplier*OVgCalFactor) - (Voltage_Multiplier*VgOffset*OVgCalFactor);

          Ig_sense = 3.3*AdccResultRegs.ADCRESULT0;           //Grid Current
          Ig_sense = Ig_sense/4095;
          Ig_measADC=(Ig_sense*Current_Multiplier*OIgCalFactor) - (Current_Multiplier*IgOffset*OIgCalFactor);

         }

         else{
             Vdc_sense=0;
             Vg_sense = 3.3*AdcbResultRegs.ADCRESULT1;
             Vg_sense = Vg_sense/4095;

             Ig_sense = 3.3*AdccResultRegs.ADCRESULT0;           //Grid Current
             Ig_sense = Ig_sense/4095;




         offsetSettingCount = offsetSettingCount + 1;



             if (offsetSettingCount >= 40000)
                     {

                VgOffset = VgOffset + Vg_sense;

                VgOffset = VgOffset/20000.0;

                IgOffset=IgOffset+Ig_sense;

                IgOffset=IgOffset/20000;

                offsetSettingDone = 1;

                     }


             else if (offsetSettingCount > 20000)   // one sec wait for 20 kHz sampling frequency
                     {

                     VgOffset = VgOffset + Vg_sense;

                     IgOffset=  IgOffset+  Ig_sense;

                     }
         }

             Vg_meas_avg[avgi]= Vg_measADC;
             Vg_meas_mavg= Vg_meas_avg[0] +Vg_meas_avg[1]+Vg_meas_avg[2]+Vg_meas_avg[3]+Vg_meas_avg[4]+Vg_meas_avg[5];
             Vg_meas_mavg= Vg_meas_mavg*0.1667;//0.1667
             avgi++;
                     if(avgi>5){
                         avgi=0;
                          }

                     // // Computing rms values for the grid voltages//

                     buffNumData = buffNumData + 1;
                                   if (buffNumData == 1600)           // 80 ms
                                    {
                                        buffNumData   = 0;
                                        VgSum = VgSum + Vg_measADC*Vg_measADC;

                                        VgRms = sqrtf(VgSum/1600.0);

                                        VgSum=0;

                                        IgSum = IgSum + Ig_measADC*Ig_measADC;

                                        IgRms = sqrt(IgSum/1600.0);

                                        IgSum=0;

                                    }
                                   else
                                   {
                                       VgSum = VgSum + Vg_measADC*Vg_measADC;

                                       IgSum = IgSum + Ig_measADC*Ig_measADC;
                                   }

        //  FOR OBSERVING WAVEFORMS IN DEBUG WINDOW
                /*   waveform1[buffNum] = VgRms;
                   waveform2[buffNum] = IgRms;*/

                                //  DAC1 = (Vg_measADC*3)+2000;
                                //  DAC3=  (Vg_measADC*3)+2000;
                                   uint32_t vg_int = *(uint32_t*)&Vg_sense;
                                   switch (display)
                                              {
                                          case 1:
                                     DacaRegs.DACVALS.all = ( vg_int>>4)+0x7FF;
                                  // DacaRegs.DACVALS.all = (Vg_measADC*3)+2000;
                                  // DacbRegs.DACVALS.all =  (Vg_measADC*3)+2000;
                                     DacbRegs.DACVALS.all =  (vg_int>>4)+0x7FF;
                                           break;
                                              }

       EALLOW;
       PieCtrlRegs.PIEACK.all = PIEACK_GROUP1; // Acknowledge PIE group 1
       EDIS;

       //--- Manage the ADC registers
       AdcaRegs.ADCINTFLGCLR.bit.ADCINT1 = 1;  // Clear ADC interrupt flag


}



//
// 1.2 - ADCB Interrupt 1
//
interrupt void ADCB1_ISR(void)
{
    PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;         // Must acknowledge the PIE group
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// 1.3 - ADCC Interrupt 1
//
interrupt void ADCC1_ISR(void)
{
    PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;         // Must acknowledge the PIE group
    asm ("      ESTOP0");
    for(;;);
}

//
// 1.4 - XINT1 Interrupt
//
interrupt void XINT1_ISR(void)
{
    PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;         // Must acknowledge the PIE group
    asm ("      ESTOP0");
    for(;;);
}

//
// 1.5 - XINT2 Interrupt
//
interrupt void XINT2_ISR(void)
{
    PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;         // Must acknowledge the PIE group
    asm ("      ESTOP0");
    for(;;);
}

//
// 1.6 - ADCD Interrupt 1
//
interrupt void ADCD1_ISR(void)
{
    PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;         // Must acknowledge the PIE group
    asm ("      ESTOP0");
    for(;;);
}

//
// 1.7 - Timer 0 Interrupt
//
interrupt void TIMER0_ISR(void)
{
    PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;         // Must acknowledge the PIE group
    asm ("      ESTOP0");
    for(;;);
}

//
// 1.8 - Standby and Halt Wakeup Interrupt
//
interrupt void WAKE_ISR(void)
{
    PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;         // Must acknowledge the PIE group
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// 2.1 - ePWM1 Trip Zone Interrupt
//
interrupt void EPWM1_TZ_ISR(void)
{

    asm ("      ESTOP0");
    for(;;);
}

//
// 2.2 - ePWM2 Trip Zone Interrupt
//
interrupt void EPWM2_TZ_ISR(void)
{
    PieCtrlRegs.PIEACK.all = PIEACK_GROUP2;         // Must acknowledge the PIE group
    asm ("      ESTOP0");
    for(;;);
}

//
// 2.3 - ePWM3 Trip Zone Interrupt
//
interrupt void EPWM3_TZ_ISR(void)
{
    PieCtrlRegs.PIEACK.all = PIEACK_GROUP2;         // Must acknowledge the PIE group
    asm ("      ESTOP0");
    for(;;);
}

//
// 2.4 - ePWM4 Trip Zone Interrupt
//
interrupt void EPWM4_TZ_ISR(void)
{
    PieCtrlRegs.PIEACK.all = PIEACK_GROUP2;         // Must acknowledge the PIE group
    asm ("      ESTOP0");
    for(;;);
}

//
// 2.5 - ePWM5 Trip Zone Interrupt
//
interrupt void EPWM5_TZ_ISR(void)
{
    PieCtrlRegs.PIEACK.all = PIEACK_GROUP2;         // Must acknowledge the PIE group
    asm ("      ESTOP0");
    for(;;);
}

//
// 2.6 - ePWM6 Trip Zone Interrupt
//
interrupt void EPWM6_TZ_ISR(void)
{
    PieCtrlRegs.PIEACK.all = PIEACK_GROUP2;         // Must acknowledge the PIE group
    asm ("      ESTOP0");
    for(;;);
}

//
// 2.7 - ePWM7 Trip Zone Interrupt
//
interrupt void EPWM7_TZ_ISR(void)
{
    PieCtrlRegs.PIEACK.all = PIEACK_GROUP2;         // Must acknowledge the PIE group

    //
    // Insert ISR Code here

    asm ("      ESTOP0");
    for(;;);
}

//
// 2.8 - ePWM8 Trip Zone Interrupt
//
interrupt void EPWM8_TZ_ISR(void)
{
    PieCtrlRegs.PIEACK.all = PIEACK_GROUP2;         // Must acknowledge the PIE group
    asm ("      ESTOP0");
    for(;;);
}

//
// 3.1 - ePWM1 Interrupt
//
interrupt void EPWM1_ISR(void)
{
    PieCtrlRegs.PIEACK.all = PIEACK_GROUP3;         // Must acknowledge the PIE group
    asm ("      ESTOP0");
    for(;;);
}

//
// 3.2 - ePWM2 Interrupt
//
interrupt void EPWM2_ISR(void)
{

    PieCtrlRegs.PIEACK.all = PIEACK_GROUP3;         // Must acknowledge the PIE group

    asm ("      ESTOP0");
    for(;;);
}

//
// 3.3 - ePWM3 Interrupt
//
interrupt void EPWM3_ISR(void)
{
    PieCtrlRegs.PIEACK.all = PIEACK_GROUP3;         // Must acknowledge the PIE group

    asm ("      ESTOP0");
    for(;;);
}

//
// 3.4 - ePWM4 Interrupt
//
interrupt void EPWM4_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt.
     PieCtrlRegs.PIEACK.all = PIEACK_GROUP3;           // Must acknowledge the PIE group
    //

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// 3.5 - ePWM5 Interrupt
//
interrupt void EPWM5_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt.
     PieCtrlRegs.PIEACK.all = PIEACK_GROUP3; // Must acknowledge the PIE group
    //

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// 3.6 - ePWM6 Interrupt
//
interrupt void EPWM6_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt.
     PieCtrlRegs.PIEACK.all = PIEACK_GROUP3;     // Must acknowledge the PIE group
    //

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// 3.7 - ePWM7 Interrupt
//
interrupt void EPWM7_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt.
     PieCtrlRegs.PIEACK.all = PIEACK_GROUP3;    // Must acknowledge the PIE group
    //

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// 3.8 - ePWM8 Interrupt
//
interrupt void EPWM8_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt.
     PieCtrlRegs.PIEACK.all = PIEACK_GROUP3;    // Must acknowledge the PIE group
    //

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// 4.1 - eCAP1 Interrupt
//
interrupt void ECAP1_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt.
     PieCtrlRegs.PIEACK.all = PIEACK_GROUP4;
    //

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// 4.2 - eCAP2 Interrupt
//
interrupt void ECAP2_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt.
    PieCtrlRegs.PIEACK.all = PIEACK_GROUP4;
    //

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// 4.3 - eCAP3 Interrupt
//
interrupt void ECAP3_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt.
        PieCtrlRegs.PIEACK.all = PIEACK_GROUP4;
    //

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// 4.4 - eCAP4 Interrupt
//
interrupt void ECAP4_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt.
        PieCtrlRegs.PIEACK.all = PIEACK_GROUP4;
    //

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// 4.5 - eCAP5 Interrupt
//
interrupt void ECAP5_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt.
        PieCtrlRegs.PIEACK.all = PIEACK_GROUP4;
    //

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// 4.6 - eCAP6 Interrupt
//
interrupt void ECAP6_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt.
     PieCtrlRegs.PIEACK.all = PIEACK_GROUP4;
    //

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// 4.7 - eCAP7 Interrupt
//
interrupt void ECAP7_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt.
     PieCtrlRegs.PIEACK.all = PIEACK_GROUP4;
    //

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// 5.1 - eQEP1 Interrupt
//
interrupt void EQEP1_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt.
     PieCtrlRegs.PIEACK.all = PIEACK_GROUP5;
    //

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// 5.2 - eQEP2 Interrupt
//
interrupt void EQEP2_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt.
     PieCtrlRegs.PIEACK.all = PIEACK_GROUP5;
    //

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// 5.3 - eQEP3 Interrupt
//
interrupt void EQEP3_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt.
     PieCtrlRegs.PIEACK.all = PIEACK_GROUP5;
    //

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// 5.5 - CLB1 (Reconfigurable Logic) Interrupt
//
interrupt void CLB1_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt.
     PieCtrlRegs.PIEACK.all = PIEACK_GROUP5;
    //

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// 5.6 - CLB2 (Reconfigurable Logic) Interrupt
//
interrupt void CLB2_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt.
     PieCtrlRegs.PIEACK.all = PIEACK_GROUP5;
    //

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// 5.7 - CLB3 (Reconfigurable Logic) Interrupt
//
interrupt void CLB3_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt.
     PieCtrlRegs.PIEACK.all = PIEACK_GROUP5;
    //

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// 5.8 - CLB4 (Reconfigurable Logic) Interrupt
//
interrupt void CLB4_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt.
     PieCtrlRegs.PIEACK.all = PIEACK_GROUP5;
    //

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// 6.1 - SPIA Receive Interrupt
//
interrupt void SPIA_RX_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt.
     PieCtrlRegs.PIEACK.all = PIEACK_GROUP6;
    //

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// 6.2 - SPIA Transmit Interrupt
//
interrupt void SPIA_TX_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt.
     PieCtrlRegs.PIEACK.all = PIEACK_GROUP6;
    //

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// 6.3 - SPIB Receive Interrupt
//
interrupt void SPIB_RX_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt.
     PieCtrlRegs.PIEACK.all = PIEACK_GROUP6;
    //

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// 6.4 - SPIB Transmit Interrupt
//
interrupt void SPIB_TX_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt.
     PieCtrlRegs.PIEACK.all = PIEACK_GROUP6;
    //

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// 6.5 - McBSPA Receive Interrupt
//
interrupt void MCBSPA_RX_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt.
     PieCtrlRegs.PIEACK.all = PIEACK_GROUP6;
    //

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// 6.6 - McBSPA Transmit Interrupt
//
interrupt void MCBSPA_TX_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt.
     PieCtrlRegs.PIEACK.all = PIEACK_GROUP6;
    //

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// 6.7 - McBSPB Receive Interrupt
//
interrupt void MCBSPB_RX_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt.
     PieCtrlRegs.PIEACK.all = PIEACK_GROUP6;
    //

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// 6.8 - McBSPB Transmit Interrupt
//
interrupt void MCBSPB_TX_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt.
    PieCtrlRegs.PIEACK.all = PIEACK_GROUP6;
    //

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// 7.1 - DMA Channel 1 Interrupt
//
interrupt void DMA_CH1_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt.
     PieCtrlRegs.PIEACK.all = PIEACK_GROUP7;
    //

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// 7.2 - DMA Channel 2 Interrupt
//
interrupt void DMA_CH2_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt.
     PieCtrlRegs.PIEACK.all = PIEACK_GROUP7;
    //

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// 7.3 - DMA Channel 3 Interrupt
//
interrupt void DMA_CH3_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt.
     PieCtrlRegs.PIEACK.all = PIEACK_GROUP7;
    //

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// 7.4 - DMA Channel 4 Interrupt
//
interrupt void DMA_CH4_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt.
     PieCtrlRegs.PIEACK.all = PIEACK_GROUP7;
    //

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// 7.5 - DMA Channel 5 Interrupt
//
interrupt void DMA_CH5_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt.
     PieCtrlRegs.PIEACK.all = PIEACK_GROUP7;
    //

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// 7.6 - DMA Channel 6 Interrupt
//
interrupt void DMA_CH6_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt.
     PieCtrlRegs.PIEACK.all = PIEACK_GROUP7;
    //

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// 8.1 - I2CA Interrupt 1
//
interrupt void I2CA_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt.
     PieCtrlRegs.PIEACK.all = PIEACK_GROUP8;
    //

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// 8.2 - I2CA Interrupt 2
//
interrupt void I2CA_FIFO_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt.
     PieCtrlRegs.PIEACK.all = PIEACK_GROUP8;
    //

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// 8.3 - I2CB Interrupt 1
//
interrupt void I2CB_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt.
     PieCtrlRegs.PIEACK.all = PIEACK_GROUP8;
    //

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// 8.4 - I2CB Interrupt 2
//
interrupt void I2CB_FIFO_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt.
     PieCtrlRegs.PIEACK.all = PIEACK_GROUP8;
    //

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// 8.5 - SCIC Receive Interrupt
//
interrupt void SCIC_RX_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt.
     PieCtrlRegs.PIEACK.all = PIEACK_GROUP8;
    //

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// 8.6 - SCIC Transmit Interrupt
//
interrupt void SCIC_TX_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt.
     PieCtrlRegs.PIEACK.all = PIEACK_GROUP8;
    //

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// 8.7 - SCID Receive Interrupt
//
interrupt void SCID_RX_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt.
     PieCtrlRegs.PIEACK.all = PIEACK_GROUP8;
    //

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// 8.8 - SCID Transmit Interrupt
//
interrupt void SCID_TX_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt.
     PieCtrlRegs.PIEACK.all = PIEACK_GROUP8;
    //

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// 9.1 - SCIA Receive Interrupt
//
interrupt void SCIA_RX_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt.
     PieCtrlRegs.PIEACK.all = PIEACK_GROUP9;
    //

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// 9.2 - SCIA Transmit Interrupt
//
interrupt void SCIA_TX_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt.
     PieCtrlRegs.PIEACK.all = PIEACK_GROUP9;
    //

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// 9.3 - SCIB Receive Interrupt
//
interrupt void SCIB_RX_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt.
     PieCtrlRegs.PIEACK.all = PIEACK_GROUP9;
    //

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// 9.4 - SCIB Transmit Interrupt
//
interrupt void SCIB_TX_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt.
     PieCtrlRegs.PIEACK.all = PIEACK_GROUP9;
    //

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// 9.5 - CANA Interrupt 0
//
interrupt void CANA0_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt.
     PieCtrlRegs.PIEACK.all = PIEACK_GROUP9;
    //

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// 9.6 - CANA Interrupt 1
//
interrupt void CANA1_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt.
     PieCtrlRegs.PIEACK.all = PIEACK_GROUP9;
    //

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// 9.7 - CANB Interrupt 0
//
interrupt void CANB0_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt.
     PieCtrlRegs.PIEACK.all = PIEACK_GROUP9;
    //

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// 9.8 - CANB Interrupt 1
//
interrupt void CANB1_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt.
     PieCtrlRegs.PIEACK.all = PIEACK_GROUP9;
    //

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// 10.1 - ADCA Event Interrupt
//
interrupt void ADCA_EVT_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt.
     PieCtrlRegs.PIEACK.all = PIEACK_GROUP10;
    //

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// 10.2 - ADCA Interrupt 2
//
interrupt void ADCA2_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt.
     PieCtrlRegs.PIEACK.all = PIEACK_GROUP10;
    //

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// 10.3 - ADCA Interrupt 3
//
interrupt void ADCA3_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt.
     PieCtrlRegs.PIEACK.all = PIEACK_GROUP10;
    //

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// 10.4 - ADCA Interrupt 4
//
interrupt void ADCA4_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt.
     PieCtrlRegs.PIEACK.all = PIEACK_GROUP10;
    //

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// 10.5 - ADCB Event Interrupt
//
interrupt void ADCB_EVT_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt.
     PieCtrlRegs.PIEACK.all = PIEACK_GROUP10;
    //

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// 10.6 - ADCB Interrupt 2
//
interrupt void ADCB2_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt.
     PieCtrlRegs.PIEACK.all = PIEACK_GROUP10;
    //

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// 10.7 - ADCB Interrupt 3
//
interrupt void ADCB3_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt.
     PieCtrlRegs.PIEACK.all = PIEACK_GROUP10;
    //

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// 10.8 - ADCB Interrupt 4
//
interrupt void ADCB4_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt.
     PieCtrlRegs.PIEACK.all = PIEACK_GROUP10;
    //

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// 11.1 - CLA1 Interrupt 1
//
interrupt void CLA1_1_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt.
     PieCtrlRegs.PIEACK.all = PIEACK_GROUP11;
    //

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// 11.2 - CLA1 Interrupt 2
//
interrupt void CLA1_2_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt.
     PieCtrlRegs.PIEACK.all = PIEACK_GROUP11;
    //

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// 11.3 - CLA1 Interrupt 3
//
interrupt void CLA1_3_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt.
     PieCtrlRegs.PIEACK.all = PIEACK_GROUP11;
    //

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// 11.4 - CLA1 Interrupt 4
//
interrupt void CLA1_4_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt.
     PieCtrlRegs.PIEACK.all = PIEACK_GROUP11;
    //

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// 11.5 - CLA1 Interrupt 5
//
interrupt void CLA1_5_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt.
     PieCtrlRegs.PIEACK.all = PIEACK_GROUP11;
    //

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// 11.6 - CLA1 Interrupt 6
//
interrupt void CLA1_6_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt.
     PieCtrlRegs.PIEACK.all = PIEACK_GROUP11;
    //

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// 11.7 - CLA1 Interrupt 7
//
interrupt void CLA1_7_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt.
     PieCtrlRegs.PIEACK.all = PIEACK_GROUP11;
    //

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// 11.8 - CLA1 Interrupt 8
//
interrupt void CLA1_8_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt.
     PieCtrlRegs.PIEACK.all = PIEACK_GROUP11;
    //

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// 12.1 - XINT3 Interrupt
//
interrupt void XINT3_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt.
     PieCtrlRegs.PIEACK.all = PIEACK_GROUP12;
    //

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// 12.2 - XINT4 Interrupt
//
interrupt void XINT4_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt.
     PieCtrlRegs.PIEACK.all = PIEACK_GROUP12;
    //

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// 12.3 - XINT5 Interrupt
//
interrupt void XINT5_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt.
     PieCtrlRegs.PIEACK.all = PIEACK_GROUP12;
    //

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// 12.4 - MPOST Interrupt
//
interrupt void MPOST_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt.
     PieCtrlRegs.PIEACK.all = PIEACK_GROUP12;
    //

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// 12.5 - Flash Wrapper Operation Done Interrupt
//
interrupt void FMC_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt.
     PieCtrlRegs.PIEACK.all = PIEACK_GROUP12;
    //

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// 12.7 - FPU Overflow Interrupt
//
interrupt void FPU_OFLOW_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt.
     PieCtrlRegs.PIEACK.all = PIEACK_GROUP12;
    //

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// 12.8 - FPU Underflow Interrupt
//
interrupt void FPU_UFLOW_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt.
     PieCtrlRegs.PIEACK.all = PIEACK_GROUP12;
    //

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// 1.9 - I2CA Interrupt high priority
//
interrupt void I2CA_HIGH_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt.
     PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;
    //

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// 1.10 - System error interrupt
//
interrupt void SYS_ERR_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt.
     PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;
    //

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// 1.11 - ETHERCAT SYNC0 interrupt
//
interrupt void ECATSYNC0_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt.
     PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;
    //

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// 1.12 - ETHERCAT main interrupt
//
interrupt void ECAT_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt.
     PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;
    //

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// 1.13 - C28x CPU IPC interrupt 1
//
interrupt void CIPC0_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt.
     PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;
    //

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// 1.14 - C28x CPU IPC interrupt 2
//
interrupt void CIPC1_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt.
     PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;
    //

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// 1.15 - C28x CPU IPC interrupt 3
//
interrupt void CIPC2_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt.
     PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;
    //

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// 1.16 - C28x CPU IPC interrupt 4
//
interrupt void CIPC3_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt.
     PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;
    //

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// 2.9 -  ePWM9 Trip Zone Interrupt
//
interrupt void EPWM9_TZ_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt.
     PieCtrlRegs.PIEACK.all = PIEACK_GROUP2;
    //

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// 2.10 - ePWM10 Trip Zone Interrupt
//
interrupt void EPWM10_TZ_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt.
     PieCtrlRegs.PIEACK.all = PIEACK_GROUP2;
    //

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// 2.11 - ePWM11 Trip Zone Interrupt
//
interrupt void EPWM11_TZ_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt.
     PieCtrlRegs.PIEACK.all = PIEACK_GROUP2;
    //

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// 2.12 - ePWM12 Trip Zone Interrupt
//
interrupt void EPWM12_TZ_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt.
     PieCtrlRegs.PIEACK.all = PIEACK_GROUP2;
    //

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// 2.13 - ePWM13 Trip Zone Interrupt
//
interrupt void EPWM13_TZ_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt.
     PieCtrlRegs.PIEACK.all = PIEACK_GROUP2;
    //

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// 2.14 - ePWM14 Trip Zone Interrupt
//
interrupt void EPWM14_TZ_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt.
     PieCtrlRegs.PIEACK.all = PIEACK_GROUP2;
    //

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// 2.15 - ePWM15 Trip Zone Interrupt
//
interrupt void EPWM15_TZ_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt.
     PieCtrlRegs.PIEACK.all = PIEACK_GROUP2;
    //

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// 2.16 - ePWM16 Trip Zone Interrupt
//
interrupt void EPWM16_TZ_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt.
     PieCtrlRegs.PIEACK.all = PIEACK_GROUP2;
    //

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// 3.9 - ePWM9 Interrupt
//
interrupt void EPWM9_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt.
     PieCtrlRegs.PIEACK.all = PIEACK_GROUP3;
    //

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// 3.10 - ePWM10 Interrupt
//
interrupt void EPWM10_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt.
     PieCtrlRegs.PIEACK.all = PIEACK_GROUP3;
    //

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// 3.11 - ePWM11 Interrupt
//
interrupt void EPWM11_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt.
     PieCtrlRegs.PIEACK.all = PIEACK_GROUP3;
    //

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// 3.12 - ePWM12 Interrupt
//
interrupt void EPWM12_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt.
     PieCtrlRegs.PIEACK.all = PIEACK_GROUP3;
    //

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// 3.13 - ePWM13 Interrupt
//
interrupt void EPWM13_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt.
     PieCtrlRegs.PIEACK.all = PIEACK_GROUP3;
    //

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// 3.14 - ePWM14 Interrupt
//
interrupt void EPWM14_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt.
     PieCtrlRegs.PIEACK.all = PIEACK_GROUP3;
    //

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// 3.15 - ePWM15 Interrupt
//
interrupt void EPWM15_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt.
     PieCtrlRegs.PIEACK.all = PIEACK_GROUP3;
    //

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// 3.16 - ePWM16 Interrupt
//
interrupt void EPWM16_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt.
     PieCtrlRegs.PIEACK.all = PIEACK_GROUP3;
    //

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// 4.9 - FSIA Transmit interrupt 1
//
interrupt void FSITXA1_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt.
     PieCtrlRegs.PIEACK.all = PIEACK_GROUP4;
    //

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// 4.10 - FSIA Transmit interrupt 2
//
interrupt void FSITXA2_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt.
     PieCtrlRegs.PIEACK.all = PIEACK_GROUP4;
    //

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// 4.11 - FSIB Transmit interrupt 1
//
interrupt void FSITXB1_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt.
     PieCtrlRegs.PIEACK.all = PIEACK_GROUP4;
    //

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// 4.12 - FSIB Transmit interrupt 2
//
interrupt void FSITXB2_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt.
     PieCtrlRegs.PIEACK.all = PIEACK_GROUP4;
    //

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// 4.13 - FSIA Receive interrupt 1
//
interrupt void FSIRXA1_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt.
     PieCtrlRegs.PIEACK.all = PIEACK_GROUP4;
    //

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// 4.14 - FSIA Receive interrupt 2
//
interrupt void FSIRXA2_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt.
    PieCtrlRegs.PIEACK.all = PIEACK_GROUP4;
    //

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// 4.15 - FSIB Receive interrupt 1
//
interrupt void FSIRXB1_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt.
     PieCtrlRegs.PIEACK.all = PIEACK_GROUP4;
    //

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// 4.16 - FSIB Receive interrupt 2
//
interrupt void FSIRXB2_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt.
     PieCtrlRegs.PIEACK.all = PIEACK_GROUP4;
    //

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// 5.9 - Sigma Delta Filter Module1  Interrupt
//
interrupt void SDFM1_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt.
     PieCtrlRegs.PIEACK.all = PIEACK_GROUP5;
    //

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// 5.10 - Sigma Delta Filter Module2 Interrupt
//
interrupt void SDFM2_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt.
     PieCtrlRegs.PIEACK.all = PIEACK_GROUP5;
    //

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// 5.11 - ETHERCAT Resetout Interrupt
//
interrupt void ECATRST_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt.
    PieCtrlRegs.PIEACK.all = PIEACK_GROUP5;
    //

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// 5.12 - ETHERCAT SYNC1 interrupt
//
interrupt void ECATSYNC1_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt.
     PieCtrlRegs.PIEACK.all = PIEACK_GROUP5;
    //

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// 5.13 - Sigma Delta Filter Module1  Filter 1 Interrupt
//
interrupt void SDFM1DR1_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt.
     PieCtrlRegs.PIEACK.all = PIEACK_GROUP5;
    //

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// 5.14 - Sigma Delta Filter Module1  Filter 2 Interrupt
//
interrupt void SDFM1DR2_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt.
     PieCtrlRegs.PIEACK.all = PIEACK_GROUP5;
    //

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// 5.15 - Sigma Delta Filter Module1  Filter 3 Interrupt
//
interrupt void SDFM1DR3_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt.
     PieCtrlRegs.PIEACK.all = PIEACK_GROUP5;
    //

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// 5.16 - Sigma Delta Filter Module1  Filter 4 Interrupt
//
interrupt void SDFM1DR4_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt.
     PieCtrlRegs.PIEACK.all = PIEACK_GROUP5;
    //

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// 6.9 - SPIC Receive Interrupt
//
interrupt void SPIC_RX_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt.
     PieCtrlRegs.PIEACK.all = PIEACK_GROUP6;
    //

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// 6.10 - SPIC Transmit Interrupt
//
interrupt void SPIC_TX_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt.
     PieCtrlRegs.PIEACK.all = PIEACK_GROUP6;
    //

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// 6.11 - SPID Receive Interrupt
//
interrupt void SPID_RX_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt.
     PieCtrlRegs.PIEACK.all = PIEACK_GROUP6;
    //

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// 6.12 - SPID Transmit Interrupt
//
interrupt void SPID_TX_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt.
     PieCtrlRegs.PIEACK.all = PIEACK_GROUP6;
    //

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// 6.13 - Sigma Delta Filter Module2  Filter 1 Interrupt
//
interrupt void SDFM2DR1_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt.
     PieCtrlRegs.PIEACK.all = PIEACK_GROUP6;
    //

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// 6.14 - Sigma Delta Filter Module2  Filter 2 Interrupt
//
interrupt void SDFM2DR2_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt.
     PieCtrlRegs.PIEACK.all = PIEACK_GROUP6;
    //

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// 6.15 - Sigma Delta Filter Module2  Filter 3 Interrupt
//
interrupt void SDFM2DR3_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt.
     PieCtrlRegs.PIEACK.all = PIEACK_GROUP6;
    //

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// 6.16 - Sigma Delta Filter Module2  Filter 4 Interrupt
//
interrupt void SDFM2DR4_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt.
     PieCtrlRegs.PIEACK.all = PIEACK_GROUP6;
    //

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// 7.9 - FSIC Receive interrupt 1
//
interrupt void FSIRXC1_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt.
     PieCtrlRegs.PIEACK.all = PIEACK_GROUP7;
    //

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// 7.10 - FSIC Receive interrupt 2
//
interrupt void FSIRXC2_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt.
     PieCtrlRegs.PIEACK.all = PIEACK_GROUP7;
    //

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// 7.11 - FSID Receive interrupt 1
//
interrupt void FSIRXD1_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt.
     PieCtrlRegs.PIEACK.all = PIEACK_GROUP7;
    //

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// 7.12 - FSID Receive interrupt 2
//
interrupt void FSIRXD2_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt.
     PieCtrlRegs.PIEACK.all = PIEACK_GROUP7;
    //

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// 7.13 - FSIE Receive interrupt 1
//
interrupt void FSIRXE1_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt.
     PieCtrlRegs.PIEACK.all = PIEACK_GROUP7;
    //

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// 7.14 - FSIE Receive interrupt 2
//
interrupt void FSIRXE2_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt.
    PieCtrlRegs.PIEACK.all = PIEACK_GROUP7;
    //

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// 7.15 - FSIF Receive interrupt 1
//
interrupt void FSIRXF1_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt.
     PieCtrlRegs.PIEACK.all = PIEACK_GROUP7;
    //

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// 7.16 - FSIF Receive interrupt 2
//
interrupt void FSIRXF2_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt.
     PieCtrlRegs.PIEACK.all = PIEACK_GROUP7;
    //

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// 8.9 - FSIG Receive interrupt 1
//
interrupt void FSIRXG1_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt.
     PieCtrlRegs.PIEACK.all = PIEACK_GROUP8;
    //

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// 8.10 - FSIG Receive interrupt 2
//
interrupt void FSIRXG2_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt.
     PieCtrlRegs.PIEACK.all = PIEACK_GROUP8;
    //

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// 8.11 - FSIH Receive interrupt 1
//
interrupt void FSIRXH1_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt.
     PieCtrlRegs.PIEACK.all = PIEACK_GROUP8;
    //

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// 8.12 - FSIH Receive interrupt 2
//
interrupt void FSIRXH2_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt.
     PieCtrlRegs.PIEACK.all = PIEACK_GROUP8;
    //

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// 8.13 - CLB5 Interrupt
//
interrupt void CLB5_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt.
     PieCtrlRegs.PIEACK.all = PIEACK_GROUP8;
    //

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// 8.14 - CLB6 Interrupt
//
interrupt void CLB6_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt.
     PieCtrlRegs.PIEACK.all = PIEACK_GROUP8;
    //

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// 8.15 - CLB7 Interrupt
//
interrupt void CLB7_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt.
     PieCtrlRegs.PIEACK.all = PIEACK_GROUP8;
    //

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// 8.16 - CLB8 Interrupt
//
interrupt void CLB8_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt.
     PieCtrlRegs.PIEACK.all = PIEACK_GROUP8;
    //

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// 9.9 - MCAN Sub-System Interrupt 0
//
interrupt void MCANA_0_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt.
     PieCtrlRegs.PIEACK.all = PIEACK_GROUP9;
    //

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// 9.10 - MCAN Sub-System Interrupt 1
//
interrupt void MCANA_1_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt.
     PieCtrlRegs.PIEACK.all = PIEACK_GROUP9;
    //

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// 9.11 - MCAN Sub-System ECC error Interrupt
//
interrupt void MCANA_ECC_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt.
     PieCtrlRegs.PIEACK.all = PIEACK_GROUP9;
    //

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// 9.12 - MCAN Sub-System wakeup Interrupt
//
interrupt void MCANA_WAKE_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt.
     PieCtrlRegs.PIEACK.all = PIEACK_GROUP9;
    //

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// 9.13 - PMBUSA Interrupt
//
interrupt void PMBUSA_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt.
     PieCtrlRegs.PIEACK.all = PIEACK_GROUP9;
    //

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// 9.14 - CM Reset Status Interrupt
//
interrupt void CM_STATUS_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt.
     PieCtrlRegs.PIEACK.all = PIEACK_GROUP9;
    //

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// 9.15 - USBA Interrupt
//
interrupt void USBA_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt.
     PieCtrlRegs.PIEACK.all = PIEACK_GROUP9;
    //

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// 10.9 - ADCC Event Interrupt
//
interrupt void ADCC_EVT_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt.
     PieCtrlRegs.PIEACK.all = PIEACK_GROUP10;
    //

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// 10.10 - ADCC Interrupt 2
//
interrupt void ADCC2_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt.
    PieCtrlRegs.PIEACK.all = PIEACK_GROUP10;
    //

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// 10.11 - ADCC Interrupt 3
//
interrupt void ADCC3_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt.
    PieCtrlRegs.PIEACK.all = PIEACK_GROUP10;
    //

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// 10.12 - ADCC Interrupt 4
//
interrupt void ADCC4_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt.
    PieCtrlRegs.PIEACK.all = PIEACK_GROUP10;
    //

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// 10.13 - ADCD Event Interrupt
//
interrupt void ADCD_EVT_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt.
        PieCtrlRegs.PIEACK.all = PIEACK_GROUP10;
    //

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// 10.14 - ADCD Interrupt 2
//
interrupt void ADCD2_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt.
    PieCtrlRegs.PIEACK.all = PIEACK_GROUP10;
    //

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// 10.15 - ADCD Interrupt 3
//
interrupt void ADCD3_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt.
     PieCtrlRegs.PIEACK.all = PIEACK_GROUP10;
    //

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// 10.16 - ADCD Interrupt 4
//
interrupt void ADCD4_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt.
     PieCtrlRegs.PIEACK.all = PIEACK_GROUP10;
    //

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// 11.9 - CM to CPU IPC Interrupt 0
//
interrupt void CMTOCPUXIPC0_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt.
     PieCtrlRegs.PIEACK.all = PIEACK_GROUP11;
    //

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// 11.10 - CM to CPU IPC Interrupt 1
//
interrupt void CMTOCPUXIPC1_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt.
     PieCtrlRegs.PIEACK.all = PIEACK_GROUP11;
    //

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// 11.11 - CM to CPU IPC Interrupt 2
//
interrupt void CMTOCPUXIPC2_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt.
     PieCtrlRegs.PIEACK.all = PIEACK_GROUP11;
    //

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// 11.12 - CM to CPU IPC Interrupt 3
//
interrupt void CMTOCPUXIPC3_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt.
     PieCtrlRegs.PIEACK.all = PIEACK_GROUP11;
    //

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// 11.13 - CM to CPU IPC Interrupt 4
//
interrupt void CMTOCPUXIPC4_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt.
     PieCtrlRegs.PIEACK.all = PIEACK_GROUP11;
    //

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// 11.14 - CM to CPU IPC Interrupt 5
//
interrupt void CMTOCPUXIPC5_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt.
     PieCtrlRegs.PIEACK.all = PIEACK_GROUP11;
    //

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// 11.15 - CM to CPU IPC Interrupt 6
//
interrupt void CMTOCPUXIPC6_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt.
     PieCtrlRegs.PIEACK.all = PIEACK_GROUP11;
    //

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// 11.16 - CM to CPU IPC Interrupt 7
//
interrupt void CMTOCPUXIPC7_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt.
    PieCtrlRegs.PIEACK.all = PIEACK_GROUP11;
    //

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// 12.10 - eCAP6 Interrupt 2
//
interrupt void ECAP6_2_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt.
     PieCtrlRegs.PIEACK.all = PIEACK_GROUP12;
    //

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// 12.11 - eCAP7 Interrupt 2
//
interrupt void ECAP7_2_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt.
     PieCtrlRegs.PIEACK.all = PIEACK_GROUP12;
    //

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// 12.13 - CPU BGCRC module interrupt
//
interrupt void CPUCRC_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt.
     PieCtrlRegs.PIEACK.all = PIEACK_GROUP12;
    //

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// 12.14 - CLA1 BGCRC module interrupt
//
interrupt void CLA1CRC_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt.
     PieCtrlRegs.PIEACK.all = PIEACK_GROUP12;
    //

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// 12.15 - CLA Overflow Interrupt
//
interrupt void CLA_OVERFLOW_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt.
    PieCtrlRegs.PIEACK.all = PIEACK_GROUP12;
    //

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// 12.16 - CLA Underflow Interrupt
//
interrupt void CLA_UNDERFLOW_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt.
     PieCtrlRegs.PIEACK.all = PIEACK_GROUP12;
    //

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// Catch-all Default ISRs:
//

//
// PIE_RESERVED_ISR - Reserved ISR
//
interrupt void PIE_RESERVED_ISR(void)
{
    asm ("      ESTOP0");
    for(;;);
}

//
// EMPTY_ISR - Only does a return
//
interrupt void EMPTY_ISR(void)
{

}

//
// NOTUSED_ISR - Unused ISR
//
interrupt void NOTUSED_ISR(void)
{
    asm ("      ESTOP0");
    for(;;);
}

//
// End of File
//

