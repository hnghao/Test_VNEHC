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

void setup()
{
    Serial.begin(115200);
    LineFollowSensor.setup(0x2A);
}

void loop()
{
    /************ SENSOR *************/
    /*-------------------------------*/
    /* |LEFT| P1 P2 P3 P4 P5 |RIGHT| */
    /*   White -> Black : (0->255)   */
    /*-------------------------------*/
    LineFollowSensor.getData();
    
    Serial.print("P1:");
    Serial.print(LineFollowSensor.getRawValue(0));
    Serial.print(" P2:");
    Serial.print(LineFollowSensor.getRawValue(1));
    Serial.print(" P3:");
    Serial.print(LineFollowSensor.getRawValue(2));
    Serial.print(" P4:");
    Serial.print(LineFollowSensor.getRawValue(3));
    Serial.print(" P5:");
    Serial.print(LineFollowSensor.getRawValue(4));

    Serial.print(" data:");
    Serial.println(LineFollowSensor.getValue(), BIN);
    
    
    delay(50);
}