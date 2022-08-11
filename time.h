#ifndef _TIME_H_
#define _TIME_H_

typedef enum { T_LED, T_KEY, T_RFD, T_SUM } TIMER_ID_TYPEDEF;

typedef enum {
  T_STA_INVAILD,
  T_STA_STOP,  //定时器停止
  T_STA_START, //定时器启动
} TIMER_STATE_TYPEDEF;

typedef struct {
  TIMER_STATE_TYPEDEF state;   // 0-定时器未启动  1-定时器启动
  unsigned short CurrentCount; //当前计时值
  unsigned short Period;       //定时周期
  void (*func)(void);          //函数指针
} Stu_TimerTypeDef;

#endif
