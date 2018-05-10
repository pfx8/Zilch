//*****************************************************************************
//
// シャドウマップ処理[ShadowMap.h]
//
// Author : LIAO HANCHEN
//
//*****************************************************************************
#ifndef _SHADOW_MAP_H_
#define _SHADOW_MAP_H_

#include "Engine.h"
#include "input.h"
#include "Shader.h"

#include "Model/Model.h"

//*****************************************************************************
//
// クラス宣言
//
//*****************************************************************************
class ShadowMap
{
private:
	
	LPDIRECT3DTEXTURE9		mShadowMap;			// シャドウマップのテクスチャ
	LPDIRECT3DSURFACE9      mShadowMapDepth;	// シャドウマップの深度バッファサーフェイス
	

	// ライトを中心にして変換行列を作る
	D3DXMATRIX				mTargetWVP;
	D3DXMATRIX				mLightView;
	D3DXMATRIX				mLightProjection;

	D3DXMATRIX				mShadowWVP;			// mTargetWVP * mLightView * mLightProjection

public:
	Shader*					mShader;
	unsigned int			mMapSize = 512;
	GameObject*				mShadowTarget;

	D3DXVECTOR3				mLightPos;
	D3DXVECTOR3				mLightAt;
	D3DXVECTOR3				mLightUp;

	ShadowMap(Shader* shader, D3DXVECTOR3 lightPos);
	~ShadowMap();

	void update();								// シャドウマップ更新
	void draw(Model* model);					// シャドウマップを描画
};

#endif // !_SHADOW_MAP_H_
