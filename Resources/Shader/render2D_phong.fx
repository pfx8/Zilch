//*****************************************************************************
//
// テストシェーダー処理 [test.fx]
//
// コンパイルはしない
//
// Author : LIAO HANCHEN
//
//*****************************************************************************
matrix wMat; // ワールド変換行列
matrix vMat; // ビューイング変換行列
matrix pMat; // プロジェクション変換行列

float lightAttenuation;     // 光の減衰値
float3 lightPos;            // 光の位置
float4 lightAmbient;        // 光の環境値
float4 lightDiffuse;        // 光の拡散反射値
float4 lightSpecular;       // 光の鏡面反射値

float3 cameraPos;           // カメラの位置

texture tex;     // テクスチャ
sampler texSam = // サンプラー
sampler_state
{
    Texture = <tex>;
    MipFilter = LINEAR;
    MinFilter = LINEAR;
    MagFilter = LINEAR;
    AddressU = WRAP;
    AddressV = WRAP;
};

texture normalMap;
sampler normalMapSam = // サンプラー
sampler_state
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
// プロトタイプ宣言
//
//*****************************************************************************
struct VSout
{
    float4 pos : POSITION0;
    float2 coord : TEXCOORD0;
    float3 worldPos : TEXCOORD1;
    float3 nor : TEXCOORD02;
};

//*****************************************************************************
//
// 頂点シェーダー
//
//*****************************************************************************
VSout vsMain(float3 pos     : POSITION0,
             float3 nor     : NORMAL0,
             float2 coord   : TEXCOORD0,
             float3 tangent : TANGENT)
{
    // 戻り値を初期化
    VSout vout = (VSout) 0;
    // 頂点を画面まで変更
    vout.pos = mul(mul(mul(float4(pos, 1.0), wMat), vMat), pMat);
    // 頂点を世界まで変更
    vout.worldPos = mul(float4(pos, 1.0), wMat);
    // 法線を世界まで変更、また正規化
    vout.nor = normalize(mul(float4(nor, 1.0), wMat));
    //vout.nor = nor;
    // UV座標変更
    vout.coord = coord;

    return vout;
}

//*****************************************************************************
//
// ピクセルシェーダー
//
//*****************************************************************************
float4 psMain(VSout vout, uniform int rendertype) : COLOR
{
    float4 color = float4(0.0, 0.0, 0.0, 0.0);
    float4 texColor = tex2D(texSam, vout.coord);

    if(rendertype == 0 /*with diffuse*/)
    {
        color = texColor;
    }
    else if (rendertype == 1 /*with light*/)
    {
        // ambient = lightColor * lightStrength * ambientStrength
        float4 ambient = lightDiffuse * 1.5 * 0.6;
        color += ambient;

        // diffuse
        float3 L = lightPos - vout.worldPos; // ライトから頂点までのベクトル
        float d = length(L); // ベクトルの長さを計算
        L /= d; // ベクトルを正規化
        float attenuation = 1 / (lightAttenuation * d); // 光の減衰値
        float diffuse = saturate(dot(vout.nor, L)); // 計算した内積を0~1の範囲にクランプする

        // specular
        float3 V = normalize(vout.worldPos - cameraPos); // 頂点からカメラまでのベクトル
        float3 R = reflect(L, vout.nor); // 入射光の向きとサーフェイス法線を使用して反射ベクトルを返します。
        int shininess = 8; // 大きくほどテカリが強いし、反射度が高いし、ハイライトが小さくなる
        float specular = pow(saturate(dot(R, V)), shininess); // 視点と表面屈折ベクトルを内積して、また反射値を計算する
        
        // 最終カラー
        color = (diffuse + specular) * texColor * attenuation;
        color.w = 1.0;
    }
    else if (rendertype == 2 /*with light & normal map*/)
    {
        // 法線を読み込み
        float3 normal = tex2D(normalMapSam, vout.coord).rgb;
        normal = normalize(normal * 2.0 - 1.0);
        normal.z = -1 * normal.z;

       // ambient = lightColor * lightStrength * ambientStrength
        float4 ambient = lightDiffuse * 1.5 * 0.6;
        color += ambient;

        // diffuse
        float3 L = lightPos - vout.worldPos; // ライトから頂点までのベクトル
        float d = length(L); // ベクトルの長さを計算
        L /= d; // ベクトルを正規化
        float attenuation = 1 / (lightAttenuation * d); // 光の減衰値
        float diffuse = saturate(dot(normal, L)); // 計算した内積を0~1の範囲にクランプする

        // specular
        float3 V = normalize(vout.worldPos - cameraPos); // 頂点からカメラまでのベクトル
        float3 R = reflect(L, normal); // 入射光の向きとサーフェイス法線を使用して反射ベクトルを返します。
        int shininess = 8; // 大きくほどテカリが強いし、反射度が高いし、ハイライトが小さくなる
        float specular = pow(saturate(dot(R, V)), shininess); // 視点と表面屈折ベクトルを内積して、また反射値を計算する
        
        // 最終カラー
        color = (diffuse + specular) * texColor * attenuation;
        color.w = 1.0;
    }

    return color;
}

//*****************************************************************************
//
// レンダリングテクニック
//
// FXファイル名前と同じ
//
//*****************************************************************************
technique render_without_light
{
    pass P0
    {
        VertexShader = compile vs_3_0 vsMain();
        PixelShader = compile ps_3_0 psMain(0);
    }
}

technique render_with_light
{
    pass P0
    {
        VertexShader = compile vs_3_0 vsMain();
        PixelShader = compile ps_3_0 psMain(1);
    }
}

technique render_with_normalMap
{
    pass P0
    {
        VertexShader = compile vs_3_0 vsMain();
        PixelShader = compile ps_3_0 psMain(2);
    }
}