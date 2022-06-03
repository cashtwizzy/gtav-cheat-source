#include "includes.h"
#include <d3dx9math.h>
#include <string>
#include <fstream>

namespace Inject
{
	extern D3DXVECTOR3 MainPosition;

	extern DWORD64 World;
	extern DWORD64 LocalPlayer;
	extern DWORD64 Camera;
	extern DWORD64 ReplayInterface;
	extern DWORD64 WeaponBase;
	extern DWORD64 BonePositionAddress;
	extern DWORD64 BlipPointer;

	extern std::string get_name_from_index(WORD i);

	extern void ToggleNametags(bool value);
	extern ImVec2 WorldToScreen(Vector3 WorldPos);
	extern ImVec2 WorldToScreen2(D3DXVECTOR3 WorldPos);

	extern D3DXVECTOR2 WorldToScreenOther(D3DXVECTOR3 WorldPos);
	extern D3DXVECTOR2 WorldToScreen2Other(D3DXVECTOR3 WorldPos);

	extern ImVec2 GetBonePosW2S(const int64_t cPed, const int32_t wMask);
	extern Vector3 GetBonePosW2S2(const int64_t cPed, const int32_t wMask);

	extern void InjectGame();
	extern DWORD64 GetCameraViewAngles();
	extern DWORD64 GetGameCameraViewAngles();
	extern DWORD64 GetCamera();
	extern DWORD64 GetReplayInterface();

	namespace Checker
	{
		namespace Player
		{
			extern bool Valid();
			extern bool In_Vehicle();
			extern int32_t invehiclenew();
		}
		namespace Vehicle
		{
			extern bool Valid();
		}
	}

	namespace InjectorWrtiter
	{
		namespace Player
		{
			extern void Set_Health(float health);
			extern float Get_Health();
			extern void Set_Armor(float armor);
			extern float Get_Armor();
			extern Vector3 GetPosition();
			extern void Set_Position();
			extern void SetPlayerPositionToCoord(D3DXVECTOR3 pos);
			extern void SetVehiclePositionToCoord(D3DXVECTOR3 pos);
			extern void Set_Godmode(uint8_t value);
			extern void SetSuperFrameflag();
			extern void TeleportToWayPoint();
			extern void Set_Seatbelt(bool value);
			extern void Set_Ragdoll(bool value);
			extern void Set_RunSpeed(float value);
			extern void Set_SwimSpeed(float value);
			extern void Set_Wantedlevel(uint32_t value);
			extern void Set_MeeleDamageMulti(float value);
			extern void SetPlayerNoCollision();
			extern void SetFOVZoom(float range);
			extern void SetNoClip();
		}

		namespace Weapon
		{
			extern void Set_Recoil(float recoil);
			extern void Set_Spread(float spread);
			extern void Set_ReloadMultipler(float reloadtime);
			extern void Set_WeaponRange(float range);
			extern void Set_WeaponDamage(float damage);
			extern void SetMaxAmmo();
			extern char* GetWeaponSzName();
		}

		namespace Vehicle
		{
			extern int GetModelHash();
			extern std::string GetVehicleName();
			extern void Set_SpeedMulti(float multi);
			extern void Set_CamDistance(float distance);
			extern void SetHealth(float health);
			extern void SetEngineHealth(float health);
			extern void SetCollisionMultiplayer(float value);
			extern void SetWeaponDamageMultiplayer(float value);
			extern void SetWeaponDamageMultiplayer(float value);
		}
	}
}