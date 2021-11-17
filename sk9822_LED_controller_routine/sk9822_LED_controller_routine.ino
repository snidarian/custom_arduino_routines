
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

//  red - mode button
#define MODE_CHANGE 36
// green color button
#define COLOR_CHANGE 39
// blue speed button
#define SPEED_CYCLE 34




// Define the array of leds
CRGB leds[NUM_LEDS];

void setup() {
    // Nodemcu esp32 ledbuiltin
    pinMode(LED_BUILTIN, OUTPUT);
    // speed cycle input button on pin 34
    pinMode(SPEED_CYCLE, INPUT); 
    // Setup pin 36 for mode change
    pinMode(MODE_CHANGE, INPUT);
    // setup pin 39 for color change
    pinMode(COLOR_CHANGE, INPUT);
    // orange speed LED indicator

    FastLED.addLeds<SK9822, DATA_PIN, CLOCK_PIN, RGB>(leds, NUM_LEDS);  // BGR ordering is typical
}


int epilepsy_mode()
{
  FastLED.clear();
  bool change_mode = false;
  bool change_color = false;
  int cycle_speed = 50;
  while(change_mode==false)
  {
    change_color = false;
    int flash_color[3] = {random(0,255), random(0,255), random(0,255)};
    while(change_color==false)
    {
      for(int i=0;i<NUM_LEDS;i++)
      {
        leds[i] = CRGB(flash_color[0],flash_color[1],flash_color[2]);
      }
      FastLED.show();
      digitalWrite(LED_BUILTIN, HIGH);
      delay(cycle_speed);
      digitalWrite(LED_BUILTIN, LOW);
      for(int j=0;j<NUM_LEDS;j++)
      {
        leds[j] = CRGB(0,0,0);
      }
      FastLED.show();
      digitalWrite(LED_BUILTIN, HIGH);
      delay(cycle_speed);
      digitalWrite(LED_BUILTIN, LOW);

      int mode_button_state = digitalRead(MODE_CHANGE);
      int color_button_state = digitalRead(COLOR_CHANGE);
      int speed_button_state = digitalRead(SPEED_CYCLE);
      
      if (mode_button_state==1) 
          {
            // change mode
            FastLED.clear();
            return 0;
          }
          else if (color_button_state==1) 
          {
            // Change color
            change_color = true;
            break;
          }
          else if (speed_button_state==1) 
          {
            if (cycle_speed >= 6) 
            {
              cycle_speed-=5;
              delay(100);
            }
            else 
            {
              cycle_speed=10;
              delay(100);
            }
          }
    }
  }
}


int twinkle_twinkle() {
    bool change_mode = false;
    int cycle_speed = 50;
    
    while(change_mode==false) {

      int mode_button_state = digitalRead(MODE_CHANGE);
      int color_button_state = digitalRead(COLOR_CHANGE);
      int speed_button_state = digitalRead(SPEED_CYCLE);
      
      bool change_color = false;
      int red_max = random(0,255);
      int green_max = random(0,255);
      int blue_max = random(0,255);
      if ((red_max + green_max + blue_max) > 500)
      {
        change_color = true;
      }
      else 
      {
        change_color = false; 
      }        
      
      while(change_color==false) 
      {
 
        for(int count = 0;count <= 10000000;count++) {
      
          mode_button_state = digitalRead(MODE_CHANGE);
          color_button_state = digitalRead(COLOR_CHANGE);
          speed_button_state = digitalRead(SPEED_CYCLE);
          
          if (mode_button_state==1) 
          {
            // change mode
            FastLED.clear();
            return 0;
          }
          else if (color_button_state==1) 
          {
            // Change color
            change_color = true;
            break;
          }
          else if (speed_button_state==1) 
          {
            if (cycle_speed >= 11) 
            {
              cycle_speed-=10;
              delay(120);
            }
            else 
            {
              cycle_speed=120;
              delay(120);
            }
          }
        leds[random(0,59)] = CRGB(random(0,red_max),random(0,green_max),random(0,blue_max));
        FastLED.show();
        delay(cycle_speed);

      }
    }
  }
  FastLED.clear();
}



