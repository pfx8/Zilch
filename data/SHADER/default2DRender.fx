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

float3 lightPos; // ライトの位置

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
};

//*****************************************************************************
//
// 頂点シェーダー
//
//*****************************************************************************
VSout vsMain(float3 pos : POSITION0,
             float2 coord : TEXCOORD0)
{
    // 戻り値を初期化
    VSout vout = (VSout) 0;

    // 頂点変更
    vout.pos = mul(mul(mul(float4(pos, 1.0), wMat), vMat), pMat);

    // UV座標変更
    vout.coord = coord;

    return vout;
}

//*****************************************************************************
//
// ピクセルシェーダー
//
//*****************************************************************************
float4 psMain(VSout vout) : COLOR
{
    float4 color = float4(0.0, 0.0, 0.0, 0.0);

    // カラーを計算
    //color = float4(1.0, 0.0, 0.0, 1.0);
    color = tex2D(texSam, vout.coord);

    return color;
}

//*****************************************************************************
//
// レンダリングテクニック
//
//*****************************************************************************
technique default2DRender
{
    pass P0
    {
        VertexShader = compile vs_3_0 vsMain();
        PixelShader = compile ps_3_0 psMain();
    }
}