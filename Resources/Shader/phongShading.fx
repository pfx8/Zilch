//*****************************************************************************
//
// フォーンシェーダー処理 [phongShading.fx]
//
// コンパイルはしない
//
// Author : LIAO HANCHEN
//
//*****************************************************************************
matrix worldMatrix;             // ワールド変換行列
matrix viewMatrix;              // ビューイング変換行列
matrix projectionMatrix;        // プロジェクション変換行列

float3 lightPos; // ライト位置
float4 lightColor; // ライトカラー
// ライト減衰プロパティ
float lightConstant;
float lightLinear;
float lightQuadratic;

texture tex;                                   // テクスチャ
sampler texSampler =                // サンプラー
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
    float4 pos : POSITION;
    float3 nor : NORMAL;
    float2 coord : TEXCOORD0;
    float4 worldPos : TEXCOORD1;
};

//*****************************************************************************
//
// 頂点シェーダー処理
//
//*****************************************************************************
VSout vertexShader(float3 pos : POSITION,
             float3 nor : NORMAL,
             float2 coord : TEXCOORD)
{
    // 戻り値を初期化
    VSout vout = (VSout) 0;

    // 頂点変換
    vout.worldPos = mul(float4(pos, 1.0), worldMatrix);
    vout.pos = mul(mul(vout.worldPos, viewMatrix), projectionMatrix);
    // 法線変更
    vout.nor = normalize(mul(float4(nor, 1.0), worldMatrix));
    // UV座標変更
    vout.coord = coord;

    return vout;
}

//*****************************************************************************
//
// ピクセルシェーダー処理
//
//*****************************************************************************
float4 pixelShader(VSout vout) : COLOR
{
    // ライト方向ベクトルを計算
    float4 lightDir = normalize(float4(lightPos, 1.0f) - vout.worldPos);
    // テクスチャからカラーを取得
    float4 texColor = tex2D(texSampler, vout.coord);
    float diffuse = max(0, dot(float4(vout.nor, 1.0f), -lightDir));

    // ライト減衰値を計算
    float distance = length(float4(lightPos, 1.0f) - vout.worldPos);
    float attenuation = 1.0 / (lightConstant + lightLinear * distance + lightQuadratic * distance * distance);
    float4 attColor = attenuation * lightColor;
    

    //return lightDir;
    //return texColor;
    //return float4(diffuse, diffuse, diffuse, diffuse);
    return float4(attenuation, attenuation, attenuation, attenuation);
}

//*****************************************************************************
//
// シェーダーテクニック
//
//*****************************************************************************
technique phongShading
{
    pass P0
    {
        // フラットシェーディング
        ShadeMode = FLAT;
        // Zバッファ
        ZEnable = TRUE;
        // 背面カリング
        CullMode = CCW;     // ポリゴンの表を表示
        // アルファブレンティング
        AlphaBlendEnable = TRUE;
        
        VertexShader = compile vs_3_0 vertexShader();
        PixelShader = compile ps_3_0 pixelShader();
    }
}