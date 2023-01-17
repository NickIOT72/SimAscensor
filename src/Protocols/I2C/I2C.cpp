#include "I2C.h"
#include <Wire.h>

void getI2Caddress()
{
  Wire.begin();
  byte error, address;
  int nDevices;

  ESP_SERIAL.println("Scanning...");

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
      ESP_SERIAL.print("I2C device found at address 0x");
      if (address < 16)
        ESP_SERIAL.print("0");
      ESP_SERIAL.print(address, HEX);
      ESP_SERIAL.println("  !");

      nDevices++;
    }
    else if (error == 4)
    {
      ESP_SERIAL.print("Unknown error at address 0x");
      if (address < 16)
        ESP_SERIAL.print("0");
      ESP_SERIAL.println(address, HEX);
    }
  }
  if (nDevices == 0)
    ESP_SERIAL.println("No I2C devices found\n");
  else
    ESP_SERIAL.println("done\n");
}
