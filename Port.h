/* ////////////////////////////////////////////////////////////////////////////////////////////////////
Name: Eslam Aboutaleb
File: Port.h
Date: 4/7/2020
//////////////////////////////////////////////////////////////////////////////////////////////////// */
#ifndef __PORT_H__
#define __PORT_H__

#include "Main.h"


/* Leds' pins */
#define LED_1_PORT_DR          (GPIO_PORTB_DATA)
#define LED_1_PORT_CR          (GPIO_PORTB_CONTROL)
#define LED_1_PIN              (GPIO_PIN_7)


/* Switches */
#define SW_PLUS_PORT_DR        (GPIO_PORTB_DATA)
#define SW_PLUS_PORT_CR        (GPIO_PORTB_CONTROL)
#define SW_PLUS_PIN            (GPIO_PIN_2)

#define SW_MINUS_PORT_DR       (GPIO_PORTB_DATA)
#define SW_MINUS_PORT_CR       (GPIO_PORTB_CONTROL)
#define SW_MINUS_PIN           (GPIO_PIN_1)

#define SW_ON_OFF_PORT_DR      (GPIO_PORTB_DATA)
#define SW_ON_OFF_PORT_CR      (GPIO_PORTB_CONTROL)
#define SW_ON_OFF_PIN          (GPIO_PIN_0)

/* SSD */
#define SSD_DATA_PORT_DR        (GPIO_PORTD_DATA)
#define SSD_DATA_PORT_CR        (GPIO_PORTD_CONTROL)

#define SSD_TEMP_TENS_DR       (GPIO_PORTA_DATA)
#define SSD_TEMP_TENS_CR       (GPIO_PORTA_CONTROL)
#define SSD_TEMP_TENS_PIN      (GPIO_PIN_4)

#define SSD_TEMP_UNITS_DR      (GPIO_PORTA_DATA)
#define SSD_TEMP_UNITS_CR      (GPIO_PORTA_CONTROL)
#define SSD_TEMP_UNITS_PIN     (GPIO_PIN_5)

/*Cooling element*/
#define COOL_DATA_PORT         (GPIO_PORTC_DATA)
#define COOL_CONTROL_PORT      (GPIO_PORTC_CONTROL)
#define COOL_PIN               (GPIO_PIN_2)

/*Heating element*/
#define HEAT_DATA_PORT         (GPIO_PORTC_DATA)
#define HEAT_CONTROL_PORT      (GPIO_PORTC_CONTROL)
#define HEAT_PIN               (GPIO_PIN_5)

/* LCD */
#define LCD_DATA_PORT_DR    (GPIO_PORTD_DATA)
#define LCD_DATA_PORT_CR    (GPIO_PORTD_CONTROL)

#define LCD_RS_DR           (GPIO_PORTE_DATA)
#define LCD_RS_CR           (GPIO_PORTE_CONTROL)
#define LCD_RS_PIN          (GPIO_PIN_2)

#define LCD_E_DR           (GPIO_PORTE_DATA)
#define LCD_E_CR           (GPIO_PORTE_CONTROL)
#define LCD_E_PIN          (GPIO_PIN_1)


#endif // __PORT_H__
