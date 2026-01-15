/*
    Y251229:
        - Test được trở kéo xuống có hoạt động không
        - Test được dòng hoạt động của led 
            - ~18mA: Vàng, đỏ 
            - ~14.4mA: Trắng, xanh dương 
            - <5mA: Led không hoạt động: có thể hở chân R hạn dòng hoặc led bị hàn ngược
            - > 20mA: Trở hạn dòng bị sai giá trị, kiểm tra lại nếu đúng phải là 220Ohm (221)

            - Buzzer:
                - 23mA ~ 32mA
            
            - 1 Relay
                - 65mA~85mA
                - Khi test cần lưu ý:
                    - Diod flyback cần phải được KT trước: Chỉnh nguồn 5V 100mA, cho bật rồi tắt relay, 
                    đo sóng tại chân C Transistor có vượt qua 6V là bị hở chân hoặc chết diod

  
*/

#include "Task_VNEHC_Test.h"

Task_VNEHC_Test Task_VNEHC_Test1;

// the setup routine runs once when you press reset:
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(115200);
  Serial.println(F("Start test M05 Relay"));
  Task_VNEHC_Test1.setup();
  Task_VNEHC_Test1.addHelp(&help);

  // // check R Pulldown Port 3

  if(!Task_VNEHC_Test1.isPullDown_Port3_OK()) 
  {
    Task_VNEHC_Test1.showInfoWithErrorCode(VNEHC_List_Error_PORT3_R_PULLDOWN_FAIL);
    // while(1);
    Task_VNEHC_Test1.stop();
  }
  

  // Set mA MAX 
  if(Task_VNEHC_Test1.checkCurrent_mA(200) != VNEHC_List_Error_None)
  {
    // Serial.println(Task_VNEHC_Test1.getPort3_mA());
    Serial.println(F("May be ERROR!!!"));
  }

  // Bật led
  Task_VNEHC_Test1.setPort3_Output(1);
  
  Task_VNEHC_Test1.delayms(100);
  float tempCurrentmA = Task_VNEHC_Test1.getPort3_mA();
  if(IS_INRANGE(tempCurrentmA,65,85))
  {
    Serial.println(F("Relay GOOD * * * * *"));
    // Serial.println(F("RESET Tool Test for next"));
  }
  else if(tempCurrentmA < 65)
  {
    Serial.println(F("ERROR! Curent < 65mA"));
    Serial.println(F("\t\t Kiem tra ho chan R ke ben Transistor, Transistor, Relay"));
    Task_VNEHC_Test1.showInfoWithErrorCode(VNEHC_List_Error_PORT3_CURRENT_LOWER);
    // Serial.println(F(""));
    // Serial.println(F("RESET Tool Test for next"));
  }
  else if(tempCurrentmA > 85)
  {
    Serial.println(F("ERROR! Curent > 85mA"));
    Task_VNEHC_Test1.showInfoWithErrorCode(VNEHC_List_Error_PORT3_CURRENT_HIGHER);
    // Serial.println(F(""));
    // Serial.println(F("RESET Tool Test for next"));
  }

  Serial.println(F(""));
  Serial.println(F("RESET Tool Test for next"));
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


  Serial.println(Task_VNEHC_Test1.getPort3_mA());
  Task_VNEHC_Test1.delayms(1000);  // delay in between reads for stability
}

void help()
{
  Serial.print(F("ERROR Code: "));
  Serial.println(VNEHC_List_Error_PORT3_R_PULLDOWN_FAIL);
  Serial.print(F("\t kiem tra ho chan R ngoai cung"));
  Serial.println();
  Serial.println();

  Serial.print(F("ERROR Code: "));
  Serial.println(VNEHC_List_Error_PORT3_CURRENT_LOWER);
  Serial.println(F("\t 1) kiem tra ho chan Tran và R ke ben"));
  Serial.println(F("\t 2) Kiem tra Tran, lay nhip nôi tat chan 2-3 cua tran lai, Relay keu la loi Tran => thay Tran"));
  Serial.println(F("\t \t - Relay keu la loi Tran => thay Tran"));
  Serial.println(F("\t \t - Relay KO keu la loi Relay => Kiem tra chieu Relay hoac thay moi"));
  Serial.println();
  Serial.println();

  Serial.print(F("ERROR Code: "));
  Serial.println(VNEHC_List_Error_PORT3_CURRENT_HIGHER);
  Serial.print(F("\t Ghi nhan lai so luong SP bi loi roi bao cao len cap tren duyet"));
  Serial.println();
  Serial.println();
}