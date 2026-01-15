#ifndef taskCheckVoltSig_h
#define taskCheckVoltSig_h

#include "kxnTask.h"
#include "kxnSetting.h"

CREATE_TASK(taskCheckVoltSig)

uint8_t flagError;
int value[6];
void setup()
{

}

void checkAnalogA4A5()
{
  // static unsigned long lastMillis;

  // if(millis() - lastMillis >= 1000)
  // {
  //   lastMillis = millis();
  pinMode(A4, INPUT);
  pinMode(A5, INPUT);
  delay(10);

    int sensorValue = analogRead(A4);
    int sensorValue2 = analogRead(A5);
    // print out the value you read:
    Serial.print(sensorValue);
    Serial.print("\t");
    Serial.println(sensorValue2);
    delay(100);  // delay in between reads for stability
  // }
  
}

int checkAnalogA1()
{
  int tempValue = 1;
  pinMode(A1, INPUT);
  
  delay(10);

    int sensorValue = analogRead(A1);
    // print out the value you read:
    Serial.println(sensorValue);
    if(sensorValue >= SAFE_ADC_VALUE_3V3)
    {
      Serial.println(ERROR_VOLT_SIG_3V3);
      tempValue = 0;

    }
    return tempValue;
}
END
#endif