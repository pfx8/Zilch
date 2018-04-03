//*****************************************************************************
//
// トゥ―ンシェーダー処理 [CelShader.h]
//
// Author : LIAO HANCHEN
//
//*****************************************************************************
#ifndef _SHADER_H_
#define _SHADER_H_

#include "Engine.h"

class Shader
{
private:

public:
	ID3DXEffect*	mEffect;		// エフェクト

	Shader(string path);
	~Shader();

	HRESULT loadEffectFile(string path);		// 頂点シェーダーファイルを読み込む
};

#endif // !_SHADER_H_
