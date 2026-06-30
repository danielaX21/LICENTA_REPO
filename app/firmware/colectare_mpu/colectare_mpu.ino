#include <Wire.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>

Adafruit_MPU6050 mpu;
const int SAMPLE_INTERVAL_US = 1000;

void setup() {
  Serial.begin(115200);
  while (!Serial) delay(10);

  Wire.begin(21, 22);
  Wire.setClock(400000);

  if (!mpu.begin(0x68)) {
    Serial.println("EROARE: MPU nu raspunde la 0x68");
    Serial.println("Verifica firele VCC/GND/SDA/SCL.");
    while (1) delay(10);
  }

  mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
  mpu.setGyroRange(MPU6050_RANGE_500_DEG);
  mpu.setFilterBandwidth(MPU6050_BAND_184_HZ);

  Serial.println("READY");
  delay(500);
}

void loop() {
  static unsigned long lastSample = 0;
  unsigned long now = micros();

  if (now - lastSample >= SAMPLE_INTERVAL_US) {
    lastSample = now;
    sensors_event_t a, g, t;
    mpu.getEvent(&a, &g, &t);
    Serial.print(a.acceleration.x, 4);
    Serial.print(',');
    Serial.print(a.acceleration.y, 4);
    Serial.print(',');
    Serial.println(a.acceleration.z, 4);
  }
}
