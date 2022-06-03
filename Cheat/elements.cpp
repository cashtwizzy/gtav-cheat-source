#include <iostream>
#include "elements.h"
#include <iostream>

#define IMGUI_DEFINE_MATH_OPERATORS

namespace guielements
{

	void draw_logo(ImVec2 pos, int sz, ImColor clr, const char* text) {
		/*ImGui::GetWindowDrawList()->AddRectFilled(
			pos,
			{ pos.x + sz, pos.y + sz },
			clr,
			100,
			1 | 2 | 4
		);
		ImGui::GetWindowDrawList()->AddCircleFilled(
			{ pos.x + sz / 2, pos.y + sz / 2 },
			(sz + 1) / 2,
			clr,
			32
		);

		ImGui::GetWindowDrawList()->AddRectFilled(
			{ pos.x + float(sz / 5.9),  pos.y + float(sz / 5.9) },
			{ pos.x + sz - (sz / 5), pos.y + sz - (sz / 5) },
			ImGui::GetColorU32(ImGuiCol_WindowBg),
			100,
			1 | 2 | 4
		);*/

		ImGui::GetWindowDrawList()->AddText(pos, clr, text);
	}

	ImU32 quick_lerp(ImVec4 from, ImVec4 to, float step) {
		ImU32 _col = ImU32();
		if (ImGui::IsItemHovered())
			_col = ImGui::GetColorU32(ImLerp(from, to, step));
		else _col = ImGui::GetColorU32(ImLerp(from, to, step));

		return _col;
	}

	bool ToggleNiggaButton(const char* label, bool* v, const ImVec2& size_arg)
	{

		ImGuiWindow* window = ImGui::GetCurrentWindow();
		if (window->SkipItems)
			return false;

		int flags = 0;
		ImGuiContext& g = *GImGui;
		const ImGuiStyle& style = g.Style;
		const ImGuiID id = window->GetID(label);
		const ImVec2 label_size = ImGui::CalcTextSize(label, NULL, true);

		ImVec2 pos = window->DC.CursorPos;
		ImVec2 size = ImGui::CalcItemSize(size_arg, label_size.x + style.FramePadding.x * 2.0f, label_size.y + style.FramePadding.y * 2.0f);

		const ImRect bb(pos, ImVec2(pos.x + size.x, pos.y + size.y));
		ImGui::ItemSize(bb, style.FramePadding.y);
		if (!ImGui::ItemAdd(bb, id))
			return false;

		if (window->DC.ItemFlags & ImGuiItemFlags_ButtonRepeat) flags |= ImGuiButtonFlags_Repeat;
		bool hovered, held;
		bool pressed = ImGui::ButtonBehavior(bb, id, &hovered, &held, flags);

		// Render
		const ImU32 col = ImGui::GetColorU32((hovered && held || *v) ? ImGuiCol_ButtonActive : (hovered ? ImGuiCol_ButtonHovered : ImGuiCol_Button));
		ImGui::RenderFrame(bb.Min, bb.Max, col, true, style.FrameRounding);
		ImGui::RenderTextClipped(ImVec2(bb.Min.x + style.FramePadding.x, bb.Min.y + style.FramePadding.y), ImVec2(bb.Max.x - style.FramePadding.x, bb.Max.y - style.FramePadding.y), label, NULL, &label_size, style.ButtonTextAlign, &bb);
		if (pressed)
			*v = !*v;

		return pressed;
	}

