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

float3 lightPos;
float3 lightAmbient;
float3 lightDiffuse;
float3 lightSpecular;
float3 cameraPos;

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
    //float3 worldPos : TEXCOORD1;
    //float3 nor : TEXCOORD2;
    float2 coord : TEXCOORD0;
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
    //vout.worldPos = mul(float4(pos, 1.0), wMat);
    // 法線を世界まで変更、また正規化
    //vout.nor = normalize(mul(float4(nor, 1.0), wMat));

    // UV座標変更
    vout.coord = coord;

    return vout;
}

//*****************************************************************************
//
// ピクセルシェーダー
//
//*****************************************************************************
float4 psMain(VSout vout
              /*uniform bool isLighting*/) : COLOR0
{
    float4 color = float4(0.0, 0.0, 0.0, 0.0);

    //if(isLighting == false)
    //{
        color = float4(1.0, 0.0, 0.0, 0.0);
        //color = tex2D(texSam, vout.coord);
    //}
    //else
    //{
        //float3 LtoV = lightPos - vout.worldPos; // ライトから頂点までのベクトル
        //float D = length(LtoV); // ベクトルの長さを計算
        //LtoV /= D; // ベクトルを正規化



    //}

    return color;
}

//*****************************************************************************
//
// レンダリングテクニック
//
//*****************************************************************************
technique render_no_light
{
    pass P0
    {
        VertexShader = compile vs_3_0 vsMain();
        PixelShader = compile ps_3_0 psMain(/*false*/);
    }
}

technique render_with_light
{
    pass P0
    {
        VertexShader = compile vs_3_0 vsMain();
        PixelShader = compile ps_3_0 psMain(/*true*/);
    }
}