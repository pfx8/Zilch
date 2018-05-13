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

//*****************************************************************************
//
//  列挙体定義
//
//*****************************************************************************
enum RenderMode
{
	RT_DIFFUSE,			// ディフューズ
	RT_NORMAL,			// 法線
	RT_TEXTURE,			// テクスチャ
	RT_SHADING,			// シェーディング
};

enum ColorRamp
{
	CR_LINEAR,			// リニア
	CR_CONSTANT,		// 一定
};

//*****************************************************************************
//
// クラス宣言
//
//*****************************************************************************
class Shader
{
private:

public:
	ID3DXEffect*	mEffect;					// エフェクト
	RenderMode		mRenderMode;				// レンダリングモード
	ColorRamp		mColorRamp;					// カラーランプモード
	D3DXVECTOR3		mColorRampSegment;			// カラーセグメント値、最大は３レベル

	Shader(wstring path);
	~Shader();

	HRESULT loadEffectFile(wstring path);		// 頂点シェーダーファイルを読み込む
};

#endif // !_SHADER_H_
