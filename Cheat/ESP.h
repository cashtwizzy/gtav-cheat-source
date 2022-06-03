#include "includes.h"

namespace ESP
{
	extern void Tick();
#ifndef _MAIN_H_
#define _MAIN_H_

	struct Players
	{
		DWORD64 ped;
		std::string name;
		ImVec4 position;
		float health;
		float armor;
	};

	struct Vehicles
	{
		DWORD64 vehicle;
		ImVec4 position;
		float health;
		float distance;
	};
#endif//_MAIN_H_
	extern Players players[300];
	extern Vehicles vehicles[120];
}