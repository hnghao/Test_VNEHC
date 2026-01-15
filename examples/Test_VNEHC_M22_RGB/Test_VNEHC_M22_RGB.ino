/*
    y251222: 
        Phát hiện chập nguồn ngắt OK
        Phát hiện I led tiêu chuẩn OK 
*/

// NeoPixel Ring simple sketch (c) 2013 Shae Erisson
// Released under the GPLv3 license to match the rest of the
// Adafruit NeoPixel library

#include "Task_VNEHC_Test.h"

Task_VNEHC_Test Task_VNEHC_Test1;
#define PIXEL_CURRENT_PER_LED_mA_MIN     (26)
#define PIXEL_CURRENT_PER_LED_mA_MAX     (60)

#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
 #include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif

// Which pin on the Arduino is connected to the NeoPixels?
#define PIN        PIN_PORT3_SIG // On Trinket or Gemma, suggest changing this to 1

// How many NeoPixels are attached to the Arduino?
#define NUMPIXELS 3 // Popular NeoPixel ring size

// When setting up the NeoPixel library, we tell it how many pixels,
// and which pin to use to send signals. Note that for older NeoPixel
// strips you might need to change the third parameter -- see the
// strandtest example for more information on possible values.
// Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel *pPixels;

#define DELAYVAL 500 // Time (in milliseconds) to pause between pixels
// float array_mA[]
void setup() {
  Serial.begin(115200);
  Task_VNEHC_Test1.setup();
  if(Task_VNEHC_Test1.checkCurrent_mA(200) != VNEHC_List_Error_None)
  {
    while(1);
  }
  Task_VNEHC_Test1.checkVoltageCurrent();
  // Task_VNEHC_Test1.checkVolSignal4P();
  if(Task_VNEHC_Test1.checkVolSignal3P() != VNEHC_List_Error_None)
  {
    while(1)
    {
      Serial.println("===");
      delay(2000);
    }
  }

  pPixels = new Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);
  
  // These lines are specifically to support the Adafruit Trinket 5V 16 MHz.
  // Any other board, you can remove this part (but no harm leaving it):
#if defined(__AVR_ATtiny85__) && (F_CPU == 16000000)
  clock_prescale_set(clock_div_1);
#endif
  // END of Trinket-specific code.

  pPixels->begin(); // INITIALIZE NeoPixel strip object (REQUIRED)
}

void loop() {
  pPixels->clear(); // Set all pixel colors to 'off'
  pPixels->show();   // Send the updated pixel colors to the hardware.
  delay(10);

  uint32_t tempCurrentmV = 0, tempLastCurrentmV = 0;
  uint8_t tempFlagNoERROR = true;

  // The first NeoPixel in a strand is #0, second is 1, all the way up
  // to the count of pixels minus one.
  for(int i=0; i<NUMPIXELS; i++) { // For each pixel...

    // pPixels->Color() takes RGB values, from 0,0,0 up to 255,255,255
    // Here we're using a moderately bright green color:
    

    if(i == 0) pPixels->setPixelColor(i, pPixels->Color(255, 255, 255));
    else
      pPixels->setPixelColor(i, pPixels->Color(255, 255, 255));

    pPixels->show();   // Send the updated pixel colors to the hardware.
    delay(20);
    
    tempCurrentmV = Task_VNEHC_Test1.INA->getCurrent_mA(0); 
    uint32_t tempLimitValue = PIXEL_CURRENT_PER_LED_mA_MIN*(i+1);
    uint32_t tempCurrentOnled = tempCurrentmV - tempLastCurrentmV;
    tempLastCurrentmV = tempCurrentmV;
    Serial.print(tempCurrentOnled);
    // Serial.print("\t");

    if(IS_INRANGE(tempCurrentOnled, PIXEL_CURRENT_PER_LED_mA_MIN, PIXEL_CURRENT_PER_LED_mA_MAX))
    {
      Serial.print(F("\t"));  
    }
    else
    {
      tempFlagNoERROR = false;
      Serial.print(F("/"));
      Serial.print(PIXEL_CURRENT_PER_LED_mA_MIN);
      Serial.print(F(" BUG "));
      Serial.print(F("\t"));
      // Serial.print(tempCurrentmV);
    }
    
    // if(Task_VNEHC_Test1.checkCurrent_mA(PIXEL_CURRENT_PER_LED_mA*(i+1)) != VNEHC_List_Error_None)
    if(Task_VNEHC_Test1.checkCurrent_mA(200) != VNEHC_List_Error_None)
    {
      while(1);
    }
    Task_VNEHC_Test1.delayms(DELAYVAL); // Pause before next pass through loop
  }
  if(tempFlagNoERROR)
  {
    Serial.println(F("GOOD"));  
  }
  else
  {
    Serial.println(F("ERROR "));
    // Serial.println(tempCurrentmV);
  }
}
