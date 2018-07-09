#include <radio.h>

#define QUAD_REMOTE_TESTING
#include <quad_remote.h>      // Header file with pin definitions and setup


// Initialize global variables for storing incoming data from input pins
int readYaw = 0;
int readThrottle = 0;
int readRoll = 0;
int readPitch = 0; 
int readPot1 = 0;
int readPot2 = 0;
int button1Value = 0;     // buttons are active high
int button2Value = 0; 
bool button1Press = 0;
bool button2Press = 0;
bool LEDVal = 0;

uint8_t scale[8] = 
     {B00000000,
      B00000000,
      B00000000,
      B00000000,
      B00000000,
      B00000000,
      B00000000,
      B00000000};


#if(0)
void update_display() {
     lcd.clear();
     lcd.home();

     for(char h = 0; h < TOTAL_CHANNELS; h++) {
	  char buf[2];
	  buf[0] = labels[h][0];
	  buf[1] = 0;
	  lcd.print(buf);
	  int n = numbers[h] >> 6;
	  if (n > 8) {
	       lcd.printCustomChar(n - 8);
	  } else {
	       lcd.print(" ");
	  }
     }


     for(char h = 0; h < TOTAL_CHANNELS; h++) {
	  char buf[2];
	  buf[0] = labels[h][1];
	  buf[1] = 0;
	  lcd.print(buf);
	  int n = numbers[h] >> 6;
	  if (n >= 8) {
	       lcd.printCustomChar(8);
	  } else if (n == 0) {
	       lcd.print(" ");
	  } else {
	       lcd.printCustomChar(n);
	  }
     }
}
#endif

void setup() {

     const int RADIO_CHANNEL = 11;        // Channel for radio communications (can be 11-26)
     const int SERIAL_BAUD = 9600 ;        // Baud rate for serial port 
     Serial.begin(SERIAL_BAUD);           // Start up serial
  
     delay(100);
     for(char i = 0; i < 8; i++) {
	  scale[7-i] = B11111111;
	  //lcd.createChar(i+1, scale);
	  delay(10);
     }

     rfBegin(RADIO_CHANNEL);              // Initialize ATmega128RFA1 radio on given channel

     quad_remote_setup();
}

int last = 0;
unsigned char magic;

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
	  delay(100);
	  rfRead(&magic, sizeof(magic));
	  numbers[TOTAL_CHANNELS] = magic;
	  digitalWrite(LED3, 0);
     } else {
	  delay(100);
	  digitalWrite(LED3, 0);
     }

     analogWrite(LCD_LED_RED, (unsigned char)(knob3.getCurrentPos() *  16));
     analogWrite(LCD_LED_GREEN, (unsigned char)(knob2.getCurrentPos() * 16));
     analogWrite(LCD_LED_BLUE, (unsigned char)(knob1.getCurrentPos() *16));

     lcd.home();
     lcd.clear();
     lcd.print("Battery = ");
     lcd.println(analogRead(BATTERY_SENSE));
}
