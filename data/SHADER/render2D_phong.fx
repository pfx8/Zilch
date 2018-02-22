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

float3 lightPos;
float3 lightAmbient;
float3 lightDiffuse;
float3 lightSpecular;
float3 cameraPos;

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
    //float3 worldPos : TEXCOORD1;
    //float3 nor : TEXCOORD2;
    float2 coord : TEXCOORD0;
};

//*****************************************************************************
//
// ���_�V�F�[�_�[
//
//*****************************************************************************
VSout vsMain(float3 pos : POSITION0,
             float3 nor : NORMAL0,
             float2 coord : TEXCOORD0)
{
    // �߂�l��������
    VSout vout = (VSout) 0;
    // ���_����ʂ܂ŕύX
    vout.pos = mul(mul(mul(float4(pos, 1.0), wMat), vMat), pMat);
    // ���_�𐢊E�܂ŕύX
    //vout.worldPos = mul(float4(pos, 1.0), wMat);
    // �@���𐢊E�܂ŕύX�A�܂����K��
    //vout.nor = normalize(mul(float4(nor, 1.0), wMat));

    // UV���W�ύX
    vout.coord = coord;

    return vout;
}

//*****************************************************************************
//
// �s�N�Z���V�F�[�_�[
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
        //float3 LtoV = lightPos - vout.worldPos; // ���C�g���璸�_�܂ł̃x�N�g��
        //float D = length(LtoV); // �x�N�g���̒������v�Z
        //LtoV /= D; // �x�N�g���𐳋K��



    //}

    return color;
}

//*****************************************************************************
//
// �����_�����O�e�N�j�b�N
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