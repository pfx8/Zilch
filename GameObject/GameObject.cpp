//*****************************************************************************
//
// GameObjectファイル [GameObject.cpp]
//
// Author : リョウ　カンシン
//
//*****************************************************************************
#include "GameObject.h"

//*****************************************************************************
//
// コンストラクタ
//
//*****************************************************************************
GameObject::GameObject()
{

}

//*****************************************************************************
//
// デストラクタ
//
//*****************************************************************************
GameObject::~GameObject()
{

}

//*****************************************************************************
//
// 初期化
//
//*****************************************************************************
void GameObject::start()
{
	for (auto it : mComponents)
	{
		it->start();
	}
}

//*****************************************************************************
//
// 更新
//
//*****************************************************************************
void GameObject::update()
{
	for (auto it : mComponents)
	{
		if (it->mActive == true)
		{
			it->update();
		}
	}
}