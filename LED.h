#ifndef _LED_H_
#define _LED_H_

const uint16 NUM_LEDS = 105;

extern uint32_t ledColor(uint8_t r, uint8_t g, uint8_t b);
extern void setLed(uint8_t n, uint8_t r, uint8_t g, uint8_t b);
extern void setLed(uint8_t n, uint32_t c);
extern bool sendLeds();

extern void initLeds();
#endif
