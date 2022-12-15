#include "interfaces.h"

template <typename Interface>
Interface* interfaces::createInterface(const char* module, const char* interfaceName) {
    HMODULE hModule = GetModuleHandle(module);

    if (!hModule) {
        return nullptr;
    }

    using getInterfaceFn = Interface *(__cdecl *)(const char *, int *);
    getInterfaceFn createInterfaceInst = reinterpret_cast<getInterfaceFn> (GetProcAddress(hModule, "CreateInterface"));

    return createInterfaceInst(interfaceName, nullptr);
}

void interfaces::init() {
    panel = createInterface<IVPanel>("vgui2.dll", "VGUI_Panel009");
}