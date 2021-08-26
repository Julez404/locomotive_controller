# Locomotive Controller

Controller for a private model (1/8) locomotive.

## Description

The project uses a **Atmega328p** as it's microcontroller, the code is primarily written for this controller.Future adaptabiliy was taken into account, but wasn't the primary focus of the project.


## Pinning

## Input

* **L_*** => Analog Input 0V to 5V (None-Inverted logic)
* **Licht** => Enables light functionality
* **Licht_Auto** => Switch lights based on current moving direction.
* **Richtung** => Select travel direction

## Output

* **PWM_*** => PWM Output (50 Hz) T_*period* = 20ms, T_*min*=1ms (0%), T_*max*=2ms (100%)
* **Lights Front Drive** => Active when locomotive is moving forwards
* **Lights Reverse Drive** => Active when locomotive is moving backwards
