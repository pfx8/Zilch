//*****************************************************************************
//
// トゥーンシェーダー処理 [cekShader.fx]
//
// コンパイルはしない
//
// Author : LIAO HANCHEN
//
//*****************************************************************************
matrix rotMatrix;               // 回転行列
matrix worldMatrix;             // ワールド変換行列
matrix viewMatrix;              // ビューイング変換行列
matrix projectionMatrix;        // プロジェクション変換行列

float3 lightDir = float3(-1.0f, 1.0f, 1.0f);   // ライト方向ベクトル
float4 lightColor = float4(1.0f, 1.0f, 1.0f, 1.0f);    // ライトカラー

float outLineFactor = 0.3f;     // outLineを描画する時、頂点ベクトルと法線ベクトルんを混ざる因子数
float outLineStr = 0.009f;      // outLineの太さをコントロール因子

float3 amibent; // 環境光
float3 diffuse; // 拡散反射光
float3 specular; // 鏡面反射光
float shininess; // 光沢

texture tex;               // テクスチャ
sampler texSampler =       // サンプラー
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
    float3 nor : NORMAL0;
    float2 coord : TEXCOORD0;
};

//*****************************************************************************
//
// outLine頂点シェーダー処理
//
//*****************************************************************************
VSout outLineVS(float3 pos : POSITION0,
               float3 nor : NORMAL0,
               float2 coord : TEXCOORD0)
{
    // 戻り値を初期化
    VSout vout = (VSout) 0;

    // outLine方向ベクトルを計算
    // まずは頂点の方向ベクトルを計算
    float3 outLineDir = normalize(pos);
    // 頂点の方向ベクトルと法線ベクトルの外積を計算
    // 
    float D = dot(outLineDir, nor);
    outLineDir *= sign(D);
    // outLineの最終方向を計算
    outLineDir = outLineDir * outLineFactor + nor * (1 - outLineFactor);

    // 頂点 + outLine方向ベクト * outLine太さ因数 = outLine頂点の場所
    float3 outLinePos = pos + outLineDir * outLineStr;

    // 頂点変換
    vout.pos = mul(mul(mul(float4(outLinePos, 1.0), worldMatrix), viewMatrix), projectionMatrix);
    // 法線変更
    vout.nor = mul(float4(nor, 1.0), worldMatrix);
    // UV座標変更
    vout.coord = coord;

    return vout;
}

//*****************************************************************************
//
// outLineピクセルシェーダー処理
//
//*****************************************************************************
float4 outLinePS(VSout vout) : COLOR
{
    // outLineカラーを設定
    return float4(0.0f, 0.0f, 0.0f, 1.0f);
}

//*****************************************************************************
//
// モデル頂点シェーダー処理
//
//*****************************************************************************
VSout modelVS(float3 pos : POSITION0,
             float3 nor : NORMAL0,
             float2 coord : TEXCOORD0)
{
    // 戻り値を初期化
    VSout vout = (VSout) 0;

    // 頂点変換
    vout.pos = mul(mul(mul(float4(pos, 1.0), worldMatrix), viewMatrix), projectionMatrix);
    // 法線変更
    vout.nor = normalize(mul(float4(nor, 1.0), rotMatrix));
    // UV座標変更
    vout.coord = coord;

    return vout;
}

//*****************************************************************************
//
// モデルピクセルシェーダー処理
//
//*****************************************************************************
float4 modelPS(VSout vout) : COLOR
{
    // テクスチャによって色をつき
    float4 color = tex2D(texSampler, vout.coord);

    // ライト方向ベクトルと法線の外積を計算その結果はdiffuseです
    // 外積の値がマイナスならばシャドウにする(0)
    // maxx(x, y) xとy のうちの大きい方の値を選択。マイナスを防ぐように
    float diffuse = max(0, dot(vout.nor, -lightDir));

    // シャドウと色を分離
    if (diffuse > 0.15f)
    {
        //　diffuse
        color *= lightColor;
    }
    else
    {
        // シャドウ
        color *= lightColor * 0.93f;
    }
    //color.a = 1.0f;

    return color;
}

//*****************************************************************************
//
// シェーダーテクニック
//
//*****************************************************************************
technique celShading
{
    // outLine
    pass P0
    {
        // アルファブレンティング
        AlphaBlendEnable = TRUE;
        // フラットシェーディング
        ShadeMode = GOURAUD;
        // Zバッファ
        ZEnable = TRUE;
        // 背面カリング
        CullMode = CW; // ポリゴンの裏を表示
        
        VertexShader = compile vs_3_0 outLineVS();
        PixelShader = compile ps_3_0 outLinePS();
    }
    
    // モデル
    pass P1
    {
        DestBlend = ONE;
        // アルファブレンティング
        AlphaBlendEnable = FALSE;
        // フラットシェーディング
        ShadeMode = GOURAUD;
        // Zバッファ
        ZEnable = TRUE;
        // 背面カリング
        CullMode = CCW; // ポリゴンの表を表示
        
        VertexShader = compile vs_3_0 modelVS();
        PixelShader = compile ps_3_0 modelPS();
    }
}