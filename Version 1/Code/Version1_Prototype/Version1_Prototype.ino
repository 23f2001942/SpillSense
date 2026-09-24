//including the libraries
#include "max6675.h" 
#include "U8glib.h"
#include <Wire.h>

//defining pins 
int buzzGND = 6;     // Buzzer GND pin
int buzzVCC = 7;    // Buzzer 5V pin
int blueVCC = 13;   // HC-06 5V Power pin
int soPin = 5;      // MAX6675 SO pin
int csPin = 4;      // MAX6675 CS pin
int sckPin = 3;     // MAX6675 SCK pin
int ThermoVCC = 2;  // MAX6675 5V Power pin
int red = 12;       // LED Red 
int yel = 11;       // LED Yellow
int blu = 10;       // LED Blue
int gre = 9;        // LED Green
int ledgnd = 8;     // LED's ground Pin

//defining OLED and other sensors
U8GLIB_SH1106_128X64 u8g(U8G_I2C_OPT_NONE);
MAX6675 thermocouple(sckPin, csPin, soPin);

void setup() {
  pinMode(buzzGND, OUTPUT);
  digitalWrite(buzzGND, LOW);
  
  pinMode(buzzVCC, OUTPUT);
  digitalWrite(buzzVCC, LOW);
  
  pinMode(blueVCC, OUTPUT);
  digitalWrite(blueVCC, HIGH);
    
  pinMode(blu, OUTPUT);
  digitalWrite(blu, LOW);
  
  pinMode(gre, OUTPUT);
  digitalWrite(gre, LOW);

  pinMode(yel, OUTPUT);
  digitalWrite(yel, LOW);
  
  pinMode(red, OUTPUT);
  digitalWrite(red, LOW);
  
  pinMode(ledgnd, OUTPUT);
  digitalWrite(ledgnd, LOW);
  
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
      digitalWrite(blu, HIGH);      // turn on Blue LED 
   else 
      digitalWrite(blu, LOW);       // turn off Blue LED
   if (temp >= 70)
      digitalWrite(gre, HIGH);     // turn on Green LED
   else 
      digitalWrite(gre, LOW);      // turn off Green LED
   if (temp >= 80)
      digitalWrite(yel, HIGH);    // turn on Yellow LED
   else 
      digitalWrite(yel, LOW);     // turn off Yellow LED
   if (temp >=90)
      digitalWrite(red, HIGH);       // turn on Red LED
   else 
      digitalWrite(red, LOW);        // turn off Red LED

 u8g.firstPage();
 do {
   draw();   
 } while (u8g.nextPage() );
 delay(1000);
}
