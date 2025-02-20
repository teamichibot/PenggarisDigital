#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// Konfigurasi OLED
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 32
#define OLED_RESET -1 // Tidak ada pin reset, gunakan -1
#define SCREEN_ADDRESS 0x3C // Alamat I2C untuk OLED
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// Konfigurasi HC-SR04
#define TRIG_PIN 3 // Pin TRIG HC-SR04
#define ECHO_PIN 2 // Pin ECHO HC-SR04

// Panjang body (85mm = 8.5cm)
#define BODY_LENGTH 8.5 // Panjang body dalam cm

void setup() {
  // Inisialisasi Serial Monitor
  Serial.begin(9600);

  // Inisialisasi OLED
  if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("Gagal menginisialisasi OLED"));
    for (;;); // Hentikan jika OLED gagal
  }
  
  // Pesan awal
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.println("Pengukur Jarak");
  display.println("Menginisialisasi...");
  display.display();
  delay(2000);

  // Konfigurasi pin HC-SR04
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  // Bersihkan layar OLED
  display.clearDisplay();
}

void loop() {
  // Variabel untuk durasi dan jarak
  long duration;
  float distance, totalDistance;

  // Kirim pulsa ke TRIG
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  // Baca pulsa dari ECHO
  duration = pulseIn(ECHO_PIN, HIGH);

  // Hitung jarak dalam cm
  distance = ((duration * 0.034) / 2) * 1.045;

  // Hitung total jarak (jarak dari sensor + panjang body)
  totalDistance = distance + BODY_LENGTH;

  // Tampilkan jarak di OLED
  display.clearDisplay();
  // display.setCursor(0, 0);
  // display.setTextSize(1);
  // display.println("Pengukur Jarak:");
  display.setTextSize(2);
  display.setCursor(0, 0);
  display.print("S: ");
  display.print(distance, 1); // Jarak sensor
  display.println("cm");
  display.setCursor(0, 18);
  display.print("B: ");
  display.print(totalDistance, 1); // Total jarak
  display.println("cm");
  display.display();

  // Debug ke Serial Monitor
  Serial.print("Jarak Sensor: ");
  Serial.print(distance, 1);
  Serial.println("cm");
  Serial.print("Jarak Total: ");
  Serial.print(totalDistance, 1);
  Serial.println("cm");

  delay(1000); // Tunggu 500ms sebelum pembacaan berikutnya
}
