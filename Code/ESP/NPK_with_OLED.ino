#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>   // Library for OLED
#include <Adafruit_SSD1306.h>   // Library for OLED
#include <ModbusMaster.h> // Library for interfacing with RS485

#define DE_RE 4 // Driver enable and receiver enable are opearting together
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

ModbusMaster node;

void preTransmission()  // Tranmission starts
{
  digitalWrite(DE_RE, HIGH);
}

void postTransmission() // Transmission stops
{
  digitalWrite(DE_RE, LOW);
}

void setup()
{
  pinMode(DE_RE, OUTPUT);
  digitalWrite(DE_RE, LOW);

  Serial.begin(115200);
  Serial1.begin(9600, SERIAL_8N1, 16, 17);
  node.begin(1, Serial1);
  node.preTransmission(preTransmission);
  node.postTransmission(postTransmission);

  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C))
  { // Address 0x3C for 128x64
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
    delay(2000);
  }
}

void loop()
{
  uint16_t nitro, phos, pota;
  uint8_t result = node.readHoldingRegisters(0x001E,3); // Starts reading from address 0x1E (Nitrogen) and reads three 16-bit data
  //Serial.print("Received Successfully\n");

  delay(1000);

  if (result == node.ku8MBSuccess)
  {
    nitro = node.getResponseBuffer(0);  // Nitrogen at Buffer(0)
    phos = node.getResponseBuffer(1);   // Phosphorous at Buffer(1)
    pota = node.getResponseBuffer(2);   // Potassium at Buffer(2)

    display.clearDisplay();
    display.setTextSize(2);

    display.setTextColor(SSD1306_WHITE);
    display.setCursor(0, 0);    // Set Cursor location (x,y)
    display.print("N: ");
    display.print(nitro);   // Display nitrogen
    display.println("mg/kg");
    display.print("P: ");
    display.print(phos);    // Display phosphorous
    display.println("mg/kg");
    display.print("K: ");
    display.print(pota);    // Display potassium
    display.println("mg/kg");

    display.display();
  }

  else
  {
    // If response fails, display error code
    display.clearDisplay();
    display.setTextSize(2);

    display.setTextColor(SSD1306_WHITE);
    display.setCursor(0, 0);
    display.print("Failed, Response Code: ");
    display.println(result, HEX);
    display.println("");
    delay(5000);
    display.display();
  }
  
  Serial.print("\n");
  delay(1000);
}