#ifndef _INTERFACES
#define _INTERFACES

// #include "..\imports.h"
#include "windows.h"
#include "..\model\ivpanel.h"

namespace interfaces {
    void init();

    inline IVPanel* panel = nullptr;

    template <typename Interface> Interface* createInterface(const char* module, const char* interfaceName);

    inline DWORD getPanelP() {
        return (DWORD) panel;
    }
}

#endif