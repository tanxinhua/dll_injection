// pch.cpp: 与预编译标头对应的源文件

#include "pch.h"

// 当使用预编译的头时，需要使用此源文件，编译才能成功。


#include <stdio.h>
#include <windows.h>

extern HMODULE g_hDllModule;

// 共享内存
#pragma data_seg("mydata")
HHOOK g_hHook = NULL;
int g_count = 0;
#pragma data_seg()
#pragma comment(linker, "/SECTION:mydata,RWS")

//钩子回调函数
LRESULT GetMsgProc(int code, WPARAM wParam, LPARAM lParam) {
  g_count++;  
  if (g_count < 2) {
    char str[1024] = {};
    sprintf_s(str, 1024, "hook is ok%d", g_count);
    //MessageBoxA(NULL, str, "hook", 1);
  } 
  return true;
  return ::CallNextHookEx(g_hHook, code, wParam, lParam);
}

// 设置钩子
BOOL SetHook() {
  g_hHook =
      SetWindowsHookEx(WH_KEYBOARD, (HOOKPROC)GetMsgProc, g_hDllModule, 0);
  if (NULL == g_hHook) {
    return FALSE;
  }
  return TRUE;
}

// 卸载钩子
BOOL UnsetHook() {
  if (g_hHook) {
    UnhookWindowsHookEx(g_hHook);
  }
  return TRUE;
}