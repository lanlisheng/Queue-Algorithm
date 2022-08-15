// #include "app.h"
// #include "key.h"

// static void KeyEventHandle(KEY_VALUE_TYPEDEF keys);

// /* 应用层重新一个回调函数
//  * 1.将该函数的地址赋值给pKeyScanCBS这个函数指针变量
//  *
//  * * */
// void KeyScanHandle(KEY_ID_TYPEDEF KeyID, KEY_STATE_TYPEDEF KeyState) {
//   if (KeyID == KEY1) {
//     printf("KeyID IS KEY1\r\n");
//     if (KeyState == KEY_PRESS) {
//       printf("KeyState is KEY_PRESS\r\n");
//     }
//   }
// }

// void AppInit(void) { hal_KeyScanCBSRegister(KeyEventHandle); }

// void AppProc(void) {}