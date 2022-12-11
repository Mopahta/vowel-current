#include "imports.h"
#include "offset.h"
#include "structs/glowStruct.h"
#include "structs/sessionInfo.h"
#include "structs/vector.h"

// #define _DEBUG

extern "C" __declspec(dllexport) BOOL vowelMain();
int modelEnglow(DWORD localTeam, bool glowTeammates);
Vector3 calcAngles(const Vector3& localPosition, const Vector3& enemyPosition, const Vector3& viewAngles);
int modelEnglowThread(DWORD localTeam);
int aimAtHead(DWORD localTeam, bool throughObjects);
void changeSettings();

char str1[256] = {0};
char str2[256] = {0};

gameInfoStruct gameInfo;
bool glowOn = true;
bool glowTeammates = true;
bool aimOn = true;
bool aimThroughObjects = false;

#ifdef _DEBUG
#define print(value1, value2) sprintf(str1, "%x", value1); \
    sprintf(str2, "%x", value2); \
    if (MessageBoxA(NULL, str1, str2, MB_OKCANCEL) == IDCANCEL) { \
        return 1; \
    }
#else
#define print(str1, str2)
#endif

typedef struct vector3 {
    float x;
    float y;
    float z;
} vector3;

DWORD WINAPI vowelThread(LPVOID params) {
    MessageBoxA(NULL, "Hi", "fkdslhf", NULL);

    gameInfo.client = GetModuleHandleA("client.dll");
    gameInfo.engine = GetModuleHandleA("engine.dll");
    print(gameInfo.client, gameInfo.engine);
    int retButtonPressed = 0;


    while (!GetAsyncKeyState(VK_END)) {
        // std::this_thread::sleep_for(std::chrono::milliseconds(1));

        using namespace hazedumper;

        static char str1[256] = {0};
        static char str2[256] = {0};
    
        gameInfo.localPlayer = *(DWORD *) (gameInfo.client + signatures::dwLocalPlayer); 
        DWORD localTeam = *(DWORD *) (gameInfo.localPlayer + netvars::m_iTeamNum); 
        DWORD localHealth = *(DWORD *) (gameInfo.localPlayer + netvars::m_iHealth);

        if (glowOn) {
            modelEnglow(localTeam, glowTeammates);
        }

        if (!GetAsyncKeyState(VK_LBUTTON)) {
            continue;
        }

        if (aimOn) {
            aimAtHead(localTeam, aimThroughObjects);
        }

        changeSettings();
    }

    return 0;
}

void changeSettings() {
    if (GetAsyncKeyState(VK_NUMPAD0)) {
        glowOn = !glowOn;
    }

    if (GetAsyncKeyState(VK_NUMPAD1)) {
        glowTeammates = !glowTeammates;
    }

    if (GetAsyncKeyState(VK_NUMPAD2)) {
        aimOn = !aimOn;
    }

    if (GetAsyncKeyState(VK_NUMPAD3)) {
        aimThroughObjects = !aimThroughObjects;
    }
}

int modelEnglowThread(DWORD localTeam) {
    while (true) {
        if (modelEnglow(localTeam, glowTeammates)) {
            return 1;
        }
    }
}

int modelEnglow(DWORD localTeam, bool glowTeammates) {
    using namespace hazedumper;
    gameInfo.glowObjManager = *(DWORD *) (gameInfo.client + signatures::dwGlowObjectManager);
    int glowCount = *(int *) (gameInfo.client + signatures::dwGlowObjectManager + 0x4);

    for (int i = 0; i < glowCount; i++) {
        DWORD entity = *(DWORD *) (gameInfo.glowObjManager + (i * 0x38) + 0x4);
        if (!entity) {
            continue;
        }

        DWORD entityHealth = *(DWORD *) (entity + netvars::m_iHealth);
        if (!entityHealth) {
            continue;
        }

        int entityTeam = *(int *) (entity + netvars::m_iTeamNum);
        if (entityTeam == localTeam && !glowTeammates) {
            continue;
        }

        glowStruct *pGlow = (glowStruct *) (gameInfo.glowObjManager + i * 0x38);

        if (entityTeam == 3) {
            pGlow->r = 0.447058827f;
            pGlow->g = 0.607843161f;
            pGlow->b = 0.8666667f;
        }
        else if (entityTeam == 2) {
            pGlow->r = 0.8784314f;
            pGlow->g = 0.6862745f;
            pGlow->b = 0.3372549f;
        }

        pGlow->m_bRenderWhenOccluded = true;
        pGlow->m_bRenderWhenUnoccluded = false;
        pGlow->a = 0.55f;
    }

    return 0;
}

int aimAtHead(DWORD localTeam, bool throughObjects) {

    using namespace hazedumper;
    Vector3 localEyePosition = (*(Vector3 *) (gameInfo.localPlayer + netvars::m_vecOrigin)) + 
        (*(Vector3 *) (gameInfo.localPlayer + netvars::m_vecViewOffset));

    print(1, 1);
    DWORD clientState = *(DWORD *) (gameInfo.engine + signatures::dwClientState);

    Vector3 viewAngles = *(Vector3 *) (clientState + signatures::dwClientState_ViewAngles);
    Vector3 aimPunch = (*(Vector3 *) (gameInfo.localPlayer + netvars::m_aimPunchAngle)) * 2;
    print(1, 2);

    float bestFov = 100.f;
    Vector3 bestAngle = Vector3();

    for (int i = 1; i <= 32; i++) {
        print(0, i);
        DWORD player = *(DWORD *) (gameInfo.client + signatures::dwEntityList + i * 0x10);

        if (!player) {
            continue;
        }

        if (*(DWORD *) (player + netvars::m_iTeamNum) == localTeam) {
            continue;
        }

        if (*(bool *) (player + signatures::m_bDormant)) {
            continue;
        }

        if (!(*(int *) (player + netvars::m_iHealth))) {
            continue;
        }

        if (!throughObjects && !(*(bool *) (player + netvars::m_bSpottedByMask))) {
            continue;
        }

        print(player, i);

        DWORD boneMatrix = *(DWORD *) (player + netvars::m_dwBoneMatrix);

        Vector3 playerHeadPosition = Vector3 {
            *(float *) (boneMatrix + 0x30 * 8 + 0x0C),
            *(float *) (boneMatrix + 0x30 * 8 + 0x1C),
            *(float *) (boneMatrix + 0x30 * 8 + 0x2C),
        };

        Vector3 angle = calcAngles(localEyePosition, playerHeadPosition, viewAngles + aimPunch);

        float fov = std::hypot(angle.x, angle.y);

        if (fov < bestFov) {
            bestFov = fov;
            bestAngle = angle;
        }

    }

    print(1, 1);

    if (!bestAngle.notChanged()) {
        Vector3* newAngle = (Vector3 *) (clientState + signatures::dwClientState_ViewAngles);
        Vector3 tempAngle = viewAngles + bestAngle / 3.f;

        newAngle->x = tempAngle.x;
        newAngle->y = tempAngle.y;
        newAngle->z = tempAngle.z;
    }

    return 0;
}

Vector3 calcAngles(const Vector3& localPosition, const Vector3& enemyPosition, const Vector3& viewAngles) {
    return ((enemyPosition - localPosition).toAngle() - viewAngles);
}

extern "C" __declspec(dllexport) BOOL vowelMain() {
    CreateThread(NULL, NULL, vowelThread, NULL, NULL, NULL);
    return TRUE;
}
