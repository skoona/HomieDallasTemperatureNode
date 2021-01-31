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
#define SKN_MOD_VERSION "1.0.2"
#define SKN_MOD_BRAND "SknSensors"
#define SKN_NODE_TITLE "Environment Monitor"
#define SKN_NODE_TYPE "sensor"
#define SKN_NODE_ID "Ambient" // "environmentMonitor"

/*
15:23:17.400 >   ◦ Temperature=74.97 for address=28e20b943c1901a3
15:23:17.414 >   ◦ Temperature=75.43 for address=2866fc543c19015b
15:23:17.427 >   ◦ Temperature=75.31 for address=28f957453c19013a
15:23:17.440 >   ◦ Temperature=74.52 for address=28fd883f3c190164
*/
DallasProperties poolRequestUnKnown = {5, 
  { //   add "" empty in the hex address field for as-is assignment           format: 28e20b943c1901a3
    {0, "tempSucPool",   "Pool Suction Temp",  "tempSucPoolState",   "Pool Suction State",  ""},
    {1, "tempRetPool",   "Pool Return Temp",   "tempRetPoolState",   "Pool Return State",   ""},
    {2, "tempSucSpa",    "Pool Suction Temp",  "tempSucSpaState",    "Pool Suction State",  ""},
    {3, "tempRetSpa",    "SPA Return Temp",    "tempRetSpaState",    "SPA Return State",    ""},
    {4, "tempRetHeater", "Heater Return Temp", "tempRetHeaterState", "Heater Return State", ""}
  }
};

DallasProperties poolRequest = {5, 
  { //   add the hex addresses in the proper order for EVERY entry                   format: 28e20b943c1901a3
    {0, "tempSucPool",   "Pool Suction Temp",  "tempSucPoolState",   "Pool Suction State",  "2866fc543c19015b"},
    {1, "tempRetPool",   "Pool Return Temp",   "tempRetPoolState",   "Pool Return State",   "28f957453c19013a"},
    {2, "tempSucSpa",    "Pool Suction Temp",  "tempSucSpaState",    "Pool Suction State",  "28e20b943c1901a3"},
    {3, "tempRetSpa",    "SPA Return Temp",    "tempRetSpaState",    "SPA Return State",    "28fd883f3c190164"},
    {4, "tempRetHeater", "Heater Return Temp", "tempRetHeaterState", "Heater Return State", "28f957453c19013a"}
  }
};

const uint8_t DTN_RANGE_LOWER = 0;
const uint8_t DTN_RANGE_UPPER     = 3;
const uint8_t PIN_DS_POOL         = D4; // Pin of Temp-Sensor Pool
const uint8_t TEMP_READ_INTERVALL = 30;

HomieSetting<long> sensorsIntervalSetting("sensorInterval", "The interval in seconds to wait between sending commands.");

DallasTemperatureNode environmentMonitor(&poolRequestUnKnown, SKN_NODE_ID, SKN_NODE_TITLE, SKN_NODE_TYPE, PIN_DS_POOL, TEMP_READ_INTERVALL);
// DallasTemperatureNode environmentMonitor(SKN_NODE_ID, SKN_NODE_TITLE, SKN_NODE_TYPE, PIN_DS_POOL, TEMP_READ_INTERVALL);
// DallasTemperatureNode environmentMonitor(SKN_NODE_ID, SKN_NODE_TITLE, SKN_NODE_TYPE, PIN_DS_POOL, TEMP_READ_INTERVALL, true, DTN_RANGE_LOWER, DTN_RANGE_UPPER);

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

  sensorsIntervalSetting.setDefaultValue(900).setValidator([](long candidate) {
    return (candidate >= 100) && (candidate <= 3000);
  });

  environmentMonitor.setMeasurementInterval(sensorsIntervalSetting.get());
  // environmentMonitor.setMeasurementInterval(10);

      Homie.setBroadcastHandler(broadcastHandler)
          .setup();
}

void loop() {
  Homie.loop();
}
