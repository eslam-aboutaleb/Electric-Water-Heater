/* ////////////////////////////////////////////////////////////////////////////////////////////////////
Name: Eslam Aboutaleb
File: SW.h
Date: 4/7/2020
//////////////////////////////////////////////////////////////////////////////////////////////////// */
#ifndef __SW_H__
#define __SW_H__

#define N_SWITCHES      (3)

/*Switches*/
typedef enum
{
    SW_PLUS = 0,
    SW_MINUS,
    SW_ON_OFF
}tSW;

/*Switches states*/
typedef enum
{
    SW_RELEASED,
    SW_PRE_PRESSED,
    SW_PRESSED,
    SW_PRE_RELEASED
}tSW_State;

/*Functions prototypes*/
void SW_Init(void);
tSW_State SW_GetState(tSW sw);
void SW_Update(void);

#endif // __SW_H__
