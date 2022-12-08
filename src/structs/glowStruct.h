#include "..\imports.h"

#ifndef _GLOWSTRUCT
#define _GLOWSTRUCT
typedef struct glowStruct {
    int32_t m_nNextFreeSlot;           //0x0000
    DWORD* m_pEntity;    //0x0004
    float r;                           //0x0008
    float g;                           //0x0014
    float b;                           //0x000C
    float a;                           //0x0010
    uint8_t unk1[16];                  //0x0018   
    bool m_bRenderWhenOccluded;        //0x0028   
    bool m_bRenderWhenUnoccluded;      //0x0029
    bool m_bFullBloom;                    //0x0018
    uint8_t unk2[1];                      //0x001C
    int m_nFullBloomStencilTestValue;     //0x0020
    int m_nStyle;                         //0x0024
    int m_nSplitScreenSlot;               //0x0025
} glowStruct;                             //0x0026
                                          //0x0027
#endif                                    //0x002C
                                          //0x0030
                                          //0x0034