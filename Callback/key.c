#include "key.h"

KEY_ID_TYPEDEF keyVal;      //按键ID
KEY_STATE_TYPEDEF keyState; //按键状态

pKeyScanCallBack pKeyScanCBS; //定义一个函数指针变量

void KeyInit(void) {
  keyVal = 0;
  keyState = KEY_IDLE;
  pKeyScanCBS = 0;
}

/*
 * 注册函数
 * 2.如何将该函数指针变量指向应用层的函数地址
 *
 * */
void KeyScanCBSRegister(pKeyScanCallBack pCBS) {
  if (pKeyScanCBS == 0) {
    //=0说明该函数指针未被注册过
    pKeyScanCBS = pCBS;
  }
}

void KeyPoll(void) {
  printf("Please Enter Key value: ");
  if (scanf("%d", &keyVal) == 1) {
    printf("\r\n");
    printf("Please Enter key state:");
    if (scanf("%d", &keyState) == 1) {
      if (pKeyScanCBS != 0) {
        pKeyScanCBS(keyVal, keyState);
        //由于将应用层的函数赋值给到了该函数指针变量,此处的操作相当于:KeyScanHandle(keyVal,keyState);
      }
    }
  }
}