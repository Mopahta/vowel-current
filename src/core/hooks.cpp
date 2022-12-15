#include "hooks.h"

int hooks::init() noexcept {
    MH_Initialize();

    MH_STATUS status = MH_CreateHook(
        vmtfunc::Get(interfaces::panel, 41),
        (LPVOID) &PaintTraverse,
        (void **) (&PaintTraverseOriginal)
    );

    print(status, 0);

    status = MH_EnableHook(MH_ALL_HOOKS);

    print(status, 0);

    return 0;
}

void hooks::destroy() noexcept {
    MH_DisableHook(MH_ALL_HOOKS);
    MH_RemoveHook(MH_ALL_HOOKS);

    MH_Uninitialize();
}

void __fastcall hooks::PaintTraverse(void* ecx, void*edx, DWORD vguiPanel, bool forceRepaint, bool allowForce) noexcept {
    PaintTraverseOriginal((IVPanel *) ecx, vguiPanel, forceRepaint, allowForce);
}