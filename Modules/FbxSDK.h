//*****************************************************************************
//
// FbxSDK���� [FbxSDK.h]
//
// Author : LIAO HANCHEN
//
//*****************************************************************************

#ifndef _FBX_SDK_H_
#define _FBX_SDK_H_

#include <fbxsdk.h>

#include "../Engine.h"

class FbxSDK
{
private:
	FbxManager*  m_manager;	// SDK�}�l�W�����g
	FbxImporter* m_importer;	// FBX�ǂݍ��݃C���|�[�g
	FbxScene*	m_scene;		// �V�[��

public:
	FbxSDK();
	~FbxSDK();

	HRESULT InitFbxSDK();	// SDK�}�l�W�����g��������
};

#endif // !_FBX_SDK_H_


