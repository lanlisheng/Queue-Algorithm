#ifndef _KEY_H_
#define _KEY_H_

typedef enum { KEY1, KEY2 } KEY_ID_TYPEDEF;

typedef enum {
  KEY_IDLE,       //����״̬
  KEY_PRESS,      //�̰�
  KEY_LONG_PRESS, //����
  KEY_RELEASE     //�����ͷ�
} KEY_STATE_TYPEDEF;

//����һ������ָ��
typedef void (*pKeyScanCallBack)(KEY_ID_TYPEDEF KeyID,
                                 KEY_STATE_TYPEDEF KeyState);

void KeyScanCBSRegister(pKeyScanCallBack pCBS);
void KeyInit(void);
void KeyPoll(void);
#endif
