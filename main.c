/******************************************************************************/
/* Files to Include                                                           */
/******************************************************************************/

#if defined(__XC)
    #include <xc.h>         /* XC8 General Include File */
#elif defined(HI_TECH_C)
    #include <htc.h>        /* HiTech General Include File */
#endif

#include <stdint.h>        /* For uint8_t definition */
#include <stdbool.h>       /* For true/false definition */

#include "system.h"        /* System funct/params, like osc/peripheral config */
#include "user.h"          /* User funct/params, such as InitApp */

/******************************************************************************/
/* User Global Variable Declaration                                           */
/******************************************************************************/
volatile unsigned char GLOBAL_sub_patterns_index = 0;         //used to communicate the selected sub pattern
volatile unsigned char GLOBAL_sub_patterns_index_copy = 0;
volatile unsigned char GLOBAL_sub_patterns_column_index = 0;  //used to move inside the selected sub pattern
volatile unsigned char GLOBAL_combo_patterns_index = 0;       //used to communicate the selected combo pattern
volatile unsigned char GLOBAL_combo_patterns_index_copy = 0;
volatile unsigned char GLOBAL_combo_patterns_column_index = 0;//used to move inside the selected combo pattern
volatile unsigned char GLOBAL_sub_patterns_timer=0;       //used to update the timer counter
volatile unsigned char GLOBAL_combo_patterns_counter=0;
volatile unsigned char GLOBAL_Selected_Mode_Number = 0;
volatile unsigned char GLOBAL_Selected_Mode_Type = 0;
volatile unsigned char GLOBAL_Selected_Mode_Type_copy = 0;
volatile unsigned char GLOBAL_Dummy_Counter = 0;
volatile unsigned char GLOBAL_Dummy_Counter2 = 0;
volatile unsigned char GLOBAL_MODE1_counter  = 0 ;
volatile unsigned char GLOBAL_SYNC_Line_counter  = 0;
volatile unsigned char GLOBAL_MODE2_counter  = 0;
volatile unsigned char GLOBAL_MODE1_LOW_counter  = 0;
volatile unsigned char GLOBAL_SYNC_Line_LOW_counter  = 0;
volatile unsigned char GLOBAL_MODE2_LOW_counter  = 0;
volatile unsigned char GLOBAL_Mode_copy[MAX_MODES] = 0;
volatile unsigned char GLOBAL_SYNC_PULSE_Counter = 0;
volatile unsigned char GLOBAL_CHANNELS_EN =0;
volatile unsigned char GLOBAL_CHANNELS_EN_copy =0;

volatile bool bGLOBAL_DISABLE_SYNC_Line_PRESSED = false;
volatile bool bGLOBAL_CHANGING_PATTERN = false;
volatile bool bGLOBAL_CHANGING_PATTERN_Enforce = false;
volatile bool bGLOBAL_SYNC_SENT = false;
volatile bool bGLOBAL_END_OF_CYCLE_COND1 = false;
volatile bool bGLOBAL_END_OF_CYCLE_COND2 = false;
volatile bool bGLOBAL_IS_PROGRAMMING = false;
volatile bool bGLOBAL_InPhase;
volatile bool bGLOBAL_InPhase_copy[MAX_MODES];
volatile bool bGLOBAL_ENABLE_LEDS = false;
volatile bool bGLOBAL_MODE1_PRESSED = false;
volatile bool bGLOBAL_MODE2_PRESSED = false;
volatile bool bGLOBAL_SYNC_Line_PRESSED = false;
volatile bool bGLOBAL_OUTPUT_BUFFER_CHANGED = false;
volatile bool bGLOBAL_STEADY_ON = false;

volatile unsigned char OUTPUT_BUFFER = 0; //OUTPUT_BUFF_type
volatile unsigned char OUTPUT_BUFFER_COPY = 0;

