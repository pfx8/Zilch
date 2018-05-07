//*****************************************************************************
//
// トゥーンシェーダー処理 [cekShader.fx]
//
// コンパイルはしない
//
// Author : LIAO HANCHEN
//
//*****************************************************************************
#include "publicValue.fx"
#include "lightingProcess.fx"
#include "outLine.fx"

//*****************************************************************************
//
// グローバル変数
//
//*****************************************************************************
// 骨行列集合
matrix boneMatrices[87];

// レンダリング選択
int renderType;

// ディフューズテクスチャサンプラー
// テクスチャ
texture tex;
// サンプラー
sampler texSampler = sampler_state
{
    Texture = <tex>;
    MipFilter = LINEAR;
    MinFilter = LINEAR;
    MagFilter = LINEAR;
    AddressU = WRAP;
    AddressV = WRAP;
};

//*****************************************************************************
//
// モデル頂点シェーダー処理
//
//*****************************************************************************
outputVS modelVS(inputVSWithBone iVS)
{
    // 戻り値を初期化
    outputVS oVS = (outputVS) 0;

    //// 骨によって頂点位置を計算
    //matrix boneTrans = boneMatrices[boneID[0]] * weight[0];
    //boneTrans += boneMatrices[boneID[1]] * weight[1];
    //boneTrans += boneMatrices[boneID[2]] * weight[2];
    //boneTrans += boneMatrices[boneID[3]] * weight[3];

    //// 頂点変換
    //float4 blendPos = mul(boneTrans, float4(pos, 1.0));
    //oVS.pos = mul(mul(mul(blendPos, worldMatrix), viewMatrix), projectionMatrix);
    //// 法線変更
    //oVS.nor = normalize(mul(float4(nor, 1.0), rotMatrix));

    // 頂点変換
    oVS.worldPos = mul(float4(iVS.pos, 1.0), worldMatrix);
    oVS.pos = mul(mul(oVS.worldPos, viewMatrix), projectionMatrix);
    // 法線変更
    oVS.nor = normalize(mul(float4(iVS.nor, 1.0), rotMatrix));
    // UV座標変更
    oVS.coord = iVS.coord;

    return oVS;
}

//*****************************************************************************
//
// モデルピクセルシェーダー処理
//
//*****************************************************************************
float4 modelPS(outputVS oVS) : COLOR
{
    float4 ambient;
    float4 diffuse;
    float4 specular;

    float4 lightDiffuse;

    // テクスチャによって色をつき
    float4 texColor = tex2D(texSampler, oVS.coord);
    // 法線の各分量を色として出す
    float4 normal = float4(oVS.nor.x, oVS.nor.y, oVS.nor.z, 1.0f);

    if (lightType == 0)
    {
        // 指向性ライト
        lightDiffuse = diffuseProcess(oVS.worldPos, oVS.nor) * lightColor;
        diffuse = diffuseProcess(oVS.worldPos, oVS.nor) * texColor;
    }
    else if (lightType == 1)
    {
        // ポイントライト
        lightDiffuse = attenuationProcess(oVS.worldPos) * lightColor;
        diffuse = attenuationProcess(oVS.worldPos) * texColor;

    }
    else if (lightType == 2)
    {
        // フラッシュライト

    }

    // 描画方法のを選択
    if(renderType == 0)
    {
        // RT_DIFFUSE
        return lightDiffuse;
    }
    else if(renderType == 1)
    {
        // RT_NORMAL
        return normal;
    }
    else if(renderType == 2)
    {
        // RT_TEXTURE
        return texColor;
    }

    // RT_SHADING -- デフォルト
    return diffuse;
}

//*****************************************************************************
//
// シェーダーテクニック
//
// FXファイル名前と同じ
//
//*****************************************************************************
technique celShading
{
    // outLine
    pass P0
    {
        // アルファブレンティング
        AlphaBlendEnable = FALSE;
        // フラットシェーディング
        ShadeMode = GOURAUD;
        // マルチ・サンプリングの設定
        MultiSampleAntialias = TRUE;
        // Zバッファ
        ZEnable = TRUE;
        // 背面カリング
        CullMode = CW; // ポリゴンの裏を表示
        
        VertexShader = compile vs_3_0 outLineVS();
        PixelShader = compile ps_3_0 outLinePS();
    }
    
    // モデル
    pass P1
    {
        // アルファブレンティング
        AlphaBlendEnable = FALSE;
        // マルチ・サンプリングの設定
        MultiSampleAntialias = TRUE;
        // フラットシェーディング
        ShadeMode = GOURAUD;
        // Zバッファ
        ZEnable = TRUE;
        // 背面カリング
        CullMode = CCW; // ポリゴンの表を表示
        
        VertexShader = compile vs_3_0 modelVS();
        PixelShader = compile ps_3_0 modelPS();
    }
}