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
	// ライト位置取得
	Transform* trans = this->mLight->mGameObject->getComponent<Transform>();

	// システムカメラを取得
	Camera* sysCamera = this->mGameObject->mScene->mSystemCamera;

	// マウス操作
	if (IsMouseCenterPressed())
	{
		// 上下移動
		if (GetMouseY() > this->mMouseIsMoving)
		{
			// プラス
			this->mLight->mLightPos -= sysCamera->mCameraUp * this->mMoveSpeed;
		}
		
		if(GetMouseY() < -this->mMouseIsMoving)
		{
			// マイナス
			this->mLight->mLightPos += sysCamera->mCameraUp * this->mMoveSpeed;
		}

		// 水平移動
		if (GetMouseX() > this->mMouseIsMoving)
		{
			// プラス
			this->mLight->mLightPos -= sysCamera->mCameraRight * this->mMoveSpeed;
		}

		if (GetMouseX() < -this->mMouseIsMoving)
		{
			// マイナス
			this->mLight->mLightPos += sysCamera->mCameraRight * this->mMoveSpeed;
		}

		// マウス操作をライトGUIに更新
		trans->mPos = this->mLight->mLightPos;
	}
}