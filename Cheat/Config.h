#include "includes.h"

namespace Config
{
	extern DWORD64 GTA5;
	extern bool MenuToggle;
	extern int CurrentTab;

	extern int esp_subtab;
	extern int self_subtab;
	extern int weapon_subtab;
	extern int vehicle_subtab;

	namespace PLAYER
	{
		extern bool player_healkey_on;
		extern float player_healkey_heal_amount;
		extern int player_healkey_bind;
		extern bool player_armorkey_on;
		extern float player_healkey_armor_amount;
		extern int player_armorkey_bind;
		extern bool player_autoheal;
		extern bool player_semi_god;
		extern bool player_no_ragdoll;
		extern bool player_seatbelt;
		extern bool player_no_collision;
		extern bool player_ninjatp;
		extern int player_ninjatp_set_bind;
		extern int player_ninjatp_tp_bind;
		extern bool player_noclip;
		extern int player_noclip_bind;
		extern bool tp_wp;
		extern int tp_wp_bind;
		extern bool tp_crosshair;
		extern int tp_crosshair_bind;
		extern bool player_superpuch;
		extern bool player_superjump;
		extern bool player_fire_ammo;
		extern bool player_explosive_ammo;
		extern bool player_explosive_fist;
		extern bool player_superpunch;

		extern bool player_runspeed;
		extern bool player_swimspeed;

		extern bool fovzoom;
		extern float FovZoom;
	}

	namespace VEHICLE
	{
		extern bool vehicle_enabled;
		extern bool vehicle_noclip;
		extern bool vehicle_unlockall;
		extern bool vehicle_allvehiclefly;
		extern float vehicle_speed;
		extern bool vehicle_downshift;
		extern float vehicle_gravity;
		extern int vehicle_deformation;
		extern int vehicle_brakeforce;
		extern int vehicle_colision;
		extern int vehicle_customhealth;
		extern int vehicle_health;
		extern int vehicle_unlock_all;
		extern bool vehicle_speedboost;
		extern float vehicle_speed_amount;
		extern int vehicle_speed_bind;

		extern bool vehicle_camdist;
		extern float vehicle_camdistance;

		extern bool destroyallvehicles;

	}

	namespace WEAPON
	{
		extern bool weapon_no_spread;
		extern bool weapon_no_recoil;
		extern bool weapon_no_reload;
		extern bool weapon_max_damage;
		extern bool weapon_unlimited_ammo;
		extern bool weapon_range;

		extern int givenormalweapon;
		extern int givespecialweapon;
		extern int giveammo;
	}

	namespace ESP
	{
		extern bool player_enable;
		extern bool player_box;
		extern int boxtype;
		extern bool player_skeleton;
		extern bool player_health;
		extern int player_health_type;
		extern bool player_weapon;
		extern bool player_distance;
		extern bool player_drawline;
		extern bool player_admin;
		extern bool player_ignoredeath;
		extern bool player_rainbowesp;

		extern bool player_nametags;
		extern bool player_usernames;

		extern int player_visual_distance;

		//colors
		extern float BoxColor[3];
		extern float SkeletColor[3];

		extern float HpColor[3];
		extern float ArmorColor[3];

		extern float player_rainbowespred;
		extern float player_rainbowespgreen;
		extern float player_rainbowespblue;

		extern bool vehicle_enable;
		extern bool vehicle_distance;

		extern bool object_enable;
		extern bool customsearchobject;
		extern bool object_distance;

		extern int crosshairstyle;
		extern float crosshairwidth;
		extern float crosshairgap;
		extern float crosshairthickness;

		extern float crosshair_color[3];

		extern bool radar;
		extern bool radar_include_player;
		extern bool radar_include_vehicle;
	}

	namespace AIMBOT
	{
		extern bool enable;
		extern int aimkey_bind;
		extern int smooth;
		extern int boneid;
		extern bool fov;
		extern int fovsize;
	}

	namespace MISC
	{
		extern bool neverwanted;
		extern bool triggerbot;

		extern int weapontogive;
		extern int weaponammotogive;
	}
}