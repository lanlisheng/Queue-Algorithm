#include "Queue.h"
#include "key.h"
#include <stdio.h>

Queue4 KeyMsg;

/* 应用层重新一个回调函数
 * 1.将该函数的地址赋值给pKeyScanCBS这个函数指针变量
 *
 * * */
void KeyScanHandle(KEY_ID_TYPEDEF KeyID, KEY_STATE_TYPEDEF KeyState) {
  if (KeyID == KEY1) {
    printf("KeyID IS KEY1\r\n");
    if (KeyState == KEY_PRESS) {
      printf("KeyState is KEY_PRESS\r\n");
    }
  }
}

int main(int argc, char *argv[]) {

  KeyInit();
  KeyScanCBSRegister(KeyScanHandle);
  KeyPoll();
  //   unsigned char a;
  //   QueueEmpty(KeyMsg);
  //   printf("site:%d\r\n", sizeof(KeyMsg.Buff));
  //   printf("&KeyMsg = 0x%x,KeyMsg.Buff = 0x%x,KeMsg.Head = 0x%x,KeyMsg.Tail =
  //   "
  //          "0x%x\r\n",
  //          &KeyMsg, KeyMsg.Buff, KeyMsg.Head, KeyMsg.Tail);
  //   printf("&buff[0]=0x%x,&buff[1]=0x%x,&buff[2]=0x%x,&buff[3]=0x%x \r\n",
  //          &KeyMsg.Buff[0], &KeyMsg.Buff[1], &KeyMsg.Buff[2],
  //          &KeyMsg.Buff[3]);
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