#include<Adafruit_NeoPixel.h>
#include"headers/jota.h"

#define DEG_STEP 5
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
   for(int deg=0; deg<360; deg+=DEG_STEP){
       for(int i=0; i<LED_CNT; i++){
           int8_t r = pic[0][deg/DEG_STEP][i][0];
           int8_t g = pic[0][deg/DEG_STEP][i][1];
           int8_t b = pic[0][deg/DEG_STEP][i][2];
           pixels.setPixelColor(i, pixels.Color(r, g, b));
       }
       delay(2);
       pixels.show();
   }
   
}
