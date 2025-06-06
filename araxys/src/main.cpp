#include <conio.h>
#include <iostream>
#include <windows.h>
#include <synchapi.h>
#include <map>
#include <functional>

#include "print/print.h"
#include "utils/offsets.h"
#include "utils/memory.h"

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