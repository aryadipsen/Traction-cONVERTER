//###########################################################################
//
// FILE:    f2838x_gpio.c
//
// TITLE:    GPIO module support functions
//Author:     Dr. Aryadip Sen
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
//   Redistributions of source code must retain the above copyright 
//   notice, this list of conditions and the following disclaimer.
// 
//   Redistributions in binary form must reproduce the above copyright
//   notice, this list of conditions and the following disclaimer in the 
//   documentation and/or other materials provided with the   
//   distribution.
// 
//   Neither the name of Texas Instruments Incorporated nor the names of
//   its contributors may be used to endorse or promote products derived
//   from this software without specific prior written permission.
// 
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS 
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT 
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT 
// OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, 
// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT 
// LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT 
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE 
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
// $
//###########################################################################

//
// Included Files
//
#include "f2838x_device.h"
#include "f2838x_examples.h"
#include "Traction_Converter_Master.h"
#include  "gpio.h"

//
//Low-level functions for GPIO configuration (CPU1 only)
//

#ifdef CPU1
    //
    // InitGpio - Sets all pins to be muxed to GPIO in input mode.
    //            Also resets CPU control to CPU1 and disables open
    //            drain and polarity inversion and sets the qualification to
    //            synchronous. Also unlocks all GPIOs. Only one CPU should call
    //            this function.
    //
    void InitGpio()
    {
        volatile Uint32 *gpioBaseAddr;
        Uint16 regOffset;

        //
        //Disable pin locks
        //
        EALLOW;
        GpioCtrlRegs.GPALOCK.all = 0x00000000;
        GpioCtrlRegs.GPBLOCK.all = 0x00000000;
        GpioCtrlRegs.GPCLOCK.all = 0x00000000;
        GpioCtrlRegs.GPDLOCK.all = 0x00000000;
        GpioCtrlRegs.GPELOCK.all = 0x00000000;
        GpioCtrlRegs.GPFLOCK.all = 0x00000000;

        //
        // Fill all registers with zeros. Writing to each register separately
        // for six GPIO modules would make this function *very* long.
        // Fortunately, we'd be writing them all with zeros anyway, so this
        // saves a lot of space.
        //
        gpioBaseAddr = (Uint32 *)&GpioCtrlRegs;
        for (regOffset = 0; regOffset < sizeof(GpioCtrlRegs)/2; regOffset++)
        {
            //
            //Hack to avoid enabling pull-ups on all pins. GPyPUD is offset
            //0x0C in each register group of 0x40 words. Since this is a
            //32-bit pointer, the addresses must be divided by 2.
            //
            if (regOffset % (0x40/2) != (0x0C/2))
            {
                gpioBaseAddr[regOffset] = 0x00000000;
            }
        }

        gpioBaseAddr = (Uint32 *)&GpioDataRegs;
        for (regOffset = 0; regOffset < sizeof(GpioDataRegs)/2; regOffset++)
        {
            gpioBaseAddr[regOffset] = 0x00000000;
        }




        EDIS;
    }

    //
    // GPIO_SetupPinMux - Set the peripheral muxing for the specified pin. The
    //                    appropriate parameters can be found in the GPIO Muxed
    //                    Pins table(4.4) in the  datasheet. Use the GPIO index
    //                    row (0 to 15) to select a muxing option for the GPIO.
    //
    void GPIO_SetupPinMux(Uint16 gpioNumber, Uint16 cpu, Uint16 muxPosition)
    {
        volatile Uint32 *gpioBaseAddr;
        volatile Uint32 *mux, *gmux, *csel;
        Uint16 pin32, pin16, pin8;

        pin32 = gpioNumber % 32;
        pin16 = gpioNumber % 16;
        pin8 = gpioNumber % 8;
        gpioBaseAddr = (Uint32 *)&GpioCtrlRegs + (gpioNumber/32)*GPY_CTRL_OFFSET;

        //
        //Sanity check for valid cpu and peripheral values
        //
        if (cpu > GPIO_MUX_CPU2CLA || muxPosition > 0xF)
            return;

        //
        //Create pointers to the appropriate registers. This is a workaround
        //for the way GPIO registers are defined. The standard definition
        //in the header file makes it very easy to do named accesses of one
        //register or bit, but hard to do arbitrary numerical accesses. It's
        //easier to have an array of GPIO modules with identical registers,
        //including arrays for multi-register groups like GPyCSEL1-4. But
        //the header file doesn't define anything we can turn into an array,
        //so manual pointer arithmetic is used instead.
        //
        mux = gpioBaseAddr + GPYMUX + pin32/16;
        gmux = gpioBaseAddr + GPYGMUX + pin32/16;
        csel = gpioBaseAddr + GPYCSEL + pin32/8;

        //
        //Now for the actual function
        //
        EALLOW;

        //
        //To change the muxing, set the peripheral mux to 0/GPIO first to avoid
        //glitches, then change the group mux, then set the peripheral mux to
        //its target value. Finally, set the CPU select. This procedure is
        //described in the TRM. Unfortunately, since we don't know the pin in
        //advance we can't hardcode a bitfield reference, so there's some
        //tricky bit twiddling here.
        //
        *mux &= ~(0x3UL << (2*pin16));
        *gmux &= ~(0x3UL << (2*pin16));
        *gmux |= (Uint32)((muxPosition >> 2) & 0x3UL) << (2*pin16);
        *mux |= (Uint32)(muxPosition & 0x3UL) << (2*pin16);

        *csel &= ~(0x3L << (4*pin8));
        *csel |= (Uint32)(cpu & 0x3L) << (4*pin8);

        //
        //WARNING: This code does not touch the analog mode select registers,
        //which are needed to give the USB module control of its IOs.
        //
        EDIS;
    }

    //
    // GPIO_SetupPinOptions - Setup up the GPIO input/output options for the
    //                        specified pin.
    //
    //The flags are a 16-bit mask produced by ORing together options.
    //For input pins, the valid flags are:
    //GPIO_PULLUP    Enable pull-up
    //GPIO_INVERT    Enable input polarity inversion
    //GPIO_SYNC        Synchronize the input latch to PLLSYSCLK
    //               (default -- you don't need to specify this)
    //GPIO_QUAL3    Use 3-sample qualification
    //GPIO_QUAL6    Use 6-sample qualification
    //GPIO_ASYNC    Do not use synchronization or qualification
    //(Note: only one of SYNC, QUAL3, QUAL6, or ASYNC is allowed)
    //
    //For output pins, the valid flags are:
    //GPIO_OPENDRAIN    Output in open drain mode
    //GPIO_PULLUP        If open drain enabled, also enable the pull-up
    //and the input qualification flags (SYNC/QUAL3/QUAL6/SYNC) listed above.
    //
    //With no flags, the default input state is synchronous with no
    //pull-up or polarity inversion. The default output state is
    //the standard digital output.
    //
    void GPIO_SetupPinOptions(Uint16 gpioNumber, Uint16 output, Uint16 flags)
    {
        volatile Uint32 *gpioBaseAddr;
        volatile Uint32 *dir, *pud, *inv, *odr, *qsel;
        Uint32 pin32, pin16, pinMask, qual;

        pin32 = gpioNumber % 32;
        pin16 = gpioNumber % 16;
        pinMask = 1UL << pin32;
        gpioBaseAddr = (Uint32 *)&GpioCtrlRegs + (gpioNumber/32)*GPY_CTRL_OFFSET;

        //
        //Create pointers to the appropriate registers. This is a workaround
        //for the way GPIO registers are defined. The standard definition
        //in the header file makes it very easy to do named accesses of one
        //register or bit, but hard to do arbitrary numerical accesses. It's
        //easier to have an array of GPIO modules with identical registers,
        //including arrays for multi-register groups like GPyQSEL1-2. But
        //the header file doesn't define anything we can turn into an array,
        //so manual pointer arithmetic is used instead.
        //
        dir = gpioBaseAddr + GPYDIR;
        pud = gpioBaseAddr + GPYPUD;
        inv = gpioBaseAddr + GPYINV;
        odr = gpioBaseAddr + GPYODR;
        qsel = gpioBaseAddr + GPYQSEL + pin32/16;

        EALLOW;

        //
        //Set the data direction
        //
        *dir &= ~pinMask;
        if (output == 1)
        {
            //
            //Output, with optional open drain mode and pull-up
            //
            *dir |= pinMask;

            //
            //Enable open drain if necessary
            //
            if (flags & GPIO_OPENDRAIN)
            {
                *odr |= pinMask;
            }
            else
            {
                *odr &= ~pinMask;
            }

            //
            //Enable pull-up if necessary. Open drain mode must be active.
            //
            if (flags & (GPIO_OPENDRAIN | GPIO_PULLUP))
            {
                *pud &= ~pinMask;
            }
            else
            {
                *pud |= pinMask;
            }
        }
        else
        {
            //
            //Input, with optional pull-up, qualification, and polarity
            //inversion
            //
            *dir &= ~pinMask;

            //
            //Enable pull-up if necessary
            //
            if (flags & GPIO_PULLUP)
            {
                *pud &= ~pinMask;
            }
            else
            {
                *pud |= pinMask;
            }

            //
            //Invert polarity if necessary
            //
            if (flags & GPIO_INVERT)
            {
                *inv |= pinMask;
            }
            else
            {
                *inv &= ~pinMask;
            }
        }

        //
        //Extract the qualification parameter and load it into the register.
        //This is also needed for open drain outputs, so we might as well do it
        //all the time.
        //
        qual = (flags & GPIO_ASYNC) / GPIO_QUAL3;
        *qsel &= ~(0x3L << (2 * pin16));
        if (qual != 0x0)
        {
            *qsel |= qual << (2 * pin16);
        }

        EDIS;
    }

    //
    // GPIO_SetupLock - Enable or disable the GPIO register bit lock for the
    //                  specified pin.
    //                  The valid flags are:
    //                  GPIO_UNLOCK - Unlock the pin setup register bits for
    //                                the specified pin
    //                  GPIO_LOCK - Lock the pin setup register bits for the
    //                              specified pin
    //
    void GPIO_SetupLock(Uint16 gpioNumber, Uint16 flags)
    {
        volatile Uint32 *gpioBaseAddr;
        volatile Uint32 *lock;
        Uint32 pin32, pinMask;

        pin32 = gpioNumber % 32;
        pinMask = 1UL << pin32;
        gpioBaseAddr = (Uint32 *)&GpioCtrlRegs + (gpioNumber/32)*GPY_CTRL_OFFSET;

        //
        //Create pointers to the appropriate registers. This is a workaround
        //for the way GPIO registers are defined. The standard definition
        //in the header file makes it very easy to do named accesses of one
        //register or bit, but hard to do arbitrary numerical accesses. It's
        //easier to have an array of GPIO modules with identical registers,
        //including arrays for multi-register groups like GPyQSEL1-2. But
        //the header file doesn't define anything we can turn into an array,
        //so manual pointer arithmetic is used instead.
        //
        lock = gpioBaseAddr + GPYLOCK;

        EALLOW;
        if(flags)
        {
            //Lock the pin
            *lock |= pinMask;
        }
        else
        {
            //Unlock the pin
            *lock &= ~pinMask;
        }
        EDIS;
    }

    //
    //External interrupt setup
    //
    void GPIO_SetupXINT1Gpio(Uint16 gpioNumber)
    {
        EALLOW;
        InputXbarRegs.INPUT4SELECT = gpioNumber;      //Set XINT1 source to GPIO-pin
        EDIS;
    }
    void GPIO_SetupXINT2Gpio(Uint16 gpioNumber)
    {
        EALLOW;
        InputXbarRegs.INPUT5SELECT = gpioNumber;      //Set XINT2 source to GPIO-pin
        EDIS;
    }
    void GPIO_SetupXINT3Gpio(Uint16 gpioNumber)
    {
        EALLOW;
        InputXbarRegs.INPUT6SELECT = gpioNumber;      //Set XINT3 source to GPIO-pin
        EDIS;
    }
    void GPIO_SetupXINT4Gpio(Uint16 gpioNumber)
    {
        EALLOW;
        InputXbarRegs.INPUT13SELECT = gpioNumber;     //Set XINT4 source to GPIO-pin
        EDIS;
    }
    void GPIO_SetupXINT5Gpio(Uint16 gpioNumber)
    {
        EALLOW;
        InputXbarRegs.INPUT14SELECT = gpioNumber;     //Set XINT5 source to GPIO-pin
        EDIS;
    }

    //
    //GPIO_EnableUnbondedIOPullupsFor176Pin - Enable pullups for the unbonded
    //                                        GPIOs on the 176PTP package:
    //                                        GPIOs     Grp Bits
    //                                        95-132    C   31
    //                                                  D   31:0
    //                                                  E   4:0
    //                                        134-168   E   31:6
    //                                                  F   8:0
    //
    void GPIO_EnableUnbondedIOPullupsFor176Pin()
    {
        EALLOW;
        GpioCtrlRegs.GPCPUD.all = ~0x80000000;  //GPIO 95
        GpioCtrlRegs.GPDPUD.all = ~0xFFFFFFF7;  //GPIOs 96-127
        GpioCtrlRegs.GPEPUD.all = ~0xFFFFFFDF;  //GPIOs 128-159 except for 133
        GpioCtrlRegs.GPFPUD.all = ~0x000001FF;  //GPIOs 160-168
        EDIS;
    }

    //
    // GPIO_EnableUnbondedIOPullups - InitSysCtrl would call this function
    //                                this takes care of enabling IO pullups.
    //
    void GPIO_EnableUnbondedIOPullups()
    {
        //
        //bits 8-10 have pin count
        //
        unsigned char pin_count = (DevCfgRegs.PARTIDL.bit.PIN_COUNT) ;

        //
        //6 = 176 pin
        //7 = 337 pin
        //
        if (pin_count == 6)
        {
            GPIO_EnableUnbondedIOPullupsFor176Pin();
        }
        else
        {
            //do nothing - this is 337 pin package
        }
    }

