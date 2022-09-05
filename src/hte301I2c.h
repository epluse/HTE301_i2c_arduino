/***************************************************************************/
/* headerfile for "hte301I2c.cpp" module */
/***************************************************************************/
/*
Read functions for measurement values of the HTE301 Sensor via I2C interface.

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

#ifndef hte301I2c_H
#define hte301I2c_H

#include "Arduino.h"
#include "Wire.h"

// Defines
//-----------------------------------------------------------------------------
#define CRC8_ONEWIRE_POLY 0x31
#define CRC8_ONEWIRE_START 0xFF


// declaration of functions
//-----------------------------------------------------------------------------

class hte301I2c
{
public:
    hte301I2c(void);
    hte301I2c(unsigned char i2cAdress);
    uint8_t singleShotTempHum(float &temperature, float &humidity, int repeatability); // with clock stretching enabled
    uint8_t singleShotTempHumClockStretchingDisabled(float &temperature, float &humidity, int repeatability); // with clock stretching disabled
    uint8_t getPeriodicMeasurementTempHum(float &temperature, float &humidity); 
    void startPeriodicMeasurement(int measurementPerSeconds , int repeatability);
    void endPeriodicMeasurement(void);
    void heaterOn(void);
    void heaterOff(void);
    uint8_t readIdentification(unsigned char identification[]);
    uint8_t constantHeaterOnOff(bool &conHeaterOnOff);
    uint8_t readStatusRegister1(unsigned char statusRegister1[]);
    uint8_t readStatusRegister2(unsigned char statusRegister2[]);
    void clearStatusregister1(void);
    void reset(void);
    void i2cReset(void);
    unsigned char address = 0x44;
    void wireWrite(unsigned char buf[], int to, bool stopmessage);
    void wireRead(unsigned char buf[], uint8_t to);
    unsigned char calcCrc8(unsigned char buf[], unsigned char from, unsigned char to);
    void getErrorString(uint8_t Status, char errorString[]);
};

#endif