const unsigned char ROM_Sub_Patterns [MAX_Sub_Patterns][MAX_Sub_Patterns_Columns] = {
// ALL Channels disabled
    {{OFFF},                                                            //0
    {OFFF},
    {OFFF},
    {OFFF},
    {OFFF},
    {OFFF},
    {OFFF}},
// End of ALL Channels disabled

     {{BOTH},                                                               //1
     {BOTH},
     {OFF},   //Had to change this frame from BOTH so that there would be enough off time 300ms to get 120 FPM. KPH 01/25/2019
     {BOTH},
     {BOTH},
     {BOTH},
     {BOTH}},

     {{OFFF},                                                                //2
     {OFFF},
     {OFFF},
     {OFFF},
     {OFFF},
     {OFFF},
     {OFFF}},

     {{BOTH},                                                               //3
     {BOTH},
     {OFF},  //Had to change this frame from BOTH so that there would be enough off time 480ms to get 75 FPM. KPH 01/25/2019
     {OFF},   //Had to change this to split up frame 2 and 3 from 18 into 2 for timing of sync being pulled low.
     {BOTH},
     {BOTH},
     {BOTH}},
// Double
     {{BOTH},                                                               //4
     {OFFF},
     {BOTH},
     {OFFF},
     {BOTH},
     {OFFF},
     {BOTH}},
// tripple
     {{BOTH},                                                               //5
     {OFFF},
     {BOTH},
     {OFFF},
     {BOTH},
     {OFFF},
     {BOTH}},

 // Double fast
     {{BOTH},                                                               //6
     {OFFF},
     {BOTH},
     {OFFF},
     {OFF},
     {OFFF},
     {BOTH}},

  // tripple fast
     {{BOTH},                                                               //7
     {OFFF},
     {BOTH},
     {OFFF},
     {BOTH},
     {OFFF},
     {BOTH}},
    
     {{BOTH},                                                               //8
     {BOTH},
     {BOTH},
     {BOTH},
     {BOTH},
     {BOTH},
     {BOTH}},

    ////////////////////////////////////////////////////////////////
    
     {{OFFF},                                                               //9
     {OFFF},
     {OFFF},
     {OFFF},
     {OFFF},
     {OFFF},
     {OFFF}},
    
     {{BOTH},                                                               //10
     {BOTH},
     {BOTH},
     {BOTH},
     {BOTH},
     {BOTH},
     {BOTH}},
    
     {{BOTH},                                                               //11
     {OFFF},
     {BOTH},
     {OFFF},
     {BOTH},
     {OFFF},
     {BOTH}},
    
     {{OFFF},                                                               //12
     {OFFF},
     {OFFF},
     {OFFF},
     {OFFF},
     {OFFF},
     {OFFF}},
    
     {{BOTH},                                                               //13
     {OFFF},
     {BOTH},
     {OFFF},
     {BOTH},
     {OFFF},
     {BOTH}},
    
     {{OFFF},                                                               //14
     {OFFF},
     {OFFF},
     {OFFF},
     {OFFF},
     {OFFF},
     {OFFF}},
    
     {{BOTH},                                                               //15
     {BOTH},
     {BOTH},
     {BOTH},
     {BOTH},
     {BOTH},
     {BOTH}},
    
     {{OFFF},                                                               //16
     {OFFF},
     {OFFF},
     {OFFF},
     {OFFF},
     {OFFF},
     {OFFF}},
};
const unsigned char ROM_Sub_Patterns_Time [MAX_Sub_Patterns][MAX_Sub_Patterns_Columns] = {
    {14,9, 0, 0, 0, 0, 0},          //0 Single Color Ch1 or Ch2 OFF    Fast
    {10,10, 6, 0, 0, 0, 0},         //1 Single Color Ch1 or Ch2 Single Fast
    {25,14, 0, 0, 0, 0, 0},          //2 Single Color Ch1 or Ch2 OFF    Slow               //This DOES affect single color dual slow pattern off time.
    {16,15, 8, 0, 0, 0},             //3 Single Color Ch1 or Ch2 Single Slow
    {16, 8, 15, 0, 0, 0, 0},       //4 Single Color Ch1 or Ch2 Double Slow                 //Index 4+2 of this array=Double slow  //This DOES affect double slow patterns. Both Color 1 and 2 independentaly. It affects the combo slow fast pattern as well. Does not affect the dual color patterns though including dead time and no dead time.
    {11, 4, 11, 4, 10, 0, 0},      //5 Single Color Ch1 or Ch2 Triple Slow
    {10, 5, 10, 1, 0, 0, 0},        //6 Single Color Ch1 or Ch2 Double Fast
    {7, 3, 6, 3, 6, 1, 0},          //7 Single Color Ch1 or Ch2 Triple Fast
    {10,10, 6, 0, 0, 0, 0},         //8
    
    {8,9,0,0,0,0,0},                //9
    {8,8,0,0,0,0,0},                //10
    {3,3,7,0,0,0,0},                //11
    {7,8,0,0,0,0,0},                //12
    {3,3,3,3,3,3,7},                //13
    {13,13,0,0,0,0,0},              //14
    {4,7,0,0,0,0,0},                //15
    {4,6,0,0,0,0,0}                 //16
    ///////////Every time above is for single color patterns.///////////////   
 
//    {35, 6, 0, 0, 0, 0, 0},          //8 CHN1 SLOW
//    {35, 6, 0, 0, 0, 0, 0},          //9 CHN2 SLOW
//    {35, 6, 0, 0, 0, 0, 0},          //10 ALL CHN OFF SLOW For dead time
//    {15, 6, 0, 0, 0, 0, 0},          //11 CHN1 FAST
//    {15, 6, 0, 0, 0, 0, 0},          //12 CHN2 FAST
//    {15, 6, 0, 0, 0, 0, 0},          //13 ALL CHN OFF FAST for dead time
//    { 1, 2, 1,10, 0, 0, 0},          //14 Double slow CH1                     //This only affects Color 1 on dual color patterns not single color patterns.
//    { 16, 8, 16,40, 0, 0, 0},          //15 Double slow CH2
//    { 16, 8, 16,40, 0, 0, 0},          //16 Double slow OFF TIME
//    { 6, 6, 6,15, 0, 0, 0},          //17 Double fast CH1
//    { 6, 6, 6,15, 0, 0, 0},          //18 Double fast CH2
//    { 6, 6, 6,15, 0, 0, 0},          //19 Double fast OFF TIME
//    { 8, 8, 8, 8, 8,35, 0},          //20 Triple slow CH1
//    { 8, 8, 8, 8, 8,35, 0},          //21 Triple slow CH2
//    { 8, 8, 8, 8, 8,35, 0},          //22 Triple slow OFF TIME
//    { 6, 6, 6, 6, 6,15, 0},          //23 Triple fast CH1
//    { 6, 6, 6, 6, 6,15, 0},          //24 Triple fast CH2
//    { 6, 6, 6, 6, 6,15, 0},          //25 Triple fast OFF TIME
//    {10,10, 0, 0, 0, 0, 0},          //26 CHN1 Steady
//    {10,10, 0, 0, 0, 0, 0},          //27 CHN2 Steady
//    { 6, 6, 6, 6, 6, 6, 0},          //28 Triple fast CH1 Brake
//    { 6, 6, 6, 6, 6, 6, 0},          //29 Triple fast CH2 Brake
};
const unsigned char ROM_COMBO_Patterns [MAX_Combo_Patterns][MAX_Combo_Patterns_Columns] = {
//  { 1, 1, 2, 2, 3, 3, 4, 4, 5, 5, 6, 6, 7, 7, 8, 8, 9, 9,10,10,11,11,12,12,13,13,14,14,15,15,16,16,17,17,18,18,19,19,20,20,21,21,22,22,23,23,24,24,25,25,26,26,27,27,28,28,29,29,30,30}
    { 8, 8, 8, 8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8}  ,       //0 single slow
    { 8, 8, 8, 8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8}  ,       //1 single fast
    { 8, 8, 8, 8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8}  ,       //2 combo
    { 8, 8, 8, 8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8}  ,       //3 double slow
    { 8, 8, 8, 8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8}  ,       //4 double fast
    { 8, 8, 8, 8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8}  ,       //5 combo
    { 8, 8, 8, 8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8}  ,       //6 triple slow
    { 8, 8, 8, 8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8} ,       //7 triple fast
    { 8, 8, 8, 8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8}  ,       //8 combo
    
    { 8, 8, 8, 8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8}  ,       //9 Attack 1
    { 8, 8, 8, 8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8}  ,       //10 Attack 2
    
    { 8, 8, 8, 8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8} ,       //11 Brake, 6 LED Tripple fast then 6 LED steady ON
    { 8, 8, 8, 8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8} ,       //12 Steady on 12 LED
    { 8, 8, 8, 8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8}       //13  Steady on 12 LED dim
    
 //   { 7, 8, 8, 8,99,99,99,99,99,99,99,99,99,99,99,99,99,99,99,99,99,99},       //14 CH2 Brake, 6 LED Tripple fast then 6 LED steady ON
 //   { 8, 8, 8, 8,99,99,99,99,99,99,99,99,99,99,99,99,99,99,99,99,99,99},       //15 CH2 Steady on 12 LED
 //   { 8, 8, 8, 8,99,99,99,99,99,99,99,99,99,99,99,99,99,99,99,99,99,99}       //16 CH2 Steady on 12 LED
//    { 8, 9, 8, 9,99,99,99,99,99,99,99,99,99,99,99,99},       //9  Single Slow                   S1
//    {11,12,11,12,99,99,99,99,99,99,99,99,99,99,99,99},       //10 Single Fast                   S2
//    { 8, 9, 8, 9, 8, 9,11,12,11,12,11,12,11,12,99,99},       //11 Single Combo
//    {14,15,14,15,99,99,99,99,99,99,99,99,99,99,99,99},       //12 Double Slow                   S3
//    {17,18,17,18,99,99,99,99,99,99,99,99,99,99,99,99},       //13 Double Fast                   S4
//    {14,15,14,15,14,15,17,18,17,18,17,18,17,18,99,99},       //14 Double Combo
//    {20,21,20,21,99,99,99,99,99,99,99,99,99,99,99,99},       //15 Tripple Slow                  S5
//    {23,24,23,24,99,99,99,99,99,99,99,99,99,99,99,99},       //16 Tripple Fast                  S6
//    {20,21,20,21,20,21,23,24,23,24,23,24,23,24,99,99},       //17 Tripple Combo
//    { 8,10, 9,10,99,99,99,99,99,99,99,99,99,99,99,99},       //18 Single Slow with dead time    S1
//    {11,13,12,13,99,99,99,99,99,99,99,99,99,99,99,99},       //19 Single Fast with dead time    S2
//    { 8,10, 9,10, 8,10,12,13,11,13,12,13,11,13,12,13},       //20 Single Combo with dead time
//    {14,16,15,16,99,99,99,99,99,99,99,99,99,99,99,99},       //21 Double Slow with dead time    S3
//    {17,19,18,19,99,99,99,99,99,99,99,99,99,99,99,99},       //22 Double Fast with dead time    S4
//    {14,16,15,16,14,16,18,19,17,19,18,19,17,19,18,19},       //23 Double combo with dead time
//    {20,22,21,22,99,99,99,99,99,99,99,99,99,99,99,99},       //24 Tripple Slow with dead time   S5
//    {23,25,24,25,99,99,99,99,99,99,99,99,99,99,99,99},       //25 Tripple Fast with dead time   S6
//    {20,22,21,22,20,22,24,25,23,25,24,25,23,25,24,25},       //26 Tripple Combo with dead time
//    {28,26,26,26,99,99,99,99,99,99,99,99,99,99,99,99},       //27 Brake, CHN1 Tripple fast then CHN1 steady ON
//    {29,27,27,27,99,99,99,99,99,99,99,99,99,99,99,99},       //28 Brake, CHN2 Tripple fast then CHN2 steady ON
//    {26,26,26,26,99,99,99,99,99,99,99,99,99,99,99,99},       //29 Steady on CHN1
//    {27,27,27,27,99,99,99,99,99,99,99,99,99,99,99,99},       //30 Steady on CHN2
//    {26,26,26,26,99,99,99,99,99,99,99,99,99,99,99,99},       //29 Steady on CHN1
//    {27,27,27,27,99,99,99,99,99,99,99,99,99,99,99,99},       //30 Steady on CHN2
};


