/*
    Y251229:
        - Test được trở kéo xuống có hoạt động không
        - Test được dòng hoạt động của led 
            - ~18mA: Vàng, đỏ 
            - ~14.4mA: Trắng, xanh dương, x-lá 
            - <5mA: Led không hoạt động: có thể hở chân R hạn dòng hoặc led bị hàn ngược
            - > 20mA: Trở hạn dòng bị sai giá trị, kiểm tra lại nếu đúng phải là 220Ohm (221)

  
*/

#include "Task_VNEHC_Test.h"

Task_VNEHC_Test Task_VNEHC_Test1;

// the setup routine runs once when you press reset:
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(115200);
  Serial.println(F("Start test 1-LED"));
  Task_VNEHC_Test1.setup();

  // // check R Pulldown Port 3

  if(!Task_VNEHC_Test1.isPullDown_Port3_OK()) while(1);

  

  // Set mA MAX 
  if(Task_VNEHC_Test1.checkCurrent_mA(30) != VNEHC_List_Error_None)
  {
    // Serial.println(Task_VNEHC_Test1.getPort3_mA());
    Serial.println(F("May be ERROR!!!"));
  }

  // Bật led
  Task_VNEHC_Test1.setPort3_Output(1);
  
  Task_VNEHC_Test1.delayms(100);
  float tempCurrentmA = Task_VNEHC_Test1.getPort3_mA();
  if(IS_INRANGE(tempCurrentmA,13,20))
  {
    Serial.println(F("Led GOOD * * * * *"));
    Serial.println(F("RESET Tool Test for next"));
  }
  else if(tempCurrentmA < 13)
  {
    Serial.println(F("ERROR! Curent < 13mA"));
    Serial.println(F("Kiem tra ho chan R han dong Led (220Ohm), Chieu led"));
    Serial.println(F("RESET Tool Test for next"));
  }
  else if(tempCurrentmA > 20)
  {
    Serial.println(F("ERROR! Curent > 20mA"));
    Serial.println(F("Kiem tra R han dong Led đúng 221 (220 Ohm) không"));
    Serial.println(F("RESET Tool Test for next"));
  }
  Serial.println();
  
  // Tắt led
  Task_VNEHC_Test1.setPort3_Output(0);

}

// the loop routine runs over and over again forever:
void loop() {
  // // read the input on analog pin 0:
  // // int sensorValue = analogRead(A0);
  // uint32_t sensorValue = Task_VNEHC_Test1.sumAnalog_CheckPullDown_Port3();
  // // print out the value you read:
  // Serial.println(sensorValue);


  // Serial.println(Task_VNEHC_Test1.getPort3_mA());
  Task_VNEHC_Test1.delayms(1000);  // delay in between reads for stability
}
