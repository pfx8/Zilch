//*****************************************************************************
//
// ライトコントローラ処理 [LightController.cpp]
//
// Author : リョウ　カンシン
//
//*****************************************************************************
#include "LightController.h"

//*****************************************************************************
//
// コンストラクタ
//
//*****************************************************************************
LightController::LightController()
{

}

//*****************************************************************************
//
// デストラクタ
//
//*****************************************************************************
LightController::~LightController()
{

}

//*****************************************************************************
//
// コントローラ更新
//
//*****************************************************************************
void LightController::update()
{
	Transform* trans = this->mLight->mGameObject->getComponent<Transform>();

	if (IsMouseCenterPressed())
	{
		// 上下移動
		if (GetMouseY() > this->mMouseIsMoving)
		{
			// プラス
			this->mLight->mLightPos.y -= 0.5;
		}
		
		if(GetMouseY() < -this->mMouseIsMoving)
		{
			// マイナス
			this->mLight->mLightPos.y += 0.5;
		}

		// 水平移動
		if (GetMouseX() > this->mMouseIsMoving)
		{
			// プラス
			this->mLight->mLightPos.x -= 0.5;
		}

		if (GetMouseX() < -this->mMouseIsMoving)
		{
			// マイナス
			this->mLight->mLightPos.x += 0.5;
		}

		trans->mPos = this->mLight->mLightPos;
	}
}