volatile unsigned char channelToBeDisplayed = 0;
volatile bool bDualColor = 0;
volatile unsigned char GLOBAL_CHANNELS_EN_DUAL = 0;
volatile unsigned bool pwmBool = true;

/*
 * Description of the COMBO matrix :
 * {Sub_Pattern_index, # of repetition, Sub_Pattern_index, # of repetition, ... }
 * {Sub_Pattern_index, # of repetition, Sub_Pattern_index, # of repetition, ... }
 *
 *
 */
eeprom unsigned char EEprom_mode [MAX_MODES];
eeprom unsigned char EEprom_Written_Flag;
eeprom bool EEprom_InPhase [MAX_MODES];

void SetOUTPUT(void)
{
    static unsigned char temporaryGPIO = 0x00;
	static unsigned char pwmCounter = 0;
    
    //if (bGLOBAL_ENABLE_LEDS)
    //{        
        
        //temporaryGPIO = OUTPUT_BUFFER & GLOBAL_CHANNELS_EN;
        
        //if((temporaryGPIO & 0x03) == 0x01 || (temporaryGPIO & 0x03) == 0x02)
        //    temporaryGPIO ^= 0x03;
        
        //if(pwmBool == true)
        //{
           pwmCounter++;
           if(pwmCounter<10)
            {
                GPIO = 0xFF;
            }
            else
            {
                GPIO = 0;
            }

            if(pwmCounter>10)
            {
                pwmCounter = 0;
            }
            
            //GPIO = 0xFF;
        //}
       //else
       // {
       //     GPIO = temporaryGPIO;
       // }   
    //}
    //else
    //{
        //if (bGLOBAL_IS_PROGRAMMING)
        //{
        //    if (!bGLOBAL_CHANGING_PATTERN)
        //    {
        //        if (bGLOBAL_InPhase)
        //            GPIO = 0x23;
        //        else
        //            GPIO = 0x20;
        //    }
        //}else
        //{
        //    GPIO = 0;
       // }
    //}
}

