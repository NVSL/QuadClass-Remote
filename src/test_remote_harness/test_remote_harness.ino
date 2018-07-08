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

#define QUAD_REMOTE_TESTING
#include <quad_remote.h>

int maxes[TOTAL_CHANNELS + 1];
int mins[TOTAL_CHANNELS + 1];

void setup()
{
  Serial.begin(9600);  // Start up serial
  rfBegin(11);  // Initialize ATmega128RFA1 radio on channel 11 (can be 11-26)

  for(int i = 0; i < TOTAL_CHANNELS + 1; i++) {
       maxes[i] = 0;
       mins[i] = 2048;
  }
}

int led_state = 0;
char sent_magic = 1;
char received_magic = 0;
bool got_radio = false;
void loop()
{
  int misses = 0;
  for (int i=  0; i < TOTAL_CHANNELS; i++) {
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
  Serial.print(numbers[TOTAL_CHANNELS]);
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
    received_magic = (uint8_t)numbers[TOTAL_CHANNELS];
    
    if (r != sizeof(numbers)) {
      Serial.print(" Short read ");
      
    } else {
      
      rfWrite(sent_magic);
      
      for (int i=  0; i < TOTAL_CHANNELS; i++) {
        mins[i] = min(mins[i], numbers[i]);
        maxes[i] = max(maxes[i], numbers[i]);
      }
    }
  }
  Serial.println();
}
