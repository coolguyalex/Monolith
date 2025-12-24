
#include <Wire.h>
#include <U8g2lib.h>
#include <BH1750.h>
#include <Adafruit_BME280.h>
#include <Adafruit_MPR121.h>
#include <QMC5883LCompass.h>

// ---------- OLED (U8g2, page buffer) ----------
U8G2_SSD1306_128X64_NONAME_1_HW_I2C u8g2(U8G2_R0, U8X8_PIN_NONE);

// ---------- Sensors ----------
BH1750 lightMeter;
Adafruit_BME280 bme;
Adafruit_MPR121 cap = Adafruit_MPR121();
QMC5883LCompass mag;

// ---------- Pins ----------
const int POT0 = A0;
const int POT1 = A1;
const int POT2 = A2;

const int PIR_PIN = 2;     // HC-SR501 OUT -> D2
const int BUTTON_PIN = 7;  // HW-483 S -> D7 (active LOW)

// ---------- Paging ----------
const int NUM_PAGES = 3;
int page = 0;

// ---------- Button debounce ----------
int lastButtonReading = HIGH;
int stableButtonState = HIGH;
unsigned long lastDebounceMs = 0;
const unsigned long debounceDelayMs = 150;

// ---------- Timing ----------
unsigned long lastDisplayMs = 0;
unsigned long lastSerialMs  = 0;
const unsigned long displayIntervalMs = 150; // OLED refresh
const unsigned long serialIntervalMs  = 50;  // 20 Hz serial stream

// ---------- Pots (smoothing) ----------
float smooth0 = 0, smooth1 = 0, smooth2 = 0;

// ---------- Latest readings ----------
float lux = 0;
float tC = 0, hum = 0, p_hPa = 0;
int magX = 0, magY = 0, magZ = 0;
int pir = 0;
uint16_t touchMask = 0;

// ---- MPR121 register addresses ----
#define MPR121_ADDR      0x5A
#define MPR121_SOFTRESET 0x80
#define MPR121_ECR       0x5E
#define MPR121_DEBOUNCE  0x5B
#define MPR121_CONFIG1   0x5C
#define MPR121_CONFIG2   0x5D

// Filter / baseline tracking (MPR121 datasheet naming)
#define MPR121_MHDR 0x2B
#define MPR121_NHDR 0x2C
#define MPR121_NCLR 0x2D
#define MPR121_FDLR 0x2E
#define MPR121_MHDF 0x2F
#define MPR121_NHDF 0x30
#define MPR121_NCLF 0x31
#define MPR121_FDLF 0x32
#define MPR121_NHDT 0x33
#define MPR121_NCLT 0x34
#define MPR121_FDLT 0x35

static void mpr121Write(uint8_t reg, uint8_t val) {
  Wire.beginTransmission(MPR121_ADDR);
  Wire.write(reg);
  Wire.write(val);
  Wire.endTransmission();
}

static uint8_t mpr121Read(uint8_t reg) {
  Wire.beginTransmission(MPR121_ADDR);
  Wire.write(reg);
  Wire.endTransmission(false);
  Wire.requestFrom(MPR121_ADDR, (uint8_t)1);
  return Wire.available() ? Wire.read() : 0xFF;
}

// Call once at startup. Treat as required boilerplate.
bool mpr121HardInit(uint8_t touchThresh = 6, uint8_t releaseThresh = 3) {
  // 1) Force stop mode
  mpr121Write(MPR121_ECR, 0x00);
  delay(5);

  // 2) Soft reset
  mpr121Write(MPR121_SOFTRESET, 0x63);
  delay(20); // longer reset settle for clones

  // 3) Stop mode again
  mpr121Write(MPR121_ECR, 0x00);
  delay(5);

  // 4) Touch/release thresholds for all 12 electrodes
  for (uint8_t i = 0; i < 12; i++) {
    mpr121Write(0x41 + i * 2, touchThresh);
    mpr121Write(0x42 + i * 2, releaseThresh);
  }

  // 5) Filter & baseline tracking registers
  mpr121Write(MPR121_MHDR, 0x01);
  mpr121Write(MPR121_NHDR, 0x01);
  mpr121Write(MPR121_NCLR, 0x00);
  mpr121Write(MPR121_FDLR, 0x00);

  mpr121Write(MPR121_MHDF, 0x01);
  mpr121Write(MPR121_NHDF, 0x01);
  mpr121Write(MPR121_NCLF, 0xFF);
  mpr121Write(MPR121_FDLF, 0x02);

  mpr121Write(MPR121_NHDT, 0x00);
  mpr121Write(MPR121_NCLT, 0x00);
  mpr121Write(MPR121_FDLT, 0x00);

  // debounce
  mpr121Write(MPR121_DEBOUNCE, 0x11);

  // 6) CONFIG1 / CONFIG2
  mpr121Write(MPR121_CONFIG1, 0x10);
  mpr121Write(MPR121_CONFIG2, 0x20);

  // 7) Re-enable scanning: 12 electrodes
  mpr121Write(MPR121_ECR, 0x8C);
  delay(50); // give baseline engine time to start

  uint8_t ecr = mpr121Read(MPR121_ECR);
  return (ecr == 0x8C);
}

