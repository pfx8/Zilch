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
    //float4 diffuse;
    //float4 specular;
    float4 finColor;

    float4 ambient = float4(0.3, 0.3, 0.3, 1.0);

    // ライトベクトルを計算
    float4 lightDir = normalize(float4(lightPos, 1.0f) - oVS.worldPos);
    // ビューベクトル
    float4 viewDir = float4(cameraPos, 1.0) - oVS.worldPos;
    //
    float4 halfDir = normalize(lightDir + viewDir);

    float4 specular = float4(0.0, 1.0, 0.0, 1.0);

    // スペキュラー計算
    float spec = max(0, dot(float4(oVS.nor, 1.0f), halfDir));
    spec = pow(spec, shininess);
    float w = fwidth(spec) * 2.0;
    if (spec < 0.5 + w)
    {
        spec = lerp(0, 1, smoothstep(0.5 - w, 0.5 + w, spec));
    }
    else
    {
        spec = 1;
    }

    // ライトによってディフューズを計算
    float diff = diffuseByLightType(lightDir, oVS.nor, oVS.worldPos);

    // テクスチャによって色をつき
    float4 texColor = tex2D(texSampler, oVS.coord);
    // 法線の各分量を色として出す
    float4 normal = float4(oVS.nor.x, oVS.nor.y, oVS.nor.z, 1.0f);
    // ディフューズ
    float4 diffuse = diff * lightColor * texColor;
    // スペキュラー
    //float4 specular = spec * lightColor * texColor;

    // 描画方法のを選択
    if(renderingMode == 0)
    {
         // RM_TEXTURE
        return texColor;
    }
    else if (renderingMode == 1)
    {
        // RM_DIFFUSE
        //diffuse = diff * lightColor;
        //diffuse.w = 1.0;
        //return diffuse;

        float lightStrength = 0.1;
        float4 ambient1 = lightStrength * lightColor;

        float4 lightDir = normalize(float4(lightPos, 1.0) - oVS.worldPos);
        float diff = max(dot(float4(oVS.nor, 1.0), lightDir), 0.0);
        float4 diffuse1 = diff * lightColor;

        float4 cameraDir = normalize(float4(cameraPos, 1.0) - oVS.worldPos);
        float4 reflectDir = reflect(-lightDir, float4(oVS.nor, 1.0));
        float specular1 = pow(max(dot(cameraDir, reflectDir), 0.0), 128);

        finColor = (ambient + diffuse1 + specular1) * float4(1.0, 0.0, 0.0, 1.0);
        finColor.w = 1.0;

        return finColor;
    }
    else if (renderingMode == 2)
    {
        // RM_SPECULAR
        return specular;
    }
    else if(renderingMode == 3)
    {
        // RM_NORMAL
        return normal;
    }

    // RT_SHADING -- シェーディング
    float4 fin = diffuse /*+ specular*/ + ambient;

    // 目テクスチャだけを透明
    if(texColor.w != 0.0)
    {
        fin.w = 1.0;
    }

    return fin;
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