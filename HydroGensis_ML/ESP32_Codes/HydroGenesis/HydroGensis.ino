// Blynk configuration
#define BLYNK_TEMPLATE_ID "************"
#define BLYNK_TEMPLATE_NAME "HydroGenesis"
#define BLYNK_PRINT Serial

// Library includes
#include <WiFi.h>
#include <BlynkSimpleEsp32.h>
#include <FirebaseESP32.h>
#include <DHT.h>
#include <NTPClient.h>
#include <WiFiUdp.h>
#include <TensorFlowLite_ESP32.h>
#include "tensorflow/lite/micro/all_ops_resolver.h"
#include "tensorflow/lite/micro/kernels/micro_ops.h"
#include "tensorflow/lite/micro/micro_error_reporter.h"
#include "tensorflow/lite/micro/micro_interpreter.h"
#include "tensorflow/lite/schema/schema_generated.h"

// Network credentials and authentication
const char blynk_auth[] = "****************************";
const char ssid[] = "********";
const char pass[] = "********";

// Firebase configuration
FirebaseConfig config;
FirebaseAuth auth;
FirebaseData firebaseData;

// NTP client for time synchronization
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org", 19800, 60000);

// Pin definitions
#define SOIL_MOISTURE_PIN 35
#define DHT_PIN 26
#define DHT_TYPE DHT22
#define TRIG_PIN 17
#define ECHO_PIN 18
#define LDR_PIN 34
#define RELAY_PIN 25

// Sleep time constants
#define DEFAULT_SLEEP_TIME_SEC 3600  // 1 hour in seconds
#define MIN_SLEEP_TIME_SEC 60        // 1 minute in seconds
#define US_TO_S_FACTOR 1000000ULL    // Microseconds to seconds conversion factor

// RTC memory storage for sleep persistence
RTC_DATA_ATTR int last_soil_moisture = -1;
RTC_DATA_ATTR bool was_pump_on = false;
RTC_DATA_ATTR float last_sleep_duration = 0;

// TensorFlow Lite model arena sizes
const int kTensorArenaSize = 16 * 1024;
uint8_t moisture_arena[kTensorArenaSize];
uint8_t water_arena[kTensorArenaSize];

// Sensor and timer objects
DHT dht(DHT_PIN, DHT_TYPE);
BlynkTimer timer;

// Firebase data path
String path = "/sensor_data";

// Model includes
#include "moisture_model.h"
#include "water_level_model.h"

// TensorFlow Lite components
tflite::MicroErrorReporter micro_error_reporter;
tflite::ErrorReporter* error_reporter = &micro_error_reporter;
const tflite::Model* moisture_model = tflite::GetModel(moisture_model_tflite);
const tflite::Model* water_level_model = tflite::GetModel(water_level_model_tflite);
static tflite::MicroMutableOpResolver<5> micro_op_resolver;
static tflite::MicroInterpreter* moisture_interpreter = nullptr;
static tflite::MicroInterpreter* water_interpreter = nullptr;

/**
 * Initializes TensorFlow Lite models and interpreters
 */
void setupModels() {
  // Add required operations to the resolver
  micro_op_resolver.AddFullyConnected();
  micro_op_resolver.AddReshape();
  micro_op_resolver.AddQuantize();
  micro_op_resolver.AddDequantize();
  micro_op_resolver.AddRelu();

  // Initialize moisture model interpreter
  moisture_interpreter = new tflite::MicroInterpreter(
    moisture_model, micro_op_resolver, moisture_arena, kTensorArenaSize, error_reporter);
  moisture_interpreter->AllocateTensors();

  // Initialize water level model interpreter
  water_interpreter = new tflite::MicroInterpreter(
    water_level_model, micro_op_resolver, water_arena, kTensorArenaSize, error_reporter);
  water_interpreter->AllocateTensors();
}

/**
 * Predicts optimal watering time based on environmental conditions
 * @param temp Current temperature
 * @param humidity Current humidity
 * @param light Current light intensity
 * @return Predicted watering time in seconds
 */
