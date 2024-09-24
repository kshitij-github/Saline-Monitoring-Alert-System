#define BLYNK_TEMPLATE_ID "TMPL3_CDRdMnD"
#define BLYNK_TEMPLATE_NAME "Saline"
#define BLYNK_AUTH_TOKEN "DTVWsxHqT9r7rATF8HCzVouF8tIDR3L7"
#define BLYNK_PRINT Serial
char ssid[] = "Nothing";
char pass[] = "11111111";
char auth[] = "DTVWsxHqT9r7rATF8HCzVouF8tIDR3L7";

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include "HX711.h"
#include <LiquidCrystal_I2C.h>
#include <SoftwareSerial.h>

const int LOADCELL_DOUT_PIN = 12;
const int LOADCELL_SCK_PIN = 13;
LiquidCrystal_I2C lcd(0x27, 16, 2);
SoftwareSerial mySerial(1,3);
HX711 scale;
int buzzer = 0;

void setup() {
  pinMode(buzzer,OUTPUT);
  lcd.init(); 
  lcd.backlight();
                  
  Serial.begin(9600);
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
  lcd.clear();
  lcd.setCursor(0, 0);         
  lcd.print("*WELCOME*");
  lcd.setCursor(0, 1);         
  lcd.print("   Project");
  delay(2444);
  Serial.begin(9600);
  Serial.println("Load Cell Interfacing with ESP8266 - DIY CHEAP PERFECT");
  
  scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);

  scale.set_scale(466.666);    
  scale.tare();				        
}


void loop() {
  Blynk.run();
  lcd.backlight();
  lcd.clear();                   
  lcd.setCursor(0, 0);          
  lcd.print("WEG :");          
  lcd.setCursor(6, 0);
  float weight = scale.get_units(1);
  Serial.print("Weight: ");
  lcd.print(weight, 1);
  Serial.println(weight, 1);
  lcd.print(" gm");
  Blynk.virtualWrite(V3, weight);


  if (weight < 50.0) {
    Serial.println("Weight is low");
    lcd.setCursor(5, 1);
    lcd.print("LOW");
    delay(1000);
    
    if(weight < 30.0 && weight > 20.0 )
    {
    lcd.clear();
    lcd.print("  Send SMS");
    delay(1000);
    lcd.clear();
    lcd.print("Buzzer");
    digitalWrite(buzzer,1);
  delay(2000);
    }
  } 
  else if (weight < 100.0) {
    Serial.println("Weight is medium");
    lcd.setCursor(5, 1);
    lcd.print("MEDIUM");
    delay(1000);
  }
else {
    Serial.println("Weight is high");
    lcd.setCursor(5, 1);
    lcd.print("HIGH");
    delay(1000);
  }
  
  scale.power_down();			        
  delay(500);
  scale.power_up();
}