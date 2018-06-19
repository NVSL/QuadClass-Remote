
#include <radio.h>


/* test_remote.ino
 * Sketch for testing all parts of QuadRemote.
 * Components tested:
 *    Gimbals:  
 *    Indicator LEDs
 *    Buttons
 *    Serial display
 *    Potentiometers
 *    Radio communications
 */

#include "quad_remote.h"      // Header file with pin definitions and setup
#include <serLCD.h>
serLCD lcd;


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

#define BUTTON_NUMBERS 2
#define ANALOG_NUMBERS 8
#define NUMBER_COUNT (BUTTON_NUMBERS + ANALOG_NUMBERS)
int numbers[NUMBER_COUNT+1] = {0,1,2,3,4,5,6,7,8,9, 0};
char *labels[NUMBER_COUNT] = {"T ", "Y ", "P ", "R ", "P1", "P2", "P3", "P4", "B1", "B2"};
char pins[NUMBER_COUNT] = {PIN_THROTTLE, PIN_YAW, PIN_PITCH, PIN_ROLL, PIN_POT1 , PIN_POT2, PIN_POT3, PIN_POT4, PIN_BTN1, PIN_BTN2};

void update_display() {
  lcd.clear();
  lcd.home();

  for(char h = 0; h < NUMBER_COUNT; h++) {
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
  //lcd.print("\r");

  for(char h = 0; h < NUMBER_COUNT; h++) {
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

void setup() {

  //lcd.print("Hello, World!");
 
  const int RADIO_CHANNEL = 11;        // Channel for radio communications (can be 11-26)
  const int SERIAL_BAUD = 9600 ;        // Baud rate for serial port 
  const int SERIAL1_BAUD = 9600;     // Baud rate for serial1 port

  Serial.begin(SERIAL_BAUD);           // Start up serial
 // Serial1.begin(SERIAL_BAUD);  
  
  Serial.println("hello");
  delay(100);
  for(char i = 0; i < 8; i++) {
    scale[7-i] = B11111111;
    //lcd.createChar(i+1, scale);
    delay(10);
  }
 
  rfBegin(RADIO_CHANNEL);              // Initialize ATmega128RFA1 radio on given channel
  
  // Send a message to other RF boards on this channel
  //rfPrint("ATmega128RFA1 Dev Board Online!\r\n");
  
  // Set pin modes for all input pins
  pinMode(PIN_YAW, INPUT);             // Gimbal: Yaw
  pinMode(PIN_THROTTLE, INPUT);        // Gimbal: throttle
  pinMode(PIN_ROLL, INPUT);            // Gimbal: roll
  pinMode(PIN_PITCH, INPUT);           // Gimbal: pitch
  pinMode(PIN_POT1, INPUT);            // Potentiometer 1
  pinMode(PIN_POT2, INPUT);            // Potentiometer 2
  
  pinMode(PIN_BTN1, INPUT_PULLUP);            // Button 1
  pinMode(PIN_BTN2, INPUT_PULLUP);            // Button 2
  
  pinMode(PIN_LED_BLUE, OUTPUT);       // LED Indicator: Blue
  pinMode(PIN_LED_GRN, OUTPUT);        // LED Indicator: Green
  pinMode(PIN_LED_RED, OUTPUT);        // LED Indicator: Red

  //analogReference(0);
  //Serial.println(ADMUX);
}

int last = 0;
char c  = 'A';
char magic;

void loop() {

  if (last + 1000 <= millis()) {
    LEDVal = 0;//!LEDVal;
    digitalWrite(PIN_LED_BLUE, LEDVal);
    digitalWrite(PIN_LED_GRN, LEDVal);
    digitalWrite(PIN_LED_RED, LEDVal);
    last = millis();
  }
  
  // Read analog values
  for(char i = 0; i < ANALOG_NUMBERS; i++) {
    numbers[i] = analogRead(pins[i]); 
  }
  
  // Read btns
  for(char i = ANALOG_NUMBERS; i < ANALOG_NUMBERS + BUTTON_NUMBERS; i++) {
    numbers[i] = digitalRead(pins[i]) ? 1023 : 0; 
  }


  update_display();

  for(char i= 0; i < NUMBER_COUNT;i++) {
    Serial.print(numbers[i]);
    Serial.print(" ");
  }

  rfWrite((uint8_t*)numbers, sizeof(numbers));

  Serial.println("\n");

  if (rfAvailable()) {  // If data receievd on radio...
      digitalWrite(34, 1);
      delay(100);
      rfRead(&magic, sizeof(magic));
      numbers[NUMBER_COUNT] = magic;
      digitalWrite(34, 0);
  } else {
    delay(100);
    digitalWrite(34,0); 
  }

}
