# HomieDallasTemperatureNode
<a href="https://homieiot.github.io/">
  <img src="https://homieiot.github.io/img/works-with-homie.png" alt="works with MQTT Homie">
</a>

Allow the use of multiple DS18B20 sensors on one bus to be identified and post temperature values on individual channel.

## HomieNode featuring
- DS18B20 Temperature Class with three constructors
    1. HomieNode  - sends multiple sensors temperatures on same channel as JSON
    2. HomieRange - sends single raw value on individual channel_0 ranges
    3. Advanced   - Accepts structure naming the property/channels and sensor address to associate

### Usage
1. Run with empty address in last column to discover available sensor addresses.
    - set interval to something short, like 10 seconds.  Log will show address and value every x seconds
    - handle each sensor and note its address and value change.  record the address for each sensor from observance.

2. Edit the structure in main.cpp to populate the address column in the proper order.
    - rebuild and deploy updated firmware; remember to set interval back to desired value (10 minutes is good)


## Advanced mode Configuration Structure

### Initial Settings
```
DallasProperties poolRequestUnKnown = {5, 
  { //   add "" empty in the hex address field for as-is assignment           format: 28e20b943c1901a3
    {0, "tempSucPool",   "Pool Suction Temp",  "tempSucPoolState",   "Pool Suction State",  ""},
    {1, "tempRetPool",   "Pool Return Temp",   "tempRetPoolState",   "Pool Return State",   ""},
    {2, "tempSucSpa",    "Pool Suction Temp",  "tempSucSpaState",    "Pool Suction State",  ""},
    {3, "tempRetSpa",    "SPA Return Temp",    "tempRetSpaState",    "SPA Return State",    ""},
    {4, "tempRetHeater", "Heater Return Temp", "tempRetHeaterState", "Heater Return State", ""}
  }
};
```

### Default Console Log
There truely are only 4 sensors online.  However you can have the node read data from a duplicate address to fill in until 5th sensor is available.  You will see this dup in customization model.

```
/*
15:23:17.400 >   ◦ Temperature=74.97 for address=28e20b943c1901a3
15:23:17.414 >   ◦ Temperature=75.43 for address=2866fc543c19015b
15:23:17.427 >   ◦ Temperature=75.31 for address=28f957453c19013a
15:23:17.440 >   ◦ Temperature=74.52 for address=28fd883f3c190164
*/
```

### Customized Settings
```
DallasProperties poolRequest = {5, 
  { //   add the hex addresses in the proper order for EVERY entry                   format: 28e20b943c1901a3
    {0, "tempSucPool",   "Pool Suction Temp",  "tempSucPoolState",   "Pool Suction State",  "2866fc543c19015b"},
    {1, "tempRetPool",   "Pool Return Temp",   "tempRetPoolState",   "Pool Return State",   "28f957453c19013a"},
    {2, "tempSucSpa",    "Pool Suction Temp",  "tempSucSpaState",    "Pool Suction State",  "28e20b943c1901a3"},
    {3, "tempRetSpa",    "SPA Return Temp",    "tempRetSpaState",    "SPA Return State",    "28fd883f3c190164"},
    {4, "tempRetHeater", "Heater Return Temp", "tempRetHeaterState", "Heater Return State", "28f957453c19013a"}
  }
};
```

## Homie Config

```
{
  "name": "Environment Monitor",
  "device_id": "<device-location-name>",
  "device_stats_interval": 900,  
  "wifi": {
    "ssid": "<wifi-host>",
    "password": "<wifi-password>"
  },
  "mqtt": {
    "host": "<mqtt-hostname-or-ip>",
    "port": 1883,
	"base_topic": "sknSensors/",
    "auth": true,
    "username": "<mqtt-username>",
    "password": "<mqtt-password>"
  },
  "ota": {
    "enabled": true
  },
  "settings": {
      "sensorsInterval": 900
    }
}
```

