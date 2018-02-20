// プログラムからもらう変数
matrix WVPMatrix; // WVP変換行列

//------------------------------------------------------
// BsaicShader(テクスチャ付き)
//------------------------------------------------------
struct BasicVertexIN
{
    float4 position : POSITION0;
    float4 normal : NORMAL0;
    float4 diffuse : COLOR0;
    float2 uvCoords : TEXCOORD0; // テクスチャ1座標
};

struct BasicVertexOUT
{
    float4 position : POSITION0;
    float4 normal : NORMAL0;
    float4 diffuse : COLOR0;
    float2 uvCoords : TEXCOORD0; // テクスチャ1座標
};

//texture Tex; // 使用するテクスチャ
//sampler Samp = // サンプラー
//sampler_state
//{
//    Texture = <Tex>;
//    MipFilter = LINEAR;
//    MinFilter = LINEAR;
//    MagFilter = LINEAR;
//};

// 頂点シェーダー
BasicVertexOUT BasicVertexShader(BasicVertexIN In)
{
    BasicVertexOUT Out = (BasicVertexOUT) 0;

    Out.position = mul(In.position, WVPMatrix);
    Out.normal = In.normal;
    Out.uvCoords = In.uvCoords;

    return Out;
}

// ピクセルシェーダー
float4 BasicPixelShader(BasicVertexOUT In) : COLOR0
{
    //return tex2D(Samp, In.uvCoords);

    return float4(0.4, 0.4, 0.4, 1.0);
}


//------------------------------------------------------
// エフェクト
//------------------------------------------------------
technique BasicShader
{
    pass P0
    {
        VertexShader = compile vs_3_0 BasicVertexShader();
        PixelShader = compile ps_3_0 BasicPixelShader();
    }
}