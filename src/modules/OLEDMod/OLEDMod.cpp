#include "OLEDMod.h"
#include "../../Protocols/SoftSerial/SoftSerial.h"
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
SoftwareSerial ESP_SERIAL_OLED(ESP_RX, ESP_TX);

void OLED_Init()
{
    ESP_SERIAL_OLED.begin(BAUD_SERIAL);
    if (!display.begin(SSD1306_SWITCHCAPVCC, ADDRES_OLED))
    {
        ESP_SERIAL_OLED.println(F("SSD1306 allocation failed"));
        for (;;)
            ; // Don't proceed, loop forever
    }
    display.display();
    delay(100); // Pause for 2 seconds
    // Clear the buffer
    display.clearDisplay();
    ESP_SERIAL_OLED.println("OLED Initiated");
}