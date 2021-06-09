 ### OpenEnergyMonitor EmonTx Shield Power Monitor + ESP8266 + DS18B20 Temperature Probe

 Sketch for the OpenEnergyMonitor EmonTX Arduino Shield which monitors
 input CT1 & a single DS18B20 temperature probe and sends the data to an EmonCMS 
 server via an Huzzah ESP8266 WiFi module instead of using the more traditional 
 RFM69CW RF Module. The ESP8266 is running the EmonESP firmware.
 
 Authored By: Martin Sidgreaves
 Part of the openenergymonitor.org project
 Licence: GNU GPL V3
 
 Builds upon the OneWire, Emonlib & DallasTemperature libraries and Arduino
 
 __OpenEnergyMonitor:__     http://openenergymonitor.org/

 __emonTx documentation:__ 	http://openenergymonitor.org/emon/modules/emontxshield/

 __emonESP Firmware:__      https://github.com/openenergymonitor/EmonESP  </br></br>
 
 



 #### THIS SKETCH REQUIRES:

 Libraries in the standard arduino libraries folder:

  - __EmonLib__		           -   https://github.com/openenergymonitor/EmonLib.git

  - __DallasTemperature__   -   https://github.com/milesburton/Arduino-Temperature-Control-Library

  - __OneWire__             -   https://github.com/PaulStoffregen/OneWire

  Also included in the '3D Printed Enclosure' folder is a  .STL file and the original Fustion 360 file for an 
  enclosure I designed to house the Arduino & Shield. The hole in the side was incorporated to allow for a DS18B20
  probe to be added.

------------------------------------------------------------------------------------------------------------
Connections between EmonTX & ESP8266

**_emonTX Shield UART Header Pin &nbsp;&nbsp;&nbsp;&nbsp;->&nbsp;&nbsp;&nbsp;&nbsp; Huzzah ESP8266 UAT Header_**

&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;GND&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;->&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;GND

&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;5v&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;->&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;V+

&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;Rx&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;->&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;Rx

-------------------------------------------------------------------------------------------------------------

Version :: v1.0.2
