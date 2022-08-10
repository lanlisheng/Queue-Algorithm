#include "OS_System.h"
#include <stdio.h>

CPUInterrupt_CallBack_t CPUInterruptCtrlCBS; //定义一个函数指针变量

volatile OS_TaskTypeDef OS_Task[OS_TASK_SUM]; //结构中的数据不会在中断中被改变.

//编写系统内核第八步：创建注册CUP中断控制函数
/*
 * Function Name : void OS_CPUInterruptCBSRegister(CPUInterrupt_CallBack_t
 * pCPUInterrupCtrlCBS)
 * Descriptin    : 注册CPU中断控制函数
 * Input         : - pCPUInterrupCtrlCBS:cpu中断控制回调函数地址
 * Return        : None
 * Attention     : None
 */
void OS_CPUInterruptCBSRegister(CPUInterrupt_CallBack_t pCPUInterrupCtrlCBS) {
  if (CPUInterruptCtrlCBS == 0) {
    CPUInterruptCtrlCBS = pCPUInterrupCtrlCBS;
  }
}

/* 编写系统内核之第二步:系统任务初始化 */
void OS_TaskInit(void) {
  unsigned char i;
  for (i = 0; i < OS_TASK_SUM; i++) {
    OS_Task[i].task = 0;
    OS_Task[i].RunFlag = OS_SLEEP;
    OS_Task[i].RunPeriod = 0;
    OS_Task[i].RunTimer = 0;
  }
}

/* 编写系统内核第三步:创建系统任务函数 */
/* Function Name:void OS_CreatTask(unsigned char ID, void (*proc)(void),
unsigned short Period, OS_TaskStatusTypeDef flag)
* Descriptin    :创建任务
* Input         :-ID       :任务ID
*               -(*proc)():用户函数入口地址
*               -Period   :任务执行频率,单位:ms
*               -flag     :任务就绪状态:OS_SLEEP-休眠
OS_RUN-运行,定时唤醒,没有作用 *Output        :None *Return        :None
*Attention     :None
* */
void OS_CreatTask(unsigned char ID, void (*proc)(void), unsigned short Period,
                  OS_TaskStatusTypeDef flag) {
  if (!OS_Task[ID].task) { //判断任务有没有被创建,不能重复创建
    OS_Task[ID].task = proc;
    OS_Task[ID].RunFlag = OS_SLEEP;
    OS_Task[ID].RunPeriod = Period;
    OS_Task[ID].RunTimer = 0;
  }
}

/* 编写系统内核第四步:创建任务系统定时函数(系统任务调度函数) */

/*
 * Function Name : OS_ClockInterruptHandle
 * Descriptin    : 系统任务调度函数
 * Input         : None
 * Return        : None
 * Attention     : 为保证任务实时性,必须放到10ms的定时器或者系统时钟中断函数里
 *
 */
void OS_ClockInterruptHandle(void) {
  unsigned char i;
  for (i = 0; i < OS_TASK_SUM; i++) {
    if (OS_Task[i].task) { //通过task函数指针指向不等于0判断任务是否被创建
      OS_Task[i].RunTimer++;
      if (OS_Task[i].RunTimer >
          OS_Task[i].RunPeriod) { //判断计时器值是否达到任务需要执行的时间
        OS_Task[i].RunTimer = 0;
        OS_Task[i].RunFlag =
            OS_RUN; //把任务的状态设置为运行状态,任务调度会一直判断这个变量的值,如果是OS_RUN就混执行task函数指针指向的函数
      }
    }
  }
}

//编写系统内核第五步：创建任务开始函数
/*
 * Function Name : void OS_Start(void)
 * Descriptin    : 开始任务函数
 * Input         : None
 * Return        : None
 * Attention     : None
 */
void OS_Start(void) {
  unsigned char i;
  while (1) {
    for (i = 0; i < OS_TASK_SUM; i++) {
      if (OS_Task[i].RunFlag == OS_RUN) {
        OS_Task[i].RunFlag = OS_SLEEP;
        (*(OS_Task[i].task))(); //通过函数指针指向外部的函数。从而实现功能
      }
    }
  }
}

//编写系统内核第六步：创建任务唤醒函数
/*
 * Function Name : void OS_TaskGetUp(OS_TaskID_TypeDef taskID)
 * Descriptin    : 唤醒任务函数
 * Input         : -taskID : 需要被唤醒任务的ID
 * Output        : None
 * Return        : None
 * Attention     : None
 */
void OS_TaskGetUp(OS_TaskID_TypeDef taskID) {
  unsigned char IptStatus;
  if (CPUInterruptCtrlCBS !=
      0) { //关闭单片机的总中断：防止在中断中改变当前任务状态
    CPUInterrupptCtrlCBS(CPU_ENTER_CRITICAL, &IptStatus);
  }
  OS_Task[taskID].RunFlag = OS_RUN;
  if (CPUInterruptCtrlCBS != 0) { //打开单片机的总中断
    CPUInterrupptCtrlCBS(CPU_EXIT_CRITICAL, &IptStatus);
  }
}

//编写系统内核第七步：创建任务休眠函数
/*
 * Function Name : void OS_TaskSleep(OS_TaskID_TypeDef taskID)
 * Descriptin    : 唤醒任务函数
 * Input         : -taskID : 需要被休眠任务的ID
 * Output        : None
 * Return        : None
 * Attention     : None
 */
void OS_TaskSleep(OS_TaskID_TypeDef taskID) {
  unsigned char IptStatus;
  if (CPUInterruptCtrlCBS !=
      0) { //关闭单片机的总中断：防止在中断中改变当前任务状态
    CPUInterrupptCtrlCBS(CPU_ENTER_CRITICAL, &IptStatus);
  }
  OS_Task[taskID].RunFlag = OS_SLEEP;
  if (CPUInterruptCtrlCBS != 0) { //打开单片机的总中断
    CPUInterrupptCtrlCBS(CPU_EXIT_CRITICAL, &IptStatus);
  }
}