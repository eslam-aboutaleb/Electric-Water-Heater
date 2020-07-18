/* ////////////////////////////////////////////////////////////////////////////////////////////////////
Name: Eslam Aboutaleb
File: WH.c
Date: 4/7/2020
//////////////////////////////////////////////////////////////////////////////////////////////////// */
#include "Main.h"
#include "Port.h"
#include "WH.h"
#include "SW.h"
#include "Timer.h"
#include "Cooling_element.h"
#include "Heating_element.h"
#include "TempSensor.h"
#include "EEPROM.h"

/*Macros*/
#define WH_PERIOD_MS              (20)
#define WH_SETTING_PERIOD_MS      (5000)

#define MIN_TEMP                  (35)
#define MAX_TEMP                  (75)
#define DEF_TEMP                  (60)

#define TEMP_CHANGE_RATE          (5)

#define TEMP_MEM_ADDRESS          ((tWord)0x0020)

/*Variables*/
static tByte Current_Temp;
static tWH_State WH_State;
static tWord WH_Setting_Counter = 0;
tWH_Settings Settings;
static tByte FirstClick =0;

/*Local function prototypes*/
static void WH_CheckChange(void);
static void WH_TurnON_OFF(void);
static void WH_SaveLastTemp(void);
static void WH_Cool_Heat(void);
static void WH_FetchLastTemp(void);
static tByte WH_CheckFirstUse(void);

/*////////////////////////////////////////////////////////////////////////////////////// */
/*Initializes the water heater*/
/*////////////////////////////////////////////////////////////////////////////////////// */
void WH_Init(void)
{
    /*Initialize temperature with default which is 60*/
    Current_Temp = DEF_TEMP;
    /*Water heater is off*/
    WH_State = WH_OFF;
    /*Settings is Normal*/
    Settings = WH_NORMAL;
}

/*////////////////////////////////////////////////////////////////////////////////////// */
/*Returns the current temperature*/
/*////////////////////////////////////////////////////////////////////////////////////// */
tWord WH_GetTemp(void)
{
    return Current_Temp;
}

/*////////////////////////////////////////////////////////////////////////////////////// */
/*Gets the state of WH whether is it on or off*/
/*////////////////////////////////////////////////////////////////////////////////////// */
tWH_State WH_GetState(void)
{
    return WH_State;
}

/*////////////////////////////////////////////////////////////////////////////////////// */
/*Water heater update*/
/*////////////////////////////////////////////////////////////////////////////////////// */
void WH_Update(void)
{
    static tWord WH_counter = 0;

    /* Check if it is time for the SW_Update to run */
    WH_counter += TMR_TICK_MS;

    if (WH_counter != WH_PERIOD_MS){
        return;
    }

    WH_counter = 0;
    /*Save the last entered temperature*/
    WH_SaveLastTemp();
    /*Checks whether the on-off switch clicked or not*/
    WH_TurnON_OFF();
    /*Check if any of increase or decrease buttons have been pressed*/
    WH_CheckChange();
    /*Checks whether the cooler and heater start or not*/
    WH_Cool_Heat();
    /*If entered the setting mode*/
    if(Settings == WH_SETTING)
    {
        WH_Setting_Counter += WH_PERIOD_MS;
        if(WH_Setting_Counter != WH_SETTING_PERIOD_MS)
        {
            return;
        }
        WH_Setting_Counter = 0;
        /*After Setting period goes back to normal mode*/
        Settings = WH_NORMAL;
        /*make first click flag zero again*/
        FirstClick = 0;
    }
}

/*////////////////////////////////////////////////////////////////////////////////////// */
/*Sets the temperature*/
/*////////////////////////////////////////////////////////////////////////////////////// */
void WH_Set_Temp(tWord Temp)
{
    Current_Temp = Temp;
}

/*////////////////////////////////////////////////////////////////////////////////////// */
/*Save the last entered temperature*/
/*////////////////////////////////////////////////////////////////////////////////////// */
static void WH_SaveLastTemp(void)
{
    tWord Address = TEMP_MEM_ADDRESS;
    /*Write the current temperature in EEPROM*/
    EEPROM_Write(Address,Current_Temp);
}

/*////////////////////////////////////////////////////////////////////////////////////// */
/*Fetches the last temperature has been used*/
/*////////////////////////////////////////////////////////////////////////////////////// */
static void WH_FetchLastTemp(void)
{
    tByte Value=0;
    tWord Address = TEMP_MEM_ADDRESS;
    /*Read the current temperature from EEPROM*/
    Value = EEPROM_Read(Address);
    Current_Temp = Value;
}

