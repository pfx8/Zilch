//*****************************************************************************
//
// �t�H�[���V�F�[�_�[���� [phongShading.fx]
//
// �R���p�C���͂��Ȃ�
//
// Author : LIAO HANCHEN
//
//*****************************************************************************
matrix worldMatrix;            // ���[���h�ϊ��s��
matrix viewMatrix;              // �r���[�C���O�ϊ��s��
matrix projectionMatrix;     // �v���W�F�N�V�����ϊ��s��

float3 lightDir; // ���C�g�����x�N�g��
float4 lightColor; // ���C�g�J���[

texture tex;                                   // �e�N�X�`��
sampler texSampler =                // �T���v���[
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
// �v���g�^�C�v�錾
//
//*****************************************************************************
struct VSout
{
    float4 pos : POSITION0;
    float4 nor : NORMAL0;
    float2 coord : TEXCOORD0;
};

//*****************************************************************************
//
// ���_�V�F�[�_�[����
//
//*****************************************************************************
VSout vertexShader(float3 pos : POSITION0,
             float3 nor : NORMAL0,
             float2 coord : TEXCOORD0)
{
    // �߂�l��������
    VSout vout = (VSout) 0;

    // ���_�ϊ�
    vout.pos = mul(mul(mul(float4(pos, 1.0), worldMatrix), viewMatrix), projectionMatrix);
    // �@���ύX
    vout.nor = mul(float4(nor, 1.0), worldMatrix);
    // UV���W�ύX
    vout.coord = coord;

    return vout;
}

//*****************************************************************************
//
// �s�N�Z���V�F�[�_�[����
//
//*****************************************************************************
float4 pixelShader(VSout vout) : COLOR
{
    float4 color = float4(0.0, 0.0, 0.0, 0.0);

    // �J���[���v�Z
    //color = float4(1.0, 0.0, 0.0, 1.0);
    color = tex2D(texSampler, vout.coord);

    return color;
}

//*****************************************************************************
//
// �V�F�[�_�[�e�N�j�b�N
//
//*****************************************************************************
technique phongShading
{
    pass P0
    {
        // �t���b�g�V�F�[�f�B���O
        ShadeMode = FLAT;
        // Z�o�b�t�@
        ZEnable = TRUE;
        // �w�ʃJ�����O
        CullMode = CCW;     // �|���S���̕\��\��
        // �A���t�@�u�����e�B���O
        AlphaBlendEnable = TRUE;
        
        VertexShader = compile vs_3_0 vertexShader();
        PixelShader = compile ps_3_0 pixelShader();
    }
}