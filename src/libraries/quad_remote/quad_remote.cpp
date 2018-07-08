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
    
     EICRA_struct.isc2 = 0x02; // These are falling edge interrupts for the buttons.
     EICRA_struct.isc3 = 0x02;
     EICRB_struct.isc4 = 0x02;
     EICRB_struct.isc6 = 0x02;
     EICRB_struct.isc7 = 0x02;
    
     EIMSK = 0b11011111;  // interrup 5 is disabled.

     PCICR = 1;  // enable pin-change interrupt 0
     PCMSK0 = 0b11110000;     // catch changes on all the pins for encoders 1 and 2

     lcd.clear();

     pinMode(ENC1_BUTTON, INPUT_PULLUP);
     pinMode(ENC2_BUTTON, INPUT_PULLUP);
     pinMode(ENC3_BUTTON, INPUT_PULLUP);

     pinMode(BUTTON1, INPUT_PULLUP);
     pinMode(BUTTON2, INPUT_PULLUP);

     pinMode(LCD_LED_RED, OUTPUT);
     pinMode(LCD_LED_GREEN, OUTPUT);
     pinMode(LCD_LED_BLUE, OUTPUT);

     pinMode(PIN_YAW,  INPUT);             // Gimbal: Yaw
     pinMode(PIN_THROTTLE, INPUT);        // Gimbal: throttle
     pinMode(PIN_ROLL, INPUT);            // Gimbal: roll
     pinMode(PIN_PITCH, INPUT);           // Gimbal: pitch

}

ISR(INT0_vect)
{  
     knob3.update();
}

ISR(INT1_vect)
{  
     knob3.update();
}

ISR(PCINT0_vect)
{  
     knob2.update();
     knob1.update();
}


ISR(INT2_vect)
{ 
     //     red_enable = !red_enable;
     Serial.println("E1-but pressed");
}

ISR(INT3_vect)
{  
     Serial.println("but2 pressed");
}

ISR(INT4_vect)
{  
     Serial.println("but1 pressed");
     Serial.print("battery level = ");
     Serial.println(analogRead(BATTERY_SENSE));
}

ISR(INT6_vect)
{  
     //     green_enable = !green_enable;
     Serial.println("E2-but pressed");
  
}

ISR(INT7_vect)
{  
     //blue_enable = !blue_enable;

     Serial.println("E3-but pressed");
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
