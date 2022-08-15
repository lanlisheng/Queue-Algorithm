#ifndef _LED_H_
#define _LED_H_

#define LED_EFFECT_END 0xFFFE
#define LED_EFFECT_AGN 0xFFFF

typedef enum { LED, BUZ, LED_SUM } LED_TYPEDEF;

typedef enum {
  LED_DARK,
  LED_LIGHT,
  LED_BLINK1,
  LED_BLINK2,
  LED_BLINK3,
  LED_BLINK4
} LED_EFFECT_TYPEDEF;

#endif