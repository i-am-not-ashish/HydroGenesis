#define BLYNK_TEMPLATE_ID "*************"
#define BLYNK_TEMPLATE_NAME "HydroGenesis"
#define BLYNK_PRINT Serial

#include <WiFi.h>
#include <BlynkSimpleEsp32.h>
#include <FirebaseESP32.h>
#include <DHT.h>
#include <NTPClient.h>

// Network and cloud service credentials
const char blynk_auth[] = "********************************";
const char ssid[] = "********";
const char pass[] = "********";

// Firebase configuration
FirebaseConfig config;
FirebaseAuth auth;
FirebaseData firebaseData;

// NTP client for timestamps
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org", 19800, 60000); // IST offset = 19800 seconds

// Sensor pin definitions
#define SOIL_MOISTURE_PIN 35
#define DHT_PIN 26
#define DHT_TYPE DHT22
#define TRIG_PIN 16
#define ECHO_PIN 17
#define LDR_PIN 34
#define RELAY_PIN 25

// Initialize sensor objects
DHT dht(DHT_PIN, DHT_TYPE);
BlynkTimer timer;

String path = "/sensor_data";

void setup() {
  Serial.begin(115200);
  Serial.println("Setup Started...");

  // Initialize WiFi connection
  Serial.print("Connecting to WiFi: ");
  Serial.println(ssid);
  WiFi.begin(ssid, pass);

  int attempt = 0;
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    attempt++;
    if (attempt > 20) {
      Serial.println("\nFailed to connect to WiFi. Restarting...");
      ESP.restart();
    }
  }
  Serial.println("\nWiFi Connected!");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());

  // Configure and initialize Firebase
  config.api_key = "**************************************";
  config.database_url = "https://*********.firebaseio.com/";
  auth.user.email = "********@gmail.com";
  auth.user.password = "***********";
  Firebase.begin(&config, &auth);
  Firebase.reconnectWiFi(true);

  timeClient.begin();
  
  // Initialize Blynk connection
  Serial.println("Connecting to Blynk...");
  Blynk.begin(blynk_auth, ssid, pass);

  if (Blynk.connected()) {
    Serial.println("Blynk Connected Successfully!");
  } else {
    Serial.println("Blynk Connection Failed!");
  }

  // Initialize sensors and pins
  dht.begin();
  pinMode(SOIL_MOISTURE_PIN, INPUT);
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(RELAY_PIN, OUTPUT);
  pinMode(LDR_PIN, INPUT);
  digitalWrite(RELAY_PIN, HIGH);  // Ensure relay is off initially

  // Set up periodic sensor reading
  timer.setInterval(4000L, readAllSensors);
}

void loop() {
  // Maintain network connections
  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("WiFi Disconnected! Reconnecting...");
    WiFi.begin(ssid, pass);
    return;
  }

  if (!Blynk.connected()) {
    Serial.println("Blynk Disconnected! Attempting Reconnect...");
    Blynk.begin(blynk_auth, ssid, pass);
    return;
  }

  // Run Blynk and timer services
  Blynk.run();
  timer.run();
  timeClient.update();
  
  // Get current timestamp for Firebase records
  unsigned long epochTime = timeClient.getEpochTime();
  String uniqueID = String(epochTime);

  // Read all sensor values
  int soil_moisture = readSoilMoisture();
  float temperature = readTemperature();
  float humidity = readHumidity();
  int distance = readUltrasonic();
  int light = readLDR();

  // Push data to Firebase
  Firebase.pushString(firebaseData, "/sensor_data/" + uniqueID + "/temperature", String(temperature));
  Firebase.pushString(firebaseData, "/sensor_data/" + uniqueID + "/humidity", String(humidity));
  Firebase.pushString(firebaseData, "/sensor_data/" + uniqueID + "/light_intensity", String(light));
  Firebase.pushString(firebaseData, "/sensor_data/" + uniqueID + "/pump_status", String(digitalRead(RELAY_PIN)));
  Firebase.pushString(firebaseData, "/sensor_data/" + uniqueID + "/soil_moisture", String(soil_moisture));
  Firebase.pushString(firebaseData, "/sensor_data/" + uniqueID + "/water_level", String(distance));
}

/**
 * Reads soil moisture level and controls pump accordingly
 * @return Moisture percentage (0-100)
 */
int readSoilMoisture() {
  int soilMoisture = analogRead(SOIL_MOISTURE_PIN);
  int moisturePercentage = map(soilMoisture, 0, 4095, 0, 100);
  moisturePercentage = constrain(moisturePercentage, 0, 100);

  Serial.print("Soil Moisture: ");
  Serial.print(moisturePercentage);
  Serial.print("% | ");
  Blynk.virtualWrite(V1, moisturePercentage);

  // Pump control logic
  if (moisturePercentage < 40) {
    digitalWrite(RELAY_PIN, LOW);
    Serial.println("Pump Activated");
  } else if (moisturePercentage >= 70) {
    digitalWrite(RELAY_PIN, HIGH);
    Serial.println("Pump Deactivated");
  } else {
    Serial.println("Moisture in optimal range, no action taken");
  }
  return moisturePercentage;
}

/**
 * Reads temperature from DHT sensor
 * @return Temperature in Celsius
 */
float readTemperature() {
  float temperature = dht.readTemperature();

  if (isnan(temperature)) {
    Serial.println("Failed to read Temperature!");
    return 0;
  }

  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.print("°C | ");
 
  Blynk.virtualWrite(V2, temperature);
  return temperature;
}

/**
 * Reads humidity from DHT sensor
 * @return Humidity percentage
 */
float readHumidity() {
  float humidity = dht.readHumidity();

  if (isnan(humidity)) {
    Serial.println("Failed to read Humidity!");
    return 0;
  }

  Serial.print("Humidity: ");
  Serial.print(humidity);
  Serial.print("% | ");

  Blynk.virtualWrite(V3, humidity);
  return humidity;
}

/**
 * Measures water level using ultrasonic sensor
 * @return Distance to water surface in cm
 */
int readUltrasonic() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  long duration = pulseIn(ECHO_PIN, HIGH);
  int distance = duration * 0.034 / 2;
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
  Blynk.virtualWrite(V0, distance);
  return distance;
}

/**
 * Measures light intensity using LDR
 * @return Light intensity in lux
 */
int readLDR() {
  int ldrValue = analogRead(LDR_PIN);
  float Vout = ldrValue * (5.0 / 4095.0);
  float Rldr = (5.0 * 10000) / Vout - 10000;

  if (Rldr < 0) Rldr = 0;
  float lux = 500 / ((Rldr + 1) / 1000.0);

  Serial.print("LDR Value: ");
  Serial.print(ldrValue);
  Serial.print(" | Light Intensity: ");
  Serial.println(lux);

  Blynk.virtualWrite(V4, lux);
  return lux;
}

/**
 * Reads all sensors and sends data to Blynk
 */
void readAllSensors() {
  readSoilMoisture();
  readTemperature();
  readHumidity();
  readUltrasonic();
  readLDR();
}