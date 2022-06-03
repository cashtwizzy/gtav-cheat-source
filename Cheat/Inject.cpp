#include "inject.h"

namespace Inject
{
	D3DXVECTOR3 MainPosition;

	typedef BOOLEAN(__cdecl* WorldToScreen_t)(Vector3* WorldPos, float* x, float* y);
	typedef BOOLEAN(__cdecl* WorldToScreenOther_t)(D3DXVECTOR3* WorldPos, float* x, float* y);

	using get_name_verify_t = DWORD64 * (*)();
	using get_rage_name_t = __int64(*)(DWORD64* thisptr, WORD a2);
	using rage_nametags_setter_t = void(*)(bool value);

	WorldToScreen_t World2Screen = nullptr;
	WorldToScreenOther_t World2ScreenOther = nullptr;
	rage_nametags_setter_t pattern_rage037_nametags_setter = nullptr;
	get_rage_name_t ptr_rage037_get_rage_name = nullptr;
	get_name_verify_t ptr_rage037_get_name_verify = nullptr;

	std::string get_name_from_index(WORD i)
	{
		/*if (i < std::size(ragemp::ragemp_player_shift))
		{
			auto id = ~__ROR2__(i + ((0x0 - 0x198) & 0x3FF), 8);
			std::string result = *reinterpret_cast<std::string*>(ptr_rage037_get_rage_name(ptr_rage037_get_name_verify(), ragemp::ragemp_player_shift[(WORD)id]));
			return result.c_str();
		}*/

		return "Dima12";
	}

	void ToggleNametags(bool value)
	{
		pattern_rage037_nametags_setter(value);
	}

	ImVec2 WorldToScreen(Vector3 WorldPos)
	{
		ImVec2 pos;
		if (Helper::ValidPTR((DWORD64)World2Screen))
		{
			if (static_cast<BOOLEAN>(World2Screen(&WorldPos, &pos.x, &pos.y)))
			{
				pos.x = pos.x * ImGui::GetIO().DisplaySize.x;
				pos.y = pos.y * ImGui::GetIO().DisplaySize.y;
				return pos;
			}
		}
		return pos;
	}

	D3DXVECTOR2 WorldToScreenOther(D3DXVECTOR3 WorldPos)
	{
		D3DXVECTOR2 pos;
		if (Helper::ValidPTR((DWORD64)World2ScreenOther))
		{
			if (static_cast<BOOLEAN>(World2ScreenOther(&WorldPos, &pos.x, &pos.y)))
			{
				pos.x = pos.x * ImGui::GetIO().DisplaySize.x;
				pos.y = pos.y * ImGui::GetIO().DisplaySize.y;
				return pos;
			}
		}
		return D3DXVECTOR2(pos.x, pos.y);
	}

	ImVec2 WorldToScreen2(D3DXVECTOR3 WorldPos)
	{
		return WorldToScreen(Vector3(WorldPos.x, WorldPos.y, WorldPos.z));
	}

	D3DXVECTOR2 WorldToScreen2Other(D3DXVECTOR3 WorldPos)
	{
		return WorldToScreenOther(D3DXVECTOR3(WorldPos.x, WorldPos.y, WorldPos.z));
	}

	DWORD64 World;
	DWORD64 LocalPlayer;
	DWORD64 LocalPlayerInfo;
	DWORD64 Camera;
	DWORD64 ReplayInterface;
	DWORD64 WeaponBase;
	DWORD64 BonePositionAddress;
	DWORD64 BlipPointer;

	DWORD64 ragemp037replayinterface;
	DWORD64 ragemp037namegetter;
	DWORD64 ragemp037namegetterverify;

