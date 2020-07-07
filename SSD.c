/* ////////////////////////////////////////////////////////////////////////////////////////////////////
Name: Eslam Aboutaleb
File: SSD.c
Date: 4/7/2020
//////////////////////////////////////////////////////////////////////////////////////////////////// */

#include "Main.h"
#include "Port.h"
#include "Timer.h"
#include "SSD.h"

/* SSD_Update period */
#define SSD_PERIOD_MS   (10)

/* Number of SSD symbols */
#define N_SSD_SYMBOLS   (11)


/* SSD Symbols port data values */
static tByte SSD_Data[N_SSD_SYMBOLS] =
{
    0b00111111,
    0b00000110,
    0b01011011,
    0b01001111,
    0b01100110,
    0b01101101,
    0b01111101,
    0b00000111,
    0b01111111,
    0b01101111,
    0b00000000,
};

/* Current SSD to be updated */
static tSSD SSD_current = SSD_TEMP_UNITS;

/* SSD values */
tSSD_Symbol SSD_Values[N_SSD] = {SSD_NULL};

static tByte SSD_DotState = SSD_OFF;

static void SSD_Out(tSSD ssd, tSSD_Symbol ssd_symbol);

/*////////////////////////////////////////////////////////////////////////////////////// */
/* Initializes the SSDs*/
/*////////////////////////////////////////////////////////////////////////////////////// */
void SSD_Init(tSSD ssd)
{
    /* Initialize SSD data pins */
    GPIO_InitPort(SSD_DATA_PORT_CR, GPIO_OUT);
    SSD_Out(ssd, SSD_NULL);

    /* Initialize SSD control pin and turn SSD OFF*/
    switch (ssd)
    {
        case SSD_TEMP_UNITS:
            GPIO_InitPortPin(SSD_TEMP_UNITS_CR, SSD_TEMP_UNITS_PIN, GPIO_OUT);
            break;
        case SSD_TEMP_TENS:
            GPIO_InitPortPin(SSD_TEMP_TENS_CR, SSD_TEMP_TENS_PIN, GPIO_OUT);
            break;
        /* Should not be here */
        default:
            break;
    }
    SSD_SetState(ssd, SSD_OFF);
}

/*////////////////////////////////////////////////////////////////////////////////////// */
/* Updates SSD*/
/*////////////////////////////////////////////////////////////////////////////////////// */
void SSD_Update(void)
{
    static tWord SSD_counter = 0;

    /* Check if it is time for the SSD_Update to run */
    SSD_counter += TMR_TICK_MS;

    if (SSD_counter != SSD_PERIOD_MS){
        return;
    }

    SSD_counter = 0;

    /* display current SSD value of the current SSD */
    SSD_Out(SSD_current, SSD_Values[SSD_current]);

    if (SSD_current == SSD_TEMP_TENS)
    {
        SSD_current = SSD_TEMP_UNITS;
    } else
    {
        SSD_current++;
    }
}

/*////////////////////////////////////////////////////////////////////////////////////// */
/* Returns the SSD current symbol*/
/*////////////////////////////////////////////////////////////////////////////////////// */
tSSD_Symbol SSD_GetValue(tSSD ssd)
{
    return SSD_Values[ssd];
}

/*////////////////////////////////////////////////////////////////////////////////////// */
/* Sets the symbol on the targeted SSD*/
/*////////////////////////////////////////////////////////////////////////////////////// */
void SSD_SetValue(tSSD ssd, tSSD_Symbol ssd_symbol)
{
    SSD_Values[ssd] = ssd_symbol;
}

/*////////////////////////////////////////////////////////////////////////////////////// */
/* Returns the state of the desired SSD*/
/*////////////////////////////////////////////////////////////////////////////////////// */
tSSD_State SSD_GetState(tSSD ssd)
{
    tSSD_State ret = SSD_OFF;
    switch (ssd)
    {
        case SSD_TEMP_UNITS:
            ret = GPIO_ReadPortPin(SSD_TEMP_UNITS_DR, SSD_TEMP_UNITS_PIN);
            break;
        case SSD_TEMP_TENS:
            ret = GPIO_ReadPortPin(SSD_TEMP_TENS_DR, SSD_TEMP_TENS_PIN);
            break;
        default:
            break;
    }
     return ret;

}

/*////////////////////////////////////////////////////////////////////////////////////// */
/* Sets the state of the targeted SSD*/
/*////////////////////////////////////////////////////////////////////////////////////// */
void SSD_SetState(tSSD ssd, tSSD_State state)
{
    switch (ssd)
    {
        case SSD_TEMP_UNITS:
            GPIO_WritePortPin(SSD_TEMP_UNITS_DR, SSD_TEMP_UNITS_PIN, state);
            break;
        case SSD_TEMP_TENS:
            GPIO_WritePortPin(SSD_TEMP_TENS_DR, SSD_TEMP_TENS_PIN, state);
            break;
        /* Should not be here */
        default:
            break;
    }
}


/*////////////////////////////////////////////////////////////////////////////////////// */
/* Prints the desired symbol on the targeted SSD*/
/*////////////////////////////////////////////////////////////////////////////////////// */
static void SSD_Out(tSSD ssd, tSSD_Symbol ssd_symbol)
{
    /* Turn off SSDs */
    SSD_SetState(SSD_TEMP_UNITS, SSD_OFF);
    SSD_SetState(SSD_TEMP_TENS, SSD_OFF);

    /* Output ssd_symbol on selected ssd */
    GPIO_WritePort(SSD_DATA_PORT_DR, SSD_Data[ssd_symbol]);

    /* Turn ssd ON */
    SSD_SetState(ssd, SSD_ON);

}

