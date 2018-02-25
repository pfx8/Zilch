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

float3 lightPos;            // ���̈ʒu
float3 lightAttenuation;    // ���̌����l
float3 lightAmbient;        // ���̊��l
float3 lightDiffuse;        // ���̊g�U���˒l
float3 lightSpecular;       // ���̋��ʔ��˒l

float3 cameraPos;           // �J�����̈ʒu

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
    float3 worldPos : TEXCOORD1;
    float3 nor : TEXCOORD02;
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
    vout.worldPos = mul(float4(pos, 1.0), wMat);
    // �@���𐢊E�܂ŕύX�A�܂����K��
    vout.nor = normalize(mul(float4(nor, 1.0), wMat));
    // UV���W�ύX
    vout.coord = coord;

    return vout;
}

//*****************************************************************************
//
// �s�N�Z���V�F�[�_�[
//
//*****************************************************************************
float4 psMain(VSout vout, uniform bool isLighting) : COLOR
{
    float4 color = float4(0.0, 0.0, 0.0, 0.0);
    float4 texColor = tex2D(texSam, vout.coord);

    if (isLighting == false)
    {
        color = texColor;
    }
    else
    {
        // ambient
        color = texColor * 0.2f;                        // �{���̃J���[

        // diffuse
        float3 LtoV = lightPos - vout.worldPos; // ���C�g���璸�_�܂ł̃x�N�g��
        float d = length(LtoV); // �x�N�g���̒������v�Z
        LtoV /= d; // �x�N�g���𐳋K��
        float attenuation = 1 / (lightAttenuation * d); // ���̌����l
        float diffuse = saturate(dot(vout.nor, LtoV)); // �v�Z�������ς�0~1�͈̔͂ɃN�����v����
        color += texColor * diffuse * attenuation;

        //// specular
        //float3 V = normalize(vout.worldPos - cameraPos);
        //float3 R = reflect(LtoV, vout.nor);             // ���ˌ��A�T�[�t�F�C�X�@���A����ы��ܗ����g�p���ċ��܃x�N�g����Ԃ��܂��B

        //float specular = pow(saturate(dot(R, V)), 8) * diffuse * attenuation;
        //color += float4(specular, specular, specular, 0);
    }

    return color;
}

//*****************************************************************************
//
// �����_�����O�e�N�j�b�N
//
//*****************************************************************************
technique render_without_light
{
    pass P0
    {
        VertexShader = compile vs_3_0 vsMain();
        PixelShader = compile ps_3_0 psMain(false);
    }
}

technique render_with_light
{
    pass P0
    {
        VertexShader = compile vs_3_0 vsMain();
        PixelShader = compile ps_3_0 psMain(true);
    }
}