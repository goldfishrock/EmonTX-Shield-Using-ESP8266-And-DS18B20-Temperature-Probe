/*
 OpenEnergyMonitor EmonTx Shield ESP8266 Power Monitor & Temperature Monitor
 
 Sketch for the OpenEnergyMonitor EmonTX Arduino Shield which monitors
 input CT1 & a single DS18B20 temperature probe and sends the data to an EmonCMS 
 server via an Huzzah ESP8266 WiFi module instead of using the RFM69CW RF Module
 
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

*/

#include <Arduino.h>
#include <OneWire.h> 
#include <DallasTemperature.h>
#include <EmonLib.h>

#define FILTERSETTLETIME 5000   
#define ONE_WIRE_BUS 4

typedef struct { int power1, temp1, value3, value4, vrms;} PayloadTX; 
float roomTemperature = 0;
unsigned long msgnum = 0;

const int LEDpin = 9;   
const int CT1 = 1; 
const float calibratedVoltage = 234.6;                                                                                
boolean settled = false;

EnergyMonitor ct1;                                          
PayloadTX emontx; 
OneWire oneWire(ONE_WIRE_BUS);                                          
DallasTemperature sensors(&oneWire); 
 
// Define I2C device address for DS18B20 temperature probe
DeviceAddress address_T1 = { 0x28, 0xC5, 0x4F, 0x28, 0x5F, 0x20, 0x01, 0x3B };

void setup() 
{
  Serial.begin(115200);
  Serial.println("emonTX Shield using ESP8266 & DS18B20"); 
  Serial.println("Author: Martin Sidgreaves");
             
  if (CT1) 
  {
    ct1.current(1, 60.606);                                     // Setup emonTX CT channel (channel, calibration)
    ct1.voltage(0, calibratedVoltage, 1.7);
  }

  // Start the temp sensor
  sensors.begin();
  
  // emonTx Shield Calibration = (100A / 0.05A) / 33 Ohms
  pinMode(LEDpin, OUTPUT);                                              // Setup indicator LED
  digitalWrite(LEDpin, HIGH);
}

void loop() 
{ 
    // Return the temperature value
    sensors.requestTemperatures();      
    emontx.temp1 = sensors.getTempC(address_T1);        

    // Return the power value
    emontx.power1 = ct1.calcIrms(1480) * calibratedVoltage;
    msgnum++;

    // Build the return message
    Serial.print("MSG:"); Serial.print(msgnum);
    Serial.print(F(",P1:")); Serial.print(emontx.power1);  
    Serial.print(F(",T1:")); Serial.print(emontx.temp1);        
    Serial.print(F(",V1:")); Serial.print(ct1.Vrms);   
    Serial.println();                                       
    
    // Quick flash
    digitalWrite(LEDpin, HIGH); delay(2); digitalWrite(LEDpin, LOW); 

    // Wait for five seconds before doing it all again
    delay(5000);                                        
    
}