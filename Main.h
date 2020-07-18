/* ////////////////////////////////////////////////////////////////////////////////////////////////////
Name: Eslam Aboutaleb
File: main.h
Date: 4/7/2020
//////////////////////////////////////////////////////////////////////////////////////////////////// */
#ifndef __MAIN_H__
#define __MAIN_H__

#include <pic16f877a.h>
#include <stdio.h>
#include <stdlib.h>

/*MCU Clock*/
#define _XTAL_FREQ 8000000

/* GPIO definitions */
/* GPIO Pins */
#define GPIO_PIN_0              (0)
#define GPIO_PIN_1              (1)
#define GPIO_PIN_2              (2)
#define GPIO_PIN_3              (3)
#define GPIO_PIN_4              (4)
#define GPIO_PIN_5              (5)
#define GPIO_PIN_6              (6)
#define GPIO_PIN_7              (7)

/* GPIO Port Registers redefinition */
#define GPIO_PORTA_DATA         (PORTA)
#define GPIO_PORTA_CONTROL      (TRISA)

#define GPIO_PORTB_DATA         (PORTB)
#define GPIO_PORTB_CONTROL      (TRISB)

#define GPIO_PORTC_DATA         (PORTC)
#define GPIO_PORTC_CONTROL      (TRISC)

#define GPIO_PORTD_DATA         (PORTD)
#define GPIO_PORTD_CONTROL      (TRISD)

#define GPIO_PORTE_DATA         (PORTE)
#define GPIO_PORTE_CONTROL      (TRISE)

/* GPIO direction setting */
#define GPIO_OUT                (0)
#define GPIO_IN                 (1)

/* GPIO level setting */
#define GPIO_LOW                (0)
#define GPIO_HIGH               (1)

/* GPIO port operations */
#define GPIO_InitPort(CONTROL, DIRECTION)   ((CONTROL) = (DIRECTION)?(~GPIO_OUT):(GPIO_OUT))
#define GPIO_WritePort(PORT, DATA)          ((PORT) = (DATA))
#define GPIO_ReadPort(PORT)                 (PORT)

/* GPIO port pin operations */
#define GPIO_InitPortPin(CONTROL, PIN, DIRECTION)   ((CONTROL) = (CONTROL & (~(1 << PIN)))|(DIRECTION << PIN))
#define GPIO_WritePortPin(PORT, PIN, DATA)          ((PORT) = (PORT & (~(1 << PIN)))|(DATA << PIN))
#define GPIO_TogPortPin(PORT, PIN)                  ((PORT) ^= (1<<PIN))
#define GPIO_ReadPortPin(PORT, PIN)                 (((PORT) & (1 << PIN)) >> (PIN))

/* Timer 0 macros */

#define TMR_SET_PRESCALER_256	PS2 = 1;\
								PS1 = 1;\
								PS0 = 1;\
								PSA = 0

#define TMR_GET_FLAG			(TMR0IF)
#define TMR_CLEAR_FLAG			(TMR0IF = 0)

#define TMR_UPDATE_REGISTER(TIME)		(TMR0 = 256 - ((TIME) * 8))

#define TMR_ENABLE_INTERRUPT	(TMR0IE = 1)
#define GLOBAL_INTERRUPT_ENABLE	(GIE = 1)

#define TMR_ENABLE_CLOCK		(T0CS = 0)
#define TMR_DISABLE_CLOCK		(T0CS = 1)


/*Timer 2 macros*/
#define TMR_DELAY_SET_PRESCALER_16       T2CKPS1=1;\
                                         T2CKPS0=0

#define TMR_DELAY_START                 (TMR2ON = 1)
#define TMR_DELAY_DISABLE               (TMR2ON = 0)
#define TMR_DELAY_GET_FLAG		        (TMR2IF    )
#define TMR_DELAY_CLEAR_FLAG		    (TMR2IF = 0)
#define TMR_DELAY_ENABLE_INTERRUPT	    (TMR2IE = 1)
#define TMR_DELAY_DISABLE_INTERRUPT  	(TMR2IE = 0)
#define TMR_DELAY_REG_VAL(T)            (TMR2   = T)
#define TMR_DELAY_UPDATE_REG_VAL(T)     (TMR2   = T)

/* ADC macros */
#define ADC_FOSC_BY_2   (0)
#define ADC_FOSC_BY_8   (1)
#define ADC_FOSC_BY_32  (2)
#define ADC_FRC_L       (3)
#define ADC_FOSC_BY_4   (4)
#define ADC_FOSC_BY_16  (5)
#define ADC_FOSC_BY_64  (6)
#define ADC_FRC_H       (7)

/* Fill missing parts below */
#define ADC_ADJUST_RESULT_LEFT      (0)
#define ADC_ADJUST_RESULT_RIGHT     (1)

#define ADC_OFF (ADON = 0)
#define ADC_ON  (ADON = 1)

#define ADC_SELECT_CLOCK(clock) (ADCS2 = ((clock) & 0x4 ) >> 2);\
                                (ADCS1 = ((clock) & 0x2 ) >> 1);\
                                (ADCS0 = (clock) & 0x1)

#define ADC_CONFIGURE_PORT      PCFG3 = 1;\
                                PCFG2 = 0;\
                                PCFG1 = 1;\
                                PCFG0 = 0

#define ADC_ADJUST_RESULT(adjustment)   (ADFM = adjustment)

#define ADC_SELECT_CHANNEL(channel)     (CHS2 = ((channel & 0x4) >> 2));\
                                        (CHS1 = ((channel & 0x2) >> 1));\
                                        (CHS0 = (channel & 0x1))


#define ADC_START_CONVERSION    (GO = 1)
#define ADC_WAIT_FOR_RESULT     while(GO == 1)
#define ADC_READ_RESULT(adjustment) (adjustment)?((((tWord)ADRESH)<<8)|(ADRESL)):((((tWord)ADRESH)<<2)|(ADRESL>>6))


/*I2C Macros*/
#define CHECK_I2C_BUSY_WAIT()            while ((SSPSTAT & 0x04) || (SSPCON2 & 0x1F))
#define I2C_SEND_ACK()                   ACKDT = 0;\
                                         ACKEN = 1 /* Send ACK Signal*/

 #define I2C_SEND_NACK()                 ACKDT = 1;\
                                         ACKEN = 1 /* Send NACK Signal*/
 #define I2C_EN_RECV()                   RCEN = 1

#define I2C_CLEAR_INTERRUPT()            SSPIF = 0
/* Standard data types */
typedef unsigned char tByte;
typedef unsigned int tWord;
typedef unsigned long tWord32;

#endif // __MAIN_H__
