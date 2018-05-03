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

float lightAttenuation;     // ���̌����l
float3 lightPos;            // ���̈ʒu
float4 lightAmbient;        // ���̊��l
float4 lightDiffuse;        // ���̊g�U���˒l
float4 lightSpecular;       // ���̋��ʔ��˒l

float3 cameraPos;           // �J�����̈ʒu

texture tex;     // �e�N�X�`��
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

texture normalMap;
sampler normalMapSam = // �T���v���[
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
    float2 coord : TEXCOORD0;
    float3 worldPos : TEXCOORD1;
    float3 nor : TEXCOORD02;
};

//*****************************************************************************
//
// ���_�V�F�[�_�[
//
//*****************************************************************************
VSout vsMain(float3 pos     : POSITION0,
             float3 nor     : NORMAL0,
             float2 coord   : TEXCOORD0,
             float3 tangent : TANGENT)
{
    // �߂�l��������
    VSout vout = (VSout) 0;
    // ���_����ʂ܂ŕύX
    vout.pos = mul(mul(mul(float4(pos, 1.0), wMat), vMat), pMat);
    // ���_�𐢊E�܂ŕύX
    vout.worldPos = mul(float4(pos, 1.0), wMat);
    // �@���𐢊E�܂ŕύX�A�܂����K��
    vout.nor = normalize(mul(float4(nor, 1.0), wMat));
    //vout.nor = nor;
    // UV���W�ύX
    vout.coord = coord;

    return vout;
}

//*****************************************************************************
//
// �s�N�Z���V�F�[�_�[
//
//*****************************************************************************
float4 psMain(VSout vout, uniform int rendertype) : COLOR
{
    float4 color = float4(0.0, 0.0, 0.0, 0.0);
    float4 texColor = tex2D(texSam, vout.coord);

    if(rendertype == 0 /*with diffuse*/)
    {
        color = texColor;
    }
    else if (rendertype == 1 /*with light*/)
    {
        // ambient = lightColor * lightStrength * ambientStrength
        float4 ambient = lightDiffuse * 1.5 * 0.6;
        color += ambient;

        // diffuse
        float3 L = lightPos - vout.worldPos; // ���C�g���璸�_�܂ł̃x�N�g��
        float d = length(L); // �x�N�g���̒������v�Z
        L /= d; // �x�N�g���𐳋K��
        float attenuation = 1 / (lightAttenuation * d); // ���̌����l
        float diffuse = saturate(dot(vout.nor, L)); // �v�Z�������ς�0~1�͈̔͂ɃN�����v����

        // specular
        float3 V = normalize(vout.worldPos - cameraPos); // ���_����J�����܂ł̃x�N�g��
        float3 R = reflect(L, vout.nor); // ���ˌ��̌����ƃT�[�t�F�C�X�@�����g�p���Ĕ��˃x�N�g����Ԃ��܂��B
        int shininess = 8; // �傫���قǃe�J�����������A���˓x���������A�n�C���C�g���������Ȃ�
        float specular = pow(saturate(dot(R, V)), shininess); // ���_�ƕ\�ʋ��܃x�N�g������ς��āA�܂����˒l���v�Z����
        
        // �ŏI�J���[
        color = (diffuse + specular) * texColor * attenuation;
        color.w = 1.0;
    }
    else if (rendertype == 2 /*with light & normal map*/)
    {
        // �@����ǂݍ���
        float3 normal = tex2D(normalMapSam, vout.coord).rgb;
        normal = normalize(normal * 2.0 - 1.0);
        normal.z = -1 * normal.z;

       // ambient = lightColor * lightStrength * ambientStrength
        float4 ambient = lightDiffuse * 1.5 * 0.6;
        color += ambient;

        // diffuse
        float3 L = lightPos - vout.worldPos; // ���C�g���璸�_�܂ł̃x�N�g��
        float d = length(L); // �x�N�g���̒������v�Z
        L /= d; // �x�N�g���𐳋K��
        float attenuation = 1 / (lightAttenuation * d); // ���̌����l
        float diffuse = saturate(dot(normal, L)); // �v�Z�������ς�0~1�͈̔͂ɃN�����v����

        // specular
        float3 V = normalize(vout.worldPos - cameraPos); // ���_����J�����܂ł̃x�N�g��
        float3 R = reflect(L, normal); // ���ˌ��̌����ƃT�[�t�F�C�X�@�����g�p���Ĕ��˃x�N�g����Ԃ��܂��B
        int shininess = 8; // �傫���قǃe�J�����������A���˓x���������A�n�C���C�g���������Ȃ�
        float specular = pow(saturate(dot(R, V)), shininess); // ���_�ƕ\�ʋ��܃x�N�g������ς��āA�܂����˒l���v�Z����
        
        // �ŏI�J���[
        color = (diffuse + specular) * texColor * attenuation;
        color.w = 1.0;
    }

    return color;
}

//*****************************************************************************
//
// �����_�����O�e�N�j�b�N
//
// FX�t�@�C�����O�Ɠ���
//
//*****************************************************************************
technique render_without_light
{
    pass P0
    {
        VertexShader = compile vs_3_0 vsMain();
        PixelShader = compile ps_3_0 psMain(0);
    }
}

technique render_with_light
{
    pass P0
    {
        VertexShader = compile vs_3_0 vsMain();
        PixelShader = compile ps_3_0 psMain(1);
    }
}

technique render_with_normalMap
{
    pass P0
    {
        VertexShader = compile vs_3_0 vsMain();
        PixelShader = compile ps_3_0 psMain(2);
    }
}