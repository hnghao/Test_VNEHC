/*
    y260126:
      - KXN chương trình Test OK: dùng ngón tay cái tiếp xúc với cảm biến đoạn 10-20
    
      - Các bug thường gặp

      - Bug chuong trình test:
          - Khi không Port 3 tự do sẽ bị loạn cho đến khi kết nối với cảm biến
        
    
        Phát hiện chập nguồn ngắt OK
        

*/


#include "Task_VNEHC_Test.h"

Task_VNEHC_Test Task_VNEHC_Test1;

// #define VOLT_THESHOLD_UP_MIN      (7260)
// #define VOLT_THESHOLD_UP_MAX      (8060)

// #define VOLT_THESHOLD_DOWN_MIN      (3800)
// #define VOLT_THESHOLD_DOWN_MAX      (4200)

// // kxn
// #define VOLT_THESHOLD_UP_MIN      (5660)
// #define VOLT_THESHOLD_UP_MAX      (6060)
// #define VOLT_THESHOLD_DOWN_MIN      (4200)
// #define VOLT_THESHOLD_DOWN_MAX      (4600)

// Hao
// #define VOLT_THESHOLD_UP_MIN      (5660)
// #define VOLT_THESHOLD_UP_MAX      (6060)
// #define VOLT_THESHOLD_DOWN_MIN      (4400)
// #define VOLT_THESHOLD_DOWN_MAX      (4800)

// Hộp nước tại 20
#define VOLT_THESHOLD_UP_MIN      (5660)
#define VOLT_THESHOLD_UP_MAX      (6860)
#define VOLT_THESHOLD_DOWN_MIN      (4000)
#define VOLT_THESHOLD_DOWN_MAX      (4800)

#define EN_DEBUG_KXN          (0)


// Which pin on the Arduino is connected to the NeoPixels?
#define PIN        PIN_PORT3_SIG // On Trinket or Gemma, suggest changing this to 1

uint8_t flag_ShowPullUpErr = true;

void setup() {
  Serial.begin(115200);
  Task_VNEHC_Test1.setup();
  
  Task_VNEHC_Test1.checkVoltageCurrent();

  if(Task_VNEHC_Test1.checkCurrent_mA(20) != VNEHC_List_Error_None)
  {
    while(1);
  }

  // Task_VNEHC_Test1.checkVolSignal4P();
  if(Task_VNEHC_Test1.checkVolSignal3P() == VNEHC_List_Error_SIG_OVER_3V3)
  {
    // while(1)
    // {
    //   Serial.println("===");
    //   delay(2000);
    // }
  }

  Task_VNEHC_Test1.addHelp(help);

  showNote();
}

void loop() {
  checkAnalog2();
  Task_VNEHC_Test1.delayms(10); // function check OverCurent
}

void checkAnalog2()
{
  if(Task_VNEHC_Test1.isPullUp_Port3_OK(EN_DEBUG_KXN, VOLT_THESHOLD_UP_MIN, VOLT_THESHOLD_UP_MAX, 50) != VNEHC_List_Error_None)
  {
    if(flag_ShowPullUpErr == true)
    {
      flag_ShowPullUpErr = false;
      Serial.println(F("\t\tERROR PULLUP"));
      // Task_VNEHC_Test1.delayms(2000);  
    }
    
  }
  else
  {
    Serial.println(F("Dùng ngón tay cái tiếp xúc với cảm biến sensor MKE-S13 đoạn 10-20 "));
    while(1)
    {
      if(Task_VNEHC_Test1.isPullDown_Port3_OK(EN_DEBUG_KXN, VOLT_THESHOLD_DOWN_MIN, VOLT_THESHOLD_DOWN_MAX) == VNEHC_List_Error_None)
      {
        
        Task_VNEHC_Test1.delayms(100);
        
        if(Task_VNEHC_Test1.isPullUp_Port3_OK(EN_DEBUG_KXN, VOLT_THESHOLD_UP_MIN, VOLT_THESHOLD_UP_MAX, 1000) == VNEHC_List_Error_None)
        {
          Serial.println(F("\t\tFLAME GOOD\t\t Sensor tiep theo"));
          flag_ShowPullUpErr = true;
          Task_VNEHC_Test1.delayms(100);
        }
        else
        {
          Serial.println(F("\t\tFLAME ERROR\t\t Sensor tiep theo"));
          flag_ShowPullUpErr = true;
          Task_VNEHC_Test1.delayms(1000);
        }

        break;
      }
      
    }
  }
}

void showNote()
{
  Serial.println();
  Serial.println();
  Serial.println();
  Serial.println();
  Serial.println(F("LUU Y TRUOC KHI TEST"));
  Serial.println(F("Dùng ngón tay cái tiếp xúc với cảm biến sensor MKE-S13 đoạn 10-20 "));
  Serial.println(F(""));
  Task_VNEHC_Test1.delayms(3000);
}

void help()
{
  Serial.println();
  Serial.println();
  Serial.println();
  Serial.println();
  Serial.println(F("Kiem tra ho chan R ke ben Lable SENSOR"));
  Serial.println(F("Kiem tra LDO 3V3"));
  Serial.println(F(""));
  Task_VNEHC_Test1.delayms(3000);
}