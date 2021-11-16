#include<Adafruit_NeoPixel.h>
#include"headers/bomb.h"


#define LED_CNT 16
#define DATA_PIN 2
#define GND_PIN 4
#define VCC_PIN 1
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(LED_CNT, DATA_PIN, NEO_GRB + NEO_KHZ800);


void setup()
{
  pixels.begin();
  pinMode(GND_PIN, OUTPUT);
  pinMode(VCC_PIN, OUTPUT);
  digitalWrite(GND_PIN, LOW);
  digitalWrite(VCC_PIN, HIGH);
}


void loop()
{
   for(int deg=0; deg<180; deg++){
       for(int i=0; i<LED_CNT; i++){
           pixels.setPixelColor(i, pic[0][deg][i]);
       }
       pixels.show();
   }
   
   delay(1000);
}
