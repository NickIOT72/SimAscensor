#include "I2C.h"
#include <Wire.h>
#include "../SoftSerial/SoftSerial.h"

void getI2Caddress()
{
  Wire.begin();
  byte error, address;
  int nDevices;

  SoftSerial_Degub_println("Scanning...");

  nDevices = 0;
  for (address = 1; address < 127; address++)
  {
    // The i2c_scanner uses the return value of
    // the Write.endTransmisstion to see if
    // a device did acknowledge to the address.
    Wire.beginTransmission(address);
    error = Wire.endTransmission();

    if (error == 0)
    {
      SoftSerial_Degub_print("I2C device found at address 0x");
      if (address < 16)
        SoftSerial_Degub_print("0");
      SoftSerial_Degub_print(address, HEX);
      SoftSerial_Degub_println("  !");

      nDevices++;
    }
    else if (error == 4)
    {
      SoftSerial_Degub_print("Unknown error at address 0x");
      if (address < 16)
        SoftSerial_Degub_print("0");
      SoftSerial_Degub_println(address, HEX);
    }
  }
  if (nDevices == 0)
    SoftSerial_Degub_println("No I2C devices found\n");
  else
    SoftSerial_Degub_println("done\n");
}
