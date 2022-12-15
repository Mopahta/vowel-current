#ifndef _IMPORTS
#define _IMPORTS

#include <Windows.h>
#include <cmath>
#include <thread>
#include <stdio.h>
#include <vector>

#define _DEBUG

inline char str1[256] = {0};
inline char str2[256] = {0};

#ifdef _DEBUG
#define print(value1, value2) sprintf(str1, "%x", value1); \
    sprintf(str2, "%x", value2); \
    if (MessageBoxA(NULL, str1, str2, MB_OKCANCEL) == IDCANCEL) { \
        return 1; \
    }
#else
#define print(str1, str2)
#endif

#endif