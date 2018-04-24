//*****************************************************************************
//
// カメラ処理 [Camera.h]
//
// Author : LIAO HANCHEN
//
//*****************************************************************************
#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "Component.h"
#include "Transform.h"
#include "../Engine/Engine.h"
#include "../Engine/DebugMessage.h"

//*****************************************************************************
//
// クラス宣言
//
//*****************************************************************************
class Camera : public Component
{
private:
	float mField;											// ビューイングの視野角
	float mRatio;											// アスペクト比
	float mRangeStart;								// NearZ値
	float mRangeEnd;									// FarZ値

public:
	D3DXVECTOR3		mCameraPos;					// カメラの位置
	Transform*		mTargetTrans;				// 目標Transformを保存

	D3DXVECTOR3		mCameraFront;				// カメラの注視方向ベクトル
	D3DXVECTOR3		mCameraRight;				// カメラの右方向ベクトル
	D3DXVECTOR3		mCameraUp;					// カメラの上方向ベクトル

	D3DXMATRIX		mViewMatrix;					// ビューイング変換行列
	D3DXMATRIX		mProjectionMatrix;		// プロジェクション変換行列

	Camera();
	~Camera();

	void start();													// 初期化
	void update();													// 更新
};
#endif // !_CAMERA_H_