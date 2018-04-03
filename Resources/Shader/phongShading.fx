//*****************************************************************************
//
// �e�X�g�V�F�[�_�[���� [test.fx]
//
// �R���p�C���͂��Ȃ�
//
// Author : LIAO HANCHEN
//
//*****************************************************************************
float4 Wmat; // ���[���h�ϊ��s��
float4 Vmat; // �r���[�C���O�ϊ��s��
float4 Pmat; // �v���W�F�N�V�����ϊ��s��

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
    float4 nor : NORMAL0;
    float2 coord : TEXCOORD0;
};


VSout vsMain(float3 pos : POSITION,
             float3 nor : NORMAL,
             float2 coord : TEXCOORD)
{
    // �߂�l��������
    VSout vout = (VSout) 0;

    // ���_�ύX
    float4 vtx = mul(float4(pos, 1.0), Wmat);
    vtx = mul(vtx, Vmat);
    vtx = mul(vtx, Pmat);
    vout.pos = vtx;

    // �@���ύX
    vout.nor = mul(float4(nor, 1.0), Wmat);

    // UV���W�ύX
    vout.coord = coord;

    return vout;
}

//*****************************************************************************
//
// ���_�錾(Shader)
//
//*****************************************************************************
float4 psMain(VSout vout) : COLOR
{
    float4 color = float4(0.0, 0.0, 0.0, 0.0);

    // �J���[���v�Z
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