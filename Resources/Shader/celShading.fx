//*****************************************************************************
//
// トゥーンシェーダー処理 [cekShader.fx]
//
// コンパイルはしない
//
// Author : LIAO HANCHEN
//
//*****************************************************************************
matrix rotMatrix;         // 回転行列
matrix worldMatrix;       // ワールド変換行列
matrix viewMatrix;        // ビューイング変換行列
matrix projectionMatrix;  // プロジェクション変換行列

matrix boneMatrices[87];  // 骨行列集合

float3 lightPos;   // ライト位置
float4 lightColor; // ライトカラー
// ライト減衰プロパティ
float lightConstant;
float lightLinear;
float lightQuadratic;

float outLineFactor = 0.1f;  // outLineを描画する時、頂点ベクトルと法線ベクトルんを混ざる因子数
float outLineStr = 0.01f;    // outLineの太さをコントロール因子

float3 amibent;   // 環境光
float3 diffuse;   // 拡散反射光
float3 specular;  // 鏡面反射光
float  shininess; // 光沢

int renderType;   // レンダリング選択

texture tex;          // テクスチャ
sampler texSampler =  // サンプラー
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
    float4 worldPos : TEXCOORD1;
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
    vout.worldPos = mul(float4(outLinePos, 1.0), worldMatrix);
    vout.pos = mul(mul(vout.worldPos, viewMatrix), projectionMatrix);

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
              float2 coord : TEXCOORD0,
              float4 weight : BLENDWEIGHT,
              float4 boneID : BLENDINDICES)
{
    // 戻り値を初期化
    VSout vout = (VSout) 0;

    //// 骨によって頂点位置を計算
    //matrix boneTrans = boneMatrices[boneID[0]] * weight[0];
    //boneTrans += boneMatrices[boneID[1]] * weight[1];
    //boneTrans += boneMatrices[boneID[2]] * weight[2];
    //boneTrans += boneMatrices[boneID[3]] * weight[3];

    //// 頂点変換
    //float4 blendPos = mul(boneTrans, float4(pos, 1.0));
    //vout.pos = mul(mul(mul(blendPos, worldMatrix), viewMatrix), projectionMatrix);
    //// 法線変更
    //vout.nor = normalize(mul(float4(nor, 1.0), rotMatrix));

    // 頂点変換
    vout.worldPos = mul(float4(pos, 1.0), worldMatrix);
    vout.pos = mul(mul(vout.worldPos, viewMatrix), projectionMatrix);
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
    float4 texColor = tex2D(texSampler, vout.coord);
    float4 lightDir = normalize(float4(lightPos, 1.0f) - vout.worldPos);

    float4 normal = float4(vout.nor.x, vout.nor.y, vout.nor.z, 1.0f);

    // ライト方向ベクトルと法線の外積を計算その結果はdiffuseです
    // 外積の値がマイナスならばシャドウにする(0)
    // max(x, y) xとy のうちの大きい方の値を選択。マイナス値を防ぐ
    float diffuse = max(0, dot(float4(vout.nor, 1.0f), -lightDir));
    // シャドウと色を分離
    //if (diffuse < 0.05f)
    //{
    //    //　diffuse
    //    texColor *= 1.0f;
    //}
    //else
    //{
    //    // シャドウ
    //    texColor *= 0.6f;
    //}

    // 減衰値を計算
    float distance = length(float4(lightPos, 1.0f) - vout.worldPos);
    float attenuation = 1.0f / (lightConstant + lightLinear * distance + lightQuadratic * (distance * distance));
    float4 attColor = attenuation * lightColor;
    texColor *= attenuation;

    // 描画方法のを選択
    if(renderType == 0)
    {
        // RT_DIFFUSE
        return float4(attenuation, attenuation, attenuation, attenuation);
    }
    else if(renderType == 1)
    {
        // RT_NORMAL
        return normal;
    }
    else if(renderType == 2)
    {
        // RT_TEXTURE
        return texColor;
    }

    // RT_SHADING -- デフォルト
    return texColor;
}

//*****************************************************************************
//
// シェーダーテクニック
//
// FXファイル名前と同じ
//
//*****************************************************************************
technique celShading
{
    // outLine
    pass P0
    {
        // アルファブレンティング
        AlphaBlendEnable = FALSE;
        // フラットシェーディング
        ShadeMode = GOURAUD;
        // マルチ・サンプリングの設定
        MultiSampleAntialias = TRUE;
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
        // アルファブレンティング
        AlphaBlendEnable = FALSE;
        // マルチ・サンプリングの設定
        MultiSampleAntialias = TRUE;
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