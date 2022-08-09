/* ���г������˼·
1.������л��������С
2.���еĲ���:��ô���У�����˳��洢����������
3.���еĲ������Ƚ��ȳ�ԭ��
 */

/* ���в�����
1.���еĻ�����Դ洢������С��λ��
2.�����Ƿ����ˣ�����Ӧ����ô����
 */
#include "Queue.h"

void S_QueueEmpty(unsigned char **Head, unsigned char **Tail,
                  unsigned char *pBuff) {
  //���еĳ�ʼ������
  *Head = pBuff;
  *Tail = pBuff;
}

/* �������ݵ����в��� */
void S_QueueDataIn(unsigned char **Head, unsigned char **Tail,
                   unsigned char *pBuff, unsigned char Len,
                   unsigned char *pData, unsigned char DataLen) {
  unsigned char num;
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
}

unsigned char S_QueueDataOut(unsigned char **Head, unsigned char **Tail,
                             unsigned char *pBuff, unsigned char Len,
                             unsigned char *pData) {
  unsigned char status;
  status = 0;
  //������Ҫ���жϻ�������������
  if (*Head != *Tail) {
    //���л����д�������
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
  //��ȡ�����еĻ��泤��
  if (*Tail > *Head) {
    return (*Tail - *Head);
  }

  //�����кܶ����ݣ����Ҷ�����û�н��г��в���������ڶ�ͷָ����ڶ�βָ��
  if (*Tail > *Head) {
    return (*Tail + Len - *Head);
  }
}