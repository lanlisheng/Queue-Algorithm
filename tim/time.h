#ifndef _TIME_H_
#define _TIME_H_

typedef enum { T_LED, T_KEY, T_RFD, T_SUM } TIMER_ID_TYPEDEF;

typedef enum { T_SUCCESS, T_FAIL } TIMER_RESULT_TYPEDEF;

typedef enum {
  T_STA_INVAILD,
  T_STA_STOP,  //定时器停止
  T_STA_START, //定时器启动
} TIMER_STATE_TYPEDEF;

typedef struct {
  TIMER_STATE_TYPEDEF state;   // 0-定时器未启动  1-定时器启动
  unsigned short CurrentCount; //当前计时值
  unsigned short Period;       //定时周期
  void (*func)(void);          //函数指针:指向外部函数，用户处理
} Stu_TimerTypeDef;

void hal_TimeInit(void);
void hal_CreatTimer(TIMER_ID_TYPEDEF id, void (*proc)(void),
                    unsigned short Period, TIMER_STATE_TYPEDEF state);
TIMER_RESULT_TYPEDEF hal_ResetTimer(TIMER_ID_TYPEDEF id,
                                    TIMER_STATE_TYPEDEF sta);
TIMER_RESULT_TYPEDEF hal_DeleteTimer(TIMER_ID_TYPEDEF id);
TIMER_RESULT_TYPEDEF hal_CtrlTimerAction(TIMER_ID_TYPEDEF id,
                                         TIMER_STATE_TYPEDEF sta);
#endif
