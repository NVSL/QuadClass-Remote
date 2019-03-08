
#include <radio.h>

#define QUAD_REMOTE_TESTING
#include <quad_remote.h>      // Header file with pin definitions and setup

void knobs_update();
void knob_pressed(bool);
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

     rfBegin(RADIO_CHANNEL);              // Initialize ATmega128RFA1 radio on given channel

     // The buttons and the knob trigger these call backs.  
     
     knobs_update_cb = knobs_update; 
     knob1_btn_cb = knob_pressed;
     btn1_cb = btn1_pressed;
     btn2_cb = btn2_pressed;
     btn_up_cb =  btn_up_pressed;
     btn_down_cb = btn_down_pressed;
     btn_left_cb =  btn_left_pressed;
     btn_right_cb = btn_right_pressed;
     btn_center_cb =  btn_center_pressed;
     
     knobs_update(); // Initialize the knob

    
    lcd.setBacklight(255, 255, 0); 
    lcd.setContrast(5); //Set contrast. Lower to 0 for higher contrast.
  
    lcd.clear(); //Clear the display - this moves the cursor to home position as well
    lcd.print("Hello, World!");
    
}


int last = 0;
unsigned char magic;

#define INFO_MODE 1
#define CONTROL_MODE 2

int mode = INFO_MODE;

void loop() {
  
     // Read analog values
     // The pins array holds the arduino pin numbers for all the inputs.
     for(char i = 0; i < GIMBAL_AXES; i++) {
	      numbers[i] = analogRead(pins[i]); 
     }
  
     // Read btns
     for(char i = GIMBAL_AXES; i < TOTAL_CHANNELS; i++) {
	      numbers[i] = digitalRead(pins[i]) ? 1023 : 0; 
     }

    for(char i= 0; i < TOTAL_CHANNELS;i++) {
	      Serial.print(numbers[i]);
	      Serial.print(" ");
	  }


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
     
     //lcd.setCursor(12, 1);
     Serial.print(constrain(map(analogRead(PIN_THROTTLE),52,890,7,0), 0, 7));
     Serial.print(" ");
     Serial.print(constrain(map(analogRead(PIN_YAW),140,800,0,7), 0 ,7));
     Serial.print(" ");
     Serial.print(constrain(map(analogRead(PIN_PITCH),140,800,0,7), 0, 7));
     Serial.print(" ");
     Serial.print(constrain(map(analogRead(PIN_ROLL),140,800,0,7), 0, 7));
     Serial.print("\n");

}

void knobs_update() {
  /*
     unsigned char b = knob1.getCurrentPos() *  16;
     unsigned char r = 0;
     unsigned char g = 0;

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
*/
      Serial.println(knob1.getCurrentPos());
    
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
		Serial.println("left down");
	} else {
    Serial.println("left up");
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
