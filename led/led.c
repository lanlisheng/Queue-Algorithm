#include "led.h"
#include "OS_System.h"
#include "hal_time.h"

Queue4 LedCmdBuff[LED_SUM]; // LED����

static void hal_Led1Drive(unsigned char sta);
static void hal_BuzDrive(unsigned char sta);

/* Ledִ�к������� */
void (*hal_LedDrive[LED_SUM])(unsigned char) = {
    hal_Led1Drive,
    hal_BuzDrive,
};

/* Led��Ч�洢���� */
unsigned short Led_Dark[] = {0, 10, LED_EFFECT_END};
unsigned short Led_Light[] = {1, 10, LED_EFFECT_END};
unsigned short Led_Light100ms[] = {1, 10, 0, 10, LED_EFFECT_END};
unsigned short Led_Blink1[] = {1, 50, 0, 50, 1, 50, 0, 50, LED_EFFECT_END};
unsigned short Led_Blink2[] = {
    1, 10, 0, 10, 1, 10, 0, 10, 1, 10, 0, 210, LED_EFFECT_AGN, 6};
unsigned short Led_Blink3[] = {1, 10, 0, 10, LED_EFFECT_AGN, 2};
unsigned short Led_Blink4[] = {1, 50, 0, 50, LED_EFFECT_AGN, 2};

/* Led��Ч���ܶ���
 * 1. ��״̬���ֵ�ʱ��
 * 2. ��״̬
 * */
unsigned short LedTimer[LED_SUM];
unsigned short *pLed[LED_SUM];

/* LED Load Flag */
unsigned char LedLoadFlag[LED_SUM];

static void hal_LedConfig(void);
static void hal_LedHandle(void);

/* LED��ʼ��״̬���� */
void LedInit(void) {
  unsigned char i = 0;
  hal_LedConfig();
  hal_CreatTimer(T_LED, hal_LedHandle, 200, T_STA_START); //��ʱ����50us*200

  for (i = 0; i < LED_SUM; i++) {
    LedLoadFlag[i] = 0;
    pLed[i] = (unsigned short *)Led_Dark;
    LedTimer[i] = *(pLed[i] + 1);
    QueueEmpty(LedCmdBuff[i]);
  }
}

/* LED��Ч���ƺ�����
 * 1. ���Ƶ�LED
 * 2. ����LED��Ч״̬
 * 3. ���뵽 10ms ��ѯȥˢ�£�����RTOS��������ѯ
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
        pLed[i] = (unsigned short *)Led_Light; /* ����ָ��ָ�������� */
        LedTimer[i] =
            *(pLed[i] + 1); /* ��ʱʱ����ǲ��ε�ַ��1��ȡ���Ƕ�Ӧ��ַ��ֵ */
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
  /* STM32�̼�����й���GPIO�������ļ� */
  /* ��ʼ�� */
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

/* ��ʱ����: 10ms��ѯ���ʡ�Ҳ����ֱ�Ӽӵ���ʱ���� */
static void hal_LedHandle(void) {
  unsigned char i;
  for (i = 0; i < LED_SUM; i++) {
    if (LedTimer[i]) {
      LedTimer[i]--;
    }

    if (!LedTimer[i]) {
      /* led ��Ч��ʱʱ�䵽 */
      if (*(pLed[i] + 2) == LED_EFFECT_END) {
        /* �жϵ�ǰ��LED��Ч�Ƿ�����Ҫѭ��ģʽ
         * 1. ����ִ��
         * 2. ѭ��ִ��
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
    hal_LedDrive[i](*pLed[i]); //ʵ��LED�ĵ�ƽ״̬����
  }
  hal_ResetTimer(T_LED, T_STA_START);
}

static void hal_Led1Drive(unsigned char sta) {
  if (sta) {
    /* �̼��⺯������Ҫ�ǿ���GPIO�ĸߵ�ƽ״̬�ĺ��� */
  } else {
    /* �̼��⺯������Ҫ�ǿ���GPIO�ĵ͵�ƽ״̬�ĺ��� */
  }
}

static void hal_Led2Drive(unsigned char sta) {
  if (sta) {
    /* �̼��⺯������Ҫ�ǿ���GPIO�ĸߵ�ƽ״̬�ĺ��� */
  } else {
    /* �̼��⺯������Ҫ�ǿ���GPIO�ĵ͵�ƽ״̬�ĺ��� */
  }
}

static void hal_Led3Drive(unsigned char sta) {
  if (sta) {
    /* �̼��⺯������Ҫ�ǿ���GPIO�ĸߵ�ƽ״̬�ĺ��� */
  } else {
    /* �̼��⺯������Ҫ�ǿ���GPIO�ĵ͵�ƽ״̬�ĺ��� */
  }
}

static void hal_Led4Drive(unsigned char sta) {
  if (sta) {
    /* �̼��⺯������Ҫ�ǿ���GPIO�ĸߵ�ƽ״̬�ĺ��� */
  } else {
    /* �̼��⺯������Ҫ�ǿ���GPIO�ĵ͵�ƽ״̬�ĺ��� */
  }
}

static void hal_BuzDrive(unsigned char sta) {
  if (sta) {
    /* �̼��⺯������Ҫ�ǿ���GPIO�ĸߵ�ƽ״̬�ĺ��� */
  } else {
    /* �̼��⺯������Ҫ�ǿ���GPIO�ĵ͵�ƽ״̬�ĺ��� */
  }
}

/* STM32���ŵ�ƽ��ת�Ĺ��� */
void hal_Led1Turn(void) {
  /* 1. ���ȶ�ȡ��ǰGPIO���ŵ�ƽ״̬
   * 2.
   * ��ν���ȡ���ĵ�ƽ״̬ͨ��ǿ��ת����1-��ǰ��ƽ״̬д�뵽��ǰ��GPIO�����ϣ�ʵ�ַ�ת
   * */
}

void hal_Led2Turn(void) {
  /* 1. ���ȶ�ȡ��ǰGPIO���ŵ�ƽ״̬
   * 2.
   * ��ν���ȡ���ĵ�ƽ״̬ͨ��ǿ��ת����1-��ǰ��ƽ״̬д�뵽��ǰ��GPIO�����ϣ�ʵ�ַ�ת
   * */
}

void hal_Led3Turn(void) {
  /* 1. ���ȶ�ȡ��ǰGPIO���ŵ�ƽ״̬
   * 2.
   * ��ν���ȡ���ĵ�ƽ״̬ͨ��ǿ��ת����1-��ǰ��ƽ״̬д�뵽��ǰ��GPIO�����ϣ�ʵ�ַ�ת
   * */
}

void hal_Led4Turn(void) {
  /* 1. ���ȶ�ȡ��ǰGPIO���ŵ�ƽ״̬
   * 2.
   * ��ν���ȡ���ĵ�ƽ״̬ͨ��ǿ��ת����1-��ǰ��ƽ״̬д�뵽��ǰ��GPIO�����ϣ�ʵ�ַ�ת
   * */
}