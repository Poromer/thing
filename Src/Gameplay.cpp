#include "pch.h"
#include "GamePlay.h"

namespace
{
	Entity test;
	UI_Manager uiManager;
}

void GamePlay::Load()
{

}

void GamePlay::Init()
{
	// Init Game Entities
	UI::InitUI_Element(test, 405, 102, { 0,0 });

	// Init Events into Entities
	UI_Event event(UI_EventType::BUTTON_HOLD, UI::ClickDragUI_Element, &test, AEVK_LBUTTON);
	test.GetComponent<UI_Element>()->m_event = event;
}

void GamePlay::Update(const f64& _deltatime)
{

}

void GamePlay::Draw()
{
	AEGfxSetBackgroundColor(0, 0, 0);
	Graphics::Draw(test);
}

void GamePlay::Free()
{

}

void GamePlay::Unload()
{

}
