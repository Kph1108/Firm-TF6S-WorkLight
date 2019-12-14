/******************************************************************************/
/*Files to Include                                                            */
/******************************************************************************/

#if defined(__XC)
    #include <xc.h>         /* XC8 General Include File */
#elif defined(HI_TECH_C)
    #include <htc.h>        /* HiTech General Include File */
#endif

#include <stdint.h>         /* For uint8_t definition */
#include <stdbool.h>

#include "user.h"        /* For true/false definition */


/******************************************************************************/
/* Interrupt Routines                                                         */
/******************************************************************************/

/* Baseline devices don't have interrupts. Note that some PIC16's 
 * are baseline devices.  Unfortunately the baseline detection macro is 
 * _PIC12 */
#ifndef _PIC12

void interrupt isr(void)
{
    volatile unsigned char temp_data1;
    static unsigned char tenMSCounter = 0;
    static unsigned char pwmCounter = 0;
   
    /* This code stub shows general interrupt handling.  Note that these
    conditional statements are not handled within 3 seperate if blocks.
    Do not use a seperate if block for each interrupt flag to avoid run
    time errors. */

#if 0
    
    /* TODO Add interrupt routine code here. */

    /* Determine which flag generated the interrupt */
    if(<Interrupt Flag 1>)
    {
        <Interrupt Flag 1=0>; /* Clear Interrupt Flag 1 */
    }
    else if (<Interrupt Flag 2>)
    {
        <Interrupt Flag 2=0>; /* Clear Interrupt Flag 2 */
    }
    else
    {
        /* Unhandled interrupts */
    }

#endif
    
    if (INTCONbits.TMR0IF && INTCONbits.TMR0IE)
    {
        TMR0 = Background_Interrupt_Timer;       
        
        //if (bGLOBAL_OUTPUT_BUFFER_CHANGED || bGLOBAL_STEADY_ON)
       // {
            SetOUTPUT();    //set the output pins
      //      bGLOBAL_OUTPUT_BUFFER_CHANGED = false;
      //  }
        tenMSCounter++;
        if(tenMSCounter>9)
        {
            tenMSCounter = 0;
//            if ((GLOBAL_sub_patterns_column_index < MAX_Sub_Patterns_Columns) && (GLOBAL_sub_patterns_timer == 0))
//            {
//                if (GLOBAL_sub_patterns_index_copy != GLOBAL_sub_patterns_index) // condition to reset the sub_patters_column_index if the sub_patterns_index was changed
//                {
//                    GLOBAL_sub_patterns_column_index = 0;
//                    GLOBAL_sub_patterns_index_copy = GLOBAL_sub_patterns_index;
//                }
//                /*updating the pattern timer variable*/
//                GLOBAL_sub_patterns_timer = ROM_Sub_Patterns_Time[GLOBAL_sub_patterns_index][GLOBAL_sub_patterns_column_index];
//                /* Updating the output buffer in a for loop*/
//                OUTPUT_BUFFER = ROM_Sub_Patterns[GLOBAL_sub_patterns_index][GLOBAL_sub_patterns_column_index];//Updating_OUTPUT_Buffer
//                /*end of updating the output buffer*/
//                GLOBAL_sub_patterns_column_index++;
//                if (ROM_Sub_Patterns_Time[GLOBAL_sub_patterns_index][GLOBAL_sub_patterns_column_index] == 0)
//                    GLOBAL_sub_patterns_column_index = MAX_Sub_Patterns_Columns;
//            }
//           else {
//                if (GLOBAL_sub_patterns_column_index > (MAX_Sub_Patterns_Columns - 1))
//               {
//                        //add here the combo logic
//                        if (GLOBAL_combo_patterns_index_copy != GLOBAL_combo_patterns_index) // condition to reset the combo_patters_column_index if the combo_patterns_index was changed
//                        {
//                            GLOBAL_combo_patterns_column_index = 0;
//                            GLOBAL_combo_patterns_index_copy = GLOBAL_combo_patterns_index;
//                        }
//
//                        if (bGLOBAL_END_OF_CYCLE_COND1)
//                            bGLOBAL_END_OF_CYCLE_COND2 = true;
//
//                        if (bGLOBAL_InPhase)
//                            GLOBAL_sub_patterns_index = ROM_COMBO_Patterns[GLOBAL_combo_patterns_index][GLOBAL_combo_patterns_column_index];
//                        else
//                        {
//                            temp_data1 = GLOBAL_combo_patterns_column_index & 0x01;
//                            if (temp_data1)
//                                temp_data1 = GLOBAL_combo_patterns_column_index - 1;
//                            else
//                                temp_data1 = GLOBAL_combo_patterns_column_index + 1;
//                            GLOBAL_sub_patterns_index = ROM_COMBO_Patterns[GLOBAL_combo_patterns_index][temp_data1];
//                        }
//                        
//                        if(bDualColor == true)
//                        {
//                            if(GLOBAL_combo_patterns_column_index%2==1)
//                            {
//                                channelToBeDisplayed++;
//                                if(channelToBeDisplayed>1)
//                                {
//                                    channelToBeDisplayed = 0;
//                                }
//                                
//                                if(channelToBeDisplayed == 0)
//                                {
//                                    GLOBAL_CHANNELS_EN_DUAL = 0xFD;  
//                                }
//                                else
//                                {
//                                    GLOBAL_CHANNELS_EN_DUAL = 0xFE; 
//                                }   
//                            }
//                        }
//                        
//                        GLOBAL_combo_patterns_column_index++;
//                        if ((GLOBAL_combo_patterns_column_index > (MAX_Combo_Patterns_Columns - 1)) || (ROM_COMBO_Patterns[GLOBAL_combo_patterns_index][GLOBAL_combo_patterns_column_index] == 99))
//                        {
//                            if (bGLOBAL_STEADY_ON)
//                                GLOBAL_combo_patterns_column_index--;
//                            else
//                            {
//                                GLOBAL_combo_patterns_column_index = 0;
//                                bGLOBAL_END_OF_CYCLE_COND1 = true;
//                            }
//                        }
//                         GLOBAL_sub_patterns_column_index = 0;       //resetting the sub patterns column index for the next cycle
//                }
//            }
//
//            if ((GLOBAL_sub_patterns_timer < 6) && bGLOBAL_END_OF_CYCLE_COND1 && SYNC_Line && (GLOBAL_SYNC_PULSE_Counter == 0) && bGLOBAL_END_OF_CYCLE_COND2)
//            {
//                OUTPUT_BUFFER = OUTPUT_BUFFER | 0x20; //under this condition the Sync line will be pulled low 50ms before the last sub pattern timer reaches 0
//                bGLOBAL_SYNC_SENT = true;
//                bGLOBAL_END_OF_CYCLE_COND1 = false;
//                bGLOBAL_END_OF_CYCLE_COND2 = false;
//            }
//
//            if (!bGLOBAL_SYNC_SENT)                             //this conditional test must be before clearing the syn_sent flag
//            {
//                if ((!SYNC_Line) && (GLOBAL_SYNC_PULSE_Counter < 200))
//                        GLOBAL_SYNC_PULSE_Counter++;
//            }
//
//            if ((GLOBAL_sub_patterns_timer < 3) && bGLOBAL_SYNC_SENT)
//            {
//                OUTPUT_BUFFER = OUTPUT_BUFFER & 0xDF; //under this condition the sync line will be released 20ms before the last sub pattern timer reaches 0
//                bGLOBAL_SYNC_SENT = false;
//            }
//
//            if ((GLOBAL_SYNC_PULSE_Counter > 1) && (GLOBAL_SYNC_PULSE_Counter < 7) && SYNC_Line && !bGLOBAL_STEADY_ON)
//            {
//                GLOBAL_sub_patterns_column_index = MAX_Sub_Patterns_Columns; //under this condition the detected sync pulse must be 20ms to 60ms wide
//                GLOBAL_sub_patterns_timer =0;
//                GLOBAL_combo_patterns_column_index = 0;
//                GLOBAL_SYNC_PULSE_Counter = 0;
//                bGLOBAL_END_OF_CYCLE_COND1 = false;
//                bGLOBAL_END_OF_CYCLE_COND2 = false;
//            }
//
//            if (SYNC_Line && ((GLOBAL_SYNC_PULSE_Counter > 6) || (GLOBAL_SYNC_PULSE_Counter < 2)))
//                GLOBAL_SYNC_PULSE_Counter = 0;
//
//            if ((OUTPUT_BUFFER_COPY - OUTPUT_BUFFER) != 0)
//                bGLOBAL_OUTPUT_BUFFER_CHANGED = true;
//            OUTPUT_BUFFER_COPY = OUTPUT_BUFFER;
            //GLOBAL_Dummy_Counter++;
            //GLOBAL_Dummy_Counter2++;
            //if (GLOBAL_sub_patterns_timer > 0)
            //    GLOBAL_sub_patterns_timer--;
            //Read_Mode_Input();
		}
        INTCONbits.TMR0IF = 0;
    }
}
#endif


