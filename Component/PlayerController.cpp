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
PlayerController::PlayerController(void)
{

}

//*****************************************************************************
//
// デストラクタ
//
//*****************************************************************************
PlayerController::~PlayerController(void)
{

}

//*****************************************************************************
//
// 更新
//
//*****************************************************************************
void PlayerController::update(void)
{
	// プレや―の位置取得
	Transform* trans = this->mParentGameObject->getComponent<Transform>();

	// システムカメラを取得
	Camera* sysCamera = this->mParentGameObject->mScene->mSystemCamera;

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
