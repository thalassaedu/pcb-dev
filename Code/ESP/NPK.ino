#include <ModbusMaster.h> //Library for interfacing with RS485

#define DE_RE 4 //Driver enable and receiver enable are opearting together

ModbusMaster node;

void preTransmission()  //Tranmission starts
{
  digitalWrite(DE_RE, HIGH);
}

void postTransmission() //Transmission stops
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
}

void loop()
{
  uint8_t result = node.readHoldingRegisters(0x001E,3); //Starts reading from address 0x1E (Nitrogen) and reads three 16-bit data
  Serial.print("Received Successfully\n");

  delay(1000);

  if (result == node.ku8MBSuccess)
  {
    Serial.print("Nitrogen: ");
    Serial.print(node.getResponseBuffer(0));    //Nitrogen at Buffer(0)
    Serial.println(" mg/kg");
    Serial.print("Phosphorous: ");
    Serial.print(node.getResponseBuffer(1));    //Phosphorous at Buffer(1)
    Serial.println(" mg/kg");
    Serial.print("Potassium: ");
    Serial.print(node.getResponseBuffer(2));    //Potassium at Buffer(2)
    Serial.println(" mg/kg");

  }

  else
  {
    Serial.print("Failed, Response Code: ");    //Even fails, gives the error code
    Serial.print(result, HEX);
    Serial.println("");
    delay(5000);
  }
  
  Serial.print("\n");
  delay(1000);
}