void WaitForSYNC_PU(void)
{
        //unsigned char temp001 = 0;
        //while(temp001 < 250)
        //{
        //    if (SYNC_Line)
        //        temp001++;
        //    else
        //        temp001 = 0;
        //}
}

void WriteEEPROMDefaults(void)
{
    //GLOBAL_Mode_copy[0] = 0;          //Starting Pattern
    //GLOBAL_Mode_copy[1] = 3;          //starting pattern
//    GLOBAL_Mode_copy[2] = 36;          // starting pattern
    //bGLOBAL_InPhase_copy[0] = true;
    //bGLOBAL_InPhase_copy[1] = true;
//    bGLOBAL_InPhase_copy[2] = true;

    //ReWriteEEPROM();
    
   // if (EEprom_Written_Flag != EEprom_Written_Flag_Value)
   //     while (1) {}        //lock program and special flash the status LED because could not write to EEprom
}

void ReWriteEEPROM (void) //This function must not be called except when updated values are saved in the shadow RAM arrays : GLOBAL_TAKEDOWN_MODULES[] and GLOBAL_Mode_copy[]
{
//    EEprom_Written_Flag = 0xFF; //clear the EEprom flag before any write to EEprom
//    for (unsigned char i=0;i<MAX_MODES;i++)
//    {
//        EEprom_mode[i] = GLOBAL_Mode_copy[i];
//        EEprom_InPhase[i] = bGLOBAL_InPhase_copy[i];
//    }
//   EEprom_Written_Flag = EEprom_Written_Flag_Value;
}

