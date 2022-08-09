#ifndef _KEY_H_
#define _KEY_H_

typedef enum { KEY1, KEY2 } KEY_ID_TYPEDEF;

typedef enum {
  KEY_IDLE,       //空闲状态
  KEY_PRESS,      //短按
  KEY_LONG_PRESS, //长按
  KEY_RELEASE     //按键释放
} KEY_STATE_TYPEDEF;

//声明一个函数指针
typedef void (*pKeyScanCallBack)(KEY_ID_TYPEDEF KeyID,
                                 KEY_STATE_TYPEDEF KeyState);

void KeyScanCBSRegister(pKeyScanCallBack pCBS);
void KeyInit(void);
void KeyPoll(void);
#endif
