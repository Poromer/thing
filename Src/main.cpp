#include "pch.h"
#include "SplashScreen.h"
#include "MainMenu.h"
#include "Test.h"
#include "GamePlay.h"

/**
// JANK List (Things to Probably Fix)
- Event being stored by value instead of pointers | Fix: store events on the heap and store their pointers in UI_Manager
- Event_UI comparism operator (operator==) is jank af not sure if there a better way of doing it
- Event has things declared a in "Components.h" shld probably move it out
- How to make eventCall in "UI_Event" handle both "void(*)(Entity&)" and "void(*)()"?
- UI_Manager::UpdateEvents() shld use switch statement instead of if statements to check for EventInputType
- Tidy up Collision stuff in Components.cpp and Components.h shld be in their own seperate files
- The way i updated the colliders currently when dragging is in the Drag function itself which is not ideal
	need to get physics? world system up as the place or some central place to update colliders
- Drawwing COllders is also quite jank but not as impt cuz its use for testing oni
*/

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
	GSMAdd<Test>();
	GSMAdd<SplashScreen>();
	GSMAdd<MainMenu>();
	GSMAdd<GamePlay>();
	//GSMInit<SplashScreen>();
	GSMInit<Test>();

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