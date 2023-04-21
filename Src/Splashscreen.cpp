#include "pch.h"
#include "SplashScreen.h"
#include "MainMenu.h"

namespace
{
	Entity BG_Hero, test;
}


void SplashScreen::Load()
{
	 
}

void SplashScreen::Init()
{
	UI::InitUI_Element(BG_Hero, 405, 102, { -UI::UNIT_X * 2.5f , UI::UNIT_Y * .5f }, ASSETS::HERO_SPLASHSCREEN);
	UI::InitUI_Element(test, 405, 102, { 0,0 });

	UI::GroupUI_Element(BG_Hero, test);

}

void SplashScreen::Update(const f64& _deltatime)
{
	std::cout << Input::GetCursorPositionDelta() << std::endl;
	if(Input::IsKeyPressed(AEVK_LBUTTON))
	{
		UI::ClickDragUI_Element(BG_Hero);
	}

	if (Input::IsKeyTriggered(AEVK_U)) UI::UnGroupUI_Element(BG_Hero,test);
	
	if (Input::IsKeyTriggered(AEVK_M)) GameStateManager::GSMChangeState<MainMenu>();
}

void SplashScreen::Draw()
{
	AEGfxSetBackgroundColor(0,0,0);
	Graphics::Draw(BG_Hero);
	Graphics::Draw(test);
}

void SplashScreen::Free()
{

}

void SplashScreen::Unload()
{
	BG_Hero.Unload();
	test.Unload();
}
