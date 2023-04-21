#include "pch.h"
#include "SplashScreen.h"

namespace
{
	Entity Hero;
}


void SplashScreen::Load()
{

}

void SplashScreen::Init()
{
	auto heroRend = Hero.AddComponent<Renderable>();
	heroRend->Mesh = Graphics::CreateQuadMesh(405, 102);
	heroRend->Texture = AEGfxTextureLoad(ASSETS::HERO_SPLASHSCREEN);

	auto heroTrans = Hero.AddComponent<Transform>();
	heroTrans->Pos = { -UI::UNIT_X * 2.5f , UI::UNIT_Y * .5f};
}

void SplashScreen::Update(const f64& _deltatime)
{
}

void SplashScreen::Draw()
{
	AEGfxSetBackgroundColor(0,0,0);
	Graphics::Draw(Hero);
}

void SplashScreen::Free()
{

}

void SplashScreen::Unload()
{
	Hero.Unload();
}
