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

#include "publicValue.fx"

//*****************************************************************************
//
// 変数声明
//
//*****************************************************************************
// ライトの基礎変数
float3  lightPos;      // ライト位置
float4  lightColor;    // ライトカラー
int     lightType;     // ライトタイプ
float   lightStrength; // ライト強度
float   lightAmbient;  // ライトアンビエント
float   lightDiffuse;  // ライトディフューズ
float   lightSpecular; // ライトスペキュラー

// 指向性ライト
float3 direction;  // ライトの方向

// ポイントライト　-- 減衰値
float  lightConstant;
float  lightLinear;
float  lightQuadratic;

// スポットライト
float  cutOff;    // スポットベクトルとライトベクトルのコサイン値
bool   isSmooth;  // スムースチェック

// カラーランプ
int colorRampType;        // カラーランプタイプ
float3 colorRampSegment;  // セグメント値

//*****************************************************************************
//
// アンビエント
//
//*****************************************************************************
float3 ambientProcess()
{
    float3 ambient;

    if (matAmibent.r == 0.0 && matAmibent.g == 0.0 && matAmibent.b == 0.0)
    {
        ambient = lightAmbient * lightColor.rgb;
    }
    else
    {
        ambient = lightAmbient * matAmibent * lightColor.rgb;
    }

    return ambient;
}

//*****************************************************************************
//
// ディフューズ
//
// max(x, y) xとy のうちの大きい方の値を選択。マイナス値を防ぐ
// saturate(x) xを0~1の範囲にクランプ
//
//*****************************************************************************
float diffuseProcess(float4 lightDir, float3 normal)
{
    float diff;

    if(lightType == 0)
    {
        // 指向性ライトの場合
        //diff = max(dot(normal, direction), 0.0);
        diff = saturate(dot(normal, direction));
    }
    else
    {
        //diff = max(dot(float4(normal, 1.0), lightDir), 0.0);
        diff = saturate(dot(float4(normal, 1.0), lightDir));
    }

    return diff;
}

//*****************************************************************************
//
// スペキュラー
//
// max(x, y) xとy のうちの大きい方の値を選択。マイナス値を防ぐ
//
//*****************************************************************************
float3 specularProcess(float4 cameraDir, float4 lightDir, float3 normal)
{
    float3 specular;
    float  spec;

    // Phong
    //float4 reflectDir = reflect(-lightDir, float4(normal, 1.0));
    //spec = pow(max(dot(cameraDir, reflectDir), 0.0), shininess);

    // Blinn-Phong
    float4 halfwayDir = normalize(lightDir + cameraDir);
    //spec = pow(max(dot(normal, halfwayDir.rgb), 0.0), shininess);
    spec = pow(saturate(dot(normal, halfwayDir.rgb)), shininess);

    specular = lightSpecular * (spec * matSpecular) * lightStrength;

    return specular;
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
float3 diffuseByLightType(float4 lightDir, float3 normal, float4 worldPos)
{
    float3 diffuse;
    float diff;

    // ディフューズ計算
    if (lightType == 0)
    {
        // 指向性ライト
        diff = diffuseProcess(lightDir, normal);
    }
    else if (lightType == 1)
    {
        // ポイントライト
        diff = diffuseProcess(lightDir, normal) * attenuationProcess(worldPos);
    }
    else if (lightType == 2)
    {
        // スポットライト
        // ライトと光方向の角度
        float theta = dot(lightDir, float4(normalize(-direction), 1.0));
        if (theta > cutOff)
        {
            // 光が差してる
            diff = diffuseProcess(lightDir, normal);
        }
        else
        {
            // ライトがない
            diff = float4(0.0, 0.0, 0.0, 1.0);
        }
    }

    // 一定モードならば
    if (colorRampType == 1)
    {
        //diff = diff * 0.5 + 0.5;
        diff = constantDiffuse(diff);
    }

    diffuse = float3(diff, diff, diff) * matDiffuse * lightDiffuse * lightStrength;

    return diffuse;
}

#endif // !_LIGHTING_PROCESS_H_