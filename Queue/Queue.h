#ifndef _QUEUE_H_
#define _QUEUE_H_

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
  unsigned char Buff[4];
} Queue4;

#endif
