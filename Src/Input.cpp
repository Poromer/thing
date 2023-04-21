#include "pch.h"

namespace Input
{
	AEVec2 GetCursorPosition()
	{
		s32 CursorX, CursorY;
		AEInputGetCursorPosition(&CursorX, &CursorY);
		CursorX -= AEGetWindowWidth() / 2;
		CursorY -= AEGetWindowHeight() / 2;
		return { static_cast<f32>(CursorX), static_cast<f32>(CursorY) }; // Convert from s32 to f32 as AEVec2 takes in f32
	}

	bool IsKeyTriggered(u8 _key)
	{
		return AEInputCheckTriggered(_key);
	}

	bool IsKeyPressed(u8 _key)
	{
		if (AEInputCheckPrev(_key) && AEInputCheckCurr(_key))
			return  true;
		return false;
	}

	bool IsKeyReleased(u8 _key)
	{
		if (AEInputCheckPrev(_key) != AEInputCheckCurr(_key))
			return  true;
		return false;
	}
}