void INC_EEPROM_MODE (void)
{
    unsigned char Temp_Mode_Data;
    Temp_Mode_Data = GLOBAL_Mode_copy[GLOBAL_Selected_Mode_Type];

//    if (GLOBAL_Selected_Mode_Type == 2)
//    {
//        if (Temp_Mode_Data < (MAX_MODE_PATTERNS - 1))
//        GLOBAL_Mode_copy[GLOBAL_Selected_Mode_Type]++;
//        else GLOBAL_Mode_copy[GLOBAL_Selected_Mode_Type] = 0;
//    }
//    if (GLOBAL_Selected_Mode_Type == 1)
//    {
//        if (Temp_Mode_Data < (MAX_MODE_PATTERNS - 1))
//        GLOBAL_Mode_copy[GLOBAL_Selected_Mode_Type]++;
//        else GLOBAL_Mode_copy[GLOBAL_Selected_Mode_Type] = 0;
//    }
//    if (GLOBAL_Selected_Mode_Type == 0)
//    {
//        if (Temp_Mode_Data < (MAX_MODE_PATTERNS - 1))
//        GLOBAL_Mode_copy[GLOBAL_Selected_Mode_Type]++;
//        else GLOBAL_Mode_copy[GLOBAL_Selected_Mode_Type] = 0;
//    }
//    ReWriteEEPROM();
//    Update_ComboPattern_Index();
}

