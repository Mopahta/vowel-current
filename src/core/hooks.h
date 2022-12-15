#ifndef _HOOK
#define _HOOK

#include "..\minhook\minhook.h"
#include "interfaces.h"
#include "..\utils\vmtfunc.h"

namespace hooks {
	int init() noexcept;

	void destroy() noexcept;

	using PaintTraverseFn = void (__thiscall *) (IVPanel *, DWORD, bool, bool) noexcept;
	inline PaintTraverseFn PaintTraverseOriginal = nullptr;
	void __fastcall PaintTraverse(void* ecx, void* edx, DWORD vguiPanel, bool forceRepaint, bool allowForce) noexcept;
}

#endif