#endif //CPU1

//
// GPIO_ReadPin - Read the GPyDAT register bit for the specified pin. Note that
//                this returns the actual state of the pin, not the state of
//                the output latch.
//
Uint16 GPIO_ReadPin(Uint16 gpioNumber)
{
    volatile Uint32 *gpioDataReg;
    Uint16 pinVal;

    gpioDataReg = (volatile Uint32 *)&GpioDataRegs + (gpioNumber/32)*GPY_DATA_OFFSET;
    pinVal = (gpioDataReg[GPYDAT] >> (gpioNumber % 32)) & 0x1;

    return pinVal;
}

//
// GPIO_WritePin - Set the GPyDAT register bit for the specified pin.
//
void GPIO_WritePin(Uint16 gpioNumber, Uint16 outVal)
{
    volatile Uint32 *gpioDataReg;
    Uint32 pinMask;

    gpioDataReg = (volatile Uint32 *)&GpioDataRegs + (gpioNumber/32)*GPY_DATA_OFFSET;
    pinMask = 1UL << (gpioNumber % 32);

    if (outVal == 0)
    {
        gpioDataReg[GPYCLEAR] = pinMask;
    }
    else
    {
        gpioDataReg[GPYSET] = pinMask;
    }


}

// GPIO_setDirectionMode
//
//*****************************************************************************
void
GPIO_setDirectionMode(uint32_t pin, GPIO_Direction pinIO)
{
    volatile uint32_t *gpioBaseAddr;
    uint32_t pinMask;

    //
    // Check the arguments.
    //
    ASSERT(GPIO_isPinValid(pin));

    gpioBaseAddr = (uint32_t *)GPIOCTRL_BASE +
                   ((pin / 32U) * GPIO_CTRL_REGS_STEP);
    pinMask = (uint32_t)1U << (pin % 32U);

    EALLOW;

    //
    // Set the data direction
    //
    if(pinIO == GPIO_DIR_MODE_OUT)
    {
        //
        // Output
        //
        gpioBaseAddr[GPIO_GPxDIR_INDEX] |= pinMask;
    }
    else
    {
        //
        // Input
        //
        gpioBaseAddr[GPIO_GPxDIR_INDEX] &= ~pinMask;
    }

    EDIS;
}

