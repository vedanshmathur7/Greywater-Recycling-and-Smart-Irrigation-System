const int soilPin = A0;       // Soil moisture sensor connected to analog pin A0
const int relayPin = 3;       // Relay module IN1 connected to digital pin 3

// Adjust these based on your sensor's calibration
const int dryValue = 1023;    // Raw value when soil is completely dry (sensor in air)
const int wetValue = 400;     // Raw value when soil is fully wet

void setup() {
  pinMode(relayPin, OUTPUT);
  digitalWrite(relayPin, HIGH); // Start with pump OFF (relay is active LOW)
  Serial.begin(9600);           // Begin serial communication
}

void loop() {
  int soilValue = analogRead(soilPin); // Read raw moisture value from sensor

  // Convert to moisture percentage
  int moisturePercent = map(soilValue, dryValue, wetValue, 0, 100);
  moisturePercent = constrain(moisturePercent, 0, 100); // Ensure value is between 0–100

  // Print readings to Serial Monitor
  Serial.print("Raw Value: ");
  Serial.print(soilValue);
  Serial.print(" | Moisture: ");
  Serial.print(moisturePercent);
  Serial.println("%");

  // Control pump based on moisture
  if (moisturePercent < 30) {
    digitalWrite(relayPin, LOW);   // Turn pump ON (relay active LOW)
    Serial.println("Soil is Dry - Pump ON");
  } else {
    digitalWrite(relayPin, HIGH);  // Turn pump OFF
    Serial.println("Soil is Moist - Pump OFF");
  }

  delay(2000); // Wait 2 seconds before next reading
}
