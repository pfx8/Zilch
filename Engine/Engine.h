//*****************************************************************************
//
// �G���W���R�A�t�@�C�� [Engine.h]
//
// Author : LIAO HANCHEN
//
//*****************************************************************************
#define _CRT_SECURE_NO_WARNINGS			// scanf ��warning�h�~

#ifndef _ENGINE_H_
#define _ENGINE_H_

//*****************************************************************************
//
// �w�b�h�t�@�C��
//
//*****************************************************************************
// DirectX9.0 and Windows
#include <windows.h>
#include <d3dx9.h>
#include <tchar.h>
#include <time.h>
#include <dinput.h>

// c++
#include <iostream>
#include <string>
#include <vector>
#include <map>

// ����w�b�h�t�@�C��
#include "Camera.h"
#include "Console.h"
#include "DebugMessage.h"
#include "input.h"
#include "Light.h"
#include "Material.h"
#include "Plane.h"
#include "ResourcesManager.h"
#include "SceneManager.h"
#include "Shader.h"
#include "SkyBox.h"
#include "Sound.h"
#include "StateMachine.h"
#include "StateMachineManager.h"

#include "..\GameObject\GameObject.h"
#include "..\Component\Component.h"

//*****************************************************************************
//
// �ˑ��t�@�C��
//
//*****************************************************************************
#if 1	// [������"0"�ɂ����ꍇ�A"�\���v���p�e�B" -> "�����J" -> "����" -> "�ǉ��̈ˑ��t�@�C��"�ɑΏۃ��C�u������ݒ肷��]
#pragma comment (lib, "d3d9.lib")
#pragma comment (lib, "d3dx9.lib")
#pragma comment (lib, "dinput8.lib")
#pragma comment (lib, "dxguid.lib")
#pragma comment (lib, "dsound.lib" )
#pragma comment (lib, "winmm.lib")

#endif

//*****************************************************************************
//
// �}�N����`
//
//*****************************************************************************
#define CLASS_NAME		_T("D3d9Class")		// �E�C���h�E�̃N���X��
#define WINDOW_NAME		_T("Project : Zilch")		// �E�C���h�E�̃L���v�V������
#define SCREEN_WIDTH		(960)				// �E�C���h�E�̕�
#define SCREEN_HEIGHT		(540)				// �E�C���h�E�̍���

#define RELEASE_POINT(ptr)					{ if(ptr) { (ptr)->Release(); (ptr) = NULL; } }
#define RELEASE_CLASS_POINT(ptr)			{ if(ptr) { delete ptr; } }
#define RELEASE_CLASS_ARRY_POINT(ptr)		{ if(ptr) { delete [] ptr;} }

#define	FVF_DX_VERTEX_3D		(D3DFVF_XYZ | D3DFVF_DIFFUSE)
// ���_�t�H�[�}�b�g
typedef struct DX_VERTEX_3D
{
	// ���_���̕ϐ��̏��Ԃ͒��_�t�H�[�}�b�g�̂Ɠ���
	D3DXVECTOR4 position;		// ���_���W
	D3DCOLOR diffuse;			// ���ˌ�
}DX_VERTEX_3D;

//*****************************************************************************
//
// �\���̒�`
//
//*****************************************************************************
// �e�N�X�`���\����
typedef struct TextureStruct
{
	const char*			Name;			// �e�N�X�`�����O
	const char*			Path;			// �e�N�X�`���p�X
	LPDIRECT3DTEXTURE9		TexturePoint;		// �e�N�X�`���|�C���^
}TextureStruct;

//*****************************************************************************
//
// �񋓑̒�`
//
//*****************************************************************************
enum RenderStatus
{
	RS_withoutLight,
	RS_withLight,
	RS_withNormalMap,
};

//*****************************************************************************
//
// �v���g�^�C�v�錾
//
//*****************************************************************************
LPDIRECT3DDEVICE9 GetDevice(void);

#endif // !_ENGINE_H_