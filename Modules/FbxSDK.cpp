//*****************************************************************************
//
// FbxSDK���� [FbxSDK.cpp]
//
// Author : LIAO HANCHEN
//
//*****************************************************************************
#include "FbxSdk.h"

//*****************************************************************************
//
// �R���X�g���N�^
//
//*****************************************************************************
FbxSDK::FbxSDK()
{
	manager = NULL;
	importer = NULL;
	scene = NULL;
}

//*****************************************************************************
//
// �f�X�g���N�^
//
//*****************************************************************************
FbxSDK::~FbxSDK()
{
	// SDK�}�l�W�����g���I������
	manager->fbxsdk::FbxManager::Destroy();
}

//*****************************************************************************
//
// SDK�}�l�W�����g��������
//
//*****************************************************************************
HRESULT FbxSDK::InitFbxSDK()
{
	// SDK�}�l�[�W������
	manager = fbxsdk::FbxManager::Create();
	if (manager == NULL)
	{
		std::cout << "[Error] SDK Manager ... Fail!" << std::endl;
		return E_FAIL;
	}

	// FBX�C���|�[�g�𐶐�
	importer = fbxsdk::FbxImporter::Create(manager, "");
	if (manager == NULL)
	{
		std::cout << "[Error] SDK Manager ... Fail!" << std::endl;
		return E_FAIL;
	}
	
	// �V�[���𐶐�
	scene = fbxsdk::FbxScene::Create(manager, "");

	return S_OK;
}

//*****************************************************************************
//
// FBX���f����ǂݍ���
//
//*****************************************************************************
HRESULT FbxSDK::LoadFbx(std::string fbxPath)
{
	if (!importer->Initialize(fbxPath.c_str()))
	{
		std::cout << "[Error] Importer Initialize ... Fail!" << std::endl;
		return E_FAIL;
	}

	return S_OK;
}