/*////////////////////////////////////////////////////////////////////////////////////// */
/*Checks whether the cooler and heater start or not*/
/*////////////////////////////////////////////////////////////////////////////////////// */
static void WH_Cool_Heat(void)
{
  if(TempS_ReadDone() == 1)
  {
      if(TempS_AvgReadings() != Current_Temp)
      {
          /*Check if is it greater more than current temp by 5*/
          if(TempS_AvgReadings() >= Current_Temp+5)
          {
              if(TempS_AvgReadings() != Current_Temp)
              {
                  /*Turn on cooler*/
                  Heat_SetState(Heat_Res,HEAT_OFF);
                  Cool_SetState(COOL_FAN,COOL_ON);
              }
              else
              {
              }
          }
          /*Check if is it smaller than current temp by 5*/
          if(TempS_AvgReadings() <= Current_Temp - 5)
          {
              if( TempS_AvgReadings() != Current_Temp)
              {
                  /*Turn on heater*/
                  Heat_SetState(Heat_Res,HEAT_ON);
                  Cool_SetState(COOL_FAN,COOL_OFF);
              }
              else
              {
              }
          }
      }
      else
      {
          /*Turn off heater & cooler if Avg = current temp*/
          Heat_SetState(Heat_Res,HEAT_OFF);
          Cool_SetState(COOL_FAN,COOL_OFF);
      }
    /*Clear flag to make to make index of array of temperature readings zero*/
    TempS_CLRReadFlag();
  }
}

/*////////////////////////////////////////////////////////////////////////////////////// */
/*Check if any of increase or decrease buttons have been pressed*/
/*////////////////////////////////////////////////////////////////////////////////////// */
static void WH_CheckChange(void)
{
    tByte Setting_ClickedFlag = 0;

  if(WH_GetState() == WH_ON)
   {
     if(FirstClick == 0){
     if((SW_GetState(SW_PLUS) == SW_PRE_PRESSED)|| (SW_GetState(SW_MINUS) == SW_PRE_PRESSED))
     {
         FirstClick = 1;
         /*Enter setting mode*/
         Settings = WH_SETTING;
         /*counter of setting period is zero*/
         WH_Setting_Counter = 0;
         return;
     }
     }
    if(FirstClick == 1){
    if(SW_GetState(SW_PLUS) == SW_PRE_PRESSED)
    {
        /*Indicates that's setting mode*/
        Setting_ClickedFlag = 1;
        if (Current_Temp <= MAX_TEMP)
        {
            Current_Temp += TEMP_CHANGE_RATE;
            /*if it is greater than the max temp assign max temp to it*/
            if(Current_Temp > MAX_TEMP)
            {
                Current_Temp = MAX_TEMP;
            }
        }

    }
    if(SW_GetState(SW_MINUS) == SW_PRE_PRESSED)
    {
        /*Indicates that's setting mode*/
        Setting_ClickedFlag = 1;
        if (Current_Temp >= MIN_TEMP)
        {
            Current_Temp -= TEMP_CHANGE_RATE;
            /*If it is smaller than the min temp assign min temp to it*/
            if(Current_Temp < MIN_TEMP)
            {
                Current_Temp = MIN_TEMP;
            }
        }
    }
   }
   }
   /*If there is any button(INC/DEC) clicked enter settings mode and make counter of setting
     period is zero*/
   if(Setting_ClickedFlag == 1)
   {
       Settings = WH_SETTING;
       WH_Setting_Counter = 0;
   }
}

/*////////////////////////////////////////////////////////////////////////////////////// */
/*Checks whether the on-off switch clicked or not*/
/*////////////////////////////////////////////////////////////////////////////////////// */
static void WH_TurnON_OFF(void)
{
    if(SW_GetState(SW_ON_OFF) == SW_PRE_PRESSED)
    {
        if (WH_State == WH_ON)
        {
            WH_State = WH_OFF;
        }
        else
        {
            WH_State = WH_ON;
        }
    }
}

/*////////////////////////////////////////////////////////////////////////////////////// */
/*To check if it is the first time to run WH*/
/*////////////////////////////////////////////////////////////////////////////////////// */
static tByte WH_CheckFirstUse(void)
{
    /*Address in the EEPROM to save dummy value (1) as flag*/
    tWord Add = 0x0010;
    tByte True =1;
    tByte Temp = EEPROM_Read(Add);
    /*If it isn't the first time terminate*/
    if(Temp == True)
    {
        return 1;
    }
    else
    {
        /*IF it is the first time Set the flag*/
        EEPROM_Write(Add,True);
        return 0;
    }
}



/*////////////////////////////////////////////////////////////////////////////////////// */
/*Function to check if is it the first time to run WH if it is initialize temperature
  with default temperature if it isn't fetch last temperature*/
/*////////////////////////////////////////////////////////////////////////////////////// */
void WH_UsedTemp(void)
{
    if(WH_CheckFirstUse()==1)
    {
        WH_FetchLastTemp();
    }
    else
    {
        WH_Set_Temp(DEF_TEMP);
    }
}
