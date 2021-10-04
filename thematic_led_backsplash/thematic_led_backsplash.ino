// runs on a nodemcu esp32s

#include <FastLED.h>

// How many leds in your strip?
#define NUM_LEDS 60

// For led chips like WS2812, which have a data line, ground, and power, you just
// need to define DATA_PIN.  For led chipsets that are SPI based (four wires - data, clock,
// ground, and power), like the LPD8806 define both DATA_PIN and CLOCK_PIN
// Clock pin only needed for SPI based chipsets when not using hardware SPI
#define DATA_PIN 21
#define CLOCK_PIN 22
#define LED_BUILTIN 2


// Define the array of leds
CRGB leds[NUM_LEDS];

void setup() {
    // Nodemcu esp32 ledbuiltin
    pinMode(LED_BUILTIN, OUTPUT); 
    // type of led strip to be used
    FastLED.addLeds<SK9822, DATA_PIN, CLOCK_PIN, RGB>(leds, NUM_LEDS);  // BGR ordering is typical
}

void forward_monochromatic() {
  // from first led to last

  // chosen color
  int LED_mix[3] = {random(0,255), random(0,255), random(0,255)};
  for(int i=0; i<=NUM_LEDS; i++) {

    leds[i] = CRGB(LED_mix[0], LED_mix[1], LED_mix[2]);
    FastLED.show();
    delay(10);
    

    leds[i] = CRGB::Black;
    FastLED.show();
    delay(10);
}
}

void backward_monochromatic() {
  // from last led to first

  // chosen color
  int LED_mix[3] = {random(0,255), random(0,255), random(0,255)};
  for(int i=NUM_LEDS; i>=0; i--) {
    leds[i] = CRGB(LED_mix[0], LED_mix[1], LED_mix[2]);
    FastLED.show();
    delay(10);

    leds[i] = CRGB::Black;
    FastLED.show();
    delay(10);
}
}


void onandoff(int speed) {
  int LED_mix[3] = {random(0,255), random(0,255), random(0,255)};
  for(int j=0;j<=NUM_LEDS;j++) {
    leds[j] = CRGB(LED_mix[0], LED_mix[1], LED_mix[2]);
    FastLED.show();
    delay(speed);
  }
  for(int k=NUM_LEDS;k>=0;k--) {
    leds[k] = CRGB::Black;
    FastLED.show();
    delay(speed);
}

}


void twinkle_twinkle() {
    int red_max = random(0,255);
    int green_max = random(0,255);
    int blue_max = random(0,255);
    bool exit = false;
    while(exit=false) {
      red_max = random(0,255);
      green_max = random(0,255);
      blue_max = random(0,255);
    if ((red_max + green_max + blue_max) > 500)
    {
      continue;
    }
    else 
    {
     exit=true;
    }
    }
    
  for(int count=0;count <= 3000; count++) {
    leds[random(0,59)] = CRGB(random(0,red_max),random(0,green_max),random(0,blue_max));
    FastLED.show();
    delay(40);
    //leds[random(0,59)] = CRGB::Black;
    //FastLED.show();
    //delay(1);
  }
  FastLED.clear();
}



void loop() 
{
  digitalWrite(LED_BUILTIN, HIGH);
  delay(20);
  digitalWrite(LED_BUILTIN, LOW);
  
  twinkle_twinkle();
  //onandoff(random(20,80));
  //backward_monochromatic();
  //forward_monochromatic();
  
  
}
   
