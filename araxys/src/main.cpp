#include <conio.h>
#include <iostream>
#include <windows.h>
#include <synchapi.h>
#include <map>
#include <functional>

#include "print/print.h"
#include "utils/offsets.h"
#include "utils/memory.h"
#include "window/window.h"

#include <dwmapi.h>
#include <d3d11.h>

#include <imgui/imgui.h>
#include <imgui/imgui_impl_win32.h>
#include <imgui/imgui_impl_dx11.h>

class CheatWindow : public Window {
private:
	Memory& memory;
	bool showMainWindow = true;

public:
	CheatWindow(HINSTANCE instance, INT cmd_show, Memory& mem)
		: Window(instance, cmd_show), memory(mem) {
	}

	void DrawEspRect(int x, int y, int width, int length) {
		ImDrawList* drawList = ImGui::GetForegroundDrawList();

		const ImVec2 rectMin(x, y);
		const ImVec2 rectMax(x + length, y + width);

		drawList->AddRect(
			rectMin,
			rectMax,
			ImColor(255, 255, 255, 255),
			0.0f,
			0,
			5.0f
		);
	}

	void RenderUI() override {
		ImGui::Begin("Araxys", &showMainWindow, ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoTitleBar);


		ImGui::End();
	}
};

INT APIENTRY WinMain(HINSTANCE instance, HINSTANCE prevInstance, PSTR cmdLine, INT cmdShow)
{
	Memory memory("ac_client.exe");

	if (!memory.getModuleBaseAddress())
		return (1);
	CheatWindow window(instance, cmdShow, memory);
	if (!window.IsRunning())
		return (1);
	return window.Run();
}

// Keep the original console-based version for backward compatibility or testing
int main(void)
{
	Memory memory("ac_client.exe");
	int keyPressed = 0;
	std::map<int, std::function<BOOL()>> keyActions;
	keyActions['a'] = [&memory]() {return memory.toggleHealthCheat(); };
	keyActions['s'] = [&memory]() {return memory.toggleArmorCheat(); };
	keyActions['d'] = [&memory]() {return memory.toggleBulletCheat(); };
	keyActions['f'] = [&memory]() {return memory.toggleFastShootCheat(); };
	keyActions['g'] = [&memory]() {return memory.toggleNoRecoilCheat(); };
	keyActions['h'] = [&memory]() {return memory.actionESPRefresh();  };
	keyActions['j'] = [&memory]() {return memory.executeESPPrint(); };

	print_header();
	while (memory.runCheat() == 0) {
		Sleep(2);
		if (!_kbhit())
			continue;
		keyPressed = _getch();
		auto keyAction = keyActions.find(keyPressed);
		if (keyAction != keyActions.end())
			keyAction->second();
	}
	return (0);
}