	bool BeginGroupBox(const char* name, const ImVec2& size_arg)
	{
		ImGuiWindow* window = ImGui::GetCurrentWindow();
		ImGuiWindowFlags flags = ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_ChildWindow;

		window->DC.CursorPos.y += GImGui->FontSize / 2;
		const ImVec2 content_avail = ImGui::GetContentRegionAvail();
		ImVec2 size = ImFloor(size_arg);
		if (size.x <= 0.0f) {
			size.x = ImMax(content_avail.x, 4.0f) - fabsf(size.x); // Arbitrary minimum zero-ish child size of 4.0f (0.0f causing too much issues)
		}
		if (size.y <= 0.0f) {
			size.y = ImMax(content_avail.y, 4.0f) - fabsf(size.y);
		}

		ImGui::SetNextWindowSize(size);
		bool ret;
		ImGui::Begin(name, &ret, flags);
		//bool ret = ImGui::Begin(name, NULL, size, -1.0f, flags);

		window = ImGui::GetCurrentWindow();

		auto padding = ImGui::GetStyle().WindowPadding;

		auto text_size = ImGui::CalcTextSize(name, NULL, true);

		if (text_size.x > 1.0f) {
			window->DrawList->PushClipRectFullScreen();
			//window->DrawList->AddRectFilled(window->DC.CursorPos - ImVec2{ 4, 0 }, window->DC.CursorPos + (text_size + ImVec2{ 4, 0 }), GetColorU32(ImGuiCol_ChildWindowBg));
			//RenderTextClipped(pos, pos + text_size, name, NULL, NULL, GetColorU32(ImGuiCol_Text));
			window->DrawList->PopClipRect();
		}
		//if (!(window->Flags & ImGuiWindowFlags_ShowBorders))
		//	ImGui::GetCurrentWindow()->Flags &= ~ImGuiWindowFlags_ShowBorders;

		return ret;
	}

	void EndGroupBox()
	{
		ImGui::EndChild();
		ImGuiWindow* window = ImGui::GetCurrentWindow();
		window->DC.CursorPosPrevLine.y -= GImGui->FontSize / 2;
	}

	void tab(const char* label, int* value, int index)
	{
		ImGuiContext& g = *GImGui;
		ImVec2 p = ImGui::GetCursorScreenPos();
		ImDrawList* draw_list = ImGui::GetWindowDrawList();

		const ImVec2 label_size = ImGui::CalcTextSize(label, NULL, true);
		const ImGuiStyle& style = g.Style;

		const ImRect total_bb = ImRect(p, ImVec2(p.x + 120, p.y + 39));

		ImGui::InvisibleButton(label, ImVec2(120, 40));

		if (ImGui::IsItemClicked())
			*value = index;

		if (ImGui::IsItemHovered())
			ImGui::SetMouseCursor(7);

		float t = *value == index ? 1.0f : 0.0f;
		if (g.LastActiveId == g.CurrentWindow->GetID(label)) {
			float t_anim = ImSaturate(g.LastActiveIdTimer / 0.23f);
			t = *value == index ? (t_anim) : (1.0f - t_anim);
		}

		ImU32 col_bg = ImU32();
		col_bg =
			quick_lerp(ImGui::ColorConvertU32ToFloat4(ImGui::GetColorU32(ImGuiCol_WindowBg)), ImGui::ColorConvertU32ToFloat4(ImColor(0, 0, 0, 255)), t);

		ImU32 col_txt = ImU32();
		col_txt =
			quick_lerp(ImGui::ColorConvertU32ToFloat4(ImGui::GetColorU32(ImGuiCol_TextDisabled)), ImGui::ColorConvertU32ToFloat4(ImGui::GetColorU32(ImGuiCol_Text)), t);

		draw_list->AddRectFilled(ImVec2(total_bb.Min.x + 0, total_bb.Min.y + 37), total_bb.Max, col_bg/*ImGui::GetColorU32(ImGuiCol_MainColorAccent, t)*/);
		draw_list->AddText(ImVec2(total_bb.Min.x + 11, total_bb.Min.y + 12), col_txt/*ImGui::GetColorU32(ImGuiCol_Text, 0.45 + t)*/, label);
	}

