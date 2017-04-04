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
                  
int numbers[8] = {0,1,2,3,4,5,6,7};
char *labels[8] = {"T ", "Y ", "P ", "R ", "P1", "P2", "B1", "B2"};
char pins[8] = {PIN_THROTTLE, PIN_YAW, PIN_PITCH, PIN_ROLL, PIN_POT1, PIN_POT2, PIN_POT1, PIN_POT2};

serLCD lcd;

void update_display() {
  lcd.clear();
  lcd.home();

  for(char h = 0; h < 8; h++) {
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

  for(char h = 0; h < 8; h++) {
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
  const int SERIAL_BAUD = 9600;        // Baud rate for serial port 
  const int SERIAL1_BAUD = 9600;     // Baud rate for serial1 port

  Serial.begin(SERIAL_BAUD);           // Start up serial
  Serial1.begin(SERIAL_BAUD);  
  
  delay(100);
  for(char i = 0; i < 8; i++) {
    scale[7-i] = B11111111;
    lcd.createChar(i+1, scale);
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

}

int last = 0;

void loop() {

  /* BUTTON TEST: Print to serial when button press registered */

  // Read incoming presses from buttons: WHY AREN'T INTERRUPTS WORKING
  button1Value = digitalRead(PIN_BTN1); 
  button2Value = digitalRead(PIN_BTN2); 
    
  // Print to serial if press registered
  if (button1Value == 0)
  {
    numbers[6] = 1024;
  } else {
    numbers[6] = 0;
  }

  if (button2Value == 0)
  {
    numbers[7] = 1024;
  } else {
    numbers[7] = 0;
  }

  /* LED TEST: Turn LEDs on and off as program cycles (start LOW) */

  if (last + 1000 <= millis()) {
    LEDVal = 1;//!LEDVal;
    digitalWrite(PIN_LED_BLUE, LEDVal);
    digitalWrite(PIN_LED_GRN, LEDVal);
    digitalWrite(PIN_LED_RED, LEDVal);
    last = millis();
  }
  // Read analog values
  for(char i = 0; i < 6; i++) {
    numbers[i] = analogRead(pins[i]); 
  }

  update_display();

  for(char i= 0; i < 8;i++) {
    Serial.print(numbers[i]);
    Serial.print(" ");
    
  }

  /* RADIO TEST: Test sending/receiving of serial data over radio */

  /* If serial comes in... */
  /*if (Serial.available())  
  {
    rfWrite(Serial.read()); // ...send it out the radio.
  }
  if (rfAvailable())  // If data received on radio...
  {
    Serial.print(rfRead());  // ... send it out serial.
  }*/

  Serial.println("\n");
 
  delay(200);

}
