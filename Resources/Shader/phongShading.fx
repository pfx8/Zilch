//*****************************************************************************
//
// �t�H�[���V�F�[�_�[���� [phongShading.fx]
//
// �R���p�C���͂��Ȃ�
//
// Author : LIAO HANCHEN
//
//*****************************************************************************
matrix worldMatrix;             // ���[���h�ϊ��s��
matrix viewMatrix;              // �r���[�C���O�ϊ��s��
matrix projectionMatrix;        // �v���W�F�N�V�����ϊ��s��

float3 lightPos; // ���C�g�ʒu
float4 lightColor; // ���C�g�J���[
// ���C�g�����v���p�e�B
float lightConstant;
float lightLinear;
float lightQuadratic;

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
    float4 pos : POSITION;
    float3 nor : NORMAL;
    float2 coord : TEXCOORD0;
    float4 worldPos : TEXCOORD1;
};

//*****************************************************************************
//
// ���_�V�F�[�_�[����
//
//*****************************************************************************
VSout vertexShader(float3 pos : POSITION,
             float3 nor : NORMAL,
             float2 coord : TEXCOORD)
{
    // �߂�l��������
    VSout vout = (VSout) 0;

    // ���_�ϊ�
    vout.worldPos = mul(float4(pos, 1.0), worldMatrix);
    vout.pos = mul(mul(vout.worldPos, viewMatrix), projectionMatrix);
    // �@���ύX
    vout.nor = normalize(mul(float4(nor, 1.0), worldMatrix));
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
    // ���C�g�����x�N�g�����v�Z
    float4 lightDir = normalize(float4(lightPos, 1.0f) - vout.worldPos);
    // �e�N�X�`������J���[���擾
    float4 texColor = tex2D(texSampler, vout.coord);
    float diffuse = max(0, dot(float4(vout.nor, 1.0f), -lightDir));

    // ���C�g�����l���v�Z
    float distance = length(float4(lightPos, 1.0f) - vout.worldPos);
    float attenuation = 1.0 / (lightConstant + lightLinear * distance + lightQuadratic * distance * distance);
    float4 attColor = attenuation * lightColor;
    

    //return lightDir;
    //return texColor;
    //return float4(diffuse, diffuse, diffuse, diffuse);
    return float4(attenuation, attenuation, attenuation, attenuation);
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