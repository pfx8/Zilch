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
// ImGui
#include "../FrameWork/ImGui/imgui.h"
#include "../FrameWork/ImGui/imgui_impl_dx9.h"
#include "../FrameWork/ImGui/imgui_internal.h"

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
#include <unordered_map>				// �y�A�֌W�����ŏ��Ԃɂ���K�v���Ȃ��̂�map����unordered_map�ɕύX����

// Assimp
#include "../FrameWork/assimp/include/assimp/Importer.hpp"
#include "../FrameWork/assimp/include/assimp/scene.h"
#include "../FrameWork/assimp/include/assimp/postprocess.h"


// FMOD
#include "../FrameWork/FMOD/include/fmod.hpp"
#include "../FrameWork/FMOD/include/fmod_errors.h"

using namespace std;

//*****************************************************************************
//
// �N���X�錾
//
//*****************************************************************************
class GUI;
class GameTimes;
class MeshRender;
class Scene;
class Component;
class Texture;
class Material;
class Bone;
class Mesh;
class Model;
class Resources;
class SceneManager;

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
#pragma comment (lib, "winmm.lib")
#pragma comment (lib, "FrameWork/FMOD/lib/fmod_vc.lib")						// fmod
#pragma comment (lib, "FrameWork/assimp/lib/x86/assimp-vc140-mt.lib")		// assimp
#endif

//*****************************************************************************
//
// �}�N����`
//
//*****************************************************************************
#define CLASS_NAME							_T("D3d9Class")				// �E�C���h�E�̃N���X��
#define WINDOW_NAME							_T("Project : Zilch")		// �E�C���h�E�̃L���v�V������
#define SCREEN_WIDTH						(1280)						// �E�C���h�E�̕�
#define SCREEN_HEIGHT						(720)						// �E�C���h�E�̍���
#define NUM_BONES_PER_VEREX					(4)							// ���_1���e������鍜�̍ő吔��4�{

#define RELEASE_POINT(ptr)					{ if(ptr) { (ptr)->Release(); (ptr) = NULL; } }
#define RELEASE_CLASS_POINT(ptr)			{ if(ptr) { delete ptr; } }
#define RELEASE_CLASS_ARRY_POINT(ptr)		{ if(ptr) { delete [] ptr;} }

#define	FVF_DX_VERTEX_3D					(D3DFVF_XYZ | D3DFVF_DIFFUSE)

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
// �\���̒�`
//
//*****************************************************************************
struct WorldVector
{
	// �Q�[�����E��3��
	D3DXVECTOR3			worldLook = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
	D3DXVECTOR3			worldUp = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	D3DXVECTOR3			worldRight = D3DXVECTOR3(1.0f, 0.0f, 0.0f);
};

//*****************************************************************************
//
// �v���g�^�C�v�錾
//
//*****************************************************************************
LPDIRECT3DDEVICE9 getD3DDevice(void);
Resources* getResources(void);
GameTimes* getGameTimes(void);
SceneManager* getSceneManager(void);

#endif // !_ENGINE_H_