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
#include "..\Engine.h"
#include "..\DebugMessage.h"
#include "..\Shader\CelShader.h"

//*****************************************************************************
//
// クラス宣言
//
//*****************************************************************************
class Character
{
private:

public:
	DebugMessage*	message;		// Debugメッセージ

	Character();
	~Character();

	D3DXVECTOR3  MoveAlongVecLook(float speedCoefficient);	// 注視方向に沿って移動
	void PosToMessageAndMessageDraw(int row);	// 座標をメッセージに渡して、画面に描画する
	void SetWorldMatrix();						// ワールド変換を
	void RotationVecUp(float angle);			// 上方向のベクトルにして回転

	virtual void Update(float rot);						// キャラクター更新
	virtual void Draw(CelShader* celShader, D3DXMATRIX* VPMatrix);	// キャラクターの描画

	void InitCharacter();

	void Move();								// キャラクター移動
};
#endif // !_CHARACTER_H_

