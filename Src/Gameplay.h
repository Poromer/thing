#pragma once
#include "GameState.h"

class GamePlay : public GameState
{
private:

public:
	GamePlay(u32 _index) : GameState(_index) {}

	void Load() override;
	void Init() override;
	void Update(const f64& _deltatime) override;
	void Draw() override;
	void Free() override;
	void Unload() override;
};
