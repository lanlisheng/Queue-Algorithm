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

/* 单片机上的定时器功能初始化 */
/*
 * Function Name : hal_Timer4Config
 * Descriptin    : 定时器硬件配置函数
 * Input         : None
 * Return        : None
 * Attention     : None
 */
static void hal_Timer4Config(void) {
  /* 此处加入定时器初始化函数：固件库与HAL库有些许不同
   * 此中配置定时器的时间基准
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
 * Descriptin    : 创建定时器函数
 * Input         : - id        :  定时器ID
 *                 - (*proc)() :  函数指针
 *                 - Period    :  定时周期，单位50um
 *                 - state     ： 定时器初始状态
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
 * Descriptin    : 控制定时器动作
 * Input         : - id  : 定时器ID
 *                 - sta : 定时器状态
 * Return        : None
 * Attention     : None
 */
TIMER_RESULT_TYPEDEF hal_CtrlTimerAction(TIMER_ID_TYPEDEF id,
                                         TIMER_STATE_TYPEDEF sta) {
  if (Stu_Timer[id].func) { /* 判断定时器是否存在 */
    Stu_Timer[id].state = sta;
    return T_SUCCESS;
  } else {
    return T_FAIL;
  }
}

/*
 * Function Name : hal_GetTimerState
 * Descriptin    : 获取定时器状态
 * Input         : - id  : 定时器ID
 *                 - sta : 定时器状态
 * Return        : None
 * Attention     : None
 */
TIMER_STATE_TYPEDEF hal_GetTimerState(TIMER_ID_TYPEDEF id) {
  if (Stu_Timer[id].func) //判断定时器是否存在
  {
    return Stu_Timer[id].state;

  } else {
    return T_STA_INVAILD;
  }
}

/*
 * Function Name : hal_DeleteTimer
 * Descriptin    : 删除定时器
 * Input         : - id  : 定时器ID
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
 * Descriptin    : 复位定时器状态和计时时间
 * Input         : - id  : 定时器ID
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
 * Descriptin    : 定时器中断计时函数
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
        //一直保持当前计时值：此时定时器时单个定时，循环的话需要复位
        Stu_Timer[i].func();
      }
    }
  }
}

/*
 * Function Name : TIMx_IRQHandle()
 * Descriptin    : 定时器中断回调函数
 * Input         : None
 * Return        : None
 * Attention     : x - 属于硬件的那个定时器：定时器1-8
 */
void TIMx_IRQHandle(void) {
  // TIM_ClearFlag(TIMx, TIM_FLAG_Update); //清除定时器标志位：定时器x，
  hal_TimerHandle();
}