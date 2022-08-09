#include "key.h"

KEY_ID_TYPEDEF keyVal;      //����ID
KEY_STATE_TYPEDEF keyState; //����״̬

pKeyScanCallBack pKeyScanCBS; //����һ������ָ�����

void KeyInit(void) {
  keyVal = 0;
  keyState = KEY_IDLE;
  pKeyScanCBS = 0;
}

/*
 * ע�ắ��
 * 2.��ν��ú���ָ�����ָ��Ӧ�ò�ĺ�����ַ
 *
 * */
void KeyScanCBSRegister(pKeyScanCallBack pCBS) {
  if (pKeyScanCBS == 0) {
    //=0˵���ú���ָ��δ��ע���
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
        //���ڽ�Ӧ�ò�ĺ�����ֵ�����˸ú���ָ�����,�˴��Ĳ����൱��:KeyScanHandle(keyVal,keyState);
      }
    }
  }
}