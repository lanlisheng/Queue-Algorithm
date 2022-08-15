#include "led.h"
#include "time.h"

static void hal_Led1Drive(unsigned char sta);
static void hal_Led2Drive(unsigned char sta);
static void hal_Led3Drive(unsigned char sta);
static void hal_Led4Drive(unsigned char sta);

/* Led执行函数数组 */
void (*hal_LedDrive[])(unsigned char) = {hal_Led1Drive, hal_Led2Drive,
                                         hal_Led3Drive, hal_Led4Drive};

/* Led特效存储数组 */
unsigned short Led_Dark[] = {0, 10, LED_EFFECT_END};
unsigned short Led_Light[] = {1, 10, LED_EFFECT_END};
unsigned short Led_Blink1[] = {1, 50, 0, 50, 1, 50, 0, 50, LED_EFFECT_END};
unsigned short Led_Blink2[] = {1, 10, 0, 10, 1, 10, 0, 210, LED_EFFECT_AGN, 4};
unsigned short Led_Blink3[] = {1, 10, 0, 10, LED_EFFECT_AGN, 2};
unsigned short Led_Blink4[] = {1, 50, 0, 50, LED_EFFECT_AGN, 2};
/* Led特效功能定义
 * 1. 灯状态保持的时间
 * 2. 灯状态
 * */
unsigned short LedTimer[LED_SUM];
unsigned short *pLed[LED_SUM];

void hal_LedConfig(void) {
  /* STM32固件库的有关于GPIO的配置文件 */
  /* 初始化 */
}

/* LED特效控制函数：
 * 1. 控制的LED
 * 2. 控制LED特效状态
 * 3. 加入到 10ms 轮询去刷新，类似RTOS中任务轮询
 * * */
void LedControl1(LED_TYPEDEF LedIdx, LED_EFFECT_TYPEDEF State) {
  switch (State) {
  case LED_DARK:
    pLed[LedIdx] = (unsigned short *)Led_Dark;
    LedTimer[LedIdx] = *(pLed[LedIdx] + 1);
    break;

  case LED_LIGHT:
    pLed[LedIdx] = (unsigned short *)Led_Light; /* 数组指针指向波形数组 */
    LedTimer[LedIdx] =
        *(pLed[LedIdx] + 1); /* 定时时间就是波形地址加1：取得是对应地址得值 */
    break;

  case LED_BLINK1:
    pLed[LedIdx] = (unsigned short *)Led_Blink1;
    LedTimer[LedIdx] = *(pLed[LedIdx] + 1);
    break;

  case LED_BLINK2:
    pLed[LedIdx] = (unsigned short *)Led_Blink2;
    LedTimer[LedIdx] = *(pLed[LedIdx] + 1);
    break;

  case LED_BLINK3:
    pLed[LedIdx] = (unsigned short *)Led_Blink3;
    LedTimer[LedIdx] = *(pLed[LedIdx] + 1);
    break;
  }
}

void LedInit(void) {
  hal_LedConfig();
  LedControl1(LED, Led_Dark);
  LedControl1(LED, LED_LIGHT);
  LedControl1(LED, LED_BLINK1);
  LedControl1(LED, LED_BLINK2);
  LedControl1(LED, LED_BLINK3);
}

/* 定时函数: 10ms轮询访问。也可以直接加到定时器中 */
void LedProc(void) {
  unsigned char i;
  for (i = 0; i < LED_SUM; i++) {
    if (LedTimer[i]) {
      LedTimer[i]--;
    } else {
      /* led 特效定时时间到 */
      if (*(pLed[i] + 2) == LED_EFFECT_END) {
        /* 判断当前得LED特效是否是需要循环模式
         * 1. 单次执行
         * 2. 循环执行
         * */
      } else {
        pLed[i] += 2;
        if (*pLed[i] == LED_EFFECT_AGN) {
          pLed[i] = pLed[i] - (*(pLed[i] + 1) * 2);
          // unsigned short Led_Blink3[] = {1, 10, 0, 10, LED_EFFECT_AGN, 2};
        }
        LedTimer[i] = *(pLed[i] + 1);
      }
    }
    hal_LedDrive[i](*pLed[i]); //实现LED的电平状态控制
  }
}

static void hal_Led1Drive(unsigned char sta) {
  if (sta) {
    /* 固件库函数，主要是控制GPIO的高电平状态的函数 */
  } else {
    /* 固件库函数，主要是控制GPIO的低电平状态的函数 */
  }
}

static void hal_Led2Drive(unsigned char sta) {
  if (sta) {
    /* 固件库函数，主要是控制GPIO的高电平状态的函数 */
  } else {
    /* 固件库函数，主要是控制GPIO的低电平状态的函数 */
  }
}

static void hal_Led3Drive(unsigned char sta) {
  if (sta) {
    /* 固件库函数，主要是控制GPIO的高电平状态的函数 */
  } else {
    /* 固件库函数，主要是控制GPIO的低电平状态的函数 */
  }
}

static void hal_Led4Drive(unsigned char sta) {
  if (sta) {
    /* 固件库函数，主要是控制GPIO的高电平状态的函数 */
  } else {
    /* 固件库函数，主要是控制GPIO的低电平状态的函数 */
  }
}

/* STM32引脚电平翻转的功能 */
void hal_Led1Turn(void) {
  /* 1. 首先读取当前GPIO引脚电平状态
   * 2.
   * 其次将读取到的电平状态通过强制转换：1-当前电平状态写入到当前的GPIO引脚上，实现翻转
   * */
}

void hal_Led2Turn(void) {
  /* 1. 首先读取当前GPIO引脚电平状态
   * 2.
   * 其次将读取到的电平状态通过强制转换：1-当前电平状态写入到当前的GPIO引脚上，实现翻转
   * */
}

void hal_Led3Turn(void) {
  /* 1. 首先读取当前GPIO引脚电平状态
   * 2.
   * 其次将读取到的电平状态通过强制转换：1-当前电平状态写入到当前的GPIO引脚上，实现翻转
   * */
}

void hal_Led4Turn(void) {
  /* 1. 首先读取当前GPIO引脚电平状态
   * 2.
   * 其次将读取到的电平状态通过强制转换：1-当前电平状态写入到当前的GPIO引脚上，实现翻转
   * */
}