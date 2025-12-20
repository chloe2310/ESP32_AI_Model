#include <Arduino.h>
#include <DHT.h>
#include <Wire.h>
#include <BH1750.h>
#include "ESP32_S3_AI_Model_inferencing.h"  // Thư viện Edge Impulse

#define DHTPIN 18
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

BH1750 lightMeter;

#define LED_PIN 5  // Chân LED, bạn có thể đổi nếu cần

void setup() {
  Serial.begin(115200);
  dht.begin();
  Wire.begin(6, 7); // SDA = 6, SCL = 7
  lightMeter.begin();

  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW); // tắt LED ban đầu

  delay(2000);
  Serial.println(" Start sensing & AI inference...");
}

void loop() {
  float temp = dht.readTemperature();
  float humid = dht.readHumidity();
  float lux = lightMeter.readLightLevel();

  if (isnan(temp) || isnan(humid) || isnan(lux)) {
    Serial.println(" Sensor read failed!");
    delay(1000);
    return;
  }

  Serial.printf(" Temperature: %.2f°C    Humidity: %.2f%%    Lux: %.2f lx\n", temp, humid, lux);

  float input[3] = { temp, humid, lux }; // tạo ra vector đặc trưng gồm 3 phần tử

  ei::signal_t signal; // truyền dữ liệu vào mô hình AI đã nhúng
  signal.total_length = 3;
  signal.get_data = [input](size_t offset, size_t length, float *out_ptr) -> int {
    memcpy(out_ptr, input + offset, length * sizeof(float));
    return 0;
  };

  ei_impulse_result_t result = {};
  EI_IMPULSE_ERROR res = run_classifier(&signal, &result, false);
/*Lệnh run_classifier(...) thực hiện inference:
Nó đưa vector [temp, humid, lux] vào mô hình đã huấn luyện.
Tính toán qua các lớp học máy như K-means distance hoặc autoencoder reconstruction error.
Trả về result.anomaly là một số thực (float), càng cao càng "lạ".
*/ 


  if (result.anomaly > 0.5) {
    Serial.println("Anomaly detected!");
    digitalWrite(LED_PIN, HIGH); // bật đèn cảnh báo
  } else {
    Serial.println("Normal state.");
    digitalWrite(LED_PIN, LOW); // tắt đèn
  }

  delay(3000);
}
