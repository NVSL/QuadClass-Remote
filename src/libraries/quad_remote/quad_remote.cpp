#include "quad_remote.h"


LiquidCrystal lcd(LCD_RS, LCD_EN, LCD_D4, LCD_D5, LCD_D6, LCD_D7);

RotaryEncoder knob1(ENC1_A, ENC1_B);
RotaryEncoder knob2(ENC2_A, ENC2_B);
RotaryEncoder knob3(ENC3_A, ENC3_B);

void quad_remote_setup() {
     knob1.setup();
     knob2.setup();
     knob3.setup();
    
     EICRA_struct.isc0 = 0x01; // Any direction interrupts for encoder 3
     EICRA_struct.isc1 = 0x01;

     EICRA_struct.isc2 = 0x01; // Report rising and falling edges for buttons
     EICRA_struct.isc3 = 0x01;
     EICRB_struct.isc4 = 0x01;
     EICRB_struct.isc6 = 0x01;
     EICRB_struct.isc7 = 0x01;
    
     EIMSK = 0b11011111;  // interrup 5 is disabled.

     PCICR = 1;  // enable pin-change interrupt 0
     PCMSK0 = 0b11110000;     // catch changes on all the pins for encoders 1 and 2

     lcd.begin(16, 2);
     lcd.clear();
     lcd.home();

     pinMode(ENC1_BUTTON, INPUT_PULLUP);
     pinMode(ENC2_BUTTON, INPUT_PULLUP);
     pinMode(ENC3_BUTTON, INPUT_PULLUP);

     pinMode(BUTTON1, INPUT_PULLUP);
     pinMode(BUTTON2, INPUT_PULLUP);

     pinMode(LCD_LED_RED, OUTPUT);

     pinMode(LCD_LED_GREEN, OUTPUT);
     pinMode(LCD_LED_BLUE, OUTPUT);

     pinMode(analogInputToDigitalPin(PIN_YAW),  INPUT);            // Gimbal: Yaw
     pinMode(analogInputToDigitalPin(PIN_THROTTLE), INPUT);        // Gimbal: throttle
     pinMode(analogInputToDigitalPin(PIN_ROLL), INPUT);            // Gimbal: roll
     pinMode(analogInputToDigitalPin(PIN_PITCH), INPUT);           // Gimbal: pitch
     
     pinMode(analogInputToDigitalPin(BATTERY_SENSE), INPUT);


}

void nop() {
}
void nop_btn(bool) {
}

void (*knobs_update_cb)() = nop;
void (*knob1_btn_cb)(bool) = nop_btn;
void (*knob2_btn_cb)(bool) = nop_btn;
void (*knob3_btn_cb)(bool) = nop_btn;

void (*btn1_cb)(bool) = nop_btn;
void (*btn2_cb)(bool) = nop_btn;


ISR(INT0_vect)
{  
     knob3.update();
     knobs_update_cb();
}

ISR(INT1_vect)
{  
     knob3.update();
     knobs_update_cb();
}

ISR(PCINT0_vect)
{  
     knob2.update();
     knob1.update();
     knobs_update_cb();
}

ISR(INT2_vect)
{ 
     knob1_btn_cb(digitalRead(ENC1_BUTTON));
}

ISR(INT6_vect)
{  
     knob2_btn_cb(digitalRead(ENC2_BUTTON));  
}

ISR(INT7_vect)
{  
     knob3_btn_cb(digitalRead(ENC3_BUTTON));
}

ISR(INT3_vect)
{  
     btn2_cb(digitalRead(BUTTON2));
}

ISR(INT4_vect)
{  
     btn1_cb(digitalRead(BUTTON1));
}



#define BUTTONS 11
#define GIMBAL_AXES 4

#define TOTAL_CHANNELS (BUTTONS + GIMBAL_AXES)
int numbers[TOTAL_CHANNELS+1];

char *labels[TOTAL_CHANNELS] = {"T ", "Y ", "P ", "R ", 
				"E1A", "E1B",
				"E2A", "E2B",
				"E3A", "E3B",
				"E1Bu", "E2Bu", "E3Bu", 
				"B1", "B2"};

char pins[TOTAL_CHANNELS] = {PIN_THROTTLE, PIN_YAW, PIN_PITCH, PIN_ROLL, 
			     ENC1_A, ENC1_B,
			     ENC2_A, ENC2_B,
			     ENC3_A, ENC3_B,
			     ENC1_BUTTON, ENC2_BUTTON, ENC3_BUTTON, 
			     BUTTON1, BUTTON2};
