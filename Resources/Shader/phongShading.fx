//*****************************************************************************
//
// テストシェーダー処理 [test.fx]
//
// コンパイルはしない
//
// Author : LIAO HANCHEN
//
//*****************************************************************************
float4 worldMatrix;            // ワールド変換行列
float4 viewMatrix;              // ビューイング変換行列
float4 projectionMatrix;    // プロジェクション変換行列

texture diffuse;                                   // テクスチャ
sampler diffuseSampler =                // サンプラー
sampler_state
{
    Texture = <diffuse>;
    MipFilter = LINEAR;
    MinFilter = LINEAR;
    MagFilter = LINEAR;
    AddressU = WRAP;
    AddressV = WRAP;
};

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
VSout vertexShader(float3 pos : POSITION,
             float3 nor : NORMAL,
             float2 coord : TEXCOORD)
{
    // 戻り値を初期化
    VSout vout = (VSout) 0;

    // 頂点変更
    float4 vtx = mul(float4(pos, 1.0), worldMatrix);
    vtx = mul(vtx, viewMatrix);
    vtx = mul(vtx, projectionMatrix);
    vout.pos = vtx;

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
    color = float4(1.0, 0.0, 0.0, 1.0);
    //color = tex2D(diffuseSampler, vout.coord);

    return color;
}

technique defaultRender
{
    pass P0
    {
        VertexShader = compile vs_3_0 vertexShader();
        PixelShader = compile ps_3_0 pixelShader();
    }
}