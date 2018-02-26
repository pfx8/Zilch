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

class FBX
{
private:
	FbxManager*		manager;	// SDK�}�l�W�����g
	FbxImporter*	importer;	// FBX�ǂݍ��݃C���|�[�g
	FbxScene*		scene;		// �V�[��

public:
	FBX();
	~FBX();

	HRESULT InitFbxSDK();					// SDK�}�l�W�����g��������
	HRESULT LoadFbx(std::string fbxPath);	// FBX���f����ǂݍ���
};

#endif // !_FBX_SDK_H_


