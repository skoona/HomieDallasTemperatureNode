# HomieDallasTemperatureNode
Allow the use of multiple DS18B20 sensors on one bus to be identified and post temperature value on individual channel.

## HomieNode featuring
- DS18B20 Temperature Class with three constructors
    1. HomieNode  - sends multiple sensors temperatures on same channel as JSON
    2. HomieRange - sends single raw value on individual channel_0 ranges
    3. Advanced   - Accepts structure naming the proertie/channels and sensor address to associate

### Usage
1. Run with empty address in last column to discover available sensor addresses.
    - set interval to something short, like 10 seconds.  Log will show address and value every x seconds
    - handle each sensor and note its address and value change.  record the address for each sensor from observance.

2. Edit the structure in main.cpp to populate the address column in the proper order.
    - rebuild and deploy updated firmware; remmeber to set interval back to desired value (10 minutes is good)


### Homie Config

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
