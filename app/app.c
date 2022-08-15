#include "app.h"
#include "key.h"

static void KeyEventHandle(KEY_VALUE_TYPEDEF keys);

/* Ӧ�ò�����һ���ص�����
 * 1.���ú����ĵ�ַ��ֵ��pKeyScanCBS�������ָ�����
 *
 * * */
static void KeyScanHandle(KEY_VALUE_TYPEDEF keys) {
  if ((keys = KEY1_CLICK) || (keys = KEY2_CLICK) || (keys = KEY3_CLICK) ||
      (keys = KEY4_CLICK) || (keys = KEY5_CLICK) || (keys = KEY6_CLICK)) {
    /* �̰�ִ�еĲ����߼� */
  } else if ((keys == KEY1_CLICK_RELEASE) || (keys == KEY2_CLICK_RELEASE) ||
             (keys == KEY3_CLICK_RELEASE) || (keys == KEY4_CLICK_RELEASE) ||
             (keys == KEY5_CLICK_RELEASE) || (keys == KEY6_CLICK_RELEASE)) {
    /* �̰��ͷ�ִ�еĲ����߼� */
  } else if ((keys == KEY1_LONG_PRESS) || (keys == KEY2_LONG_PRESS) ||
             (keys == KEY3_LONG_PRESS) || (keys == KEY4_LONG_PRESS) ||
             (keys == KEY5_LONG_PRESS) || (keys == KEY6_LONG_PRESS)) {
    /* ����ִ�еĲ����߼� */
  }
}

void AppInit(void) { hal_KeyScanCBSRegister(KeyEventHandle); }

void AppProc(void) {}