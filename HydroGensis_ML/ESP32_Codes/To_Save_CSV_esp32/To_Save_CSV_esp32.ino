#include <WiFi.h>
#include <SPIFFS.h>
#include <WebServer.h>

// WiFi credentials
const char* ssid = "********";      // Replace with your WiFi SSID
const char* password = "********";  // Replace with your WiFi password

// Create a web server on port 80
WebServer server(80);

void setup() {
  Serial.begin(115200);
  Serial.println("Setup Started...");

  // Initialize SPIFFS
  if (!SPIFFS.begin(true)) {
    Serial.println("Failed to mount SPIFFS!");
    return;
  }
  Serial.println("SPIFFS mounted successfully.");

  // Connect to WiFi
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi...");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi Connected!");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());

  // Serve the CSV file
  server.on("/data", HTTP_GET, []() {
    File file = SPIFFS.open("/sensor_data.csv", "r");
    if (!file) {
      server.send(500, "text/plain", "Failed to open file!");
      return;
    }

    // Send the file to the client
    server.streamFile(file, "text/csv");
    file.close();
  });

  // Start the server
  server.begin();
  Serial.println("HTTP server started.");
}

void loop() {
  server.handleClient();  // Handle client requests
}