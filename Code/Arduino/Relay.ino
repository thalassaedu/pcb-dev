const int relayPin = 5;    // Define the digital PWM Pin 7 as relay input

void setup() {
  // put your setup code here, to run once:
  pinMode(relayPin, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(relayPin, HIGH); // Relay connection ON
  delay(5000);  // Wait for 5 seconds
  digitalWrite(relayPin, LOW);  // Relay connection OFF
  delay(5000);  // Wait for 5 seconds
}