## Homie MQTT Log (Advanced/Customized)
`DallasTemperatureNode environmentMonitor(&poolRequestUnKnown, SKN_NODE_ID, SKN_NODE_TITLE, SKN_NODE_TYPE, PIN_DS_POOL, TEMP_READ_INTERVALL);`
- Node reads multiple sensor and reports to console log the sensors address.
  - using a two step process, set Interval to 10 seconds (in main.cpp), populate structure with address field empty (not Null but ""), build/run collect address from log.
  - handle or heat a sensor and notice the address of the sensor that increased.  ID accomplish
  - edit the structure in main.cpp and add the adresses in the proper sequence, then reset you interval value; rebuild and deploy.
- Node uses structure to read sensors, in the order of the structure: `DallasProperties`.  DallasProperties is defined in `DallasTemperatureNode.hpp`.
- Values are now read in an address sequence defined by the request structure, with hard associations accross reboots.

```
sknSensors/DSMonitor/$state lost
sknSensors/DSMonitor/$state init
sknSensors/DSMonitor/$homie 3.0.1
sknSensors/DSMonitor/$name Environment-DS18B20
sknSensors/DSMonitor/$mac DC:4F:22:3B:33:4F
sknSensors/DSMonitor/$localip 10.100.1.164
sknSensors/DSMonitor/$nodes Ambient
sknSensors/DSMonitor/$stats uptime
sknSensors/DSMonitor/$stats/interval 905
sknSensors/DSMonitor/$fw/name Environment-DS18B20
sknSensors/DSMonitor/$fw/version 1.0.2
sknSensors/DSMonitor/$fw/checksum d37b3f27645b79e80e7b39aa8e9d94fe
sknSensors/DSMonitor/$implementation esp8266
sknSensors/DSMonitor/$implementation/config {"name":"Environment-DS18B20","device_id":"DSMonitor","device_stats_interval":900,"wifi":{"ssid":"SFNSS1-24G"},"mqtt":{"host":"openhab.skoona.net","port":1883,"base_topic":"sknSensors/","auth":true},"ota":{"enabled":true},"settings":{"sensorsInterval":900}}
sknSensors/DSMonitor/$implementation/version 3.0.0
sknSensors/DSMonitor/$implementation/ota/enabled true
sknSensors/DSMonitor/Ambient/$name Environment Monitor
sknSensors/DSMonitor/Ambient/$type sensor
sknSensors/DSMonitor/Ambient/$properties tempSucPoolState,tempSucPool,tempRetPoolState,tempRetPool,tempSucSpaState,tempSucSpa,tempRetSpaState,tempRetSpa,tempRetHeaterState,tempRetHeater
sknSensors/DSMonitor/Ambient/tempSucPoolState/$name Pool Suction State
sknSensors/DSMonitor/Ambient/tempSucPoolState/$datatype enum
sknSensors/DSMonitor/Ambient/tempSucPoolState/$format OK,Error,InvalidAddress
sknSensors/DSMonitor/Ambient/tempSucPool/$name Pool Suction Temp
sknSensors/DSMonitor/Ambient/tempSucPool/$datatype float
sknSensors/DSMonitor/Ambient/tempSucPool/$unit °F
sknSensors/DSMonitor/Ambient/tempRetPoolState/$name Pool Return State
sknSensors/DSMonitor/Ambient/tempRetPoolState/$datatype enum
sknSensors/DSMonitor/Ambient/tempRetPoolState/$format OK,Error,InvalidAddress
sknSensors/DSMonitor/Ambient/tempRetPool/$name Pool Return Temp
sknSensors/DSMonitor/Ambient/tempRetPool/$datatype float
sknSensors/DSMonitor/Ambient/tempRetPool/$unit °F
sknSensors/DSMonitor/Ambient/tempSucSpaState/$name Pool Suction State
sknSensors/DSMonitor/Ambient/tempSucSpaState/$datatype enum
sknSensors/DSMonitor/Ambient/tempSucSpaState/$format OK,Error,InvalidAddress
sknSensors/DSMonitor/Ambient/tempSucSpa/$name Pool Suction Temp
sknSensors/DSMonitor/Ambient/tempSucSpa/$datatype float
sknSensors/DSMonitor/Ambient/tempSucSpa/$unit °F
sknSensors/DSMonitor/Ambient/tempRetSpaState/$name SPA Return State
sknSensors/DSMonitor/Ambient/tempRetSpaState/$datatype enum
sknSensors/DSMonitor/Ambient/tempRetSpaState/$format OK,Error,InvalidAddress
sknSensors/DSMonitor/Ambient/tempRetSpa/$name SPA Return Temp
sknSensors/DSMonitor/Ambient/tempRetSpa/$datatype float
sknSensors/DSMonitor/Ambient/tempRetSpa/$unit °F
sknSensors/DSMonitor/Ambient/tempRetHeaterState/$name Heater Return State
sknSensors/DSMonitor/Ambient/tempRetHeaterState/$datatype enum
sknSensors/DSMonitor/Ambient/tempRetHeaterState/$format OK,Error,InvalidAddress
sknSensors/DSMonitor/Ambient/tempRetHeater/$name Heater Return Temp
sknSensors/DSMonitor/Ambient/tempRetHeater/$datatype float
sknSensors/DSMonitor/Ambient/tempRetHeater/$unit °F
sknSensors/DSMonitor/$state ready

sknSensors/DSMonitor/Ambient/tempSucPool 77.22
sknSensors/DSMonitor/Ambient/tempSucPoolState OK
sknSensors/DSMonitor/Ambient/tempRetPool 76.89
sknSensors/DSMonitor/Ambient/tempRetPoolState OK
sknSensors/DSMonitor/Ambient/tempSucSpa 76.44
sknSensors/DSMonitor/Ambient/tempSucSpaState OK
sknSensors/DSMonitor/Ambient/tempRetSpa 75.99
sknSensors/DSMonitor/Ambient/tempRetSpaState OK
sknSensors/DSMonitor/Ambient/tempRetHeater 76.89
sknSensors/DSMonitor/Ambient/tempRetHeaterState OK

sknSensors/DSMonitor/$stats/interval 905
sknSensors/DSMonitor/$stats/signal 68
sknSensors/DSMonitor/$stats/uptime 5
```

