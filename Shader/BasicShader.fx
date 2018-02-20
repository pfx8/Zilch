// �v���O����������炤�ϐ�
matrix WVPMatrix; // WVP�ϊ��s��

//------------------------------------------------------
// BsaicShader(�e�N�X�`���t��)
//------------------------------------------------------
struct BasicVertexIN
{
    float4 position : POSITION0;
    float4 normal : NORMAL0;
    float4 diffuse : COLOR0;
    float2 uvCoords : TEXCOORD0; // �e�N�X�`��1���W
};

struct BasicVertexOUT
{
    float4 position : POSITION0;
    float4 normal : NORMAL0;
    float4 diffuse : COLOR0;
    float2 uvCoords : TEXCOORD0; // �e�N�X�`��1���W
};

//texture Tex; // �g�p����e�N�X�`��
//sampler Samp = // �T���v���[
//sampler_state
//{
//    Texture = <Tex>;
//    MipFilter = LINEAR;
//    MinFilter = LINEAR;
//    MagFilter = LINEAR;
//};

// ���_�V�F�[�_�[
BasicVertexOUT BasicVertexShader(BasicVertexIN In)
{
    BasicVertexOUT Out = (BasicVertexOUT) 0;

    Out.position = mul(In.position, WVPMatrix);
    Out.normal = In.normal;
    Out.uvCoords = In.uvCoords;

    return Out;
}

// �s�N�Z���V�F�[�_�[
float4 BasicPixelShader(BasicVertexOUT In) : COLOR0
{
    //return tex2D(Samp, In.uvCoords);

    return float4(0.4, 0.4, 0.4, 1.0);
}


//------------------------------------------------------
// �G�t�F�N�g
//------------------------------------------------------
technique BasicShader
{
    pass P0
    {
        VertexShader = compile vs_3_0 BasicVertexShader();
        PixelShader = compile ps_3_0 BasicPixelShader();
    }
}