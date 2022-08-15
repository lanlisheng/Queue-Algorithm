#ifndef _OS_SYSTEM_H_
#define _OS_SYSTEM_H_

extern void S_QueueEmpty(unsigned char **Head, unsigned char **Tail,
                         unsigned char *pBuff);
extern void S_QueueDataIn(unsigned char **Head, unsigned char **Tail,
                          unsigned char *pBuff, unsigned char Len,
                          unsigned char *pData, unsigned char DataLen);
extern unsigned char S_QueueDataOut(unsigned char **Head, unsigned char **Tail,
                                    unsigned char *pBuff, unsigned char Len,
                                    unsigned char *pData);
extern unsigned short S_QueueDataLen(unsigned char **Head, unsigned char **Tail,
                                     unsigned char *pBuff, unsigned char Len);

#define QueueEmpty(x)                                                          \
  S_QueueEmpty((unsigned char **)&(x).Head, (unsigned char **)&(x).Tail,       \
               (unsigned char *)(x).Buff)

#define QueueDataIn(x, y, z)                                                   \
  S_QueueDataIn((unsigned char **)&(x).Head, (unsigned char **)&(x).Tail,      \
                (unsigned char *)(x).Buff, sizeof((x).Buff), y, z)

#define QueueDataOut(x, y)                                                     \
  ((unsigned char **)&(x).Head, (unsigned char **)&(x).Tail,                   \
   (unsigned char *)(x).Buff, sizeof((x).Buff), y)
#define QueueDataLen(x)                                                        \
  ((unsigned char **)&(x).Head, (unsigned char **)&(x).Tail,                   \
   (unsigned char *)(x).Buff, sizeof((x).Buff))

/* 1.定义好一个队列的数据结构 */
typedef struct {
  unsigned char *Head;
  unsigned char *Tail;
  unsigned char Buff[4 + 1];
} Queue4;

typedef struct {
  unsigned char *Head;
  unsigned char *Tail;
  unsigned char Buff[8 + 1];
} Queue8;
typedef struct {
  unsigned char *Head;
  unsigned char *Tail;
  unsigned char Buff[16 + 1];
} Queue16;
typedef struct {
  unsigned char *Head;
  unsigned char *Tail;
  unsigned char Buff[32 + 1];
} Queue32;
typedef struct {
  unsigned char *Head;
  unsigned char *Tail;
  unsigned char Buff[64 + 1];
} Queue64;
typedef struct {
  unsigned char *Head;
  unsigned char *Tail;
  unsigned char Buff[90 + 1];
} Queue90;
typedef struct {
  unsigned char *Head;
  unsigned char *Tail;
  unsigned char Buff[120 + 1];
} Queue120;
typedef struct {
  unsigned char *Head;
  unsigned char *Tail;
  unsigned char Buff[340 + 1];
} Queue340;
typedef struct {
  unsigned char *Head;
  unsigned char *Tail;
  unsigned char Buff[745 + 1];
} Queue745;
typedef struct {
  unsigned char *Head;
  unsigned char *Tail;
  unsigned char Buff[128 + 1];
} Queue128;
typedef struct {
  unsigned char *Head;
  unsigned char *Tail;
  unsigned char Buff[248 + 1];
} Queue248;
typedef struct {
  unsigned char *Head;
  unsigned char *Tail;
  unsigned char Buff[256 + 1];
} Queue256;
typedef struct {
  unsigned char *Head;
  unsigned char *Tail;
  unsigned char Buff[512 + 1];
} Queue512;
typedef struct {
  unsigned char *Head;
  unsigned char *Tail;
  unsigned char Buff[1024 + 1];
} Queue1K;
typedef struct {
  unsigned char *Head;
  unsigned char *Tail;
  unsigned char Buff[2048 + 1];
} Queue2K;
typedef struct {
  unsigned char *Head;
  unsigned char *Tail;
  unsigned char Buff[5120 + 1];
} Queue5K;
typedef struct {
  unsigned char *Head;
  unsigned char *Tail;
  unsigned char Buff[10240 + 1];
} Queue10K;

typedef enum {
  CPU_ENTER_CRITICAL, // CPU进入临界状态
  CPU_EXIT_CRITICAL   // CPU退出临界状态
} CPU_EA_TYPEDEF;

/* 定义一个CPU中断控制回调函数指针，别名：CPUInterrupt_CallBack_t
 * 形参：- cmd    ：传入CPU中断打开还是关闭中断临界。
 *      - *pSta  : 通过指针传入地址
 * */
typedef void (*CPUInterrupt_CallBack_t)(CPU_EA_TYPEDEF cmd,
                                        unsigned char *pSta);

//系统任务ID.数量:用枚举灵活分配数组大小
typedef enum { OS_TASK1, OS_TASK_SUM } OS_TaskID_TypeDef;

//系统任务运行状态
typedef enum {
  OS_SLEEP,          //任务休眠
  OS_RUN = !OS_SLEEP //任务运行
} OS_TaskStatusTypeDef;

// 编写系统内核之第一步:创建系统任务结构体
typedef struct {
  void (*task)(void); //任务函数指针:函数指针指向处理函数,一般是while(1)中的函数
  OS_TaskStatusTypeDef RunFlag; //任务运行状态:休眠还是运行
  unsigned short RunPeriod; //任务调度频率:任务指向的处理函数执行的频率
  unsigned short RunTimer; //任务调度计时器:时间达到任务调度频率时,任务会被执行
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