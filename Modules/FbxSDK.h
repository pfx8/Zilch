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

#include "Mesh.h"
#include "..\Engine.h"

class FBX_SDK
{
private:
	FbxManager*	m_manager;	// SDK�}�l�W�����g
	FbxImporter*	m_importer;	// FBX�ǂݍ��݃C���|�[�g
	FbxNode*		m_rootnode;	// ���[�g�m�[�h
	FbxScene*	m_scene;		// �V�[��
	FbxMesh*		m_mesh;		// ���b�V��

	void ProbeNode(FbxNode* node);	// �V�[���̉��ɂ���FBX�m�[�h��T��
	bool LoadMaterial(FbxMesh* mesh);	// �}�e���A����ǂݍ���
public:
	FBX_SDK();
	~FBX_SDK();

	HRESULT InitFbxSDK();	// FbxSDK��������
	HRESULT LoadFbxScene(std::string fbxPath = " ");	// Fbx��ǂݍ���
	HRESULT FbxMeshToDirectXMesh(DX_MESH* dxMesh);		// Fbx�f�[�^��DX�֓]������
};

#endif // !_FBX_SDK_H_


