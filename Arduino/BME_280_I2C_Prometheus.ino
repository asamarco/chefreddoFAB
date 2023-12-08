/*
BME280 I2C Prometheus.ino

This code shows how to record data from the BME280 environmental sensor
using I2C interface and print it on serial port in a format understandable to Prometheus.
This file is a minor adaptation of the example file part of the Arduino BME280 library and released under the GNU General Public License.

Connecting the BME280 Sensor:
Sensor              ->  Board
-----------------------------
Vin (Voltage In)    ->  3.3V
Gnd (Ground)        ->  Gnd
SDA (Serial Data)   ->  A4 on Uno/Pro-Mini, 20 on Mega2560/Due, 2 Leonardo/Pro-Micro
SCK (Serial Clock)  ->  A5 on Uno/Pro-Mini, 21 on Mega2560/Due, 3 Leonardo/Pro-Micro

 */

#include <BME280I2C.h>
#include <Wire.h>

#define SERIAL_BAUD 115200
#define LABELS ", \"labels\": {\"place\": \"thin films\"}}"

BME280I2C bme;    // Default : forced mode, standby time = 1000 ms
                  // Oversampling = pressure ×1, temperature ×1, humidity ×1, filter off,

//////////////////////////////////////////////////////////////////
void setup()
{
  Serial.begin(SERIAL_BAUD);

  while(!Serial) {} // Wait

  Wire.begin();

  while(!bme.begin())
  {
    Serial.println("Could not find BME280 sensor!");
    delay(1000);
  }

  switch(bme.chipModel())
  {
     case BME280::ChipModel_BME280:
       //Serial.println("Found BME280 sensor! Success.");
       break;
     case BME280::ChipModel_BMP280:
       Serial.println("Found BMP280 sensor! No Humidity available.");
       break;
     default:
       Serial.println("Found UNKNOWN sensor! Error!");
  }
}

//////////////////////////////////////////////////////////////////
void loop()
{
   printBME280Data(&Serial);
   delay(500);
}

//////////////////////////////////////////////////////////////////
void printBME280Data
(
   Stream* client
)
{
   float temp(NAN), hum(NAN), pres(NAN);

   BME280::TempUnit tempUnit(BME280::TempUnit_Celsius);
   BME280::PresUnit presUnit(BME280::PresUnit_Pa);

   bme.read(pres, temp, hum, tempUnit, presUnit);

 client->print("{\"type\": \"gauge\", \"name\": \"temperature\", \"help\": \"Temperature in °C.\", \"method\": \"set\", \"value\":");
 client->print(temp);
 client->println(LABELS);

 client->print("{\"type\": \"gauge\", \"name\": \"humidity\", \"help\": \"Relative Humidity.\", \"method\": \"set\", \"value\":");
 client->print(hum);
 client->println(LABELS);

 client->print("{\"type\": \"gauge\", \"name\": \"pressure\", \"help\": \"Pressure in Pa.\", \"method\": \"set\", \"value\":");
 client->print(pres);
 client->println(LABELS);
 
   delay(5000);
}