void Read_Mode_Input(void)
{
   //if (MODE1)
   //{   GLOBAL_MODE1_LOW_counter = 0;
   //    if (GLOBAL_MODE1_counter < General_Debounce_Max_Count) GLOBAL_MODE1_counter++;
   //    else bGLOBAL_MODE1_PRESSED = true;
   //}   else {
   //    GLOBAL_MODE1_counter = 0;
   //    if (GLOBAL_MODE1_LOW_counter < General_Debounce_Max_Count) GLOBAL_MODE1_LOW_counter++;
   //    else bGLOBAL_MODE1_PRESSED = false;
  // }
//   if (MODE2)
//   {   GLOBAL_MODE2_LOW_counter = 0;
//       if (GLOBAL_MODE2_counter < General_Debounce_Max_Count) GLOBAL_MODE2_counter++;
//       else bGLOBAL_MODE2_PRESSED = true;
//   }   else {
//       GLOBAL_MODE2_counter = 0;
//       if (GLOBAL_MODE2_LOW_counter < General_Debounce_Max_Count) GLOBAL_MODE2_LOW_counter++;
//       else bGLOBAL_MODE2_PRESSED = false;
//   }
//   if (!SYNC_Line) //For Pattern line PRESSED = true status is not asserted here
//   {   GLOBAL_SYNC_Line_LOW_counter = 0;
//       if (GLOBAL_SYNC_Line_counter < SYNC_Line_Debounce_Max_Count) GLOBAL_SYNC_Line_counter++;
//       //else bGLOBAL_SYNC_Line_PRESSED = true;
//   }   else {
//       GLOBAL_SYNC_Line_counter = 0;
//       if (GLOBAL_SYNC_Line_LOW_counter < General_Debounce_Low_Max_Count) GLOBAL_SYNC_Line_LOW_counter++;
//       else bGLOBAL_SYNC_Line_PRESSED = false;
//   }
}

