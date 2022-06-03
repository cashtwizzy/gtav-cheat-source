#include "Config.h"

namespace Config
{
	DWORD64 GTA5;
	bool MenuToggle = false;
	int CurrentTab = 1;

	int esp_subtab = 1;
	int self_subtab = 1;
	int weapon_subtab = 1;
	int vehicle_subtab = 1;

	namespace PLAYER
	{
		bool player_healkey_on = false;
		float player_healkey_heal_amount = 100.0f;
		int player_healkey_bind = 78;
		bool player_armorkey_on = false;
		float player_healkey_armor_amount = 100.0f;
		int player_armorkey_bind = 78;
		bool player_autoheal = false;
		bool player_semi_god = false;
		bool player_no_ragdoll = false;
		bool player_seatbelt = false;
		bool player_no_collision = false;
		bool player_ninjatp = false;
		int player_ninjatp_tp_bind = 6;
		bool player_noclip = false;
		int player_noclip_bind = 5;
		bool tp_wp = false;
		int tp_wp_bind = 74;
		bool tp_crosshair = false;
		int tp_crosshair_bind = 75;
		bool player_superpuch = false;
		bool player_superjump = false;
		bool player_fire_ammo = false;
		bool player_explosive_ammo = false;
		bool player_explosive_fist = false;
		bool player_superpunch = false;

		bool player_runspeed = false;
		bool player_swimspeed = false;

		bool fovzoom = false;
		float FovZoom = 90;
	}

	namespace VEHICLE
	{
		bool vehicle_enabled = false;
		bool vehicle_noclip = false;
		bool vehicle_unlockall = false;
		bool vehicle_allvehiclefly = false;
		float vehicle_speed = 9.800000191;
		bool vehicle_downshift = false;
		float vehicle_gravity = 1.1;
		int vehicle_deformation = 1;
		int vehicle_brakeforce = 1;
		int vehicle_colision = 1;
		int vehicle_customhealth = 0;
		int vehicle_health = 1000;
		int vehicle_unlock_all = 0;
		bool vehicle_speedboost = false;
		float vehicle_speed_amount = 100;
		int vehicle_speed_bind = 107;

		bool vehicle_camdist = false;
		float vehicle_camdistance = 0.5f;

		bool destroyallvehicles = false;
	}

	namespace WEAPON
	{
		bool weapon_no_spread = false;
		bool weapon_no_recoil = false;
		bool weapon_no_reload = false;
		bool weapon_max_damage = false;
		bool weapon_unlimited_ammo = false;
		bool weapon_range = false;

		int givenormalweapon = 0;
		int givespecialweapon = 0;
		int giveammo = 0;
	}

	namespace ESP
	{
		bool player_enable = false;
		bool player_box = false;
		int boxtype = 0;
		bool player_skeleton = false;
		bool player_health = false;
		int player_health_type = 0;
		bool player_weapon = false;
		bool player_distance = false;
		bool player_drawline = false;
		bool player_admin = false;
		bool player_ignoredeath = false;
		bool player_rainbowesp = false;

		bool player_nametags = false;
		bool player_usernames = false;

		int player_visual_distance = 150;

		//colors
		float BoxColor[3] = { 1.0f, 0.0f, 0.0f };
		float SkeletColor[3] = { 1.0f, 0.0f, 0.0f };

		float HpColor[3] = { 0.0f, 1.0f, 0.0f };
		float ArmorColor[3] = { 0.0f, 0.0f, 1.0f };

		float player_rainbowespred = 255;
		float player_rainbowespgreen = 255;
		float player_rainbowespblue = 255;

		bool vehicle_enable = false;
		bool vehicle_distance = false;

		bool object_enable = false;
		bool customsearchobject = false;
		bool object_distance = false;

		int crosshairstyle = 0;
		float crosshairwidth = 7.0f;
		float crosshairgap = 7.0f;
		float crosshairthickness = 7.0f;

		float crosshair_color[3] = { 1.0f, 0.0f, 1.0f };

		bool radar = false;
		bool radar_include_player = true;
		bool radar_include_vehicle = false;
	}

	namespace AIMBOT
	{
		bool enable = false;
		int aimkey_bind = 2;
		int smooth = 0;
		int boneid = 1;
		bool fov = false;
		int fovsize = 60;
	}

	namespace MISC
	{
		bool neverwanted = false;
		bool triggerbot = false;

		int weapontogive = 0;
		int weaponammotogive = 0;
	}
}