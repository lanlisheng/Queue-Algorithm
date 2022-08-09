/* 队列程序设计思路
1.定义队列缓存数组大小
2.入列的操作:怎么入列，按照顺序存储到数组里面
3.出列的操作：先进先出原则
 */

/* 入列操作：
1.队列的缓存可以存储的数组小标位置
2.队列是否满了，后续应该怎么处理
 */
#include "Queue.h"

void S_QueueEmpty(unsigned char **Head, unsigned char **Tail,
                  unsigned char *pBuff) {
  //队列的初始化过程
  *Head = pBuff;
  *Tail = pBuff;
}

/* 队列数据的入列操作 */
void S_QueueDataIn(unsigned char **Head, unsigned char **Tail,
                   unsigned char *pBuff, unsigned char Len,
                   unsigned char *pData, unsigned char DataLen) {
  unsigned char num;
  for (num = 0; num < DataLen; num++, pData++) {
    //单个单个入列的操作
    **Tail = *pData; //数据入列
    (*Tail)++;       //队尾指针加1

    //判断队列数据是否满了
    if (*Tail == pBuff + Len) {
      //数组首地址加上入列数据长度
      *Tail = pBuff;
    }
    //队尾指针与对头指针产生冲突：只入列，不出列的情况，防止违背先进先出原则
    if (*Tail == *Head) {
      if (++(*Head) == pBuff + Len) {
        *Head = pBuff;
      }
    }
  }
}

unsigned char S_QueueDataOut(unsigned char **Head, unsigned char **Tail,
                             unsigned char *pBuff, unsigned char Len,
                             unsigned char *pData) {
  unsigned char status;
  status = 0;
  //出列需要先判断缓存中有无数据
  if (*Head != *Tail) {
    //队列缓存中存在数据
    *pData = **Head;
    status = 1;
    if (++(*Head) == pBuff + Len) {
      *Head = pBuff;
    }
  }
  return status;
}

unsigned short S_QueueDataLen(unsigned char **Head, unsigned char **Tail,
                              unsigned char *pBuff, unsigned char Len) {
  //获取队列中的缓存长度
  if (*Tail > *Head) {
    return (*Tail - *Head);
  }

  //当入列很多数据，并且队列中没有进行出列操作，会存在队头指针大于队尾指针
  if (*Tail > *Head) {
    return (*Tail + Len - *Head);
  }
}