	void InjectGame()
	{
		const char* process = "GTA5.exe";

		World = Helper::GetPointerAddress(Helper::FindPattern(process, "48 8B 05 ? ? ? ? 48 8B 58 08 48 85 DB 74 32"), 0x3); //GTA5
		World = *(DWORD64*)(World + 0x0);
		LocalPlayer = *(DWORD64*)(World + 0x8);
		LocalPlayerInfo = *(DWORD64*)(LocalPlayer + 0x10C8);
		WeaponBase = *(DWORD64*)(LocalPlayer + 0x10D8);
		ReplayInterface = Helper::GetPointerAddress(Helper::FindPattern(process, "48 8D 0D ? ? ? ? 48 8B D7 E8 ? ? ? ? 48 8D 0D ? ? ? ? 8A D8 E8 ? ? ? ? 84 DB 75 13 48 8D 0D"), 0x3);
		World2Screen = (WorldToScreen_t)Helper::FindPattern(process, "48 89 5C 24 ?? 55 56 57 48 83 EC 70 65 4C 8B 0C 25 ?? 00 00 00 8B");
		World2ScreenOther = (WorldToScreenOther_t)Helper::FindPattern(process, "48 89 5C 24 ?? 55 56 57 48 83 EC 70 65 4C 8B 0C 25 ?? 00 00 00 8B");

		Camera = Helper::GetPointerAddress(Helper::FindPattern(process, "48 8B 05 ? ? ? ? 48 8B 98 ? ? ? ? EB"), 0x3);
		BonePositionAddress = Helper::FindPattern(process, "48 89 5C 24 ?? 48 89 6C 24 ?? 48 89 74 24 ?? 57 48 83 EC 60 48 8B 01 41 8B E8 48 8B F2 48 8B F9 33 DB");
		BlipPointer = Helper::GetPointerAddress(Helper::FindPattern(process, "4C 8D 05 ? ? ? ? 0F B7 C1"), 0x3);

		const char* ragempdll = "multiplayerL.dll";
		DWORD ragempmoduledll = (DWORD)GetModuleHandleA("multiplayerL.dll");

		if (ragempmoduledll != NULL)
		{
			pattern_rage037_nametags_setter = (rage_nametags_setter_t)Helper::FindPattern(ragempdll, "88 0D ? ? ? ? C3");
			ptr_rage037_get_rage_name = (get_rage_name_t)Helper::FindPattern(ragempdll, "0F B7 C2 48 C1 E0 05");
			ptr_rage037_get_name_verify = (get_name_verify_t)Helper::FindPattern(ragempdll, "48 83 EC 38 48 C7 44 24 ? ? ? ? ? 48 8B 05 ? ? ? ? 48 85 C0 75 1B 8D 48 08");
		}
	}

	ImVec2 GetBonePosW2S(const int64_t cPed, const int32_t wMask)
	{
		__m128 tempVec4;
		reinterpret_cast<void* (__fastcall*)(int64_t, __m128*, int32_t)>(BonePositionAddress)(cPed, &tempVec4, wMask);
		Vector3 x(Vector3::FromM128(tempVec4).x, Vector3::FromM128(tempVec4).y, Vector3::FromM128(tempVec4).z);
		return WorldToScreen(x);
	}

	Vector3 GetBonePosW2S2(const int64_t cPed, const int32_t wMask)
	{
		__m128 tempVec4;
		reinterpret_cast<void* (__fastcall*)(int64_t, __m128*, int32_t)>(BonePositionAddress)(cPed, &tempVec4, wMask);
		Vector3 x(Vector3::FromM128(tempVec4).x, Vector3::FromM128(tempVec4).y, Vector3::FromM128(tempVec4).z);
		return x;
	}

	DWORD64 GetCamera()
	{
		if (Helper::ValidPTR(Camera))
			return *(DWORD64*)(Camera + 0x0);
	}

	DWORD64 GetReplayInterface()
	{
		if (Helper::ValidPTR(ReplayInterface))
			return *(DWORD64*)(ReplayInterface + 0x0);
	}