void Update_ComboPattern_Index(void)
{
 //GLOBAL_Selected_Mode_Number = GLOBAL_Mode_copy[GLOBAL_Selected_Mode_Type];
 //   GLOBAL_combo_patterns_index = GLOBAL_Selected_Mode_Number;
    
  //  pwmBool = true;
    
  //  if(GLOBAL_Selected_Mode_Number < 11)    //CH1 patterns
  //  {
  //      bGLOBAL_STEADY_ON = false;
  //      GLOBAL_combo_patterns_index = GLOBAL_Selected_Mode_Number;
  //      GLOBAL_CHANNELS_EN = 0xFE;
  //      bDualColor = false;
   // }
    //else if(GLOBAL_Selected_Mode_Number >= 11 && GLOBAL_Selected_Mode_Number < 22)  //CH2 patterns
    //{
    //   GLOBAL_Selected_Mode_Number = GLOBAL_Selected_Mode_Number - 11;
    //    GLOBAL_combo_patterns_index = GLOBAL_Selected_Mode_Number;
    //    GLOBAL_CHANNELS_EN = 0xFE;        
    //    bGLOBAL_STEADY_ON = false;
    //    bDualColor = false;
    //}
    //else if(GLOBAL_Selected_Mode_Number >= 22 && GLOBAL_Selected_Mode_Number < 33) //CH1 and CH2 patterns
    //{
    //    GLOBAL_Selected_Mode_Number = GLOBAL_Selected_Mode_Number - 22;
    //    GLOBAL_combo_patterns_index = GLOBAL_Selected_Mode_Number;
    //    //GLOBAL_CHANNELS_EN = 0xFD;        
    //    bGLOBAL_STEADY_ON = false;
    //    bDualColor = true;
    //}
    //else if(GLOBAL_Selected_Mode_Number >= 33 && GLOBAL_Selected_Mode_Number < 36) //CH1 Steady on patterns
    //{
    //   GLOBAL_Selected_Mode_Number = GLOBAL_Selected_Mode_Number - 22;
    //    GLOBAL_combo_patterns_index = GLOBAL_Selected_Mode_Number;
    //    GLOBAL_CHANNELS_EN = 0xFE;
    //    bGLOBAL_STEADY_ON = true;
    //    bDualColor = false;
    //}
    //else if(GLOBAL_Selected_Mode_Number >= 36 && GLOBAL_Selected_Mode_Number < 39) //CH2 Steady on pattens
    //{
    //    GLOBAL_Selected_Mode_Number = GLOBAL_Selected_Mode_Number - 25;
    //    GLOBAL_combo_patterns_index = GLOBAL_Selected_Mode_Number;
    //    GLOBAL_CHANNELS_EN = 0xFD;
    //    bGLOBAL_STEADY_ON = true;
    //    bDualColor = false;
    //}
      
//    if (GLOBAL_Selected_Mode_Number < 9)
//    {
//        GLOBAL_combo_patterns_index = GLOBAL_Selected_Mode_Number;
//        GLOBAL_CHANNELS_EN = 0xFD;
//    } 
//    else
//    {
//        GLOBAL_Selected_Mode_Number = GLOBAL_Selected_Mode_Number - 9;
//        GLOBAL_combo_patterns_index = GLOBAL_Selected_Mode_Number;
//        if (GLOBAL_Selected_Mode_Number < 9)
//        {
//            GLOBAL_CHANNELS_EN = 0xFE;
//        }
//        else
//            GLOBAL_CHANNELS_EN = 0xFF;
//    }
//    if (GLOBAL_combo_patterns_index > 26)
//    {
//        OUTPUT_BUFFER = OUTPUT_BUFFER & GLOBAL_CHANNELS_EN_copy;
//        bGLOBAL_STEADY_ON = true;
//    }
//    else
//        bGLOBAL_STEADY_ON = false;
    
//    if(GLOBAL_combo_patterns_index == MAX_MODE_PATTERNS-1)
//    {
//        pwmBool = true;
//    }
    
//    if (GLOBAL_combo_patterns_index >= 11)
//    { 
//          bGLOBAL_STEADY_ON = true;
//          GLOBAL_CHANNELS_EN = 0xFE;
//    }
//    else
//    {
//        bGLOBAL_STEADY_ON = false;
//    }
    
    //GLOBAL_CHANNELS_EN_copy = GLOBAL_CHANNELS_EN;
//    GLOBAL_sub_patterns_column_index = MAX_Sub_Patterns_Columns;
//    GLOBAL_sub_patterns_timer = 0;
//    GLOBAL_Dummy_Counter2 = 0;

}


void Update_Input_Mode_Type(void)
{
 //   GLOBAL_Selected_Mode_Type = 0;
 //   if (bGLOBAL_MODE1_PRESSED)
 //       GLOBAL_Selected_Mode_Type = 1;
//    if (bGLOBAL_MODE2_PRESSED)
//        GLOBAL_Selected_Mode_Type = 2;
 //   if (GLOBAL_Selected_Mode_Type_copy != GLOBAL_Selected_Mode_Type)
 //       Update_ComboPattern_Index();
 //   bGLOBAL_InPhase = bGLOBAL_InPhase_copy[GLOBAL_Selected_Mode_Type];
 //   GLOBAL_Selected_Mode_Type_copy = GLOBAL_Selected_Mode_Type;
}

