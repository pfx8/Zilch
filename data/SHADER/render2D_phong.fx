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
float3 lightAmbient;        // 光の環境値
float3 lightDiffuse;        // 光の拡散反射値
float3 lightSpecular;       // 光の鏡面反射値

float3 cameraPos;           // カメラの位置

texture tex; // テクスチャ
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
VSout vsMain(float3 pos : POSITION0,
             float3 nor : NORMAL0,
             float2 coord : TEXCOORD0)
{
    // 戻り値を初期化
    VSout vout = (VSout) 0;
    // 頂点を画面まで変更
    vout.pos = mul(mul(mul(float4(pos, 1.0), wMat), vMat), pMat);
    // 頂点を世界まで変更
    vout.worldPos = mul(float4(pos, 1.0), wMat);
    // 法線を世界まで変更、また正規化
    vout.nor = normalize(mul(float4(nor, 1.0), wMat));
    // UV座標変更
    vout.coord = coord;

    return vout;
}

//*****************************************************************************
//
// ピクセルシェーダー
//
//*****************************************************************************
float4 psMain(VSout vout, uniform bool isLighting) : COLOR
{
    float4 color = float4(0.0, 0.0, 0.0, 0.0);
    float4 texColor = tex2D(texSam, vout.coord);

    if (isLighting == false)
    {
        color = texColor;
    }
    else
    {
        // ambient
        color = texColor * 0.2f; // 本来のカラー

        // diffuse
        float3 L = lightPos - vout.worldPos;            // ライトから頂点までのベクトル
        float d = length(L);                            // ベクトルの長さを計算
        L /= d;                                         // ベクトルを正規化
        float attenuation = 1 / (lightAttenuation * d); // 光の減衰値
        float diffuse = saturate(dot(vout.nor, L));     // 計算した内積を0~1の範囲にクランプする
        color += texColor * diffuse * attenuation;      // カラーを足す

        // specular
        float3 V = normalize(vout.worldPos - cameraPos);                      // 頂点からカメラまでのベクトル
        float3 R = reflect(L, vout.nor);                                      // 入射光、サーフェイス法線を使用して屈折ベクトルを返します。
        float shininess = 64;                                                 // 大きくほどテカリが強いし、反射度が高いし、ハイライトが小さくなる
        float specular = pow(saturate(dot(R, V)), shininess) * diffuse * attenuation; // 視点と表面屈折ベクトルを内積して、また反射値を計算する
        color += float4(specular, specular, specular, 0);                     // カラーを足す
    }

    return color;
}

//*****************************************************************************
//
// レンダリングテクニック
//
//*****************************************************************************
technique render_without_light
{
    pass P0
    {
        VertexShader = compile vs_3_0 vsMain();
        PixelShader = compile ps_3_0 psMain(false);
    }
}

technique render_with_light
{
    pass P0
    {
        VertexShader = compile vs_3_0 vsMain();
        PixelShader = compile ps_3_0 psMain(true);
    }
}