	namespace Checker
	{
		namespace Player
		{
			bool Valid()
			{
				if (Helper::ValidPTR(World))
				{
					LocalPlayer = *(DWORD64*)(World + 0x8);
					if (LocalPlayer != NULL)
						return true;
				}
				return false;
			}

			bool In_Vehicle()
			{
				if (Inject::Checker::Player::Valid())
				{
					BYTE state = *(BYTE*)(LocalPlayer + 0xE50);
					if (state == 12)
						return true;
				}
				return false;
			}

			int32_t invehiclenew()
			{
				int32_t state = *(int32_t*)(LocalPlayer + 0xE50);
				if (state != 0)
					return true;
				else
					return false;
			}
		}
		namespace Vehicle
		{
			bool Valid()
			{
				if (Helper::ValidPTR(World))
				{
					DWORD64 vehicle = *(DWORD64*)(LocalPlayer + 0xD28);
					if (vehicle != NULL)
						return true;
				}
				return false;
			}
		}
	}

	namespace InjectorWrtiter
	{
		namespace Player
		{
			void Set_Health(float health)
			{
				if (Inject::Checker::Player::Valid()) {
					*(float*)(LocalPlayer + 0x280) = health;
				}
			}

			float Get_Health()
			{
				if (Inject::Checker::Player::Valid()) {
					return *(float*)(LocalPlayer + 0x280);
				}
			}

			void Set_Armor(float armor)
			{
				if (Inject::Checker::Player::Valid()) {
					*(float*)(LocalPlayer + 0x1530) = armor;
				}
			}

			float Get_Armor()
			{
				if (Inject::Checker::Player::Valid()) {
					return *(float*)(LocalPlayer + 0x1530);
				}
			}

			Vector3 GetPosition()
			{
				if (Inject::Checker::Player::Valid())
					return *(Vector3*)(LocalPlayer + 0x90);
			}

			void Set_Position()
			{
				if (MainPosition.x == 0 && MainPosition.y == 0) return;
				if (Inject::Checker::Player::In_Vehicle())
				{
					DWORD64 curveh = *(DWORD64*)(LocalPlayer + 0xD30);
					if (curveh != 0) {
						DWORD64 posbase = *(DWORD64*)(curveh + 0x30);
						*(D3DXVECTOR3*)(posbase + 0x50) = MainPosition;
						*(D3DXVECTOR3*)(curveh + 0x90) = MainPosition;
					}
				}
				else
				{
					DWORD64 posbase = *(DWORD64*)(LocalPlayer + 0x30);
					*(D3DXVECTOR3*)(posbase + 0x50) = MainPosition;
					*(D3DXVECTOR3*)(LocalPlayer + 0x90) = MainPosition;
					uintptr_t dpos = *(uintptr_t*)(LocalPlayer + 0x30);
					D3DXVECTOR3 vec = *(D3DXVECTOR3*)(dpos + 0x50);
					*(D3DXVECTOR3*)(LocalPlayer + 0x90) = MainPosition;
				}
			}

			void SetPlayerPositionToCoord(D3DXVECTOR3 pos)
			{

				DWORD64 posbase = *(DWORD64*)(LocalPlayer + 0x30);
				*(D3DXVECTOR3*)(posbase + 0x50) = pos;
				*(D3DXVECTOR3*)(LocalPlayer + 0x90) = pos;
				uintptr_t dpos = *(uintptr_t*)(LocalPlayer + 0x30);
				D3DXVECTOR3 vec = *(D3DXVECTOR3*)(dpos + 0x50);
				*(D3DXVECTOR3*)(LocalPlayer + 0x90) = pos;
			}

			void SetVehiclePositionToCoord(D3DXVECTOR3 pos)
			{
				uintptr_t curveh = *(uintptr_t*)(Inject::LocalPlayer + 0x0D30);
				DWORD64 posbase = *(DWORD64*)(curveh + 0x30);
				*(D3DXVECTOR3*)(posbase + 0x50) = pos;
				*(D3DXVECTOR3*)(curveh + 0x90) = pos;
			}

