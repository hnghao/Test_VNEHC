/**
 * MKE_M15 Bluetooth Module JDY-33 Class Library
 * Copyright (c) 2021 MakerLab VN.  All right reserved.
 * MIT License.
 *    MKE_M15_setup_h_260116
 *      - add function checkMacAddress to get last 4 characters of MAC Address
 *      - add function setNameWithMacEnd to set name with last 4 characters of MAC Address
 *        - e.g: setNameWithMacEnd("MKE-M15") -> "MKE-M15_7AE8"
 */
#ifndef MKE_M15_setup_h
#define MKE_M15_setup_h
#include "Arduino.h"
// https://bitbucket.org/makerlap_team/bluetooth_jdy33_setup
/*

MKE_M15_HSerial(Serial);

void setup(){
  // PCSerial.begin(9600);
  
  MKE_M15.setBaudrate(115200);
  MKE_M15.setName("MKE-M15_2");

  // unsigned long baudValue = jdy33.scanBaud();
  // PCSerial.print(F("JDY33 Baudrate: "));
  // PCSerial.println(baudValue);
}

*/

#define MKE_M15_HSerial(x) jdy33_class<HardwareSerial> MKE_M15(&x)
#define MKE_M15_SSerial(x) jdy33_class<SoftwareSerial> MKE_M15(&x)

typedef struct
{
  unsigned long baudrate;
  uint8_t baudrateID;
} jdy33_info_Struct;

extern jdy33_info_Struct jdy33_baudTable[];
extern uint16_t jdy33_sizeBaudTable;

template <typename T>
class jdy33_class
{
private:
  /* data */
  T *myp_Serial;
  unsigned long baudRate;
  

public:
  String strLog;
  String strMac;

  jdy33_class(T *pSerial_)
  {
    myp_Serial = pSerial_;
  }
  ~jdy33_class() {}

  bool sendCommand(String pa_StrCM, String pa_StrCondition){
    unsigned long timeWaitRespond_ms = 200;
    unsigned long tempCurrentTime = 0;
    uint8_t tempLenStrCondition = pa_StrCondition.length();
    String tempStrRespond = "";

    this->strLog = "";

    while(this->myp_Serial->available()){
      this->myp_Serial->read(); 
    }
    this->myp_Serial->println(pa_StrCM);
    this->myp_Serial->println(pa_StrCM);
    tempCurrentTime = millis();

    while(this->myp_Serial->available() < tempLenStrCondition){
      if((millis() - tempCurrentTime) >= timeWaitRespond_ms) return false;
      delay(10);
    }

    while(this->myp_Serial->available()){
      char tempChar = this->myp_Serial->read();
      tempStrRespond = tempStrRespond + tempChar;
    }
    this->strLog = tempStrRespond;
    // Serial.println("CMD debug: " + pa_StrCM);
    // Serial.println(this->strLog);
    if(tempStrRespond.indexOf(pa_StrCondition) > -1){
      return true;
    }
    return false;
  }

  bool setDisconnect(){
    if(!this->sendCommand("AT+DISC", "OK")){   // first time fail
      delay(100);
      return this->sendCommand("AT+DISC", "OK");  // Try the second time
    }else{
      return true;
    }
  }

  bool restart(){
    if(!this->sendCommand("AT+RESET", "OK")){   // first time fail
      delay(100);
      return this->sendCommand("AT+RESET", "OK");  // Try the second time
    }else{
      return true;
    }
  }

  unsigned long scanBaud(){
    if(this->baudRate != 0){
      this->myp_Serial->begin(this->baudRate);
      if(this->setDisconnect()){
        return this->baudRate;
      }
    }

    this->baudRate = 0;

    for (int cf = 0; cf < jdy33_sizeBaudTable; cf++)
    {
      this->myp_Serial->begin(jdy33_baudTable[cf].baudrate);

      if(this->setDisconnect()){
        this->baudRate = jdy33_baudTable[cf].baudrate;
        return this->baudRate;
      }
    }    
    return this->baudRate;
  }

