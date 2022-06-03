#include "Aimbot.h"

namespace Aimbot
{
	float RandomFloat(float min, float max)
	{
		assert(max > min);
		float random = ((float)rand()) / (float)RAND_MAX;
		float range = max - min;
		return (random * range) + min;
	}

	int locked = 0;
	int locktimer = 0;

	DWORD64 addr;
	void AimVec(Vector3 point)
	{
		auto draw_list = ImGui::GetBackgroundDrawList();
		DWORD64 addr = Inject::GetCamera();
		if (Helper::ValidPTR(addr))
		{
			Vector3 CrosshairPos = *(Vector3*)(addr + 0x60);
			float distance = Vector3().Distance(CrosshairPos, point);
			if (locked != 0)
			{
				const ImU32 col = ImGui::ColorConvertFloat4ToU32(ImVec4(0.95f, 0.34f, 0.20f, 0.5f));
				draw_list->AddText(NULL, 16.0f, ImVec2(CrosshairPos.x - 0.05, CrosshairPos.y), col, "L", NULL);
			}

				int smooth = 0;

				smooth = Config::AIMBOT::smooth;

				float threshold = 0.5f / (10 * 20);
				Vector3 Out = Vector3((point.x - CrosshairPos.x) / distance, (point.y - CrosshairPos.y) / distance, (point.z - CrosshairPos.z) / distance);

				if (smooth <= 1)
				{
					*(Vector3*)(addr + 0x40) = Out;  //FPS
					*(Vector3*)(addr + 0x3D0) = Out; //TPS
				}
				else
				{
					//First Person
					{
						Vector3 angles = *(Vector3*)(addr + 0x40);
						if (((Out.x - angles.x) > threshold) || ((angles.x - Out.x) > threshold))
						{
							if (angles.x > Out.x)
								*(float*)(addr + 0x40 + 0x0) -= threshold;
							else if (angles.x < Out.x)
								*(float*)(addr + 0x40 + 0x0) += threshold;
						}
						if (((Out.y - angles.y) > threshold) || ((angles.y - Out.y) > threshold))
						{
							if (angles.y > Out.y)
								*(float*)(addr + 0x40 + 0x4) -= threshold;
							else if (angles.y < Out.y)
								*(float*)(addr + 0x40 + 0x4) += threshold;
						}
						if (((Out.z - angles.z) > threshold) || ((angles.z - Out.z) > threshold))
						{
							if (angles.z > Out.z)
								*(float*)(addr + 0x40 + 0x8) -= threshold;
							else if (angles.z < Out.z)
								*(float*)(addr + 0x40 + 0x8) += threshold;
						}
					}
					//Third Person
					{
						Vector3 angles = *(Vector3*)(addr + 0x3D0);
						if (((Out.x - angles.x) > threshold) || ((angles.x - Out.x) > threshold))
						{
							if (angles.x > Out.x)
								*(float*)(addr + 0x3D0 + 0x0) -= threshold;
							else if (angles.x < Out.x)
								*(float*)(addr + 0x3D0 + 0x0) += threshold;
						}
						if (((Out.y - angles.y) > threshold) || ((angles.y - Out.y) > threshold))
						{
							if (angles.y > Out.y)
								*(float*)(addr + 0x3D0 + 0x4) -= threshold;
							else if (angles.y < Out.y)
								*(float*)(addr + 0x3D0 + 0x4) += threshold;
						}
						if (((Out.z - angles.z) > threshold) || ((angles.z - Out.z) > threshold))
						{
							if (angles.z > Out.z)
								*(float*)(addr + 0x3D0 + 0x8) -= threshold;
							else if (angles.z < Out.z)
								*(float*)(addr + 0x3D0 + 0x8) += threshold;
						}
					}
				}
		}
	}

	void Tick()
	{
		if (!Config::AIMBOT::enable) return;
		if (GetAsyncKeyState(Config::AIMBOT::aimkey_bind) & 0x8000)
		{
			DWORD64 m_CCameraViewAngles = Inject::GetCamera();
			DWORD64 camParams = *(DWORD64*)(m_CCameraViewAngles + 0x10);

			float ScreenCX = ImGui::GetIO().DisplaySize.x / 2;
			float ScreenCY = ImGui::GetIO().DisplaySize.y / 2;

			int closest_id = -1;
			float closest_distance = 5000.0f;
			float closest_fov = 5000.0f;
			ImVec2 closest_screenPos;

			for (int i = 0; i < 299; i++)
			{
				if (ESP::players[i].ped == NULL)
					continue;

				if (ESP::players[i].ped == Inject::LocalPlayer)
					continue;

				if (ESP::players[i].health < 1.0f)
					continue;

				Vector3 myPos;
				DWORD64 addr = Inject::GetCamera();
				if (addr != NULL)
					myPos = *(Vector3*)(addr + 0x60);

				Vector3 pedPos = Vector3(ESP::players[i].position.x, ESP::players[i].position.y, ESP::players[i].position.z);
				if (pedPos.x == 0.0f || pedPos.y == 0.0f || pedPos.z == 0.0f)
					continue;

				float distance = Vector3().Distance(pedPos, myPos);

				if (distance < 2.0f)
					continue;

				Vector3 originPos = Vector3(ESP::players[i].position.x, ESP::players[i].position.y, ESP::players[i].position.z);
				ImVec2 screenPos = Inject::WorldToScreen(originPos);
				int fov = 100;
				fov = Config::AIMBOT::fovsize;
				if (screenPos.x > 0)
				{
					float AngleDifferences = sqrt(pow((screenPos.x - ScreenCX), 2) + pow((screenPos.y - ScreenCY), 2));
					if (AngleDifferences > 0.01f && AngleDifferences < fov && distance <= closest_distance)
					{
						closest_id = i;
						closest_distance = distance;
						closest_fov = AngleDifferences;
						closest_screenPos = screenPos;
					}
				}
			}
			if (closest_fov >= 1000.0f) return;
			if (closest_id == -1) return;

			if (ESP::players[closest_id].position.x == 0.0f)
				return;

			if (locked != 0) {
				if (ESP::players[locked].health < 1) {
					locked = closest_id;
				}
			}
			else
			{
				locked = closest_id;
			}

			if (locked != 0) {

			}

			if (Config::AIMBOT::boneid == 0) {
				if (closest_screenPos.x > 0)
				{
					const auto head = Inject::GetBonePosW2S2(ESP::players[closest_id].ped, 0x796E);
					AimVec(head);
				}
			}
			else if (Config::AIMBOT::boneid == 1)
			{
				if (closest_screenPos.x > 0)
				{
					const auto neck = Inject::GetBonePosW2S2(ESP::players[closest_id].ped, 0x9995);
					AimVec(neck);
				}
			}
			else if (Config::AIMBOT::boneid == 2)
			{
				if (closest_screenPos.x > 0)
				{
					const auto pelvis = Inject::GetBonePosW2S2(ESP::players[closest_id].ped, 0x2E28);
					AimVec(pelvis);
				}
			}
		}
		else
		{
			if (locktimer >= 3) {
				locked = 0;
				locktimer = 0;
			}
			else
			{
				locktimer++;
			}
		}
	}
}