/*
    Wiring:
        Sensor  ------ Arduino Uno
        - SDA --- to ----A4
        - SCL --- to ----A5
        - 5V  --- to ----5V
        - GND --- to ----GND
*/
#include "kxnTaskShowValueSensor.h"

kxnTaskShowValueSensor kxnTaskShowValueSensor1;

void setup()
{
    kxnTaskShowValueSensor1.setup();
}

void loop()
{
    kxnTaskManager.run(millis());
}