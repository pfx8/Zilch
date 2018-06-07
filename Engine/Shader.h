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
enum RenderingMode
{
	RM_TEXTURE,			// テクスチャ
	RM_DIFFUSE,			// ディフューズ
	RM_SPECULAR,		// スペキュラー
	RM_NORMAL,			// 法線
	RM_SHADING,			// シェーディング
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
	RenderingMode	mRenderingMode;				// レンダリングモード
	ColorRamp		mColorRampType;				// カラーランプモード
	D3DXVECTOR3		mColorRampSegment;			// カラーセグメント値、最大は３レベル
	float			mSpecularColorSegment;		// スペキュラーセグメント値、0.0 ~ 1.0

	Shader(wstring path);
	~Shader(void);

	HRESULT loadEffectFile(wstring path);		// 頂点シェーダーファイルを読み込む
};

#endif // !_SHADER_H_
