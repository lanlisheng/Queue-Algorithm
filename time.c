#include "time.h"

volatile Stu_TimerTypeDef Stu_Timer[T_SUM];

void hal_TimeInit(void) {
  unsigned char i;
  hal_Timer4Config();
  for (i = 0; i < T_SUM;i++){
    Stu_Timer[i].state = T_STA_STOP;
    Stu_Timer[i].CurrentCount = 0;
    Stu_Timer[i].Period = 0;
    Stu_Timer[i].func = 0;
  }
}


/* 单片机上的定时器功能初始化 */
void hal_Timer4Config(void){
    /* 此处加入定时器初始化函数：固件库与HAL库有些许不同 */
 }


/*
 * Function Name : hal_CreatTimer
 * Descriptin    : 创建定时器函数
 * Input         : - id : 定时器ID
 *                 - (*proc)() :函数指针
 *                 - Period : 定时周期，单位50um
 *                 - state ： 定时器初始状态
 * Return        : None
 * Attention     : None
 */
void hal_CreatTimer(TIMER_ID_TYPEDEF id,void (*proc)(void),unsigned short Period,TIMER_STATE_TYPEDEF state){
  Stu_Timer[id].state = state;
  Stu_Timer[id].CurrentCount = 0;
  Stu_Timer[id].Period = Period;
  Stu_Timer[id].func = proc;
}

/*
 * Function Name : hal_TimerHandle
 * Descriptin    : 定时器中断计时函数
 * Input         : None
 * Return        : None
 * Attention     : None
 */
void hal_TimerHandle(void) { unsigned char i;
  for (i = 0; i < T_SUM;i++){
    if ((Stu_Timer[i].func)&&(Stu_Timer[i].state == T_STA_START))
    {
      Stu_Timer[i].CurrentCount++;
      if(Stu_Timer[i].CurrentCount>=Stu_Timer[i].Period){
          Stu_Timer[i].state = T_STA_STOP;
          Stu_Timer[i].CurrentCount = Stu_Timer[i].CurrentCount;
          Stu_Timer[i].func ();
      }
    }
  }
}