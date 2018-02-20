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

#include "Mesh.h"
#include "../Engine.h"
#include "../DebugMessage.h"

//*****************************************************************************
//
// クラス宣言
//
//*****************************************************************************
class Character
{
private:
	DX_MESH*			m_dxMesh;	// メッシュ
	float r;

	DebugMessage*	m_message;	// Debugメッセージ

public:
	D3DXMATRIX		m_worldMatrix;	// ワールド変換マトリックス

	// ベクトル
	D3DXVECTOR3		m_upVector;		// カメラの上方向ベクトル
	D3DXVECTOR3		m_lookVector;	// カメラの注視方向ベクトル
	D3DXVECTOR3		m_rightVector;	// カメラの右方向ベクトル

	// 固定属性
	D3DXVECTOR3		m_pos;		// 位置
	D3DXVECTOR3		m_rot;		// 回転
	D3DXVECTOR3		m_scl;		// 拡大縮小

	Character();
	~Character();

	void InitCharacter(D3DXVECTOR3 pos, D3DXVECTOR3 direction);		// 座標を設定

	void PosToMessageAndMessageDraw(int row);	// 座標をメッセージに渡して、画面に描画する
	void SetWorldMatrix();					// ワールド変換を設定
	void Draw(CelShader* celShader);			// キャラクターの描画(Shader)
	void Move();								// 臨時ーーキャラクター移動
	
	void Update(float rot);	// キャラクター更新
	bool CheckHitBB(Character* Object);	// 当たり判定

	void RotationVecUp(float angle);		// 上方向のベクトルにして回転
	D3DXVECTOR3  MoveAlongVecLook(float unit);	// 注視方向に沿って移動
};
#endif // !_CHARACTER_H_

