// Pin definitions
const int waterSensorPin = A4; // Water level sensor pin
const int buzzerPin = 10; // Buzzer pin
const int waterRelayPin = 9; // Water relay pin
const int soilSensorPin = A0; // Soil moisture sensor pin
const int soilRelayPin = 8; // Soil relay pin
const int LedPin = 13; // Onboard LED pin
const int MainRelayPin = 7; // Main relay pin
// Soil moisture threshold
const int moistureThreshold = 700; // Threshold for dry soil
String voice; 
void setup() {
 // Configure the pins as input or output
 pinMode(waterSensorPin, INPUT); // Water sensor input
 pinMode(buzzerPin, OUTPUT); // Buzzer output
 pinMode(waterRelayPin, OUTPUT); // Water relay output
 pinMode(soilSensorPin, INPUT); // Soil moisture sensor input
 pinMode(soilRelayPin, OUTPUT); // Soil relay output
 pinMode(LedPin, OUTPUT); // Onboard LED output
 pinMode(MainRelayPin, OUTPUT); // Main relay output
 // Initialize the outputs to a safe state
 digitalWrite(MainRelayPin, LOW);
 digitalWrite(LedPin, LOW);
 digitalWrite(waterRelayPin, LOW);
 digitalWrite(soilRelayPin, LOW);
 digitalWrite(buzzerPin, LOW);
 // Start Serial communication for debugging
 Serial.begin(9600);
}
void loop() {
while (Serial.available())
 { 
 delay(10); 
 char c = Serial.read(); 
 voice += c; 
 } 
 if (voice.length() > 0)
 {
 Serial.println(voice); 
 if(voice == "on")
 {
 digitalWrite(7, HIGH);
 digitalWrite(13, HIGH);
 } 
 if(voice == "off")
 {
 digitalWrite(7, LOW);
 digitalWrite(13, LOW);
 } 
voice="";
}
 // Water level sensor logic
 int waterSensorValue = digitalRead(waterSensorPin);
 // Print the water sensor value for debugging
 Serial.print("Water Sensor Value: ");
 Serial.println(waterSensorValue);f (waterSensorValue == HIGH) { // No water detected (empty bottle)
 digitalWrite(waterRelayPin, HIGH); // Activate relay
 digitalWrite(buzzerPin, HIGH); // Turn on buzzer
 Serial.println("No water detected (bottle empty)");
 }
  else { // Water detected (full bottle)
 digitalWrite(waterRelayPin, LOW); // Deactivate relay
 digitalWrite(buzzerPin, LOW); // Turn off buzzer
 Serial.println("Water detected (bottle full)");
 }
 
 // Soil moisture sensor logic
 int soilSensorValue = analogRead(soilSensorPin);
 
 // Print the soil moisture value for debugging
 Serial.print("Soil Moisture: ");
 Serial.println(soilSensorValue);
 
 if (soilSensorValue < moistureThreshold) { // Soil is dry
 digitalWrite(soilRelayPin, HIGH); // Activate watering relay
 Serial.println("Soil is dry, relay activated (watering)");
 } else { // Soil is wet
 digitalWrite(soilRelayPin, LOW); // Deactivate watering relay
 Serial.println("Soil is wet, relay deactivated");
 }
 
 // Main relay logic (toggle LED for testing)
 if (waterSensorValue == HIGH || soilSensorValue < moistureThreshold) {
 digitalWrite(MainRelayPin, HIGH); // Activate main relay
 digitalWrite(LedPin, HIGH); // Turn on LED
 } else {
 digitalWrite(MainRelayPin, LOW); // Deactivate main relay
 digitalWrite(LedPin, LOW); // Turn off LED
 }
 
 // Add a small delay for stability
 delay(1000);
}