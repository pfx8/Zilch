//*****************************************************************************
//
// D3DTutorial���� [Scene01.h]
//
// Author : LIAO HANCHEN
//
//*****************************************************************************
#ifndef _SCENE01_H_
#define _SCENE01_H_

#include <map>

#include "ResourcesManager.h"
#include "Engine.h"
#include "Character.h"
#include "Modules\Scene.h"
#include "Modules\Camera.h"
#include "Modules\Light.h"
#include "Modules\SkyBox.h"
#include "Modules\Shader.h"

//*****************************************************************************
//
// �N���X�錾
//
//*****************************************************************************
class Scene01 : public Scene
{
private:
	Shader*				shader2D;			// �V�F�[�_�[
	//Shader*				shader3D;			// �V�F�[�_�[
	Camera*				camera;				// �J����
	Light*				directionLight;		// ���C�g
	Plane*				field;				// �t�B�[���h
	//SkyBox*				skyBox;				// �X�J�C�{�b�N�X

	LPDIRECTSOUNDBUFFER8 seHit;

public:
	Character*			woman;			// �v���[���[

	Scene01();
	~Scene01();

	void Initialization();	// ������
	void Update();			// �X�V
	void Draw();			// �`��
	void SetRenderState();	// �����_�����O��ݒ�
};
#endif // !_SCENE00_H_