// GPIO_getDirectionMode
//
//*****************************************************************************
GPIO_Direction
GPIO_getDirectionMode(uint32_t pin)
{
    volatile uint32_t *gpioBaseAddr;

    //
    // Check the arguments.
    //
    ASSERT(GPIO_isPinValid(pin));

    gpioBaseAddr = (uint32_t *)GPIOCTRL_BASE +
                   ((pin / 32U) * GPIO_CTRL_REGS_STEP);

    return((GPIO_Direction)((uint32_t)((gpioBaseAddr[GPIO_GPxDIR_INDEX] >>
                             (pin % 32U)) & 1U)));

}


// GPIO_setPadConfig
//
//*****************************************************************************
void
GPIO_setPadConfig(uint32_t pin, uint32_t pinType)
{
    volatile uint32_t *gpioBaseAddr;
    uint32_t pinMask;

    //
    // Check the arguments.
    //
    ASSERT(GPIO_isPinValid(pin));

    gpioBaseAddr = (uint32_t *)GPIOCTRL_BASE +
                   ((pin / 32U) * GPIO_CTRL_REGS_STEP);
    pinMask = (uint32_t)1U << (pin % 32U);

    EALLOW;

    //
    // Enable open drain if necessary
    //
    if((pinType & GPIO_PIN_TYPE_OD) != 0U)
    {
        gpioBaseAddr[GPIO_GPxODR_INDEX] |= pinMask;
    }
    else
    {
        gpioBaseAddr[GPIO_GPxODR_INDEX] &= ~pinMask;
    }

    //
    // Enable pull-up if necessary
    //
    if((pinType & GPIO_PIN_TYPE_PULLUP) != 0U)
    {
        gpioBaseAddr[GPIO_GPxPUD_INDEX] &= ~pinMask;
    }
    else
    {
        gpioBaseAddr[GPIO_GPxPUD_INDEX] |= pinMask;
    }

    //
    // Invert polarity if necessary
    //
    if((pinType & GPIO_PIN_TYPE_INVERT) != 0U)
    {
        gpioBaseAddr[GPIO_GPxINV_INDEX] |= pinMask;
    }
    else
    {
        gpioBaseAddr[GPIO_GPxINV_INDEX] &= ~pinMask;
    }

    EDIS;
}

