//*****************************************************************************
//
// ���C�e�B���O���� [lightingProcess.fx]
//
// �R���p�C���͂��Ȃ�
//
// Author : LIAO HANCHEN
//
//*****************************************************************************
#ifndef _LIGHTING_PROCESS_H_
#define _LIGHTING_PROCESS_H_

#include "publicValue.fx"

//*****************************************************************************
//
// �ϐ�����
//
//*****************************************************************************
// ���C�g�̊�b�ϐ�
float3  lightPos;      // ���C�g�ʒu
float4  lightColor;    // ���C�g�J���[
int     lightType;     // ���C�g�^�C�v
float   lightStrength; // ���C�g���x
float   lightAmbient;  // ���C�g�A���r�G���g
float   lightDiffuse;  // ���C�g�f�B�t���[�Y
float   lightSpecular; // ���C�g�X�y�L�����[

// �w�������C�g
float3 direction;  // ���C�g�̕���

// �|�C���g���C�g�@-- �����l
float  lightConstant;
float  lightLinear;
float  lightQuadratic;

// �X�|�b�g���C�g
float  cutOff;    // �X�|�b�g�x�N�g���ƃ��C�g�x�N�g���̃R�T�C���l
bool   isSmooth;  // �X���[�X�`�F�b�N

// �J���[�����v
int colorRampType;        // �J���[�����v�^�C�v
float3 colorRampSegment;  // �Z�O�����g�l

//*****************************************************************************
//
// �A���r�G���g
//
//*****************************************************************************
float3 ambientProcess()
{
    float3 ambient;

    if (matAmibent.r == 0.0 && matAmibent.g == 0.0 && matAmibent.b == 0.0)
    {
        ambient = lightAmbient * lightColor.rgb;
    }
    else
    {
        ambient = lightAmbient * matAmibent * lightColor.rgb;
    }

    return ambient;
}

//*****************************************************************************
//
// �f�B�t���[�Y
//
// max(x, y) x��y �̂����̑傫�����̒l��I���B�}�C�i�X�l��h��
// saturate(x) x��0~1�͈̔͂ɃN�����v
//
//*****************************************************************************
float diffuseProcess(float4 lightDir, float3 normal)
{
    float diff;

    if(lightType == 0)
    {
        // �w�������C�g�̏ꍇ
        //diff = max(dot(normal, direction), 0.0);
        diff = saturate(dot(normal, direction));
    }
    else
    {
        //diff = max(dot(float4(normal, 1.0), lightDir), 0.0);
        diff = saturate(dot(float4(normal, 1.0), lightDir));
    }

    return diff;
}

//*****************************************************************************
//
// �X�y�L�����[
//
// max(x, y) x��y �̂����̑傫�����̒l��I���B�}�C�i�X�l��h��
//
//*****************************************************************************
float3 specularProcess(float4 cameraDir, float4 lightDir, float3 normal)
{
    float3 specular;
    float  spec;

    // Phong
    //float4 reflectDir = reflect(-lightDir, float4(normal, 1.0));
    //spec = pow(max(dot(cameraDir, reflectDir), 0.0), shininess);

    // Blinn-Phong
    float4 halfwayDir = normalize(lightDir + cameraDir);
    //spec = pow(max(dot(normal, halfwayDir.rgb), 0.0), shininess);
    spec = pow(saturate(dot(normal, halfwayDir.rgb)), shininess);

    specular = lightSpecular * (spec * matSpecular) * lightStrength;

    return specular;
}

//*****************************************************************************
//
// �|�C���g���C�g�f�B�t���[�Y
//
//*****************************************************************************
float attenuationProcess(float4 worldPos)
{
    float distance = length(float4(lightPos, 1.0f) - worldPos);
    float attenuation = 1.0f / (lightConstant + lightLinear * distance + lightQuadratic * (distance * distance));

    return attenuation;
}

//*****************************************************************************
//
// ���f�B�t���[�Y�v�Z
//
//*****************************************************************************
float constantDiffuse(float diff)
{
    float w = fwidth(diff) * 2.0;

    if (diff < colorRampSegment.x + w)
    {
        diff = lerp(colorRampSegment.x, colorRampSegment.y, smoothstep(colorRampSegment.x - w, colorRampSegment.x + w, diff));
    }
    else if (diff < colorRampSegment.y + w)
    {
        diff = lerp(colorRampSegment.y, colorRampSegment.z, smoothstep(colorRampSegment.y - w, colorRampSegment.y + w, diff));
    }
    else if (diff < colorRampSegment.z + w)
    {
        diff = lerp(colorRampSegment.z, 1.0, smoothstep(colorRampSegment.z - w, colorRampSegment.z + w, diff));
    }
    else
    {
        diff = 1.0;
    }

    return diff;
}

//*****************************************************************************
//
// �e��ނ̃��C�g�̃f�B�t���[�Y���v�Z
//
//*****************************************************************************
float3 diffuseByLightType(float4 lightDir, float3 normal, float4 worldPos)
{
    float3 diffuse;
    float diff;

    // �f�B�t���[�Y�v�Z
    if (lightType == 0)
    {
        // �w�������C�g
        diff = diffuseProcess(lightDir, normal);
    }
    else if (lightType == 1)
    {
        // �|�C���g���C�g
        diff = diffuseProcess(lightDir, normal) * attenuationProcess(worldPos);
    }
    else if (lightType == 2)
    {
        // �X�|�b�g���C�g
        // ���C�g�ƌ������̊p�x
        float theta = dot(lightDir, float4(normalize(-direction), 1.0));
        if (theta > cutOff)
        {
            // ���������Ă�
            diff = diffuseProcess(lightDir, normal);
        }
        else
        {
            // ���C�g���Ȃ�
            diff = float4(0.0, 0.0, 0.0, 1.0);
        }
    }

    // ��胂�[�h�Ȃ��
    if (colorRampType == 1)
    {
        //diff = diff * 0.5 + 0.5;
        diff = constantDiffuse(diff);
    }

    diffuse = float3(diff, diff, diff) * matDiffuse * lightDiffuse * lightStrength;

    return diffuse;
}

#endif // !_LIGHTING_PROCESS_H_