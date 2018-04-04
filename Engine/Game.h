//*****************************************************************************
//
// ÉQÅ[ÉÄèàóù [Game.h]
//
// Author : LIAO HANCHEN
//
//*****************************************************************************
#ifndef _GAME_H_
#define _GAME_H_

#include "Console.h"
#include "Engine.h"
#include "Resources.h"
#include "SceneManager.h"
#include "Time.h"
#include "Windows.h"

class Game
{
private:

public:
	D3DXVECTOR3			mWorldFront = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
	D3DXVECTOR3			mWorldUp = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	D3DXVECTOR3			mWorldRight = D3DXVECTOR3(1.0f, 0.0f, 0.0f);

	

	Game();
	~Game();
};

#endif // !_GAME_H_
