/******************************************************************************/
/* Files to Include                                                           */
/******************************************************************************/

#if defined(__XC)
    #include <xc.h>         /* XC8 General Include File */
#elif defined(HI_TECH_C)
    #include <htc.h>        /* HiTech General Include File */
#endif

#include <stdint.h>         /* For uint8_t definition */
#include <stdbool.h>        /* For true/false definition */

#include "user.h"

/******************************************************************************/
/* User Functions                                                             */
/******************************************************************************/

/* <Initialize variables in user.h and insert code for user algorithms.> */

void InitApp(void)
{
    /* TODO Initialize User Ports/Peripherals/Project here */

    /* Setup analog functionality and port direction */

    /* Initialize peripherals */

    /* Enable interrupts */
//    PCONbits.SBODEN = 1;
    WDTCON = 0x17;               //Watch Dog timer reset to 1:65536 SWDTEN set high ~2.114ms
    OPTION_REGbits.nGPPU = 0;   // All internal pull up are enabled
    WPU = 0x10;                    //weak pull up enabled for GP4;
    GPIO = 0;
    CMCON0 = 0x07;
    ANSEL = 0;
    TRISIO = ~(_TRISIO_TRISIO0_MASK + _TRISIO_TRISIO1_MASK + _TRISIO_TRISIO5_MASK); //PINS of PortA as output
    bGLOBAL_ENABLE_LEDS = false;
    /* Timer 0 setup */
    OPTION_REGbits.T0CS = 0;    // Clock source for Timer0 to be internal instruction cycle clock
    OPTION_REGbits.PS = 0x3;     //Prescaler rate to be 1:256
    OPTION_REGbits.PSA = 0;     //Prescaler is assigned to Timer0 module
    /*interrupt setup */
    // Loop to make sure Sync line is pulled high before starting the program
    CLRWDT();
    WaitForSYNC_PU();               //Typical time till Pull up stabilized < ~2.5ms
    WPU = 0x00;                    //weak pull up disabled for All ports;
    TRISIObits.TRISIO4 = 0;
    GPIO = 0;
    TRISIObits.TRISIO4 = 1;
    WaitForSYNC_PU();              //Typical time till pull up stabilized at this location < ~1.7ms
    TMR0 = Background_Interrupt_Timer;
    INTCONbits.TMR0IF = 0;
    INTCON = _INTCON_T0IE_MASK + _INTCON_GIE_MASK; // Enabling Timer0 interrupt.
}

