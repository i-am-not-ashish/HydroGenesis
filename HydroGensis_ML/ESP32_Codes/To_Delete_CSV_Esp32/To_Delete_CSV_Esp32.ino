#include <SPIFFS.h>

void setup() {
  Serial.begin(115200);
  Serial.println("Setup Started...");

  // Initialize SPIFFS
  if (!SPIFFS.begin(true)) {
    Serial.println("Failed to mount SPIFFS!");
    return;
  }
  Serial.println("SPIFFS mounted successfully.");

  // Delete the CSV file
  deleteCSVFile();
}

void loop() {
  // Your main code here
}

void deleteCSVFile() {
  if (SPIFFS.remove("/sensor_data.csv")) {
    Serial.println("CSV file deleted successfully.");
  } else {
    Serial.println("Failed to delete CSV file. File may not exist.");
  }
}