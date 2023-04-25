#include "pch.h"
#include "MainMenu.h"

namespace
{
	Entity test;
	UI_Manager uiManager;
}

void MainMenu::Load()
{

}

void MainMenu::Init()
{
	// Init Game Entities
	UI::InitUI_Element(test, 405, 102, { 0,0 });

	// Init Events into Entities
	UI_Event event(UI_EventType::BUTTON_HOLD, UI::ClickDragUI_Element, &test, AEVK_LBUTTON);
	test.GetComponent<UI_Element>()->m_event = event;
}

void MainMenu::Update(const f64& _deltatime)
{

}

void MainMenu::Draw()
{
	AEGfxSetBackgroundColor(0, 0, 0);
	Graphics::Draw(test);
}

void MainMenu::Free()
{

}

void MainMenu::Unload()
{

}
