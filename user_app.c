/*!*********************************************************************************************************************
@file user_app.c                                                                
@brief User's tasks / applications are written here.  This description
should be replaced by something specific to the task.

------------------------------------------------------------------------------------------------------------------------
GLOBALS
- NONE

CONSTANTS
- NONE

TYPES
- NONE

PUBLIC FUNCTIONS
- NONE

PROTECTED FUNCTIONS
- void UserApp1Initialize(void)
- void UserApp1Run(void)


**********************************************************************************************************************/

#include "configuration.h"

/***********************************************************************************************************************
Global variable definitions with scope across entire project.
All Global variable names shall start with "G_<type>UserApp1"
***********************************************************************************************************************/
/* New variables */
volatile u8 G_u8UserAppFlags;                             /*!< @brief Global state flags */


/*--------------------------------------------------------------------------------------------------------------------*/
/* Existing variables (defined in other files -- should all contain the "extern" keyword) */
extern volatile u32 G_u32SystemTime1ms;                   /*!< @brief From main.c */
extern volatile u32 G_u32SystemTime1s;                    /*!< @brief From main.c */
extern volatile u32 G_u32SystemFlags;                     /*!< @brief From main.c */


/***********************************************************************************************************************
Global variable definitions with scope limited to this local application.
Variable names shall start with "UserApp_<type>" and be declared as static.
***********************************************************************************************************************/


/**********************************************************************************************************************
Function Definitions
**********************************************************************************************************************/

/*--------------------------------------------------------------------------------------------------------------------*/
/*! @publicsection */                                                                                            
/*--------------------------------------------------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------------------------------------------------*/
/*! @protectedsection */                                                                                            
/*--------------------------------------------------------------------------------------------------------------------*/

/*!--------------------------------------------------------------------------------------------------------------------
@fn void UserAppInitialize(void)

@brief
Initializes the application's variables.

Should only be called once in main init section.

Requires:
- NONE

Promises:
- NONE

*/
void UserAppInitialize(void)
{
    T0CON0 =0x90;
    T0CON1 =0x54;


} /* end UserAppInitialize() */

  
/*!----------------------------------------------------------------------------------------------------------------------
@fn void UserAppRun(void)

@brief Application code that runs once per system loop

Requires:
- 

Promises:
- 

*/
void UserAppRun(void)
{
    static u16 u16counter=0; //timer counter
    static u8 u8pcounter=0;  //pattern counter
    u8 au8pattern[]={0x01,0x20,0x02,0x10,0x04,0x08};
    if(u16counter>=500) //delay 500 ms
    {
        u16counter=0;
        LATA=au8pattern[u8pcounter];
        u8pcounter++;
        
    }
    u16counter++;
    if(u8pcounter>5)
        u8pcounter=0;
    
}
  /* end UserAppRun */
/*--------------------
void TimeXus(INPUT_PARAMETER_)
 * Sets Timer0 to count u16Microseconds_
 * 
 * Requires:
 * -Timer0 configured such that each timer tick is 1 microsecond
 * -INPUT_PARAMETER_ is the value in microseconds to time from 1 to 65535
 * 
 * Promises:
 * -Pre-loads TMR0H:L to clock out desired period
 * -TMR0IF cleared 
 * -Timer0 enabled
 */

void TimeXus(u16 u16timer)
{
    T0CON0 =T0CON0 & 0x7f;
    TMR0H =((0xffff - u16timer) & 0xff00) >> 8;
    TMR0L =(0xffff - u16timer) & 0xff;
    PIR3 =PIR3 & 0x7f;
    T0CON0 =T0CON0 | 0x80;
}


/*------------------------------------------------------------------------------------------------------------------*/
/*! @privatesection */                                                                                            
/*--------------------------------------------------------------------------------------------------------------------*/





/*--------------------------------------------------------------------------------------------------------------------*/
/* End of File                                                                                                        */
/*--------------------------------------------------------------------------------------------------------------------*/
