#pragma once
#include <Windows.h>
#include <vector>
#include <d3d11.h>
#include "SteamOverlay.hpp"
#include <emmintrin.h>
#include "ImGui/imgui.h"
#include "ImGui/imgui_impl_dx11.h"
#include "ImGui/imgui_impl_win32.h"
#include "Math.h"
#include "ida.hpp"
typedef HRESULT(*Present)(IDXGISwapChain*, UINT, UINT);
typedef LRESULT(CALLBACK* WNDPROC)(HWND, UINT, WPARAM, LPARAM);

#include "Config.h"
#include "elements.h"
#include "Math.h"
#include "Helper.h"
#include "Inject.h"
#include "Player.h"
#include "Weapon.h"
#include "Vehicle.h"
#include "ESP.h"
#include "Aimbot.h"
#include "fonts.hpp"
#include "ragemp_shift.hpp"