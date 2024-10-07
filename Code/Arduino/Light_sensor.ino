//  This is a prototype code which uses a photoresistor as a light sensor. Currently the code is supported for a very small LED (<5V).
const int sensorPin = A0;   // Reads the analog value of the photoresistor
const int ledPin = 9;   // Digital PWM pin

int sensorValue = 0;

int threshold = 500;    // Threshold value below which LED brightens

void setup()
{
    pinMode(ledPin, OUTPUT);
    Serial.begin(9600);
}

void loop()
{
    sensorValue = analogRead(sensorPin);
    Serial.println(sensorValue);

    if (sensorValue < threshold)
    {
        analogWrite(ledPin, 255);   // 255 - HIGH
    }

    else
    {
        analogWrite(ledPin, 50);    // 50 - LOW
    }

    delay(100); // Small delay to stabilise the entire process.
}