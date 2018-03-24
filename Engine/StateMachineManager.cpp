//*****************************************************************************
//
// 有限オートマトンマネジメント [StateMachineManager.cpp]
//
// Author : LIAO HANCHEN
//
//*****************************************************************************
#include "StateMachineManager.h"

using namespace std;

//*****************************************************************************
//
// 状態を更新
//
//*****************************************************************************
void StateMachineManager::Update(Player player)
{
	if (this->curState != nullptr)
	{
		this->curState->Update(player);
	}
}

//*****************************************************************************
//
// 状態をチェンジ
//
//*****************************************************************************
void StateMachineManager::Change(Player player, StateMachine* state)
{
	if (this->curState != state)
	{
		this->curState->Exit(player);
		this->preState = this->curState;

		this->curState = state;
		this->curState->Enter(player);
	}
}