  bool setBaudrate(unsigned long pa_ulBaud){
    this->myp_Serial->begin(pa_ulBaud);

    if(this->setDisconnect()){
      this->baudRate = pa_ulBaud;
      return true;
    }

    // if(this->sendCommand("AT+DISC", "OK")){
    //   return true;
    // }

    unsigned long tempBaud = this->scanBaud();
    this->myp_Serial->begin(tempBaud);

    if(tempBaud == 0){
      // return false;
    }else;
    
    for (int cf = 0; cf < jdy33_sizeBaudTable; cf++)
    {
      if(jdy33_baudTable[cf].baudrate == pa_ulBaud){
        if(this->sendCommand("AT+BAUD"+ String(jdy33_baudTable[cf].baudrateID), "OK")) {
          this->baudRate = pa_ulBaud;
          return true; 
        }else{
          if(this->restart()) {
            return true;
          }
        }
      }
      
    }
    return false;
  }

  bool setName(String pa_strName){  // max 12 character in "+NAME=123456789012"
    int tempLen = pa_strName.length();
    // String tempString = pa_strName.substring(0,min(11, (int)pa_strName.length()));
    String tempString = pa_strName.substring(0,min(11, tempLen));
    if(this->baudRate != 0){
      this->myp_Serial->begin(this->baudRate);
      this->setDisconnect();
    }
    else
      this->scanBaud();
    
    if(this->baudRate != 0){
        if(this->sendCommand("AT+NAME", tempString)){
          int tempLen = this->strLog.length();
          // tempLen = (tempLen - 16)/2;
          // if(tempString.length() == tempLen){
          //   return true;
          // }
          // Serial.println(F("KXN read name OK!"));
          // Serial.println(tempString);
          // Serial.println(this->strLog);

          return true; // Y260116 KXN DEBUG
        }
        Serial.println(this->strLog);

        this->sendCommand("AT+NAME"+tempString, "+OK");
        
        String tempStringNameBLE = "AT+NAMB"+tempString+"_BLE";
        
        if(this->sendCommand(tempStringNameBLE, "+OK")){
            this->restart();
            return true;
        }
    }
    this->restart();
    return false;
  }

  /*
    checkMacAddress: 
      - cmd: AT+LADDR
      - result: +LADDR=AAAA16047AE8
      - strMac = "7AE8"
   */
  bool checkMacAddress(){
    if(this->baudRate != 0){
      this->myp_Serial->begin(this->baudRate);
      this->setDisconnect();
    }
    else
      this->scanBaud();
    
    if(this->baudRate != 0){
        // if(this->sendCommand("AT+LADDR", "+LADDR=")){
          // int indexStart = this->strLog.indexOf("+LADDR=") + 15;
          // this->strMac = this->strLog.substring(indexStart, indexStart + 4);
        if(this->sendCommand("AT+LADDR", "AAA")){
          int indexStart = this->strLog.indexOf("AAA") + 8;
          this->strMac = this->strLog.substring(indexStart, indexStart + 4);

          // Serial.print(F("JDY33 MAC Address End: "));
          // Serial.print(indexStart);
          // Serial.print(F("\t"));
          // Serial.println(this->strMac);
          // Serial.println(this->strLog);
          return true;
        }
        else{
          Serial.println(this->strLog);
        }
        
    }
    return false;
  }

  bool setNameWithMacEnd(String pa_strName){  // max 12-4 character in "+NAME=123456789012"
    delay(100);
    this->checkMacAddress();
    String tempString = pa_strName.substring(0,min(7, (int)pa_strName.length()));
    tempString = tempString + "_" + this->strMac;
    // String tempString = pa_strName + "_" + this->strMac;
    return this->setName(tempString);
  }
};

// extern jdy33_class<HardwareSerial> MKE_M15;

#endif
