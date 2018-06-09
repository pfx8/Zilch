//*****************************************************************************
//
// シャドウマップ処理[ShadowMap.h]
//
// Author : LIAO HANCHEN
//
//*****************************************************************************
#include "ShadowMap.h"

//*****************************************************************************
//
// コンストラクタ
//
//*****************************************************************************
ShadowMap::ShadowMap(Shader* shader, D3DXVECTOR3 lightPos)
{
	// 各初期化
	this->mShader = shader;
	this->mLightPos = mLightPos;
	this->mLightAt = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	this->mLightUp = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	HRESULT result;
	// シャドウマップテクスチャを作る
	result = D3DXCreateTexture(getD3DDevice(), this->mMapSize, this->mMapSize, 1, D3DUSAGE_RENDERTARGET, D3DFMT_R32F, D3DPOOL_DEFAULT, &this->mShadowMap);
	//シャドウマップ深度バッファサーフェイスを作る
	result = getD3DDevice()->CreateDepthStencilSurface(this->mMapSize, this->mMapSize, D3DFMT_D16, D3DMULTISAMPLE_NONE, 0, TRUE, &this->mShadowMapDepth, NULL);
}

//*****************************************************************************
//
// デストラクタ
//
//*****************************************************************************
ShadowMap::~ShadowMap()
{
	RELEASE_POINT(this->mShadowMap);
	RELEASE_POINT(this->mShadowMapDepth);
}

//*****************************************************************************
//
// シャドウマップ更新
//
//*****************************************************************************
void ShadowMap::update()
{
	// ライトによりのビューイング変換
	D3DXMatrixLookAtLH(&this->mLightView, &this->mLightPos, &this->mLightAt, &this->mLightUp);

	// プロジェクション変換
	D3DXMatrixPerspectiveFovLH(&this->mLightProjection, D3DXToRadian(45), 1.0f, 1.0f, 1024.0f);

	// シャドウマップ用WVP計算
	this->mShadowWVP = this->mTargetWVP * this->mLightView * this->mLightProjection;
}

//*****************************************************************************
//
// シャドウマップを描画
//
//*****************************************************************************
void ShadowMap::draw(Model* model)
{
	// シャドウマップのサーフェイスを取得
	LPDIRECT3DSURFACE9 renderTarget;
	this->mShadowMap->GetSurfaceLevel(0, &renderTarget);

	// 前のレンダリングターゲットを保存
	LPDIRECT3DSURFACE9 oldRenderTarget;
	getD3DDevice()->GetRenderTarget(0, &oldRenderTarget);
	// シャドウマップを新しいレンダリングターゲットに設定
	getD3DDevice()->SetRenderTarget(0, renderTarget);

	// 深度バッファも交換
	LPDIRECT3DSURFACE9 oldDepth;
	getD3DDevice()->GetDepthStencilSurface(&oldDepth);
	getD3DDevice()->SetDepthStencilSurface(this->mShadowMapDepth);

	// バックバッファ＆Ｚバッファのクリア
	getD3DDevice()->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(255, 0, 0), 1.0f, 0);

	// シャドウマップを描画
	this->mShader->mEffect->SetMatrix("worldViewProjectionShadow", &this->mShadowWVP);
	model->drawShadow(this->mShader);

	// 保存シャドウマップ
	if (GetKeyboardTrigger(DIK_F6))			// key F6
	{
		D3DXSaveTextureToFile(L"shadowMap.jpg", D3DXIFF_JPG, this->mShadowMap, NULL);
	}

	// シャドウマップ作った後で、元のレンダリングターゲットと深度バッファに戻す
	getD3DDevice()->SetRenderTarget(0, oldRenderTarget);
	getD3DDevice()->SetDepthStencilSurface(oldDepth);

	// リリースシャドウマップに関するポインタ
	RELEASE_POINT(oldRenderTarget);
	RELEASE_POINT(oldDepth);
	RELEASE_POINT(renderTarget);
}