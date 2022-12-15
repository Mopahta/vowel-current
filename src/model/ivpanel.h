#ifndef _IVPANEL
#define _IVPANEL

#include "..\imports.h"
#include "..\utils\vmtfunc.h"

class IVPanel
{
public:
	constexpr const char* GetName(DWORD panel) noexcept
	{
		return vmtfunc::Call<const char*>(this, 36, panel);
	}
};

#endif