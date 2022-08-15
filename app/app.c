#include "app.h"
#include "key.h"

static void KeyEventHandle(KEY_VALUE_TYPEDEF keys);

/* 应用层重新一个回调函数
 * 1.将该函数的地址赋值给pKeyScanCBS这个函数指针变量
 *
 * * */
static void KeyScanHandle(KEY_VALUE_TYPEDEF keys) {
  if ((keys = KEY1_CLICK) || (keys = KEY2_CLICK) || (keys = KEY3_CLICK) ||
      (keys = KEY4_CLICK) || (keys = KEY5_CLICK) || (keys = KEY6_CLICK)) {
    /* 短按执行的操作逻辑 */
  } else if ((keys == KEY1_CLICK_RELEASE) || (keys == KEY2_CLICK_RELEASE) ||
             (keys == KEY3_CLICK_RELEASE) || (keys == KEY4_CLICK_RELEASE) ||
             (keys == KEY5_CLICK_RELEASE) || (keys == KEY6_CLICK_RELEASE)) {
    /* 短按释放执行的操作逻辑 */
  } else if ((keys == KEY1_LONG_PRESS) || (keys == KEY2_LONG_PRESS) ||
             (keys == KEY3_LONG_PRESS) || (keys == KEY4_LONG_PRESS) ||
             (keys == KEY5_LONG_PRESS) || (keys == KEY6_LONG_PRESS)) {
    /* 长按执行的操作逻辑 */
  }
}

void AppInit(void) { hal_KeyScanCBSRegister(KeyEventHandle); }

void AppProc(void) {}