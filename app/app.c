// #include "app.h"
// #include "key.h"

// static void KeyEventHandle(KEY_VALUE_TYPEDEF keys);

// /* Ӧ�ò�����һ���ص�����
//  * 1.���ú����ĵ�ַ��ֵ��pKeyScanCBS�������ָ�����
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