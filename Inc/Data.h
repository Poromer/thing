#pragma once
#include "pch.h"

namespace GameData
{
	// Settings
	static AEVec2 WindowSize{ 800,600 };

	AEVec2& GetWindowSize()
	{
		return WindowSize;
	}
}

namespace UI
{
	
	// Variables Affected By GameData WINDOW_WIDTH & WINDOW_HEIGHT
	
	// Font Size to be 3% of Screen Width
	static f32 FONT_SIZE{ GameData::WindowSize.x * 0.03f };
	
	// CSS Style Column & Grid System
	constexpr f32 GAME_ROW_UNIT{ 12.f };
	constexpr f32 GAME_COL_UNIT{ 12.f };
	static f32	UNIT_X{ GameData::WindowSize.x / GAME_ROW_UNIT };
	static f32	UNIT_Y{ GameData::WindowSize.y / GAME_COL_UNIT };

	// End
}

namespace GameConstants
{
	constexpr const char* GAME_NAME				{ "Pingu Pong" };
	constexpr const char* ASSETS_PATH			{ "../Assets/" };	// Gerald Said this is bad practice as it means having to concated strings 
																	// which causes new strings to be construct wasiting performace since projects can have alot of strings
}

namespace PATHS
{
	constexpr const char* ASSETS_PATH{ "../Assets/" };
	constexpr const char* FONTS_PATH{ "../Assets/Font/PressStart2P-Regular.ttf" };
}