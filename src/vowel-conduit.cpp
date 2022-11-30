#define WIN32_LEAN_AND_MEAN
#include <windows.h>

extern "C" __declspec(dllexport) BOOL vowelMain();

DWORD WINAPI vowelThread(LPVOID params) {
    MessageBoxA(NULL, "Hi", "fkdslhf", NULL);
    int c = 2+2;
    int a = 5;
    int b = c * a;

    return 0;
}

extern "C" __declspec(dllexport) BOOL vowelMain() {
    CreateThread(NULL, NULL, vowelThread, NULL, NULL, NULL);
    return TRUE;
}

