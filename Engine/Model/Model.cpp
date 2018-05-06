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
Model::Model(MeshType type, string name, string const &path)
{
	// メッシュタイプを初期化
	this->mMeshType = type;
	switch (this->mMeshType)
	{
	case MT_default:
		cout << "<Model><default> : " << name;
		break;
	case MT_withBone:
		cout << "<Model><withBone> : " << name;
		break;
	}

	// モデルの名前を初期化
	this->mName = name;

	// Assimpでモデルを読み込み
	loadModel(path);
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

	cout << " loading ... success!" << endl;

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
// ノードをトラバース
//
//*****************************************************************************
void Model::traverseNode(Node* node, unsigned int level)
{
	string space;

	for (unsigned count = 0; count < level; count++)
	{
		space += "  ";
	}

	ImGui::Text("%s%s", space.c_str(), node->mName.c_str());

	for (auto it : node->mChildren)
	{
		traverseNode(it, level + 1);
	}
}

//*****************************************************************************
//
// モデルを描画
//
//*****************************************************************************
void Model::drawModel(Shader* shader)
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
		it->drawModel(shader);
	}
}

//*****************************************************************************
//
// モデルのシャドウマップを描画
//
//*****************************************************************************
void Model::drawShadow(Shader* shader)
{
	// 各メッシュのシャドウマップを描画
	for (auto it : mMeshes)
	{
		it->drawShadow(shader);
	}
}