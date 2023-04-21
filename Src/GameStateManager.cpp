#include "pch.h"
#include "GameStateManager.h"

namespace GameStateManager
{
	u32 GSM_Current		= 0;
	u32 GSM_Previous	= 0;
	u32 GSM_Next		= 0;
	static GameStateList _GameStateList = {};
	static GameState* _CurrentStateInstance = nullptr;

	void GSM_Initialize(u32 StartState)
	{
		std::cout << "GSM:Initialize" << '\n';

		GSM_Current = GSM_Previous = GSM_Next = StartState;
	}

	void GSM_Update()
	{
		std::cout << "GSM:Update" << '\n';

		switch (GSM_Current)
		{
			case GSM_RESTART:
				GSM_Current = GSM_Previous;
				GSM_Next = GSM_Previous;
				break;
			case GSM_QUIT:
				break;
			default:
				GameState* next = nullptr;
				next = GetGameStateList().at(GSM_Next);
				CurrentStateInstance() = next;
				CurrentStateInstance()->Load();
		}
	}

	void GSM_Restart()
	{
		GSM_Next = GSM_RESTART;
	}

	void GSM_Quit()
	{
		GSM_Next = GSM_QUIT;
	}

	void GSM_Terminate()
	{
		for (auto& state : _GameStateList) {
			//state.second->Terminate();
			delete state.second;
		}
		_GameStateList.clear();
	}

	GameStateList& GetGameStateList()
	{
		return _GameStateList;
	}

	GameState*& CurrentStateInstance()
	{
		return _CurrentStateInstance;
	}

	void Load()
	{
		if (!_CurrentStateInstance)
			return;
		_CurrentStateInstance->Load();
	}

	void Init()
	{
		if (!_CurrentStateInstance)
			return;
		_CurrentStateInstance->Init();

	}

	void Update()
	{
		if (!_CurrentStateInstance)
			return;
		_CurrentStateInstance->Update(AEFrameRateControllerGetFrameTime());
	}

	void Draw()
	{
		if (!_CurrentStateInstance)
			return;
		_CurrentStateInstance->Draw();
	}

	void Free()
	{
		if (!_CurrentStateInstance)
			return;
		_CurrentStateInstance->Free();
	}

	void Unload()
	{

		if (!_CurrentStateInstance)
			return;
		_CurrentStateInstance->Unload();
	}
}