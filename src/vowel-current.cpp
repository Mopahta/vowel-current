#include "imports.h"
#include "offset.h"

extern "C" __declspec(dllexport) BOOL vowelMain();

typedef struct glowStruct {
    float r;
    float g;
    float b;
    float a;
    uint8_t unk1[16];
    bool m_bRenderWhenOccluded;
    bool m_bRenderWhenUnoccluded;
    bool m_bFullBloom;
    uint8_t unk2[1];
    int m_nFullBloomStencilTestValue;
    int m_nStyle;
    int m_nSplitScreenSlot;
} glowStruct;

DWORD WINAPI vowelThread(LPVOID params) {
    MessageBoxA(NULL, "Hi", "fkdslhf", NULL);

    HANDLE hClient = GetModuleHandleA("client.dll");
    int retButtonPressed = 0;
    glowStruct glowOptions = {
            .r = 0.255, .g = 0, .b = 0.255, .a = 0.55, 
            .m_bRenderWhenOccluded = true, .m_bRenderWhenUnoccluded = false
        };

    while (true) {

        using namespace hazedumper;

        static char str1[256] = {0};
        static char str2[256] = {0};
    
        DWORD localPlayer = *(DWORD *) (hClient + signatures::dwLocalPlayer); 
        DWORD localTeam = *(DWORD *) (localPlayer + netvars::m_iTeamNum); 
        DWORD localHealth = *(DWORD *) (localPlayer + netvars::m_iHealth);

        // sprintf(str1, "%x", localTeam);
        // sprintf(str2, "%d", localHealth);
        // if (MessageBoxA(NULL, str1, str2, MB_OKCANCEL) == IDCANCEL) {
        //     break;
        // }


        DWORD glowArray = *(DWORD *) (hClient + signatures::dwGlowObjectManager);
        int glowCount = *(int *) (hClient + signatures::dwGlowObjectManager + 0x4);
        // sprintf(str1, "%x", glowArray);
        // sprintf(str2, "%d", glowCount);
        // if (MessageBoxA(NULL, str1, str2, MB_OKCANCEL) == IDCANCEL) {
        //     break;
        // }

        for (int i = 0; i < glowCount; i++) {
            // sprintf(str1, "%d", i);
            // MessageBoxA(NULL, str1, "index", NULL);

            DWORD entity = *(DWORD *) (glowArray + (i * 0x38) + 0x4);
            if (!entity) {
                continue;
            }
            // sprintf(str1, "%x", entity);
            // if (MessageBoxA(NULL, str1, "entity", MB_OKCANCEL) == IDCANCEL) {
            //     break;
            // }

            DWORD entityHealth = *(DWORD *) (entity + netvars::m_iHealth);
            if (!entityHealth) {
                continue;
            }
            // sprintf(str1, "%x", entityHealth);
            // if (MessageBoxA(NULL, str1, "entityHealth", MB_OKCANCEL) == IDCANCEL) {
            //     break;
            // }

            int entityTeam = *(int *) (entity + netvars::m_iTeamNum);
            if (entityTeam == localTeam) {
                continue;
            }
            // sprintf(str1, "%x", entityTeam);
            // if (MessageBoxA(NULL, str1, "entityTeam", MB_OKCANCEL) == IDCANCEL) {
            //     break;
            // }

            glowStruct *pGlow = (glowStruct *) (glowArray + i * 0x38 + 0x8);
            // sprintf(str1, "%x", pGlow);
            // if (MessageBoxA(NULL, str1, "pGlow", MB_OKCANCEL) == IDCANCEL) {
            //     break;
            // }

            // glowOptions = *pGlow;


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
    }

    return 0;
}

extern "C" __declspec(dllexport) BOOL vowelMain() {
    CreateThread(NULL, NULL, vowelThread, NULL, NULL, NULL);
    return TRUE;
}
