//*****************************************************************************
//
// シャドーシェーダー[ShadowMapShader.h]
//
// Author : LIAO HANCHEN
//
//*****************************************************************************
#ifndef _SHADOW_MAP_SHADER_H_
#define _SHADOW_MAP_SHADER_H_

#include "../Modules/Shader.h"

class ShadowMapShader : public Shader
{
private:
	HRESULT LoadEffectFile();		// 頂点シェーダーファイルを読み込む

public:
	ID3DXEffect*		effectPoint;				// エフェクト(複数レンダリング保存される)
	LPDIRECT3DTEXTURE9	shadowMapTex;		// シャドーマップ
	D3DXHANDLE			shadeowMapShaderHandle;	// エフェクトのテクニック

	ShadowMapShader();
	~ShadowMapShader();

	HRESULT InitShader();	// シェーダーを初期化する
};

#endif // !_SHADOW_MAP_SHADER_H_
