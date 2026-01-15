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

  Task_VNEHC_Test1.addHelp(help);

  showNote();
}

void loop() {
  checkAnalog();
}

void checkAnalog()
{
  int tempValue = analogRead(PIN);
  // adc to V
  tempValue = map(tempValue, 0, 1023, 0, 5000);
  Serial.print(tempValue);
  Serial.print(" mV");
  if(IS_INRANGE(tempValue, 2400, 3300))
  {
    Serial.println(F(" GOOD"));
  }
  else
  {
    Serial.println(F(" ERROR, Thu che mat LDR, go help<CR><LF> vào SerialMonitor de biet cach fix"));
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
  Serial.println(F("Che mat LDR de test"));
  Serial.println(F(""));
  Task_VNEHC_Test1.delayms(3000);
}

void help()
{
  Serial.println();
  Serial.println();
  Serial.println();
  Serial.println();
  Serial.println(F("Kiểm tra trở kéo lên"));
  Serial.println(F("Kiểm tra LDO 3V3"));
  Serial.println(F(""));
  Task_VNEHC_Test1.delayms(3000);
}