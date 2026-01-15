#pragma once

#ifndef __Makerlabvn_I2C_Line_Follower_Sensor_H__
#define __Makerlabvn_I2C_Line_Follower_Sensor_H__

#include "kxnTask.h"
#include <Wire.h>
#include <Arduino.h>

#define SENSOR_ADDRESS 0x2A
#define MAKERLABVN_I2C_LINE_FOLLOWER_SENSOR_BUFFER_SIZE 11

CREATE_TASK(Makerlabvn_I2C_Line_Follower_Sensor)

void setup(uint8_t paAddress = SENSOR_ADDRESS, uint8_t paCountSensor = 5);
void setBlack()
{
    isBlack = 1;
}

void setWhite()
{
    isBlack = 0;
}
void loop();
void getData();
uint8_t getValue(uint8_t index);
uint8_t getValue();
uint8_t getRawValue(uint8_t index);
uint8_t getThresHoldValue(uint8_t index);
void setI2C_Address(uint8_t paAdd);

private:
uint8_t readValue[MAKERLABVN_I2C_LINE_FOLLOWER_SENSOR_BUFFER_SIZE] = {0, 0, 0, 0, 0};
uint8_t countSensor;
uint8_t address;
uint8_t isBlack;

END

#endif