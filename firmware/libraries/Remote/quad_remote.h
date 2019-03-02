#ifndef QUAD_REMOTE_INCLUDED
#define QUAD_REMOTE_INCLUDED

/* quad_remote.h
 */
#include <Arduino.h>
#include <RotaryEncoder.h>
#include <SerLCD.h>

// Pin definitions for Gimbals (Analog inputs).  It is not clear why the A1, A2,... etc. don't work, but they don't.
#define PIN_YAW		        A0
#define PIN_THROTTLE 	        A1 
#define PIN_ROLL	        A2 
#define	PIN_PITCH		A3  

#define LED3 18

extern void quad_remote_setup();

extern RotaryEncoder knob1;
extern SerLCD lcd;

#define ENC1_BUTTON 20
#define ENC1_A 9
#define ENC1_B 8

// If you changes these, you need to change the interrupt assigments in .cpp
#define BUTTON1 15
#define BUTTON2 14

#define BUTTON_UP 4
#define BUTTON_DOWN 21 
#define BUTTON_LEFT 5
#define BUTTON_RIGHT 7
#define BUTTON_CENTER 6

#define LCD_RX 25
#define LCD_TX 24

#define BATTERY_SENSE A4
#define MIN_BATTERY (775.0) // calculated
#define MAX_BATTERY (928.0)
//#define MIN_BATTERY (683.0) // calculated
//#define MAX_BATTERY (817.0)


#define BUTTONS 10
#define GIMBAL_AXES 4

#define TOTAL_CHANNELS (BUTTONS + GIMBAL_AXES)

extern int foo;

extern void (*knobs_update_cb)();
extern void (*knob1_btn_cb)(bool);

extern void (*btn1_cb)(bool);
extern void (*btn2_cb)(bool);

extern void (*btn_up_cb)(bool);
extern void (*btn_down_cb)(bool);
extern void (*btn_left_cb)(bool);
extern void (*btn_right_cb)(bool);
extern void (*btn_center_cb)(bool);

#ifdef QUAD_REMOTE_TESTING

extern int numbers[TOTAL_CHANNELS+1];
extern char *labels[TOTAL_CHANNELS];
extern char pins[TOTAL_CHANNELS];
#endif

#endif
