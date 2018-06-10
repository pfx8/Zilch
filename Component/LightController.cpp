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
	Camera* sysCamera = this->mParentGameObject->mParentScene->mSystemCamera;

	// マウス操作
	if (IsMouseRightPressed())
	{
		// 上下移動
		if (GetMouseY() > this->mIsMouseMoving)
		{
			// プラス
			this->mCurrentLight->mLightPos -= sysCamera->mCameraUp * this->mMouseMoveSpeed;
		}
		
		if(GetMouseY() < -this->mIsMouseMoving)
		{
			// マイナス
			this->mCurrentLight->mLightPos += sysCamera->mCameraUp * this->mMouseMoveSpeed;
		}

		// 水平移動
		if (GetMouseX() > this->mIsMouseMoving)
		{
			// プラス
			this->mCurrentLight->mLightPos -= sysCamera->mCameraRight * this->mMouseMoveSpeed;
		}

		if (GetMouseX() < -this->mIsMouseMoving)
		{
			// マイナス
			this->mCurrentLight->mLightPos += sysCamera->mCameraRight * this->mMouseMoveSpeed;
		}

		// マウス操作の結果をライトに渡す
		trans->mPos = this->mCurrentLight->mLightPos;
	}
}

//*****************************************************************************
//
// GUIパネル
//
//*****************************************************************************
void LightController::drawImGui(void)
{
	ImGui::TextUnformatted(u8"操作説明は左のデバッグウインドウに書いてあります");
}