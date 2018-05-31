//*****************************************************************************
//
// プレーヤコントローラ [PlayerControllers.cpp]
//
// Author : リョウ　カンシン
//
//*****************************************************************************
#include "PlayerController.h"

//*****************************************************************************
//
// コンストラクタ
//
//*****************************************************************************
PlayerController::PlayerController()
{

}

//*****************************************************************************
//
// デストラクタ
//
//*****************************************************************************
PlayerController::~PlayerController()
{

}

//*****************************************************************************
//
// 更新
//
//*****************************************************************************
void PlayerController::update()
{
	// プレや―の位置取得
	Transform* trans = this->mGameObject->getComponent<Transform>();

	// システムカメラを取得
	Camera* sysCamera = this->mGameObject->mScene->mSystemCamera;

	// マウス操作
	if (IsMouseRightPressed())
	{
		// 上下移動
		if (GetMouseY() > this->mMouseIsMoving)
		{
			// プラス
			trans->mPos -= sysCamera->mCameraUp * this->mMoveSpeed;
		}

		if (GetMouseY() < -this->mMouseIsMoving)
		{
			// マイナス
			trans->mPos += sysCamera->mCameraUp * this->mMoveSpeed;
		}

		// 水平移動
		if (GetMouseX() > this->mMouseIsMoving)
		{
			// プラス
			trans->mPos -= sysCamera->mCameraRight * this->mMoveSpeed;
		}

		if (GetMouseX() < -this->mMouseIsMoving)
		{
			// マイナス
			trans->mPos += sysCamera->mCameraRight * this->mMoveSpeed;
		}
	}
}
