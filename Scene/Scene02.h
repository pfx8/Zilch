//*****************************************************************************
//
// �A�j���[�V�������� [Scene02.h]
//
// Author : LIAO HANCHEN
//
//*****************************************************************************
#ifndef _SCENE02_H_
#define _SCENE02_H_

#include "Scene.h"
#include "../Component/Transform.h"
#include "../Component/Camera.h"
#include "../Component/PlayerController.h"
#include "../Component/Camera.h"
#include "../Engine/Shader.h"
#include "../Engine/Light.h"
#include "../Engine/Plane.h"

//*****************************************************************************
//
// �N���X�錾
//
//*****************************************************************************
class Scene02 : public Scene
{
private:

public:
	Scene02();
	~Scene02();

	void start();				// ������
	void draw();			// �`��
};
#endif // !_SCENE02_H_

