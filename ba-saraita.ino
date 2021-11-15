#include<Adafruit_NeoPixel.h>
#include"headers/sample.h"

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
   uint32_t tmp_color;
   for(int deg=0; deg<36; deg++){
       for(int i=0; i<LED_CNT; i++){
           tmp_color = pic[0][deg][i];
           pixels.setPixelColor(i, tmp_color);
       }
   }
   pixels.show();
   delay(1000);
}
