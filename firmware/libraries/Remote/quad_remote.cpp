#include "quad_remote.h"


//#include <SoftwareSerial2.h>

//SoftwareSerial lcdSerial(LCD_TX, LCD_RX);

//SerLCD lcd;

RotaryEncoder knob1(ENC1_A, ENC1_B);

void quad_remote_setup() {
	knob1.setup();

	EICRA_struct.isc0 = 0x01; // Any direction interrupts for encoder 3
	EICRA_struct.isc1 = 0x01;

	EICRA_struct.isc2 = 0x01;
	EICRA_struct.isc3 = 0x01;
	EICRB_struct.isc4 = 0x01;
	EICRB_struct.isc5 = 0x01;
	EICRB_struct.isc6 = 0x01;
	EICRB_struct.isc7 = 0x01;
    
	EIMSK = 0b11111111;
     
	PCICR = 1;  // enable pin-change interrupt 0
	PCMSK0 = 0b00110000;     // catch changes on all the pins for encoders 1 and 2
	/*lcdSerial.begin(9600);
	  lcd.begin(lcdSerial);
	  lcd.clear();
	  lcd.home();*/

	/*     ADMUX_struct.refs = 3;
	       ADCSRA_struct.aden = 0;
	       ADCSRA_struct.aden = 1;
	       delay(1000);

	       Serial.println(ADCSRA);
	       Serial.println(ADCSRB);
	       Serial.println(ADMUX); */
     
	pinMode(ENC1_BUTTON, INPUT_PULLUP);

	pinMode(BUTTON1, INPUT_PULLUP);
	pinMode(BUTTON2, INPUT_PULLUP);

	pinMode(BUTTON_UP, INPUT_PULLUP);
	pinMode(BUTTON_DOWN, INPUT_PULLUP);
	pinMode(BUTTON_LEFT, INPUT_PULLUP);
	pinMode(BUTTON_RIGHT, INPUT_PULLUP);
	pinMode(BUTTON_CENTER, INPUT_PULLUP);

	pinMode(analogInputToDigitalPin(PIN_YAW),  INPUT);            // Gimbal: Yaw
	pinMode(analogInputToDigitalPin(PIN_THROTTLE), INPUT);        // Gimbal: throttle
	pinMode(analogInputToDigitalPin(PIN_ROLL), INPUT);            // Gimbal: roll
	pinMode(analogInputToDigitalPin(PIN_PITCH), INPUT);           // Gimbal: pitch
     
	pinMode(analogInputToDigitalPin(BATTERY_SENSE), INPUT);
}

bool is_pressed(int button)
{
	return ! digitalRead(button);
}

void nop() {
}

void nop_btn(bool) {
}

void (*knobs_update_cb)() = nop;
void (*knob1_btn_cb)(bool) = nop_btn;

void (*btn1_cb)(bool) = nop_btn;
void (*btn2_cb)(bool) = nop_btn;

void (*btn_up_cb)(bool) = nop_btn;   
void (*btn_down_cb)(bool) = nop_btn;
void (*btn_left_cb)(bool) = nop_btn;
void (*btn_right_cb)(bool) = nop_btn;
void (*btn_center_cb)(bool) = nop_btn;


ISR(PCINT0_vect)
{  
	knob1.update();
	knobs_update_cb();
}


#define BUTTON_INTERRUPT(vector, cb, pin)	\
	ISR(vector)				\
	{					\
		cb(!digitalRead(pin));		\
	}

BUTTON_INTERRUPT(INT2_vect, knob1_btn_cb, ENC1_BUTTON);

BUTTON_INTERRUPT(INT1_vect, btn2_cb, BUTTON2);
BUTTON_INTERRUPT(INT0_vect, btn1_cb, BUTTON1);

BUTTON_INTERRUPT(INT4_vect, btn_up_cb, BUTTON_UP);
BUTTON_INTERRUPT(INT3_vect, btn_down_cb, BUTTON_DOWN);
BUTTON_INTERRUPT(INT5_vect, btn_left_cb, BUTTON_LEFT);
BUTTON_INTERRUPT(INT7_vect, btn_right_cb, BUTTON_RIGHT);
BUTTON_INTERRUPT(INT6_vect, btn_center_cb, BUTTON_CENTER);


int numbers[TOTAL_CHANNELS+1];

char *labels[TOTAL_CHANNELS] = {"T ", "Y ", "P ", "R ", 
				"E1A", "E1B",
				"E1B", 
				"B1", "B2",
				"UP",
				"DOWN",
				"LEFT",
				"RIGHT",
				"CENTER"};

char pins[TOTAL_CHANNELS] = {PIN_THROTTLE, PIN_YAW, PIN_PITCH, PIN_ROLL, 
			     ENC1_A, ENC1_B,
			     ENC1_BUTTON, 
			     BUTTON1, BUTTON2,
			     BUTTON_UP,
			     BUTTON_DOWN,
			     BUTTON_LEFT,
			     BUTTON_RIGHT,
			     BUTTON_CENTER};
