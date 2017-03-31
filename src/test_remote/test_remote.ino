
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
#include "RadioFunctions.h"   // Header file for radio functions


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


void setup() {

  //lcd.print("Hello, World!");
 
  const int RADIO_CHANNEL = 11;        // Channel for radio communications (can be 11-26)
  const int SERIAL_BAUD = 9600;        // Baud rate for serial port 
  const int SERIAL1_BAUD = 115200;     // Baud rate for serial1 port

  Serial.begin(SERIAL_BAUD);           // Start up serial
  Serial1.begin(SERIAL_BAUD);         // TODO: what will we use this for
  rfBegin(RADIO_CHANNEL);              // Initialize ATmega128RFA1 radio on given channel
  
  // Send a message to other RF boards on this channel
  rfPrint("ATmega128RFA1 Dev Board Online!\r\n");

  // Set pin modes for all input pins
  pinMode(PIN_YAW, INPUT);             // Gimbal: Yaw
  pinMode(PIN_THROTTLE, INPUT);        // Gimbal: throttle
  pinMode(PIN_ROLL, INPUT);            // Gimbal: roll
  pinMode(PIN_PITCH, INPUT);           // Gimbal: pitch
  pinMode(PIN_POT1, INPUT);            // Potentiometer 1
  pinMode(PIN_POT2, INPUT);            // Potentiometer 2
  pinMode(PIN_BTN1, INPUT);            // Button 1
  pinMode(PIN_BTN2, INPUT);            // Button 2
  pinMode(PIN_LED_BLUE, OUTPUT);       // LED Indicator: Blue
  pinMode(PIN_LED_GRN, OUTPUT);        // LED Indicator: Green
  pinMode(PIN_LED_RED, OUTPUT);        // LED Indicator: Red

  // Write HIGH to buttons for pullup
  digitalWrite(PIN_BTN1, HIGH);   // buttons are active low
  digitalWrite(PIN_BTN2, HIGH);

  // Write low to LED pins
  digitalWrite(PIN_LED_BLUE, 0);
  digitalWrite(PIN_LED_GRN, 0);
  digitalWrite(PIN_LED_RED, 0);
  

  // Attach interrupt for button presses
  //attachInterrupt(PIN_BTN1, button1Callback, CHANGE);
  //attachInterrupt(PIN_BTN2, button2Callback, CHANGE);

}

void button1Callback()
{

  button1Value = digitalRead(PIN_BTN1);
  if (button1Value == LOW)
  {
    button1Press = 1;
  }
  
}

void button2Callback()
{

  button2Value = digitalRead(PIN_BTN2);
  if (button2Value == LOW)
  {
    button2Press = 1;
  }
  
}

void loop() {

  /* BUTTON TEST: Print to serial when button press registered */

  // Read incoming presses from buttons: WHY AREN'T INTERRUPTS WORKING
  button1Value = digitalRead(PIN_BTN1); 
  button2Value = digitalRead(PIN_BTN2); 

  //Serial.println(digitalRead(PIN_BTN1));
  //Serial.println(digitalRead(PIN_BTN2));

  // Print to serial if press registered
  if (button1Value == 0)
  {
    Serial.println("Button 1 press registered!");
    //button1Press = 0;
  }

  if (button2Value == 0)
  {
    Serial.println("Button 2 press registered!");
    //button2Press = 0;
  }

  /* LED TEST: Turn LEDs on and off as program cycles (start LOW) */
  LEDVal = !LEDVal;
  digitalWrite(PIN_LED_BLUE, LEDVal);
  digitalWrite(PIN_LED_GRN, LEDVal);
  digitalWrite(PIN_LED_RED, LEDVal);


  /* GIMBAL TEST: Output incoming values to serial */
  
  /* Read the incoming data from gimbal pins and potentiometer pins
  /*readYaw = analogRead(PIN_YAW);
  readThrottle = analogRead(PIN_THROTTLE);
  readRoll = analogRead(PIN_ROLL);
  readPitch = analogRead(PIN_PITCH);
  readPot1 = analogRead(PIN_POT1);
  readPot2 = analogRead(PIN_POT2);


  // Simple check of analog input functionality: print incoming data to serial out
  //Serial.println("Gimbal Inputs: Roll: " + String(readRoll) + ", Pitch: " + String(readPitch) + ", Yaw: " + String(readYaw) + ", Throttle: " + String(readThrottle));
  //Serial.println("Potentiometer 1: " + String(readPot1) + ", Potentiometer 2: " + String(readPot2));

  /* RADIO TEST: Test sending/receiving of serial data over radio */

  /* If serial comes in...
 /* if (Serial.available())  
  {
    rfWrite(Serial.read()); // ...send it out the radio.
  }
  if (rfAvailable())  // If data received on radio...
  {
    Serial.print(rfRead());  // ... send it out serial.
  }

  Serial.println("\n");
  delay(1);*/

  //Serial1.print("Hello!");
  /*for (int i = 0; i <=255; i++)
  {
    Serial1.write(i);
  }*/

  delay(50);

}
