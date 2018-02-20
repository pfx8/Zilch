//*****************************************************************************
//
// FbxSDK���� [FbxSDK.cpp]
//
// Author : LIAO HANCHEN
//
//*****************************************************************************
#include "FbxSdk.h"

using namespace fbxsdk;

//*****************************************************************************
//
// �R���X�g���N�^
//
//*****************************************************************************
FBX_SDK::FBX_SDK()
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
FBX_SDK::~FBX_SDK()
{
	// �I������
	m_importer->FbxImporter::Destroy();
	m_scene->FbxScene::Destroy();
	m_manager->FbxManager::Destroy();
}

//*****************************************************************************
//
// FbxSDK��������
//
//*****************************************************************************
HRESULT FBX_SDK::InitFbxSDK()
{
	// �R���\�[���̒��ɍ����珈�����镔���̖��O���o��
	std::cout << "<FbxSDK>" << std::endl;

	// SDK�}�l�[�W������
	m_manager = FbxManager::Create();
	if (m_manager == NULL)
	{
		std::cout << "[Error]SDK Manager -- Failed!" << std::endl;
		return E_FAIL;
	}
	std::cout << "[Information]SDK Manager -- Success!" << std::endl;

	// FBX�C���|�[�g�𐶐�
	m_importer = FbxImporter::Create(m_manager, "");
	if (m_manager == NULL)
	{
		std::cout << "[Error]Importer Initialize ... Failed!" << std::endl;
		return E_FAIL;
	}
	std::cout << "[Information]Importer Initialize ... Success!" << std::endl;

	return S_OK;
}

//*****************************************************************************
//
// Fbx��ǂݍ���
//
//*****************************************************************************
HRESULT FBX_SDK::LoadFbxScene(std::string fbxPath)
{
	if (!m_importer->Initialize(fbxPath.c_str()))
	{
		std::cout << "[Error]Loading FBX ... Failed!" << std::endl;
		return E_FAIL;
	}
	std::cout << "[Information]Loading FBX " << fbxPath.c_str() << " ... Success!" << std::endl;

	// �V�[���𐶐�
	m_scene = FbxScene::Create(m_manager, "");
	if (!m_importer->Import(m_scene))
	{
		std::cout << "[Error]Importer Scene ... Failed!" << std::endl;
		return E_FAIL;
	}
	std::cout << "[Information]Importer Scene ... Success!" << std::endl;

	// �R���\�[���̒��ɍ����珈�����镔���̖��O���o��
	std::cout << std::endl << "<Node>" << std::endl;
	// ���[�g�̃m�[�h���擾
	m_rootnode = m_scene->GetRootNode();
	// Fbx�V�[�����̂��ׂẴm�[�h���g���o�[�T��
	ProbeNode(m_rootnode);

	return S_OK;
}

//*****************************************************************************
//
// �V�[���̉��ɂ���FBX�m�[�h��T��
//
//*****************************************************************************
void FBX_SDK::ProbeNode(FbxNode* node)
{
	if (node)
	{
		// �m�[�h�̑��������擾
		FbxNodeAttribute* attribute = node->GetNodeAttribute();
		if (attribute != NULL)
		{
			// �����𔻒f
			switch (attribute->GetAttributeType())
			{
			case FbxNodeAttribute::eMesh: // ���b�V��
				std::cout << " |-" << node->FbxObject::GetName()
					<< " -> [Mesh] ... " << node->GetName() << std::endl;
				// ���b�V�����擾
				m_mesh = node->FbxNode::GetMesh();

				// �}�e���A����ǂݍ���
				LoadMaterial(m_mesh);

				break;

			case FbxNodeAttribute::eLight: // ���C�g
				std::cout << " |-" << node->FbxObject::GetName()
					<< " -> [Light]" << std::endl;
				break;

			case	 FbxNodeAttribute::eCamera: // �J����
				std::cout << " |-" << node->FbxObject::GetName()
					<< " -> [Camera]" << std::endl;
				break;

			default:
				break;
			}
		}

		// �ċA�֐��ɂ���
		for (int count = 0; count < node->FbxNode::GetChildCount(); count++)
		{
			// �e�m�[�h�ɂ��q�m�[�h��T��
			ProbeNode(node->GetChild(count));
		}
	}
}