float predict_water_time(float temp, float humidity, float light) {
  TfLiteTensor* input = moisture_interpreter->input(0);
  input->data.f[0] = temp / 50.0;
  input->data.f[1] = humidity / 100.0;
  input->data.f[2] = light / 200000.0;

  if (moisture_interpreter->Invoke() != kTfLiteOk) {
    Serial.println("Water time prediction failed!");
    return DEFAULT_SLEEP_TIME_SEC;
  }
  float output = moisture_interpreter->output(0)->data.f[0];
  return max((float)(output * 3600.0), (float)MIN_SLEEP_TIME_SEC);
}

/**
 * Predicts when water tank will be empty based on current conditions
 * @param level Current water level
 * @param temp Current temperature
 * @param humidity Current humidity
 * @param light Current light intensity
 * @return Predicted time until tank is empty in seconds
 */
float predict_tank_empty_time(float level, float temp, float humidity, float light) {
  TfLiteTensor* input = water_interpreter->input(0);
  input->data.f[0] = level / 30.0;
  input->data.f[1] = temp / 50.0;
  input->data.f[2] = humidity / 100.0;
  input->data.f[3] = light / 200000.0;

  if (water_interpreter->Invoke() != kTfLiteOk) {
    Serial.println("Tank time prediction failed!");
    return DEFAULT_SLEEP_TIME_SEC;
  }
  float output = water_interpreter->output(0)->data.f[0];
  return max((float)(output * 3600.0), (float)MIN_SLEEP_TIME_SEC);
}

/**
 * Puts the device into deep sleep for specified time
 * @param sleep_time_us Sleep duration in microseconds
 */
void goToSleep(uint64_t sleep_time_us) {
  Serial.println("\nPreparing for deep sleep...");
  
  // Save current state to RTC memory
  last_sleep_duration = sleep_time_us / US_TO_S_FACTOR;
  was_pump_on = digitalRead(RELAY_PIN) == LOW;
  
  // Turn off all outputs
  digitalWrite(RELAY_PIN, HIGH);
  
  // Disconnect from Blynk
  Blynk.disconnect();
  delay(500);
  
  // Close Firebase connection
  if (Firebase.ready()) {
    Firebase.reconnectWiFi(false);
    delay(500);
  }
  
  // Disconnect WiFi
  WiFi.disconnect(true);
  WiFi.mode(WIFI_OFF);
  delay(500);
  
  // Release all pins
  pinMode(TRIG_PIN, INPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(LDR_PIN, INPUT);
  pinMode(SOIL_MOISTURE_PIN, INPUT);
  
  // Final cleanup before sleep
  Serial.printf("Going to sleep for %.1f seconds\n", sleep_time_us / 1000000.0);
  Serial.flush();
  delay(200);
  
  // Configure and start deep sleep
  esp_sleep_disable_wakeup_source(ESP_SLEEP_WAKEUP_ALL);
  esp_sleep_enable_timer_wakeup(sleep_time_us);
  esp_deep_sleep_start();
}

/**
 * Initial setup function runs once on startup
 */
void setup() {
  Serial.begin(115200);
  delay(100);
  Serial.println("Setup Started...");
  
  // Print reset reason
  Serial.printf("\nBooted. Reset reason: %d\n", esp_reset_reason());
  
  // Disable watchdogs
  disableCore0WDT();
  disableCore1WDT();

  // Connect to WiFi
  Serial.print("Connecting to WiFi: ");
  Serial.println(ssid);
  WiFi.begin(ssid, pass);

  int attempt = 0;
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    attempt++;
    if (attempt > 20) {  // Timeout after 10 seconds
      Serial.println("\nFailed to connect to WiFi. Restarting...");
      ESP.restart();
    }
  }
  Serial.println("\nWiFi Connected!");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());

  // Initialize Firebase
  config.api_key = "************************************";
  config.database_url = "https://******************.firebaseio.com/";
  auth.user.email = "************@gmail.com";
  auth.user.password = "*************";
  Firebase.begin(&config, &auth);
  Firebase.reconnectWiFi(true);

  // Initialize NTP client
  timeClient.begin();
  
  // Connect to Blynk
  Serial.println("Connecting to Blynk...");
  Blynk.begin(blynk_auth, ssid, pass);

  if (Blynk.connected()) {
    Serial.println("Blynk Connected Successfully!");
  } else {
    Serial.println("Blynk Connection Failed!");
  }

  // Initialize sensors
  dht.begin();
  pinMode(SOIL_MOISTURE_PIN, INPUT);
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(RELAY_PIN, OUTPUT);
  pinMode(LDR_PIN, INPUT);
  digitalWrite(RELAY_PIN, HIGH);  // Ensure relay is off initially

  // Initialize ML models
  setupModels();

  // Set up timer for periodic sensor readings
  timer.setInterval(4000L, readAllSensors);  // Every 4 seconds
}

