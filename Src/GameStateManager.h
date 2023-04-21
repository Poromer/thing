#pragma once
#include "GameState.h"

namespace GameStateManager
{
	inline u32 GetNewStateID()
	{
		static u32 lastID = 0;
		return lastID++;
	}

	template <typename T>
	u32 GetStateTypeID()
	{
		static u32 typeID = GetNewStateID();
		return typeID;
	}

	extern u32 GSM_Current;
	extern u32 GSM_Previous;
	extern u32 GSM_Next;

	using GameStateList = std::unordered_map<u32, GameState*>;
	GameStateList& GetGameStateList();
	GameState*& CurrentStateInstance();

	void GSM_Initialize(u32 StartState);
	void GSM_Update();
	void GSM_Quit();
	void GSM_Terminate();


	template <typename T>
	void GSMAdd()
	{
		T* newGS = new T(GetStateTypeID<T>());
		GetGameStateList().emplace(std::make_pair(newGS->GameStateIndex, newGS)); // Adding the instance of a new state to a list
	}


	template <typename T>
	void GSMInit()
	{
		GSM_Current = GSM_Previous = GSM_Next = GetStateTypeID<T>();
		CurrentStateInstance() = GetGameStateList().at(GetStateTypeID<T>());

	}


	template <typename T>
	void GSMChangeState()
	{
		std::cout << GetStateTypeID<T>();
		GSM_Next = GetStateTypeID<T>();
	}

	void Load();
	void Init();
	void Update();
	void Draw();
	void Free();
	void Unload();
}