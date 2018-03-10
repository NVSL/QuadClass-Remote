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

int numbers[9] = {512,512,512,512, 512,512,512,512, 0};
int maxes[8] = {0,0,0,0,0,0,0,0};
int mins[8] = {1024,1024,1024,1024,1024,1024,1024,1024};

void setup()
{
  Serial.begin(9600);  // Start up serial
  rfBegin(11);  // Initialize ATmega128RFA1 radio on channel 11 (can be 11-26)
  pinMode(34, OUTPUT);  // Pin B6 as output
  // Send a message to other RF boards on this channel
  rfPrint("ATmega128RFA1 Dev Board Online!\r\n");
}

int led_state = 0;
char sent_magic = 0x25;
char received_magic = 0;

void loop()
{
  int misses = 0;
  for (int i=  0; i < 8; i++) {
     if (mins[i] > 256) 
        misses++;
     if (maxes[i] < 256)
        misses++;
     Serial.print(numbers[i]);
     Serial.print(" ");
  }
  Serial.print(misses);
  Serial.print(" ");
  if (misses == 0) {
    Serial.print("Test passed ");
   }

  if (sent_magic == received_magic) {
    Serial.print("RADIO! ");
  }
  Serial.println();

  if (rfAvailable())  // If data receievd on radio...
  {
    digitalWrite(34, 1);
    int r = rfRead((uint8_t*)numbers, sizeof(numbers));
    received_magic = (uint8_t)numbers[8];
    
    if (r != sizeof(numbers)) {
      Serial.println("Short read");
      
    } else {
      
      rfWrite(sent_magic);
      
      for (int i=  0; i < 8; i++) {
        mins[i] = min(mins[i], numbers[i]);
        maxes[i] = max(maxes[i], numbers[i]);
      }
    }
  }
}
