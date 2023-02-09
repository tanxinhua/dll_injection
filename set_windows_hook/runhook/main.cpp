// GolbalInjectDll.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <Windows.h>

#include <iostream>

int main() {
  typedef BOOL (*typedef_SetGlobalHook)();
  typedef BOOL (*typedef_UnsetGlobalHook)();
  HMODULE hDll = NULL;
  typedef_SetGlobalHook SetGlobalHook = NULL;
  typedef_UnsetGlobalHook UnsetGlobalHook = NULL;
  BOOL bRet = FALSE;

  do {
    hDll = ::LoadLibraryW(TEXT("hookdll.dll"));
    if (NULL == hDll) {
      printf("LoadLibrary Error[%d]\n", ::GetLastError());
      break;
    }

    SetGlobalHook = (typedef_SetGlobalHook)::GetProcAddress(hDll, "SetHook");
    if (NULL == SetGlobalHook) {
      printf("GetProcAddress Error[%d]\n", ::GetLastError());
      break;
    }

    bRet = SetGlobalHook();
    if (bRet) {
      printf("SetGlobalHook OK.\n");
    } else {
      printf("SetGlobalHook ERROR.\n");
    }

    system("pause");

    UnsetGlobalHook =
        (typedef_UnsetGlobalHook)::GetProcAddress(hDll, "UnsetHook");
    if (NULL == UnsetGlobalHook) {
      printf("GetProcAddress Error[%d]\n", ::GetLastError());
      break;
    }
    UnsetGlobalHook();
    printf("UnsetGlobalHook OK.\n");

  } while (FALSE);

  system("pause");
  return 0;
}