void InitOutputGpios(void)
{

                    asm(" EALLOW");

                    //--- Unlock the GPxLOCK register bits for all ports
                        GpioCtrlRegs.GPACR.all   = 0x00000000;
                        GpioCtrlRegs.GPBCR.all   = 0x00000000;
                        GpioCtrlRegs.GPCCR.all   = 0x00000000;
                        GpioCtrlRegs.GPDCR.all   = 0x00000000;
                        GpioCtrlRegs.GPECR.all   = 0x00000000;
                        GpioCtrlRegs.GPFCR.all   = 0x00000000;


                        //--- Disable the register locks for all ports
                        GpioCtrlRegs.GPALOCK.all = 0x00000000;
                        GpioCtrlRegs.GPBLOCK.all = 0x00000000;
                        GpioCtrlRegs.GPCLOCK.all = 0x00000000;
                        GpioCtrlRegs.GPDLOCK.all = 0x00000000;
                        GpioCtrlRegs.GPELOCK.all = 0x00000000;
                        GpioCtrlRegs.GPFLOCK.all = 0x00000000;
                        //--- Group A pins
                        GpioCtrlRegs.GPACTRL.all  = 0x00000000;     // QUALPRD = PLLSYSCLK for all group A GPIO
                        GpioCtrlRegs.GPAQSEL1.all = 0x00000000;     // Synchronous qualification for all group A GPIO 0-15
                        GpioCtrlRegs.GPAQSEL2.all = 0x00000000;     // Synchronous qualification for all group A GPIO 16-31
                        GpioCtrlRegs.GPADIR.all   = 0x00000000;     // All GPIO are inputs
                        GpioCtrlRegs.GPAPUD.all   = 0x00000000;     // All pullups enabled
                        GpioCtrlRegs.GPAINV.all   = 0x00000000;     // No inputs inverted
                        GpioCtrlRegs.GPAODR.all   = 0x00000000;     // All outputs normal mode (no open-drain outputs)
                        GpioCtrlRegs.GPACSEL1.all = 0x00000000;     // GPIO 0-7   \.
                        GpioCtrlRegs.GPACSEL2.all = 0x00000000;     // GPIO 8-15   |. GPIODAT/SET/CLEAR/TOGGLE reg. master:
                        GpioCtrlRegs.GPACSEL3.all = 0x00000000;     // GPIO 16-23  |. 0=CPU1, 1=CPU1.CLA1, 2=CPU2, 3=CPU2.CLA1
                        GpioCtrlRegs.GPACSEL4.all = 0x00000000;     // GPIO 24-31 /.

                                                //-----------------------------------------------------------------------------------------------------
                        GpioCtrlRegs.GPAGMUX1.bit.GPIO0 = 0;        // 0|0=GPIO  0|1=EPWM1A       0|2=rsvd         0|3=rsvd
                        GpioCtrlRegs.GPAMUX1.bit.GPIO0  = 1;        // 1|0=GPIO  1|1=rsvd         1|2=SDAA         1|3=rsvd
                                                               // 2|0=GPIO  2|1=rsvd         2|2=rsvd         2|3=rsvd
                        //-----------------------------------------------------------------------------------------------------
                        GpioCtrlRegs.GPAGMUX1.bit.GPIO1 = 0;        // 0|0=GPIO  0|1=EPWM1B       0|2=rsvd         0|3=MFSRB
                        GpioCtrlRegs.GPAMUX1.bit.GPIO1  = 1;        // 1|0=GPIO  1|1=rsvd         1|2=SCLA         1|3=rsvd
                        //-----------------------------------------------------------------------------------------------------
                        GpioCtrlRegs.GPAGMUX1.bit.GPIO2 = 0;        // 0|0=GPIO  0|1=EPWM2A       0|2=rsvd         0|3=rsvd
                        GpioCtrlRegs.GPAMUX1.bit.GPIO2  = 1;        // 1|0=GPIO  1|1=OUTPUTXBAR1  1|2=SDAB         1|3=rsvd
                                                                   // 2|0=GPIO  2|1=rsvd         2|2=rsvd         2|3=rsvd
                                                                   // 3|0=GPIO  3|1=rsvd         3|2=rsvd         3|3=rsvd
                        //-----------------------------------------------------------------------------------------------------
                        GpioCtrlRegs.GPAGMUX1.bit.GPIO3 = 0;        // 0|0=GPIO  0|1=EPWM2B       0|2=OUTPUTXBAR2  0|3=MCLKRB
                        GpioCtrlRegs.GPAMUX1.bit.GPIO3  = 1;        // 1|0=GPIO  1|1=OUTPUTXBAR2  1|2=SCLB         1|3=rsvd
                                                                   // 2|0=GPIO  2|1=rsvd         2|2=rsvd         2|3=rsvd
                                                                   // 3|0=GPIO  3|1=rsvd         3|2=rsvd         3|3=rsvd
                        //-----------------------------------------------------------------------------------------------------
                        GpioCtrlRegs.GPAGMUX1.bit.GPIO4 = 0;        // 0|0=GPIO  0|1=EPWM3A       0|2=rsvd         0|3=rsvd
                        GpioCtrlRegs.GPAMUX1.bit.GPIO4  = 1;        // 1|0=GPIO  1|1=OUTPUTXBAR3  1|2=CANTXA       1|3=rsvd
                                                                   // 2|0=GPIO  2|1=rsvd         2|2=rsvd         2|3=rsvd
                                                                   // 3|0=GPIO  3|1=rsvd         3|2=rsvd         3|3=rsvd
                        //-----------------------------------------------------------------------------------------------------
                        GpioCtrlRegs.GPAGMUX1.bit.GPIO5 = 0;        // 0|0=GPIO  0|1=EPWM3B       0|2=MFSRA        0|3=OUTPUTXBAR3
                        GpioCtrlRegs.GPAMUX1.bit.GPIO5  = 1;        // 1|0=GPIO  1|1=rsvd         1|2=CANRXA       1|3=rsvd
                                                                   // 2|0=GPIO  2|1=rsvd         2|2=rsvd         2|3=rsvd
                                                                   // 3|0=GPIO  3|1=rsvd         3|2=rsvd         3|3=rsvd
                        //-----------------------------------------------------------------------------------------------------
                        GpioCtrlRegs.GPAGMUX1.bit.GPIO6 = 0;        // 0|0=GPIO  0|1=EPWM4A       0|2=OUTPUTXBAR4  0|3=EPWMSYNCO
                        GpioCtrlRegs.GPAMUX1.bit.GPIO6  = 1;        // 1|0=GPIO  1|1=EQEP3A       1|2=CANTXB       1|3=rsvd
                                                                   // 2|0=GPIO  2|1=rsvd         2|2=rsvd         2|3=rsvd
                                                                   // 3|0=GPIO  3|1=rsvd         3|2=rsvd         3|3=rsvd
                        //-----------------------------------------------------------------------------------------------------
                        GpioCtrlRegs.GPAGMUX1.bit.GPIO7 = 0;        // 0|0=GPIO  0|1=EPWM4B       0|2=MCLKRA       0|3=OUTPUTXBAR5
                        GpioCtrlRegs.GPAMUX1.bit.GPIO7  = 1;        // 1|0=GPIO  1|1=EQEP3B       1|2=CANRXB       1|3=rsvd
                                                                   // 2|0=GPIO  2|1=rsvd         2|2=rsvd         2|3=rsvd
                                                                   // 3|0=GPIO  3|1=rsvd         3|2=rsvd         3|3=rsvd
                        //-----------------------------------------------------------------------------------------------------
                        GpioCtrlRegs.GPAGMUX1.bit.GPIO8 = 0;        // 0|0=GPIO  0|1=EPWM5A       0|2=CANTXB       0|3=ADCSOCAO
                        GpioCtrlRegs.GPAMUX1.bit.GPIO8  = 1;        // 1|0=GPIO  1|1=EQEP3S       1|2=SCITXDA      1|3=rsvd
                                                                   // 2|0=GPIO  2|1=rsvd         2|2=rsvd         2|3=rsvd
                                                                   // 3|0=GPIO  3|1=rsvd         3|2=rsvd         3|3=rsvd
                        //-----------------------------------------------------------------------------------------------------
                        GpioCtrlRegs.GPAGMUX1.bit.GPIO9 = 0;        // 0|0=GPIO  0|1=EPWM5B       0|2=SCITXDB      0|3=OUTPUTXBAR6
                        GpioCtrlRegs.GPAMUX1.bit.GPIO9  = 1;        // 1|0=GPIO  1|1=EQEP3I       1|2=SCIRXDA      1|3=rsvd
                                                                   // 2|0=GPIO  2|1=rsvd         2|2=rsvd         2|3=rsvd
                                                                   // 3|0=GPIO  3|1=rsvd         3|2=rsvd         3|3=rsvd
                        //-----------------------------------------------------------------------------------------------------
                        GpioCtrlRegs.GPAGMUX1.bit.GPIO10 = 0;       // 0|0=GPIO  0|1=EPWM6A       0|2=CANRXB       0|3=ADCSOCBO
                        GpioCtrlRegs.GPAMUX1.bit.GPIO10  = 1;       // 1|0=GPIO  1|1=EQEP1A       1|2=SCITXDB      1|3=rsvd
                                                                   // 2|0=GPIO  2|1=rsvd         2|2=rsvd         2|3=rsvd
                                                                   // 3|0=GPIO  3|1=rsvd         3|2=rsvd         3|3=UPP-WAIT
                        //-----------------------------------------------------------------------------------------------------
                        GpioCtrlRegs.GPAGMUX1.bit.GPIO11 = 0;       // 0|0=GPIO  0|1=EPWM6B       0|2=SCIRXDB      0|3=OUTPUTXBAR7
                        GpioCtrlRegs.GPAMUX1.bit.GPIO11  = 1;       // 1|0=GPIO  1|1=EQEP1B       1|2=SCIRXDB      1|3=rsvd
                                                                   // 2|0=GPIO  2|1=rsvd         2|2=rsvd         2|3=rsvd
                                                                   // 3|0=GPIO  3|1=rsvd         3|2=rsvd         3|3=UPP-STRT
                        //-----------------------------------------------------------------------------------------------------
                        GpioCtrlRegs.GPAGMUX1.bit.GPIO12 = 0;       // 0|0=GPIO  0|1=EPWM7A       0|2=CANTXB       0|3=MDXB
                        GpioCtrlRegs.GPAMUX1.bit.GPIO12  = 1;       // 1|0=GPIO  1|1=EQEP1S       1|2=SCITXDC      1|3=rsvd
                                                                   // 2|0=GPIO  2|1=rsvd         2|2=rsvd         2|3=rsvd
                                                                   // 3|0=GPIO  3|1=rsvd         3|2=rsvd         3|3=UPP-ENA
                        //-----------------------------------------------------------------------------------------------------
                        GpioCtrlRegs.GPAGMUX1.bit.GPIO13 = 0;       // 0|0=GPIO  0|1=EPWM7B       0|2=CANRXB       0|3=MDRB
                        GpioCtrlRegs.GPAMUX1.bit.GPIO13  = 1;       // 1|0=GPIO  1|1=EQEP1I       1|2=SCIRXDC      1|3=rsvd
                                                                   // 2|0=GPIO  2|1=rsvd         2|2=rsvd         2|3=rsvd
                                                                   // 3|0=GPIO  3|1=rsvd         3|2=rsvd         3|3=UPP-D7
                        //-----------------------------------------------------------------------------------------------------
                        GpioCtrlRegs.GPAGMUX1.bit.GPIO14 = 0;       // 0|0=GPIO  0|1=EPWM8A       0|2=SCITXDB      0|3=MCLKXB
                        GpioCtrlRegs.GPAMUX1.bit.GPIO14  = 1;       // 1|0=GPIO  1|1=rsvd         1|2=OUTPUTXBAR3  1|3=rsvd
                                                                   // 2|0=GPIO  2|1=rsvd         2|2=rsvd         2|3=rsvd
                                                                   // 3|0=GPIO  3|1=rsvd         3|2=rsvd         3|3=UPP-D6
                        //-----------------------------------------------------------------------------------------------------
                        GpioCtrlRegs.GPAGMUX1.bit.GPIO15 = 0;       // 0|0=GPIO  0|1=EPWM8B       0|2=SCIRXDB      0|3=MFSXB
                        GpioCtrlRegs.GPAMUX1.bit.GPIO15  = 1;       // 1|0=GPIO  1|1=rsvd         1|2=OUTPUTXBAR4  1|3=rsvd
                                                                   // 2|0=GPIO  2|1=rsvd         2|2=rsvd         2|3=rsvd
                                                                   // 3|0=GPIO  3|1=rsvd         3|2=rsvd         3|3=UPP-D5                                                 // 2|0=GPIO  2|1=rsvd         2|2=rsvd         2|3=rsvd
                                                                   // 3|0=GPIO  3|1=rsvd         3|2=rsvd         3|3=rsvd                                                // 3|0=GPIO  3|1=rsvd         3|2=rsvd         3|3=rsvd
                        //-----------------------------------------------------------------------------------------------------
                        GpioCtrlRegs.GPAGMUX2.bit.GPIO16 = 1;       // 0|0=GPIO  0|1=SPISIMOA     0|2=CANTXB       0|3=OUTPUTXBAR7
                        GpioCtrlRegs.GPAMUX2.bit.GPIO16  = 1;       // 1|0=GPIO  1|1=EPWM9A       1|2=rsvd         1|3=SD1_D1
                                                                  // 2|0=GPIO  2|1=rsvd         2|2=rsvd         2|3=rsvd
                                                                  // 3|0=GPIO  3|1=rsvd         3|2=rsvd         3|3=UPP-D4
                        //-----------------------------------------------------------------------------------------------------
                        GpioCtrlRegs.GPAGMUX2.bit.GPIO17 = 1;       // 0|0=GPIO  0|1=SPISOMIA     0|2=CANRXB       0|3=OUTPUTXBAR8
                        GpioCtrlRegs.GPAMUX2.bit.GPIO17  = 1;       // 1|0=GPIO  1|1=EPWM9B       1|2=rsvd         1|3=SD1_C1
                                                                  // 2|0=GPIO  2|1=rsvd         2|2=rsvd         2|3=rsvd
                        //-----------------------------------------------------------------------------------------------------
                        //-----------------------------------------------------------------------------------------------------
                       //-----------------------------------------------------------------------------------------------------// 3|0=GPIO  3|1=rsvd         3|2=rsvd         3|3=UPP-D3
                        //--- Group B pins
                        GpioCtrlRegs.GPBCTRL.all  = 0x00000000;     // QUALPRD = PLLSYSCLK for all group B GPIO
                        GpioCtrlRegs.GPBQSEL1.all = 0x00000000;     // Synchronous qualification for all group B GPIO 32-47
                        GpioCtrlRegs.GPBQSEL2.all = 0x00000000;     // Synchronous qualification for all group B GPIO 48-63
                        GpioCtrlRegs.GPBDIR.all   = 0x00000000;     // All group B GPIO are inputs
                        GpioCtrlRegs.GPBPUD.all   = 0x00000000;     // All group B pullups enabled
                        GpioCtrlRegs.GPBINV.all   = 0x00000000;     // No inputs inverted
                        GpioCtrlRegs.GPBODR.all   = 0x00000000;     // All outputs normal mode (no open-drain outputs)
                        GpioCtrlRegs.GPBCSEL1.all = 0x00000000;     // GPIO 32-39 \.
                        GpioCtrlRegs.GPBCSEL2.all = 0x00000000;     // GPIO 40-47  |. GPIODAT/SET/CLEAR/TOGGLE reg. master:
                        GpioCtrlRegs.GPBCSEL3.all = 0x00000000;     // GPIO 48-55  |. 0=CPU1, 1=CPU1.CLA1, 2=CPU2, 3=CPU2.CLA1
                        GpioCtrlRegs.GPBCSEL4.all = 0x00000000;     // GPIO 56-63 /.



                        //-----------------------------------------------------------------------------------------------------
                       //-----------------------------------------------------------------------------------------------------

                        //--- Group C pins
                        GpioCtrlRegs.GPCCTRL.all  = 0x00000000;     // QUALPRD = PLLSYSCLK for all group pinsC GPIO
                        GpioCtrlRegs.GPCQSEL1.all = 0x00000000;     // Synchronous qualification for all group C GPIO 64-79
                        GpioCtrlRegs.GPCQSEL2.all = 0x00000000;     // Synchronous qualification for all group C GPIO 80-95
                        GpioCtrlRegs.GPCDIR.all   = 0x00000000;     // All GPIO are inputs
                        GpioCtrlRegs.GPCPUD.all   = 0x00000000;     // All pullups enabled
                        GpioCtrlRegs.GPCINV.all   = 0x00000000;     // No inputs inverted
                        GpioCtrlRegs.GPCODR.all   = 0x00000000;     // All outputs normal mode (no open-drain outputs)
                        GpioCtrlRegs.GPCCSEL1.all = 0x00000000;     // GPIO 64-71 \.
                        GpioCtrlRegs.GPCCSEL2.all = 0x00000000;     // GPIO 72-79  |. GPIODAT/SET/CLEAR/TOGGLE reg. master:
                        GpioCtrlRegs.GPCCSEL3.all = 0x00000000;     // GPIO 80-87  |. 0=CPU1, 1=CPU1.CLA1, 2=CPU2, 3=CPU2.CLA1
                        GpioCtrlRegs.GPCCSEL4.all = 0x00000000;     // GPIO 88-95 /.

                       //-----------------------------------------------------------------------------------------------------

                        //--- Group D pins
                        GpioCtrlRegs.GPDCTRL.all  = 0x00000000;     // QUALPRD = PLLSYSCLK for all group D GPIO
                        GpioCtrlRegs.GPDQSEL1.all = 0x00000000;     // Synchronous qualification for all group D GPIO 96-111
                        GpioCtrlRegs.GPDQSEL2.all = 0x00000000;     // Synchronous qualification for all group D GPIO 112-127
                        GpioCtrlRegs.GPDDIR.all   = 0x00000000;     // All GPIO are inputs
                        GpioCtrlRegs.GPDPUD.all   = 0x00000000;     // All pullups enabled
                        GpioCtrlRegs.GPDINV.all   = 0x00000000;     // No inputs inverted
                        GpioCtrlRegs.GPDODR.all   = 0x00000000;     // All outputs normal mode (no open-drain outputs)
                        GpioCtrlRegs.GPDCSEL1.all = 0x00000000;     // GPIO 96-103  \.
                        GpioCtrlRegs.GPDCSEL2.all = 0x00000000;     // GPIO 104-111  |. GPIODAT/SET/CLEAR/TOGGLE reg. master:
                        GpioCtrlRegs.GPDCSEL3.all = 0x00000000;     // GPIO 112-119  |. 0=CPU1, 1=CPU1.CLA1, 2=CPU2, 3=CPU2.CLA1
                        GpioCtrlRegs.GPDCSEL4.all = 0x00000000;     // GPIO 120-127 /.

                        //-----------------------------------------------------------------------------------------------------
                        //-----------------------------------------------------------------------------------------------------

                        //--- Group E pins
                        GpioCtrlRegs.GPECTRL.all  = 0x00000000;     // QUALPRD = PLLSYSCLK for all group E GPIO
                        GpioCtrlRegs.GPEQSEL1.all = 0x00000000;     // Synchronous qualification for all group E GPIO 128-143
                        GpioCtrlRegs.GPEQSEL2.all = 0x00000000;     // Synchronous qualification for all group E GPIO 144-159
                        GpioCtrlRegs.GPEDIR.all   = 0x00000000;     // All GPIO are inputs
                        GpioCtrlRegs.GPEPUD.all   = 0x00000000;     // All pullups enabled
                        GpioCtrlRegs.GPEINV.all   = 0x00000000;     // No inputs inverted
                        GpioCtrlRegs.GPEODR.all   = 0x00000000;     // All outputs normal mode (no open-drain outputs)
                        GpioCtrlRegs.GPECSEL1.all = 0x00000000;     // GPIO 128-135 \.
                        GpioCtrlRegs.GPECSEL2.all = 0x00000000;     // GPIO 136-143  |. GPIODAT/SET/CLEAR/TOGGLE reg. master:
                        GpioCtrlRegs.GPECSEL3.all = 0x00000000;     // GPIO 144-151  |. 0=CPU1, 1=CPU1.CLA1, 2=CPU2, 3=CPU2.CLA1
                        GpioCtrlRegs.GPECSEL4.all = 0x00000000;     // GPIO 152-159 /.

                        //-----------------------------------------------------------------------------------------------------
                      //-----------------------------------------------------------------------------------------------------

                        //--- Group F pins
                        GpioCtrlRegs.GPFCTRL.all  = 0x00000000;     // QUALPRD = PLLSYSCLK for all group F GPIO
                        GpioCtrlRegs.GPFQSEL1.all = 0x00000000;     // Synchronous qualification for all group F GPIO 160-168
                        GpioCtrlRegs.GPFDIR.all   = 0x00000000;     // All GPIO are inputs
                        GpioCtrlRegs.GPFPUD.all   = 0x00000000;     // All pullups enabled
                        GpioCtrlRegs.GPFINV.all   = 0x00000000;     // No inputs inverted
                        GpioCtrlRegs.GPFODR.all   = 0x00000000;     // All outputs normal mode (no open-drain outputs)
                        GpioCtrlRegs.GPFCSEL1.all = 0x00000000;     // GPIO 160-167 \. GPIODAT/SET/CLEAR/TOGGLE reg. master:
                        GpioCtrlRegs.GPFCSEL2.all = 0x00000000;     // GPIO 168     /. 0=CPU1, 1=CPU1.CLA1, 2=CPU2, 3=CPU2.CLA1

                        //-----------------------------------------------------------------------------------------------------
                      //-----------------------------------------------------------------------------------------------------

                        //--- Select pin configurations

                        // STEP-1: DIRECTION TO GPIO PINS USED BY CPU1
                        //1A: AS INPUTS
                        GpioCtrlRegs.GPDDIR.bit.GPIO96 =  0; // Precharger Contactor Normaly Open
                        GpioCtrlRegs.GPDDIR.bit.GPIO99 =  0; // Precharger Contactor Normaly Close
                        GpioCtrlRegs.GPDDIR.bit.GPIO97 =  0; //Main Contactor 1 Normaly Open
                        GpioCtrlRegs.GPDDIR.bit.GPIO98 =  0; //Main Contactor 2 Normaly Open
                        GpioCtrlRegs.GPDDIR.bit.GPIO100 = 0; //Main Contactor 1 Normaly Close
                        GpioCtrlRegs.GPDDIR.bit.GPIO101 = 0; //Main Contactor 2 Normaly Close
                        GpioCtrlRegs.GPDDIR.bit.GPIO102 = 0; //System ON/OFF
                        GpioCtrlRegs.GPDDIR.bit.GPIO103 = 0; //System Reset
                        GpioCtrlRegs.GPDDIR.bit.GPIO104 = 0; //Collant level
                        GpioCtrlRegs.GPEDIR.bit.GPIO143 = 0; //Heat Sink Temprature of LSC1 & LSC 2
                        GpioCtrlRegs.GPEDIR.bit.GPIO136 = 0; //Pressure of DC Link Capacitor 1, 2 & 3
                        GpioCtrlRegs.GPEDIR.bit.GPIO137 = 0; //Pressure of DC Link Capacitor 4, 5 & 6
                        GpioCtrlRegs.GPEDIR.bit.GPIO138 = 0; //Pressure of DC Link Capacitor 7, 8 & 9
                        GpioCtrlRegs.GPFDIR.bit.GPIO165 = 0; //Line Trip Input 1
                        GpioCtrlRegs.GPFDIR.bit.GPIO167 = 0; //Line Trip Input 2
                        GpioCtrlRegs.GPEDIR.bit.GPIO146 = 0; //LCB Fast Open 1
                        GpioCtrlRegs.GPEDIR.bit.GPIO147 = 0; //LCB Fast Open 2
                        GpioCtrlRegs.GPCDIR.bit.GPIO76 =  0; // Contactor Filter ON/OFF Feedback
                        GpioCtrlRegs.GPEDIR.bit.GPIO141 = 0; //Contactor Filter Adaption Feedback
                        GpioCtrlRegs.GPEDIR.bit.GPIO142 = 0; //Contactor Discharge Resistor Feedback
                        GpioCtrlRegs.GPEDIR.bit.GPIO148 = 0; //Grid Input Current




                        //1B: AS OUTPUTS
                        GpioCtrlRegs.GPCDIR.bit.GPIO94 =  1; //  Pre-Charger Contactor Command
                        GpioCtrlRegs.GPCDIR.bit.GPIO95 =  1; //  Main Contactor Command
                        GpioCtrlRegs.GPEDIR.bit.GPIO133 = 1; //  Flow Pump Control Contactor Command
                        GpioCtrlRegs.GPFDIR.bit.GPIO166 = 1; //  Line Trip Output 1
                        GpioCtrlRegs.GPFDIR.bit.GPIO168 = 1; //  Line Trip Output 2
                        GpioCtrlRegs.GPCDIR.bit.GPIO74 =  1; //  Contactor Filter ON/OFF Command
                        GpioCtrlRegs.GPEDIR.bit.GPIO139 = 1; //  Contactor Filter Adaption Command
                        GpioCtrlRegs.GPEDIR.bit.GPIO140 = 1; //  Contactor Discharge Resistor Command
                        GpioCtrlRegs.GPEDIR.bit.GPIO134 = 1; //Any
                        GpioCtrlRegs.GPDDIR.bit.GPIO121 = 1; //Any
                        GpioCtrlRegs.GPBDIR.bit.GPIO36 =  1; //Any
                        GpioCtrlRegs.GPBDIR.bit.GPIO33 =  1; //Any



                        //DSP Control card rack address selection identification INPUT

                        GpioCtrlRegs.GPCDIR.bit.GPIO70 =  0;//CC1-SEL1-Control Card Rack Address Identification Pin 1
                        GpioCtrlRegs.GPCDIR.bit.GPIO71 =  0;//CC2-SEL2-Control Card Rack Address Identification Pin 2
                        GpioCtrlRegs.GPBDIR.bit.GPIO32 =  0;//CC3-SEL3-Control Card Rack Address Identification Pin 3

                     //  DSP Control card Redundancy OUTPUT
                        //GpioCtrlRegs.GPCDIR.bit.GPIO73   =1;//   //SW1-CC [A16] M1(MCU selection signal)

                        //AS PWM CONTROL SIGNAL OUTPUT
                        GpioCtrlRegs.GPDDIR.bit.GPIO127 = 1;// L1-RUN Signal
                        GpioCtrlRegs.GPADIR.bit.GPIO27 = 1;// L2-RUN Signal
                        GpioCtrlRegs.GPADIR.bit.GPIO26 = 1;// Chopper-RUN Signal

                          // PWM CONTROL FAULT CLEAR SIGNAL INPUT
                         GpioCtrlRegs.GPEDIR.bit.GPIO149 = 0;//Line Side 1 Leg 1 Top GDU Fault
                         GpioCtrlRegs.GPEDIR.bit.GPIO150 = 0;//Line Side 1 Leg 1 Bottom GDU Fault
                         GpioCtrlRegs.GPEDIR.bit.GPIO151 = 0;//Line Side 1 Leg 2 Top GDU Fault
                         GpioCtrlRegs.GPEDIR.bit.GPIO152 = 0;//Line Side 1 Leg 2 Bottom GDU Fault
                         GpioCtrlRegs.GPEDIR.bit.GPIO153 = 0;//Line Side 2 Leg 1 Top GDU Fault
                         GpioCtrlRegs.GPEDIR.bit.GPIO154 = 0;//Line Side 2 Leg 1 Bottom GDU Fault
                         GpioCtrlRegs.GPEDIR.bit.GPIO155 = 0;//Line Side 2 Leg 2 Top GDU Fault
                         GpioCtrlRegs.GPEDIR.bit.GPIO156 = 0;//Line Side 2 Leg 2 Bottom GDU Fault
                         GpioCtrlRegs.GPEDIR.bit.GPIO157 = 0;//Chopper Top GDU Fault
                         GpioCtrlRegs.GPEDIR.bit.GPIO158 = 0;// Chopper Bottom GDU Fault


                         //As PWM FAULT CLEAR SIGNAL OUTPUT
                         GpioCtrlRegs.GPEDIR.bit.GPIO128 = 0;//Line side converter fault clear


                        //DAC-Configuration


                         CpuSysRegs.PCLKCR16.bit.DAC_A = 1;   // Power up DAC A (channel A)
                         CpuSysRegs.PCLKCR16.bit.DAC_B = 1;   // Power up DAC B (channel B)
                         CpuSysRegs.PCLKCR16.bit.DAC_C = 1;   // Power up DAC c (channel c)


                      /*   DacaRegs.DACCTL.bit.DACREFSEL = 1;    // 0 = VDAC, 1 = VREFHI
                       //  DacaRegs.DACCTL.bit.MODE       = 0;    // Buffered DAC
                         DacaRegs.DACCTL.bit.LOADMODE   = 4;    // EPWM SYNC
                         DacaRegs.DACOUTEN.bit.DACOUTEN = 1;    // Enable DAC output
                        // (Optional) Insert delay here
                         DacaRegs.DACVALA.bit.DACVALA = 0x800;      // Set 12-bit DAC shadow value
*/



                                              //--- Finish up



                                                      asm(" EDIS");
}
//
// End of file
//
