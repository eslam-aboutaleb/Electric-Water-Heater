# Electric-Water-Heater
Electric water heater (my submission to ACT Swift internship challange) based on  PIC MCU 

                               Electric Water Heater

First to turn on the Water heater there is a button used as turn on/off, clicking on
the button turns on the water heater if it is off or turn off the water heater if it
is on.

The electric water heater temperature is initialized as 60 if it is the first time to
use the water heater there is a flag in EEPROM which indicates whether it is the first
time or not, if it is not the first time then the water heater fetches from another
Section in the EEPROM the last temperature has been used.

The default of the seven segments is showing the current temperature that's when the
water heater is in the normal mode.
To preview the setting temperature click one click on increase or decrease button to
enter the setting mode without changing the value until the next clicks.

If the user clicked Increase or decrease buttons the first click makes the user enters
the setting mode then the next clicks to adjust the temperature by increasing or dec-
-reasing it b 5.

If the Water heater in setting mode then the seven segments shall display the entered
value not the temperature.

To exit the setting mode don't click on any buttons for 5 seconds in these five seconds
the seven segments shall blink indicate the user in the setting mode.

After going back to normal mode the seven segments shall display the current temperature
again.

The water heater has temperature sensor measures the current temperature of the water
and it is responsible of turning cooler if the temperature more than the entered temper-
-ature by 5 or more or turning heater if the temperature less than entered temperature
by 5 or less.

If the heater is on the led shall blank every 1 second.

If the cooler is on the led shall turned continuously on.

If the cooler and heater are turned off the led is turned off (assumed).

The water heater has external EEPROM to save the last entered temperature.
