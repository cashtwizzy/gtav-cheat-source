#include "Helper.h"
#pragma warning(disable : 4996)
#include <Psapi.h>
#define INRANGE(x,a,b)  (x >= a && x <= b) 
#define getBits( x )    (INRANGE((x&(~0x20)),'A','F') ? ((x&(~0x20)) - 'A' + 0xa) : (INRANGE(x,'0','9') ? x - '0' : 0))
#define getByte( x )    (getBits(x[0]) << 4 | getBits(x[1]))

#ifdef _WIN64
#define PTRMAXVAL ((DWORD64)0x000F000000000000)
#else
#define PTRMAXVAL ((DWORD64)0xFFF00000)
#endif

namespace Helper
{
	bool ValidPTR(DWORD64 ptr)
	{
		if (ptr >= 0x10000 && ptr < PTRMAXVAL)
			return true;

		return false;
	}

	DWORD64 FindPattern(const char* szModule, const char* szSignature)
	{
		MODULEINFO modInfo;
		GetModuleInformation(GetCurrentProcess(), GetModuleHandleA(szModule), &modInfo, sizeof(MODULEINFO));
		DWORD64 startAddress = (DWORD64)GetModuleHandleA(szModule);
		DWORD64 endAddress = (startAddress + (DWORD64)modInfo.SizeOfImage);
		const char* pat = szSignature;
		DWORD64 firstMatch = 0;
		for (DWORD64 pCur = startAddress; pCur < endAddress; pCur++)
		{
			if (!*pat) return firstMatch;
			if (*(PBYTE)pat == ('\?') || *(BYTE*)pCur == getByte(pat))
			{
				if (!firstMatch) firstMatch = pCur;
				if (!pat[2]) return firstMatch;
				if (*(PWORD)pat == ('\?\?') || *(PBYTE)pat != ('\?')) pat += 3;
				else pat += 2;
			}
			else {
				pat = szSignature;
				firstMatch = 0;
			}
		}
		return NULL;
	}
	SIZE_T GetPointerAddress(SIZE_T Address, UINT Offset)
	{
		if (Address == 0)
			return 0;

		if (sizeof(SIZE_T) == 8)
			return Address + (INT)((*(INT*)(Address + Offset) + Offset) + sizeof(INT));

		return (SIZE_T) * (DWORD*)(Address + Offset);
	}
}