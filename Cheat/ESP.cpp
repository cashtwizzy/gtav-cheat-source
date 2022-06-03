#include "ESP.h"

namespace ESP
{
	Players players[300];
	Vehicles vehicles[120];

	void DrawBoneLine(ImVec2 start, ImVec2 stop)
	{
		auto draw_list = ImGui::GetBackgroundDrawList();
		draw_list->AddLine(start, stop, ImColor(Config::ESP::SkeletColor[0], Config::ESP::SkeletColor[1], Config::ESP::SkeletColor[2], 255.0f));
	}

	int DistanceInt(const Vector3& point1, const Vector3& point2)
	{
		float distance = sqrt((point1.x - point2.x) * (point1.x - point2.x) +
			(point1.y - point2.y) * (point1.y - point2.y) +
			(point1.z - point2.z) * (point1.z - point2.z));
		return distance;
	}

	void Draw_Skeleton(DWORD64 cPed)
	{
		const auto rToe = Inject::GetBonePosW2S(cPed, 0x512D);
		const auto rFoot = Inject::GetBonePosW2S(cPed, 0xCC4D);
		const auto rCalf = Inject::GetBonePosW2S(cPed, 0x9000);
		const auto rThigh = Inject::GetBonePosW2S(cPed, 0xCA72);

		const auto lToe = Inject::GetBonePosW2S(cPed, 0x083C);
		const auto lFoot = Inject::GetBonePosW2S(cPed, 0x3779);
		const auto lCalf = Inject::GetBonePosW2S(cPed, 0xF9BB);
		const auto lThigh = Inject::GetBonePosW2S(cPed, 0xE39F);

		const auto pelvis = Inject::GetBonePosW2S(cPed, 0x2E28);
		const auto spineRoot = Inject::GetBonePosW2S(cPed, 0xE0FD);
		const auto spine0 = Inject::GetBonePosW2S(cPed, 0x5C01);
		const auto spine1 = Inject::GetBonePosW2S(cPed, 0x60F0);
		const auto spine2 = Inject::GetBonePosW2S(cPed, 0x60F1);
		const auto spine3 = Inject::GetBonePosW2S(cPed, 0x60F2);

		const auto lClavicle = Inject::GetBonePosW2S(cPed, 0xFCD9);
		const auto lUpperArm = Inject::GetBonePosW2S(cPed, 0xB1C5);
		const auto lForearm = Inject::GetBonePosW2S(cPed, 0xEEEB);
		const auto lHand = Inject::GetBonePosW2S(cPed, 0x49D9);

		const auto rClavicle = Inject::GetBonePosW2S(cPed, 0x29D2);
		const auto rUpperArm = Inject::GetBonePosW2S(cPed, 0x9D4D);
		const auto rForearm = Inject::GetBonePosW2S(cPed, 0x6E5C);
		const auto rHand = Inject::GetBonePosW2S(cPed, 0xDEAD);

		const auto neck = Inject::GetBonePosW2S(cPed, 0x9995);
		const auto head = Inject::GetBonePosW2S(cPed, 0x796E);

		//ImGui::GetOverlayDrawList()->AddCircle(ImVec2(head.x, head.y - 15), 22.5, ImColor(0.0f, 255.0f, 0.0f, 255.0f), 30);

		DrawBoneLine(rToe, rFoot);
		DrawBoneLine(rFoot, rCalf);
		DrawBoneLine(rCalf, rThigh);
		DrawBoneLine(rThigh, pelvis);

		DrawBoneLine(lToe, lFoot);
		DrawBoneLine(lFoot, lCalf);
		DrawBoneLine(lCalf, lThigh);
		DrawBoneLine(lThigh, pelvis);

		DrawBoneLine(pelvis, spineRoot);
		DrawBoneLine(spineRoot, spine0);
		DrawBoneLine(spine0, spine1);
		DrawBoneLine(spine1, spine2);
		DrawBoneLine(spine2, spine3);
		DrawBoneLine(spine3, neck);
		DrawBoneLine(neck, head);

		DrawBoneLine(lClavicle, lUpperArm);
		DrawBoneLine(lUpperArm, lForearm);
		DrawBoneLine(lForearm, lHand);

		DrawBoneLine(rClavicle, rUpperArm);
		DrawBoneLine(rUpperArm, rForearm);
		DrawBoneLine(rForearm, rHand);

		DrawBoneLine(rClavicle, neck);
		DrawBoneLine(lClavicle, neck);
	}

