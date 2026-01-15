/*
    y251222: 
        Phát hiện chập nguồn ngắt OK
        Sang sang Test

*/

// NeoPixel Ring simple sketch (c) 2013 Shae Erisson
// Released under the GPLv3 license to match the rest of the
// Adafruit NeoPixel library

#include "Task_VNEHC_Test.h"

Task_VNEHC_Test Task_VNEHC_Test1;
#define PIXEL_CURRENT_PER_LED_mA_MIN     (26)
#define PIXEL_CURRENT_PER_LED_mA_MAX     (60)

// Which pin on the Arduino is connected to the NeoPixels?
#define PIN        PIN_PORT3_SIG // On Trinket or Gemma, suggest changing this to 1

#define DELAYVAL 500 // Time (in milliseconds) to pause between pixels

void setup() {
  Serial.begin(115200);
  Task_VNEHC_Test1.setup();
  
  Task_VNEHC_Test1.checkVoltageCurrent();

  if(Task_VNEHC_Test1.checkCurrent_mA(50) != VNEHC_List_Error_None)
  {
    while(1);
  }

  // Task_VNEHC_Test1.checkVolSignal4P();
  if(Task_VNEHC_Test1.checkVolSignal3P() != VNEHC_List_Error_None)
  {
    while(1)
    {
      Serial.println("===");
      delay(2000);
    }
  }

  // pinMode(PIN, INPUT_PULLUP);

  showNote();

  // checkAnalog();
}

void loop() {
  checkAnalog();
}

void checkAnalog()
{
  int tempValue = analogRead(PIN);
  int tempDigitalValue = digitalRead(PIN);
  // adc to V
  tempValue = map(tempValue, 0, 1023, 0, 5000);
  Serial.print(tempDigitalValue);
  Serial.print("\t");
  Serial.print(tempValue);
  Serial.print(" mV");
  if(IS_INRANGE(tempValue, 3200, 3400))
  {
    Serial.println(F(" GOOD"));
  }
  else if(IS_INRANGE(tempValue, 300, 3200) || IS_INRANGE(tempValue, 3400, 6000))
  {
    Serial.println(F(" ERROR"));
  }
  else
  {
    Serial.println(F(" Nut đang duoc nhan, neu khong thi ERROR"));
  }
  Task_VNEHC_Test1.delayms(1000);
}

void showNote()
{
  Serial.println();
  Serial.println();
  Serial.println();
  Serial.println();
  Serial.println(F("LUU Y TRUOC KHI TEST"));
  Serial.println(F("Nhan nut (~0mV) và nha nut (~3300mV), quan sat gia tri mV"));
  Serial.println(F(""));
  Task_VNEHC_Test1.delayms(3000);
}