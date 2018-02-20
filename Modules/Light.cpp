//*****************************************************************************
//
// ライト処理 [Light.cpp]
//
// Author : LIAO HANCHEN
//
//*****************************************************************************
#include "Light.h"

//*****************************************************************************
//
// コンストラクタ
//
//*****************************************************************************
Light::Light()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 平行光源を初期化
	::ZeroMemory(&this->light, sizeof(this->light));	// this->light変数のメモリを初期化

	this->light.Type = D3DLIGHT_DIRECTIONAL;

	this->light.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);	// 拡散反射光(モデル本来のカラー)
	this->light.Specular = D3DXCOLOR(0.3f, 0.3f, 0.3f, 1.0f);	// 鏡面反射光

	this->light.Direction = D3DXVECTOR3(1.0f, -1.0f, 0.0f);		// 光の方向

	this->pos = D3DXVECTOR3(-1250.0f, 1250.0f, 0.0f);

	pDevice->SetLight(0, &this->light);
	pDevice->LightEnable(0, true);
}

//*****************************************************************************
//
// デストラクタ
//
//*****************************************************************************
Light::~Light()
{

}