	void DrawCornerBox(int x, int y, int w, int h, int thickness, float coverage)
	{
		auto draw_list = ImGui::GetBackgroundDrawList();

		// links oben
		draw_list->AddLine(ImVec2(x, y), ImVec2(x + (w * coverage), y), ImColor(Config::ESP::BoxColor[0], Config::ESP::BoxColor[1], Config::ESP::BoxColor[2], 255.0f), thickness);
		draw_list->AddLine(ImVec2(x, y), ImVec2(x, y + (h * coverage)), ImColor(Config::ESP::BoxColor[0], Config::ESP::BoxColor[1], Config::ESP::BoxColor[2], 255.0f), thickness);

		// links unten
		draw_list->AddLine(ImVec2(x, y + h), ImVec2(x + (w * coverage), y + h), ImColor(Config::ESP::BoxColor[0], Config::ESP::BoxColor[1], Config::ESP::BoxColor[2], 255.0f), thickness);
		draw_list->AddLine(ImVec2(x, y + h), ImVec2(x, (y + h) - (h * coverage)), ImColor(Config::ESP::BoxColor[0], Config::ESP::BoxColor[1], Config::ESP::BoxColor[2], 255.0f), thickness);

		// rechts oben
		draw_list->AddLine(ImVec2(x + w, y), ImVec2((x + w) - (w * coverage), y), ImColor(Config::ESP::BoxColor[0], Config::ESP::BoxColor[1], Config::ESP::BoxColor[2], 255.0f), thickness);
		draw_list->AddLine(ImVec2(x + w, y), ImVec2(x + w, y + (h * coverage)), ImColor(Config::ESP::BoxColor[0], Config::ESP::BoxColor[1], Config::ESP::BoxColor[2], 255.0f), thickness);

		// rechts unten
		draw_list->AddLine(ImVec2(x + w, y + h), ImVec2((x + w) - (w * coverage), y + h), ImColor(Config::ESP::BoxColor[0], Config::ESP::BoxColor[1], Config::ESP::BoxColor[2], 255.0f), thickness);
		draw_list->AddLine(ImVec2(x + w, y + h), ImVec2(x + w, (y + h) - (h * coverage)), ImColor(Config::ESP::BoxColor[0], Config::ESP::BoxColor[1], Config::ESP::BoxColor[2], 255.0f), thickness);
	}

