//*****************************************************************************
//
// トゥ―ンシェーダー処理 [CelShader.h]
//
// Author : LIAO HANCHEN
//
//*****************************************************************************
#ifndef _CEL_SHADER_H_
#define _CEL_SHADER_H_

#include "../Modules/Shader.h"

class CelShader : public Shader
{
private:
	HRESULT LoadEffectFile();					// 頂点シェーダーファイルを読み込む
	void GetShaderParameter();		// シェーダーを使うために、各設定をする

public:
	ID3DXEffect*		effectPoint;		// エフェクト(複数レンダリング保存される)
	D3DXHANDLE			celShaderHandle;	// エフェクトのテクニック
	D3DXHANDLE			WMatrixHandle;	// ワールド変換
	D3DXHANDLE			VPMatrixHandle;	// ビューイング変換とプロジェクション変換
	D3DXHANDLE			lightingHandle;	// 光の方向
	D3DXHANDLE			typeHandle;		// オブジェクトの種類を判断

	CelShader();
	~CelShader();

	void InitShader();						// シェーダーを初期化する
};

#endif // !_CEL_SHADER_H_
