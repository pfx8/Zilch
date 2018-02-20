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
	m_manager = NULL;
	m_importer = NULL;
	m_scene = NULL;
}

//*****************************************************************************
//
// �f�X�g���N�^
//
//*****************************************************************************
FbxSDK::~FbxSDK()
{
	// SDK�}�l�W�����g���I������
	m_manager->fbxsdk::FbxManager::Destroy();
}

//*****************************************************************************
//
// SDK�}�l�W�����g��������
//
//*****************************************************************************
HRESULT FbxSDK::InitFbxSDK()
{
	// SDK�}�l�[�W������
	m_manager = fbxsdk::FbxManager::Create();
	if (m_manager == NULL)
	{
		std::cout << "[Error]SDK Manager -- Failed!" << std::endl;
		return E_FAIL;
	}

	// FBX�C���|�[�g�𐶐�
	m_importer = fbxsdk::FbxImporter::Create(m_manager, "");
	if (m_manager == NULL)
	{
		std::cout << "[Error]SDK Manager -- Failed!" << std::endl;
		return E_FAIL;
	}
	const char* filePath = "data/MODEL/lowP.fbx";
	if (!m_importer->Initialize(filePath)) 
	{
		std::cout << "[Error]Importer Initialize -- Failed!" << std::endl;
		return E_FAIL;
	}
	
	// �V�[���𐶐�
	m_scene = fbxsdk::FbxScene::Create(m_manager, "");
}