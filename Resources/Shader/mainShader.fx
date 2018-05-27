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
#include "outLineProcess.fx"

//*****************************************************************************
//
// グローバル変数
//
//*****************************************************************************
// 骨行列集合
matrix boneMatrices[87];

// レンダリング選択
int renderingMode;

//*****************************************************************************
//
// サンプラー
//
//*****************************************************************************
// ディフューズテクスチャ
texture tex;
// ディフューズテクスチャサンプラー
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
    oVS.nor = normalize(mul(float4(iVS.nor, 1.0), norMatrix));
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
    // 基本変数を用意する
    float3 ambient;
    float3 specular;
    float3 diffuse;
    float4 finColor;

    float4 lightDir = normalize(float4(lightPos, 1.0f) - oVS.worldPos);
    float4 cameraDir = float4(cameraPos, 1.0) - oVS.worldPos;
    float4 normalColor = float4(oVS.nor.x, oVS.nor.y, oVS.nor.z, 1.0f);
    float4 texColor = tex2D(texSampler, oVS.coord);

    // 各分量を計算
    ambient = ambientProcess();
    diffuse = diffuseProcess(lightDir, oVS.nor);
    specular = specularProcess(cameraDir, lightDir, oVS.nor);

    // ライトによってディフューズを計算
    float diff = diffuseByLightType(lightDir, oVS.nor, oVS.worldPos);

    // 各レンダリングモード
    if(renderingMode == 0)
    {
        // RM_TEXTURE
        finColor = texColor;
    }
    else if (renderingMode == 1)
    {
        // RM_DIFFUSE
        finColor = float4(diffuse, 1.0);
    }
    else if (renderingMode == 2)
    {
        // RM_SPECULAR
        finColor = float4(specular, 1.0);
    }
    else if(renderingMode == 3)
    {
        // RM_NORMAL
        finColor = normalColor;
    }
    else
    {
        // RT_SHADING
        finColor = float4((ambient + diffuse + specular), 1.0) * texColor;
    }

    return finColor;
}

//*****************************************************************************
//
// シェーダーテクニック
//
// FXファイル名前と同じ
//
//*****************************************************************************
technique mainShader
{
    // outLine
    pass P0
    {
        // アルファブレンティング
        AlphaBlendEnable = FALSE;
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
        AlphaBlendEnable = TRUE;
        // 目透明合成
        DestBlend = InvSrcAlpha;
        SrcBlend = SrcAlpha;
        // マルチ・サンプリングの設定
        MultiSampleAntialias = TRUE;
        // Zバッファ
        ZEnable = TRUE;
        // 背面カリング
        CullMode = CCW; // ポリゴンの表を表示
        
        VertexShader = compile vs_3_0 modelVS();
        PixelShader = compile ps_3_0 modelPS();
    }
}