float toPercent(float raw) { return raw * 100.0f / 1023.0f; }

void handleButton() {
  int reading = digitalRead(BUTTON_PIN);

  if (reading != lastButtonReading) {
    lastDebounceMs = millis();
    lastButtonReading = reading;
  }

  if ((millis() - lastDebounceMs) > debounceDelayMs) {
    if (reading != stableButtonState) {
      stableButtonState = reading;
      if (stableButtonState == LOW) {
        page = (page + 1) % NUM_PAGES;
        lastDisplayMs = 0; // force immediate redraw
      }
    }
  }
}

void readPots() {
  int raw0 = analogRead(POT0);
  int raw1 = analogRead(POT1);
  int raw2 = analogRead(POT2);

  smooth0 = 0.85f * smooth0 + 0.15f * raw0;
  smooth1 = 0.85f * smooth1 + 0.15f * raw1;
  smooth2 = 0.85f * smooth2 + 0.15f * raw2;
}

void readSensors() {
  pir = digitalRead(PIR_PIN);

  lux = lightMeter.readLightLevel();

  tC = bme.readTemperature();
  hum = bme.readHumidity();
  p_hPa = bme.readPressure() / 100.0f;

  mag.read();
  magX = mag.getX();
  magY = mag.getY();
  magZ = mag.getZ();

  // IMPORTANT: read touch AFTER the hard init, and do NOT call cap.begin() again later
  touchMask = cap.touched();
}

void printSerialForPd() {
  // MONO pot0 pot1 pot2 lux tC hum p_hPa magX magY magZ pir touchMask t0..t11
  Serial.print("MONO ");

  Serial.print((int)smooth0); Serial.print(' ');
  Serial.print((int)smooth1); Serial.print(' ');
  Serial.print((int)smooth2); Serial.print(' ');

  Serial.print(lux, 1);   Serial.print(' ');
  Serial.print(tC, 2);    Serial.print(' ');
  Serial.print(hum, 1);   Serial.print(' ');
  Serial.print(p_hPa, 1); Serial.print(' ');

  Serial.print(magX); Serial.print(' ');
  Serial.print(magY); Serial.print(' ');
  Serial.print(magZ); Serial.print(' ');

  Serial.print(pir); Serial.print(' ');

  Serial.print(touchMask); Serial.print(' ');

  for (int i = 0; i < 12; i++) {
    Serial.print((touchMask & (1 << i)) ? 1 : 0);
    if (i < 11) Serial.print(' ');
  }

  Serial.println();
}

// ---------- OLED drawing helpers ----------
void drawHeader(const char* title) {
  u8g2.setFont(u8g2_font_6x10_tf);
  u8g2.setCursor(0, 10);
  u8g2.print(title);
}

void drawPage1_Pots() {
  float p0 = toPercent(smooth0);
  float p1 = toPercent(smooth1);
  float p2 = toPercent(smooth2);

  u8g2.firstPage();
  do {
    drawHeader("PAGE 1/3  POTS");

    u8g2.setFont(u8g2_font_6x10_tf);

    u8g2.setCursor(0, 26);
    u8g2.print("A0: "); u8g2.print(p0, 0); u8g2.print("%");

    u8g2.setCursor(0, 40);
    u8g2.print("A1: "); u8g2.print(p1, 0); u8g2.print("%");

    u8g2.setCursor(0, 54);
    u8g2.print("A2: "); u8g2.print(p2, 0); u8g2.print("%");
  } while (u8g2.nextPage());
}

