/*
  AnalogReadSerial

  Reads an analog input on pin 0, prints the result to the Serial Monitor.
  Graphical representation is available using Serial Plotter (Tools > Serial Plotter menu).
  Attach the center pin of a potentiometer to pin A0, and the outside pins to +5V and ground.

  This example code is in the public domain.

  https://www.arduino.cc/en/Tutorial/BuiltInExamples/AnalogReadSerial
*/

#include "SoftwareSerial.h"

SoftwareSerial sSerial(A4, A5);

// the setup routine runs once when you press reset:
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  delay(1000);
  checkAnalog();
  checkAnalog();
  checkAnalog();
  checkAnalog();
  checkAnalog();
  sSerial.begin(9600);
}

// the loop routine runs over and over again forever:
void loop() {
  // read the input on analog pin 0:
  // checkSerial(&Serial, &sSerial);
  // checkSerial(&sSerial, &Serial);

  checkSerial(&Serial, &Serial);
  autoSendAT();
}

void autoSendAT()
{
  static unsigned long lastMillis;

  if(millis() - lastMillis >= 1000)
  {
    lastMillis = millis();

    Serial.println("AT");
  }
}

void checkSerial(Stream *in, Stream *out)
{
  while(in->available()){
    out->write(in->read());
  }
}

void checkAnalog()
{
  // static unsigned long lastMillis;

  // if(millis() - lastMillis >= 1000)
  // {
  //   lastMillis = millis();
  pinMode(A4, INPUT);
  pinMode(A5, INPUT);
  delay(100);

    int sensorValue = analogRead(A4);
    int sensorValue2 = analogRead(A5);
    // print out the value you read:
    Serial.print(sensorValue);
    Serial.print("\t");
    Serial.println(sensorValue2);
    delay(100);  // delay in between reads for stability
  // }
  
}
