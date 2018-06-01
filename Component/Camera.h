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

#include "..\Engine\Engine.h"

//*****************************************************************************
//
// クラス宣言
//
//*****************************************************************************
class Camera : public Component
{
private:
	float			mField;						// ビューイングの視野角
	float			mRatio;						// アスペクト比
	float			mRangeStart;				// NearZ値
	float			mRangeEnd;					// FarZ値

public:
	bool			mIsVerticalLimited;			// カメラ垂直角度制限されたかどうかをチェック
	bool			mIsZoomLimited;				// カメラズームされたかどうかをチェック
	D3DXVECTOR3		mCameraFront;				// カメラの注視方向ベクトル
	D3DXVECTOR3		mCameraRight;				// カメラの右方向ベクトル
	D3DXVECTOR3		mCameraUp;					// カメラの上方向ベクトル

	D3DXVECTOR3		mCameraPos;
	D3DXVECTOR3		mTargetPos;
	D3DXMATRIX		mViewMatrix;
	D3DXMATRIX		mProjectionMatrix;

	Camera(void);
	~Camera(void);

	void start(void);
	void update(void);
	void drawImGui(void);
};
#endif // !_CAMERA_H_