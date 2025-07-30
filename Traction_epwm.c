//###########################################################################
//
// FILE:   f2838x_epwm.c
//
// TITLE:  F2838x EPwm Initialization & Support Functions.
//
//###########################################################################
//
//
// 
// C2000Ware v5.04.00.00
//
// Copyright (C) 2024 Texas Instruments Incorporated - http://www.ti.com
//
// Redistribution and use in source and binary forms, with or without 
// modification, are permitted provided that the following conditions 
// are met:
// 
// Author: Dr.Aryadip Sen
// 
//
//###########################################################################

//
// Included Files
//
#include "f2838x_device.h"
#include "f2838x_examples.h"
#include "Traction_Converter_Master.h"
#include "epwm.h"


//
// InitEPwmGpio - Initialize all EPWM modules' GPIOs
//
void InitEPwm(void)
{

        asm(" EALLOW");                     // Enable EALLOW protected register access

        // Configure the prescaler to the ePWM modules.  Max ePWM input clock is 100 MHz.
        ClkCfgRegs.PERCLKDIVSEL.bit.EPWMCLKDIV = 1;     // EPWMCLK divider from PLLSYSCLK.  0=/1, 1=/2

        // Must disable the clock to the ePWM modules if you want all ePWM modules synchronized.
        CpuSysRegs.PCLKCR0.bit.TBCLKSYNC = 0;

        asm(" EDIS");                       // Disable EALLOW protected register access


        asm(" EALLOW");                         // Enable EALLOW protected register access
          DevCfgRegs.SOFTPRES2.bit.EPWM1 = 1;     // ePWM1 is reset
          DevCfgRegs.SOFTPRES2.bit.EPWM1 = 0;     // ePWM1 is released from reset
          DevCfgRegs.SOFTPRES2.bit.EPWM2 = 1;     // ePWM2 is reset
          DevCfgRegs.SOFTPRES2.bit.EPWM2 = 0;     // ePWM2 is released from reset
          DevCfgRegs.SOFTPRES2.bit.EPWM3 = 1;     // ePWM3 is reset
          DevCfgRegs.SOFTPRES2.bit.EPWM3 = 0;     // ePWM3 is released from reset
          DevCfgRegs.SOFTPRES2.bit.EPWM4 = 1;     // ePWM4 is reset
          DevCfgRegs.SOFTPRES2.bit.EPWM4 = 0;     // ePWM4 is released from reset
          DevCfgRegs.SOFTPRES2.bit.EPWM5 = 1;     // ePWM5 is reset
          DevCfgRegs.SOFTPRES2.bit.EPWM5 = 0;     // ePWM5 is released from reset
          DevCfgRegs.SOFTPRES2.bit.EPWM8 = 1;     // ePWM8 is reset
          DevCfgRegs.SOFTPRES2.bit.EPWM8 = 0;     // ePWM8 is released from reset

          asm(" EDIS");                           // Disable EALLOW protected register access

          // ePWM1 Module Initialization : Rectifier 1 leg-1
          //---------------------------------------------------------------------------------------------
              EPwm1Regs.TBCTL.bit.CTRMODE = 0x3;               // Disable the timer'
              EPwm1Regs.TBCTL.all         = 0xC033;           // Configure timer control register
              // bit 15-14     11:     FREE/SOFT, 11 = ignore emulation suspend
              // bit 13        0:      PHSDIR, 0 = count down after sync event
              // bit 12-10     000:    CLKDIV, 000 => TBCLK = HSPCLK/1
              // bit 9-7       000:    HSPCLKDIV, 000 => HSPCLK = EPWMCLK/1
              // bit 6         0:      SWFSYNC, 0 = no software sync produced
              // bit 5-4       11:     SYNCOSEL, 11 = sync-out disabled
              // bit 3         0:      PRDLD, 0 = reload PRD on counter=0
              // bit 2         0:      PHSEN, 0 = phase control disabled
              // bit 1-0       11:     CTRMODE, 11 = timer stopped (disabled)

              EPwm1Regs.TBCTL.bit.HSPCLKDIV = 0;
              EPwm1Regs.TBCTL.bit.CLKDIV    = 0;                   // Clock to EPWM Module is 100 MHz
              EPwm1Regs.TBCTL.bit.CTRMODE   = 2;                   // Count Up-Down Mode
              EPwm1Regs.TBPRD               = PWM_PERIOD_RECTIFIER;// 1 kHz switching frequency set
              EPwm1Regs.CMPA.bit.CMPA       = 0;                   // Set PWM duty cycle to 0 initially
              EPwm1Regs.CMPCTL.all          = 0x0000;              // Shadowing of compare registers set to default
              EPwm1Regs.AQCTLA.all          = 0x0090;              // Normal Sine-Triangle PWM
          /*
              EPwm1Regs.ETSEL.bit.SOCAEN    = 1;                   // Enable SOCA
              EPwm1Regs.ETSEL.bit.SOCASEL   = 3;                   // SOCA on CTR = 0 or CTR = PRD
              EPwm1Regs.ETPS.bit.SOCAPRD    = 1;                   // sampling frequency = 2*switching frequency = 2 kHz
          */
              asm(" EALLOW");                                      // Enable EALLOW protected register access
              EPwm1Regs.DCTRIPSEL.bit.DCAHCOMPSEL    = 3;          // select TRIPIN4 as source for DCAH
              EPwm1Regs.TZDCSEL.bit.DCAEVT1          = 2;          // define event as  : DCAH high
              EPwm1Regs.DCACTL.bit.EVT1SRCSEL        = 0;          // DCAEVT1 is selected as source
              EPwm1Regs.DCACTL.bit.EVT1FRCSYNCSEL    = 0;          // Source is synchronized with EPWMCLK
              EPwm1Regs.DCACTL.bit.EVT1SOCE          = 0;          // SOC generation Disabled
              EPwm1Regs.DCACTL.bit.EVT1SYNCE         = 0;          // Synch disabled
              EPwm1Regs.DCACTL.bit.EVT1LATSEL        = 1;          // DCAEVT1 Latch enabled
              EPwm1Regs.TZCTL2.bit.ETZE              = 1;          // Use data from TZCTL2 and TZCTLDCA
              EPwm1Regs.TZCTL2.bit.TZAU              = 2;          // Force EPWMA to zero on UP count   if TZ1-TZ6 occurs
              EPwm1Regs.TZCTL2.bit.TZAD              = 2;          // Force EPWMA to zero on down count if TZ1-TZ6 occurs
              EPwm1Regs.TZCTL2.bit.TZBU              = 2;          // Force EPWMB to zero on UP count   if TZ1-TZ6 occurs
              EPwm1Regs.TZCTL2.bit.TZBD              = 2;          // Force EPWMB to zero on down count if TZ1-TZ6 occurs
              EPwm1Regs.TZCTLDCA.bit.DCAEVT1D        = 2;          // Force EPWMA to zero on down count if DCAEVT1 occurs
              EPwm1Regs.TZCTLDCA.bit.DCAEVT1U        = 2;          // Force EPWMA to zero on up count   if DCAEVT1 occurs
              EPwm1Regs.TZCTLDCB.bit.DCBEVT1D        = 2;          // Force EPWMB to zero on down count if DCAEVT1 occurs
              EPwm1Regs.TZCTLDCB.bit.DCBEVT1U        = 2;          // Force EPWMB to zero on up count   if DCAEVT1 occurs
              EPwm1Regs.TZSEL.bit.DCAEVT1            = 1;          // DCAEVT1 trip as One Shot
              EPwm1Regs.TZSEL.bit.OSHT1              = 1;          // TZ1 as one Shot
              EPwm1Regs.TZEINT.bit.OST               = 1;          // enable One Shot Trip interrupt

              asm(" EDIS");                                        // Disable EALLOW protected register access


//---------------------------------------------------------------------------------------------
// ePWM2 Module Initialization : Rectifier 1 leg-2
//---------------------------------------------------------------------------------------------
    EPwm2Regs.TBCTL.bit.CTRMODE = 0x3;      // Disable the timer'
    EPwm2Regs.TBCTL.all         = 0xC033;   // Configure timer control register
    // bit 15-14     11:     FREE/SOFT, 11 = ignore emulation suspend
    // bit 13        0:      PHSDIR, 0 = count down after sync event
    // bit 12-10     000:    CLKDIV, 000 => TBCLK = HSPCLK/1
    // bit 9-7       000:    HSPCLKDIV, 000 => HSPCLK = EPWMCLK/1
    // bit 6         0:      SWFSYNC, 0 = no software sync produced
    // bit 5-4       11:     SYNCOSEL, 11 = sync-out disabled
    // bit 3         0:      PRDLD, 0 = reload PRD on counter=0
    // bit 2         0:      PHSEN, 0 = phase control disabled
    // bit 1-0       11:     CTRMODE, 11 = timer stopped (disabled)

    EPwm2Regs.TBCTL.bit.HSPCLKDIV = 0;
    EPwm2Regs.TBCTL.bit.CLKDIV    = 0;                   // Clock to EPWM Module is 100 MHz
    EPwm2Regs.TBCTL.bit.CTRMODE   = 2;                   // Count Up-Down Mode
    EPwm2Regs.TBPRD               = PWM_PERIOD_RECTIFIER;    // 1 kHz switching frequency set
    EPwm2Regs.CMPA.bit.CMPA       = 0;                   // 0 Duty Cycle at initialization
    EPwm2Regs.CMPCTL.all          = 0x0000;              // Shadowing of compare registers set to default
    EPwm2Regs.AQCTLA.all          = 0x0090;              // Normal Sine-Triangle PWM

    asm(" EALLOW");                                      // Enable EALLOW protected register access
    EPwm2Regs.DCTRIPSEL.bit.DCAHCOMPSEL    = 3;          // select TRIPIN4 as source for DCAH
    EPwm2Regs.TZDCSEL.bit.DCAEVT1          = 2;          // define event as  : DCAH high
    EPwm2Regs.DCACTL.bit.EVT1SRCSEL        = 0;          // DCAEVT1 is selected as source
    EPwm2Regs.DCACTL.bit.EVT1FRCSYNCSEL    = 0;          // Source is synchronized with EPWMCLK
    EPwm2Regs.DCACTL.bit.EVT1SOCE          = 0;          // SOC generation Disabled
    EPwm2Regs.DCACTL.bit.EVT1SYNCE         = 0;          // Synch disabled
    EPwm2Regs.DCACTL.bit.EVT1LATSEL        = 1;          // DCAEVT1 Latch enabled
    EPwm2Regs.TZCTL2.bit.ETZE              = 1;          // Use data from TZCTL2 and TZCTLDCA
    EPwm2Regs.TZCTL2.bit.TZAU              = 2;          // Force EPWMA to zero on UP count   if TZ1-TZ6 occurs
    EPwm2Regs.TZCTL2.bit.TZAD              = 2;          // Force EPWMA to zero on down count if TZ1-TZ6 occurs
    EPwm2Regs.TZCTLDCA.bit.DCAEVT1D        = 2;          // Force EPWMA to zero on down count if DCAEVT1 occurs
    EPwm2Regs.TZCTLDCA.bit.DCAEVT1U        = 2;          // Force EPWMA to zero on up count   if DCAEVT1 occurs
    EPwm2Regs.TZCTL2.bit.TZBU              = 2;          // Force EPWMB to zero on UP count   if TZ1-TZ6 occurs
    EPwm2Regs.TZCTL2.bit.TZBD              = 2;          // Force EPWMB to zero on down count if TZ1-TZ6 occurs
    EPwm2Regs.TZCTLDCB.bit.DCBEVT1D        = 2;          // Force EPWMA to zero on down count if DCAEVT1 occurs
    EPwm2Regs.TZCTLDCB.bit.DCBEVT1U        = 2;          // Force EPWMA to zero on up count   if DCAEVT1 occurs
    EPwm2Regs.TZSEL.bit.DCAEVT1            = 1;          // DCAEVT1 trip as One Shot
    EPwm2Regs.TZSEL.bit.OSHT1              = 1;          // TZ1 as one Shot

    asm(" EDIS");                                        // Disable EALLOW protected register access



    //---------------------------------------------------------------------------------------------
    // ePWM3 Module Initialization : Rectifier 2 leg-1

    //---------------------------------------------------------------------------------------------
         EPwm3Regs.TBCTL.bit.CTRMODE = 0x3;               // Disable the timer'
         EPwm3Regs.TBCTL.all         = 0xC033;           // Configure timer control register
         // bit 15-14     11:     FREE/SOFT, 11 = ignore emulation suspend
         // bit 13        0:      PHSDIR, 0 = count down after sync event
         // bit 12-10     000:    CLKDIV, 000 => TBCLK = HSPCLK/1
         // bit 9-7       000:    HSPCLKDIV, 000 => HSPCLK = EPWMCLK/1
         // bit 6         0:      SWFSYNC, 0 = no software sync produced
         // bit 5-4       11:     SYNCOSEL, 11 = sync-out disabled
         // bit 3         0:      PRDLD, 0 = reload PRD on counter=0
         // bit 2         0:      PHSEN, 0 = phase control disabled
         // bit 1-0       11:     CTRMODE, 11 = timer stopped (disabled)

         EPwm3Regs.TBCTL.bit.HSPCLKDIV = 0;
         EPwm3Regs.TBCTL.bit.CLKDIV    = 0;                   // Clock to EPWM Module is 100 MHz
         EPwm3Regs.TBCTL.bit.CTRMODE   = 2;                   // Count Up-Down Mode
         EPwm3Regs.TBPRD               = PWM_PERIOD_RECTIFIER;// 1 kHz switching frequency set
         EPwm3Regs.CMPA.bit.CMPA       = 0;                   // Set PWM duty cycle to 0 initially
         EPwm3Regs.CMPCTL.all          = 0x0000;              // Shadowing of compare registers set to default
         EPwm3Regs.AQCTLA.all          = 0x0090;              // Normal Sine-Triangle PWM */

         EPwm1Regs.ETSEL.bit.SOCAEN    = 1;                   // Enable SOCA
         EPwm1Regs.ETSEL.bit.SOCASEL   = 3;                   // SOCA on CTR = 0 or CTR = PRD
         EPwm1Regs.ETPS.bit.SOCAPRD    = 1;                   // sampling frequency = 2*switching frequency = 2 kHz

         asm(" EALLOW");                                      // Enable EALLOW protected register access
         EPwm3Regs.DCTRIPSEL.bit.DCAHCOMPSEL    = 3;          // select TRIPIN4 as source for DCAH
         EPwm3Regs.TZDCSEL.bit.DCAEVT1          = 2;          // define event as  : DCAH high
         EPwm3Regs.DCACTL.bit.EVT1SRCSEL        = 0;          // DCAEVT1 is selected as source
         EPwm3Regs.DCACTL.bit.EVT1FRCSYNCSEL    = 0;          // Source is synchronized with EPWMCLK
         EPwm3Regs.DCACTL.bit.EVT1SOCE          = 0;          // SOC generation Disabled
         EPwm3Regs.DCACTL.bit.EVT1SYNCE         = 0;          // Synch disabled
         EPwm3Regs.DCACTL.bit.EVT1LATSEL        = 1;          // DCAEVT1 Latch enabled
         EPwm3Regs.TZCTL2.bit.ETZE              = 1;          // Use data from TZCTL2 and TZCTLDCA
         EPwm3Regs.TZCTL2.bit.TZAU              = 2;          // Force EPWMA to zero on UP count   if TZ1-TZ6 occurs
         EPwm3Regs.TZCTL2.bit.TZAD              = 2;          // Force EPWMA to zero on down count if TZ1-TZ6 occurs
         EPwm3Regs.TZCTL2.bit.TZBU              = 2;          // Force EPWMB to zero on UP count   if TZ1-TZ6 occurs
         EPwm3Regs.TZCTL2.bit.TZBD              = 2;          // Force EPWMB to zero on down count if TZ1-TZ6 occurs
         EPwm3Regs.TZCTLDCA.bit.DCAEVT1D        = 2;          // Force EPWMA to zero on down count if DCAEVT1 occurs
         EPwm3Regs.TZCTLDCA.bit.DCAEVT1U        = 2;          // Force EPWMA to zero on up count   if DCAEVT1 occurs
         EPwm3Regs.TZCTLDCB.bit.DCBEVT1D        = 2;          // Force EPWMB to zero on down count if DCAEVT1 occurs
         EPwm3Regs.TZCTLDCB.bit.DCBEVT1U        = 2;          // Force EPWMB to zero on up count   if DCAEVT1 occurs
         EPwm3Regs.TZSEL.bit.DCAEVT1            = 1;          // DCAEVT1 trip as One Shot
         EPwm3Regs.TZSEL.bit.OSHT1              = 1;          // TZ1 as one Shot
         EPwm3Regs.TZEINT.bit.OST               = 1;          // enable One Shot Trip interrupt

         asm(" EDIS");                                        // Disable EALLOW protected register access

     //---------------------------------------------------------------------------------------------
     // ePWM4 Module Initialization : Rectifier 2 leg-2
     //---------------------------------------------------------------------------------------------
         EPwm4Regs.TBCTL.bit.CTRMODE = 0x3;      // Disable the timer'
         EPwm4Regs.TBCTL.all         = 0xC033;   // Configure timer control register
         // bit 15-14     11:     FREE/SOFT, 11 = ignore emulation suspend
         // bit 13        0:      PHSDIR, 0 = count down after sync event
         // bit 12-10     000:    CLKDIV, 000 => TBCLK = HSPCLK/1
         // bit 9-7       000:    HSPCLKDIV, 000 => HSPCLK = EPWMCLK/1
         // bit 6         0:      SWFSYNC, 0 = no software sync produced
         // bit 5-4       11:     SYNCOSEL, 11 = sync-out disabled
         // bit 3         0:      PRDLD, 0 = reload PRD on counter=0
         // bit 2         0:      PHSEN, 0 = phase control disabled
         // bit 1-0       11:     CTRMODE, 11 = timer stopped (disabled)

         EPwm4Regs.TBCTL.bit.HSPCLKDIV = 0;
         EPwm4Regs.TBCTL.bit.CLKDIV    = 0;                   // Clock to EPWM Module is 100 MHz
         EPwm4Regs.TBCTL.bit.CTRMODE   = 2;                   // Count Up-Down Mode
         EPwm4Regs.TBPRD               = PWM_PERIOD_RECTIFIER;    // 1 kHz switching frequency set
         EPwm4Regs.CMPA.bit.CMPA       = 0;                   // 0 Duty Cycle at initialization
         EPwm4Regs.CMPCTL.all          = 0x0000;              // Shadowing of compare registers set to default
         EPwm4Regs.AQCTLA.all          = 0x0090;              // Normal Sine-Triangle PWM

         asm(" EALLOW");                                      // Enable EALLOW protected register access
         EPwm4Regs.DCTRIPSEL.bit.DCAHCOMPSEL    = 3;          // select TRIPIN4 as source for DCAH
         EPwm4Regs.TZDCSEL.bit.DCAEVT1          = 2;          // define event as  : DCAH high
         EPwm4Regs.DCACTL.bit.EVT1SRCSEL        = 0;          // DCAEVT1 is selected as source
         EPwm4Regs.DCACTL.bit.EVT1FRCSYNCSEL    = 0;          // Source is synchronized with EPWMCLK
         EPwm4Regs.DCACTL.bit.EVT1SOCE          = 0;          // SOC generation Disabled
         EPwm4Regs.DCACTL.bit.EVT1SYNCE         = 0;          // Synch disabled
         EPwm4Regs.DCACTL.bit.EVT1LATSEL        = 1;          // DCAEVT1 Latch enabled
         EPwm4Regs.TZCTL2.bit.ETZE              = 1;          // Use data from TZCTL2 and TZCTLDCA
         EPwm4Regs.TZCTL2.bit.TZAU              = 2;          // Force EPWMA to zero on UP count   if TZ1-TZ6 occurs
         EPwm4Regs.TZCTL2.bit.TZAD              = 2;          // Force EPWMA to zero on down count if TZ1-TZ6 occurs
         EPwm4Regs.TZCTLDCA.bit.DCAEVT1D        = 2;          // Force EPWMA to zero on down count if DCAEVT1 occurs
         EPwm4Regs.TZCTLDCA.bit.DCAEVT1U        = 2;          // Force EPWMA to zero on up count   if DCAEVT1 occurs
         EPwm4Regs.TZCTL2.bit.TZBU              = 2;          // Force EPWMB to zero on UP count   if TZ1-TZ6 occurs
         EPwm4Regs.TZCTL2.bit.TZBD              = 2;          // Force EPWMB to zero on down count if TZ1-TZ6 occurs
         EPwm4Regs.TZCTLDCB.bit.DCBEVT1D        = 2;          // Force EPWMA to zero on down count if DCAEVT1 occurs
         EPwm4Regs.TZCTLDCB.bit.DCBEVT1U        = 2;          // Force EPWMA to zero on up count   if DCAEVT1 occurs
         EPwm4Regs.TZSEL.bit.DCAEVT1            = 1;          // DCAEVT1 trip as One Shot
         EPwm4Regs.TZSEL.bit.OSHT1              = 1;          // TZ1 as one Shot

         asm(" EDIS");                                       // Disable EALLOW protected register access

         //---------------------------------------------------------------------------------------------
         // ePWM4 Module Initialization : Rectifier 2 leg-2
         //---------------------------------------------------------------------------------------------
             EPwm5Regs.TBCTL.bit.CTRMODE = 0x3;      // Disable the timer'
             EPwm5Regs.TBCTL.all         = 0xC033;   // Configure timer control register
             // bit 15-14     11:     FREE/SOFT, 11 = ignore emulation suspend
             // bit 13        0:      PHSDIR, 0 = count down after sync event
             // bit 12-10     000:    CLKDIV, 000 => TBCLK = HSPCLK/1
             // bit 9-7       000:    HSPCLKDIV, 000 => HSPCLK = EPWMCLK/1
             // bit 6         0:      SWFSYNC, 0 = no software sync produced
             // bit 5-4       11:     SYNCOSEL, 11 = sync-out disabled
             // bit 3         0:      PRDLD, 0 = reload PRD on counter=0
             // bit 2         0:      PHSEN, 0 = phase control disabled
             // bit 1-0       11:     CTRMODE, 11 = timer stopped (disabled)

             EPwm5Regs.TBCTL.bit.HSPCLKDIV = 0;
             EPwm5Regs.TBCTL.bit.CLKDIV    = 0;                   // Clock to EPWM Module is 100 MHz
             EPwm5Regs.TBCTL.bit.CTRMODE   = 2;                   // Count Up-Down Mode
             EPwm5Regs.TBPRD               = PWM_PERIOD_RECTIFIER;    // 1 kHz switching frequency set
             EPwm5Regs.CMPA.bit.CMPA       = 0;                   // 0 Duty Cycle at initialization
             EPwm5Regs.CMPCTL.all          = 0x0000;              // Shadowing of compare registers set to default
             EPwm5Regs.AQCTLA.all          = 0x0090;              // Normal Sine-Triangle PWM

             asm(" EALLOW");                                      // Enable EALLOW protected register access
             EPwm5Regs.DCTRIPSEL.bit.DCAHCOMPSEL    = 3;          // select TRIPIN4 as source for DCAH
             EPwm5Regs.TZDCSEL.bit.DCAEVT1          = 2;          // define event as  : DCAH high
             EPwm5Regs.DCACTL.bit.EVT1SRCSEL        = 0;          // DCAEVT1 is selected as source
             EPwm5Regs.DCACTL.bit.EVT1FRCSYNCSEL    = 0;          // Source is synchronized with EPWMCLK
             EPwm5Regs.DCACTL.bit.EVT1SOCE          = 0;          // SOC generation Disabled
             EPwm5Regs.DCACTL.bit.EVT1SYNCE         = 0;          // Synch disabled
             EPwm5Regs.DCACTL.bit.EVT1LATSEL        = 1;          // DCAEVT1 Latch enabled
             EPwm5Regs.TZCTL2.bit.ETZE              = 1;          // Use data from TZCTL2 and TZCTLDCA
             EPwm5Regs.TZCTL2.bit.TZAU              = 2;          // Force EPWMA to zero on UP count   if TZ1-TZ6 occurs
             EPwm5Regs.TZCTL2.bit.TZAD              = 2;          // Force EPWMA to zero on down count if TZ1-TZ6 occurs
             EPwm5Regs.TZCTLDCA.bit.DCAEVT1D        = 2;          // Force EPWMA to zero on down count if DCAEVT1 occurs
             EPwm5Regs.TZCTLDCA.bit.DCAEVT1U        = 2;          // Force EPWMA to zero on up count   if DCAEVT1 occurs
             EPwm5Regs.TZCTL2.bit.TZBU              = 2;          // Force EPWMB to zero on UP count   if TZ1-TZ6 occurs
             EPwm5Regs.TZCTL2.bit.TZBD              = 2;          // Force EPWMB to zero on down count if TZ1-TZ6 occurs
             EPwm5Regs.TZCTLDCB.bit.DCBEVT1D        = 2;          // Force EPWMA to zero on down count if DCAEVT1 occurs
             EPwm5Regs.TZCTLDCB.bit.DCBEVT1U        = 2;          // Force EPWMA to zero on up count   if DCAEVT1 occurs
             EPwm5Regs.TZSEL.bit.DCAEVT1            = 1;          // DCAEVT1 trip as One Shot
             EPwm5Regs.TZSEL.bit.OSHT1              = 1;          // TZ1 as one Shot

             asm(" EDIS");                                       // Disable EALLOW protected register access

         //---------------------------------------------------------------------------------------------
           // ePWM8 Module Initialization : For making sampling frequency = 30 kHz
           //---------------------------------------------------------------------------------------------
             EPwm8Regs.TBCTL.bit.CTRMODE = 0x3;      // Disable the timer'
             EPwm8Regs.TBCTL.all         = 0xC033;   // Configure timer control register
             // bit 15-14     11:     FREE/SOFT, 11 = ignore emulation suspend
             // bit 13        0:      PHSDIR, 0 = count down after sync event
             // bit 12-10     000:    CLKDIV, 000 => TBCLK = HSPCLK/1
             // bit 9-7       000:    HSPCLKDIV, 000 => HSPCLK = EPWMCLK/1
             // bit 6         0:      SWFSYNC, 0 = no software sync produced
             // bit 5-4       11:     SYNCOSEL, 11 = sync-out disabled
             // bit 3         0:      PRDLD, 0 = reload PRD on counter=0
             // bit 2         0:      PHSEN, 0 = phase control disabled
             // bit 1-0       11:     CTRMODE, 11 = timer stopped (disabled)

             EPwm8Regs.TBCTL.bit.HSPCLKDIV = 0;
             EPwm8Regs.TBCTL.bit.CLKDIV    = 0;                   // Clock to EPWM Module is 100 MHz
             EPwm8Regs.TBCTL.bit.CTRMODE   = 2;                   // Count Up Mode
             EPwm8Regs.TBPRD               = SAMPLING_FREQUENCY_NUMBER;    // 15 kHz switching frequency set
             EPwm8Regs.CMPA.bit.CMPA       = 0;                   // 0 Duty Cycle at initialization
             EPwm8Regs.CMPCTL.all          = 0x0000;              // Shadowing of compare registers set to default
             EPwm8Regs.AQCTLA.all          = 0x0090;              // Normal Sine-Triangle PWM

             EPwm8Regs.ETSEL.bit.SOCAEN    = 1;                   // Enable SOCA
             EPwm8Regs.ETSEL.bit.SOCASEL   = 3;                   // SOCA on CTR = 0 or CTR = PRD
             EPwm8Regs.ETPS.bit.SOCAPRD    = 1;                   // sampling frequency = 2*switching frequency = 30 kHz

             asm(" EDIS");                                        // Disable EALLOW protected register access


            // ------------------------------------------------------------
                       // Phase Synchronizations
            // ------------------------------------------------------------


         EPwm1Regs.EPWMSYNCINSEL.bit.SEL = 0x01;  //generate a synchout if CTR = 0

         EPwm2Regs.TBCTL.bit.PHSEN  = 1;              // enable phase shift for ePWM2
         EPwm2Regs.TBCTL.bit.PHSDIR = 1;              // count down after synchronization
         EPwm2Regs.TBPHS.bit.TBPHS  = 0;              //  phase always same as EPWM 1


     // ------------------------------------------------------------------------------------------
     // Interrupt Settings
     // ------------------------------------------------------------------------------------------
         asm(" EALLOW");                              // Enable EALLOW protected register access
         PieCtrlRegs.PIEIER2.bit.INTx1=1;             // Enable Trip interrupt from EPwm1 (Trip ISR)
         IER |= 0x0002;

         asm(" EDIS");                                // Disable EALLOW protected register access
     //---------------------------------------------------------------------
     //--- Enable the clocks to the ePWM module.
     //--- Note: this should be done after all ePWM modules are configured
     //--- to ensure synchronization between the ePWM modules.
     //---------------------------------------------------------------------
         asm(" EALLOW");                         // Enable EALLOW protected register access
         CpuSysRegs.PCLKCR0.bit.TBCLKSYNC = 1;   // TBCLK to ePWM modules enabled
         asm(" EDIS");                           // Disable EALLOW protected register access

    }

//
// End of File
//
