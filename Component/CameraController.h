//*****************************************************************************
//
// カメラコントローラ処理 [CameraController..h]
//
// Author : LIAO HANCHEN
//
//*****************************************************************************
#ifndef _CAMERA_CONTROLLER_H_
#define _CAMERA_CONTROLLER_H_

#include "Transform.h"
#include "Camera.h"

#include "..\Engine\Engine.h"
#include "..\Engine\input.h"
#include "..\Engine\GameTimes.h"

#include "..\GameObject\GameObject.h"

#include "..\Scene\Scene.h"

//*****************************************************************************
//
// クラス宣言
//
//*****************************************************************************
class CameraController : public Component
{
private:
	float				mOffsetFromTargetMin  = 5.0f;								// プレーヤーとカメラの偏り(半径)の最小値
	float				mOffsetFromTargetMax  = 9.0f;								// プレーヤーとカメラの偏り(半径)の最大値
	float				mVerticalRadiansMin   = cosf(D3DXToRadian(65.0f));			// カメラの垂直角度の最小値
	float				mVerticalRadiansMax   = cosf(D3DXToRadian(-15.0f));			// カメラの垂直角度の最大値
	float				mHorizonalRotateSpeed = 4.0f;
	float				mVerticalRotateSpeed  = 2.0f;
	float				mZoomSpeed            = 0.6f;
	float				mMoveSpeed            = 0.3f;
	int					mMouseIsMoving        = 5;
	D3DXVECTOR3			mOffsetFromTarget;

public:
	Camera*				mSceneCurrentCamera;

	CameraController(void);
	~CameraController(void);

	void start(void);
	void update(void);
	void drawImGui(void);

	void inputUpdate(void);
	void zoom(float distance);										// ズーム調整
	void rotation(float verticalRadians, float horizonalRadians);	// 回転
	void move(float sign, bool isVertical);							// 移動

};
#endif // !_CAMERA_H_