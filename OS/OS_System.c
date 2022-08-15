/* ��ֲ���̣����rtos��Ӳ�����(�ں���ֲ)
 * 1.��OS_ClockInterruptHandle()�ŵ���Ƭ����ʱ���жϴ��������ʱƵ��10ms��һ����õ�Ƭ��systick
 * 2.��д��Ƭ�����ж�
 * 3.ͨ��OS_CPUInterruptCBSRegister()�������ں��жϴ�����ָ��ָ��Ƭ�����жϿ��ش�����
 * * * */

#include "OS_System.h"
#include <stdio.h>

CPUInterrupt_CallBack_t CPUInterruptCtrlCBS; //����һ������ָ�����

volatile OS_TaskTypeDef OS_Task[OS_TASK_SUM]; //�ṹ�е����ݲ������ж��б��ı�.

//��дϵͳ�ں˵ڰ˲�������ע��CUP�жϿ��ƺ���
/*
 * Function Name : OS_CPUInterruptCBSRegister
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
* Descriptin    : ��������
* Input         : -    ID       : ����ID
*                 -   (*proc)(): �û�������ڵ�ַ
*                 -   Period   : ����ִ��Ƶ��,��λ:ms
*                 -   flag     : �������״̬:OS_SLEEP-����
OS_RUN-����,��ʱ����,û������
*Output        :  None
*Return        :  None
*Attention     :  None
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
      if (OS_Task[i].RunTimer >=
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
  if (CPUInterruptCtrlCBS != 0) {
    //�رյ�Ƭ�������жϣ���ֹ���ж��иı䵱ǰ����״̬
    CPUInterruptCtrlCBS(CPU_ENTER_CRITICAL, &IptStatus);
  }
  OS_Task[taskID].RunFlag = OS_RUN;
  if (CPUInterruptCtrlCBS != 0) {
    //�򿪵�Ƭ�������ж�
    CPUInterruptCtrlCBS(CPU_EXIT_CRITICAL, &IptStatus);
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
  if (CPUInterruptCtrlCBS != 0) {
    //�رյ�Ƭ�������жϣ���ֹ���ж��иı䵱ǰ����״̬
    CPUInterruptCtrlCBS(CPU_ENTER_CRITICAL, &IptStatus);
  }
  OS_Task[taskID].RunFlag = OS_SLEEP;
  if (CPUInterruptCtrlCBS != 0) {
    //�򿪵�Ƭ�������ж�
    CPUInterruptCtrlCBS(CPU_EXIT_CRITICAL, &IptStatus);
  }
}

/* ���г������˼·
1.������л��������С
2.���еĲ���:��ô���У�����˳��洢����������
3.���еĲ������Ƚ��ȳ�ԭ��
 */

/* ���в�����
1.���еĻ�����Դ洢������С��λ��
2.�����Ƿ����ˣ�����Ӧ����ô����
 */

/********************************************************************************************************
 *  @������   S_QueueEmpty
 *  @����     ���һ������
 *  @����     Head-����ͷ��ַ,  Tail-����β��ַ,   pBuff-���л���
 *  @����ֵ   ��
 *  @ע��    ��
 ********************************************************************************************************/
void S_QueueEmpty(unsigned char **Head, unsigned char **Tail,
                  unsigned char *pBuff) {
  //���еĳ�ʼ������
  *Head = pBuff;
  *Tail = pBuff;
}

/********************************************************************************************************
 *  @������   S_QueueDataIn
 *  @����     ����һ���ֽ����ݽ�����
 *  @����     Head-����ͷ��ַ,  Tail-����β��ַ,   pBuff-���л���
 *  @����ֵ   ��
 *  @ע��     ��
 ********************************************************************************************************/
/* �������ݵ����в��� */
void S_QueueDataIn(unsigned char **Head, unsigned char **Tail,
                   unsigned char *pBuff, unsigned char Len,
                   unsigned char *pData, unsigned char DataLen) {
  unsigned char num;
  unsigned char IptStatus = 0;
  if (CPUInterruptCtrlCBS != 0) {
    CPUInterruptCtrlCBS(CPU_ENTER_CRITICAL, &IptStatus);
  }
  for (num = 0; num < DataLen; num++, pData++) {
    //�����������еĲ���
    **Tail = *pData; //��������
    (*Tail)++;       //��βָ���1

    //�ж϶��������Ƿ�����
    if (*Tail == pBuff + Len) {
      //�����׵�ַ�����������ݳ���
      *Tail = pBuff;
    }
    //��βָ�����ͷָ�������ͻ��ֻ���У������е��������ֹΥ���Ƚ��ȳ�ԭ��
    if (*Tail == *Head) {
      if (++(*Head) == pBuff + Len) {
        *Head = pBuff;
      }
    }
  }
  if (CPUInterruptCtrlCBS != 0) {
    CPUInterruptCtrlCBS(CPU_EXIT_CRITICAL, &IptStatus);
  }
}

/********************************************************************************************************
 *  @������   S_QueueDataOut
 *  @����     �Ӷ�����ȡ��һ������
 *  @����     Head-����ͷ��ַ,  Tail-����β��ַ,   pBuff-���л���
 *  @����ֵ   ȡ��������
 *  @ע��     ��
 ********************************************************************************************************/
unsigned char S_QueueDataOut(unsigned char **Head, unsigned char **Tail,
                             unsigned char *pBuff, unsigned char Len,
                             unsigned char *pData) {
  unsigned char status = 0;
  unsigned char IptStatus = 0;
  if (CPUInterruptCtrlCBS != 0) {
    CPUInterruptCtrlCBS(CPU_ENTER_CRITICAL, &IptStatus);
  }

  *pData = 0;
  //������Ҫ���жϻ�������������
  if (*Head != *Tail) {
    //���л����д�������
    *pData = **Head;
    status = 1;
    if (++(*Head) == pBuff + Len) {
      *Head = pBuff;
    }
  }
  if (CPUInterruptCtrlCBS != 0) {
    CPUInterruptCtrlCBS(CPU_EXIT_CRITICAL, &IptStatus);
  }
  return status;
}

/********************************************************************************************************
 *  @������   S_QueueDataLen
 *  @����     �ж϶��������ݵĳ���
 *  @����     Head-����ͷ��ַ,  Tail-����β��ַ,   HBuff-���л���
 *  @����ֵ   �����������ݸ���
 *  @ע��     ��
 ********************************************************************************************************/
unsigned short S_QueueDataLen(unsigned char **Head, unsigned char **Tail,
                              unsigned char *pBuff, unsigned char Len) {
  //��ȡ�����еĻ��泤��
  if (*Tail > *Head) {
    return (*Tail - *Head);
  }

  //�����кܶ����ݣ����Ҷ�����û�н��г��в���������ڶ�ͷָ����ڶ�βָ��
  if (*Tail > *Head) {
    return (*Tail + Len - *Head);
  }
  return 0;
}