			void Set_Godmode(uint8_t value)
			{
				if (Inject::Checker::Player::Valid()) {
					*(uint8_t*)(LocalPlayer + 0x0189) = value;
				}
			}

			void SetSuperFrameflag()
			{
				uint32_t frameFlags = *(uint32_t*)(Inject::LocalPlayerInfo + 0x0218);
				if (Config::PLAYER::player_superjump)
				{
					frameFlags |= 1 << 14;
				}
				if (Config::PLAYER::player_explosive_fist)
				{
					frameFlags |= 1 << 13;
				}
				if (Config::PLAYER::player_fire_ammo)
				{
					frameFlags |= 1 << 12;
				}
				if (Config::PLAYER::player_explosive_ammo)
				{
					frameFlags |= 1 << 11;
				}
				*(uint32_t*)(Inject::LocalPlayerInfo + 0x0218) = frameFlags;
			}

			void TeleportToWayPoint() {
				if (Inject::Checker::Player::Valid()) {
					D3DXVECTOR3 waypoint = *(D3DXVECTOR3*)(Config::GTA5 + 0x1FFD190);
					if (waypoint.x != 64000.0f && waypoint.x != 0.0f)
					{
						waypoint.z = -225.0f;
						if (Inject::Checker::Player::invehiclenew())
						{
							Player::SetVehiclePositionToCoord(waypoint);
						}
						else 
						{
							Player::SetPlayerPositionToCoord(waypoint);
						}
					}
				}
			}

			void Set_Seatbelt(bool value)
			{
				if (Inject::Checker::Player::Valid()) {
					if (value)
					{
						*(BYTE*)(LocalPlayer + 0x13EC) = 0xC9;
					}
					else
					{
						*(BYTE*)(LocalPlayer + 0x13EC) = 0xC8;
					}
				}
			}

			void Set_Ragdoll(bool value)
			{
				if (Inject::Checker::Player::Valid()) {
					if (value)
					{
						*(unsigned char*)(LocalPlayer + 0x10B8) = 1;
					}
					else 
					{
						*(unsigned char*)(LocalPlayer + 0x10B8) = 32;
					}
				}
			}

			void Set_RunSpeed(float value)
			{
				if (Inject::Checker::Player::Valid()) {
					*(float*)(LocalPlayerInfo + 0xCF0) = value;
				}
			}

			void Set_SwimSpeed(float value)
			{
				if (Inject::Checker::Player::Valid()) {
					*(float*)(LocalPlayerInfo + 0x170) = value;
				}
			}

			void Set_Wantedlevel(uint32_t value)
			{
				if (Inject::Checker::Player::Valid()) {
					*(uint32_t*)(LocalPlayerInfo + 0x888) = value;
				}
			}

			void Set_MeeleDamageMulti(float value)
			{
				if (Inject::Checker::Player::Valid()) {
					*(float*)(LocalPlayerInfo + 0x0D1C) = value;
				}
			}

			void SetPlayerNoCollision()
			{
				if (Inject::Checker::Player::Valid()) {
					uintptr_t PlayerNext = *(uintptr_t*)(LocalPlayer + 0x30);
					uintptr_t PlayerNext2 = *(uintptr_t*)(PlayerNext + 0x10);
					uintptr_t PlayerNext3 = *(uintptr_t*)(PlayerNext2 + 0x20);
					uintptr_t PlayerNext4 = *(uintptr_t*)(PlayerNext3 + 0x70);
					uintptr_t PlayerNext5 = *(uintptr_t*)(PlayerNext4 + 0x0);
					*(float*)(PlayerNext5 + 0x2C) = 0.0f;
				}
			}

			void SetFOVZoom(float range)
			{
				DWORD64 addr = Inject::GetCamera();
				DWORD64 CameraData = *(DWORD64*)(addr + 0x0010);
				*(float*)(CameraData + 0x0030) = range;
			}