//*****************************************************************************
//
// �}�e���A����ǂݍ���
//
//*****************************************************************************
bool FBX_SDK::LoadMaterial(FbxMesh* mesh)
{
	// ���b�V������m�[�h���擾
	FbxNode* node = mesh->GetNode();

	int materialNum = node->GetMaterialCount();	//�@�}�e���A�������擾
	
	if (materialNum == 0)
	{
		return false;	// �}�e���A�����Ȃ��̂ŁA�ǂݍ��݂ł����Ȃ�
	}
	else
	{
		std::cout << " |-�}�e���A��" << std::endl;

		for (int count = 0; count < materialNum; count++)
		{
			FbxSurfaceMaterial* material = node->GetMaterial(count);

			// �}�e���A���̃v���p�e�B���擾
			FbxProperty prop = material->FindProperty(FbxSurfaceMaterial::sDiffuse);

			int texFileNum = prop.GetSrcObjectCount<FbxFileTexture>();

			for (int count = 0; count < texFileNum; count++)
			{
				FbxFileTexture* texture = prop.GetSrcObject<FbxFileTexture>(count);

				// �ǂݍ��݂�����������
				if (texture != NULL)
				{
					// �e�N�X�`���t�@�C���̖��O���o��
					const char* texName = texture->GetRelativeFileName();
					std::cout << "  |-Tex" << count << " ... " << texName << std::endl;

					// UV�Z�b�g�̖��O���擾
					const char* uvSetName = texture->UVSet.Get().Buffer();
					std::cout << "  |-UVset" << count << " ... " << uvSetName << std::endl;
				}
			}
			
			/*
			// �v���p�e�B�ɕ����̃e�N�X�`�����A�^�b�`����Ă��邩�ۂ��Ŕ��ʂ���
			int layeredTexNum = prop.GetSrcObjectCount<FbxLayeredTexture>();
				
			if (layeredTexNum > 0)
			{
				// �����e�N�X�`�����A�^�b�`����Ă���ꍇ
				for (int count = 0; count < layeredTexNum; count++)
				{
					// �e�N�X�`�����擾
					FbxLayeredTexture* layeredTex = prop.GetSrcObject<FbxLayeredTexture>();
					// ���C���[�X���擾
					int layeredNum = layeredTex->GetSrcObjectCount<FbxFileTexture>();
					// ���C���[���J��Ԃ��ăe�N�X�`�����擾
					for (int count = 0; count < layeredNum; count++)
					{
						FbxFileTexture* texture = prop.GetSrcObject<FbxFileTexture>(count);

						// �ǂݍ��݂�����������
						if (texture != NULL)
						{
							// �e�N�X�`���t�@�C���̖��O���o��
							std::cout << texture->GetRelativeFileName();
							// UV�Z�b�g�̖��O���擾
							std::string uvSetName = texture->UVSet.Get().Buffer();
						}
					}
				}
			}
			else
			{
				// �P��e�N�X�`�����A�^�b�`����Ă���ꍇ
				int texFileNum = prop.GetSrcObjectCount<FbxFileTexture>();

				for (int count = 0; count < texFileNum; count++)
				{
					FbxFileTexture* texture = prop.GetSrcObject<FbxFileTexture>(count);

					// �ǂݍ��݂�����������
					if (texture != NULL)
					{
						// �e�N�X�`���t�@�C���̖��O���o��
						std::cout << texture->GetRelativeFileName();
						// UV�Z�b�g�̖��O���擾
						std::string uvSetName = texture->UVSet.Get().Buffer();
					}
				}
			}*/
		}
	}

	return true;
}