/**
 * Main program loop
 */
void loop() {
  delay(10);  // Small delay to prevent watchdog triggers

  // Maintain WiFi connection
  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("WiFi Disconnected! Reconnecting...");
    WiFi.begin(ssid, pass);
    return;
  }

  // Maintain Blynk connection
  if (!Blynk.connected()) {
    Serial.println("Blynk Disconnected! Attempting Reconnect...");
    Blynk.begin(blynk_auth, ssid, pass);
    return;
  }

  // Run Blynk and timer tasks
  Blynk.run();
  timer.run();
  timeClient.update();
  unsigned long epochTime = timeClient.getEpochTime();
  String uniqueID = String(epochTime);

  // Read all sensors
  int soil_moisture = readSoilMoisture();
  float temperature = readTemperature();
  float humidity = readHumidity();
  int distance = readUltrasonic();
  int light = readLDR();

  // Upload data to Firebase
  Firebase.pushString(firebaseData, "/sensor_data/" + uniqueID + "/temperature", String(temperature));
  Firebase.pushString(firebaseData, "/sensor_data/" + uniqueID + "/humidity", String(humidity));
  Firebase.pushString(firebaseData, "/sensor_data/" + uniqueID + "/light_intensity", String(light));
  Firebase.pushString(firebaseData, "/sensor_data/" + uniqueID + "/pump_status", String(digitalRead(RELAY_PIN)));
  Firebase.pushString(firebaseData, "/sensor_data/" + uniqueID + "/soil_moisture", String(soil_moisture));
  Firebase.pushString(firebaseData, "/sensor_data/" + uniqueID + "/water_level", String(distance));

  // Control pump and determine sleep time based on soil moisture
  if (soil_moisture < 40) {
    digitalWrite(RELAY_PIN, LOW);
    delay(5000);
    digitalWrite(RELAY_PIN, HIGH);

    float sleep_seconds = predict_water_time(temperature, humidity, light);
    float tank_seconds = predict_tank_empty_time(distance, temperature, humidity, light);
    uint64_t sleep_time_us = min(sleep_seconds, tank_seconds) * US_TO_S_FACTOR;
    sleep_time_us = max(sleep_time_us, (uint64_t)(MIN_SLEEP_TIME_SEC * US_TO_S_FACTOR));

    Serial.print("Calculated sleep time: ");
    Serial.print(sleep_time_us / US_TO_S_FACTOR);
    Serial.println(" seconds");

    goToSleep(sleep_time_us);
  } else {
    Serial.println("Using default sleep time");
    goToSleep(DEFAULT_SLEEP_TIME_SEC * US_TO_S_FACTOR);
  }
}

/**
 * Reads soil moisture level and controls pump accordingly
 * @return Soil moisture percentage (0-100)
 */
int readSoilMoisture() {
  int soilMoisture = analogRead(SOIL_MOISTURE_PIN);
  int moisturePercentage = map(soilMoisture, 0, 4095, 0, 100);
  moisturePercentage = constrain(moisturePercentage, 0, 100);

  Serial.print("Soil Moisture: ");
  Serial.print(moisturePercentage);
  Serial.print("% | ");
  Blynk.virtualWrite(V1, moisturePercentage);

  // Control pump based on moisture level
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
 * @return Relative humidity percentage
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
 * Reads light intensity from LDR
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
 * Reads all sensors and updates their values
 */
void readAllSensors() {
  readSoilMoisture();
  readTemperature();
  readHumidity();
  readUltrasonic();
  readLDR();
}