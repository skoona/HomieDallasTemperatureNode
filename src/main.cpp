/**
 * @file main.cpp
 * @author James Scott, Jr.  aka(Skoona) (skoona@gmail.com)
 * @brief HomieNode featuring an DS18B20 Temperature Class, 
 *        using HomeNode and/or HomieRange methods.
 * @version 1.0.0
 * @date 2021-01-28
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include <Arduino.h>
#include <Homie.h>
#include "DallasTemperatureNode.hpp"

#ifdef ESP8266
extern "C"
{
#include "user_interface.h" // to set CPU Freq for Non-Huzzah's
}
#endif

/*
 * SKN_NODE_ID becomes the base name when ranges are used
 * ex: sknSensors/deviceName/DS18B20_0/temperature -> 72.3 degress
 * Note: HomieNode(...range,lower,upper) manages this array suffix change; i.e no more name fixups
*/
#define SKN_MOD_NAME "Environment-DS18B20"
#define SKN_MOD_VERSION "1.0.1"
#define SKN_MOD_BRAND "SknSensors"
#define SKN_MOD_TITLE "Environment Monitor"
#define SKN_NODE_ID "DS18B20" // "environmentMonitor"

const uint8_t DTN_RANGE_LOWER = 0;
const uint8_t DTN_RANGE_UPPER = 3;
const uint8_t PIN_DS_POOL = D4; // Pin of Temp-Sensor Pool
const uint8_t TEMP_READ_INTERVALL = 30;

DallasTemperatureNode environmentMonitor(SKN_NODE_ID, SKN_MOD_TITLE, PIN_DS_POOL, TEMP_READ_INTERVALL); //, true, DTN_RANGE_LOWER, DTN_RANGE_UPPER);

bool broadcastHandler(const String &level, const String &value)
{
  Homie.getLogger() << "Received broadcast level " << level << ": " << value << endl;
  return true;
}

void setup() {
  delay(50);
  Serial.begin(115200);
  Serial << endl
         << endl;

  Homie_setFirmware(SKN_MOD_NAME, SKN_MOD_VERSION);
  Homie_setBrand(SKN_MOD_BRAND);

  Homie.setBroadcastHandler(broadcastHandler)
       .setup();
}

void loop() {
  Homie.loop();
}
