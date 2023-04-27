#include <Wire.h>
#include "OLED.h"

#define OLED_ADDR 0x3C
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 32

OLED::OLED() {}

void OLED::begin() {
  Wire.begin();
  sendCommand(0xAE); // display off
  sendCommand(0xD5); // set display clock divide ratio/oscillator frequency
  sendCommand(0x80); // recommended value
  sendCommand(0xA8); // set multiplex ratio
  sendCommand(SCREEN_HEIGHT - 1);
  sendCommand(0xD3); // set display offset
  sendCommand(0x00);
  sendCommand(0x40); // set display start line
  sendCommand(0x8D); // charge pump
  sendCommand(0x14); // turn on charge pump
  sendCommand(0x20); // set memory mode
  sendCommand(0x00); // horizontal addressing mode
  sendCommand(0xA0); // set segment remap
  sendCommand(0xC8); // set com output scan direction
  sendCommand(0xDA); // set com pins hardware configuration
  sendCommand(0x12);
  sendCommand(0x81); // set contrast control
  sendCommand(0xCF);
  sendCommand(0xD9); // set pre-charge period
  sendCommand(0xF1);
  sendCommand(0xDB); // set vcomh deselect level
  sendCommand(0x40);
  sendCommand(0xA4); // display on resume
  sendCommand(0xA6); // normal display
  clearDisplay();
  sendCommand(0xAF); // display on
}

void OLED::clearDisplay() {
  memset(buffer, 0, sizeof(buffer));
}

void OLED::drawPixel(int16_t x, int16_t y, uint16_t color) {
  if (x < 0 || x >= SCREEN_WIDTH || y < 0 || y >= SCREEN_HEIGHT) {
    return;
  }
  int buffer_index = (int)x + ((int)y / 8) * SCREEN_WIDTH;
  buffer[buffer_index] |= (1 << (y % 8));
}

void OLED::display() {
  sendCommand(0x21); // set column address
  sendCommand(0x00); // start column = 0
  sendCommand(SCREEN_WIDTH - 1); // end column = SCREEN_WIDTH - 1
  sendCommand(0x22); // set page address
  sendCommand(0x00); // start page = 0
  sendCommand(SCREEN_HEIGHT / 8 - 1); // end page = SCREEN_HEIGHT / 8 - 1
  for (int i = 0; i < SCREEN_WIDTH * SCREEN_HEIGHT / 8; i += 16) {
    Wire.beginTransmission(OLED_ADDR);
    Wire.write(0x40);
    for (int j = 0; j < 16; j++) {
      Wire.write(buffer[i + j]);
    }
    Wire.endTransmission();
  }
}

void OLED::sendCommand(byte cmd) {
  Wire.beginTransmission(OLED_ADDR);
  Wire.write(0x00);
  Wire.write(cmd);
  Wire.endTransmission();
}

OLED oled;

