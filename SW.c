/* ////////////////////////////////////////////////////////////////////////////////////////////////////
Name: Eslam Aboutaleb
File: SW.c
Date: 4/7/2020
//////////////////////////////////////////////////////////////////////////////////////////////////// */
#include "Main.h"
#include "Port.h"
#include "Timer.h"
#include "SW.h"

/* SW_Update period */
#define SW_PERIOD_MS    (20)

/* Number of samples per SW */
#define N_SAMPLES       (2)


/* SW voltage level */
#define SW_PRESSED_LEVEL        (0)
#define SW_RELEASED_LEVEL       (1)


/* SW info: samples, state */
typedef struct
{
    tByte sw_samples[N_SAMPLES];
    tSW_State sw_state;
}tSW_Info;

/* Switches info */
static tSW_Info SWs_Info[N_SWITCHES];

/*////////////////////////////////////////////////////////////////////////////////////// */
/* Initializes the switches*/
/*////////////////////////////////////////////////////////////////////////////////////// */
void SW_Init(void)
{
    tByte index = 0;

    /* Initialize switches as inputs */
    GPIO_InitPortPin(SW_PLUS_PORT_CR, SW_PLUS_PIN, GPIO_IN);
    GPIO_InitPortPin(SW_MINUS_PORT_CR, SW_MINUS_PIN, GPIO_IN);
    GPIO_InitPortPin(SW_ON_OFF_PORT_CR, SW_ON_OFF_PIN, GPIO_IN);

    /* Initialize switches info */
    for (index = SW_PLUS; index < N_SWITCHES; index++)
    {
        /* Initialize switch samples */
        SWs_Info[index].sw_samples[0] = SW_RELEASED_LEVEL;
        SWs_Info[index].sw_samples[1] = SW_RELEASED_LEVEL;

        /* Initialize sw state */
        SWs_Info[index].sw_state = SW_RELEASED;

    }
}

/*////////////////////////////////////////////////////////////////////////////////////// */
/* Returns the state of the desired switch*/
/*////////////////////////////////////////////////////////////////////////////////////// */
tSW_State SW_GetState(tSW sw)
{
    /* return sw state */
    return SWs_Info[sw].sw_state;
}


/*////////////////////////////////////////////////////////////////////////////////////// */
/* Updates the state of all switches */
/*////////////////////////////////////////////////////////////////////////////////////// */
void SW_Update(void)
{
    static tWord SW_counter = 0;
    tByte index = 0;

    /* Check if it is time for the SW_Update to run */
    SW_counter += TMR_TICK_MS;

    if (SW_counter != SW_PERIOD_MS){
        return;
    }

    SW_counter = 0;

    /* Update switches states */
    for (index = SW_PLUS; index < N_SWITCHES; index++)
    {
        /* Update switch samples */
        SWs_Info[index].sw_samples[0] = SWs_Info[index].sw_samples[1];

        if (index == SW_PLUS)
        {
            SWs_Info[index].sw_samples[1] = GPIO_ReadPortPin(SW_PLUS_PORT_DR, SW_PLUS_PIN);
        }
        else if (index == SW_MINUS)
        {
            SWs_Info[index].sw_samples[1] = GPIO_ReadPortPin(SW_MINUS_PORT_DR, SW_MINUS_PIN);
        }
         else if (index == SW_ON_OFF)
        {
            SWs_Info[index].sw_samples[1] = GPIO_ReadPortPin(SW_ON_OFF_PORT_DR, SW_ON_OFF_PIN);
        }
        else
        {
            /* Do nothing should not be here !! */
        }

        /* Update switch state */
        switch(SWs_Info[index].sw_state)
        {

            case SW_RELEASED:
                /* Go to pre-pressed state if needed */
                if ((SWs_Info[index].sw_samples[0] == SW_PRESSED_LEVEL) &&
                    (SWs_Info[index].sw_samples[1] == SW_PRESSED_LEVEL))
                {
                    SWs_Info[index].sw_state = SW_PRE_PRESSED;
                } else
                {
                    /* Do nothing */
                }
                break;
            case SW_PRE_PRESSED:
                /* Go to pressed state if needed  */
                if (SWs_Info[index].sw_samples[1] == SW_PRESSED_LEVEL)
                {
                    SWs_Info[index].sw_state = SW_PRESSED;
                } else
                {
                    /* Do nothing */
                }
                break;
            case SW_PRESSED:
                /* Go to pre-released state if needed */
                if ((SWs_Info[index].sw_samples[0] == SW_RELEASED_LEVEL) &&
                    (SWs_Info[index].sw_samples[1] == SW_RELEASED_LEVEL))
                {
                    SWs_Info[index].sw_state = SW_PRE_RELEASED;
                }
                else
                {
                    /* Do nothing */
                }
                break;
            case SW_PRE_RELEASED:
                /* Go to released state if needed */
                if (SWs_Info[index].sw_samples[1] == SW_RELEASED_LEVEL)
                {
                    SWs_Info[index].sw_state = SW_RELEASED;
                } else
                {
                    /* Do nothing */
                }
                break;
            /* Should not be here */
            default:
                break;
        }
    }

}
