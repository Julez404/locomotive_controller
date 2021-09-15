# Locomotive Controller

Controller for a private model (1/8) locomotive.

## Description

The project uses a **Atmega328p** as it's microcontroller, the code is primarily written for this controller. Future adaptabiliy was taken into account, but wasn't the primary focus of the project.


## Pinning and Functions

| **Pin**   | **PORTB**  | **PORTC**    | **PORTD** |
| ---       |  ---       | ---          | ---       |
| 0 | Richtung-AVR  | L-Gas     | Umschalt-B    |
| 1 | PWM-Laut      | L-Bremse  | Richtung      |
| 2 | PWM-Bremse    | L-Laut    | Licht         |
| 3 | PWM-Gas (MOSI)| L-Spare   | Licht-Auto    |
| 4 | Rück1 (MISO)  | Licht-A1  | *--WAGEN_V--* |
| 5 | Licht1 (SCK)  | Licht-A2  | PWM-Spare     | 
| 6 | *QUARZ1*      | *RESET*   | *--WAGEN_H-*  |
| 7 | *QUARZ2*      |           | B-Gas         |


### Input Functions

Description of input function.

| Input (PCB) | Input (SW) | Function |
| --- | --- | --- |
| Umschalt-B | ControlSource | Switch between local or remote control (0=remote, 1=local). Locked by the current speed source (B-Gas or L-Gas <4%). |
| B-Gas | TBD | Speed information from the remote control, mapped to PWM-Gas. (Input is a PWM-Signal) |
| L-Gas | TBD | Analog value to transform onto PWM-Gas |
| L-Bremse | TBD | Analog value to transform onto PWM-Bremse |
| L-Laut | TBD | Analog value to transform onto PWM-Laut |
| L-Spare | TBD | Analog value to transform onto PWM-Spare |
| Richtung | DirectionSelection | Select travel direction (0=Forwards, 1=Backwards) |
| Licht | LightsMain | Main switch to enable lights |
| Licht-Auto | LightsAutomatic | Select if lights switch automatically (0=Selected by Licht-A1/A2), 1=switch based on travel) |
| Licht-A1 | LightsOn | Turn on lights in forward direction (Hardware locked with Licht-A2) |
| Licht-A2 | NOT USED | Turn on lights in reverse direction (Hardware locked with Licht-A1) |

#### L-* Input Info

Inputs are analog and are utilisation is linear mapped to the current voltage.
0V=0%, 5V=100%

### Output Functions

| Output (PCB) | Output (SW) | Function |
| --- | ---| ---|
| PWM-Gas | PWM_Gas | Send speed to motor |
| PWM-Bremse | PWM_Break | Control breaking |
| PWM-Laut | PWM_Horn | What does this do? Sound? |
| PWM-Spare | NOT USED | Spare port for future use |
| Richtung-AVR | DirectionControl | Select the travel direction, value change only possible when current Speed source is <4% |
| Licht1 | LightsFront | Turn on all lights for forward travel |
| Rück1 | LightsRear | Turn on all lights for reverse travel |

#### PWM Output Info

**Frequency** = 50Hz (T_*p*=20ms)
**Min Value** = T_*min*= 1ms (0%)
**Max Value** = T_*max*= 2ms (100%)

## Additional Notes

* In remote mode (Umschalt-B=1) L-Bremse, L-Laut, L-Spare and the corrosponding PWM Outputs are not used.
* Change in direction is locked by the current speed source (B-GAS or L-Gas). Change will only take effect when Speed os below 4% utilization.

## Open Question

* If Umschalt-B is high (remote mode) do the PWM outputs need to change state to *input* to avoid problems with external voltages?
* What does PWM-Laut do?