## Homie MQTT Log Basic/JSON)
`DallasTemperatureNode environmentMonitor(SKN_NODE_ID, SKN_NODE_TITLE, SKN_NODE_TYPE, PIN_DS_POOL, TEMP_READ_INTERVALL);`
- Node reads multiple sensor and reports on SINGLE channel consistently during each run.
- Node cannot certify sensorX is always on range_X.  Sensors announce in random order, thus their JSON messages include both an (announce) index and device address.
- Use the Advanced constructor with assignment structure if hard association is required accross reboots.

```
sknSensors/DSMonitor/$state lost
sknSensors/DSMonitor/$state init
sknSensors/DSMonitor/$homie 3.0.1
sknSensors/DSMonitor/$name Environment-DS18B20
sknSensors/DSMonitor/$mac DC:4F:22:3B:33:4F
sknSensors/DSMonitor/$localip 10.100.1.164
sknSensors/DSMonitor/$nodes Ambient
sknSensors/DSMonitor/$stats uptime
sknSensors/DSMonitor/$stats/interval 905
sknSensors/DSMonitor/$fw/name Environment-DS18B20
sknSensors/DSMonitor/$fw/version 1.0.2
sknSensors/DSMonitor/$fw/checksum a979be4d89138f8e65d4bd905d080868
sknSensors/DSMonitor/$implementation esp8266
sknSensors/DSMonitor/$implementation/config {"name":"Environment-DS18B20","device_id":"DSMonitor","device_stats_interval":900,"wifi":{"ssid":"SFNSS1-24G"},"mqtt":{"host":"openhab.skoona.net","port":1883,"base_topic":"sknSensors/","auth":true},"ota":{"enabled":true},"settings":{"sensorsInterval":900}}
sknSensors/DSMonitor/$implementation/version 3.0.0
sknSensors/DSMonitor/$implementation/ota/enabled true
sknSensors/DSMonitor/Ambient/$name Environment Monitor
sknSensors/DSMonitor/Ambient/$type sensor
sknSensors/DSMonitor/Ambient/$properties state,temperature
sknSensors/DSMonitor/Ambient/state/$name State
sknSensors/DSMonitor/Ambient/state/$datatype enum
sknSensors/DSMonitor/Ambient/temperature/$name Temperature
sknSensors/DSMonitor/Ambient/temperature/$datatype string
sknSensors/DSMonitor/Ambient/temperature/$format OK,Error,InvalidAddress
sknSensors/DSMonitor/$state ready
sknSensors/DSMonitor/Ambient/state {"0":{"deviceAddress":"28e20b943c1901a3","State":"OK"}}
sknSensors/DSMonitor/Ambient/temperature {"0":{"deviceAddress":"28e20b943c1901a3","Temperature":73.287498}}
sknSensors/DSMonitor/Ambient/state {"1":{"deviceAddress":"2866fc543c19015b","State":"OK"}}
sknSensors/DSMonitor/Ambient/temperature {"1":{"deviceAddress":"2866fc543c19015b","Temperature":74.187500}}
sknSensors/DSMonitor/Ambient/state {"2":{"deviceAddress":"28f957453c19013a","State":"OK"}}
sknSensors/DSMonitor/Ambient/temperature {"2":{"deviceAddress":"28f957453c19013a","Temperature":73.737503}}
sknSensors/DSMonitor/Ambient/state {"3":{"deviceAddress":"28fd883f3c190164","State":"OK"}}
sknSensors/DSMonitor/Ambient/temperature {"3":{"deviceAddress":"28fd883f3c190164","Temperature":72.837494}}
sknSensors/DSMonitor/$stats/interval 905
sknSensors/DSMonitor/$stats/signal 76
sknSensors/DSMonitor/$stats/uptime 5

-- Interval 1

sknSensors/DSMonitor/Ambient/state {"0":{"deviceAddress":"28e20b943c1901a3","State":"OK"}}
sknSensors/DSMonitor/Ambient/temperature {"0":{"deviceAddress":"28e20b943c1901a3","Temperature":73.287498}}
sknSensors/DSMonitor/Ambient/state {"1":{"deviceAddress":"2866fc543c19015b","State":"OK"}}
sknSensors/DSMonitor/Ambient/temperature {"1":{"deviceAddress":"2866fc543c19015b","Temperature":74.187500}}
sknSensors/DSMonitor/Ambient/state {"2":{"deviceAddress":"28f957453c19013a","State":"OK"}}
sknSensors/DSMonitor/Ambient/temperature {"2":{"deviceAddress":"28f957453c19013a","Temperature":73.737503}}
sknSensors/DSMonitor/Ambient/state {"3":{"deviceAddress":"28fd883f3c190164","State":"OK"}}
sknSensors/DSMonitor/Ambient/temperature {"3":{"deviceAddress":"28fd883f3c190164","Temperature":72.837494}}

-- Interval 2

sknSensors/DSMonitor/Ambient/state {"0":{"deviceAddress":"28e20b943c1901a3","State":"OK"}}
sknSensors/DSMonitor/Ambient/temperature {"0":{"deviceAddress":"28e20b943c1901a3","Temperature":73.287498}}
sknSensors/DSMonitor/Ambient/state {"1":{"deviceAddress":"2866fc543c19015b","State":"OK"}}
sknSensors/DSMonitor/Ambient/temperature {"1":{"deviceAddress":"2866fc543c19015b","Temperature":74.187500}}
sknSensors/DSMonitor/Ambient/state {"2":{"deviceAddress":"28f957453c19013a","State":"OK"}}
sknSensors/DSMonitor/Ambient/temperature {"2":{"deviceAddress":"28f957453c19013a","Temperature":73.849998}}
sknSensors/DSMonitor/Ambient/state {"3":{"deviceAddress":"28fd883f3c190164","State":"OK"}}
sknSensors/DSMonitor/Ambient/temperature {"3":{"deviceAddress":"28fd883f3c190164","Temperature":72.837494}}
```

