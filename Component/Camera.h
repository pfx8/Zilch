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
	float						field;										// ビューイングの視野角
	float						ratio;										// アスペクト比
	float						rangeStart;								// NearZ値
	float						rangeEnd;								// FarZ値

public:
	D3DXVECTOR3		cameraPos;					// カメラの位置
	Transform*				targetTrans;				// 目標Transformを保存

	D3DXVECTOR3		cameraFront;				// カメラの注視方向ベクトル
	D3DXVECTOR3		cameraRight;				// カメラの右方向ベクトル
	D3DXVECTOR3		cameraUp;					// カメラの上方向ベクトル

	D3DXMATRIX			viewMatrix;					// ビューイング変換行列
	D3DXMATRIX			projectionMatrix;		// プロジェクション変換行列

	Camera();
	~Camera();

	void start();														// 初期化
	void update();													// 更新
};
#endif // !_CAMERA_H_