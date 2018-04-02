//*****************************************************************************
//
// �A�j���[�V�������� [Scene02.h]
//
// Author : LIAO HANCHEN
//
//*****************************************************************************
#ifndef _SCENE02_H_
#define _SCENE02_H_

#include "..\Engine\Engine.h"
#include "..\Engine\Shader.h"
#include "..\Engine\Camera.h"
#include "..\Engine\Light.h"
#include "..\Engine\Plane.h"
#include "Scene.h"

//*****************************************************************************
//
// �N���X�錾
//
//*****************************************************************************
class Scene02 : public Scene
{
private:
	string				mSceneName;
	Shader*				shader2D;			// �V�F�[�_�[
	//Shader*				shader3D;			// �V�F�[�_�[
	Camera*				camera;				// �J����
	Light*				light;				// ���C�g
	Plane*				field;				// �t�B�[���h
	//SkyBox*				skyBox;				// �X�J�C�{�b�N�X

public:
	Character*			woman;			// �v���[���[

	Scene02();
	~Scene02();

	void Initialization();	// ������
	void Update();			// �X�V
	void Draw();			// �`��
	void oneFrame();		// 1�t���[���̕`����e
	void SetRenderState();	// �����_�����O��ݒ�
};
#endif // !_SCENE02_H_

