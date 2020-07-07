/* ////////////////////////////////////////////////////////////////////////////////////////////////////
Name: Eslam Aboutaleb
File: Display.c
Date: 4/7/2020
//////////////////////////////////////////////////////////////////////////////////////////////////// */
#include "Main.h"
#include "SSD.h"
#include "Timer.h"
#include "Display.h"
#include "SW.h"
#include "Led.h"
#include "Heating_element.h"
#include "Cooling_element.h"
#include "WH.h"
#include "TempSensor.h"

/* SSD_Update period */
#define DISP_PERIOD_MS   (10)
#define DISP_BLNK_MS (1000)

/*Local functions prototypes*/
static void Disp_ToggleSSD(void);
static void DISP_Blink(void);
static void Disp_PrintTemp(void);
static void Disp_ElementsLED(void);
/*Extern global value which indicates current setting mode*/
extern tWH_Settings Settings;
/*SSD state*/
static tSSD_State SSD_State = SSD_OFF;


/* /////////////////////////////////////////////////////////////////////////////////
Func: DISP_Init
Parameters: void
Return: void
job: initializes elements led and SSDs which indicate the current temp or settings
temp
///////////////////////////////////////////////////////////////////////////////// */
void DISP_Init(void)
{
        /*Initialize Seven segments*/
        SSD_Init(SSD_TEMP_UNITS);
        SSD_Init(SSD_TEMP_TENS);
        /*First initial value is 0*/
        SSD_SetValue(SSD_TEMP_UNITS, SSD_0);
        SSD_SetValue(SSD_TEMP_TENS,SSD_0);
        /*initialize elements led*/
        LED_Init(LED_1,LED_OFF);
}


/* /////////////////////////////////////////////////////////////////////////////////
Func: DISP_Update
Parameters: void
Job: Printing the current temp or setting temp based on WH module
///////////////////////////////////////////////////////////////////////////////// */
void DISP_Update(void)
{
    static tWord DISP_counter = 0;
    static tWord DISP_Blink_Counter=0;
    /* Check if it is time for the DISP_Update to run */
    DISP_counter += TMR_TICK_MS;

    if(DISP_counter != DISP_PERIOD_MS)
    {
        return;
    }
    DISP_counter = 0;
    Disp_ElementsLED();
    if(Settings == WH_NORMAL){
    Disp_PrintTemp();
    return;
    }
    else{
    DISP_Blink_Counter += DISP_PERIOD_MS;
    if(DISP_Blink_Counter != DISP_BLNK_MS)
    {
        return;
    }
    DISP_Blink_Counter=0;

    Disp_ToggleSSD();
    DISP_Blink();
    }
}

/*////////////////////////////////////////////////////////////////////////////////////// */
/*Toggles the SSDs*/
/*////////////////////////////////////////////////////////////////////////////////////// */
static void DISP_Blink(void)
{
    /* Toggle the SSD if there is any of SSDs is on or off*/
    if(SSD_State == SSD_ON)
    {

        Disp_PrintTemp();
    }
    else
    {
        SSD_SetValue(SSD_TEMP_UNITS, SSD_NULL);
        SSD_SetValue(SSD_TEMP_TENS,SSD_NULL);
    }
}

/*////////////////////////////////////////////////////////////////////////////////////// */
/*Changes the state of the SSDs*/
/*////////////////////////////////////////////////////////////////////////////////////// */
static void Disp_ToggleSSD(void)
{
    if(SSD_State == SSD_OFF)
    {
        SSD_State=SSD_ON;
    }
    else
    {
        SSD_State=SSD_OFF;
    }
}

/*////////////////////////////////////////////////////////////////////////////////////// */
/*Check the cooler and the heater and do actions depending on their states*/
/*////////////////////////////////////////////////////////////////////////////////////// */
static void Disp_ElementsLED(void)
{
    static tWord HeatCounter=0;
    /*If the heater is on toggle the Led every 1 second*/
    if(Heat_GetState(Heat_Res)==HEAT_ON)
    {
        HeatCounter+=DISP_PERIOD_MS;
        if(HeatCounter != DISP_BLNK_MS)
        {
            return;
        }
        HeatCounter = 0;
        LED_Toggle(LED_1);
    }
    /*If the cooler is on turn on the led continuously*/
    else if(Cool_GetState(COOL_FAN) == COOL_ON)
    {
        LED_SetState(LED_1,LED_ON);
    }
    /*If the cooler and the fan are off turn off the led*/
    else if (Cool_GetState(COOL_FAN) == COOL_OFF && Heat_GetState(Heat_Res)==HEAT_OFF)
    {
        LED_SetState(LED_1,LED_OFF);
    }
}

/*////////////////////////////////////////////////////////////////////////////////////// */
/* Decides whether the SSDs print current temperature or the setting temperature depending
   on the water heater setting state*/
/*////////////////////////////////////////////////////////////////////////////////////// */
static void Disp_PrintTemp(void)
{
    tWord Temp=0;
    tByte rem;
    tByte FirstSSD=0;
    /*If the water heater is in the setting mode print the Setting temperature*/
    if(Settings == WH_NORMAL){
        Temp = TempS_GetTemp();
    }
    /*If the water heater is in the normal mode print the current temperature*/
    else if(Settings == WH_SETTING){
        Temp = WH_GetTemp();
    }

    /*Divide the digits of temp variable and print them on SSDs*/
    while(Temp>0)
    {
        rem=Temp%10;
        if(FirstSSD == 0){
        SSD_SetValue(SSD_TEMP_UNITS, rem);
        FirstSSD = 1;
        }
        else
        {
            SSD_SetValue(SSD_TEMP_TENS, rem);
        }
        Temp/=10;
    }
}
