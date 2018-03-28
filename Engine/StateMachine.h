//*****************************************************************************
//
// 有限オートマトン [StateMachine.h]
//
// Author : LIAO HANCHEN
//
//*****************************************************************************
#ifndef _STATE_MACHINE_H_
#define _STATE_MACHINE_H_

#include "Engine.h"

enum State
{
	Stop,
	Walk,
	Run,
};

class Player
{
private:
	string playerName;
public:
	Player() = default;
	Player(string str) :playerName(str) {}
};

//*****************************************************************************
//
// クラス宣言
//
//*****************************************************************************
class StateMachine
{
private:
	const string stateName;

public:
	StateMachine() = default;
	StateMachine(string str) :stateName(str) {}
	~StateMachine() {}

	string getStateName() { return stateName; }

	virtual void Enter(Player player);
	virtual void Update(Player player);
	virtual void Exit(Player player);
}; 

#endif // !_STATE_MACHINE_H_

