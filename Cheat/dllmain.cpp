#include "includes.h"
////https://github.com/cashtwizzy
HWND hWnd = NULL;
Present oPresent = NULL;
ID3D11Device* pDevice = NULL;
ID3D11DeviceContext* pContext = NULL;
ID3D11RenderTargetView* pRenderTargetView;
WNDPROC oWndProc;

ImFont* g_pDefaultFont;
ImFont* g_pSecondFont;

int ScreenX = GetSystemMetrics(SM_CXSCREEN);
int ScreenY = GetSystemMetrics(SM_CYSCREEN);

void GetLoadedFonts() {

	// menu font
	ImGui::GetIO().Fonts->AddFontFromMemoryCompressedTTF(
		Fonts::Droid_compressed_data,
		Fonts::Droid_compressed_size,
		14.f);

	// esp font
	g_pDefaultFont = ImGui::GetIO().Fonts->AddFontFromMemoryCompressedTTF(
		Fonts::Droid_compressed_data,
		Fonts::Droid_compressed_size,
		18.f);


	// font for watermark; just example
	g_pSecondFont = ImGui::GetIO().Fonts->AddFontFromMemoryCompressedTTF(
		Fonts::Cousine_compressed_data,
		Fonts::Cousine_compressed_size,
		18.f);
}

extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

LRESULT __stdcall WndProc(const HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	if (true && ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam))
	{
		return true;
	}
	return CallWindowProc(oWndProc, hWnd, uMsg, wParam, lParam);
}

bool ImGuiInit = false;
bool menu = false;

int getFPS()
{
	return ImGui::GetIO().Framerate;
};

