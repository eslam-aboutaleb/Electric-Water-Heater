/* ////////////////////////////////////////////////////////////////////////////////////////////////////
Name: Eslam Aboutaleb
File: WH.h
Date: 4/7/2020
//////////////////////////////////////////////////////////////////////////////////////////////////// */
#ifndef WH_H
#define WH_H

/*Water heater states*/
typedef enum{
    WH_OFF,
    WH_ON
}tWH_State;

/*Water heater settings states*/
typedef enum{
    WH_NORMAL,
    WH_SETTING
}tWH_Settings;

/*Functions prototypes*/
void WH_Init(void);
tWord WH_GetTemp(void);
tWH_State WH_GetState(void);
void WH_Set_Temp(tWord Temp);
void WH_UsedTemp(void);
void WH_Update(void);

#endif // WH_H
