#include "pch.h"
#include "SplashScreen.h"
#include "MainMenu.h"

namespace
{
	Entity BG_Hero;
}


void SplashScreen::Load()
{

}

void SplashScreen::Init()
{
	auto heroRend = BG_Hero.AddComponent<Renderable>();
	heroRend->Mesh = Graphics::CreateQuadMesh(405, 102);
	heroRend->Texture = AEGfxTextureLoad(ASSETS::HERO_SPLASHSCREEN);

	auto heroTrans = BG_Hero.AddComponent<Transform>();
	heroTrans->Pos = { -UI::UNIT_X * 2.5f , UI::UNIT_Y * .5f};
}

void SplashScreen::Update(const f64& _deltatime)
{
	//std::cout << Input::GetCursorPosition() << std::endl;
	if (Input::IsKeyPressed(AEVK_1)) tprint("Key 1");
	if(Input::IsKeyTriggered(AEVK_2)) tprint("Key 2");
	if(Input::IsKeyReleased(AEVK_3)) tprint("Key 3");

	if (Input::IsKeyReleased(AEVK_M)) GameStateManager::GSMChangeState<MainMenu>();
}

void SplashScreen::Draw()
{
	AEGfxSetBackgroundColor(0,0,0);
	Graphics::Draw(BG_Hero);
}

void SplashScreen::Free()
{

}

void SplashScreen::Unload()
{
	BG_Hero.Unload();
}