int dichromatic_wave()
{
    bool change_mode = false;
    bool change_color = false;
    int cycle_speed = 50;
    
    // cycle through the wave
    while(change_mode==false)
    {   
      // reinitialize change_color to false for when it breaks from loop
      change_color=false;
      // initialize current wave and background colors
      int wave_color[3] = {random(0,255), random(0,255), random(0,255)};
      int background_color[3] = {random(0,255), random(0,255), random(0,255)};
      // For loop to initialize all LEDs to background color
      for(int i=0; i<NUM_LEDS-1;i++)
      {
        leds[i] = CRGB(background_color[0], background_color[1], background_color[2]);
        FastLED.show();
        delay(5);
      } 
      while(change_color==false) {
        
      // For loop that runs the wave cycle function
      for(int j=2; j < NUM_LEDS-1;j++)
      {
        int mode_button_state = digitalRead(MODE_CHANGE);
        int color_button_state = digitalRead(COLOR_CHANGE);
        int speed_button_state = digitalRead(SPEED_CYCLE);
        if (mode_button_state==1) {
        // change mode
        //change_mode = true;
        //change_color = true;
        return 0;
        }
        else if (color_button_state==1) {
        // Change color
        change_color = true;
        break;
        }
        else if (speed_button_state==1) {
          if (cycle_speed >= 6) {
            cycle_speed-=5;
            delay(100);
          }
          else {
            cycle_speed=120;
            delay(100);
          }
        }
        leds[j] = CRGB(wave_color[0], wave_color[1], wave_color[2]);
        leds[j-1] = CRGB(wave_color[0], wave_color[1], wave_color[2]);
        leds[j+1] = CRGB(wave_color[0], wave_color[1], wave_color[2]);
        // change back to background as wave passes
        leds[j-2] = CRGB(background_color[0], background_color[1], background_color[2]);
        FastLED.show();
        delay(cycle_speed);

      }

    }
    }
    return 0;
    FastLED.clear();
}

int solid_color_mode()
{
  int mode_button_state = digitalRead(MODE_CHANGE);
  int color_button_state = digitalRead(COLOR_CHANGE);
  int speed_button_state = digitalRead(SPEED_CYCLE);
  bool change_mode = false;
  bool change_color = false;
  
  while(change_mode==false)
  {
    change_color = false;
    // select solid color to display
    int solid_color[3] = {random(0,255), random(0,255), random(0,255)};
    while(change_color==false)
    {
      for(int i=0;i<NUM_LEDS;i++)
      {
        leds[i] = CRGB(solid_color[0], solid_color[1], solid_color[2]);
      }
      FastLED.show();
      // for loop that checks for button presses
      for(int j=0;j<NUM_LEDS;j++)
      {
        mode_button_state = digitalRead(MODE_CHANGE);
        color_button_state = digitalRead(COLOR_CHANGE);
        speed_button_state = digitalRead(SPEED_CYCLE);
         
        if (mode_button_state==1) 
        {
          // change mode
          FastLED.clear();
          return 0;
        }
        else if (color_button_state==1) 
        {
          // Change color
          change_color = true;
          delay(100);
          break;
        }
        delay(20);
      }
    }
  }
}


// quick led reset indicator function to show mode is changing
int mode_change_led_sperg()
{
    for(int p=0;p<10;p++)
    {
    digitalWrite(LED_BUILTIN, HIGH);
    delay(50);
    digitalWrite(LED_BUILTIN, LOW);
    delay(50);
    }
    return 0;
}


void loop() 
{
  solid_color_mode();

  mode_change_led_sperg();
  
  dichromatic_wave();

  mode_change_led_sperg();
  
  twinkle_twinkle();

  mode_change_led_sperg();

  epilepsy_mode();

  mode_change_led_sperg();
}
  
