# 📌 Pengukur Jarak Digital dengan Arduino Nano & OLED

Proyek ini adalah alat pengukur jarak digital berbasis **Arduino Nano** yang menggunakan **sensor ultrasonik HC-SR04** untuk mengukur jarak dan menampilkannya di **OLED SSD1306 (I2C, 128x32)**. Rangkaian ini juga menggunakan **modul TP4056 dengan boost converter 5V** untuk daya dari **baterai LiPo**.

![[Wiring Diagram]([wiring_diagram.jpg](https://github.com/teamichibot/PenggarisDigital/blob/main/ICHIBOT.png))](https://github.com/teamichibot/PenggarisDigital/blob/main/ICHIBOT.png)
---

## 📋 Fitur
✅ **Mengukur jarak menggunakan HC-SR04**  
✅ **Menampilkan hasil di OLED SSD1306 (128x32)**  
✅ **Menampilkan hasil di Serial Monitor**  
✅ **Kalkulasi total jarak dengan panjang body alat**  
✅ **Menggunakan daya baterai LiPo + TP4056**  
✅ **Sakelar untuk menghidupkan/mematikan perangkat**  

---

## 🛠️ Komponen yang Dibutuhkan
| No  | Komponen                         | Jumlah | Link Pembelian |
|-----|----------------------------------|--------|----------------|
| 1   | Arduino Nano Type C              | 1      | [Shopee](https://s.shopee.co.id/9pPbwEx4MN) |
| 2   | Sensor Ultrasonik HC-SR04         | 1      | [Shopee](https://s.shopee.co.id/20gkbo9tQd) |
| 3   | OLED Display SSD1306 (128x32)     | 1      | [Shopee](https://s.shopee.co.id/6V99yDxRce) |
| 4   | Modul Charger TP4056 + Boost 5V   | 1      | [Shopee](https://s.shopee.co.id/4fhVmxg4xF) |
| 5   | Baterai LiPo 3.7V 1000mAh         | 1      | [Shopee](https://s.shopee.co.id/5VGcn1glLF) |
| 6   | PCB Lubang 4x6 cm                 | 1      | [Shopee](https://s.shopee.co.id/9UmlXvhaZV) |
| 7   | Sakelar Geser Slide Switch SS-12D10 | 1      | [Shopee](https://s.shopee.co.id/8pX4kmm5uX) |
| 8   | Heatsink 9x9x5 mm                 | 1      | [Shopee](https://s.shopee.co.id/4q0vzu7H7b) |
| 9   | Kabel Jumper                      | -      | [Shopee](https://shopee.co.id/ichibot) |

---

## ⚡ Skema Rangkaian
### 1️⃣ Koneksi HC-SR04 ke Arduino Nano
| HC-SR04 | Arduino Nano |
|---------|-------------|
| VCC     | 5V          |
| GND     | GND         |
| TRIG    | D3          |
| ECHO    | D2          |

### 2️⃣ Koneksi OLED SSD1306 ke Arduino Nano (I2C)
| OLED SSD1306 | Arduino Nano |
|-------------|--------------|
| VCC         | 5V           |
| GND         | GND          |
| SCL         | A5           |
| SDA         | A4           |

### 3️⃣ Koneksi TP4056 + Boost Converter 5V
| TP4056 (Boost) | Komponen     |
|---------------|-------------|
| BAT+         | Baterai (+)  |
| BAT-         | Baterai (-)  |
| IN+          | Sakelar ke Baterai (+) |
| IN-          | Sakelar ke Baterai (-) |
| VOUT+        | 5V Arduino & OLED |
| VOUT-        | GND Arduino & OLED |

---

## 📜 Kode Program
```cpp
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// Konfigurasi OLED
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 32
#define OLED_RESET -1
#define SCREEN_ADDRESS 0x3C
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// Konfigurasi HC-SR04
#define TRIG_PIN 3
#define ECHO_PIN 2
#define BODY_LENGTH 8.5 // Panjang body dalam cm

void setup() {
  Serial.begin(9600);

  if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("Gagal menginisialisasi OLED"));
    for (;;);
  }
  
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.println("Pengukur Jarak");
  display.println("Menginisialisasi...");
  display.display();
  delay(2000);

  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  display.clearDisplay();
}

void loop() {
  long duration;
  float distance, totalDistance;

  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  duration = pulseIn(ECHO_PIN, HIGH);
  distance = ((duration * 0.034) / 2) * 1.045;
  totalDistance = distance + BODY_LENGTH;

  display.clearDisplay();
  display.setTextSize(2);
  display.setCursor(0, 0);
  display.print("S: ");
  display.print(distance, 1);
  display.println("cm");
  display.setCursor(0, 18);
  display.print("B: ");
  display.print(totalDistance, 1);
  display.println("cm");
  display.display();

  Serial.print("Jarak Sensor: ");
  Serial.print(distance, 1);
  Serial.println("cm");
  Serial.print("Jarak Total: ");
  Serial.print(totalDistance, 1);
  Serial.println("cm");

  delay(1000);
}
```

⚙️ Cara Menggunakan
1️⃣ Pasang semua komponen sesuai skema rangkaian di atas.
2️⃣ Sambungkan Arduino Nano ke PC dan unggah kode di atas menggunakan Arduino IDE.
3️⃣ Nyalakan sakelar untuk menyalakan perangkat.
4️⃣ Lihat hasil pengukuran di OLED display & Serial Monitor.
5️⃣ Alat siap digunakan sebagai pengukur jarak digital.

💡 Pengembangan Lebih Lanjut
✅ Menggunakan baterai berkapasitas lebih besar untuk daya lebih lama.
✅ Menambahkan fitur pemrosesan data untuk kalibrasi otomatis.
✅ Menampilkan grafik perubahan jarak di OLED.

📜 Lisensi
Proyek ini open-source dan dapat digunakan oleh siapa saja untuk tujuan edukasi dan non-komersial. Jika menggunakan proyek ini, mohon sertakan atribusi ke repository ini. 😊
