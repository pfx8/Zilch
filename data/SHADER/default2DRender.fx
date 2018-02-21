//*****************************************************************************
//
// �e�X�g�V�F�[�_�[���� [test.fx]
//
// �R���p�C���͂��Ȃ�
//
// Author : LIAO HANCHEN
//
//*****************************************************************************
matrix wMat; // ���[���h�ϊ��s��
matrix vMat; // �r���[�C���O�ϊ��s��
matrix pMat; // �v���W�F�N�V�����ϊ��s��

float3 lightPos; // ���C�g�̈ʒu

texture tex; // �e�N�X�`��
sampler texSam = // �T���v���[
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
// ���_�V�F�[�_�[
//
//*****************************************************************************
VSout vsMain(float3 pos : POSITION0,
             float2 coord : TEXCOORD0)
{
    // �߂�l��������
    VSout vout = (VSout) 0;

    // ���_�ύX
    vout.pos = mul(mul(mul(float4(pos, 1.0), wMat), vMat), pMat);

    // UV���W�ύX
    vout.coord = coord;

    return vout;
}

//*****************************************************************************
//
// �s�N�Z���V�F�[�_�[
//
//*****************************************************************************
float4 psMain(VSout vout) : COLOR
{
    float4 color = float4(0.0, 0.0, 0.0, 0.0);

    // �J���[���v�Z
    //color = float4(1.0, 0.0, 0.0, 1.0);
    color = tex2D(texSam, vout.coord);

    return color;
}

//*****************************************************************************
//
// �����_�����O�e�N�j�b�N
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