//*****************************************************************************
//
// GUI����[GUI.h]
//
// Author : LIAO HANCHEN
//
// ImGui�𗘗p����GUI���\�z����
// 
//****************************************************************************
#ifndef _GUI_H_
#define _GUI_H_

#include "Engine.h"
#include "GameTimes.h"
#include "SceneManager.h"

#include "GameObject/GameObject.h"

//*****************************************************************************
//
// �N���X�錾
//
//*****************************************************************************
class GUI
{
private:
	bool				mIsWireframe;							// ���C���t���[���`�F�b�N
	char				mNewGameObjectName[20] = {NULL};		// �ő�19����

	const char*			mColorRamp[2] {u8"���j�A", u8"���"};
	const char*			mShadingMode[4] {u8"�f�B�t���[�Y", u8"�m�[�}��", u8"�e�N�X�`���F", u8"�V�F�[�f�B���O"};

public:
	bool				mIsAddingModel;							// ���f���ǂݍ���ł���`�F�b�N
	bool				mIsDropFileError;						// �h���b�v���ꂽ�t�@�C�����ΏۊO�G���[
	string				mAddingFilePath = {" "};				// �h���b�v���ꂽ�t�@�C���̃p�X��ۑ�

	GUI();
	~GUI();

	void start(HWND hWnd, LPDIRECT3DDEVICE9 D3DDevice);		// ImGui������

	void draw();											// ImGui�̕`�揈��
	void systemGUI();										// �V�X�e������GUI
	void sceneGUI();										// �V�[��GUI
	void createNewGameObjectGUI();							// �V����GameObject����胁�j���[
	
	bool isAnyImGuiFocused();								// ImGui�ƃA�v���P�[�V�����̑��앪��
	void addModelImGui();									// ���f���ǉ�GUI
	bool isGameObjectNameRight(string name);				// �`�F�b�N�ǉ�GameObject���O
	void dropFileErrorGUI();								// �h���b�v���ꂽ�t�@�C�����ΏۊO�G���[GUI
};

#endif // !_GUI_H_
