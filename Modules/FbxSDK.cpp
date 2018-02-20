//*****************************************************************************
//
// FbxSDK処理 [FbxSDK.cpp]
//
// Author : LIAO HANCHEN
//
//*****************************************************************************
#include "FbxSdk.h"

using namespace fbxsdk;

//*****************************************************************************
//
// コンストラクタ
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
// デストラクタ
//
//*****************************************************************************
FBX_SDK::~FBX_SDK()
{
	// 終了処理
	m_importer->FbxImporter::Destroy();
	m_scene->FbxScene::Destroy();
	m_manager->FbxManager::Destroy();
}

//*****************************************************************************
//
// FbxSDKを初期化
//
//*****************************************************************************
HRESULT FBX_SDK::InitFbxSDK()
{
	// コンソールの中に今から処理する部分の名前を出す
	std::cout << "<FbxSDK>" << std::endl;

	// SDKマネージャ生成
	m_manager = FbxManager::Create();
	if (m_manager == NULL)
	{
		std::cout << "[Error]SDK Manager -- Failed!" << std::endl;
		return E_FAIL;
	}
	std::cout << "[Information]SDK Manager -- Success!" << std::endl;

	// FBXインポートを生成
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
// Fbxを読み込み
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

	// シーンを生成
	m_scene = FbxScene::Create(m_manager, "");
	if (!m_importer->Import(m_scene))
	{
		std::cout << "[Error]Importer Scene ... Failed!" << std::endl;
		return E_FAIL;
	}
	std::cout << "[Information]Importer Scene ... Success!" << std::endl;

	// コンソールの中に今から処理する部分の名前を出す
	std::cout << std::endl << "<Node>" << std::endl;
	// ルートのノードを取得
	m_rootnode = m_scene->GetRootNode();
	// Fbxシーン中のすべてのノードをトラバーサル
	ProbeNode(m_rootnode);

	return S_OK;
}

//*****************************************************************************
//
// シーンの下にあるFBXノードを探査
//
//*****************************************************************************
void FBX_SDK::ProbeNode(FbxNode* node)
{
	if (node)
	{
		// ノードの属性数を取得
		FbxNodeAttribute* attribute = node->GetNodeAttribute();
		if (attribute != NULL)
		{
			// 属性を判断
			switch (attribute->GetAttributeType())
			{
			case FbxNodeAttribute::eMesh: // メッシュ
				std::cout << " |-" << node->FbxObject::GetName()
					<< " -> [Mesh] ... " << node->GetName() << std::endl;
				// メッシュを取得
				m_mesh = node->FbxNode::GetMesh();

				// マテリアルを読み込み
				LoadMaterial(m_mesh);

				break;

			case FbxNodeAttribute::eLight: // ライト
				std::cout << " |-" << node->FbxObject::GetName()
					<< " -> [Light]" << std::endl;
				break;

			case	 FbxNodeAttribute::eCamera: // カメラ
				std::cout << " |-" << node->FbxObject::GetName()
					<< " -> [Camera]" << std::endl;
				break;

			default:
				break;
			}
		}

		// 再帰関数にする
		for (int count = 0; count < node->FbxNode::GetChildCount(); count++)
		{
			// 親ノードにより子ノードを探査
			ProbeNode(node->GetChild(count));
		}
	}
}

