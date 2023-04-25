#include "pch.h"
#include "SplashScreen.h"
#include "MainMenu.h"
#include "Test.h"

namespace
{
	Entity BG_Hero;
	UI_Manager uiManager;
}


void SplashScreen::Load()
{
	 
}

void SplashScreen::Init()
{
	UI::InitUI_Element(BG_Hero, 405, 102, { -UI::UNIT_X * 2.5f , UI::UNIT_Y * .5f }, ASSETS::HERO_SPLASHSCREEN); // Also Kinda Loading in Assets doe

}

void SplashScreen::Update(const f64& _deltatime)
{
	if(Input::IsKeyTriggered(AEVK_T))
		GameStateManager::GSMChangeState<Test>();
	if (Input::IsKeyTriggered(AEVK_M))
		GameStateManager::GSMChangeState<MainMenu>();

	uiManager.UpdateEvents();
	uiManager.ClearEvent();
}

void SplashScreen::Draw()
{
	AEGfxSetBackgroundColor(0, 0, 0);
	Graphics::Draw(BG_Hero);
}

void SplashScreen::Free()
{

}

void SplashScreen::Unload()
{
	BG_Hero.Unload();
}