			void SetFreeze(bool toggle)
			{
				if (toggle)
				{
					*(BYTE*)(LocalPlayer + 0x218) = 2;
				}
				else if (!toggle)
				{
					*(BYTE*)(LocalPlayer + 0x218) = 0;
				}
			}

			void SetNoClip()
			{
				if (Config::PLAYER::player_noclip)
				{
					if (GetAsyncKeyState(Config::PLAYER::player_noclip_bind) & 0x8000)
					{
						if (Inject::Checker::Player::invehiclenew())
						{
							uintptr_t curveh = *(uintptr_t*)(Inject::LocalPlayer + 0x0D30);
							D3DXVECTOR3 newpos = *(D3DXVECTOR3*)(curveh + 0x90);
							DWORD64 addr = Inject::GetCamera();
							Vector3 TPSangles = *(Vector3*)(addr + 0x03D0);
							newpos.x += TPSangles.x * 1.025f;
							newpos.y += TPSangles.y * 1.025f;
							newpos.z += TPSangles.z * 1.025f;
							Player::SetVehiclePositionToCoord(newpos);
						}
						else
						{
							SetFreeze(true);
							D3DXVECTOR3 newpos = *(D3DXVECTOR3*)(Inject::LocalPlayer + 0x90);
							DWORD64 addr = Inject::GetCamera();
							Vector3 TPSangles = *(Vector3*)(addr + 0x03D0);
							newpos.x += TPSangles.x * 1.025f;
							newpos.y += TPSangles.y * 1.025f;
							newpos.z += TPSangles.z * 1.025f;
							Player::SetPlayerPositionToCoord(newpos);
						}
					}
					SetFreeze(false);
				}
			}
		}

		namespace Vehicle
		{
			void Set_SpeedMulti(float multi)
			{
				if (Inject::Checker::Player::Valid()) {
					if (Inject::Checker::Player::invehiclenew())
					{
						uintptr_t CurrentVehicle = *(uintptr_t*)(Inject::LocalPlayer + 0x0D30);
						*(float*)(CurrentVehicle + 0x0C5C) = multi;
					}
				}
			}

			void Set_CamDistance(float distance)
			{
				if (Inject::Checker::Player::Valid()) {
					if (Inject::Checker::Player::invehiclenew())
					{
						uintptr_t CurrentVehicle = *(uintptr_t*)(Inject::LocalPlayer + 0x0D30);
						uintptr_t CurrentVehicleInfo = *(uintptr_t*)(CurrentVehicle + 0x20);
						*(float*)(CurrentVehicleInfo + 0x38) = distance;
					}
				}
			}

			void SetHealth(float health)
			{
				if (Inject::Checker::Player::Valid()) {
					if (Inject::Checker::Player::invehiclenew())
					{
						uintptr_t CurrentVehicle = *(uintptr_t*)(Inject::LocalPlayer + 0x0D30);
						*(float*)(CurrentVehicle + 0x0280) = health;
					}
				}
			}

			void SetEngineHealth(float health)
			{
				if (Inject::Checker::Player::Valid()) {
					if (Inject::Checker::Player::invehiclenew())
					{
						uintptr_t CurrentVehicle = *(uintptr_t*)(Inject::LocalPlayer + 0x0D30);
						*(float*)(CurrentVehicle + 0x0908) = health;
					}
				}
			}

			void SetCollisionMultiplayer(float value)
			{
				if (Inject::Checker::Player::Valid()) {
					if (Inject::Checker::Player::invehiclenew())
					{
						uintptr_t CurrentVehicle = *(uintptr_t*)(Inject::LocalPlayer + 0x0D30);
						uintptr_t CurrentVehicleHandling = *(uintptr_t*)(CurrentVehicle + 0x938);
						*(float*)(CurrentVehicleHandling + 0x00F0) = value;
					}
				}
			}

