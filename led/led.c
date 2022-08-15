#include "led.h"
#include "OS_System.h"
#include "hal_time.h"

Queue4 LedCmdBuff[LED_SUM]; // LED信箱

static void hal_Led1Drive(unsigned char sta);
static void hal_BuzDrive(unsigned char sta);

/* Led执行函数数组 */
void (*hal_LedDrive[LED_SUM])(unsigned char) = {
    hal_Led1Drive,
    hal_BuzDrive,
};

/* Led特效存储数组 */
unsigned short Led_Dark[] = {0, 10, LED_EFFECT_END};
unsigned short Led_Light[] = {1, 10, LED_EFFECT_END};
unsigned short Led_Light100ms[] = {1, 10, 0, 10, LED_EFFECT_END};
unsigned short Led_Blink1[] = {1, 50, 0, 50, 1, 50, 0, 50, LED_EFFECT_END};
unsigned short Led_Blink2[] = {
    1, 10, 0, 10, 1, 10, 0, 10, 1, 10, 0, 210, LED_EFFECT_AGN, 6};
unsigned short Led_Blink3[] = {1, 10, 0, 10, LED_EFFECT_AGN, 2};
unsigned short Led_Blink4[] = {1, 50, 0, 50, LED_EFFECT_AGN, 2};

/* Led特效功能定义
 * 1. 灯状态保持的时间
 * 2. 灯状态
 * */
unsigned short LedTimer[LED_SUM];
unsigned short *pLed[LED_SUM];

/* LED Load Flag */
unsigned char LedLoadFlag[LED_SUM];

static void hal_LedConfig(void);
static void hal_LedHandle(void);

/* LED初始化状态函数 */
void LedInit(void) {
  unsigned char i = 0;
  hal_LedConfig();
  hal_CreatTimer(T_LED, hal_LedHandle, 200, T_STA_START); //定时周期50us*200

  for (i = 0; i < LED_SUM; i++) {
    LedLoadFlag[i] = 0;
    pLed[i] = (unsigned short *)Led_Dark;
    LedTimer[i] = *(pLed[i] + 1);
    QueueEmpty(LedCmdBuff[i]);
  }
}

/* LED特效控制函数：
 * 1. 控制的LED
 * 2. 控制LED特效状态
 * 3. 加入到 10ms 轮询去刷新，类似RTOS中任务轮询
 * * */
void hal_LedProc(void) {
  unsigned char i;
  unsigned char cmd;
  for (i = 0; i < LED_SUM; i++) {
    if ((QueueDataLen(LedCmdBuff[i]) > 0) && (LedLoadFlag[i] == 0)) {
      QueueDataOut(LedCmdBuff[i], &cmd);
      LedLoadFlag[i] = 1;
      switch (cmd) {
      case LED_DARK:
        pLed[i] = (unsigned short *)Led_Dark;
        LedTimer[i] = *(pLed[i] + 1);
        break;

      case LED_LIGHT:
        pLed[i] = (unsigned short *)Led_Light; /* 数组指针指向波形数组 */
        LedTimer[i] =
            *(pLed[i] + 1); /* 定时时间就是波形地址加1：取得是对应地址得值 */
        break;

      case LED_BLINK1:
        pLed[i] = (unsigned short *)Led_Blink1;
        LedTimer[i] = *(pLed[i] + 1);
        break;

      case LED_BLINK2:
        pLed[i] = (unsigned short *)Led_Blink2;
        LedTimer[i] = *(pLed[i] + 1);
        break;

      case LED_BLINK3:
        pLed[i] = (unsigned short *)Led_Blink3;
        LedTimer[i] = *(pLed[i] + 1);
        break;

      case LED_BLINK4:
        pLed[i] = (unsigned short *)Led_Blink4;
        LedTimer[i] = *(pLed[i] + 1);
        break;
      }
    }
  }
}

void LedMsgInput(unsigned char type, LED_EFFECT_TYPEDEF cmd,
                 unsigned char clr) {
  unsigned char bLedCMD;
  if (type >= LED_SUM) {
    return;
  }
  bLedCMD = cmd;
  if (clr) {
    QueueEmpty(LedCmdBuff[type]);
    LedLoadFlag[type] = 0;
  }
  QueueDataIn(LedCmdBuff[type], &bLedCMD, 1);
}

static void hal_LedConfig(void) {
  /* STM32固件库的有关于GPIO的配置文件 */
  /* 初始化 */
  // GPIO_InitTypeDef GPIO_InitStructure;

  // RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
  // RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);

  // GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
  // GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  // GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  // ;
  // GPIO_Init(GPIOA, &GPIO_InitStructure);
  // GPIO_ResetBits(GPIOA, GPIO_Pin_1);

  // GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
  // GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  // GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  // ;
  // GPIO_Init(GPIOB, &GPIO_InitStructure);
  // GPIO_ResetBits(GPIOB, GPIO_Pin_0);
}

/* 定时函数: 10ms轮询访问。也可以直接加到定时器中 */
static void hal_LedHandle(void) {
  unsigned char i;
  for (i = 0; i < LED_SUM; i++) {
    if (LedTimer[i]) {
      LedTimer[i]--;
    }

    if (!LedTimer[i]) {
      /* led 特效定时时间到 */
      if (*(pLed[i] + 2) == LED_EFFECT_END) {
        /* 判断当前得LED特效是否是需要循环模式
         * 1. 单次执行
         * 2. 循环执行
         * */
        LedLoadFlag[i] = 0;
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
  hal_ResetTimer(T_LED, T_STA_START);
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

static void hal_BuzDrive(unsigned char sta) {
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