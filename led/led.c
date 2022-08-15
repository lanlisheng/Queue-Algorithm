#include "led.h"
#include "time.h"

static void hal_Led1Drive(unsigned char sta);
static void hal_Led2Drive(unsigned char sta);
static void hal_Led3Drive(unsigned char sta);
static void hal_Led4Drive(unsigned char sta);

/* Ledִ�к������� */
void (*hal_LedDrive[])(unsigned char) = {hal_Led1Drive, hal_Led2Drive,
                                         hal_Led3Drive, hal_Led4Drive};

/* Led��Ч�洢���� */
unsigned short Led_Dark[] = {0, 10, LED_EFFECT_END};
unsigned short Led_Light[] = {1, 10, LED_EFFECT_END};
unsigned short Led_Blink1[] = {1, 50, 0, 50, 1, 50, 0, 50, LED_EFFECT_END};
unsigned short Led_Blink2[] = {1, 10, 0, 10, 1, 10, 0, 210, LED_EFFECT_AGN, 4};
unsigned short Led_Blink3[] = {1, 10, 0, 10, LED_EFFECT_AGN, 2};
unsigned short Led_Blink4[] = {1, 50, 0, 50, LED_EFFECT_AGN, 2};
/* Led��Ч���ܶ���
 * 1. ��״̬���ֵ�ʱ��
 * 2. ��״̬
 * */
unsigned short LedTimer[LED_SUM];
unsigned short *pLed[LED_SUM];

void hal_LedConfig(void) {
  /* STM32�̼�����й���GPIO�������ļ� */
  /* ��ʼ�� */
}

/* LED��Ч���ƺ�����
 * 1. ���Ƶ�LED
 * 2. ����LED��Ч״̬
 * 3. ���뵽 10ms ��ѯȥˢ�£�����RTOS��������ѯ
 * * */
void LedControl1(LED_TYPEDEF LedIdx, LED_EFFECT_TYPEDEF State) {
  switch (State) {
  case LED_DARK:
    pLed[LedIdx] = (unsigned short *)Led_Dark;
    LedTimer[LedIdx] = *(pLed[LedIdx] + 1);
    break;

  case LED_LIGHT:
    pLed[LedIdx] = (unsigned short *)Led_Light; /* ����ָ��ָ�������� */
    LedTimer[LedIdx] =
        *(pLed[LedIdx] + 1); /* ��ʱʱ����ǲ��ε�ַ��1��ȡ���Ƕ�Ӧ��ַ��ֵ */
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

/* ��ʱ����: 10ms��ѯ���ʡ�Ҳ����ֱ�Ӽӵ���ʱ���� */
void LedProc(void) {
  unsigned char i;
  for (i = 0; i < LED_SUM; i++) {
    if (LedTimer[i]) {
      LedTimer[i]--;
    } else {
      /* led ��Ч��ʱʱ�䵽 */
      if (*(pLed[i] + 2) == LED_EFFECT_END) {
        /* �жϵ�ǰ��LED��Ч�Ƿ�����Ҫѭ��ģʽ
         * 1. ����ִ��
         * 2. ѭ��ִ��
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
    hal_LedDrive[i](*pLed[i]); //ʵ��LED�ĵ�ƽ״̬����
  }
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