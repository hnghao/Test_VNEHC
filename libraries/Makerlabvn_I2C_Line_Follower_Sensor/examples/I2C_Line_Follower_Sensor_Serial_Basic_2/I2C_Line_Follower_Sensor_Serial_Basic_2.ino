/*
    Wiring:
        Sensor  ------ Arduino Uno
        - SDA --- to ----A4
        - SCL --- to ----A5
        - 5V  --- to ----5V
        - GND --- to ----GND
*/
#include "Makerlabvn_I2C_Line_Follower_Sensor.h"

Makerlabvn_I2C_Line_Follower_Sensor LineFollowSensor;
Makerlabvn_I2C_Line_Follower_Sensor LineFollowSensor2;

void setup()
{
    Serial.begin(115200);
    LineFollowSensor.setup(0x2A);
    LineFollowSensor2.setup(0x2B);
}

void loop()
{
    /************ SENSOR **********************************************/
    /*-------------0x2A-----------------------------0x2B--------------*/
    /* |LEFT| P1 P2 P3 P4 P5 |RIGHT|   |LEFT| P1 P2 P3 P4 P5 |RIGHT|  */
    /*     0b 1  1  1  1  1                0b 1  1  1  1  1           */
    /*         0: White;                       0: White;              */
    /*         1: Black                        1: Black               */
    /*----------------------------------------------------------------*/
    LineFollowSensor.getData();
    LineFollowSensor2.getData();
    
    ShowValue();
}

void ShowValue(){
    static unsigned long tempLastTime = 0;
    if(millis() - tempLastTime > 100){
        tempLastTime = millis();
        Serial.print("P1:");
        Serial.print(LineFollowSensor.getValue(0));
        Serial.print(" P2:");
        Serial.print(LineFollowSensor.getValue(1));
        Serial.print(" P3:");
        Serial.print(LineFollowSensor.getValue(2));
        Serial.print(" P4:");
        Serial.print(LineFollowSensor.getValue(3));
        Serial.print(" P5:");
        Serial.print(LineFollowSensor.getValue(4));

        Serial.print(" P12:");
        Serial.print(LineFollowSensor2.getValue(0));
        Serial.print(" P22:");
        Serial.print(LineFollowSensor2.getValue(1));
        Serial.print(" P32:");
        Serial.print(LineFollowSensor2.getValue(2));
        Serial.print(" P42:");
        Serial.print(LineFollowSensor2.getValue(3));
        Serial.print(" P52:");
        Serial.println(LineFollowSensor2.getValue(4));
        
    }
}