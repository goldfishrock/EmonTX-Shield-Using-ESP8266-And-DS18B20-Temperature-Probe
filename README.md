 OpenEnergyMonitor EmonTx Shield Power Monitor + ESP8266 + DS18B20 Temperature Probe

 Sketch for the OpenEnergyMonitor EmonTX Arduino Shield which monitors
 input CT1 & a single DS18B20 temperature probe and sends the data to an EmonCMS 
 server via an Huzzah ESP8266 WiFi module instead of using the more traditional 
 RFM69CW RF Module
 
 Authored By: Martin Sidgreaves
 Part of the openenergymonitor.org project
 Licence: GNU GPL V3
 
 Builds upon the OneWire, Emonlib & DallasTemperature libraries and Arduino
 
 OpenEnergyMonitor:     http://openenergymonitor.org/
 emonTx documentation: 	http://openenergymonitor.org/emon/modules/emontxshield/


 THIS SKETCH REQUIRES:

 Libraries in the standard arduino libraries folder:

  - EmonLib		          -   https://github.com/openenergymonitor/EmonLib.git
  - DallasTemperature   -   https://github.com/milesburton/Arduino-Temperature-Control-Library
  - OneWire             -   https://github.com/PaulStoffregen/OneWire

------------------------------------------------------------------------------------------------------------
Connections between EmonTX & ESP8266

emonTX Shield UART Header Pin             Huzzah ESP8266 UAT Header

GND                           ->          GND
5v                            ->          V+
Rx                            ->          Rx

-------------------------------------------------------------------------------------------------------------

Version :: v1.0.1
