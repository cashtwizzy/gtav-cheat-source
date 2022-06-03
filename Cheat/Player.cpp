#include "Player.h"
#include <vector>
//https://github.com/cashtwizzy
namespace Player
{
	void Tick()
	{
		if (Config::PLAYER::player_healkey_on)
		{
			if (GetAsyncKeyState(Config::PLAYER::player_healkey_bind))
			{
				Inject::InjectorWrtiter::Player::Set_Health(Config::PLAYER::player_healkey_heal_amount);
			}
		}

		if (Config::PLAYER::player_armorkey_on)
		{
			if (GetAsyncKeyState(Config::PLAYER::player_armorkey_bind))
			{
				Inject::InjectorWrtiter::Player::Set_Armor(Config::PLAYER::player_healkey_armor_amount);
			}
		}

		if (Config::PLAYER::tp_wp)
		{
			if (GetAsyncKeyState(Config::PLAYER::player_armorkey_bind) & 1)
			{
				Inject::InjectorWrtiter::Player::TeleportToWayPoint();
			}
		}

		if (Config::PLAYER::tp_crosshair)
		{
			if (GetAsyncKeyState(Config::PLAYER::tp_crosshair_bind))
			{
				//DWORD64 addr = Inject::GetCamera();
				//D3DXVECTOR3 CrosshairPos = *(D3DXVECTOR3*)(addr + 0x60);
				//Inject::MainPosition = *(D3DXVECTOR3*)(CrosshairPos + 0x90);
				//Inject::InjectorWrtiter::Player::Set_Position();
			}
		}

		if (Config::PLAYER::player_autoheal)
		{
			if (Inject::InjectorWrtiter::Player::Get_Health() <= 140)
			{
				Inject::InjectorWrtiter::Player::Set_Health(200);
			}
		}

		if (Config::PLAYER::player_semi_god)
		{
			Inject::InjectorWrtiter::Player::Set_Godmode(0x1);
		}
		else if (!Config::PLAYER::player_semi_god)
		{
			Inject::InjectorWrtiter::Player::Set_Godmode(0x0);
		}
		if (Config::PLAYER::player_superpunch)
		{
			Inject::InjectorWrtiter::Player::Set_MeeleDamageMulti(300.0f);
		}
		else if (!Config::PLAYER::player_superpunch)
		{
			Inject::InjectorWrtiter::Player::Set_MeeleDamageMulti(0.0f);
		}
		if (Config::PLAYER::player_no_collision)
		{
			Inject::InjectorWrtiter::Player::SetPlayerNoCollision();
		}
		if (Config::PLAYER::fovzoom)
		{
			Inject::InjectorWrtiter::Player::SetFOVZoom(Config::PLAYER::FovZoom);
		}
		if (Config::PLAYER::player_noclip)
		{
			Inject::InjectorWrtiter::Player::SetNoClip();
		}
		/*if (Config::PLAYER::player_no_ragdoll)
		{
			Inject::InjectorWrtiter::Player::Set_Ragdoll(true);
		}
		else if (!Config::PLAYER::player_no_ragdoll)
		{
			Inject::InjectorWrtiter::Player::Set_Ragdoll(false);
		}*/
		if (Config::PLAYER::player_runspeed)
		{
			Inject::InjectorWrtiter::Player::Set_RunSpeed(5.0f);
		}
		else if (!Config::PLAYER::player_runspeed)
		{
			Inject::InjectorWrtiter::Player::Set_RunSpeed(1.0f);
		}
		if (Config::PLAYER::player_swimspeed)
		{
			Inject::InjectorWrtiter::Player::Set_SwimSpeed(5.0f);
		}
		else if (!Config::PLAYER::player_swimspeed)
		{
			Inject::InjectorWrtiter::Player::Set_SwimSpeed(1.0f);
		}
		if (Config::MISC::neverwanted)
		{
			Inject::InjectorWrtiter::Player::Set_Wantedlevel(0);
		}

		//Inject::InjectorWrtiter::Player::Set_Seatbelt(Config::PLAYER::player_seatbelt);
		//Inject::InjectorWrtiter::Player::SetSuperFrameflag();
	}
}