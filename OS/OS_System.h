#ifndef _OS_SYSTEM_H_
#define _OS_SYSTEM_H_

typedef enum {
  CPU_ENTER_CRITICAL, // CPU�����ٽ�״̬
  CPU_EXIT_CRITICAL   // CPU�˳��ٽ�״̬
} CPU_EA_TYPEDEF;

/* ����һ��CPU�жϿ��ƻص�����ָ�룬������CPUInterrupt_CallBack_t
 * �βΣ�- cmd    ������CPU�жϴ򿪻��ǹر��ж��ٽ硣
 *      - *pSta  : ͨ��ָ�봫���ַ
 * */
typedef void (*CPUInterrupt_CallBack_t)(CPU_EA_TYPEDEF cmd,
                                        unsigned char *pSta);

//ϵͳ����ID.����:��ö�������������С
typedef enum { OS_TASK1, OS_TASK_SUM } OS_TaskID_TypeDef;

//ϵͳ��������״̬
typedef enum {
  OS_SLEEP,          //��������
  OS_RUN = !OS_SLEEP //��������
} OS_TaskStatusTypeDef;

 // ��дϵͳ�ں�֮��һ��:����ϵͳ����ṹ��
typedef struct {
  void (*task)(void); //������ָ��:����ָ��ָ������,һ����while(1)�еĺ���
  OS_TaskStatusTypeDef RunFlag; //��������״̬:���߻�������
  unsigned short RunPeriod; //�������Ƶ��:����ָ��Ĵ�����ִ�е�Ƶ��
  unsigned short RunTimer; //������ȼ�ʱ��:ʱ��ﵽ�������Ƶ��ʱ,����ᱻִ��
} OS_TaskTypeDef;

void OS_CPUInterruptCBSRegister(CPUInterrupt_CallBack_t pCPUInterrupCtrlCBS);
void OS_TaskInit(void);
void OS_CreatTask(unsigned char ID, void (*proc)(void), unsigned short Period,
                  OS_TaskStatusTypeDef flag);
void OS_ClockInterruptHandle(void);
void OS_Start(void);
void OS_TaskGetUp(OS_TaskID_TypeDef taskID);
void OS_TaskSleep(OS_TaskID_TypeDef taskID);

#endif