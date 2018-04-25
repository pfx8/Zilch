//*****************************************************************************
//
// モデル処理 [Model.cpp]
//
// Author : LIAO HANCHEN
//
//*****************************************************************************
#include "Model.h"

//*****************************************************************************
//
// コンストラクタ
//
//*****************************************************************************
Model::Model(MeshType type, string const &path)
{
	// メッシュタイプを取得
	this->mMeshType = type;
	// モデルの名前を取得
	string fileName = path.substr(path.find_last_of("/") + 1, path.find_first_of("."));	// exp c:/aaa/bbb/ccc.fbx -> ccc

	switch (this->mMeshType)
	{
	case MT_default:
		cout << endl << "<Model><default> : [" << fileName << "]" << endl;
		break;
	case MT_withBone:
		cout << endl << "<Model><withBone> : [" << fileName << "]" << endl;
		break;
	}

	loadModel(path);

	// モデル構造をdebugウインドに出す
	//unsigned msehNum = 0;
	//unsigned int meshesNum = 1;
	//for (auto it : this->mMeshes)
	//{
	//	cout << "  |- <Mesh><No." << meshesNum << "> : [" << it->mName << "]" << endl;
	//	meshesNum++;

	//	// material
	//	unsigned int materialsNum = 1;
	//	for (auto it1 : it->mMaterials)
	//	{
	//		cout << "    |- <Material><No." << materialsNum << "> : [" << it1->mName << "]" << endl;
	//		materialsNum++;

	//		// texture
	//		unsigned int texturesNum = 1;
	//		for (auto it2 : it1->mTextures)
	//		{
	//			cout << "      |- <Texture><No." << texturesNum << "> : [" << it2->mName << "]" << endl;
	//			texturesNum++;
	//		}
	//	}
	//}

	// ImGuiでメッシュの構築を表示
	//ImGui::Begin("Model");
	//スクロール
}

//*****************************************************************************
//
// デストラクタ
//
//*****************************************************************************
Model::~Model()
{
	// delete vector
}

//*****************************************************************************
//
// モデルをロードする
//
//*****************************************************************************
HRESULT Model::loadModel(string const &path)
{
	Assimp::Importer import;			// Assimpのインポートを作る
	const aiScene *scene = import.ReadFile(path, aiProcessPreset_TargetRealtime_Quality | aiProcess_FixInfacingNormals | aiProcess_ConvertToLeftHanded);

	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
	{
		cout << "[Error] Assimp::" << import.GetErrorString() << endl;
		return E_FAIL;
	}

	// ルートノードから処理を始める
	processNode(scene->mRootNode, scene);

	return S_OK;
}

//*****************************************************************************
//
// ノード処理
//
//*****************************************************************************
void Model::processNode(aiNode *node, const aiScene *scene)
{
	// もし今のノードにメッシュがあれば処理する
	for (unsigned int count = 0; count < node->mNumMeshes; count++)
	{
		// sceneのmMeshesは本当のメッシュデータ、一歩でnodeのmMesherはメッシュのインデックス
		aiMesh* aiMesh = scene->mMeshes[node->mMeshes[count]];
		this->mMeshes.push_back(new Mesh(this->mMeshType, aiMesh, this->mBones, scene));
	}

	// ノードメッセージを保存

	// 子供ノードを同じように処理する
	for (unsigned int count = 0; count < node->mNumChildren; count++)
	{
		processNode(node->mChildren[count], scene);
	}
}

//*****************************************************************************
//
// アニメーションデータを読み込み
//
//*****************************************************************************
void Model::addAnimation(Animation* animation)
{
	this->mAnimationes.push_back(animation);
}

//*****************************************************************************
//
// アニメーション更新
//
//*****************************************************************************
void Model::updateAnimation(float timeInSeconds)
{
	this->mAnimationes[this->mCurAnimation]->updateBoneTransforms(timeInSeconds, this->mBones, this->mTransforms);
}

//*****************************************************************************
//
// モデルのシャドウマップを描画
//
//*****************************************************************************
void Model::draw(Shader* shader)
{
	// 各メッシュのシャドウマップを描画
	for (auto it : mMeshes)
	{
		it->draw(shader);
	}
}

//*****************************************************************************
//
// モデルを描画
//
//*****************************************************************************
void Model::draw(Shader* shader, Transform* trans, Camera* camera)
{
	D3DXMATRIX mat[87] = { };

	unsigned int count = 0;
	for (auto it : this->mBones)
	{
		mat[count] = it->mFinaTransform;
		//cout << "<Test><Mat> : " << it->mFinaTransform._11 << ", " << it->mFinaTransform._12 << ", " << it->mFinaTransform._13 << endl;
		count++;
	}

	// 骨の行列をシェーダーに渡す
	HRESULT hr;
	hr = shader->mEffect->SetMatrixArray("boneMatrices", mat, 87);

	// 各メッシュを描画
	for (auto it : mMeshes)
	{
		it->draw(shader, trans, camera);
	}
}