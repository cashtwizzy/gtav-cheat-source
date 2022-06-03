#include "Weapon.h"

namespace Weapon
{
	void Tick()
	{
		if (Config::WEAPON::weapon_no_recoil)
		{
			Inject::InjectorWrtiter::Weapon::Set_Recoil(0.0f);
		}
		if (!Config::WEAPON::weapon_no_recoil)
		{
			Inject::InjectorWrtiter::Weapon::Set_Recoil(0.3f);
		}

		if (Config::WEAPON::weapon_no_spread)
		{
			Inject::InjectorWrtiter::Weapon::Set_Spread(0.0f);
		}
		if (!Config::WEAPON::weapon_no_spread)
		{
			Inject::InjectorWrtiter::Weapon::Set_Spread(0.3f);
		}

		if (Config::WEAPON::weapon_no_reload)
		{
			Inject::InjectorWrtiter::Weapon::Set_ReloadMultipler(10.0f);
		}
		if (!Config::WEAPON::weapon_no_reload)
		{
			Inject::InjectorWrtiter::Weapon::Set_ReloadMultipler(1.0f);
		}

		if (Config::WEAPON::weapon_range)
		{
			Inject::InjectorWrtiter::Weapon::Set_WeaponRange(300.0f);
		}
		if (!Config::WEAPON::weapon_range)
		{
			Inject::InjectorWrtiter::Weapon::Set_WeaponRange(80.0f);
		}

		if (Config::WEAPON::weapon_max_damage)
		{
			Inject::InjectorWrtiter::Weapon::Set_WeaponDamage(500.0f);
		}
		if (!Config::WEAPON::weapon_max_damage)
		{
			Inject::InjectorWrtiter::Weapon::Set_WeaponDamage(30.0f);
		}
	}
}