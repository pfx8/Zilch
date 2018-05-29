//*****************************************************************************
//
// アウトライン処理 [outLine.fx]
//
// コンパイルはしない
//
// Author : LIAO HANCHEN
//
//*****************************************************************************
#ifndef _OUTLINE_FX_
#define _OUTLINE_FX_

#include "publicValue.fx"
#include "lightingProcess.fx"

//*****************************************************************************
//
// グローバル変数
//
//*****************************************************************************
// アウトラインを描画する時、頂点ベクトルと法線ベクトルんを混ざる因子数
float outLineFactor = 0.2f;

// アウトラインの太さをコントロール因子
float outLineStr = 0.01f;

//*****************************************************************************
//
// outLine頂点シェーダー処理
//
//*****************************************************************************
outputVS outLineVS(inputVS iVS)
{
    // 戻り値を初期化
    outputVS oVS = (outputVS) 0;

    // outLine方向ベクトルを計算
    // まずは頂点の方向ベクトルを計算
    float3 outLineDir = normalize(iVS.pos);
    // 頂点の方向ベクトルと法線ベクトルの外積を計算
    float D = dot(outLineDir, iVS.nor);
    // outLineの最終向きを計算
    outLineDir *= sign(D);
    outLineDir = outLineDir * outLineFactor + iVS.nor * (1 - outLineFactor);
    // 頂点 + outLine方向ベクト * outLine太さ因数 = outLine頂点の場所
    float3 outLinePos = iVS.pos + outLineDir * outLineStr;

    // 頂点変換
    oVS.worldPos = mul(float4(outLinePos, 1.0), worldMatrix);
    oVS.pos = mul(mul(oVS.worldPos, viewMatrix), projectionMatrix);

    // 法線変更
    oVS.nor = mul(float4(iVS.nor, 1.0), worldMatrix);
    // UV座標変更
    oVS.coord = iVS.coord;

    return oVS;
}

//*****************************************************************************
//
// outLineピクセルシェーダー処理
//
//*****************************************************************************
float4 outLinePS(outputVS oVS) : COLOR
{
    // outLineカラーを設定
    return float4(0.0f, 0.0f, 0.0f, 1.0f);
}

#endif // !_PUBLIC_VALUE_FX_