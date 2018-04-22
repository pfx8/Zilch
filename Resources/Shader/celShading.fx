//*****************************************************************************
//
// �g�D�[���V�F�[�_�[���� [cekShader.fx]
//
// �R���p�C���͂��Ȃ�
//
// Author : LIAO HANCHEN
//
//*****************************************************************************
matrix rotMatrix;         // ��]�s��
matrix worldMatrix;       // ���[���h�ϊ��s��
matrix viewMatrix;        // �r���[�C���O�ϊ��s��
matrix projectionMatrix;  // �v���W�F�N�V�����ϊ��s��

matrix boneMatrices[87]; // ���s��W��

float3 lightDir;   // ���C�g�����x�N�g��
float4 lightColor; // ���C�g�J���[

float outLineFactor = 0.1f;  // outLine��`�悷�鎞�A���_�x�N�g���Ɩ@���x�N�g�������������q��
float outLineStr = 0.01f;    // outLine�̑������R���g���[�����q

float3 amibent;  // ����
float3 diffuse;  // �g�U���ˌ�
float3 specular; // ���ʔ��ˌ�
float shininess; // ����

texture tex;          // �e�N�X�`��
sampler texSampler =  // �T���v���[
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
    float3 nor : NORMAL0;
    float2 coord : TEXCOORD0;
};

//*****************************************************************************
//
// outLine���_�V�F�[�_�[����
//
//*****************************************************************************
VSout outLineVS(float3 pos : POSITION0,
                float3 nor : NORMAL0,
                float2 coord : TEXCOORD0)
{
    // �߂�l��������
    VSout vout = (VSout) 0;

    // outLine�����x�N�g�����v�Z
    // �܂��͒��_�̕����x�N�g�����v�Z
    float3 outLineDir = normalize(pos);
    // ���_�̕����x�N�g���Ɩ@���x�N�g���̊O�ς��v�Z
    // 
    float D = dot(outLineDir, nor);
    outLineDir *= sign(D);
    // outLine�̍ŏI�������v�Z
    outLineDir = outLineDir * outLineFactor + nor * (1 - outLineFactor);

    // ���_ + outLine�����x�N�g * outLine�������� = outLine���_�̏ꏊ
    float3 outLinePos = pos + outLineDir * outLineStr;

    // ���_�ϊ�
    vout.pos = mul(mul(mul(float4(outLinePos, 1.0), worldMatrix), viewMatrix), projectionMatrix);
    // �@���ύX
    vout.nor = mul(float4(nor, 1.0), worldMatrix);
    // UV���W�ύX
    vout.coord = coord;

    return vout;
}

//*****************************************************************************
//
// outLine�s�N�Z���V�F�[�_�[����
//
//*****************************************************************************
float4 outLinePS(VSout vout) : COLOR
{
    // outLine�J���[��ݒ�
    return float4(0.0f, 0.0f, 0.0f, 1.0f);
}

//*****************************************************************************
//
// ���f�����_�V�F�[�_�[����
//
//*****************************************************************************
VSout modelVS(float3 pos : POSITION0,
              float3 nor : NORMAL0,
              float2 coord : TEXCOORD0,
              float4 weight : BLENDWEIGHT,
              float4 bone : BLENDINDICES)
{
    // �߂�l��������
    VSout vout = (VSout) 0;

    //// ���ɂ���Ē��_�ʒu���v�Z
    //float4 blendVertex = float4(0.0f, 0.0f, 0.0f, 0.0f);
    //float4 blendWeight = weight;
    //int4 blendBone = int4(bone);

    //for (int count = 0; count < 4; count++)
    //{
    //    blendVertex += mul(float4(pos, 1.0f), boneMatrices[blendBone.x]) * blendWeight.x;
    //    blendBone = blendBone.yzwx;
    //    blendWeight = blendWeight.yzwx;
    //}
    //// ���_�ϊ�
    //vout.pos = mul(mul(mul(blendVertex, worldMatrix), viewMatrix), projectionMatrix);

    // ���_�ϊ�
    vout.pos = mul(mul(mul(float4(pos, 1.0f), worldMatrix), viewMatrix), projectionMatrix);
    // �@���ύX
    vout.nor = normalize(mul(float4(nor, 1.0), rotMatrix));
    // UV���W�ύX
    vout.coord = coord;

    return vout;
}

//*****************************************************************************
//
// ���f���s�N�Z���V�F�[�_�[����
//
//*****************************************************************************
float4 modelPS(VSout vout) : COLOR
{
    // �e�N�X�`���ɂ���ĐF����
    float4 color = tex2D(texSampler, vout.coord);

    // ���C�g�����x�N�g���Ɩ@���̊O�ς��v�Z���̌��ʂ�diffuse�ł�
    // �O�ς̒l���}�C�i�X�Ȃ�΃V���h�E�ɂ���(0)
    // maxx(x, y) x��y �̂����̑傫�����̒l��I���B�}�C�i�X�l��h���悤��
    float diffuse = max(0, dot(vout.nor, -lightDir));

    // �V���h�E�ƐF�𕪗�
    if (diffuse > 0.1f)
    {
        //�@diffuse
        color *= lightColor;
    }
    else
    {
        // �V���h�E
        color *= lightColor * 0.75f;
    }
    color.a = 1.0f;

    return color;
}

//*****************************************************************************
//
// �V�F�[�_�[�e�N�j�b�N
//
//*****************************************************************************
technique celShading
{
    // outLine
    pass P0
    {
        // �A���t�@�u�����e�B���O
        AlphaBlendEnable = TRUE;
        // �t���b�g�V�F�[�f�B���O
        ShadeMode = GOURAUD;
        // Z�o�b�t�@
        ZEnable = TRUE;
        // �w�ʃJ�����O
        CullMode = CW; // �|���S���̗���\��
        
        VertexShader = compile vs_3_0 outLineVS();
        PixelShader = compile ps_3_0 outLinePS();
    }
    
    // ���f��
    pass P1
    {
        DestBlend = ONE;
        // �A���t�@�u�����e�B���O
        AlphaBlendEnable = FALSE;
        // �t���b�g�V�F�[�f�B���O
        ShadeMode = GOURAUD;
        // Z�o�b�t�@
        ZEnable = TRUE;
        // �w�ʃJ�����O
        CullMode = CCW; // �|���S���̕\��\��
        
        VertexShader = compile vs_3_0 modelVS();
        PixelShader = compile ps_3_0 modelPS();
    }
}