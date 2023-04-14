#include "pch.h"

s8 Font_PStart2P{};

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	// Enable run-time memory check for debug builds.
	#if defined(DEBUG) | defined(_DEBUG)
		_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	#endif

	int gGameRunning = 1;

	AESysInit(hInstance, nCmdShow, GameData::WindowSize.x, GameData::WindowSize.y, 1, 60, true, NULL);
	AESysSetWindowTitle(GameConstants::GAME_NAME);
	AESysReset();

	Font_PStart2P = AEGfxCreateFont(PATHS::FONTS_PATH, UI::FONT_SIZE);

	// Game Loop
	while (gGameRunning)
	{
		AESysFrameStart();
		AEInputUpdate();
		AESysFrameEnd();

		// check if forcing the application to quit
		if (AEInputCheckTriggered(AEVK_ESCAPE) || 0 == AESysDoesWindowExist())
			gGameRunning = 0;
	}


	AEGfxDestroyFont(Font_PStart2P);
	AESysExit();
}