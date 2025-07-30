#include "F28x_Project.h"
#include "Traction_Converter_Master.h"
#include <math.h>

//Author: Dr.Aryadip Sen



//Variable related to testState
            Uint16 Pre_Charger_Contactor_Command = 0;
            Uint16 Main_Contactor_Command=0;
            Uint16 Flow_Pump_Control_Contactor_Command=0;
            Uint16 Line_Trip_Output_1_Command=0;
            Uint16 Line_Trip_Output_2_Command=0;
            Uint16 Contactor_Filter_On_OFF_Command=0;
            Uint16 Contactor_Filter_Adaption_Command=0;
            Uint16 Contactor_Discharge_Resistor_Command=0;


           // Uint16 Pre_Charge_Contactor_NOpen_Command=0;
            Uint16 Pre_Charge_Contactor_NOpen_test= 0;
            Uint16 Pre_Charge_Contactor_NClose_test=0;
            Uint16 Main_Contactor_1_NOpen_test=0;
            Uint16 Main_Contactor_1_NClose_test=0;
            Uint16 Main_Contactor_2_NOpen_test =0;
            Uint16 Main_Contactor_2_NClose_test=0;
            Uint16 System_ON_OFF_test=0;
            Uint16 System_Reset_Command_test=0;
            Uint16 Coolent_Level_Command_test=0;
            Uint16 Heat_Sink_Temprature_LSC1_LSC_2_test=0;
            Uint16 Pressure_DC_Link_Capacitor_1_2_3_test=0;
            Uint16 Pressure_DC_Link_Capacitor_4_5_6_test=0;
            Uint16 Pressure_DC_Link_Capacitor_7_8_9_test=0;
            Uint16 Line_Trip_Input_1_test =0;
            Uint16 Line_Trip_Input_2_test=0;
            Uint16 LCB_Fast_Open_1_test=0;
            Uint16 LCB_Fast_Open_2_test=0;
            Uint16 Contactor_Filter_ON_OFF_Feedback_test=0;
            Uint16 Contactor_Filter_Adaption_Feedback_test=0;
            Uint16 Contactor_Discharge_Resistor_Feedback_test=0;
            Uint16 Grid_Input_Current_Command_test=0;


 // Sampling Time for the Controller
            float32 Ts = 0.0005;         // 500 us = 2 Khz

 // Variables for Unipolar PWM Technique

            float32 mi = 0.0;
            float32 Finv= 0.0;
            int32 sampleInstant  =0.0;
            float32 ThetaA = 0.0;          // Phase a theta
            float32 ma_a = 0.0;
            float32 ma_b = 0.0;
            float32 ma_c = 0.0;
            float32 ma_d = 0.0;
            float32 ma_e = 0.0;
            Uint16 a = 0;
            Uint16 b = 0;
            Uint16 c = 0;
            Uint16 d = 0;
            Uint16 e = 0;

 // Variables for observing waveforms
            float32 waveform1[10000];
            float32 waveform2[10000];
 //  Variables related to OBSERVING WAVEFORMS IN DEBUG WINDOW
             int32 buffNum = 0;




// Variables for ADC Sesning
            Uint16 offsetSettingDone = 0;
            float32 Vdc_sense = 0;
            float32 Vdc_measADC = 0.0;

            float32 VdcCalFactor = 1;

            float32 Vg_sense =0;
            float32 Ig_sense =0;
            float32 OVgCalFactor = 1;
            float32 OIgCalFactor=1;
            float32 Vg_measADC = 0.0;
            float32 Vg_measADCSum = 0.0;
            float32 VgOffset = 0;
            float32 Vg_meas = 0;
            float Vg_meas_avg[12];
            float Vg_meas_mavg=0;
            float VgSum=0;
            float VgRms=0;
            float32 Ig_measADC=0;
            float32 IgOffset=0;
            float IgRms=0;
            float   IgSum=0;
            Uint16 avgi = 0;
            Uint16 buffNumData = 0;





            Uint32 offsetSettingCount= 0;
            int32 averagingWindowCounter = 0;
            int32 averagingWindow = 15;
            float32 averagingWindowFloat = 15;

            //DAC Configuration
            Uint16 DAC3, DAC1;
            Uint16 display = 0;



            //void configureDAC(Uint16 dac_num);
            void ConfigureDAC(void);

          //  volatile struct DAC_REGS* DAC_PTR[4] = {0x0,&DacaRegs,&DacbRegs,&DaccRegs};


            void main(void)
                        {
                //--- CPU Initialization
                            InitSysCtrl();
                            DINT;

                            InitGpio();
                            InitOutputGpios();
                           /* InitGPIO_setDirectionMode();
                            InitGPIO_getDirectionMode();
                            InitGPIO_setPadConfig();*/

                            InitPieCtrl();
                            InitPieVectTable();

           //----DAC Configuration
                           /* configureDAC(2);
                            configureDAC(1);*/
                            ConfigureDAC();

              //--- Peripheral Initialization
                            InitAdc();                   // Initialize the ADC-A (FILE: Adc.c)
                            InitEPwm();                  // Initialize the EPwm (FILE: EPwm.c)
                            //InitDacc();                 // Initialization of DAC file

                            // Map ISR
                            EALLOW;
                            PieVectTable.ADCA1_INT = &ADCA1_ISR;
                            EDIS;


                        //--- Clear IPC Flags
                           // IpcRegs.IPCCLR.all = 0xFFFFFFFF;

                            // Enable PIE interrupt and CPU interrupt
                           // PieCtrlRegs.PIEIER1.bit.INTx1 = 1;
                           // IER |= M_INT1;
                            IER |= 0x0001;

                            EINT;   // Enable global interrupts
                            ERTM;   // Enable real-time interrupts
                //--- Enable global interrupts
                            asm(" CLRC INTM, DBGM");            // Enable global interrupts and real-time debug

                            while(1)
                            {
                                AdcaRegs.ADCSOCFRC1.all = 0x1;   // Trigger SOC0 conversion
                               // DELAY_US(5000);                // 0.5 second delay
                            }
                        }
 /*           void configureDAC(Uint16 dac_num){
                EALLOW;
                DAC_PTR[dac_num]->DACCTL.bit.DACREFSEL = REFERENCE;
                DAC_PTR[dac_num]->DACCTL.bit.SYNCSEL   = 7;
                DAC_PTR[dac_num]->DACOUTEN.bit.DACOUTEN = 1;
                DAC_PTR[dac_num]->DACCTL.bit.LOADMODE = 1;
                DAC_PTR[dac_num]->DACVALS.all = 0;
                DELAY_US(10); // Delay for buffered DAC to power up
                EDIS;
            }

*/
            void ConfigureDAC(void)
                  {
                  EALLOW;
                  DacbRegs.DACCTL.bit.DACREFSEL = 1;
                  DacbRegs.DACCTL.bit.LOADMODE = 1;
                  DacbRegs.DACCTL.bit.SYNCSEL = 7;
                  DacbRegs.DACVALS.all =0x0800;
                  DacbRegs.DACOUTEN.bit.DACOUTEN = 1;
                  EDIS;

                  EALLOW;
                  DacaRegs.DACCTL.bit.DACREFSEL = 1;
                  DacaRegs.DACCTL.bit.LOADMODE = 1;
                  DacaRegs.DACCTL.bit.SYNCSEL = 7;
                  DacaRegs.DACVALS.all = 0x0800;
                  DacaRegs.DACOUTEN.bit.DACOUTEN = 1;
                  EDIS;
                  }
