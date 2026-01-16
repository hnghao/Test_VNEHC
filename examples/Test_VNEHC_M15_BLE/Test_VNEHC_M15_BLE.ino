/*
  Y260116: 
    - Kiem tra dien ap cua tin hieu 3V < S < 3V3 OK
    - Set ten theo chuan M0015_xxxx voi xxxx la 4 chu cuoi ma MAC
*/
#include "Task_VNEHC_Test.h"
#include "SoftwareSerial.h"
#include "MKE_M15.h"

Task_VNEHC_Test Task_VNEHC_Test1;

// #define PIN_PORT4_RX      A1
// #define PIN_PORT4_TX      A2
SoftwareSerial sSerial(PIN_PORT4_RX, PIN_PORT4_TX);


MKE_M15_SSerial(sSerial);

// the setup routine runs once when you press reset:
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  Serial.println();
  Serial.println();
  Serial.println();
  Serial.println();
  // delay(1000);

  Task_VNEHC_Test1.VNEHC_Serial = &Serial;
  Task_VNEHC_Test1.OutPWR_setup();
  // delay(1000);
  // Task_VNEHC_Test1.delayms(1000);
  if(Task_VNEHC_Test1.checkVolSignal4P_sSerial() != VNEHC_List_Error_None)
  {
    Task_VNEHC_Test1.OutPWR_off();
    Serial.println("\t\tSignal FAIL");
    Serial.println("\t1. ket noi day khong chac (TX - RX)");
    Serial.println("\t2. LDO 3V3 Loi");
    Serial.println("PLEASE RESET FOR NEXT TEST!");
    while(1);
  }
  else
  {
    Serial.println("\t\tSignal GOOD");
  }
  
  Task_VNEHC_Test1.delayms(100);
  pinMode(PIN_PORT4_TX, OUTPUT);
  sSerial.begin(9600);

  // MKE_M15.checkMacAddress();

  uint8_t tempStatus = MKE_M15.setNameWithMacEnd("M0015");
  if(tempStatus && (MKE_M15.strMac.length() == 4))
  {
    Serial.println("Setname OK " + MKE_M15.strMac);
  }
  else
  {
    Serial.println("Setname FAIL");
  }

  Serial.println("PLEASE RESET FOR NEXT TEST!");
  Task_VNEHC_Test1.OutPWR_off();
}

// the loop routine runs over and over again forever:
void loop() {
  // // read the input on analog pin 0:
  checkSerial(&Serial, &sSerial);
  checkSerial(&sSerial, &Serial);

  // // checkSerial(&Serial, &Serial);
  // autoSendAT();
}

void autoSendAT()
{
  static unsigned long lastMillis;

  if(millis() - lastMillis >= 1000)
  {
    lastMillis = millis();

    sSerial.println("AT");
  }
}

// void checkSerial(Stream *in, Stream *out)
// {
//   while(in->available()){
//     out->write(in->read());
//   }
// }


void checkSerial(Stream *in, Stream *out)
{
  if(in->available()){
    String tempCmd = in->readString();
    out->println(tempCmd);
  }
}