## Homie MQTT Log (Range/Raw)
#### `DallasTemperatureNode environmentMonitor(SKN_NODE_ID, SKN_NODE_TITLE, SKN_NODE_TYPE, PIN_DS_POOL, TEMP_READ_INTERVALL, true, DTN_RANGE_LOWER, DTN_RANGE_UPPER);`
- Node reads multiple sensor and reports on same channel consistently during each run.
- Node cannot certify sensorX is always on range_X.  Sensors announce in random order, thus their announce sequence is reflected by the range_x suffix. Which is subject to change after a reboot.
- Use the Advanced constructor with assignment structure if hard association is required accross reboots.

```
sknSensors/DSMonitor/$state lost
sknSensors/DSMonitor/$state init
sknSensors/DSMonitor/$homie 3.0.1
sknSensors/DSMonitor/$name Environment-DS18B20
sknSensors/DSMonitor/$mac DC:4F:22:3B:33:4F
sknSensors/DSMonitor/$localip 10.100.1.164
sknSensors/DSMonitor/$nodes Ambient[]
sknSensors/DSMonitor/$stats uptime
sknSensors/DSMonitor/$stats/interval 905
sknSensors/DSMonitor/$fw/name Environment-DS18B20
sknSensors/DSMonitor/$fw/version 1.0.2
sknSensors/DSMonitor/$fw/checksum 93341625d6fa5d9533e6e315fbdde634
sknSensors/DSMonitor/$implementation esp8266
sknSensors/DSMonitor/$implementation/config {"name":"Environment-DS18B20","device_id":"DSMonitor","device_stats_interval":900,"wifi":{"ssid":"SFNSS1-24G"},"mqtt":{"host":"openhab.skoona.net","port":1883,"base_topic":"sknSensors/","auth":true},"ota":{"enabled":true},"settings":{"sensorsInterval":900}}
sknSensors/DSMonitor/$implementation/version 3.0.0
sknSensors/DSMonitor/$implementation/ota/enabled true
sknSensors/DSMonitor/Ambient/$name Environment Monitor
sknSensors/DSMonitor/Ambient/$type sensor
sknSensors/DSMonitor/Ambient/$array 0-3
sknSensors/DSMonitor/Ambient_0/$name Ambient_0
sknSensors/DSMonitor/Ambient_1/$name Ambient_1
sknSensors/DSMonitor/Ambient_2/$name Ambient_2
sknSensors/DSMonitor/Ambient_3/$name Ambient_3
sknSensors/DSMonitor/Ambient/$properties state,temperature
sknSensors/DSMonitor/Ambient/state/$name State
sknSensors/DSMonitor/Ambient/state/$datatype enum
sknSensors/DSMonitor/Ambient/state/$format OK,Error,InvalidAddress
sknSensors/DSMonitor/Ambient/temperature/$name Temperature
sknSensors/DSMonitor/Ambient/temperature/$datatype float
sknSensors/DSMonitor/Ambient/temperature/$unit °F
sknSensors/DSMonitor/$state ready
sknSensors/DSMonitor/Ambient_0/state OK
sknSensors/DSMonitor/Ambient_0/temperature 73.06
sknSensors/DSMonitor/Ambient_1/state OK
sknSensors/DSMonitor/Ambient_1/temperature 74.07
sknSensors/DSMonitor/Ambient_2/state OK
sknSensors/DSMonitor/Ambient_2/temperature 73.63
sknSensors/DSMonitor/Ambient_3/state OK
sknSensors/DSMonitor/Ambient_3/temperature 72.39
sknSensors/DSMonitor/$stats/interval 905
sknSensors/DSMonitor/$stats/signal 80
sknSensors/DSMonitor/$stats/uptime 5

-- Cycle 1

sknSensors/DSMonitor/Ambient_0/state OK
sknSensors/DSMonitor/Ambient_0/temperature 73.06
sknSensors/DSMonitor/Ambient_1/state OK
sknSensors/DSMonitor/Ambient_1/temperature 74.07
sknSensors/DSMonitor/Ambient_2/state OK
sknSensors/DSMonitor/Ambient_2/temperature 73.74
sknSensors/DSMonitor/Ambient_3/state OK
sknSensors/DSMonitor/Ambient_3/temperature 72.39

-- Cycle 2

sknSensors/DSMonitor/Ambient_0/state OK
sknSensors/DSMonitor/Ambient_0/temperature 73.06
sknSensors/DSMonitor/Ambient_1/state OK
sknSensors/DSMonitor/Ambient_1/temperature 73.96
sknSensors/DSMonitor/Ambient_2/state OK
sknSensors/DSMonitor/Ambient_2/temperature 73.63
sknSensors/DSMonitor/Ambient_3/state OK
sknSensors/DSMonitor/Ambient_3/temperature 72.39
```