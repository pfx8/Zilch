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

//*****************************************************************************
//
// �ϐ�����
//
//*****************************************************************************
// ���C�g�̊�b�ϐ�
float3  lightPos;    // ���C�g�ʒu
float4  lightColor;  // ���C�g�J���[
int     lightType;   // ���C�g�^�C�v

// �w�������C�g
float3 direction;  // ���C�g�̕���

// �|�C���g���C�g�@-- �����l
float  lightConstant;
float  lightLinear;
float  lightQuadratic;

// �X�|�b�g���C�g
float  cutOff;    // �X�|�b�g�x�N�g���ƃ��C�g�x�N�g���̃R�T�C���l
bool   isSmooth;  // �X���[�X�`�F�b�N

// �J���[�����v�I��
int colorRamp;
// �Z�O�����g�l
float3 colorRampSegment;

//*****************************************************************************
//
// ���C�g�f�B�t���[�Y�v�Z
//
//*****************************************************************************
float diffuseProcess(float4 lightDir, float3 normal)
{
    float diffuse;

    if(lightType == 0)
    {
        // �w�������C�g�̏ꍇ
        diffuse = dot(-direction, normal);

        return diffuse;
    }

    // ���C�g�����x�N�g���Ɩ@���̊O�ς��v�Z���̌��ʂ�diffuse�ł�
    // �O�ς̒l���}�C�i�X�Ȃ�΃V���h�E�ɂ���(0)
    // max(x, y) x��y �̂����̑傫�����̒l��I���B�}�C�i�X�l��h��
    diffuse = max(0, dot(float4(normal, 1.0f), -lightDir));

    return diffuse;
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
float diffuseByLightType(float4 lightDir, float3 normal, float4 worldPos)
{
    // ���ʃf�B�t���[�Y
    float diff;

     // �w�������C�g
    if (lightType == 0)
    {
        // �f�B�t���[�Y�v�Z
        // ���j�A���[�h
        diff = diffuseProcess(lightDir, normal);

        if (colorRamp == 1)
        {
            // ��胂�[�h
            diff = diff * 0.5 + 0.5;
            diff = constantDiffuse(diff);
        }
    }

    // �|�C���g���C�g
    else if (lightType == 1)
    {
        // �f�B�t���[�Y�v�Z
        // ���j�A���[�h
        diff = attenuationProcess(worldPos);

        if (colorRamp == 1)
        {
            // ��胂�[�h
            diff = diff * 0.5 + 0.5;
            diff = constantDiffuse(diff);
        }
    }

    // �X�|�b�g���C�g
    else if (lightType == 2)
    {
        // �f�B�t���[�Y�v�Z
        // ���j�A���[�h

        // �p�x�ɂ���Ė��邳�𒲐�
        float theta = dot(lightDir, float4(normalize(-direction), 1.0));
        if (theta > cutOff)
        {
            // ���������Ă�
            diff = diffuseProcess(lightDir, normal);
        }
        else
        {
            // ���C�g���Ȃ�
            diff = float4(0, 0, 0, 1);
        }

        if (colorRamp == 1)
        {
            // ��胂�[�h
            diff = diff * 0.5 + 0.5;
            diff = constantDiffuse(diff);
        }
    }

    return diff;
}

#endif // !_LIGHTING_PROCESS_H_