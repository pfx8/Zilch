//*****************************************************************************
//
// 有限オートマトンマネジメント [StateMachineManager.h]
//
// Author : LIAO HANCHEN
//
//*****************************************************************************
#ifndef _STATE_MACHINE_MANAGER_H_
#define _STATE_MACHINE_MANAGER_H_

#include <iostream>

#include "StateMachine.h"
//*****************************************************************************
//
// クラス宣言
//
//*****************************************************************************
class StateMachineManager
{
private:
	StateMachine* preState;
	StateMachine* curState;

public:
	StateMachineManager(StateMachine* state) : curState(state) {}
	~StateMachineManager() {}

	void Update(Player player);
	void Change(Player player, StateMachine* state);

	StateMachine *getCurState() { return curState; }
}; 

#endif // !_STATE_MACHINE_MANAGER_H_