HRESULT hkPresent(IDXGISwapChain* pSwapchain, UINT SyncInterval, UINT Flags) {
	if (!ImGuiInit) {
		if (SUCCEEDED(pSwapchain->GetDevice(__uuidof(ID3D11Device), (void**)&pDevice))) {
			pDevice->GetImmediateContext(&pContext);
			DXGI_SWAP_CHAIN_DESC sd;
			pSwapchain->GetDesc(&sd);
			hWnd = sd.OutputWindow;
			ID3D11Texture2D* pBackBuffer;
			pSwapchain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);
			pDevice->CreateRenderTargetView(pBackBuffer, NULL, &pRenderTargetView);
			pBackBuffer->Release();
			oWndProc = (WNDPROC)SetWindowLongPtr(hWnd, GWLP_WNDPROC, (LONG_PTR)WndProc);
			ImGui::CreateContext();
			ImGuiIO& io = ImGui::GetIO();
			io.ConfigFlags = ImGuiConfigFlags_NoMouseCursorChange;
			ImGui_ImplWin32_Init(hWnd);
			ImGui_ImplDX11_Init(pDevice, pContext);
			ImGuiInit = true;
			GetLoadedFonts();
			Config::GTA5 = (uintptr_t)GetModuleHandleA("GTA5.exe");
			Inject::InjectGame();
		}
		else return oPresent(pSwapchain, SyncInterval, Flags);
	}

	ImGui::StyleColorsDark();
	ImGui::SetColorEditOptions(ImGuiColorEditFlags_HEX);
	auto& _style = ImGui::GetStyle();
	_style.FrameRounding = 0.f;
	_style.WindowRounding = 0.f;
	_style.ChildRounding = 0.f;
	_style.Colors[ImGuiCol_Button] = ImVec4(0.260f, 0.590f, 0.980f, 0.670f);
	_style.Colors[ImGuiCol_Header] = ImVec4(0.260f, 0.590f, 0.980f, 0.670f);
	_style.Colors[ImGuiCol_HeaderHovered] = ImVec4(0.260f, 0.590f, 0.980f, 1.000f);
	//_style.Colors[ImGuiCol_ButtonHovered] = ImVec4(0.000f, 0.545f, 1.000f, 1.000f);
	//_style.Colors[ImGuiCol_ButtonActive] = ImVec4(0.060f, 0.416f, 0.980f, 1.000f);
	_style.Colors[ImGuiCol_FrameBg] = ImVec4(0.20f, 0.25f, 0.30f, 1.0f);
	_style.Colors[ImGuiCol_WindowBg] = ImVec4(0.000f, 0.009f, 0.120f, 0.940f);
	_style.Colors[ImGuiCol_PopupBg] = ImVec4(0.076f, 0.143f, 0.209f, 1.000f);

	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	ImGui::GetIO().WantCaptureMouse = Config::MenuToggle;
	ImGui::GetIO().WantCaptureKeyboard = Config::MenuToggle;
	ImGui::GetIO().WantTextInput = Config::MenuToggle;
	ImGui::GetIO().MouseDrawCursor = Config::MenuToggle;

	if (GetAsyncKeyState(VK_END) & 1)
	{
		Config::MenuToggle = !Config::MenuToggle;
	}

	if (Config::MenuToggle)
	{
		ImGui::CaptureKeyboardFromApp(true);
	}
	else
	{
		ImGui::CaptureKeyboardFromApp(false);
	}

	ImGui::SetNextWindowSize(ImVec2{ 1000, 400 });
	if (Config::MenuToggle)
	{
		ImGui::SetNextWindowSize(ImVec2{ 1000, 400 });
		ImGui::Begin("GTA5 Cheat", NULL, ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse);
		{
			ImGui::CaptureKeyboardFromApp(Config::MenuToggle);

			guielements::BeginGroupBox("##tab_content", ImVec2(165, 325));
			{
				ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0, 0));
				{
					if (ImGui::Button("AIMBOT", ImVec2(150.0f, 50.0f)))
					{
						Config::CurrentTab = 1;
					}
					if (ImGui::Button("ESP", ImVec2(150.0f, 50.0f)))
					{
						Config::CurrentTab = 2;
					}
					if (ImGui::Button("VEHICLE", ImVec2(150.0f, 50.0f)))
					{
						Config::CurrentTab = 3;
					}
					if (ImGui::Button("MISC", ImVec2(150.0f, 50.0f)))
					{
						Config::CurrentTab = 4;
					}
					if (ImGui::Button("FRIENDLIST", ImVec2(150.0f, 50.0f)))
					{
						Config::CurrentTab = 5;
					}
					if (ImGui::Button("HOTKEYS", ImVec2(150.0f, 50.0f)))
					{
						Config::CurrentTab = 6;
					}
				}
				ImGui::PopStyleVar();
			}
			guielements::EndGroupBox();
			ImGui::SameLine();
			guielements::BeginGroupBox("##body_content", ImVec2(810, 325));
			{
				if (Config::CurrentTab == 1)
				{
					ImGui::Button("AIMBOT", ImVec2(795, 25.0f));
					guielements::BeginGroupBox("##aimbot_content", ImVec2(795, 270));
					{
						ImGui::Checkbox("Enable Aimbot", &Config::AIMBOT::enable);
						ImGui::Checkbox("Draw Field of View", &Config::AIMBOT::fov);
						ImGui::SetCursorPos(ImVec2(450, 5));
						ImGui::PushItemWidth(250);
						ImGui::SliderInt("Field of View", &Config::AIMBOT::fovsize, 5, 500);
						ImGui::PopItemWidth();
						ImGui::SetCursorPos(ImVec2(450, 30));
						ImGui::PushItemWidth(250);
						ImGui::SliderInt("Smooth", &Config::AIMBOT::smooth, 0, 200);
						ImGui::PopItemWidth();
						ImGui::SetCursorPos(ImVec2(450, 55));
						const char* aimbotbodyname[3] = { "Head", "Neck", "Body" };
						ImGui::PushItemWidth(250);
						ImGui::Combo("Aimbot Mode", &Config::AIMBOT::boneid, aimbotbodyname, 3);
						ImGui::PopItemWidth();
					}
					guielements::EndGroupBox();
				} 
				else if (Config::CurrentTab == 2)
				{
					if (ImGui::Button("PLAYER", ImVec2(198.75f, 25.0f)))
					{
						Config::esp_subtab = 1;
					}
					ImGui::SameLine(0, 0.f);
					if (ImGui::Button("OBJECT", ImVec2(198.75f, 25.0f)))
					{
						Config::esp_subtab = 2;
					}
					ImGui::SameLine(0, 0.f);
					if (ImGui::Button("VEHICLE", ImVec2(198.75f, 25.0f)))
					{
						Config::esp_subtab = 3;
					}
					ImGui::SameLine(0, 0.f);
					if (ImGui::Button("CROSSHAIR", ImVec2(198.75f, 25.0f)))
					{
						Config::esp_subtab = 4;
					}
					guielements::BeginGroupBox("##esp_content", ImVec2(795, 270));
					{
						if (Config::esp_subtab == 1)
						{
							ImGui::Checkbox("Show Visuals", &Config::ESP::player_enable);
							ImGui::Checkbox("Draw Box", &Config::ESP::player_box);
							ImGui::Checkbox("Draw Distance", &Config::ESP::player_distance);
							ImGui::Checkbox("Draw Health", &Config::ESP::player_health);
							ImGui::Checkbox("Draw Weapon", &Config::ESP::player_weapon);
							ImGui::Checkbox("Draw Skeleton", &Config::ESP::player_skeleton);
							ImGui::Checkbox("Draw Line", &Config::ESP::player_drawline);
							ImGui::Checkbox("Show Usernames (Only ragemp)", &Config::ESP::player_usernames);
							ImGui::Checkbox("Show Nametags (Only ragemp)", &Config::ESP::player_nametags);
							ImGui::Spacing();
							ImGui::SliderInt("Distance", &Config::ESP::player_visual_distance, 10, 1000);
							ImGui::SetCursorPos(ImVec2(200, 5));
							const char* healthbartype[2] = { "Vertical Bar", "Horizontal Bar" };
							ImGui::PushItemWidth(250);
							ImGui::Combo("Health Style", &Config::ESP::player_health_type, healthbartype, 2);
							ImGui::PopItemWidth();
							ImGui::SetCursorPos(ImVec2(200, 30));
							const char* boxtypes[2] = { "Box", "Corners only" };
							ImGui::PushItemWidth(250);
							ImGui::Combo("Box Style", &Config::ESP::boxtype, boxtypes, 2);
							ImGui::PopItemWidth();
							ImGui::SetCursorPos(ImVec2(600, 5));
							ImGui::PushItemWidth(50);
							ImGui::ColorEdit3("Skeleton", Config::ESP::SkeletColor, ImGuiColorEditFlags_NoInputs);
							ImGui::PopItemWidth();
							ImGui::SetCursorPos(ImVec2(600, 30));
							ImGui::PushItemWidth(50);
							ImGui::ColorEdit3("HP Bar", Config::ESP::HpColor, ImGuiColorEditFlags_NoInputs);
							ImGui::PopItemWidth();
							ImGui::SetCursorPos(ImVec2(600, 55));
							ImGui::PushItemWidth(50);
							ImGui::ColorEdit3("Armor Bar", Config::ESP::ArmorColor, ImGuiColorEditFlags_NoInputs);
							ImGui::PopItemWidth();
							ImGui::SetCursorPos(ImVec2(600, 80));
							ImGui::PushItemWidth(50);
							ImGui::ColorEdit3("Box ESP", Config::ESP::BoxColor, ImGuiColorEditFlags_NoInputs);
							ImGui::PopItemWidth();

						}
						else if (Config::esp_subtab == 2)
						{
							ImGui::Checkbox("Object ESP", &Config::ESP::object_enable);
						}
						else if (Config::esp_subtab == 3)
						{
							ImGui::Checkbox("Vehicle ESP", &Config::ESP::vehicle_enable);
							static float col11[3] = { 1.0f, 0.0f, 0.2f };
							ImGui::ColorEdit3("Vehicle Color", col11, ImGuiColorEditFlags_NoInputs);
							ImGui::Checkbox("Draw Distance", &Config::ESP::vehicle_distance);
						}
						else if (Config::esp_subtab == 4)
						{
							const char* crosshairstyles[4] = { "None", "Empty Circle", "Filled Circle", "Cross" };
							ImGui::PushItemWidth(350);
							ImGui::Combo("Crosshair Style", &Config::ESP::crosshairstyle, crosshairstyles, 4);
							ImGui::SliderFloat("Width", &Config::ESP::crosshairwidth, 0.5f, 20.0f);
							ImGui::SliderFloat("Gap", &Config::ESP::crosshairgap, 0.5f, 20.0f);
							ImGui::SliderFloat("Thickness", &Config::ESP::crosshairthickness, 0.5f, 20.0f);
							ImGui::PopItemWidth();
							ImGui::ColorEdit3("Crosshair Color", Config::ESP::crosshair_color, ImGuiColorEditFlags_NoInputs);
						}
					}
					guielements::EndGroupBox();
				}
				else if (Config::CurrentTab == 3)
				{
					ImGui::Button("VEHICLE", ImVec2(795, 25.0f));
					guielements::BeginGroupBox("##vehicle_content", ImVec2(795, 270));
					{
						ImGui::Checkbox("Enable", &Config::VEHICLE::vehicle_enabled);
						ImGui::Checkbox("Vehicle Speed", &Config::VEHICLE::vehicle_speedboost);
						if (Config::VEHICLE::vehicle_speedboost)
						{
							ImGui::PushItemWidth(250);
							ImGui::SliderFloat("Speed", &Config::VEHICLE::vehicle_speed_amount, 5, 200);
							ImGui::PopItemWidth();
						}
						ImGui::Checkbox("Custom Camera", &Config::VEHICLE::vehicle_camdist);
						if (Config::VEHICLE::vehicle_camdist)
						{
							ImGui::PushItemWidth(250);
							ImGui::SliderFloat("Camera Ditance", &Config::VEHICLE::vehicle_camdistance, -250, 5);
							ImGui::PopItemWidth();
						}
						ImGui::Separator();
						ImGui::Checkbox("Unlock all", &Config::VEHICLE::vehicle_unlockall);
						ImGui::Checkbox("Make all Vehicles Fly", &Config::VEHICLE::vehicle_allvehiclefly);
						ImGui::Checkbox("Destroy all Vehicles", &Config::VEHICLE::destroyallvehicles);
					}
					guielements::EndGroupBox();
				}
				else if (Config::CurrentTab == 4)
				{
					if (ImGui::Button("WEAPON", ImVec2(265, 25.0f)))
					{
						Config::weapon_subtab = 1;
					}
					ImGui::SameLine(0, 0.f);
					if (ImGui::Button("MOVEMENT", ImVec2(265, 25.0f)))
					{
						Config::weapon_subtab = 2;
					}
					ImGui::SameLine(0, 0.f);
					if (ImGui::Button("MISC", ImVec2(265, 25.0f)))
					{
						Config::weapon_subtab = 3;
					}
					guielements::BeginGroupBox("##misc_content", ImVec2(795, 270));
					{
						if (Config::weapon_subtab == 1)
						{
							ImGui::Checkbox("No Spread", &Config::WEAPON::weapon_no_spread);
							ImGui::Checkbox("No Recoil", &Config::WEAPON::weapon_no_recoil);
							ImGui::Checkbox("No Reload", &Config::WEAPON::weapon_no_reload);
							ImGui::Checkbox("Max Damage", &Config::WEAPON::weapon_max_damage);
							ImGui::Checkbox("Max Range", &Config::WEAPON::weapon_range);
							ImGui::Spacing();
							const char* weapontogive[1] = { "Unarmed" };
							ImGui::Combo("Weapon", &Config::MISC::weaponammotogive, weapontogive, 1);
							ImGui::SliderInt("Ammo", &Config::MISC::weaponammotogive, 0, 9999);
						}
						else if (Config::weapon_subtab == 2)
						{
							ImGui::Checkbox("No Clip", &Config::PLAYER::player_noclip);
							ImGui::Checkbox("No Collision", &Config::PLAYER::player_no_collision);
							ImGui::Checkbox("Teleport to Waypoint", &Config::PLAYER::tp_wp);
							ImGui::Checkbox("Custom FOV", &Config::PLAYER::fovzoom);
							ImGui::SetCursorPos(ImVec2(450, 5));
							ImGui::PushItemWidth(200);
							ImGui::SliderFloat("FOV Zoom", &Config::PLAYER::FovZoom, 0, 200);
							ImGui::PopItemWidth();
						}
						else if (Config::weapon_subtab == 3)
						{
							ImGui::Checkbox("Godmode", &Config::PLAYER::player_semi_god);
							ImGui::Checkbox("Autoheal", &Config::PLAYER::player_autoheal);
							ImGui::Checkbox("Healkey", &Config::PLAYER::player_healkey_on);
							ImGui::Checkbox("Armorkey", &Config::PLAYER::player_armorkey_on);
							ImGui::Checkbox("No Ragdoll (Dont use!)", &Config::PLAYER::player_no_ragdoll);
							ImGui::Checkbox("Seatbelt", &Config::PLAYER::player_seatbelt);
							ImGui::Checkbox("Runspeed", &Config::PLAYER::player_runspeed);
							ImGui::Checkbox("Swimspeed", &Config::PLAYER::player_swimspeed);
							ImGui::SetCursorPos(ImVec2(250, 5));
							ImGui::Checkbox("Super Jump", &Config::PLAYER::player_superjump);
							ImGui::SetCursorPos(ImVec2(250, 30));
							ImGui::Checkbox("Super Punch", &Config::PLAYER::player_superpunch);
							ImGui::SetCursorPos(ImVec2(250, 55));
							ImGui::Checkbox("Fire Ammo", &Config::PLAYER::player_fire_ammo);
							ImGui::SetCursorPos(ImVec2(250, 80));
							ImGui::Checkbox("Explosive Ammo", &Config::PLAYER::player_explosive_ammo);
							ImGui::SetCursorPos(ImVec2(250, 105));
							ImGui::Checkbox("Explosive Fist", &Config::PLAYER::player_explosive_fist);
							ImGui::SetCursorPos(ImVec2(250, 130));
							ImGui::Checkbox("Never Wanted", &Config::MISC::neverwanted);
							ImGui::SetCursorPos(ImVec2(450, 5));
							ImGui::PushItemWidth(200);
							ImGui::SliderFloat("Heal Amount", &Config::PLAYER::player_healkey_heal_amount, 0, 200);
							ImGui::PopItemWidth();
							ImGui::SetCursorPos(ImVec2(450, 30));
							ImGui::PushItemWidth(200);
							ImGui::SliderFloat("Armor Amount", &Config::PLAYER::player_healkey_armor_amount, 0, 100);
							ImGui::PopItemWidth();
							ImGui::SetCursorPos(ImVec2(450, 55));
							ImGui::PushItemWidth(200);
							if (ImGui::Button("Give Heal"))
							{
								Inject::InjectorWrtiter::Player::Set_Health(Config::PLAYER::player_healkey_heal_amount);
							}
							ImGui::PopItemWidth();
							ImGui::SetCursorPos(ImVec2(450, 80));
							ImGui::PushItemWidth(200);
							if (ImGui::Button("Give Armor"))
							{
								Inject::InjectorWrtiter::Player::Set_Armor(Config::PLAYER::player_healkey_armor_amount);
							}
							ImGui::PopItemWidth();
						}
					}
					guielements::EndGroupBox();
				}
				else if (Config::CurrentTab == 5)
				{
					ImGui::Button("FRIENDLIST", ImVec2(795, 25.0f));
					guielements::BeginGroupBox("##friendlist_content", ImVec2(795, 270));
					{

					}
					guielements::EndGroupBox();
				}
				else if (Config::CurrentTab == 6)
				{
					ImGui::Button("HOTKEYS", ImVec2(795, 25.0f));
					guielements::BeginGroupBox("##hotkeys_content", ImVec2(795, 270));
					{
						guielements::key_bind("Aimbot Key", Config::AIMBOT::aimkey_bind, ImVec2(100.0f, 25.0f));
						guielements::key_bind("Heal Key", Config::PLAYER::player_healkey_bind, ImVec2(100.0f, 25.0f));
						guielements::key_bind("Armor Key", Config::PLAYER::player_armorkey_bind, ImVec2(100.0f, 25.0f));
						guielements::key_bind("Speedboost Key", Config::VEHICLE::vehicle_speed_bind, ImVec2(100.0f, 25.0f));
					}
					guielements::EndGroupBox();
				}
			}
			guielements::EndGroupBox();
		}
		ImGui::End();
	}

	if (Config::AIMBOT::enable)
	{
		if (Config::AIMBOT::fov)
		{
			auto draw_list = ImGui::GetBackgroundDrawList();
			draw_list->AddCircle(ImVec2(ScreenX / 2, ScreenY / 2), Config::AIMBOT::fovsize, IM_COL32(255, 255, 255, 255), 100);
		}

		Aimbot::Tick();
	}
	if (Config::VEHICLE::vehicle_enabled)
	{
		Vehicler::Tick();
	}
	Player::Tick();
	Weapon::Tick();
	ESP::Tick();

	ImGui::Render();
	pContext->OMSetRenderTargets(1, &pRenderTargetView, NULL);
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
	return oPresent(pSwapchain, SyncInterval, Flags);
}

void STDMETHODCALLTYPE MainThread() 
{
	uintptr_t pPresentAddr = SteamOverlay::FindPattern(SteamOverlay::GetSteamModule(), "48 89 6C 24 18 48 89 74 24 20 41 56 48 83 EC 20 41 8B E8");
	SteamOverlay::CreateHook(pPresentAddr, (uintptr_t)hkPresent, (long long*)&oPresent);
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD dwReason, LPVOID lpReserved) 
{
	if (dwReason == DLL_PROCESS_ATTACH)
	{
		DisableThreadLibraryCalls(hModule);
		MainThread();
	}
	return TRUE;
}