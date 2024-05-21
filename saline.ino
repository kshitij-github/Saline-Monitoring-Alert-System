#include <ESP8266WiFi.h>
#include "HX711.h"
#define BLYNK_PRINT Serial
#include <Blynk.h>
#include <BlynkSimpleEsp8266.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);
#define BLYNK_PRINT Serial
 
#define BLYNK_TEMPLATE_ID "TMPL3_CDRdMnD"
#define BLYNK_TEMPLATE_NAME "Saline"
#define BLYNK_AUTH_TOKEN "DTVWsxHqT9r7rATF8HCzVouF8tIDR3L7"

char ssid[] = "Kshitij"; // replace with your wifi ssid and wpa2 key
char pass[] = "kshitij@1";
char auth[] = "DTVWsxHqT9r7rATF8HCzVouF8tIDR3L7";    // You should get Auth Token in the Blynk App.
 
WiFiClient client;
 
HX711 scale(D5, D6);

int buzzer = D0;


int rbutton = D4; // this button will be used to reset the scale to 0.
float weight;
float calibration_factor = 101525; // for me this vlaue works just perfect 419640
 
void setup() 
{
  Serial.begin(9600);
  pinMode(rbutton, INPUT_PULLUP); 
  scale.set_scale(466.366);
  scale.tare(); //Reset the scale to 0
  long zero_factor = scale.read_average(); //Get a baseline reading
  Blynk.begin(auth, ssid, pass);
  Wire.begin(D2, D1);
  lcd.begin();
  lcd.setCursor(6,0);
  lcd.print("IOT");
  lcd.setCursor(1,1);
  lcd.print("Weighing Scale");
  delay(3000);
  lcd.clear();
 
  lcd.print("Connecting Wifi");
  
  WiFi.begin(ssid, pass);
  {
  delay(1000);
  Serial.print(".");
  lcd.clear();
  }
  Serial.println("");
  Serial.println("WiFi connected");
  lcd.clear();
  lcd.print("WiFi connected");
  
  delay(2000);
}
 
void loop() 
 
{
 
  Blynk.run();
  scale.set_scale(calibration_factor); //Adjust to this calibration factor
 
  weight = scale.get_units(5); 
 
  lcd.setCursor(0, 0);
  lcd.print("Measured Weight");
  lcd.setCursor(0, 1);
  lcd.print(weight);
  lcd.print(" KG  ");
  Blynk.virtualWrite(V3, weight);
  delay(2000);
  lcd.clear();
  
  Serial.print("Weight: ");
  Serial.print(weight);
  Serial.println(" KG");
  Serial.println();
  
  if(weight>4 && weight<1)
  {
    digitalWrite(buzzer,1);
   
    


  if ( digitalRead(rbutton) == LOW)
{
  scale.set_scale();
  scale.tare(); //Reset the scale to 0
}
 
  }

}