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

void hal_LedTurn(void);

void hal_LedInit(void);
void hal_LedProc(void);

/* LED特效控制执行函数，输入的部分
 * type - 需要驱动的LED类型，使用枚举
 * cmd  - 需要使用的LED特效逻辑
 * clr  - 确认是否运行，还是处于静默状态
 * * * */
void LedMsgInput(unsigned char type, LED_EFFECT_TEPEDEF cmd, unsigned char clr);

#endif