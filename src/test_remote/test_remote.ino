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

void knobs_update();
void btn1_pressed(bool);

void setup() {

     const int RADIO_CHANNEL = 11;        // Channel for radio communications (can be 11-26)
     const int SERIAL_BAUD = 9600 ;        // Baud rate for serial port 
     Serial.begin(SERIAL_BAUD);           // Start up serial
     delay(100);
     quad_remote_setup();

     ADMUX_struct.refs = 0;
     
     for(char i = 0; i < 8; i++) {
	  scale[7-i] = B11111111;
	  lcd.createChar(i, scale);
	  delay(10);
     }

     rfBegin(RADIO_CHANNEL);              // Initialize ATmega128RFA1 radio on given channel

     knobs_update_cb = knobs_update;
     btn1_cb = btn1_pressed;
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
	  delay(100);
	  rfRead(&magic, sizeof(magic));
	  numbers[TOTAL_CHANNELS] = magic;
	  digitalWrite(LED3, 0);
     } else {
	  delay(100);
	  digitalWrite(LED3, 0);
     }
     
     lcd.setCursor(12, 1);
     lcd.write(constrain(map(analogRead(PIN_THROTTLE),140,800,0,7), 0, 7));
     lcd.write(constrain(map(analogRead(PIN_YAW),140,800,0,7), 0 ,7));
     lcd.write(constrain(map(analogRead(PIN_PITCH),140,800,0,7), 0, 7));
     lcd.write(constrain(map(analogRead(PIN_ROLL),140,800,0,7), 0, 7));

}

void knobs_update() {
     unsigned char r = knob3.getCurrentPos() *  16;
     unsigned char g = knob2.getCurrentPos() *  16;
     unsigned char b = knob1.getCurrentPos() *  16;

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
}


void btn1_pressed(bool down) {
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
