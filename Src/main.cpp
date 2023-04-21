#include "pch.h"
#include "SplashScreen.h"
#include "MainMenu.h"

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

	AESysInit(hInstance, nCmdShow, GameData::WindowSize.x, GameData::WindowSize.y, 1, 60, true, NULL);
	AESysSetWindowTitle(Game_Constants::GAME_NAME);
	AESysReset();

	Font_PStart2P = AEGfxCreateFont(ASSETS::FONTS_PATH, UI::FONT_SIZE);

	using namespace GameStateManager;

	// GSM Loop
	//GSM_Initialize(1);
	GSMAdd<SplashScreen>();
	GSMAdd<MainMenu>();
	GSMInit<SplashScreen>();

	while (GSM_Current != GSM_QUIT)
	{
		GSM_Update();
		Init();

		// Game Loop
		while (GSM_Current == GSM_Next)
		{
			AESysFrameStart();
			AEAudioUpdate();
			AEInputUpdate();

			Update();
			Draw();

			AESysFrameEnd();

			// check if forcing the application to quit
			if (0 == AESysDoesWindowExist())
				GSM_Quit();
		}

		Free();
		if (GSM_Next != GSM_RESTART)
			Unload();
		GSM_Previous = GSM_Current;
		GSM_Current = GSM_Next;
	}

	GSM_Terminate();
	AEGfxDestroyFont(Font_PStart2P);
	AESysExit();
}