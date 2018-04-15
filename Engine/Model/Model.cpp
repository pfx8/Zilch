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
Model::Model(string const &path)
{
	// モデルの名前を取得
	string fileName = path.substr(path.find_last_of("/") + 1, path.find_first_of("."));	// exp c:/aaa/bbb/ccc.fbx -> ccc.fbx
	cout << endl << "<Model> : ["  << fileName << "]" << endl;

	loadModel(path);

	//cout << "   <Mesh Nums> : [" << mMeshes.size() << "]" << endl;
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
HRESULT Model::loadModel(string const &mPath)
{
	Assimp::Importer import;			// Assimpのインポートを作る
	const aiScene *scene = import.ReadFile(mPath, aiProcessPreset_TargetRealtime_Quality | aiProcess_FixInfacingNormals | aiProcess_ConvertToLeftHanded);

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
		this->mMeshes.push_back(new Mesh(aiMesh, scene));
	}

	// 子供ノードを同じように処理する
	for (unsigned int count = 0; count < node->mNumChildren; count++)
	{
		processNode(node->mChildren[count], scene);
	}
}

//*****************************************************************************
//
// モデルを描画
//
//*****************************************************************************
void Model::draw(Transform* trans, Camera* camera)
{
	// 各メッシュを描画
	for (auto it : mMeshes)
	{
		it->draw(trans, camera);
	}
}