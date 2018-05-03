//*****************************************************************************
//
// シャドーマップ処理 [shadowMap.fx]
//
// コンパイルはしない
//
// Author : LIAO HANCHEN
//
//*****************************************************************************
matrix worldViewProjectionShadow;  // シャドウマップ用WVP行列

//*****************************************************************************
//
// プロトタイプ宣言
//
//*****************************************************************************
struct VSout
{
    float4 pos : POSITION;      // 変更した座標
    float4 tex : TEXCOORD0;     // 変更した頂点によってシャドウマップのテクスチャで位置をケメル
};

//*****************************************************************************
//
// shadowMap頂点シェーダー処理
//
//*****************************************************************************
VSout shadowMapVS(float3 pos : POSITION0)
{
    VSout vout = (VSout) 0;

    // 変更頂点を計算
    vout.pos = mul(float4(pos, 1.0f), worldViewProjectionShadow);
    // テクスチャの座標として、頂点座標を出す
    vout.tex = vout.pos;

    return vout;
}

//*****************************************************************************
//
// shadowMapピクセルシェーダー処理
//
//*****************************************************************************
float4 shadowMapPS(VSout vout) : COLOR0
{
    // Z軸値によって色をつき
    return (vout.tex.z / vout.tex.w);
}

//*****************************************************************************
//
// シェーダーテクニック
//
// FXファイル名前と同じ
//
//*****************************************************************************
technique shadowMap
{
    pass P0
    {
        // Zバッファ
        ZEnable = TRUE;
        // マルチ・サンプリングの設定
        MultiSampleAntialias = FALSE;
        // 背面カリング
        CullMode = CW; // ポリゴンの裏を表示
        // アルファブレンティング
        AlphaBlendEnable = FALSE;
        // フラットシェーディング
        ShadeMode = FLAT;

        VertexShader = compile vs_3_0 shadowMapVS();
        PixelShader = compile ps_3_0 shadowMapPS();
    }
}