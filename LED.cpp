#include <Adafruit_NeoPixel.h>
#include "LED.h"
#include "state.h"

const int DEBUG_LED = 1;
const int NUM_LED_DEBUG = 32;
const int LED_PIN = 2;
Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_LEDS, LED_PIN, NEO_GRB + NEO_KHZ800);

bool ledsChanged = false;
time_t lastLedChange = 0;

time_t getLastLedChangeDelta() {
  return state.now - lastLedChange;
}

uint32_t ledColor(uint8_t r, uint8_t g, uint8_t b) {
  return Adafruit_NeoPixel::Color(r, g, b);
}

void setLed(uint8_t n, uint32_t c) {
  uint32_t oldC = strip.getPixelColor(n);
  if (oldC != c) {
    lastLedChange = state.now;
    ledsChanged = true;
    strip.setPixelColor(n, c);
  }
}

void setLed(uint8_t n, uint8_t r, uint8_t g, uint8_t b) {
  setLed(n, ledColor(r, g, b));
}

bool sendLeds() {
  if (ledsChanged & strip.canShow()) {
    if (DEBUG_LED) {
      Serial.print("LEDs: ");
      for (uint16_t i = 0; i < NUM_LED_DEBUG; i++) {
        Serial.print((strip.getPixelColor(i) >> 8) % 16 , HEX);
      }
      Serial.println();
    }
    strip.show();
    ledsChanged = false;
    return true;
  }
  else {
    if (DEBUG_LED) {
      Serial.println("No LED output");
    }
    return false;
  }
}

void initLeds() {
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);
  strip.begin();
  sendLeds(); // Initialize all pixels to 'off'
}

