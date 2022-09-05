/*
Example script reading measurement values from the HTE301 sensor via I2C interface.

Copyright 2022 E+E Elektronik Ges.m.b.H.

Disclaimer:
This application example is non-binding and does not claim to be complete with regard
to configuration and equipment as well as all eventualities. The application example
is intended to provide assistance with the HTE301 sensor module design-in and is provided "as is".
You yourself are responsible for the proper operation of the products described.
This application example does not release you from the obligation to handle the product safely
during application, installation, operation and maintenance. By using this application example,
you acknowledge that we cannot be held liable for any damage beyond the liability regulations
described.

We reserve the right to make changes to this application example at any time without notice.
In case of discrepancies between the suggestions in this application example and other E+E
publications, such as catalogues, the content of the other documentation takes precedence.
We assume no liability for the information contained in this document.
*/

#include <hte301I2c.h>
#include <Wire.h>
hte301I2c hte(0x44);
#define REQUEST_INTERVAL_MS 2000 //Time interval between measurements in ms
#define CSV_DELIMITER ','


float temperature, humidity;
unsigned char identification[8];
char errorString[200];
uint8_t errorcode;

void setup()
{
  Serial.begin(9600); //Start Serial communication
  Wire.begin();       //initialize I2C peripheral (SDA..A4, SCL..A5)
  delay(1000);
  errorcode = hte.readIdentification(identification);
  if (errorcode != 0)
  {
    hte.getErrorString(errorcode, errorString);
    Serial.println(errorString);
  }
  else
  {
    Serial.print("Identificationnumber: ");
    for (int i = 0; i < 8; i++)
    {
      Serial.print(identification[i] < 16 ? "0" : "");
      Serial.print(identification[i], HEX);
    }
  }
  Serial.println("");
  hte.startPeriodicMeasurement(2, 2); // measurementPerSeconds: 0 = 0.5 mps, 1 = 1mps, 2 = 2mps, 3 = 4mps, 4 = 10mps;  repeatability: 0 = low, 1 = medium, 2 = high; 
  delay(2000);
  Serial.print("temperature");
  Serial.print(CSV_DELIMITER);
  Serial.println(" relative humidity");
  delay(1000);
}

void loop()
{
  errorcode = hte.getPeriodicMeasurementTempHum(temperature, humidity);
  if (errorcode != 0)
  {
    hte.getErrorString(errorcode, errorString);
    Serial.println(errorString);
  }
  else
  {
   Serial.print(temperature);
   Serial.print(" °C");
   Serial.print(CSV_DELIMITER);
   Serial.print(humidity);
   Serial.println(" %RH");
  }

  delay(REQUEST_INTERVAL_MS); //time until the next loop start
}
