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
LightController::LightController(void)
{

}

//*****************************************************************************
//
// デストラクタ
//
//*****************************************************************************
LightController::~LightController(void)
{

}

//*****************************************************************************
//
// 更新
//
//*****************************************************************************
void LightController::update(void)
{
	// ライト位置取得
	Transform* trans = this->mCurrentLight->mParentGameObject->getComponent<Transform>();

	// システムカメラを取得
	Camera* sysCamera = this->mParentGameObject->mScene->mSystemCamera;

	// マウス操作
	if (IsMouseCenterPressed())
	{
		// 上下移動
		if (GetMouseY() > this->mIsMouseMoving)
		{
			// プラス
			this->mCurrentLight->mLightPos -= sysCamera->mCameraUp * this->mMoveSpeed;
		}
		
		if(GetMouseY() < -this->mIsMouseMoving)
		{
			// マイナス
			this->mCurrentLight->mLightPos += sysCamera->mCameraUp * this->mMoveSpeed;
		}

		// 水平移動
		if (GetMouseX() > this->mIsMouseMoving)
		{
			// プラス
			this->mCurrentLight->mLightPos -= sysCamera->mCameraRight * this->mMoveSpeed;
		}

		if (GetMouseX() < -this->mIsMouseMoving)
		{
			// マイナス
			this->mCurrentLight->mLightPos += sysCamera->mCameraRight * this->mMoveSpeed;
		}

		// マウス操作の結果をライトに渡す
		trans->mPos = this->mCurrentLight->mLightPos;
	}
}