//*****************************************************************************
//
// キャラクターベース処理 [Character.h]
//
// Author : LIAO HANCHEN
//
//*****************************************************************************
#ifndef _CHARACTER_H_
#define _CHARACTER_H_

#include <map>

#include "Model.h"
#include "Sound.h"
#include "BoundingBox.h"
#include "..\Engine.h"
#include "..\DebugMessage.h"
#include "..\Shader\CelShader.h"


// 移動　= lookVector * SPEED_COEFFICIENT
#define MAX_BACK_SPEED_COEFFICIENT	(-0.28f)
#define MAX_FRONT_SPEED_COEFFICIENT	(0.38f)

#define MAX_HP						(3)

#define BULLET_TIME					(3.0f)

struct PlayerModel
{
	Model*			shipBody;
	Model*			shipCannon;
};

typedef enum
{
	LL_BACK = -1,	// [-1]後退
	LL_STOP,		// [0]停止
	LL_FRONT,		// [1]前進
}LEVER_LEVEL;

enum Border_Status
{
	BS_dotMinus,
	BS_dotplus,
};

//*****************************************************************************
//
// クラス宣言
//
//*****************************************************************************
class Character
{
private:
	bool			CheckMapBorder();	// マップから出るかどうかをチェック

public:
	D3DXMATRIX		worldMatrix;	// ワールド変換マトリックス
	D3DXMATRIX		lightMatrix;	// ライトマトリックス
	D3DXMATRIX		normalMatrix;	// ライトマトリックス

	LEVER_LEVEL		leverLevel;		// 船のレバー操作
	double			speed;			// スピードに関する倍数
	DebugMessage*	message;		// Debugメッセージ
	float			waveAngle;		// 揺れ係数

	// ベクトル
	D3DXVECTOR3		upVector;		// カメラの上方向ベクトル
	D3DXVECTOR3		lookVector;		// カメラの注視方向ベクトル
	D3DXVECTOR3		rightVector;	// カメラの右方向ベクトル

	// 固定属性
	D3DXVECTOR3		pos;			// 位置
	D3DXVECTOR3		rot;			// 回転
	D3DXVECTOR3		scl;			// 拡大縮小

	PlayerModel		player;			// プレーヤーモデル集合
	BoundingBox*	check;			// ダメージ用
	BoundingBox*	space;			// 空間用
	
	int				HP;

	float			leftTime;
	bool			leftShooting;
	float			rightTime;
	bool			rightShooting;

	bool			isBorder;
	Border_Status	borderStatus;

	Character();
	~Character();

	D3DXVECTOR3  MoveAlongVecLook(float speedCoefficient);	// 注視方向に沿って移動
	void PosToMessageAndMessageDraw(int row);	// 座標をメッセージに渡して、画面に描画する
	void SetWorldMatrix();						// ワールド変換を
	void ChangeLever(LEVER_LEVEL level);		// レバーの操作によってスピードを変わる
	bool CheckHitBB(Character* Object);			// 当たり判定
	void RotationVecUp(float angle);			// 上方向のベクトルにして回転

	virtual void Update(float rot);						// キャラクター更新
	virtual void Draw(CelShader* celShader, D3DXMATRIX* VPMatrix);	// キャラクターの描画

	void InitCharacter();

	void Move();								// キャラクター移動
};
#endif // !_CHARACTER_H_

