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
      Serial.println(F("Restart Please!"));
      Task_VNEHC_Test1.OutPWR_off();

      Task_VNEHC_Test1.delayms(2000);
    }
  }

  showNote();
  int tempmV = readVoltFromPIN3P_mV();
  while(!IS_INRANGE(tempmV,3200,3400) )
  {
    tempmV = readVoltFromPIN3P_mV();
    showNote();
    Serial.print(tempmV);
    Serial.print("\t");
    if(tempmV > 3400)
    {
      Serial.println(F("ERROR LDO 3V3"));
    }
    // Task_VNEHC_Test1.delayms(1000);
  }
}

void loop() {
  checkAnalog();
}

int readVoltFromPIN3P_mV()
{
  int tempValue = analogRead(PIN);
  
  // adc to V
  tempValue = map(tempValue, 0, 1023, 0, 5000);
  return tempValue;
}

uint8_t checkAnalog()
{
  // int tempValue = analogRead(PIN);
  // // adc to V
  // tempValue = map(tempValue, 0, 1023, 0, 5000);

  int tempValue = readVoltFromPIN3P_mV();
  Serial.print(tempValue);
  Serial.print(" mV");
  if(IS_INRANGE(tempValue, 3200, 3400) || IS_INRANGE(tempValue, 0, 0.7) || IS_INRANGE(tempValue, 1500, 1730))
  {
    Serial.println(F(" GOOD"));
  }
  else
  {
    if(tempValue >= 3400)
    {
      Serial.println(F("ERROR SIGNAL OVER 3V3"));  
      Serial.println(F("Restart Please!"));
      Task_VNEHC_Test1.OutPWR_off();
      Task_VNEHC_Test1.restart();
    }
    Serial.println(F(" ERROR nêu khong xoay bien tro Theo MAX(~3300mV), MIN(~0mV), MID(~1650mV)"));
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
  Serial.println(F("Van bien tro theo chieu kim dong ho de có Vmax 3300mV"));
  Serial.println(F(""));
  Task_VNEHC_Test1.delayms(1000);
}