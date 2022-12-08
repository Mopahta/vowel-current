#include "..\imports.h"

#ifndef _GAMEINFO
#define _GAMEINFO
typedef struct gameInfoStruct {
    HANDLE client;
    HANDLE engine;
    DWORD glowObjManager;
    DWORD localPlayer;

} gameInfoStruct;

#endif