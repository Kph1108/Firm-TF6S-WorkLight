/******************************************************************************/
/*Files to Include                                                            */
/******************************************************************************/

#if defined(__XC)
    #include <xc.h>         /* XC8 General Include File */
#elif defined(HI_TECH_C)
    #include <htc.h>        /* HiTech General Include File */
#endif

#include <stdint.h>        /* For uint8_t definition */
#include <stdbool.h>       /* For true/false definition */

#include "system.h"

/* Refer to the device datasheet for information about available
oscillator configurations. */
void ConfigureOscillator(void)
{
    /* TODO Add clock switching code if appropriate.  */

    /* Typical actions in this function are to tweak the oscillator tuning
    register, select new clock sources, and to wait until new clock sources
    are stable before resuming execution of the main project. */

    /*Setting up internal oscillator to be 8MHz using internal oscillator block*/
    OSCCON = _OSCCON_IRCF2_MASK | _OSCCON_IRCF1_MASK | _OSCCON_IRCF0_MASK | _OSCCON_SCS_MASK & (~_OSCCON_OSTS_MASK) ;
    while (OSCCONbits.HTS && OSCCONbits.LTS) // making sure internal clock is ready before proceeding
    {}
}
