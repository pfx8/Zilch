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
	Camera* sysCamera = this->mParentGameObject->mParentScene->mSystemCamera;

	// マウス操作
	if (IsMouseLeftPressed())
	{
		// 上下移動
		if (GetMouseY() > this->mMouseIsMoving)
		{
			// プラス
			trans->mPos -= sysCamera->mCameraUp * this->mMouseMoveSpeed;
		}

		if (GetMouseY() < -this->mMouseIsMoving)
		{
			// マイナス
			trans->mPos += sysCamera->mCameraUp * this->mMouseMoveSpeed;
		}

		// 水平移動
		if (GetMouseX() > this->mMouseIsMoving)
		{
			// プラス
			trans->mPos -= sysCamera->mCameraRight * this->mMouseMoveSpeed;
		}

		if (GetMouseX() < -this->mMouseIsMoving)
		{
			// マイナス
			trans->mPos += sysCamera->mCameraRight * this->mMouseMoveSpeed;
		}
	}
}