			void SetWeaponDamageMultiplayer(float value)
			{
				if (Inject::Checker::Player::Valid()) {
					if (Inject::Checker::Player::invehiclenew())
					{
						uintptr_t CurrentVehicle = *(uintptr_t*)(Inject::LocalPlayer + 0x0D30);
						uintptr_t CurrentVehicleHandling = *(uintptr_t*)(CurrentVehicle + 0x938);
						*(float*)(CurrentVehicleHandling + 0x00F4) = value;
					}
				}
			}

			int GetModelHash()
			{
				if (Inject::Checker::Player::Valid()) {
					if (Inject::Checker::Player::invehiclenew())
					{
						uintptr_t CurrentVehicle = *(uintptr_t*)(Inject::LocalPlayer + 0x0D30);
						uintptr_t CurrentVehicleInfo = *(uintptr_t*)(CurrentVehicle + 0x20);
						return *(int*)(CurrentVehicle + 0x18);
					}
				}
			}

			std::string GetVehicleName()
			{
				if (Inject::Checker::Player::Valid()) {
					if (Inject::Checker::Player::invehiclenew())
					{
						uintptr_t CurrentVehicle = *(uintptr_t*)(Inject::LocalPlayer + 0x0D30);
						uintptr_t CurrentVehicleInfo = *(uintptr_t*)(CurrentVehicle + 0x20);
						return *(std::string*)(CurrentVehicleInfo + 0x298);
					}
				}
			}
		}

		namespace Weapon
		{
			void Set_Recoil(float recoil)
			{
				if (Inject::Checker::Player::Valid()) {
					uintptr_t CurrentWeaponForRecoil = *(uintptr_t*)(WeaponBase + 0x20);
					*(float*)(CurrentWeaponForRecoil + 0x2F4) = recoil;
				}
			}
			void Set_Spread(float spread)
			{
				if (Inject::Checker::Player::Valid()) {
					uintptr_t CurrentWeaponForSpread = *(uintptr_t*)(WeaponBase + 0x20);
					*(float*)(CurrentWeaponForSpread + 0x74) = spread;
				}
			}
			void Set_ReloadMultipler(float reloadtime)
			{
				if (Inject::Checker::Player::Valid()) {
					uintptr_t CurrentWeaponForReload = *(uintptr_t*)(WeaponBase + 0x20);
					*(float*)(CurrentWeaponForReload + 0x0134) = reloadtime;
				}
			}
			void Set_WeaponRange(float range)
			{
				if (Inject::Checker::Player::Valid()) {
					uintptr_t CurrentWeaponForMaxRange = *(uintptr_t*)(WeaponBase + 0x20);
					*(float*)(CurrentWeaponForMaxRange + 0x028C) = range;
				}
			}
			void Set_WeaponDamage(float damage)
			{
				if (Inject::Checker::Player::Valid()) {
					uintptr_t CurrentWeaponForMaxDamage = *(uintptr_t*)(WeaponBase + 0x20);
					*(float*)(CurrentWeaponForMaxDamage + 0x00BC) = damage;
				}
			}
			void SetMaxAmmo()
			{
				if (Inject::Checker::Player::Valid()) {
					uintptr_t CurrentWeaponForMaxAmmo = *(uintptr_t*)(WeaponBase + 0x20);
					uintptr_t CurrentWeaponForMaxAmmo2 = *(uintptr_t*)(CurrentWeaponForMaxAmmo + 0x0060);
					*(float*)(CurrentWeaponForMaxAmmo2 + 0x18) = 999999;
				}
			}
			char* GetWeaponSzName()
			{
				if (Inject::Checker::Player::Valid()) {
					uintptr_t CurrentWeapon = *(uintptr_t*)(WeaponBase + 0x20);
					return (*reinterpret_cast<char**>((DWORD64)CurrentWeapon + 0x5F0));
				}
			}
		}
	}
}