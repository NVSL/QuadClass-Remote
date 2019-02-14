#include <radio.h>

#define QUAD_REMOTE_TESTING
#include <quad_remote.h>      // Header file with pin definitions and setup

uint8_t scale[8] = 
     {B00000000,
      B00000000,
      B00000000,
      B00000000,
      B00000000,
      B00000000,
      B00000000,
      B00000000};

void knobs_update();
void knobs_pressed();
void btn1_pressed(bool);
void btn2_pressed(bool);

void btn_up_pressed(bool down);
void btn_down_pressed(bool down);
void btn_left_pressed(bool down);
void btn_right_pressed(bool down);
void btn_center_pressed(bool down);

void setup() {

     const int RADIO_CHANNEL = 11;        // Channel for radio communications (can be 11-26)
     const int SERIAL_BAUD = 9600 ;        // Baud rate for serial port 
     Serial.begin(SERIAL_BAUD);           // Start up serial
     delay(100);
     quad_remote_setup();
     
     ADMUX_struct.refs = 3;
     ADCSRA_struct.aden = 0;
     ADCSRA_struct.aden = 1;
     delay(1000);

     Serial.println(ADCSRA);
     Serial.println(ADCSRB);
     Serial.println(ADMUX);
     
     
     for(char i = 0; i < 8; i++) {
	  scale[7-i] = B11111111;
	  lcd.createChar(i, scale);
	  delay(10);
     }

     rfBegin(RADIO_CHANNEL);              // Initialize ATmega128RFA1 radio on given channel

     knobs_update_cb = knobs_update;
     knob1_btn_cb = knob_pressed;
     btn1_cb = btn1_pressed;
     btn2_cb = btn2_pressed;
     btn_up_cb =  btn_up_pressed;
     btn_down_cb = btn_down_pressed;
     btn_left_cb =  btn_left_pressed;
     btn_right_cb = btn_right_pressed;
     btn_center_cb =  btn_center_pressed;
     knobs_update();
}


int last = 0;
unsigned char magic;

#define INFO_MODE 1
#define CONTROL_MODE 2

int mode = INFO_MODE;

void loop() {
  
     // Read analog values
     for(char i = 0; i < GIMBAL_AXES; i++) {
	  numbers[i] = analogRead(pins[i]); 
     }
  
     // Read btns
     for(char i = GIMBAL_AXES; i < TOTAL_CHANNELS; i++) {
	  numbers[i] = digitalRead(pins[i]) ? 1023 : 0; 
     }

     //update_display();
     
      for(char i= 0; i < TOTAL_CHANNELS;i++) {
	  Serial.print(numbers[i]);
	  Serial.print(" ");
	  }

	  Serial.println("\n");

     rfWrite((uint8_t*)numbers, sizeof(numbers));

     if (rfAvailable()) {  // If data receievd on radio...
	  digitalWrite(LED3, 1);
	  //delay(100);
	  rfRead(&magic, sizeof(magic));
	  numbers[TOTAL_CHANNELS] = magic;
	  digitalWrite(LED3, 0);
     } else {
	  digitalWrite(LED3, 0);
     }

     // This delay (or having one somewhere) is important.  If we send too
     // fast, the packets will run together on the receive side.
     delay(100);
     
     lcd.setCursor(12, 1);
     lcd.write(constrain(map(analogRead(PIN_THROTTLE),140,800,0,7), 0, 7));
     lcd.write(constrain(map(analogRead(PIN_YAW),140,800,0,7), 0 ,7));
     lcd.write(constrain(map(analogRead(PIN_PITCH),140,800,0,7), 0, 7));
     lcd.write(constrain(map(analogRead(PIN_ROLL),140,800,0,7), 0, 7));

}

void knobs_update() {
     unsigned char b = knob1.getCurrentPos() *  16;
     unsigned char r = 0;
     unsigned char g = 0;
     
     analogWrite(LCD_LED_RED, (unsigned char)(r));
     analogWrite(LCD_LED_GREEN, (unsigned char)(g));
     analogWrite(LCD_LED_BLUE, (unsigned char)(b));

     lcd.home();
     lcd.clear();
     lcd.print("R");
     lcd.print(r);
     lcd.setCursor(4,0);
     lcd.print(" G");
     lcd.print(g);
     lcd.setCursor(9,0);
     lcd.print(" B");
     lcd.print(b);
     lcd.setCursor(0,1);
     lcd.print("Bat: ");

     if (mode == INFO_MODE) {
	  lcd.print(map(analogRead(BATTERY_SENSE), MIN_BATTERY, MAX_BATTERY, 0, 100));
	  lcd.print("%");
     } else {
	  lcd.print(analogRead(BATTERY_SENSE));
     }
	  
     digitalWrite(LED1,!digitalRead(LED1));
     digitalWrite(LED2,!digitalRead(LED2));
     digitalWrite(LED3,!digitalRead(LED3));

     //Serial.println(knob1.getCurrentPos());
}


void btn1_pressed(bool down) {
	if(down) {
		Serial.println("btn1");
	}
	
	if (down) {
		Serial.println("changing modes");
		if (mode == INFO_MODE) {
			mode = CONTROL_MODE;
		} else {
			mode = INFO_MODE;
		}
		knobs_update();
	}
}

void btn2_pressed(bool down) {
	if(down) {
		Serial.println("btn2");
	}
}

void knob_pressed(bool down) {
	if(down) {
		Serial.println("knob");
		Serial.println(knob1.getCurrentPos());
	}
}


void btn_up_pressed(bool down) {
	if(down) {
		Serial.println("up");
	}
}

void btn_down_pressed(bool down) {
	if(down) {
		Serial.println("down");
	}
}

void btn_left_pressed(bool down) {
	if(down) {
		Serial.println("left");
	}
}

void btn_right_pressed(bool down) {
	if(down) {
		Serial.println("right");
	}
}

	
void btn_center_pressed(bool down) {
	if(down) {
		Serial.println("center");
	}
}
