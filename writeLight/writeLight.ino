#include<Adafruit_NeoPixel.h>
#include"headers/akashi_HELLO.h"
#include"headers/side.h"

#define STAY_COUNT 8
#define DEG_STEP 6
#define LED_CNT 16

#define DATA_PIN 2
#define GND_PIN 4
#define VCC_PIN 1
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(LED_CNT+8, DATA_PIN, NEO_GRB + NEO_KHZ800);


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
  for(int img_no=0; img_no<FRAME_COUNT; img_no++){
    for(int stay=0; stay<STAY_COUNT; stay++){
     
     for(int deg=0; deg<360; deg+=DEG_STEP/2){
      for(int i=0; i<LED_CNT; i++){
           int8_t r = pic[img_no][deg/DEG_STEP][i][0];
           int8_t g = pic[img_no][deg/DEG_STEP][i][1];
           int8_t b = pic[img_no][deg/DEG_STEP][i][2];
           pixels.setPixelColor(i, pixels.Color(r, g, b));
       }
       for(int i=0; i<8; i++){
        int8_t r = sidepic[deg/(DEG_STEP/2)][i][0];
        int8_t g = sidepic[deg/(DEG_STEP/2)][i][1];
        int8_t b = sidepic[deg/(DEG_STEP/2)][i][2];
        pixels.setPixelColor(i+LED_CNT, pixels.Color(r, g, b));
        //pixels.setPixelColor(i+LED_CNT, pixels.Color(127, 0, 0));
        Serial.printf("%d %d %d\n", r, g, b);
       }
       delay(0.8);
       pixels.show();
      } 
    
    }
  }
   
}
