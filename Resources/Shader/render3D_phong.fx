//*****************************************************************************
//
// テストシェーダー処理 [test.fx]
//
// コンパイルはしない
//
// Author : LIAO HANCHEN
//
//*****************************************************************************
float4 Wmat; // ワールド変換行列
float4 Vmat; // ビューイング変換行列
float4 Pmat; // プロジェクション変換行列

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
    float4 nor : NORMAL0;
    float2 coord : TEXCOORD0;
};


VSout vsMain(float3 pos : POSITION,
             float3 nor : NORMAL,
             float2 coord : TEXCOORD)
{
    // 戻り値を初期化
    VSout vout = (VSout) 0;

    // 頂点変更
    float4 vtx = mul(float4(pos, 1.0), Wmat);
    vtx = mul(vtx, Vmat);
    vtx = mul(vtx, Pmat);
    vout.pos = vtx;

    // 法線変更
    vout.nor = mul(float4(nor, 1.0), Wmat);

    // UV座標変更
    vout.coord = coord;

    return vout;
}

//*****************************************************************************
//
// 頂点宣言(Shader)
//
//*****************************************************************************
float4 psMain(VSout vout) : COLOR
{
    float4 color = float4(0.0, 0.0, 0.0, 0.0);

    // カラーを計算
    color = float4(1.0, 0.0, 0.0, 1.0);
    //color = tex2D(texSam, vout.coord);

    return color;
}

technique defaultRender
{
    pass P0
    {
        VertexShader = compile vs_3_0 vsMain();
        PixelShader = compile ps_3_0 psMain();
    }
}