	const char* const KeyNames[] = {
	"Unknown",
	"VK_LBUTTON",
	"VK_RBUTTON",
	"VK_CANCEL",
	"VK_MBUTTON",
	"VK_XBUTTON1",
	"VK_XBUTTON2",
	"Unknown",
	"VK_BACK",
	"VK_TAB",
	"Unknown",
	"Unknown",
	"VK_CLEAR",
	"VK_RETURN",
	"Unknown",
	"Unknown",
	"VK_SHIFT",
	"VK_CONTROL",
	"VK_MENU",
	"VK_PAUSE",
	"VK_CAPITAL",
	"VK_KANA",
	"Unknown",
	"VK_JUNJA",
	"VK_FINAL",
	"VK_KANJI",
	"Unknown",
	"VK_ESCAPE",
	"VK_CONVERT",
	"VK_NONCONVERT",
	"VK_ACCEPT",
	"VK_MODECHANGE",
	"VK_SPACE",
	"VK_PRIOR",
	"VK_NEXT",
	"VK_END",
	"VK_HOME",
	"VK_LEFT",
	"VK_UP",
	"VK_RIGHT",
	"VK_DOWN",
	"VK_SELECT",
	"VK_PRINT",
	"VK_EXECUTE",
	"VK_SNAPSHOT",
	"VK_INSERT",
	"VK_DELETE",
	"VK_HELP",
	"0",
	"1",
	"2",
	"3",
	"4",
	"5",
	"6",
	"7",
	"8",
	"9",
	"Unknown",
	"Unknown",
	"Unknown",
	"Unknown",
	"Unknown",
	"Unknown",
	"Unknown",
	"A",
	"B",
	"C",
	"D",
	"E",
	"F",
	"G",
	"H",
	"I",
	"J",
	"K",
	"L",
	"M",
	"N",
	"O",
	"P",
	"Q",
	"R",
	"S",
	"T",
	"U",
	"V",
	"W",
	"X",
	"Y",
	"Z",
	"VK_LWIN",
	"VK_RWIN",
	"VK_APPS",
	"Unknown",
	"VK_SLEEP",
	"VK_NUMPAD0",
	"VK_NUMPAD1",
	"VK_NUMPAD2",
	"VK_NUMPAD3",
	"VK_NUMPAD4",
	"VK_NUMPAD5",
	"VK_NUMPAD6",
	"VK_NUMPAD7",
	"VK_NUMPAD8",
	"VK_NUMPAD9",
	"VK_MULTIPLY",
	"VK_ADD",
	"VK_SEPARATOR",
	"VK_SUBTRACT",
	"VK_DECIMAL",
	"VK_DIVIDE",
	"VK_F1",
	"VK_F2",
	"VK_F3",
	"VK_F4",
	"VK_F5",
	"VK_F6",
	"VK_F7",
	"VK_F8",
	"VK_F9",
	"VK_F10",
	"VK_F11",
	"VK_F12",
	"VK_F13",
	"VK_F14",
	"VK_F15",
	"VK_F16",
	"VK_F17",
	"VK_F18",
	"VK_F19",
	"VK_F20",
	"VK_F21",
	"VK_F22",
	"VK_F23",
	"VK_F24",
	"Unknown",
	"Unknown",
	"Unknown",
	"Unknown",
	"Unknown",
	"Unknown",
	"Unknown",
	"Unknown",
	"VK_NUMLOCK",
	"VK_SCROLL",
	"VK_OEM_NEC_EQUAL",
	"VK_OEM_FJ_MASSHOU",
	"VK_OEM_FJ_TOUROKU",
	"VK_OEM_FJ_LOYA",
	"VK_OEM_FJ_ROYA",
	"Unknown",
	"Unknown",
	"Unknown",
	"Unknown",
	"Unknown",
	"Unknown",
	"Unknown",
	"Unknown",
	"Unknown",
	"VK_LSHIFT",
	"VK_RSHIFT",
	"VK_LCONTROL",
	"VK_RCONTROL",
	"VK_LMENU",
	"VK_RMENU"
	};

	static bool IsKeyPressedMap(ImGuiKey key, bool repeat = true)
	{
		const int key_index = GImGui->IO.KeyMap[key];
		return (key_index >= 0) ? ImGui::IsKeyPressed(key_index, repeat) : false;
	}

