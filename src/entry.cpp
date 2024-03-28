#include "includes.hpp"
#include "overlay.hpp"
#include "menu.hpp"

int main()
{
	HWND game = FindWindowA("UnrealWindow", "Fortnite  ");

	while (!game)
	{
		std::cout << "Waiting for game..." << std::endl;
		game = FindWindowA("UnrealWindow", "Fortnite  ");
		Sleep(3000);
	}

	std::cout << "Game found!" << std::endl;
	Sleep(3000);

	HWND medal = FindWindowA("MedalOverlayClass", "MedalOverlay");

	while (!medal)
	{
		std::cout << "Waiting for medal..." << std::endl;
		medal = FindWindowA("MedalOverlayClass", "MedalOverlay");
		Sleep(3000);
	}

	std::cout << "Medal found!" << std::endl;
	Sleep(3000);
	
	if (!Overlay::Begin())
	{
		std::cerr << "Failed to start overlay." << std::endl;
		Sleep(3000);
		return 1;
	}

	std::cout << "Overlay started." << std::endl;
	Sleep(3000);

	while (Overlay::StartRender())
	{
		if (GetAsyncKeyState(VK_INSERT) & 1)
			Menu::open = !Menu::open;

		if (Menu::open)
		{
			SetForegroundWindow(Overlay::hwnd);
			Menu::Draw();
		}

		Overlay::EndRender();

		if (GetAsyncKeyState(VK_DELETE))
			break;
	}

	Overlay::StartRender();
	Overlay::EndRender();
		
	Overlay::Destroy();
	std::cout << "Overlay destroyed." << std::endl;

	Sleep(2000);

	return 0;
}