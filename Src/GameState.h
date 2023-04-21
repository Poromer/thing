/*!************************************************************************
 * \file    GameState.h
 * \author  Koh Wei Jie
 * \date    14/04/2023
 * \brief
 *	GameState class, Super Class to use for other child gamestates.
 *************************************************************************/


#pragma once
#include <AETypes.h>


 constexpr u32 GSM_RESTART = 0xFFFFFFFE;
 constexpr u32 GSM_QUIT = 0xFFFFFFFF;

 /*!*************************************************************************
  * \brief
  * GameState Super Class.
  * Declares virtual functions for essential functions that a Child Gamestate
  * will have
 ***************************************************************************/
class GameState
{
public:
	u32 GameStateIndex;

	GameState(u32 _index) : GameStateIndex(_index) {}

	virtual void Load() {};
	virtual void Init() {};
	virtual void Update(const f64&) {};
	virtual void Draw() {};
	virtual void Free() {};
	virtual void Unload() {};
};