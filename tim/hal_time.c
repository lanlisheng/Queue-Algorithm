#include "hal_time.h"
#include "led.h"

static void hal_TimerHandle(void);
static void hal_Timer4Config(void);

volatile Stu_TimerTypeDef Stu_Timer[T_SUM];

void hal_TimeInit(void) {
  unsigned char i;
  hal_Timer4Config();
  for (i = 0; i < T_SUM; i++) {
    Stu_Timer[i].state = T_STA_STOP;
    Stu_Timer[i].CurrentCount = 0;
    Stu_Timer[i].Period = 0;
    Stu_Timer[i].func = 0;
  }
}

/* ��Ƭ���ϵĶ�ʱ�����ܳ�ʼ�� */
/*
 * Function Name : hal_Timer4Config
 * Descriptin    : ��ʱ��Ӳ�����ú���
 * Input         : None
 * Return        : None
 * Attention     : None
 */
static void hal_Timer4Config(void) {
  /* �˴����붨ʱ����ʼ���������̼�����HAL����Щ����ͬ
   * �������ö�ʱ����ʱ���׼
   *
   * * */
  // TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
  // NVIC_InitTypeDef NVIC_InitStructure;
  // RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);

  // TIM_DeInit(TIM4);
  // // TIM_TimeBaseStructure.TIM_Period = 10000; 			//10ms
  // //	TIM_TimeBaseStructure.TIM_Period = 1000; 			//1ms
  // TIM_TimeBaseStructure.TIM_Period = 50; // 50us
  // TIM_TimeBaseStructure.TIM_Prescaler = SystemCoreClock / 1000000 - 1;
  // TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
  // TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
  // TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;
  // TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);

  // TIM_ClearFlag(TIM4, TIM_FLAG_Update);
  // TIM_ITConfig(TIM4, TIM_IT_Update, ENABLE);

  // TIM_Cmd(TIM4, ENABLE);

  // NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);
  // NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQn;
  // NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
  // NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  // NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  // NVIC_Init(&NVIC_InitStructure);
}

/*
 * Function Name : hal_CreatTimer
 * Descriptin    : ������ʱ������
 * Input         : - id        :  ��ʱ��ID
 *                 - (*proc)() :  ����ָ��
 *                 - Period    :  ��ʱ���ڣ���λ50um
 *                 - state     �� ��ʱ����ʼ״̬
 * Return        : None
 * Attention     : None
 */
void hal_CreatTimer(TIMER_ID_TYPEDEF id, void (*proc)(void),
                    unsigned short Period, TIMER_STATE_TYPEDEF state) {
  Stu_Timer[id].state = state;
  Stu_Timer[id].CurrentCount = 0;
  Stu_Timer[id].Period = Period;
  Stu_Timer[id].func = proc;
}

/*
 * Function Name : hal_CtrlTimerAction
 * Descriptin    : ���ƶ�ʱ������
 * Input         : - id  : ��ʱ��ID
 *                 - sta : ��ʱ��״̬
 * Return        : None
 * Attention     : None
 */
TIMER_RESULT_TYPEDEF hal_CtrlTimerAction(TIMER_ID_TYPEDEF id,
                                         TIMER_STATE_TYPEDEF sta) {
  if (Stu_Timer[id].func) { /* �ж϶�ʱ���Ƿ���� */
    Stu_Timer[id].state = sta;
    return T_SUCCESS;
  } else {
    return T_FAIL;
  }
}

/*
 * Function Name : hal_GetTimerState
 * Descriptin    : ��ȡ��ʱ��״̬
 * Input         : - id  : ��ʱ��ID
 *                 - sta : ��ʱ��״̬
 * Return        : None
 * Attention     : None
 */
TIMER_STATE_TYPEDEF hal_GetTimerState(TIMER_ID_TYPEDEF id) {
  if (Stu_Timer[id].func) //�ж϶�ʱ���Ƿ����
  {
    return Stu_Timer[id].state;

  } else {
    return T_STA_INVAILD;
  }
}

/*
 * Function Name : hal_DeleteTimer
 * Descriptin    : ɾ����ʱ��
 * Input         : - id  : ��ʱ��ID
 * Return        : None
 * Attention     : None
 */
TIMER_RESULT_TYPEDEF hal_DeleteTimer(TIMER_ID_TYPEDEF id) {
  if (Stu_Timer[id].func) {
    Stu_Timer[id].state = T_STA_STOP;
    Stu_Timer[id].CurrentCount = 0;
    Stu_Timer[id].func = 0;
    return T_SUCCESS;
  } else {
    return T_FAIL;
  }
}

/*
 * Function Name : hal_ResetTimer
 * Descriptin    : ��λ��ʱ��״̬�ͼ�ʱʱ��
 * Input         : - id  : ��ʱ��ID
 * Return        : None
 * Attention     : None
 */
TIMER_RESULT_TYPEDEF hal_ResetTimer(TIMER_ID_TYPEDEF id,
                                    TIMER_STATE_TYPEDEF sta) {
  if (Stu_Timer[id].func) {
    Stu_Timer[id].state = sta;
    Stu_Timer[id].CurrentCount = 0;
    return T_SUCCESS;
  } else {
    return T_FAIL;
  }
}

/*
 * Function Name : hal_TimerHandle
 * Descriptin    : ��ʱ���жϼ�ʱ����
 * Input         : None
 * Return        : None
 * Attention     : None
 */
static void hal_TimerHandle(void) {
  unsigned char i;
  for (i = 0; i < T_SUM; i++) {
    if ((Stu_Timer[i].func) && (Stu_Timer[i].state == T_STA_START)) {
      Stu_Timer[i].CurrentCount++;
      if (Stu_Timer[i].CurrentCount >= Stu_Timer[i].Period) {
        Stu_Timer[i].state = T_STA_STOP;
        Stu_Timer[i].CurrentCount = Stu_Timer[i].CurrentCount;
        //һֱ���ֵ�ǰ��ʱֵ����ʱ��ʱ��ʱ������ʱ��ѭ���Ļ���Ҫ��λ
        Stu_Timer[i].func();
      }
    }
  }
}

/*
 * Function Name : TIMx_IRQHandle()
 * Descriptin    : ��ʱ���жϻص�����
 * Input         : None
 * Return        : None
 * Attention     : x - ����Ӳ�����Ǹ���ʱ������ʱ��1-8
 */
void TIMx_IRQHandle(void) {
  // TIM_ClearFlag(TIMx, TIM_FLAG_Update); //�����ʱ����־λ����ʱ��x��
  hal_TimerHandle();
}