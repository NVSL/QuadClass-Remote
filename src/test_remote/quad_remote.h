/* quad_remote.h
 * Provides pin defn's and setup for ATmega128RFA1.
 * Components:
 * 		Gimbal
 * 		Potentiometers (POT1 and POT2)
 * 		Buttons
 * 		Indicator LEDs
 */

#include <Arduino.h>

// Pin definitions for Gimbals (Analog inputs)
#define PIN_YAW			A0
#define PIN_THROTTLE 	A1
#define PIN_ROLL		A2
#define	PIN_PITCH		A3 

// Pin definitions for potentiometers (Analog inputs)
#define PIN_POT1		A6
#define PIN_POT2		A7

// Pin definitions for digital pins (buttons and indicator LEDs)
#define PIN_BTN1		16		// PG0 (schematic) G0 (red board)
#define PIN_BTN2		17		// PG1 (schematic) G1 (red board)
#define PIN_LED_BLUE	22		// PD6 (schematic) D4 (red board)
#define PIN_LED_GRN		23		// PD5 (schematic) D5 (red board)
#define PIN_LED_RED		24		// PD4 (schematic) D6 (red board)		
