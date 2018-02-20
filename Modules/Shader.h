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

public:
	ID3DXEffect*	effect;		// エフェクト
	D3DXHANDLE		technique;	// テクニック

	Shader();
	~Shader();

	HRESULT LoadEffectFile(std::string shaderName);		// 頂点シェーダーファイルを読み込む
};

#endif // !_SHADER_H_
