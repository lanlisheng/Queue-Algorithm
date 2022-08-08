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
  return 0;
}