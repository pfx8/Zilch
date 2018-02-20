//*****************************************************************************
//
// D3DTutorial���� [Scene00.h]
//
// Author : LIAO HANCHEN
//
//*****************************************************************************
#ifndef _SCENE00_H_
#define _SCENE00_H_

#include <map>

#include "ResourcesManager.h"
#include "Engine.h"

#include "Modules\Scene.h"
#include "Modules\Character.h"
#include "Modules\Camera.h"
#include "Modules\Plane.h"
#include "Modules\Light.h"
#include "Modules\Shader.h"
#include "Modules\SkyBox.h"
#include "Modules\Billboard.h"

#include "Shader\CelShader.h"
#include "Shader\ShadowMapShader.h"

#define ENEMY_MAX		(1)
#define BULLET_MAX		(21)
#define BILLBOARD_MAX	(4)

//*****************************************************************************
//
// �N���X�錾
//
//*****************************************************************************
class Scene00 : public Scene
{
private:
	Camera*				camera;		// �J����
	CelShader*			celShader;	// �g�D�\���V�F�[�_�[

	Shader*				shader;				// �x�[�V�b�N�V�F�[�_�[
	Plane*				sea;				// �t�B�[���h�C
	Light*				directionLight;		// ���C�g
	SkyBox*				skyBox;				// �X�J�C�{�b�N�X

	LPDIRECTSOUNDBUFFER8 seHit;

	//BillBoard*		billboard;

	//ShadowMapShader*	shadowMap;	// �V���h�[�}�b�v

public:
	Character*			ship;			// �v���[���[

	Scene00();
	~Scene00();

	void InitScene00();		// ������
	void Update();			// �X�V
	void Draw();			// �`��
	void Control();			// ����֐�
	void SetRenderState();	// �����_�����O��ݒ�
};

#endif // !_SCENE00_H_