void drawPage2_EnvMagPir() {
  u8g2.firstPage();
  do {
    drawHeader("PAGE 2/3  ENV + MAG + PIR");

    u8g2.setFont(u8g2_font_5x8_tf);

    u8g2.setCursor(0, 22);
    u8g2.print("T "); u8g2.print(tC, 1); u8g2.print("C  H "); u8g2.print(hum, 0); u8g2.print("%");

    u8g2.setCursor(0, 32);
    u8g2.print("P "); u8g2.print(p_hPa, 0); u8g2.print(" hPa  Lux "); u8g2.print(lux, 0);

    u8g2.setCursor(0, 42);
    u8g2.print("Mag X "); u8g2.print(magX);

    u8g2.setCursor(0, 52);
    u8g2.print("Mag Y "); u8g2.print(magY);

    u8g2.setCursor(0, 62);
    u8g2.print("Mag Z "); u8g2.print(magZ);
    u8g2.print("  PIR "); u8g2.print(pir);
  } while (u8g2.nextPage());
}

void drawPage3_MPR121() {
  u8g2.firstPage();
  do {
    drawHeader("PAGE 3/3  CAP TOUCH");

    u8g2.setFont(u8g2_font_5x8_tf);

    u8g2.setCursor(0, 22);
    u8g2.print("Mask: "); u8g2.print(touchMask);

    u8g2.setCursor(0, 34);
    u8g2.print("Touched: ");
    bool any = false;
    for (int i = 0; i < 12; i++) {
      if (touchMask & (1 << i)) {
        any = true;
        u8g2.print(i);
        u8g2.print(' ');
      }
    }
    if (!any) u8g2.print("-");

    u8g2.setCursor(0, 50);
    u8g2.print("Bits: ");
    for (int i = 0; i < 12; i++) {
      u8g2.print((touchMask & (1 << i)) ? '1' : '0');
    }

  } while (u8g2.nextPage());
}

void setup() {
  Serial.begin(9600);

  Wire.begin();
  Wire.setClock(100000);
  delay(200);

  pinMode(BUTTON_PIN, INPUT);
  pinMode(PIR_PIN, INPUT);

  // OLED (U8g2 uses 8-bit I2C address)
  u8g2.setI2CAddress(0x3C << 1);
  u8g2.begin();

  // Other sensors
  lightMeter.begin(BH1750::CONTINUOUS_HIGH_RES_MODE);
  if (!bme.begin(0x76)) bme.begin(0x77);
  mag.init();

  // ---- MPR121: DO THIS ONCE. DO NOT CALL cap.begin() AGAIN LATER. ----
  if (!cap.begin(0x5A)) {
    Serial.println("MPR121 not found at 0x5A");
  } else {
    Serial.println("MPR121 I2C OK, applying hard init...");
    bool ok = mpr121HardInit(6, 3);
    Serial.print("MPR121 hard init ECR ok? ");
    Serial.println(ok ? "YES" : "NO");
    // Give baseline engine time to populate after enabling scanning
    delay(300);
  }

  // Boot screen
  u8g2.firstPage();
  do {
    u8g2.setFont(u8g2_font_6x10_tf);
    u8g2.setCursor(0, 14); u8g2.print("Monolith OLED (U8g2)");
    u8g2.setCursor(0, 30); u8g2.print("1:Pots  2:Env  3:Touch");
    u8g2.setCursor(0, 46); u8g2.print("Serial token: MONO");
  } while (u8g2.nextPage());

  delay(600);
}

void loop() {
  handleButton();
  readPots();

  if (millis() - lastSerialMs >= serialIntervalMs) {
    lastSerialMs = millis();
    readSensors();
    printSerialForPd();
  }

  if (millis() - lastDisplayMs >= displayIntervalMs) {
    lastDisplayMs = millis();

    switch (page) {
      case 0: drawPage1_Pots(); break;
      case 1: drawPage2_EnvMagPir(); break;
      case 2: drawPage3_MPR121(); break;
    }
  }
}
