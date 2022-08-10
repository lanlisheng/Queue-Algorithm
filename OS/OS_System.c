#include "OS_System.h"
#include <stdio.h>

CPUInterrupt_CallBack_t CPUInterruptCtrlCBS; //����һ������ָ�����

volatile OS_TaskTypeDef OS_Task[OS_TASK_SUM]; //�ṹ�е����ݲ������ж��б��ı�.

//��дϵͳ�ں˵ڰ˲�������ע��CUP�жϿ��ƺ���
/*
 * Function Name : void OS_CPUInterruptCBSRegister(CPUInterrupt_CallBack_t
 * pCPUInterrupCtrlCBS)
 * Descriptin    : ע��CPU�жϿ��ƺ���
 * Input         : - pCPUInterrupCtrlCBS:cpu�жϿ��ƻص�������ַ
 * Return        : None
 * Attention     : None
 */
void OS_CPUInterruptCBSRegister(CPUInterrupt_CallBack_t pCPUInterrupCtrlCBS) {
  if (CPUInterruptCtrlCBS == 0) {
    CPUInterruptCtrlCBS = pCPUInterrupCtrlCBS;
  }
}

/* ��дϵͳ�ں�֮�ڶ���:ϵͳ�����ʼ�� */
void OS_TaskInit(void) {
  unsigned char i;
  for (i = 0; i < OS_TASK_SUM; i++) {
    OS_Task[i].task = 0;
    OS_Task[i].RunFlag = OS_SLEEP;
    OS_Task[i].RunPeriod = 0;
    OS_Task[i].RunTimer = 0;
  }
}

/* ��дϵͳ�ں˵�����:����ϵͳ������ */
/* Function Name:void OS_CreatTask(unsigned char ID, void (*proc)(void),
unsigned short Period, OS_TaskStatusTypeDef flag)
* Descriptin    :��������
* Input         :-ID       :����ID
*               -(*proc)():�û�������ڵ�ַ
*               -Period   :����ִ��Ƶ��,��λ:ms
*               -flag     :�������״̬:OS_SLEEP-����
OS_RUN-����,��ʱ����,û������ *Output        :None *Return        :None
*Attention     :None
* */
void OS_CreatTask(unsigned char ID, void (*proc)(void), unsigned short Period,
                  OS_TaskStatusTypeDef flag) {
  if (!OS_Task[ID].task) { //�ж�������û�б�����,�����ظ�����
    OS_Task[ID].task = proc;
    OS_Task[ID].RunFlag = OS_SLEEP;
    OS_Task[ID].RunPeriod = Period;
    OS_Task[ID].RunTimer = 0;
  }
}

/* ��дϵͳ�ں˵��Ĳ�:��������ϵͳ��ʱ����(ϵͳ������Ⱥ���) */

/*
 * Function Name : OS_ClockInterruptHandle
 * Descriptin    : ϵͳ������Ⱥ���
 * Input         : None
 * Return        : None
 * Attention     : Ϊ��֤����ʵʱ��,����ŵ�10ms�Ķ�ʱ������ϵͳʱ���жϺ�����
 *
 */
void OS_ClockInterruptHandle(void) {
  unsigned char i;
  for (i = 0; i < OS_TASK_SUM; i++) {
    if (OS_Task[i].task) { //ͨ��task����ָ��ָ�򲻵���0�ж������Ƿ񱻴���
      OS_Task[i].RunTimer++;
      if (OS_Task[i].RunTimer >
          OS_Task[i].RunPeriod) { //�жϼ�ʱ��ֵ�Ƿ�ﵽ������Ҫִ�е�ʱ��
        OS_Task[i].RunTimer = 0;
        OS_Task[i].RunFlag =
            OS_RUN; //�������״̬����Ϊ����״̬,������Ȼ�һֱ�ж����������ֵ,�����OS_RUN�ͻ�ִ��task����ָ��ָ��ĺ���
      }
    }
  }
}

//��дϵͳ�ں˵��岽����������ʼ����
/*
 * Function Name : void OS_Start(void)
 * Descriptin    : ��ʼ������
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
        (*(OS_Task[i].task))(); //ͨ������ָ��ָ���ⲿ�ĺ������Ӷ�ʵ�ֹ���
      }
    }
  }
}

//��дϵͳ�ں˵����������������Ѻ���
/*
 * Function Name : void OS_TaskGetUp(OS_TaskID_TypeDef taskID)
 * Descriptin    : ����������
 * Input         : -taskID : ��Ҫ�����������ID
 * Output        : None
 * Return        : None
 * Attention     : None
 */
void OS_TaskGetUp(OS_TaskID_TypeDef taskID) {
  unsigned char IptStatus;
  if (CPUInterruptCtrlCBS !=
      0) { //�رյ�Ƭ�������жϣ���ֹ���ж��иı䵱ǰ����״̬
    CPUInterrupptCtrlCBS(CPU_ENTER_CRITICAL, &IptStatus);
  }
  OS_Task[taskID].RunFlag = OS_RUN;
  if (CPUInterruptCtrlCBS != 0) { //�򿪵�Ƭ�������ж�
    CPUInterrupptCtrlCBS(CPU_EXIT_CRITICAL, &IptStatus);
  }
}

//��дϵͳ�ں˵��߲��������������ߺ���
/*
 * Function Name : void OS_TaskSleep(OS_TaskID_TypeDef taskID)
 * Descriptin    : ����������
 * Input         : -taskID : ��Ҫ�����������ID
 * Output        : None
 * Return        : None
 * Attention     : None
 */
void OS_TaskSleep(OS_TaskID_TypeDef taskID) {
  unsigned char IptStatus;
  if (CPUInterruptCtrlCBS !=
      0) { //�رյ�Ƭ�������жϣ���ֹ���ж��иı䵱ǰ����״̬
    CPUInterrupptCtrlCBS(CPU_ENTER_CRITICAL, &IptStatus);
  }
  OS_Task[taskID].RunFlag = OS_SLEEP;
  if (CPUInterruptCtrlCBS != 0) { //�򿪵�Ƭ�������ж�
    CPUInterrupptCtrlCBS(CPU_EXIT_CRITICAL, &IptStatus);
  }
}