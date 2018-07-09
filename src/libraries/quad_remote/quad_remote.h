#ifndef QUAD_REMOTE_INCLUDED
#define QUAD_REMOTE_INCLUDED

/* quad_remote.h
 */
#include <Arduino.h>
#include <LiquidCrystal.h>
#include <RotaryEncoder.h>

// Pin definitions for Gimbals (Analog inputs).  It is not clear why the A1, A2,... etc. don't work, but they don't.
#define PIN_YAW		        A0
#define PIN_THROTTLE 	        A1 
#define PIN_ROLL	        A2 
#define	PIN_PITCH		A3  

extern LiquidCrystal lcd;

#define LCD_LED_RED 3
#define LCD_LED_GREEN 5  // these should be switch, but... board design error.
#define LCD_LED_BLUE 19

#define LED3 18

extern void quad_remote_setup();

extern RotaryEncoder knob1;
extern RotaryEncoder knob2;
extern RotaryEncoder knob3;

#define ENC1_BUTTON 20
#define ENC1_A 9
#define ENC1_B 8

#define ENC2_BUTTON 6
#define ENC2_A 34
#define ENC2_B 35

#define ENC3_BUTTON 7
#define ENC3_A 15
#define ENC3_B 14

#define BUTTON1 4
#define BUTTON2 21

#define LCD_RS 10
#define LCD_EN 2
#define LCD_D4 22
#define LCD_D5 23
#define LCD_D6 24
#define LCD_D7 25

#define BATTERY_SENSE A4
#define MIN_BATTERY (683.0) // calculated
#define MAX_BATTERY (817.0)


#define BUTTONS 11
#define GIMBAL_AXES 4

#define TOTAL_CHANNELS (BUTTONS + GIMBAL_AXES)

#define BUTTONS 11
#define GIMBAL_AXES 4

extern int foo;

extern void (*knobs_update_cb)();
extern void (*knob1_btn_cb)(bool);
extern void (*knob2_btn_cb)(bool);
extern void (*knob3_btn_cb)(bool);

extern void (*btn1_cb)(bool);
extern void (*btn2_cb)(bool);


#ifdef QUAD_REMOTE_TESTING

extern int numbers[TOTAL_CHANNELS+1];
extern char *labels[TOTAL_CHANNELS];
extern char pins[TOTAL_CHANNELS];
#endif

#endif
