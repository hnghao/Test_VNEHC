/*
    Wiring:
        Sensor  ------ Arduino Uno
        - P1 ---- to ---- 3
        - P2 ---- to ---- 4 
        - P3 ---- to ---- 5
        - P4 ---- to ---- 6
        - P5 ---- to ---- 7
        - 5V  --- to ----5V
        - GND --- to ----GND
*/

#define PIN_SENSOR_P1   3
#define PIN_SENSOR_P2   4
#define PIN_SENSOR_P3   5
#define PIN_SENSOR_P4   6
#define PIN_SENSOR_P5   7

void setup()
{
    Serial.begin(115200);
    pinMode(PIN_SENSOR_P1, INPUT_PULLUP);
    pinMode(PIN_SENSOR_P2, INPUT_PULLUP);
    pinMode(PIN_SENSOR_P3, INPUT_PULLUP);
    pinMode(PIN_SENSOR_P4, INPUT_PULLUP);
    pinMode(PIN_SENSOR_P5, INPUT_PULLUP);
}

void loop()
{
    /************ SENSOR *************/
    /*-------------------------------*/
    /* |LEFT| P1 P2 P3 P4 P5 |RIGHT| */
    /*     0b 1  1  1  1  1          */
    /*         0: White;             */
    /*         1: Black              */
    /*-------------------------------*/
    Serial.print("P1:");
    Serial.print(digitalRead(PIN_SENSOR_P1));
    Serial.print(" P2:");
    Serial.print(digitalRead(PIN_SENSOR_P2));
    Serial.print(" P3:");
    Serial.print(digitalRead(PIN_SENSOR_P3));
    Serial.print(" P4:");
    Serial.print(digitalRead(PIN_SENSOR_P4));
    Serial.print(" P5:");
    Serial.println(digitalRead(PIN_SENSOR_P5));
    delay(50);
}