	bool key_bind(const char* label, int& k, const ImVec2& size_arg)
	{
		ImGuiWindow* window = ImGui::GetCurrentWindow();
		if (window->SkipItems)
			return false;

		ImGuiContext& g = *GImGui;
		ImGuiIO& io = g.IO;
		const ImGuiStyle& style = g.Style;

		const ImGuiID id = window->GetID(label);
		const ImVec2 label_size = ImGui::CalcTextSize(label, NULL, true);
		ImVec2 size = ImGui::CalcItemSize(size_arg, ImGui::CalcItemWidth(), label_size.y + style.FramePadding.y * 2.0f);
		const ImRect frame_bb(window->DC.CursorPos, ImVec2(window->DC.CursorPos.x + size.x, window->DC.CursorPos.y + size.y));
		const ImRect total_bb(window->DC.CursorPos, frame_bb.Max);

		ImGui::ItemSize(total_bb, style.FramePadding.y);
		if (!ImGui::ItemAdd(total_bb, id))
			return false;

		const bool focus_requested = ImGui::FocusableItemRegister(window, g.ActiveId == id);
		//const bool focus_requested_by_code = focus_requested && (window->FocusIdxAllCounter == window->FocusIdxAllRequestCurrent);
		//const bool focus_requested_by_tab = focus_requested && !focus_requested_by_code;

		const bool hovered = ImGui::ItemHoverable(frame_bb, id);

		if (hovered) {
			ImGui::SetHoveredID(id);
			g.MouseCursor = ImGuiMouseCursor_TextInput;
		}

		const bool user_clicked = hovered && io.MouseClicked[0];

		if (focus_requested || user_clicked) {
			if (g.ActiveId != id) {
				// Start edition
				memset(io.MouseDown, 0, sizeof(io.MouseDown));
				memset(io.KeysDown, 0, sizeof(io.KeysDown));
				k = 0;
			}
			ImGui::SetActiveID(id, window);
			ImGui::FocusWindow(window);
		}
		else if (io.MouseClicked[0]) {
			// Release focus when we click outside
			if (g.ActiveId == id)
				ImGui::ClearActiveID();
		}

		bool value_changed = false;
		int key = k;

		if (g.ActiveId == id) {
			for (auto i = 0; i < 5; i++) {
				if (io.MouseDown[i]) {
					switch (i) {
					case 0:
						key = VK_LBUTTON;
						break;
					case 1:
						key = VK_RBUTTON;
						break;
					case 2:
						key = VK_MBUTTON;
						break;
					case 3:
						key = VK_XBUTTON1;
						break;
					case 4:
						key = VK_XBUTTON2;
						break;
					}
					value_changed = true;
					ImGui::ClearActiveID();
				}
			}
			if (!value_changed) {
				for (auto i = VK_BACK; i <= VK_RMENU; i++) {
					if (io.KeysDown[i]) {
						key = i;
						value_changed = true;
						ImGui::ClearActiveID();
					}
				}
			}

			if (IsKeyPressedMap(ImGuiKey_Escape)) {
				k = 0;
				ImGui::ClearActiveID();
			}
			else {
				k = key;
			}
		}

		// Render
		// Select which buffer we are going to display. When ImGuiInputTextFlags_NoLiveEdit is Set 'buf' might still be the old value. We Set buf to NULL to prevent accidental usage from now on.

		char buf_display[64] = "None";

		ImGui::RenderFrame(frame_bb.Min, frame_bb.Max, ImGui::GetColorU32(ImGuiCol_Button), true, 5);
		window->DrawList->AddRect(frame_bb.Min, frame_bb.Max, ImColor(90, 90, 90, 255), 5);

		if (k != 0 && g.ActiveId != id) {
			strcpy_s(buf_display, KeyNames[k]);
		}
		else if (g.ActiveId == id) {
			strcpy_s(buf_display, "Waiting...");
		}

		const ImRect clip_rect(frame_bb.Min.x, frame_bb.Min.y, frame_bb.Min.x + size.x, frame_bb.Min.y + size.y); // Not using frame_bb.Max because we have adjusted size
		ImVec2 render_pos = ImVec2(frame_bb.Min.x + style.FramePadding.x, frame_bb.Min.y + style.FramePadding.y);
		ImGui::RenderTextClipped(ImVec2(frame_bb.Min.x + style.FramePadding.x, frame_bb.Min.y + style.FramePadding.y), ImVec2(frame_bb.Max.x - style.FramePadding.x, frame_bb.Max.y - style.FramePadding.y), buf_display, NULL, NULL, style.ButtonTextAlign, &clip_rect);
		//RenderTextClipped(frame_bb.Min + style.FramePadding, frame_bb.Max - style.FramePadding, buf_display, NULL, NULL, GetColorU32(ImGuiCol_Text), style.ButtonTextAlign, &clip_rect);
		//draw_window->DrawList->AddText(g.Font, g.FontSize, render_pos, GetColorU32(ImGuiCol_Text), buf_display, NULL, 0.0f, &clip_rect);

		if (label_size.x > 0)
			ImGui::RenderText(ImVec2(total_bb.Max.x + style.FramePadding.x, frame_bb.Min.y + style.FramePadding.y), label);

		return value_changed;
	}
}