//*****************************************************************************
//
// フォーンシェーダー処理 [phongShading.fx]
//
// コンパイルはしない
//
// Author : LIAO HANCHEN
//
//*****************************************************************************
matrix worldMatrix;            // ワールド変換行列
matrix viewMatrix;              // ビューイング変換行列
matrix projectionMatrix;     // プロジェクション変換行列

float3 lightDir; // ライト方向ベクトル
float4 lightColor; // ライトカラー

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
    float4 pos : POSITION0;
    float4 nor : NORMAL0;
    float2 coord : TEXCOORD0;
};

//*****************************************************************************
//
// 頂点シェーダー処理
//
//*****************************************************************************
VSout vertexShader(float3 pos : POSITION0,
             float3 nor : NORMAL0,
             float2 coord : TEXCOORD0)
{
    // 戻り値を初期化
    VSout vout = (VSout) 0;

    // 頂点変換
    vout.pos = mul(mul(mul(float4(pos, 1.0), worldMatrix), viewMatrix), projectionMatrix);
    // 法線変更
    vout.nor = mul(float4(nor, 1.0), worldMatrix);
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
    float4 color = float4(0.0, 0.0, 0.0, 0.0);

    // カラーを計算
    //color = float4(1.0, 0.0, 0.0, 1.0);
    color = tex2D(texSampler, vout.coord);

    return color;
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