void Initial_Start (void)
{
    //unsigned char read_data;
    //read_data = EEprom_Written_Flag;
    //if (read_data ^ EEprom_Written_Flag_Value)
        //WriteEEPROMDefaults();
    //for (unsigned char i=0;i<MAX_MODES;i++)
    //{
   //     GLOBAL_Mode_copy[i] = EEprom_mode[i];
    //    bGLOBAL_InPhase_copy[i] = EEprom_InPhase[i];
    //}
    //while (GLOBAL_Dummy_Counter < 5) {}
    //Update_Input_Mode_Type();
    //Update_ComboPattern_Index();
}
/******************************************************************************/
/* Main Program                                                               */
/******************************************************************************/
void main(void)
{
    unsigned char tempvar1;
    /* Configure the oscillator for the device */
    ConfigureOscillator();
    /* Initialize I/O and Peripherals for application */
    InitApp();
    Initial_Start(); //Verify and set the EEprom on initial start
    //bGLOBAL_ENABLE_LEDS = true;         //MCU will turn ON outputs after a typical time of ~34ms

    while(1)
    {
        //if (!bGLOBAL_IS_PROGRAMMING)
            CLRWDT();
            
        //    SetOUTPUT();
//        Update_Input_Mode_Type();
        /* TODO <INSERT USER APPLICATION CODE HERE> */

    //    Update_Input_Mode_Type();
        //if ((GLOBAL_SYNC_Line_counter == SYNC_Line_Debounce_Max_Count) && (!bGLOBAL_SYNC_Line_PRESSED))
       // {
       //     bGLOBAL_SYNC_Line_PRESSED = true;
       //     bGLOBAL_ENABLE_LEDS = false;
       //     SetOUTPUT();
       // }
       // SetOUTPUT();
        /*
        if (bGLOBAL_SYNC_Line_PRESSED && (!bGLOBAL_IS_PROGRAMMING))
        {
            GLOBAL_Dummy_Counter = 0;
            while ((GLOBAL_Dummy_Counter < 199)) {}
            tempvar1 = GLOBAL_Dummy_Counter;
            CLRWDT();
            if (tempvar1 > 198)
            {
                GLOBAL_Mode_copy[GLOBAL_Selected_Mode_Type] = 0;
                bGLOBAL_CHANGING_PATTERN = false;
                bGLOBAL_InPhase = !bGLOBAL_InPhase;
                bGLOBAL_InPhase_copy[GLOBAL_Selected_Mode_Type] = bGLOBAL_InPhase;
                bGLOBAL_IS_PROGRAMMING = true;
                SetOUTPUT();
                ReWriteEEPROM();
				Update_ComboPattern_Index();
            }
            if (tempvar1 < 199)
            {
                GLOBAL_Dummy_Counter = 0;
                while (SYNC_Line && GLOBAL_Dummy_Counter < 2) {}   //this is added to check if the line was effectively released between 10ms to 20ms high
                if (GLOBAL_Dummy_Counter > 1)                      // and a pattern change command is the intended command to be sent on the line
                {
                    bGLOBAL_CHANGING_PATTERN = true;
                    INC_EEPROM_MODE();
                    GLOBAL_Dummy_Counter = 0;
                    bGLOBAL_IS_PROGRAMMING = true;
                }
            }
        }
*/
        /*
        if (((GLOBAL_SYNC_Line_LOW_counter > 3) || (GLOBAL_Dummy_Counter > 4)) && (!bGLOBAL_CHANGING_PATTERN_Enforce) && bGLOBAL_CHANGING_PATTERN)
        {
            bGLOBAL_CHANGING_PATTERN_Enforce = true; // this condition will generate a pull down of the sync line
            GLOBAL_Dummy_Counter = 0;                  //after the Changing pattern condition is flagged to ensure all modules are changing pattern
            SYNC_CTRL = 1;                              //the line will stay high for at least 30 ms before pulling the sync line low
        }

        if (bGLOBAL_CHANGING_PATTERN_Enforce && (GLOBAL_Dummy_Counter > 12))
        {
            GLOBAL_Dummy_Counter = 0;                       //this condition will release the sync line after a duration of 130ms
            bGLOBAL_DISABLE_SYNC_Line_PRESSED = true;       //this condition will not be executed unless the changing pattern enforce flag is set
            SYNC_CTRL = 0;
        }

        if (bGLOBAL_DISABLE_SYNC_Line_PRESSED)
        {
            if (!SYNC_Line)                     //if sync line stays low after the MCU finishes sending the pattern change enforce signal for a 130ms
            {                                    //then the sync line counter will be always cleared not allowing the code to enter into another programming sequence
                GLOBAL_Dummy_Counter = 0;       //the sync line counter will be allowed back to increment until
                GLOBAL_SYNC_Line_counter = 0;   //the MCU sees the Sync line high for a continous duration of (General_Debounce_Low_Max_Count + 3)
            }
            if (GLOBAL_Dummy_Counter > General_Debounce_Low_Max_Count + 3)
               bGLOBAL_DISABLE_SYNC_Line_PRESSED = false;
        }

        if (!bGLOBAL_SYNC_Line_PRESSED)
        {
            bGLOBAL_ENABLE_LEDS = true;
            bGLOBAL_CHANGING_PATTERN = false;
            bGLOBAL_CHANGING_PATTERN_Enforce = false;
            bGLOBAL_IS_PROGRAMMING = false;
        }
        */
    }
}