//*****************************************************************************
//
// Fbx�f�[�^��DX�֓]������
//
//*****************************************************************************
HRESULT FBX_SDK::FbxMeshToDirectXMesh(DX_MESH* dxMesh)
{
	if (m_mesh != NULL)
	{
		// �R���\�[���Ƀ��b�Z�[�W���o��	
		std::cout << std::endl << "<FbxToDx>" << std::endl;
		
		{
			// �|���S��
			int polygonNum = m_mesh->GetPolygonCount(); // �|���S����
			dxMesh->m_polygonNum = polygonNum;
			std::cout << " �|���S���� - " << polygonNum << std::endl;
		}

		{
			// ���_
			int vertexNum = m_mesh->GetControlPointsCount();		// ���_��
			dxMesh->m_vertexNum = vertexNum;

			FbxVector4* vertexArray = m_mesh->GetControlPoints(); // ���_�z��|�C���^

			dxMesh->m_vertex = new DX_VERTEX_3D[dxMesh->m_vertexNum];

			//std::cout << "---->" << sizeof(dxMesh->m_vertex) << std::endl;

			for (int count = 0; count < vertexNum; count++)
			{
				// ���_���W��DXMesh�ɓ]��
				dxMesh->m_vertex[count].position.x = vertexArray[count][0];
				dxMesh->m_vertex[count].position.y = vertexArray[count][1];
				dxMesh->m_vertex[count].position.z = vertexArray[count][2];
				dxMesh->m_vertex[count].position.w = vertexArray[count][3];

				// �R���\�[���Ƀf�[�^���o��
				/*std::cout << "  ���_ " << count + 1 << " ("
				<< VertexArray[count][0] << ", "
				<< VertexArray[count][1] << ", "
				<< VertexArray[count][2] << ", "
				<< VertexArray[count][3] << ") - ("
				<< dxMesh->m_vertex3D->position.x << ", "
				<< dxMesh->m_vertex3D->position.y << ", "
				<< dxMesh->m_vertex3D->position.z << ", "
				<< dxMesh->m_vertex3D->position.w << ")"
				<< std::endl;*/
			}
		}

		{
			// �C���f�b�N�X
			int IndexNum = m_mesh->GetPolygonVertexCount(); // ���_�C���f�b�N�X��
			dxMesh->m_IndexNum = IndexNum;

			int* indexArray = m_mesh->GetPolygonVertices();			 // ���_�C���f�b�N�X�z��|�C���^
			dxMesh->m_Index = new int[dxMesh->m_IndexNum];

			for (int count = 0; count < IndexNum; count++)
			{
				// �C���f�b�N�X��DXMesh�ɓ]��
				dxMesh->m_Index[count] = indexArray[count];
				//std::cout << indexArray[count]
			}
		}

		{
			// ���_�@��
			//FbxArray<FbxVector4> normals;		// Vec4�z��
			//m_mesh->GetPolygonVertexNormals(normals);	// �@�����擾

			//// ���_�@�������o���A���_���Ɠ����ׂ�
			//std::cout << " ���_�@���� - " << normals.Size() << std::endl;

			//for (int count = 0; count < normals.Size(); count++)
			//{
			//	// �e���_�̖@�����o��
			//	const FbxVector4 n = normals[count];

			//	// ���_�@����DXMesh�ɓ]��
			//	dxMesh->m_vertex->normal.x = n[0];
			//	dxMesh->m_vertex->normal.y = n[1];
			//	dxMesh->m_vertex->normal.z = n[2];
			//	dxMesh->m_vertex->normal.w = n[3];

			//	// �R���\�[���Ƀf�[�^���o��
			//	/*std::cout << "  �@��" << count + 1 << " ("
			//	<< n[0] << ", "
			//	<< n[1] << ", "
			//	<< n[2] << ", "
			//	<< n[3] << ") - ("
			//	<< dxMesh->m_vertex3D->normal.x << ", "
			//	<< dxMesh->m_vertex3D->normal.y << ", "
			//	<< dxMesh->m_vertex3D->normal.z << ", "
			//	<< dxMesh->m_vertex3D->normal.w << ")"
			//	<< std::endl;*/
			//}
			
		}

		/*{
			// UV���W
			FbxStringList uvSetName;			// �����񃊃X�g
			m_mesh->GetUVSetNames(uvSetName);	// UV�Z�b�g���X�g���擾

			if (uvSetName.GetCount() > 0)
			{
				// �����e�N�X�`���̂���
				for (int count = 0; count < uvSetName.GetCount(); count++)
				{
					// ����UV������Ζ��O���o��
					std::cout << " UV�}�b�v" << count + 1 << " ... "
						<< uvSetName.GetStringAt(count) << std::endl;

					FbxArray<FbxVector2> uvSets;	// Vec2�z��
					m_mesh->GetPolygonVertexUVs(uvSetName.GetStringAt(count), uvSets);	// UV�Z�b�g���擾

					std::cout << "  UV���_�� - " << uvSets.Size() << std::endl;

					for (int count = 0; count < uvSets.Size(); count++)
					{
						FbxVector2 uv = uvSets[count];

						// UV���W��DXMesh�ɓ]��
						dxMesh->m_vertex3D->UVposition.x = uv[0];
						dxMesh->m_vertex3D->UVposition.y = uv[1];

						// �R���\�[���Ƀf�[�^���o��
						std::cout << "   UV���_" << count + 1 << " ("
						<< uv[0] << ", "
						<< uv[1] << ")"
						<< std::endl;
					}
					
				}
			}
			else
			{
				std::cout << " [Warning]UV�}�b�v���t���ĂȂ�!" << std::endl;
			}
		}*/
	}

	return S_OK;
}