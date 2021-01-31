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
```
sknSensors/DSMonitor/$state lost
sknSensors/DSMonitor/$state init
sknSensors/DSMonitor/$homie 3.0.1
sknSensors/DSMonitor/$name Environment-DS18B20
sknSensors/DSMonitor/$mac DC:4F:22:3B:33:4F
sknSensors/DSMonitor/$localip 10.100.1.164
sknSensors/DSMonitor/$nodes DS18B20
sknSensors/DSMonitor/$stats uptime
sknSensors/DSMonitor/$stats/interval 905
sknSensors/DSMonitor/$fw/name Environment-DS18B20
sknSensors/DSMonitor/$fw/version 1.0.2
sknSensors/DSMonitor/$fw/checksum b749ba42c2bf7becf74dd0d98fab2e54
sknSensors/DSMonitor/$implementation esp8266
sknSensors/DSMonitor/$implementation/config {"name":"Environment-DS18B20","device_id":"DSMonitor","device_stats_interval":900,"wifi":{"ssid":"SFNSS1-24G"},"mqtt":{"host":"openhab.skoona.net","port":1883,"base_topic":"sknSensors/","auth":true},"ota":{"enabled":true},"settings":{"sensorsInterval":900}}
sknSensors/DSMonitor/$implementation/version 3.0.0
sknSensors/DSMonitor/$implementation/ota/enabled true
sknSensors/DSMonitor/DS18B20/$name Environment Monitor
sknSensors/DSMonitor/DS18B20/$type sensor
sknSensors/DSMonitor/DS18B20/$properties tempSucPoolState,tempSucPool,tempRetPoolState,tempRetPool,tempSucSpaState,tempSucSpa,tempRetSpaState,tempRetSpa,tempRetHeaterState,tempRetHeater
sknSensors/DSMonitor/DS18B20/tempSucPoolState/$name Pool Suction State
sknSensors/DSMonitor/DS18B20/tempSucPoolState/$datatype string
sknSensors/DSMonitor/DS18B20/tempSucPoolState/$format OK,Error,InvalidAddress
sknSensors/DSMonitor/DS18B20/tempSucPool/$name Pool Suction Temp
sknSensors/DSMonitor/DS18B20/tempSucPool/$datatype float
sknSensors/DSMonitor/DS18B20/tempSucPool/$unit °F
sknSensors/DSMonitor/DS18B20/tempRetPoolState/$name Pool Return State
sknSensors/DSMonitor/DS18B20/tempRetPoolState/$datatype string
sknSensors/DSMonitor/DS18B20/tempRetPoolState/$format OK,Error,InvalidAddress
sknSensors/DSMonitor/DS18B20/tempRetPool/$name Pool Return Temp
sknSensors/DSMonitor/DS18B20/tempRetPool/$datatype float
sknSensors/DSMonitor/DS18B20/tempRetPool/$unit °F
sknSensors/DSMonitor/DS18B20/tempSucSpaState/$name Pool Suction State
sknSensors/DSMonitor/DS18B20/tempSucSpaState/$datatype string
sknSensors/DSMonitor/DS18B20/tempSucSpaState/$format OK,Error,InvalidAddress
sknSensors/DSMonitor/DS18B20/tempSucSpa/$name Pool Suction Temp
sknSensors/DSMonitor/DS18B20/tempSucSpa/$datatype float
sknSensors/DSMonitor/DS18B20/tempSucSpa/$unit °F
sknSensors/DSMonitor/DS18B20/tempRetSpaState/$name SPA Return State
sknSensors/DSMonitor/DS18B20/tempRetSpaState/$datatype string
sknSensors/DSMonitor/DS18B20/tempRetSpaState/$format OK,Error,InvalidAddress
sknSensors/DSMonitor/DS18B20/tempRetSpa/$name SPA Return Temp
sknSensors/DSMonitor/DS18B20/tempRetSpa/$datatype float
sknSensors/DSMonitor/DS18B20/tempRetSpa/$unit °F
sknSensors/DSMonitor/DS18B20/tempRetHeaterState/$name Heater Return State
sknSensors/DSMonitor/DS18B20/tempRetHeaterState/$datatype string
sknSensors/DSMonitor/DS18B20/tempRetHeaterState/$format OK,Error,InvalidAddress
sknSensors/DSMonitor/DS18B20/tempRetHeater/$name Heater Return Temp
sknSensors/DSMonitor/DS18B20/tempRetHeater/$datatype float
sknSensors/DSMonitor/DS18B20/tempRetHeater/$unit °F
sknSensors/DSMonitor/$state ready
sknSensors/DSMonitor/DS18B20/tempSucPool 75.88
sknSensors/DSMonitor/DS18B20/tempSucPoolState OK
sknSensors/DSMonitor/DS18B20/tempRetPool 75.54
sknSensors/DSMonitor/DS18B20/tempRetPoolState OK
sknSensors/DSMonitor/DS18B20/tempSucSpa 75.09
sknSensors/DSMonitor/DS18B20/tempSucSpaState OK
sknSensors/DSMonitor/DS18B20/tempRetSpa 74.30
sknSensors/DSMonitor/DS18B20/tempRetSpaState OK
sknSensors/DSMonitor/DS18B20/tempRetHeater 75.54
sknSensors/DSMonitor/DS18B20/tempRetHeaterState OK
sknSensors/DSMonitor/$stats/interval 905
sknSensors/DSMonitor/$stats/signal 82
sknSensors/DSMonitor/$stats/uptime 5

```