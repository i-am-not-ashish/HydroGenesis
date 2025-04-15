#define uS_TO_S_FACTOR 1000000ULL

void setup() {
  // Initialize serial with timeout
  Serial.begin(115200);
  delay(1000); // Give serial time to initialize
  
  // Print diagnostic information
  Serial.println("\n\nESP32 Deep Sleep Test");
  Serial.printf("CPU Freq: %d MHz\n", ESP.getCpuFreqMHz());
  Serial.printf("Free Heap: %d bytes\n", ESP.getFreeHeap());
  
  // Print reset reason
  esp_reset_reason_t reason = esp_reset_reason();
  Serial.printf("Reset Reason: %d\n", reason);
  
  // Configure sleep
  uint64_t sleep_time = 10 * uS_TO_S_FACTOR;
  esp_sleep_enable_timer_wakeup(sleep_time);
  
  Serial.printf("Going to sleep for %llu seconds...\n", sleep_time/uS_TO_S_FACTOR);
  Serial.flush();
  delay(100);
  
  esp_deep_sleep_start();
}

void loop() {}