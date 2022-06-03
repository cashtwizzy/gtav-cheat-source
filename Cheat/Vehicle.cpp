#include "Vehicle.h"

namespace Vehicler
{
	void Tick()
	{
		auto draw_list = ImGui::GetBackgroundDrawList();
		if (Config::VEHICLE::vehicle_speedboost)
		{
			if (GetAsyncKeyState(Config::VEHICLE::vehicle_speed_bind))
			{
				Inject::InjectorWrtiter::Vehicle::Set_SpeedMulti(Config::VEHICLE::vehicle_speed_amount);
			}
			else
			{
				Inject::InjectorWrtiter::Vehicle::Set_SpeedMulti(Config::VEHICLE::vehicle_speed);
			}
		}
		if (!Config::VEHICLE::vehicle_speedboost)
		{
			Inject::InjectorWrtiter::Vehicle::Set_SpeedMulti(Config::VEHICLE::vehicle_speed);
		}
		if (Config::VEHICLE::vehicle_camdist)
		{
			Inject::InjectorWrtiter::Vehicle::Set_CamDistance(Config::VEHICLE::vehicle_camdistance);
		}
	}
}