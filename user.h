/******************************************************************************/
/* User Level #define Macros                                                  */
/******************************************************************************/

#define OUT1        (GPIObits.GP0) //
#define OUT2        (GPIObits.GP1) //
#define SYNC_CTRL   (GPIObits.GP5) //

#define MODE1       (GPIObits.GP2) //for F6-S
#define MODE2       (GPIObits.GP3) // for F6-S and HAW
#define SYNC_Line    (GPIObits.GP4) //

#define Interrupt_Timer_ms  10
#define Background_Interrupt_Timer 131//(256 - (Interrupt_Timer_ms * FCY * 0.001 % 256)) //formula to compute TMR0 value
#define EEprom_Written_Flag_Value 0xA6
#define OFF 0
#define OFFF 0
#define CH1 1
#define CH2 2
#define DISABLED 0
#define CHN1 1
#define CHN2 2
#define BOTH 3
#define MAX_Sub_Patterns     17
#define MAX_Sub_Patterns_Columns        7
#define MAX_MODE_PATTERNS               14                    //
#define MAX_MODES                       2
#define MAX_Combo_Patterns              (MAX_MODE_PATTERNS)
#define MAX_Combo_Patterns_Columns      22
#define General_Debounce_Max_Count      4
#define General_Debounce_Low_Max_Count  7
#define SYNC_Line_Debounce_Max_Count    9+0              //added from 25 to 9





/* TODO Application specific user parameters used in user.c may go here */
extern volatile unsigned char GLOBAL_sub_patterns_index;         //used to communicate the selected sub pattern
extern volatile unsigned char GLOBAL_sub_patterns_index_copy;
extern volatile unsigned char GLOBAL_sub_patterns_column_index;  //used to move inside the selected sub pattern
extern volatile unsigned char GLOBAL_combo_patterns_index;       //used to communicate the selected combo pattern
extern volatile unsigned char GLOBAL_combo_patterns_index_copy;
extern volatile unsigned char GLOBAL_combo_patterns_column_index;//used to move inside the selected combo pattern
extern volatile unsigned char GLOBAL_sub_patterns_timer;       //used to update the timer counter
extern volatile unsigned char GLOBAL_combo_patterns_counter;
extern volatile unsigned char GLOBAL_Selected_Mode_Number;
extern volatile unsigned char GLOBAL_Selected_Mode_Type;
extern volatile unsigned char GLOBAL_Dummy_Counter;
extern volatile unsigned char GLOBAL_Dummy_Counter2;
extern volatile unsigned char GLOBAL_MODE1_counter;
extern volatile unsigned char GLOBAL_SYNC_Line_counter;
extern volatile unsigned char GLOBAL_MODE2_counter;
extern volatile unsigned char GLOBAL_TEMP_REG;
extern volatile unsigned char GLOBAL_MODE1_LOW_counter;
extern volatile unsigned char GLOBAL_SYNC_Line_LOW_counter;
extern volatile unsigned char GLOBAL_MODE2_LOW_counter;
extern volatile unsigned char GLOBAL_SYNC_PULSE_Counter;
extern volatile unsigned char GLOBAL_CHANNELS_EN;

extern volatile bool bGLOBAL_CHANGING_PATTERN;
extern volatile bool bGLOBAL_SYNC_SENT;
extern volatile bool bGLOBAL_END_OF_CYCLE_COND1;
extern volatile bool bGLOBAL_END_OF_CYCLE_COND2;
extern volatile bool bGLOBAL_IS_PROGRAMMING;
extern volatile bool bGLOBAL_InPhase;
extern volatile bool bGLOBAL_ENABLE_LEDS;
extern volatile bool bGLOBAL_SYNC_Line_PRESSED;
extern volatile bool bGLOBAL_OUTPUT_BUFFER_CHANGED;
extern volatile bool bGLOBAL_STEADY_ON ;

extern volatile unsigned char OUTPUT_BUFFER;
extern volatile unsigned char OUTPUT_BUFFER_COPY;
extern const unsigned char ROM_Sub_Patterns [MAX_Sub_Patterns][MAX_Sub_Patterns_Columns];
extern const unsigned char ROM_Sub_Patterns_Time [MAX_Sub_Patterns][MAX_Sub_Patterns_Columns];
extern const unsigned char ROM_COMBO_Patterns [MAX_Combo_Patterns][MAX_Combo_Patterns_Columns];

extern volatile unsigned char channelToBeDisplayed;
extern volatile bool bDualColor;
extern volatile unsigned char GLOBAL_CHANNELS_EN_DUAL;


/******************************************************************************/
/* User Function Prototypes                                                   */
/******************************************************************************/

/* TODO User level functions prototypes (i.e. InitApp) go here */

void InitApp(void);         /* I/O and Peripheral Initialization */
void SetOUTPUT(void);
void Read_Mode_Input(void);
void Update_ComboPattern_Index(void);
void ReWriteEEPROM(void);
void WaitForSYNC_PU(void);