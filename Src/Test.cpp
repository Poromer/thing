#include "pch.h"
#include "Test.h"
#include "MainMenu.h"

namespace
{
	Entity BG_Hero, test;
	UI_Manager uiManager;
}


void Test::Load()
{
	 
}

void Test::Init()
{
	// Sizes Hard coded for now
	UI::InitUI_Element(BG_Hero, 405, 102, { -UI::UNIT_X * 2.5f , UI::UNIT_Y * .5f }, ASSETS::HERO_SPLASHSCREEN);
	UI::InitUI_Element(test, 405, 102, { 0,0 });

	// Testing Groupping of UI Elements
	UI::GroupUI_Element(BG_Hero, test);

	// adding the event to a entity directlty
	UI_Event event(UI_EventType::BUTTON_HOLD, UI::ClickDragUI_Element, &BG_Hero, AEVK_LBUTTON);
	BG_Hero.GetComponent<UI_Element>()->m_event = event;
}

void Test::Update(const f64& _deltatime)
{
	if(UI::IsCursorOnUI_Element(BG_Hero))
	{
		// Creating and sending a "event" // super ineffient doe since its all by value... really need to do heap allocation soon
		// UI_Event event(UI_EventType::BUTTON_HOLD, UI::ClickDragUI_Element, &BG_Hero, AEVK_LBUTTON);
		// BG_Hero.GetComponent<UI_Element>()->m_event = event;

		uiManager.AddEvent(BG_Hero.GetComponent<UI_Element>()->m_event);
	}

	if (Input::IsKeyTriggered(AEVK_U)) UI::UnGroupUI_Element(BG_Hero,test);
	
	if (Input::IsKeyTriggered(AEVK_M)) GameStateManager::GSMChangeState<MainMenu>();

	uiManager.UpdateEvents();
	uiManager.ClearEvent();
}

void Test::Draw()
{
	AEGfxSetBackgroundColor(0,0,0);
	Graphics::Draw(BG_Hero);
	Graphics::Draw(test);
}

void Test::Free()
{

}

void Test::Unload()
{
	BG_Hero.Unload();
	test.Unload();
}
