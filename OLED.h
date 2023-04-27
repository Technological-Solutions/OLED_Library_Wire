#ifndef OLED_H
#define OLED_H

#include <Arduino.h>

class OLED {
public:
  OLED();
  void begin();
  void clearDisplay();
  void drawPixel(int16_t x, int16_t y, uint16_t color);
  void display();
private:
  void sendCommand(byte cmd);
  byte buffer[1024] = {};
};

extern OLED oled;

#endif
