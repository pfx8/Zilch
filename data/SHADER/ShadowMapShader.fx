//*****************************************************************************
//
// シャドーマップ処理 [ShadowMapShader.fx]
//
// コンパイルはしない
//
// Author : LIAO HANCHEN
//
//*****************************************************************************

#define SMAP_SIZE (512)

#define SHADOW_BIAS 0.001f

// シャドーマップ頂点IN構造体
struct CreateShadowMap_VSIn
{
    float3 position : POSITION;
    float3 normal : NORMAL0;
};

// シャドーマップ頂点OUT構造体
struct CreateShadowMap_VSOut
{
    float4 position : POSITION;
    float  depth : TEXCOORD0;
};

// シャドー頂点IN構造体
struct DrawWithShadowMap_VSIn
{
    float3 position : POSITION;
    float3 normal : NORMAL0;
    float2 uvcoord : TEXCOORD0;
};

// シャドー頂点OUT構造体
struct DrawWithShadowMap_VSOut
{
    float4 position : POSITION;
    float3 normal : TEXCOORD0;
    float2 uvcoord : TEXCOORD1;
    float4 worldpos: TEXCOORD2;
};

// 行列
matrix WMatrix; // ワールド変換換行列
matrix VMatrix; // ビューイング変換行列
matrix PMatrix; // プロジェクション変換行列

// ライト
float3 lightPos;
float3 lightDir;     // ライト方向ベクトル
float4 lightAmbient; // 拡散反射光(モデル本来のカラー)

matrix lightViewProj;

// マテリアル
float4 material;

// サンプラー
texture shadowMap;
sampler shadowMapSampler =
sampler_state
{
    Texture = <shadowMap>;
    MinFilter = Point;
    MagFilter = Point;
    MipFilter = Point;
    AddressU = Clamp;
    AddressV = Clamp;
};

texture tex;
sampler texSampler =
sampler_state
{
    Texture = <tex>;
    MinFilter = Point;
    MagFilter = Linear;
    MipFilter = Linear;
};

//------------------------------------------------------
//
// 頂点シェーダー
//
// シャドーマップを生成
//
//------------------------------------------------------
CreateShadowMap_VSOut ShadowMapVertexShader(CreateShadowMap_VSIn In)
{
    CreateShadowMap_VSOut Out = (CreateShadowMap_VSOut) 0;

    // 座標を変換
    Out.position = mul(float4(In.position, 1.0), mul(WMatrix, lightViewProj));

    // 深度を取得(Z座標を取得)
    Out.depth = Out.position.z /Out.position.w;

    return Out;
}

//------------------------------------------------------
//
// ピクセルシェーダー
//
// シャドーマップを生成
//
//------------------------------------------------------
float4 ShadowMapPixelShader(CreateShadowMap_VSOut In) : COLOR
{
    // 
    return float4(In.depth, 0, 0, 0);
}

//------------------------------------------------------
//
// 頂点シェーダー
//
// シャドーを生成
//
//------------------------------------------------------
DrawWithShadowMap_VSOut ShadowVertexShader(DrawWithShadowMap_VSIn In)
{
    DrawWithShadowMap_VSOut Out = (DrawWithShadowMap_VSOut) 0;
    
    // ワールド変換、ビューイング変換、プロジェクション変換行列を求める
    matrix WVPMatrix = mul(mul(WMatrix, VMatrix), PMatrix);

    // 位置座標と法線座標を行列により変換する
    Out.position = mul(float4(In.position, 1.0), WVPMatrix);
    Out.normal = normalize(mul(float4(In.normal, 1.0), WMatrix));

    // UV座標は変更しない
    Out.uvcoord = In.uvcoord;

    // 頂点のワールド座標を保存
    Out.worldpos = mul(float4(In.position, 1.0), WMatrix);

    return Out;
}

//------------------------------------------------------
//
// ピクセルシェーダー
//
// シャドーを生成
//
//------------------------------------------------------
float4 ShadowPixelShader(DrawWithShadowMap_VSOut In) : COLOR
{
    // カラーを計算する
    float4 color = tex2D(texSampler, In.uvcoord);

    // saturate:指定された値を0～1の範囲にクランプします。
    // ライトの方向によって強度を計算する
    float diffuseIntensity = saturate(dot(
    , In.normal));

    // ライトのアンビエンドにより最終のカラーを求める
    float4 diffuse = diffuseIntensity * color + lightAmbient;

    // ライトの空間でこのピクセル位置を見つける
    float4 lightingPosition = mul(In.worldpos, lightViewProj);

    // シャドーマップでこのピクセル位置を見つける
    float2 shadowTexCoord = 0.5 * lightingPosition.xy / lightingPosition.w + float2(0.5, 0.5);
    shadowTexCoord.y = 1.0 - shadowTexCoord.y;

    // シャドーマップによって保存された深度を取得
    float shadowDepth = tex2D(shadowMapSampler, shadowTexCoord).r;

    // ピクセルの深度を計算する
    float depth = (lightingPosition.z / lightingPosition.w) - SHADOW_BIAS;

    // 深度によってシャドーかどうかを判断
    if (shadowDepth < depth)
    {
        diffuse *= float4(0.5, 0.5, 0.5, 0);
    }

    return diffuse;
}

//------------------------------------------------------
// エフェクト
//------------------------------------------------------
technique createShadowMap
{
	pass P0
	{
        VertexShader = compile vs_3_0 ShadowMapVertexShader();
        PixelShader = compile ps_3_0 ShadowMapPixelShader();
    }
}

technique drawWithShadowMap
{
    pass P0
    {
        VertexShader = compile vs_3_0 ShadowVertexShader();
        PixelShader = compile ps_3_0 ShadowPixelShader();
    }
}

