#include "max6675.h"
#include <Wire.h> 
#include "U8glib.h"

U8GLIB_SH1106_128X64 u8g(U8G_I2C_OPT_NONE);

int soPin = 3;         // SO = Serial Out
int csPin = 4;         // CS = chip select CS pin
int sckPin = 5;        // SCK = Serial Clock pin
int ThermoVCC = 6;     // MAX6675 5V Power pin
int ThermoGND = 7;     // MAX6675 GND pin

int BlueVCC = 2;       // HC-06 5V Power pin

int buzzVCC = 8;       // Buzzer 5V Power pin
int buzzGND = 9;       // Buzzer GND Power pin

int blueVCC = 11;
int blueGND = 10;
int greenVCC = 13;
int greenGND = 12;
int yellowVCC = A3;
int yellowGND = A2;
int redVCC = A1;
int redGND = A0;

MAX6675 thermocouple(sckPin, csPin, soPin);

void setup() {
  pinMode(buzzVCC, OUTPUT);
  digitalWrite(buzzVCC, LOW);     // intially Power pin is kept at 0V because we don't want Buzzer to start ringing.
  
  pinMode(buzzGND, OUTPUT);
  digitalWrite(buzzGND, LOW);
  
  pinMode(ThermoVCC, OUTPUT);
  digitalWrite(ThermoVCC, HIGH);
  
  pinMode(ThermoGND, OUTPUT);
  digitalWrite(ThermoGND, LOW);
  
  pinMode(blueVCC, OUTPUT);
  digitalWrite(blueVCC, LOW);     // intially VCC pin of LED is kept at 0V because we don't want LED to glow.

  pinMode(blueGND, OUTPUT);
  digitalWrite(blueGND, LOW);     

  pinMode(greenVCC, OUTPUT);
  digitalWrite(greenVCC, LOW);    // intially VCC pin of LED is kept at 0V because we don't want LED to glow.

  pinMode(greenGND, OUTPUT);
  digitalWrite(greenGND, LOW);

  pinMode(yellowVCC , OUTPUT);
  digitalWrite(yellowVCC , LOW);  // intially VCC pin of LED is kept at 0V because we don't want LED to glow.

  pinMode(yellowGND , OUTPUT);
  digitalWrite(yellowGND , LOW);

  pinMode(redVCC , OUTPUT);
  digitalWrite(redVCC , LOW);     // intially VCC pin of LED is kept at 0V because we don't want LED to glow.

  pinMode(redGND , OUTPUT);
  digitalWrite(redGND , LOW);
    
  Serial.begin(9600);
}

void draw(void) {
  u8g.setFont(u8g_font_unifont);
  u8g.setPrintPos(0, 12);
  u8g.print("Milk");
  u8g.setPrintPos(0, 26);
  u8g.print("Temperature");
  u8g.setFont(u8g_font_unifont);
  u8g.setPrintPos(0, 45);
  u8g.print(thermocouple.readCelsius());
  u8g.print(" ");
  u8g.print(char(176));      // ASCII code for the symbol " ° "
  u8g.print("C");
  u8g.setPrintPos(0, 60);
  u8g.print(thermocouple.readFahrenheit());
  u8g.print(" ");
  u8g.print(char(176));      // ASCII code for the symbol " ° "
  u8g.print("F");
}

void loop() {
   delay(100);
   double temp = thermocouple.readCelsius();
   Serial.println(temp);
   if (temp >= 50 && temp <= 51) {
      digitalWrite(buzzVCC, HIGH);
      delay(100);
      digitalWrite(buzzVCC, LOW);
   }

   if (temp >= 60 && temp <= 61) {
      digitalWrite(buzzVCC, HIGH);
      delay(100);
      digitalWrite(buzzVCC, LOW); 
   }

   if (temp >= 70 && temp <= 71) {
      digitalWrite(buzzVCC, HIGH);
      delay(100);
      digitalWrite(buzzVCC, LOW);
   }

   if (temp >= 80 && temp <= 81) {
      digitalWrite(buzzVCC, HIGH);
      delay(100);
      digitalWrite(buzzVCC, LOW);
   }

   if (temp >= 90 && temp <= 91) {
      digitalWrite(buzzVCC, HIGH);
      delay(100);
      digitalWrite(buzzVCC, LOW);
   }

   if (temp >= 98) {
      digitalWrite(buzzVCC, HIGH);
      delay(100);
      digitalWrite(buzzVCC, LOW);
   }

   if (temp >= 60) 
      digitalWrite(blueVCC, HIGH);      // turn on Blue LED 
   else 
      digitalWrite(blueVCC, LOW);       // turn off Blue LED
   if (temp >= 70)
      digitalWrite(greenVCC, HIGH);     // turn on Green LED
   else 
      digitalWrite(greenVCC, LOW);      // turn off Green LED
   if (temp >= 80)
      digitalWrite(yellowVCC, HIGH);    // turn on Yellow LED
   else 
      digitalWrite(yellowVCC, LOW);     // turn off Yellow LED
   if (temp >=90)
      digitalWrite(redVCC, HIGH);       // turn on Red LED
   else 
      digitalWrite(redVCC, LOW);        // turn off Red LED

 u8g.firstPage();
 do {
   draw();   
 } while (u8g.nextPage() );
 delay(1000);
}
