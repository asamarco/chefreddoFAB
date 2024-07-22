
/**************************************************************************
   Tests the getTemperature and getHumidity functions of the aht20 library
 **************************************************************************/
#include <Wire.h>
#include <AHT20.h>

#define SERIAL_BAUD 115200
#define LABELS ", \"labels\": {\"place\": \"Back end\"}}"

AHT20 aht20;

void setup()
{


  Serial.begin(SERIAL_BAUD);
  Serial.println("Humidity AHT20 examples");

  Wire.begin(); //Join I2C bus
  //Check if the AHT20 will acknowledge
  if (aht20.begin() == false)
  {
    Serial.println("AHT20 not detected. Please check wiring. Freezing.");
    while (1);
  }
  Serial.println("AHT20 acknowledged.");
}

void loop()
{
  printAHT20Data(&Serial);

  //The AHT20 can respond with a reading every ~50ms. However, increased read time can cause the IC to heat around 1.0C above ambient.
  //The datasheet recommends reading every 2 seconds.
  delay(2000);
}

void printAHT20Data (Stream* client)
{
 
    //If a new measurement is available
  if (aht20.available() == true)
  {
    //Get the new temperature and humidity value
    float temperature = aht20.getTemperature();
    float humidity = aht20.getHumidity();

    //Print the results

    client->print("{\"type\": \"gauge\", \"name\": \"temperature\", \"help\": \"Temperature in °C.\", \"method\": \"set\", \"value\":");
    client->print(temperature);
    client->println(LABELS);

    client->print("{\"type\": \"gauge\", \"name\": \"humidity\", \"help\": \"Relative Humidity.\", \"method\": \"set\", \"value\":");
    client->print(humidity);
    client->println(LABELS);
  }
}
