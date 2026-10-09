#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ST7789.h>

#define TFT_CS -1
#define TFT_DC D6
#define TFT_RST D7

Adafruit_ST7789 tft = Adafruit_ST7789(TFT_CS, TFT_DC, TFT_RST);

const int buttons[] = {D0, D1, D2, D3, D4};
const char* labels[] = {"UP", "DOWN", "LEFT", "RIGHT", "SELECT"};

float goldPrice = 5842.50;
float usdTry = 42.75;
float eurTry = 49.60;

int selected = 0;
bool lastState[] = {HIGH, HIGH, HIGH, HIGH, HIGH};

uint16_t bg = 0x0841;
uint16_t gold = 0xFEA0;
uint16_t muted = 0x9CF3;
uint16_t white = 0xFFFF;
uint16_t green = 0x47E9;

void drawDashboard() {
  tft.fillScreen(bg);

  tft.setTextSize(2);
  tft.setTextColor(gold);
  tft.setCursor(12, 12);
  tft.print("AURUM");

  tft.setTextSize(1);
  tft.setTextColor(muted);
  tft.setCursor(13, 36);
  tft.print("PERSONAL ASSET TRACKER");

  tft.drawFastHLine(12, 53, 216, muted);

  tft.setTextColor(muted);
  tft.setCursor(12, 66);
  tft.print("GOLD / GRAM");

  tft.setTextSize(2);
  tft.setTextColor(white);
  tft.setCursor(12, 81);
  tft.print(goldPrice, 2);
  tft.print(" TL");

  tft.setTextSize(1);
  tft.setTextColor(muted);
  tft.setCursor(12, 119);
  tft.print("USD / TRY");

  tft.setTextSize(2);
  tft.setTextColor(white);
  tft.setCursor(12, 133);
  tft.print(usdTry, 2);

  tft.setTextSize(1);
  tft.setTextColor(muted);
  tft.setCursor(130, 119);
  tft.print("EUR / TRY");

  tft.setTextSize(2);
  tft.setTextColor(white);
  tft.setCursor(130, 133);
  tft.print(eurTry, 2);

  tft.drawFastHLine(12, 169, 216, muted);

  tft.setTextSize(1);
  tft.setTextColor(green);
  tft.setCursor(12, 180);
  tft.print("DEMO MODE");

  tft.setTextColor(muted);
  tft.setCursor(12, 196);
  tft.print("Prices are not live");

  tft.setTextColor(gold);
  tft.setCursor(12, 222);
  tft.print(labels[selected]);
}

void setup() {
  for (int i = 0; i < 5; i++) {
    pinMode(buttons[i], INPUT_PULLUP);
  }

  SPI.begin(D8, D9, D10, -1);

  tft.init(240, 240);
  tft.setRotation(0);
  tft.setTextWrap(false);

  drawDashboard();
}

void loop() {
  for (int i = 0; i < 5; i++) {
    bool state = digitalRead(buttons[i]);

    if (lastState[i] == HIGH && state == LOW) {
      selected = i;
      drawDashboard();
    }

    lastState[i] = state;
  }

  delay(20);
}
