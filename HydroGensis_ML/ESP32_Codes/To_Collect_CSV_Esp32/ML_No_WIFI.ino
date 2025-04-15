#include <SPIFFS.h>
#include <DHT.h>

// Sensor Pins
#define SOIL_MOISTURE_PIN 35
#define DHT_PIN 26
#define DHT_TYPE DHT22
#define TRIG_PIN 16
#define ECHO_PIN 17
#define LDR_PIN 34
#define RELAY_PIN 25

// Initialize objects
DHT dht(DHT_PIN, DHT_TYPE);

// Initial time (set this to the desired starting time)
int initialHours = 17;    // Set initial hour (0-23)
int initialMinutes = 28;  // Set initial minute (0-59)
int initialSeconds = 0;   // Set initial second (0-59)

void setup() {
  Serial.begin(115200);
  Serial.println("Setup Started...");

  // Initialize SPIFFS
  if (!SPIFFS.begin(true)) {
    Serial.println("Failed to mount SPIFFS!");
    return;
  }
  Serial.println("SPIFFS mounted successfully.");

  // Initialize sensors
  dht.begin();
  pinMode(SOIL_MOISTURE_PIN, INPUT);
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(RELAY_PIN, OUTPUT);
  pinMode(LDR_PIN, INPUT);
  digitalWrite(RELAY_PIN, HIGH);  // Ensure relay is off initially
}

void loop() {
  // Read and save sensor data every 4 seconds
  readAllSensors();
  delay(4000);  // 4-second delay between readings
}

// Function to get current time in HH:MM:SS format
String getCurrentTime() {
  unsigned long elapsedMillis = millis();             // Get elapsed time in milliseconds
  unsigned long totalSeconds = elapsedMillis / 1000;  // Convert to seconds

  // Calculate current time based on initial time
  int hours = 15 + (totalSeconds / 3600) % 24;      // Add elapsed hours
  int minutes = 10 + (totalSeconds % 3600) / 60;  // Add elapsed minutes
  int seconds = 00 + totalSeconds % 60;           // Add elapsed seconds

  // Handle overflow (e.g., if seconds > 59 or minutes > 59)
  if (seconds >= 60) {
    seconds -= 60;
    minutes += 1;
  }
  if (minutes >= 60) {
    minutes -= 60;
    hours += 1;
  }
  if (hours >= 24) {
    hours -= 24;
  }

  // Format time as HH:MM:SS
  char timeString[9];
  sprintf(timeString, "%02d:%02d:%02d", hours, minutes, seconds);
  return String(timeString);
}

void readSoilMoisture() {
  int soilMoisture = analogRead(SOIL_MOISTURE_PIN);
  int dryValue = 0;     // Analog value when soil is completely dry
  int wetValue = 4095;  // Analog value when soil is completely wet
  int moisturePercentage = map(soilMoisture, dryValue, wetValue, 0, 100);
  moisturePercentage = constrain(moisturePercentage, 0, 100);

  Serial.print("Soil Moisture: ");
  Serial.print(moisturePercentage);
  Serial.print("% | ");

  // Control relay based on soil moisture level
  if (moisturePercentage < 30) {
    digitalWrite(RELAY_PIN, LOW);  // Turn ON pump
    Serial.println("Pump Activated");
  } else if (moisturePercentage >= 70) {
    digitalWrite(RELAY_PIN, HIGH);  // Turn OFF pump
    Serial.println("Pump Deactivated");
  } else {
    Serial.println("Moisture in optimal range, no action taken");
  }
}

void readTemperature() {
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();

  if (isnan(temperature) || isnan(humidity)) {
    Serial.print("Failed to read from DHT sensor!");
    temperature = 0.0;  // Default value if reading fails
    humidity = 0.0;     // Default value if reading fails
  }

  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.print("°C | Humidity: ");
  Serial.print(humidity);
  Serial.print("% | ");
}

void readUltrasonic() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  long duration = pulseIn(ECHO_PIN, HIGH);
  int distance = duration * 0.034 / 2;  // Convert to cm
  distance = 30 - distance;
  if (distance > 0 && distance < 5) {
    Serial.print("Water Level Distance: ");
    Serial.print(distance);
    Serial.print(" cm | ");
  } else if (distance >= 5 && distance <= 15) {
    Serial.print("Water Level Distance: ");
    Serial.print(distance);
    Serial.print(" cm | ");
  } else {
    distance = 30;
    Serial.print("The tank has enough Water. | ");
  }
}

void readLDR() {
  int ldrValue = analogRead(LDR_PIN);
  float Vout = ldrValue * (5.0 / 4095.0);     // Convert to voltage (12-bit ADC)
  float Rldr = (5.0 * 10000) / Vout - 10000;  // Calculate LDR resistance

  // Avoid division by zero and negative values
  if (Rldr < 1) Rldr = 1;  // Set a minimum resistance to avoid infinity

  // Calculate lux (adjust the constant 500 based on calibration)
  float lux = 500 / ((Rldr + 1) / 1000.0);

  // Handle invalid lux values
  if (isinf(lux) || isnan(lux)) {
    lux = 0.0;  // Set lux to 0 if calculation fails
  }

  Serial.print("LDR Value: ");
  Serial.print(ldrValue);
  Serial.print(" | Light Intensity: ");
  Serial.println(lux);
}

void saveSensorData(float soilMoisture, float temperature, float humidity, float waterLevel, float lightIntensity, String pumpStatus) {
  File file = SPIFFS.open("/sensor_data.csv", FILE_APPEND);
  if (!file) {
    Serial.println("Failed to open file for writing!");
    return;
  }

  // Get current time in HH:MM:SS format
  String timestamp = getCurrentTime();

  // Format: Time, Soil Moisture, Temperature, Humidity, Water Level, Light Intensity, Pump Status
  String data = timestamp + "," + String(soilMoisture) + "," + String(temperature) + "," + String(humidity) + "," + String(waterLevel) + "," + String(lightIntensity) + "," + pumpStatus + "\n";
  file.print(data);
  file.close();
  Serial.println("Data saved to file.");
}

void readAllSensors() {
  readSoilMoisture();
  readTemperature();
  readUltrasonic();
  readLDR();

  // Save sensor data to file
  float soilMoisture = analogRead(SOIL_MOISTURE_PIN);
  float dryValue = 0;     // Analog value when soil is completely dry
  float wetValue = 4095;  // Analog value when soil is completely wet
  float moisturePercentage = map(soilMoisture, dryValue, wetValue, 0, 100);
  moisturePercentage = constrain(moisturePercentage, 0, 100);

  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();

  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  long duration = pulseIn(ECHO_PIN, HIGH);
  int distance = duration * 0.034 / 2;  // Convert to cm
  float waterLevel = 30 - distance;

  float ldrValue = analogRead(LDR_PIN);
  float Vout = ldrValue * (5.0 / 4095.0);     // Convert to voltage (12-bit ADC)
  float Rldr = (5.0 * 10000) / Vout - 10000;  // Calculate LDR resistance
  // Avoid division by zero and negative values
  if (Rldr < 1) Rldr = 1;  // Set a minimum resistance to avoid infinity
  // Calculate lux (adjust the constant 500 based on calibration)
  float lux = 500 / ((Rldr + 1) / 1000.0);
  // Handle invalid lux values
  if (isinf(lux) || isnan(lux)) {
    lux = 0.0;  // Set lux to 0 if calculation fails
  }

  String pumpStatus = (digitalRead(RELAY_PIN) == LOW) ? "YES" : "NO";  // Check pump status

  saveSensorData(moisturePercentage, temperature, humidity, waterLevel, lux, pumpStatus);
}