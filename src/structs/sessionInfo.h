#include "..\imports.h"

#ifndef _GAMEINFO
#define _GAMEINFO
typedef struct gameInfoStruct {
    HMODULE client;
    DWORD engine;
    DWORD glowObjManager;
    DWORD localPlayer;

} gameInfoStruct;

#endif