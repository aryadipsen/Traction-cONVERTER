//###########################################################################
//
// FILE:   f2838x_adc.c
//
// TITLE:  F2838x Adc Support Functions.
//
//###########################################################################
//
//
// 
// C2000Ware v5.04.00.00
//
// Copyright (C) 2024 Texas Instruments Incorporated - http://www.ti.com
//
// Author: Dr. Aryadip Sen
//###########################################################################

//
// Included Files
//
#include "f2838x_device.h"
#include "f2838x_examples.h"
#include "Traction_Converter_Master.h"
#include "f28x_project.h"
//

/**********************************************************************
* Function: InitAdca()
*
* Description: Initializes ADC on the F28x38D
**********************************************************************/
void   InitAdc(void)
   {

   // Configure ADC
   EALLOW;


   //--- Reset the ADC.  This is good programming practice.
   //--- Resetting ADCs - A, B, C and D
       DevCfgRegs.SOFTPRES13.bit.ADC_A = 1;    // ADC A is reset
       DevCfgRegs.SOFTPRES13.bit.ADC_A = 0;    // ADC A is released from reset
       DevCfgRegs.SOFTPRES13.bit.ADC_B = 1;    // ADC B is reset
       DevCfgRegs.SOFTPRES13.bit.ADC_B = 0;    // ADC B is released from reset
       DevCfgRegs.SOFTPRES13.bit.ADC_C = 1;    // ADC C is reset
       DevCfgRegs.SOFTPRES13.bit.ADC_C = 0;    // ADC C is released from reset
       DevCfgRegs.SOFTPRES13.bit.ADC_D = 1;    // ADC D is reset
       DevCfgRegs.SOFTPRES13.bit.ADC_D = 0;    // ADC D is released from reset
   //--- Configure the ADC base registers
       //--- Configuring ADC A and ADC B base registers
           AdcaRegs.ADCCTL1.all = 0x0004;      // Main ADC A configuration
           AdcbRegs.ADCCTL1.all = 0x0004;      // Main ADC B configuration
           AdccRegs.ADCCTL1.all = 0x0004;      // Main ADC C configuration
           AdcdRegs.ADCCTL1.all = 0x0004;      // Main ADC D configuration
       // bit 15-14     00:     reserved
       // bit 13        0:      ADCBSY, ADC busy, read-only
       // bit 12        0:      reserved
       // bit 11-8      0's:    ADCBSYCHN, ADC busy channel, read-only
       // bit 7         0:      ADCPWDNZ, ADC power down, 0=powered down, 1=powered up
       // bit 6-3       0000:   reserved
       // bit 2         1:      INTPULSEPOS, INT pulse generation, 0=start of conversion, 1=end of conversion
       // bit 1-0       00:     reserved

            AdcaRegs.ADCCTL2.all = 0x0006;        // ADC A clock configuration
            AdcbRegs.ADCCTL2.all = 0x0006;      // ADC B clock configuration
            AdccRegs.ADCCTL2.all = 0x0006;     // ADC C clock configuration
            AdcdRegs.ADCCTL2.all = 0x0006;    // ADC D clock configuration
        // bit 15-8      0's:    reserved
        // bit 7         0:      SIGNALMODE, configured by AdcSetMode() below to get calibration correct
        // bit 6         0:      RESOLUTION, configured by AdcSetMode() below to get calibration correct
        // bit 5-4       00:     reserved
        // bit 3-0       0110:   PRESCALE, ADC clock prescaler.  0110=CPUCLK/4

            AdcaRegs.ADCBURSTCTL.all = 0x0000;
            AdcbRegs.ADCBURSTCTL.all = 0x0000;
            AdccRegs.ADCBURSTCTL.all = 0x0000;
            AdcdRegs.ADCBURSTCTL.all = 0x0000;
        // bit 15        0:      BURSTEN, 0=burst mode disabled, 1=burst mode enabled
        // bit 14-12     000:    reserved
        // bit 11-8      0000:   BURSTSIZE, 0=1 SOC converted (don't care)
        // bit 7-6       00:     reserved
        // bit 5-0       000000: BURSTTRIGSEL, 00=software only (don't care)

        //--- Call AdcSetMode() to configure the resolution and signal mode.
        //    This also performs the correct ADC calibration for the configured mode.
            AdcSetMode(ADC_ADCA, ADC_RESOLUTION_12BIT, ADC_SIGNALMODE_SINGLE);
            AdcSetMode(ADC_ADCB, ADC_RESOLUTION_12BIT, ADC_SIGNALMODE_SINGLE);
            AdcSetMode(ADC_ADCC, ADC_RESOLUTION_12BIT, ADC_SIGNALMODE_SINGLE);
            AdcSetMode(ADC_ADCD, ADC_RESOLUTION_12BIT, ADC_SIGNALMODE_SINGLE);

//Traction ADC Configuration
        //--- SOC0, SOC1  configuration for ADC A
            AdcaRegs.ADCSOC0CTL.bit.TRIGSEL = 0x13;     // Trigger by ePWM8 SOC A
            AdcaRegs.ADCSOC0CTL.bit.CHSEL   = 0xE;      // Convert channel ADC A ADCIN14 :I-CONVL1(Line Side Converter Current1)
            AdcaRegs.ADCSOC0CTL.bit.ACQPS   = 0x013;    // Acquisition window (20 SYSCLK Cycles)

            AdcaRegs.ADCSOC1CTL.bit.TRIGSEL = 0x13;     // Trigger by ePWM8 SOC A
            AdcaRegs.ADCSOC1CTL.bit.CHSEL   = 0xF;     //  Convert channel ADC A ADCIN15 :I-CONVL2(Line Side Converter Current1)
            AdcaRegs.ADCSOC1CTL.bit.ACQPS   = 0x013;    // Acquisition window (20 SYSCLK Cycles)



        //--- SOC0, SOC1, SCO2 configuration for ADC B
            AdcbRegs.ADCSOC0CTL.bit.TRIGSEL = 0x13;     //  Trigger by ePWM8 SOC A
            AdcbRegs.ADCSOC0CTL.bit.CHSEL   = 0x0;      // Convert channel ADC INB0 : DC link Voltage [V2] V_dc1
            AdcbRegs.ADCSOC0CTL.bit.ACQPS   = 0x013;    // Acquisition window (20 SYSCLK Cycles)

            AdcbRegs.ADCSOC1CTL.bit.TRIGSEL = 0x13;     // Trigger by ePWM8 SOC A
            AdcbRegs.ADCSOC1CTL.bit.CHSEL   = 0x3;      // Convert channel ADC INB3 : Grid Voltage, V_  grid
            AdcbRegs.ADCSOC1CTL.bit.ACQPS   = 0x013;    // Acquisition window (20 SYSCLK Cycles)

            AdcbRegs.ADCSOC2CTL.bit.TRIGSEL = 0x13;     // Trigger by ePWM8 SOC A
            AdcbRegs.ADCSOC2CTL.bit.CHSEL   = 0x4;      // Convert channel ADC INB4 : Auxilary Current ,I_aux
            AdcbRegs.ADCSOC2CTL.bit.ACQPS   = 0x013;    // Acquisition window (20 SYSCLK Cycles)

            //--- SOC0, SOC1 configuration for ADC C
            AdccRegs.ADCSOC0CTL.bit.TRIGSEL = 0x13;      // Trigger by ePWM8 SOC A
            AdccRegs.ADCSOC0CTL.bit.CHSEL   = 0x4;      // Convert channel ADC INC4 :  Grid Return Current,Igrid_rtn
            AdccRegs.ADCSOC0CTL.bit.ACQPS   = 0x013;    // Acquisition window (20 SYSCLK Cycles)

            AdccRegs.ADCSOC1CTL.bit.TRIGSEL = 0x13;    //Trigger by ePWM8 SOC A
            AdccRegs.ADCSOC1CTL.bit.CHSEL   = 0x3;     // Convert channel ADC INC3 :  Chopper Current , I_chop
            AdccRegs.ADCSOC1CTL.bit.ACQPS   = 0x013;   // Acquisition window (20 SYSCLK Cycles)

            AdccRegs.ADCSOC2CTL.bit.TRIGSEL = 0x13;    //Trigger by ePWM8 SOC A
            AdccRegs.ADCSOC2CTL.bit.CHSEL   = 0x5;     // Convert channel ADC INC5 :Harmonic Filter Current , I_harmonic
            AdccRegs.ADCSOC2CTL.bit.ACQPS   = 0x013;   // Acquisition window (20 SYSCLK Cycles)


            AdccRegs.ADCSOC3CTL.bit.TRIGSEL = 0x13;    //Trigger by ePWM8 SOC A
            AdccRegs.ADCSOC3CTL.bit.CHSEL   = 0x2;     // Convert channel ADC INC2 : Second Harmonic (100 Hz) Current ,I_harmonic2
            AdccRegs.ADCSOC3CTL.bit.ACQPS   = 0x013;  // Acquisition window (20 SYSCLK Cycles)

         //Traction ADC Configuration

        // --- SOC0, SOC1 configuration for ADC D
            AdcdRegs.ADCSOC0CTL.bit.TRIGSEL = 0x0F;     // Trigger by ePWM6 SOC A
            AdcdRegs.ADCSOC0CTL.bit.CHSEL   = 0x0;      // Convert channel ADC D0 : I_y
            AdcdRegs.ADCSOC0CTL.bit.ACQPS   = 0x013;    // Acquisition window (20 SYSCLK Cycles)

            AdcdRegs.ADCSOC1CTL.bit.TRIGSEL = 0x0F;     // Trigger by ePWM6 SOC A
            AdcdRegs.ADCSOC1CTL.bit.CHSEL   = 0x2;      // Convert channel ADC D2 :  I_g
            AdcdRegs.ADCSOC1CTL.bit.ACQPS   = 0x013;    // Acquisition window (20 SYSCLK Cycles)






            AdcaRegs.ADCINTSOCSEL1.bit.SOC0 = 0;        // ADC interrupt triggers
            AdcaRegs.ADCINTSOCSEL1.bit.SOC1 = 0;        // ADC interrupt triggers
            AdcaRegs.ADCINTSOCSEL1.bit.SOC2 = 0;        // ADC interrupt triggers

            AdcbRegs.ADCINTSOCSEL1.bit.SOC0 = 0;        // ADC interrupt triggers
            AdcbRegs.ADCINTSOCSEL1.bit.SOC1 = 0;        // ADC interrupt triggers

            AdccRegs.ADCINTSOCSEL1.bit.SOC0 = 0;        // ADC interrupt triggers
            AdccRegs.ADCINTSOCSEL1.bit.SOC1 = 0;        // ADC interrupt triggers

            AdcdRegs.ADCINTSOCSEL1.bit.SOC0 = 0;        // ADC interrupt triggers
            AdcdRegs.ADCINTSOCSEL1.bit.SOC1 = 0;        // ADC interrupt triggers


            AdcaRegs.ADCSOCPRICTL.bit.SOCPRIORITY = 0;  // SOC priority mode
            AdcbRegs.ADCSOCPRICTL.bit.SOCPRIORITY = 0;  // SOC priority mode
            AdccRegs.ADCSOCPRICTL.bit.SOCPRIORITY = 0;  // SOC priority mode
            AdcdRegs.ADCSOCPRICTL.bit.SOCPRIORITY = 0;  // SOC priority mode


                //--- ADC A1 (SOC2) interrupt configuration
                AdcaRegs.ADCINTSEL1N2.bit.INT1CONT = 1;     // Interrupt pulses
                AdcaRegs.ADCINTSEL1N2.bit.INT1E    = 1;     // ADC A interrupt enable
                AdcaRegs.ADCINTSEL1N2.bit.INT1SEL  = 2;     // EOC2 triggers the interrupt

                AdcbRegs.ADCINTSEL1N2.bit.INT1E    = 0;     // ADC B interrupt disable
                AdccRegs.ADCINTSEL1N2.bit.INT1E    = 0;     // ADC C interrupt disable
                AdcdRegs.ADCINTSEL1N2.bit.INT1E    = 0;     // ADC D interrupt disable



 // Initial Setting for Testing//

  /* AdcaRegs.ADCSOC0CTL.bit.CHSEL = 0;        // ADCIN0
   AdcaRegs.ADCSOC0CTL.bit.ACQPS = 14;
   AdcaRegs.ADCSOC0CTL.bit.TRIGSEL = 0x013;      // EPWM8 SOCA Trigger*/

   AdcaRegs.ADCINTSEL1N2.bit.INT1SEL = 0;    // ADCINT1 triggers on SOC0
   AdcaRegs.ADCINTSEL1N2.bit.INT1E = 1;      // Enable ADCINT1
   AdcaRegs.ADCINTFLGCLR.bit.ADCINT1 = 1;    // Clear interrupt flag

   // Setup SOC
  /* AdcbRegs.ADCSOC0CTL.bit.CHSEL  = 0;
   AdcbRegs.ADCSOC0CTL.bit.TRIGSEL = 0x013;   // EPMW8 SOC A Trigger
   AdcbRegs.ADCSOC0CTL.bit.ACQPS = 0x013;

   AdccRegs.ADCSOC0CTL.bit.CHSEL  = 0x3;
   AdccRegs.ADCSOC0CTL.bit.TRIGSEL = 0x013;   // EPWM8 SOCA trigger
   AdccRegs.ADCSOC0CTL.bit.ACQPS = 0x013;

   // In measurement function:
   AdcbRegs.ADCSOCFRC1.all = 1 << 0;      // force SOC0
   //while(!AdcbRegs.ADCDSTAT.bit.SOC0_EOC) {}
  // uint16_t raw = AdcbResultRegs.ADCRESULT0;
   AdccRegs.ADCSOCFRC1.all = 1 << 0;      // force SOC0*/
 /*             EPwm8Regs.ETSEL.bit.SOCAEN = 1;
                EPwm8Regs.ETSEL.bit.SOCASEL = ET_CTR_ZERO;
                EPwm8Regs.ETPS.bit.SOCAPRD = ET_1ST;


                // Start PWM counter
                EPwm8Regs.TBPRD = 1000;                    // e.g. some period
                EPwm8Regs.TBCTL.bit.CTRMODE = TB_COUNT_UP;*/


 //  EDIS;
//Enable the ADC Interrupt
           PieCtrlRegs.PIEIER1.bit.INTx1 = 1;          // Enable ADCA1 interrupt in PIE group 1
              IER |= 0x0001;                              // Enable INT1 in IER to enable PIE group

          //--- Finish up
              AdcaRegs.ADCCTL1.bit.ADCPWDNZ = 1;          // Power up the ADC A
              AdcbRegs.ADCCTL1.bit.ADCPWDNZ = 1;          // Power up the ADC B
              AdccRegs.ADCCTL1.bit.ADCPWDNZ = 1;          // Power up the ADC C
              AdcdRegs.ADCCTL1.bit.ADCPWDNZ = 1;          // Power up the ADC D
              DELAY_US(1000);                              // Wait 1 ms after power-up before using the ADC
EDIS;
   }





//
// End of file
//
