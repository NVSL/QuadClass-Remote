/*
  ATmega128RFA1 Dev Board Basic Chat
  by: Jim Lindblom
      SparkFun Electronics
  date: July 3, 2012
  License: Beerware. Feel free to use, reuse, and modify this code
  as you please. If you find it useful, you can buy me a beer.

  This code sets up the ATmega128RFA1's wireless transciever in
  the most basic way possible to serve as a serial gateway.
  Serial into the ATmega128RFA1's UART0 will go out the RF radio.
  Data into the RF radio will go out the MCU's UART0.
*/

#include "radio.h"


#define BUTTON_NUMBERS 2
#define ANALOG_NUMBERS 8
#define NUMBER_COUNT (BUTTON_NUMBERS + ANALOG_NUMBERS)
int numbers[NUMBER_COUNT+1] = {0,1,2,3,4,5,6,7,8,9, 0};
//int numbers[9] = {512,512,512,512, 512,512,512,512, 0};
int maxes[NUMBER_COUNT] = {0,0,0,0,0,0,0,0};
int mins[NUMBER_COUNT] = {1024,1024,1024,1024,1024,1024,1024,1024};

void setup()
{
  Serial.begin(9600);  // Start up serial
  rfBegin(11);  // Initialize ATmega128RFA1 radio on channel 11 (can be 11-26)
  pinMode(34, OUTPUT);  // Pin B6 as output
  // Send a message to other RF boards on this channel
  //frfPrint("ATmega128RFA1 Dev Board Online!\r\n");
}

int led_state = 0;
char sent_magic = 1;
char received_magic = 0;
bool got_radio = false;
void loop()
{
  int misses = 0;
  for (int i=  0; i < NUMBER_COUNT; i++) {
     if (mins[i] > 256) 
        misses++;
     if (maxes[i] < 256)
        misses++;
     Serial.print(numbers[i]);
     Serial.print(" ");
  }
  if (sent_magic > 20) {
    got_radio = true;
  }
  if (!got_radio) {
    misses++;
  }
  Serial.print(numbers[NUMBER_COUNT]);
  Serial.print(" ");
  Serial.print(misses);
  Serial.print(" ");
  if (misses == 0) {
    Serial.print("Test passed ");
  }

  if (sent_magic == received_magic) {
    Serial.print("RADIO! ");
    sent_magic++;
  }

  if (rfAvailable())  // If data receievd on radio...
  {
    
    int r = rfRead((uint8_t*)numbers, sizeof(numbers));
    received_magic = (uint8_t)numbers[NUMBER_COUNT];
    
    if (r != sizeof(numbers)) {
      Serial.print(" Short read ");
      
    } else {
      
      rfWrite(sent_magic);
      
      for (int i=  0; i < NUMBER_COUNT; i++) {
        mins[i] = min(mins[i], numbers[i]);
        maxes[i] = max(maxes[i], numbers[i]);
      }
    }
  }
  Serial.println();
}