	void Tick() 
	{
		if (Config::ESP::player_nametags)
		{
			Inject::ToggleNametags(true);
		}
		auto draw_list = ImGui::GetBackgroundDrawList();
		if (Config::ESP::player_enable)
		{
			DWORD64 list_interface = NULL;
			DWORD64 list = NULL;
			int list_max_ptr = 0;
			DWORD64 replayInterface = Inject::GetReplayInterface();
			if (Helper::ValidPTR(replayInterface))
			{
				list_interface = *(DWORD64*)(replayInterface + 0x18);
				list = *(DWORD64*)(list_interface + 0x100);
				list_max_ptr = *(int*)(list_interface + 0x108);
			}
			for (int i = 0; i < 299; i++)
			{
				if (i < list_max_ptr)
				{
					DWORD64 ped = *(DWORD64*)(list + i * 0x10);
					if (Helper::ValidPTR(ped))
					{
						if (ped == Inject::LocalPlayer)
							continue;

						Vector3 localpos = *(Vector3*)(Inject::LocalPlayer + 0x90);
						Vector3 pedPos = *(Vector3*)(ped + 0x90);

						float health = *(float*)(ped + 0x280);
						if (health > 200.0f)    health = 200.0f;
						else if (health < 0.0f) health = 0.0f;

						float armor = *(float*)(ped + 0x1530);
						if (armor > 100.0f)    armor = 100.0f;
						else if (armor < 0.0f) armor = 0.0f;

						if (pedPos.x == 0.0f || pedPos.y == 0.0f || pedPos.z == 0.0f)
							continue;

						players[i].ped = ped;
						players[i].position = ImVec4(pedPos.x, pedPos.y, pedPos.z, 0.0f);
						players[i].health = health - 100.0f;
						players[i].armor = armor;

						Vector3 originPos = Vector3(pedPos.x, pedPos.y, pedPos.z - 1.0f);
						Vector3 headPos = Vector3(pedPos.x, pedPos.y, pedPos.z + 0.9f);
						ImVec2 screenPos = Inject::WorldToScreen(originPos);
						ImVec2 screenPosHead = Inject::WorldToScreen(headPos);

						float distance = DistanceInt(pedPos, localpos);

						if (screenPos.x > 0 && screenPosHead.x > 0)
						{
							float h = screenPosHead.y - screenPos.y;
							float w = (screenPos.y - screenPosHead.y) / 3.5f;

							if (health > 0)
							{
								if (Config::ESP::player_box)
								{
									if (Config::ESP::boxtype == 0)
									{
										draw_list->AddLine(ImVec2(screenPos.x - w, screenPosHead.y), ImVec2(screenPos.x + w, screenPosHead.y), ImColor(Config::ESP::BoxColor[0], Config::ESP::BoxColor[1], Config::ESP::BoxColor[2], 255.0f), 1.25f); // Oben
										draw_list->AddLine(ImVec2(screenPos.x - w, screenPos.y), ImVec2(screenPos.x - w, screenPosHead.y), ImColor(Config::ESP::BoxColor[0], Config::ESP::BoxColor[1], Config::ESP::BoxColor[2], 255.0f), 1.25f); // Links
										draw_list->AddLine(ImVec2(screenPos.x + w, screenPos.y), ImVec2(screenPos.x + w, screenPosHead.y), ImColor(Config::ESP::BoxColor[0], Config::ESP::BoxColor[1], Config::ESP::BoxColor[2], 255.0f), 1.25f); // Rechts
										draw_list->AddLine(ImVec2(screenPos.x - w, screenPos.y), ImVec2(screenPos.x + w, screenPos.y), ImColor(Config::ESP::BoxColor[0], Config::ESP::BoxColor[1], Config::ESP::BoxColor[2], 255.0f), 1.25f); // Unten
									}
									else
									{
										DrawCornerBox(
											screenPos.x - (((screenPos.y - screenPosHead.y) * 0.5f) / 2),
											screenPosHead.y,
											(screenPos.y - screenPosHead.y) * 0.5f,
											screenPos.y - screenPosHead.y,
											1.25f,
											0.2f / 2
										);
									}
								}
								if (Config::ESP::player_health)
								{
									float oneHealth2 = h / 100;
									float newhealth2 = health / 2;
									draw_list->AddLine(ImVec2(screenPos.x - w - 6.0f, screenPos.y), ImVec2(screenPos.x - w - 6.0f, screenPosHead.y), ImColor(0, 0, 0, 255), 2.0f);
									draw_list->AddLine(ImVec2(screenPos.x - w - 6.0f, screenPos.y), ImVec2(screenPos.x - w - 6.0f, screenPosHead.y - h + oneHealth2 * newhealth2), ImColor(Config::ESP::HpColor[0], Config::ESP::HpColor[1], Config::ESP::HpColor[2], 255.0f), 2.0f);

									if (armor > 0)
									{
										draw_list->AddLine(ImVec2(screenPos.x - w - 9.0f, screenPos.y), ImVec2(screenPos.x - w - 9.0f, screenPosHead.y), ImColor(0, 0, 0, 255), 2.0f);
										draw_list->AddLine(ImVec2(screenPos.x - w - 9.0f, screenPos.y), ImVec2(screenPos.x - w - 9.0f, screenPosHead.y - h + oneHealth2 * armor), ImColor(Config::ESP::ArmorColor[0], Config::ESP::ArmorColor[1], Config::ESP::ArmorColor[2], 255.0f), 2.0f);
									}
								}
								if (Config::ESP::player_skeleton)
								{
									Draw_Skeleton(ped);
								}
								float font_scale = 17.5f;
								font_scale = ((font_scale * 2.5) - distance);
								if (font_scale >= 17.5f)
								{
									font_scale = 17.5f;
								}
								if (font_scale <= 13.5f)
								{
									font_scale = 13.5f;
								}
								uintptr_t WpBase = *(uintptr_t*)(ped + 0x10D8);
								uintptr_t CurrentWeapon = *(uintptr_t*)(WpBase + 0x20);
								char* weaponnme = (*reinterpret_cast<char**>((DWORD64)CurrentWeapon + 0x5F0));

								if (Config::ESP::player_weapon && Config::ESP::player_distance)
								{
									float neww = w / 2;
									std::string weaponhashtoname = weaponnme;
									std::string distancestring = weaponhashtoname + " - [" + std::to_string((int)round(distance)) + "m]";
									draw_list->AddText(NULL, font_scale, ImVec2(screenPos.x - neww, screenPos.y), ImColor(255.0f, 255.0f, 255.0f, 255.0f), distancestring.c_str());
								}
								else if (Config::ESP::player_weapon)
								{
									std::string weaponhashtoname = weaponnme;
									float neww = w / 2;
									draw_list->AddText(NULL, font_scale, ImVec2(screenPos.x - neww, screenPos.y), ImColor(255.0f, 255.0f, 255.0f, 255.0f), weaponhashtoname.c_str());
								}
								else if (Config::ESP::player_distance)
								{
									std::string distancestring = "[" + std::to_string((int)round(distance)) + "m]";
									float neww = w / 2;
									draw_list->AddText(NULL, font_scale, ImVec2(screenPos.x - neww, screenPos.y), ImColor(255.0f, 255.0f, 255.0f, 255.0f), distancestring.c_str());
								}
								if (Config::ESP::player_drawline)
								{
									Vector3 localoriginPos = Vector3(localpos.x, localpos.y, localpos.z);
									ImVec2 localscreenPos = Inject::WorldToScreen(localoriginPos);
									draw_list->AddLine(ImVec2(localscreenPos.x, localscreenPos.y), ImVec2(screenPosHead.x, screenPosHead.y), ImColor(255, 0, 0, 255), 1.0f);
								}
								if (Config::ESP::player_usernames)
								{
									float neww = w / 2;
									std::string player_name = Inject::get_name_from_index(i);
									draw_list->AddText(NULL, font_scale, ImVec2(screenPos.x - neww, screenPos.y), ImColor(255.0f, 255.0f, 255.0f, 255.0f), player_name.c_str());
								}
							}
						}
					}
				}
			}
		}
			DWORD64 list_interface_vehicle = NULL;
			DWORD64 list_vehicle = NULL;
			int list_max_ptr_vehicle = 0;
			DWORD64 replayInterface = Inject::GetReplayInterface();
			if (Helper::ValidPTR(replayInterface))
			{
				list_interface_vehicle = *(DWORD64*)(replayInterface + 0x10);
				list_vehicle = *(DWORD64*)(list_interface_vehicle + 0x180);
				list_max_ptr_vehicle = *(int*)(list_interface_vehicle + 0x108);
			}

			for (int i = 0; i < 119; i++)
			{
				DWORD64 veh = *(DWORD64*)(list_vehicle + i * 0x10);
				if (Helper::ValidPTR(veh))
				{
					Vector3 localpos = *(Vector3*)(Inject::LocalPlayer + 0x90);
					Vector3 vehPos = *(Vector3*)(veh + 0x90);

					float health = *(float*)(veh + 0x908);
					int distance = DistanceInt(vehPos, localpos);

					if (distance <= Config::ESP::player_visual_distance)
					{
						if (vehPos.x == 0.0f || vehPos.y == 0.0f || vehPos.z == 0.0f)
							continue;

						vehicles[i].vehicle = veh;
						vehicles[i].position = ImVec4(vehPos.x, vehPos.y, vehPos.z, 0.0f);
						vehicles[i].health = health / 10;
						vehicles[i].distance = distance;

						Vector3 originPos = Vector3(vehPos.x, vehPos.y, vehPos.z - 1.0f);
						Vector3 headPos = Vector3(vehPos.x, vehPos.y, vehPos.z + 0.9f);
						ImVec2 screenPos = Inject::WorldToScreen(originPos);
						ImVec2 screenPosHead = Inject::WorldToScreen(headPos);

						if (screenPos.x > 0 && screenPosHead.x > 0)
						{
							float h = screenPosHead.y - screenPos.y;
							float w = (screenPos.y - screenPosHead.y) / 3.5f;

							//Vehicle ESP
							if (Config::ESP::vehicle_enable)
							{
								float font_scale = 17.5f;
								font_scale = ((font_scale * 2.5) - distance);
								if (font_scale >= 17.5f)
								{
									font_scale = 17.5f;
								}
								if (font_scale <= 13.5f)
								{
									font_scale = 13.5f;
								}
								float vhealth = *(float*)(veh + 0x280);
								std::string healthstring = std::to_string((int)round(vhealth)) + " HP";
								float neww = w / 2;
								draw_list->AddText(NULL, font_scale, ImVec2(screenPos.x - neww, screenPos.y - 12.5f), ImColor(255.0f, 255.0f, 255.0f, 255.0f), healthstring.c_str());
								if (Config::ESP::vehicle_distance)
								{
									std::string distancestring = "[" + std::to_string((int)round(distance)) + "m]";
									float neww = w / 2;
									draw_list->AddText(NULL, font_scale, ImVec2(screenPos.x - neww, screenPos.y), ImColor(255.0f, 255.0f, 255.0f, 255.0f), distancestring.c_str());
								}
							}

							//Features
							if (Config::VEHICLE::vehicle_allvehiclefly)
							{
								*(float*)(veh + 0x0C5C) = -15.f;
							}
							if (Config::VEHICLE::vehicle_unlockall)
							{
								*(BYTE*)(veh + 0x1390) = -2.f;
							}
							if (Config::VEHICLE::destroyallvehicles)
							{
								*(float*)(veh + 0x280) = -5000.f;
								*(float*)(veh + 0x0908) = -5000.f;
							}
						}
					}
				}
			}
		}
}