//*****************************************************************************
//
// マテリアルを読み込み
//
//*****************************************************************************
bool FBX_SDK::LoadMaterial(FbxMesh* mesh)
{
	// メッシュからノードを取得
	FbxNode* node = mesh->GetNode();

	int materialNum = node->GetMaterialCount();	//　マテリアル数を取得
	
	if (materialNum == 0)
	{
		return false;	// マテリアルがないので、読み込みできあない
	}
	else
	{
		std::cout << " |-マテリアル" << std::endl;

		for (int count = 0; count < materialNum; count++)
		{
			FbxSurfaceMaterial* material = node->GetMaterial(count);

			// マテリアルのプロパティを取得
			FbxProperty prop = material->FindProperty(FbxSurfaceMaterial::sDiffuse);

			int texFileNum = prop.GetSrcObjectCount<FbxFileTexture>();

			for (int count = 0; count < texFileNum; count++)
			{
				FbxFileTexture* texture = prop.GetSrcObject<FbxFileTexture>(count);

				// 読み込みが成功したら
				if (texture != NULL)
				{
					// テクスチャファイルの名前を出す
					const char* texName = texture->GetRelativeFileName();
					std::cout << "  |-Tex" << count << " ... " << texName << std::endl;

					// UVセットの名前を取得
					const char* uvSetName = texture->UVSet.Get().Buffer();
					std::cout << "  |-UVset" << count << " ... " << uvSetName << std::endl;
				}
			}
			
			/*
			// プロパティに複数のテクスチャがアタッチされているか否かで判別する
			int layeredTexNum = prop.GetSrcObjectCount<FbxLayeredTexture>();
				
			if (layeredTexNum > 0)
			{
				// 複数テクスチャがアタッチされている場合
				for (int count = 0; count < layeredTexNum; count++)
				{
					// テクスチャを取得
					FbxLayeredTexture* layeredTex = prop.GetSrcObject<FbxLayeredTexture>();
					// レイヤースを取得
					int layeredNum = layeredTex->GetSrcObjectCount<FbxFileTexture>();
					// レイヤーを繰り返してテクスチャを取得
					for (int count = 0; count < layeredNum; count++)
					{
						FbxFileTexture* texture = prop.GetSrcObject<FbxFileTexture>(count);

						// 読み込みが成功したら
						if (texture != NULL)
						{
							// テクスチャファイルの名前を出す
							std::cout << texture->GetRelativeFileName();
							// UVセットの名前を取得
							std::string uvSetName = texture->UVSet.Get().Buffer();
						}
					}
				}
			}
			else
			{
				// 単一テクスチャがアタッチされている場合
				int texFileNum = prop.GetSrcObjectCount<FbxFileTexture>();

				for (int count = 0; count < texFileNum; count++)
				{
					FbxFileTexture* texture = prop.GetSrcObject<FbxFileTexture>(count);

					// 読み込みが成功したら
					if (texture != NULL)
					{
						// テクスチャファイルの名前を出す
						std::cout << texture->GetRelativeFileName();
						// UVセットの名前を取得
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
// FbxデータをDXへ転送する
//
//*****************************************************************************
HRESULT FBX_SDK::FbxMeshToDirectXMesh(DX_MESH* dxMesh)
{
	if (m_mesh != NULL)
	{
		// コンソールにメッセージを出す	
		std::cout << std::endl << "<FbxToDx>" << std::endl;
		
		{
			// ポリゴン
			int polygonNum = m_mesh->GetPolygonCount(); // ポリゴン数
			dxMesh->m_polygonNum = polygonNum;
			std::cout << " ポリゴン数 - " << polygonNum << std::endl;
		}

		{
			// 頂点
			int vertexNum = m_mesh->GetControlPointsCount();		// 頂点数
			dxMesh->m_vertexNum = vertexNum;

			FbxVector4* vertexArray = m_mesh->GetControlPoints(); // 頂点配列ポインタ

			dxMesh->m_vertex = new DX_VERTEX_3D[dxMesh->m_vertexNum];

			//std::cout << "---->" << sizeof(dxMesh->m_vertex) << std::endl;

			for (int count = 0; count < vertexNum; count++)
			{
				// 頂点座標をDXMeshに転送
				dxMesh->m_vertex[count].position.x = vertexArray[count][0];
				dxMesh->m_vertex[count].position.y = vertexArray[count][1];
				dxMesh->m_vertex[count].position.z = vertexArray[count][2];
				dxMesh->m_vertex[count].position.w = vertexArray[count][3];

				// コンソールにデータを出す
				/*std::cout << "  頂点 " << count + 1 << " ("
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
			// インデックス
			int IndexNum = m_mesh->GetPolygonVertexCount(); // 頂点インデックス数
			dxMesh->m_IndexNum = IndexNum;

			int* indexArray = m_mesh->GetPolygonVertices();			 // 頂点インデックス配列ポインタ
			dxMesh->m_Index = new int[dxMesh->m_IndexNum];

			for (int count = 0; count < IndexNum; count++)
			{
				// インデックスをDXMeshに転送
				dxMesh->m_Index[count] = indexArray[count];
				//std::cout << indexArray[count]
			}
		}

		{
			// 頂点法線
			//FbxArray<FbxVector4> normals;		// Vec4配列
			//m_mesh->GetPolygonVertexNormals(normals);	// 法線を取得

			//// 頂点法線数を出す、頂点数と同じべき
			//std::cout << " 頂点法線数 - " << normals.Size() << std::endl;

			//for (int count = 0; count < normals.Size(); count++)
			//{
			//	// 各頂点の法線を出す
			//	const FbxVector4 n = normals[count];

			//	// 頂点法線をDXMeshに転送
			//	dxMesh->m_vertex->normal.x = n[0];
			//	dxMesh->m_vertex->normal.y = n[1];
			//	dxMesh->m_vertex->normal.z = n[2];
			//	dxMesh->m_vertex->normal.w = n[3];

			//	// コンソールにデータを出す
			//	/*std::cout << "  法線" << count + 1 << " ("
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
			// UV座標
			FbxStringList uvSetName;			// 文字列リスト
			m_mesh->GetUVSetNames(uvSetName);	// UVセットリストを取得

			if (uvSetName.GetCount() > 0)
			{
				// 複数テクスチャのため
				for (int count = 0; count < uvSetName.GetCount(); count++)
				{
					// もしUVがあれば名前を出す
					std::cout << " UVマップ" << count + 1 << " ... "
						<< uvSetName.GetStringAt(count) << std::endl;

					FbxArray<FbxVector2> uvSets;	// Vec2配列
					m_mesh->GetPolygonVertexUVs(uvSetName.GetStringAt(count), uvSets);	// UVセットを取得

					std::cout << "  UV頂点数 - " << uvSets.Size() << std::endl;

					for (int count = 0; count < uvSets.Size(); count++)
					{
						FbxVector2 uv = uvSets[count];

						// UV座標をDXMeshに転送
						dxMesh->m_vertex3D->UVposition.x = uv[0];
						dxMesh->m_vertex3D->UVposition.y = uv[1];

						// コンソールにデータを出す
						std::cout << "   UV頂点" << count + 1 << " ("
						<< uv[0] << ", "
						<< uv[1] << ")"
						<< std::endl;
					}
					
				}
			}
			else
			{
				std::cout << " [Warning]UVマップが付いてない!" << std::endl;
			}
		}*/
	}

	return S_OK;
}