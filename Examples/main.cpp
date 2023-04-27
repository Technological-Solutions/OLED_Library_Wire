#include <Arduino.h>
#include "OLED.h"

#define OLED_WIDTH 128
#define OLED_HEIGHT 32

int freq = 1;

void setup() {
  oled.begin();
}

void loop() {
  oled.clearDisplay();
  delay(100);
  for (int i = 0; i < OLED_WIDTH; i++) {
    float value = sin(freq * i * PI / OLED_WIDTH) * OLED_HEIGHT / 2 + OLED_HEIGHT / 2;
    oled.drawPixel(i, value, 1);
  }
  freq++;
  oled.display();
  delay(1000);
}
