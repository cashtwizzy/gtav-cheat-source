#include <cstdlib>
#include <Windows.h>
#include <iostream>
#include <vector>

#include "includes.h"

namespace Helper
{
	extern bool ValidPTR(DWORD64 ptr);
	extern DWORD64 FindPattern(const char* szModule, const char* szSignature);
	extern SIZE_T GetPointerAddress(SIZE_T Address, UINT Offset);
}