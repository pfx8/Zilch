//*****************************************************************************
//
// キャラクターベース処理 [Character.cpp]
//
// Author : LIAO HANCHEN
//
//*****************************************************************************
#include "Character.h"

//*****************************************************************************
//
// コンストラクタ
//
//*****************************************************************************
Character::Character()
{
	m_upVector = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	m_lookVector = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
	m_rightVector = D3DXVECTOR3(1.0f, 0.0f, 0.0f);

	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_scl = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	//m_directionVector = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	r = 0.0f;

	// クラスポインタ
	m_model = new Model;
	m_message = new DebugMessage;
	m_boundingBox = new BoundingBox;
}

//*****************************************************************************
//
// デストラクタ
//
//*****************************************************************************
Character::~Character()
{
	// クラスポインタ
	RELEASE_CLASS_POINT(m_model);
	RELEASE_CLASS_POINT(m_message);
	RELEASE_CLASS_POINT(m_boundingBox);
}

//*****************************************************************************
//
// 座標をメッセージに渡して、画面に描画する
//
//*****************************************************************************
void Character::PosToMessageAndMessageDraw(int row)
{
	m_message->DrawPosMessage("Hero Pos", m_pos, D3DXVECTOR2(0, float(row * 18)));
	m_message->DrawPosMessage("H-look", m_lookVector, D3DXVECTOR2(0, float((row + 1) * 18)));
}

//*****************************************************************************
//
// 座標を設定
//
//*****************************************************************************
void Character::InitCharacter(D3DXVECTOR3 pos, D3DXVECTOR3 direction)
{
	m_pos = pos;	// 位置
	m_boundingBox->InitBox(3, 13, 3, 0.1f);	// バウンディングボックスを初期化
}

//*****************************************************************************
//
// キャラクターの描画
//
//*****************************************************************************
void Character::Draw(CelShader* celShader)
{
	m_model->DrawModel(celShader);	// メッシュを描画する

	if (m_boundingBox->m_isBoundingBoxDraw == true)
	{
		m_boundingBox->Draw(celShader);	// バウンディングボックスを描画する
	}
}

//*****************************************************************************
//
// キャラクター移動
//
//*****************************************************************************
void Character::Move()
{
	
}

//*****************************************************************************
//
// キャラクター更新
//
//*****************************************************************************
void Character::Update(float rot)
{
	r = rot;

	if (r > D3DX_PI * 2.0f)
		r = 0.0f;

	m_pos.y = 0.7 * sinf(r);
}

//*****************************************************************************
//
// 当たり判定
//
//*****************************************************************************
bool Character::CheckHitBB(Character* Object)
{
	D3DXVECTOR3 ObjectPos = Object->m_pos;
	D3DXVECTOR3 ObjectSize = Object->m_boundingBox->m_size;

	if (
		m_pos.x + m_boundingBox->m_size.x / 2 > ObjectPos.x - ObjectSize.x / 2 &&
		m_pos.x - m_boundingBox->m_size.x / 2 < ObjectPos.x + ObjectSize.x / 2 &&
		m_pos.y - m_boundingBox->m_size.y / 2 < ObjectPos.y + ObjectSize.y / 2 &&
		m_pos.y + m_boundingBox->m_size.y / 2 > ObjectPos.y - ObjectSize.y / 2 &&
		m_pos.z + m_boundingBox->m_size.z / 2 > ObjectPos.z - ObjectSize.z / 2 &&
		m_pos.z - m_boundingBox->m_size.z / 2 < ObjectPos.z + ObjectSize.z / 2
		)
	{
		return true;
	}
	else
	{
		return false;
	}
}

//*****************************************************************************
//
// 上方向のベクトルにして回転
//
//*****************************************************************************
void Character::RotationVecUp(float angle)
{
	if (m_rot.y > D3DX_PI * 2.0f || m_rot.y < -D3DX_PI * 2.0f)
	{
		m_rot.y = 0;
	}

	// 角度を記録する
	m_rot.y -= angle;

	// 新しい右方向ベクトルを計算する
	m_rightVector.x = cosf(m_rot.y);
	m_rightVector.z = sinf(m_rot.y);

	// 新しい注視方向ベクトルを計算する
	m_lookVector.x = cosf(m_rot.y + D3DX_PI / 2);
	m_lookVector.z = sinf(m_rot.y + D3DX_PI / 2);
}

//*****************************************************************************
//
// 注視方向に沿って移動
//
//*****************************************************************************
D3DXVECTOR3 Character::MoveAlongVecLook(float unit)
{
	m_pos += m_lookVector * unit;

	return m_lookVector * unit;
}

//*****************************************************************************
//
// ワールド変換を設定
//
//*****************************************************************************
void Character::SetWorldMatrix()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	D3DXMATRIX mtxScl, mtxRot, mtxTranslate;
	D3DXMatrixIdentity(&m_worldMatrix);

	// ワールドマトリックスの初期化
	D3DXMatrixIdentity(&m_worldMatrix);

	// スケールを反映
	D3DXMatrixScaling(&mtxScl, m_scl.x, m_scl.y, m_scl.z);
	D3DXMatrixMultiply(&m_worldMatrix, &m_worldMatrix, &mtxScl);

	// 回転を反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_worldMatrix, &m_worldMatrix, &mtxRot);

	// 移動を反映
	D3DXMatrixTranslation(&mtxTranslate, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_worldMatrix, &m_worldMatrix, &mtxTranslate);

	// ワールドマトリックスの設定
	//pDevice->SetTransform(D3DTS_WORLD, &m_worldMatrix);
}