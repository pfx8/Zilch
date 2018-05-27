//*****************************************************************************
//
// ライティング処理 [lightingProcess.fx]
//
// コンパイルはしない
//
// Author : LIAO HANCHEN
//
//*****************************************************************************
#ifndef _LIGHTING_PROCESS_H_
#define _LIGHTING_PROCESS_H_

//*****************************************************************************
//
// 変数声明
//
//*****************************************************************************
// ライトの基礎変数
float3  lightPos;    // ライト位置
float4  lightColor;  // ライトカラー
int     lightType;   // ライトタイプ

// 指向性ライト
float3 direction;  // ライトの方向

// ポイントライト　-- 減衰値
float  lightConstant;
float  lightLinear;
float  lightQuadratic;

// スポットライト
float  cutOff;    // スポットベクトルとライトベクトルのコサイン値
bool   isSmooth;  // スムースチェック

// カラーランプ選択
int colorRamp;
// セグメント値
float3 colorRampSegment;

//*****************************************************************************
//
// ライトディフューズ計算
//
//*****************************************************************************
float diffuseProcess(float4 lightDir, float3 normal)
{
    float diffuse;

    if(lightType == 0)
    {
        // 指向性ライトの場合
        diffuse = dot(-direction, normal);

        return diffuse;
    }

    // ライト方向ベクトルと法線の外積を計算その結果はdiffuseです
    // 外積の値がマイナスならばシャドウにする(0)
    // max(x, y) xとy のうちの大きい方の値を選択。マイナス値を防ぐ
    diffuse = max(0, dot(float4(normal, 1.0f), -lightDir));

    return diffuse;
}

//*****************************************************************************
//
// ポイントライトディフューズ
//
//*****************************************************************************
float attenuationProcess(float4 worldPos)
{
    float distance = length(float4(lightPos, 1.0f) - worldPos);
    float attenuation = 1.0f / (lightConstant + lightLinear * distance + lightQuadratic * (distance * distance));

    return attenuation;
}

//*****************************************************************************
//
// 一定ディフューズ計算
//
//*****************************************************************************
float constantDiffuse(float diff)
{
    float w = fwidth(diff) * 2.0;
    if (diff < colorRampSegment.x + w)
    {
        diff = lerp(colorRampSegment.x, colorRampSegment.y, smoothstep(colorRampSegment.x - w, colorRampSegment.x + w, diff));
    }
    else if (diff < colorRampSegment.y + w)
    {
        diff = lerp(colorRampSegment.y, colorRampSegment.z, smoothstep(colorRampSegment.y - w, colorRampSegment.y + w, diff));
    }
    else if (diff < colorRampSegment.z + w)
    {
        diff = lerp(colorRampSegment.z, 1.0, smoothstep(colorRampSegment.z - w, colorRampSegment.z + w, diff));
    }
    else
    {
        diff = 1.0;
    }

    return diff;
}

//*****************************************************************************
//
// 各種類のライトのディフューズを計算
//
//*****************************************************************************
float diffuseByLightType(float4 lightDir, float3 normal, float4 worldPos)
{
    // 結果ディフューズ
    float diff;

     // 指向性ライト
    if (lightType == 0)
    {
        // ディフューズ計算
        // リニアモード
        diff = diffuseProcess(lightDir, normal);

        if (colorRamp == 1)
        {
            // 一定モード
            diff = diff * 0.5 + 0.5;
            diff = constantDiffuse(diff);
        }
    }

    // ポイントライト
    else if (lightType == 1)
    {
        // ディフューズ計算
        // リニアモード
        diff = attenuationProcess(worldPos);

        if (colorRamp == 1)
        {
            // 一定モード
            diff = diff * 0.5 + 0.5;
            diff = constantDiffuse(diff);
        }
    }

    // スポットライト
    else if (lightType == 2)
    {
        // ディフューズ計算
        // リニアモード

        // 角度によって明るさを調整
        float theta = dot(lightDir, float4(normalize(-direction), 1.0));
        if (theta > cutOff)
        {
            // 光が差してる
            diff = diffuseProcess(lightDir, normal);
        }
        else
        {
            // ライトがない
            diff = float4(0, 0, 0, 1);
        }

        if (colorRamp == 1)
        {
            // 一定モード
            diff = diff * 0.5 + 0.5;
            diff = constantDiffuse(diff);
        }
    }

    return diff;
}

#endif // !_LIGHTING_PROCESS_H_