#include <windows.h>

extern "C" __declspec(dllexport) void __stdcall vowelMain();

extern "C" __declspec(dllexport) void __stdcall vowelMain() {
    MessageBoxA(NULL, "Hi", "fkdslhf", NULL);

}