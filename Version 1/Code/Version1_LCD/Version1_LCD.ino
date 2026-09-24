#include "max6675.h"
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

int soPin = 3;   // SO=Serial Out
int csPin = 4;   // CS = chip select CS pin
int sckPin = 5;  // SCK = Serial Clock pin
int ThermoVCC = 6; 
int ThermoGND = 7;

int BlueVCC = 2;

int buzzVCC = 8;
int buzzGND = 9;

MAX6675 thermocouple(sckPin, csPin, soPin);

void setup() {
  pinMode(buzzVCC, OUTPUT);
  pinMode(buzzGND, OUTPUT);
  pinMode(ThermoVCC, OUTPUT);
  pinMode(ThermoGND, OUTPUT);
  pinMode(BlueVCC, OUTPUT);

  digitalWrite(buzzVCC, LOW);
  digitalWrite(buzzGND, LOW);
  digitalWrite(ThermoVCC, HIGH);
  digitalWrite(ThermoGND, LOW);
  digitalWrite(BlueVCC, HIGH);
       
  Serial.begin(9600);
}

void loop() {
   double temp = thermocouple.readCelsius();
   Serial.print(temp);
   if (temp < 50) {
      digitalWrite(buzzVCC, LOW);
      delay(50);
   }
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
   }
 
  lcd.clear(); 
      lcd.setCursor(0,0);      
      lcd.print("Temperature");

      lcd.setCursor(0,1);
      lcd.print(thermocouple.readCelsius()); 
      lcd.setCursor(5,1);
      lcd.print((char)223); 
      lcd.setCursor(6,1);
      lcd.print("C");    
                  
      lcd.setCursor(7,1);
      lcd.print(" ");       
      lcd.setCursor(8,1);
      lcd.print(thermocouple.readFahrenheit()); 
      lcd.setCursor(14,1);      
      lcd.print((char)223); 
      lcd.setCursor(15,1);
      lcd.print("F");   
}
