#include <DHT_U.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);

#define temperatureInside 0 
#define dhtpinOutside 6
#define DHTTYPE DHT11
int val;
float tempOldOut = 0;
float tempOldIn = 0;
float mv = 0;
DHT_Unified dhtOut(dhtpinOutside, DHTTYPE);

void setup() 
{
  Serial.begin(9600);
  dhtOut.begin();
  lcd.begin();
  lcd.setBacklight(HIGH);
}

void loop() 
{

  sensors_event_t event;
  dhtOut.temperature().getEvent(&event);
  if (isnan(event.temperature)) {
    Serial.println(F("Error reading temperature!"));
    lcd.setCursor(0,1);
    lcd.print("Error reading");
  }
  else {
    if(tempOldOut!= event.temperature){
      tempOldOut = event.temperature;  
      Serial.print(F("Temperature out: "));
      Serial.print(event.temperature);
      Serial.println(F("°C"));
      lcd.setCursor(0,1);
      lcd.print("OUT: ");
      lcd.setCursor(5,1);
      lcd.print(event.temperature);
      lcd.setCursor(10,1);
      lcd.print("C");
       }   
    
  }
  val = analogRead(temperatureInside);
  mv = ( val * 500)/1023;
  
  if(tempOldIn!=mv)
  {
    tempOldIn = mv;
    Serial.print("Temperature in: ");
    Serial.print(mv);
    Serial.print("*C");
    Serial.println();
    lcd.setCursor(0,0);
    lcd.print("IN: ");
    lcd.setCursor(5,0);
    lcd.print(mv);
    lcd.setCursor(11,0);
    lcd.print("C");
  }
  delay(1000);
}
