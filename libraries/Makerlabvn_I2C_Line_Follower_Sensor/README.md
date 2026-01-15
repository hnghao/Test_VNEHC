# Arduino_Library_Template

## Introduction

The Makerlabvn_I2C_Line_Follower_Sensor library allows you to interface with the Makerlabvn I2C Line Follower Sensor using Arduino. This sensor helps in detecting lines on the ground, which is useful for line-following robots.

## Installation

1. Open the Arduino IDE.
2. Go to `Sketch` > `Include Library` > `Manage Libraries...`.
3. In the Library Manager, search for `Makerlabvn_I2C_Line_Follower_Sensor`.
4. Click on the library and install it.

## Usage

Here is a simple example to get you started:

```cpp
/*
    File: I2C_Line_Follower_Sensor_Serial_Basic_5_Digital
    Wiring:
        Sensor  ------ Arduino Uno
        - P1 ---- to ---- 3
        - P2 ---- to ---- 4 
        - P3 ---- to ---- 5
        - P4 ---- to ---- 6
        - P5 ---- to ---- 7
        - 5V  --- to ---- 5V
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
```

```cpp
/*
    File: I2C_Line_Follower_Sensor_Serial_Basic
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
    /*     0b 1  1  1  1  1          */
    /*         0: White;             */
    /*         1: Black              */
    /*-------------------------------*/
    LineFollowSensor.getData();
    
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

    Serial.print(" data:");
    Serial.println(LineFollowSensor.getValue(), BIN);
    
    
    delay(50);
}
```

## API Reference

### `void setup(uint8_t address)`

Initializes the sensor with the specified I2C address.

- **Parameters:**
    - `address` (uint8_t): The I2C address of the sensor. (From 0x2A to 0x2E), setup by Double-Click then Long Press button S1 on the sensor

### `void getData()`

Reads the sensor data and updates the internal state.

### `uint8_t getValue(uint8_t position)`

Returns the value of the sensor at the specified position.

- **Parameters:**
    - `position` (uint8_t): The position of the sensor (0 to 4).

- **Returns:**
    - `uint8_t`: The value of the sensor at the specified position (0 for white, 1 for black).

### `uint8_t getValue()`

Returns the combined value of all sensors as a single byte.

- **Returns:**
    - `uint8_t`: The combined value of all sensors in binary format.

## License

This library is licensed under the MIT License. See the `LICENSE` file for more details.

## Contributing

Contributions are welcome! Please open an issue or submit a pull request on GitHub.

## Contact

For any questions or feedback, please contact [contact.makerlabvn@gmail.com](mailto:contact.makerlabvn@gmail.com).