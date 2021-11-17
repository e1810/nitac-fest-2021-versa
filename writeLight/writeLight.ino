#include<Adafruit_NeoPixel.h>
#include"headers/rainbow.h"

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
   for(int deg=0; deg<360; deg+=2){
       for(int i=0; i<LED_CNT; i++){
           int8_t r = pic[0][deg][i][0];
           int8_t g = pic[0][deg][i][1];
           int8_t b = pic[0][deg][i][2];
           pixels.setPixelColor(i, pixels.Color(r, g, b));
       }
       pixels.show();
   }
   
}
