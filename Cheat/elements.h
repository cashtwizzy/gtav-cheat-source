#include "includes.h"
#include "imgui/imgui_internal.h"

namespace guielements
{
	bool ToggleNiggaButton(const char* label, bool* v, const ImVec2& size_arg);
	bool BeginGroupBox(const char* name, const ImVec2& size_arg);
	void EndGroupBox();
	void draw_logo(ImVec2 pos, int sz, ImColor clr, const char* text);
	void pregui_init();
	void tab(const char* label, int* value, int index);
	ImU32 quick_lerp(ImVec4 from, ImVec4 to, float step);
	bool key_bind(const char* label, int& k, const ImVec2& size_arg);
}