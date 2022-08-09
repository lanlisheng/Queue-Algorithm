#include "Queue.h"
#include <stdio.h>

Queue4 KeyMsg;

int main(int argc, char *argv[]) {
  unsigned char a;
  QueueEmpty(KeyMsg);
  printf("site:%d\r\n", sizeof(KeyMsg.Buff));
  printf("&KeyMsg = 0x%x,KeyMsg.Buff = 0x%x,KeMsg.Head = 0x%x,KeyMsg.Tail = "
         "0x%x\r\n",
         &KeyMsg, KeyMsg.Buff, KeyMsg.Head, KeyMsg.Tail);
  printf("&buff[0]=0x%x,&buff[1]=0x%x,&buff[2]=0x%x,&buff[3]=0x%x \r\n",
         &KeyMsg.Buff[0], &KeyMsg.Buff[1], &KeyMsg.Buff[2], &KeyMsg.Buff[3]);
  return 0;
}

/* Test */
//入列操作
// a = 1;
// QueueDataIn(KeyMsg, &a, 1);
// printf("&KeyMsg = 0x%x,KeyMsg.Buff= 0x%x,KeyMsg.Head = 0x%x,KeyMsg.Tail = "
//        "0x%x\r\n",
//        &KeyMsg, KeyMsg.Buff, KeyMsg.Head, KeyMsg.Tail);

//出列操作
// QueueDataOut(KeyMsg, &a);
// printf("a = %d\r\n", a);
// printf("&TestMsg = 0x%x,TestMsg.Buff = 0x%x,TestMsg.Head = 0x%x,TestMsg.Tail
// = "
//        "0x%x\r\n",
//        &KeyMsg, KeyMsg.Buff, KeyMsg.Head, KeyMsg.Tail);
// printf("buff[0] = 0x%x,buff[1] = 0x%x,buff[2] = 0x%x,buff[3] = 0x%x,buff[4] =
// "
//        "0x%x\r\n",
//        KeyMsg.Buff[0], KeyMsg.Buff[1], KeyMsg.Buff[2], KeyMsg.Buff[3], );
// printf("\r\n");