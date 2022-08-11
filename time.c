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


/* ��Ƭ���ϵĶ�ʱ�����ܳ�ʼ�� */
void hal_Timer4Config(void){
    /* �˴����붨ʱ����ʼ���������̼�����HAL����Щ��ͬ */
 }


/*
 * Function Name : hal_CreatTimer
 * Descriptin    : ������ʱ������
 * Input         : - id : ��ʱ��ID
 *                 - (*proc)() :����ָ��
 *                 - Period : ��ʱ���ڣ���λ50um
 *                 - state �� ��ʱ����ʼ״̬
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
 * Descriptin    : ��ʱ���жϼ�ʱ����
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