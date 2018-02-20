//*****************************************************************************
//
// トゥ―ンシェーダー処理 [CelShader.h]
//
// Author : LIAO HANCHEN
//
//*****************************************************************************
#ifndef _SHADER_H_
#define _SHADER_H_

#include "../Engine.h"

class Shader
{
private:
	virtual HRESULT LoadEffectFile();					// 頂点シェーダーファイルを読み込む
	virtual void GetShaderTechniqueAndParameter();		// シェーダーを使うために、各設定をする

public:
	ID3DXEffect* m_effectPoint;		// エフェクト(複数レンダリング保存される)
	D3DXHANDLE   m_basicShaderHandle;	// エフェクトのテクニック
	D3DXHANDLE   m_WVPMatrixHandle;	// 変換行列
	//D3DXHANDLE   m_texture1Handle;	// テクスチャ

	Shader();
	~Shader();

	void InitShader();				// シェーダーを初期化する
};

#endif // !_SHADER_H_
