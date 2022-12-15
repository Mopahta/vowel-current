#ifndef _VMTFUNC
#define _VMTFUNC

#include "..\imports.h"

namespace vmtfunc {
	// call virtual function @ given index
	template <typename Return, typename ... Arguments>
	constexpr Return Call(void* vmt, const DWORD index, Arguments ... args) noexcept
	{
		using Function = Return(__thiscall*)(void*, decltype(args)...);
		return (*static_cast<Function**>(vmt))[index](vmt, args...);
	}

	// get void pointer to virtual function @ given index
	constexpr void* Get(void* vmt, const DWORD index) noexcept
	{
		return (*static_cast<void***>(vmt))[index];
	}
}
#endif