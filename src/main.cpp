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


ESP8266 need to be loaded and configured with EmonEsp. This will allow your emonTX shield to 
communicate with the outside world over Wifi. Please visit:

https://github.com/openenergymonitor/EmonESP

Configuration and setup is beyond the scope of this document however all the information you need
can be found at the above URL

------------------------------------------------------------------------------------------------------------
Connections between EmonTX & ESP8266

emonTX Shield UART Header Pin             Huzzah ESP8266 UAT Header

GND                           ->          GND
5v                            ->          V+
Rx                            ->          Rx

-------------------------------------------------------------------------------------------------------------

Version :: v1.1.0

*/

#include <Arduino.h>
#include <OneWire.h> 
#include <DallasTemperature.h>
#include <EmonLib.h>

#define FILTERSETTLETIME 5000   
#define ONE_WIRE_BUS 4

typedef struct { int power1, power2, power3, power4, temp1, vrms;} PayloadTX; 
float roomTemperature = 0;
unsigned long msgnum = 0;

const int LEDpin = 9;   
const int CT1 = 1; 
const int CT2 = 1;  
const int CT3 = 1;                                                      
const int CT4 = 1;

const float calibratedVoltage = 234.6;                                                                                
boolean settled = false;

EnergyMonitor ct1, ct2, ct3, ct4;                                          
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
             
  if (CT1) ct1.current(1, 60.606);                                     // Setup emonTX CT channel (ADC input, calibration)
  if (CT2) ct2.current(2, 60.606);                                     // Calibration factor = CT ratio / burden resistance
  if (CT3) ct3.current(3, 60.606);                                     // emonTx Shield Calibration factor = (100A / 0.05A) / 33 Ohms
  if (CT4) ct4.current(4, 60.606);

  if (CT1) ct1.voltage(0, 268.97, 1.7);                                // ct.voltageTX(ADC input, calibration, phase_shift) - make sure to select correct calibration for AC-AC adapter  http://openenergymonitor.org/emon/modules/emontx/firmware/calibration. Default set for Ideal Power adapter                                         
  if (CT2) ct2.voltage(0, 268.97, 1.7);                                // 268.97 for the UK adapter, 260 for the Euro and 130 for the US.
  if (CT3) ct3.voltage(0, 268.97, 1.7);
  if (CT4) ct4.voltage(0, 268.97, 1.7);

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

    if (CT1) {
        ct1.calcVI(20,2000);                                                  // Calculate all. No.of crossings, time-out 
        emontx.power1 = ct1.realPower;
        Serial.print(emontx.power1);                                         
    }
    
    emontx.vrms = ct1.Vrms*100; 

    if (CT2) {
      ct2.calcVI(20,2000);                                                  // Calculate all. No.of crossings, time-out 
      emontx.power2 = ct2.realPower;
      Serial.print(" "); Serial.print(emontx.power2);
    } 

    if (CT3) {
      ct3.calcVI(20,2000);                                                  // Calculate all. No.of crossings, time-out 
      emontx.power3 = ct3.realPower;
      Serial.print(" "); Serial.print(emontx.power3);
    } 
    
    if (CT4) {
      ct4.calcVI(20,2000);                                                  // Calculate all. No.of crossings, time-out 
      emontx.power4 = ct4.realPower;
      Serial.print(" "); Serial.print(emontx.power4);
    } 

    msgnum++;

    // Build the return message
    Serial.print("MSG:"); Serial.print(msgnum);
    Serial.print(F(",P1:")); Serial.print(emontx.power1);  
    Serial.print(F(",P2:")); Serial.print(emontx.power2);
    Serial.print(F(",P3")); Serial.print(emontx.power3);
    Serial.print(F(",P4:")); Serial.print(emontx.power4);
    Serial.print(F(",T1:")); Serial.print(emontx.temp1);        
    Serial.print(F(",V1:")); Serial.print(emontx.vrms);   
    Serial.println();                                       
    
    // Quick flash
    digitalWrite(LEDpin, HIGH); delay(2); digitalWrite(LEDpin, LOW); 

    // Wait for five seconds before doing it all again
    delay(5000);                                        
    
}