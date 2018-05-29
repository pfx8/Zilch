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
Model::Model(wstring const& path)
{
	// Assimpでモデルを読み込み
	loadModel(path);

	// Debugウインドへ
	wcout << "<Scene> loading <Model> " << path << " ... successed!" << endl;
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
HRESULT Model::loadModel(wstring const& wPath)
{
	// パスを保存
	this->mPath = wPath;
	// Assimpで読み込むためにwstring -> string
	string path = wStringToString(wPath);

	// Assimpのインポートを作る
	Assimp::Importer import;
	// Assimpシーンを作る
	const aiScene* scene = import.ReadFile(path, aiProcessPreset_TargetRealtime_Quality | aiProcess_FixInfacingNormals | aiProcess_ConvertToLeftHanded);

	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
	{
		// Debugウインドへ
		cout << "<Error> Assimp::" << import.GetErrorString() << endl;
		return E_FAIL;
	}

	// モデル情報を取得
	this->mModelInfo.numMeshes = scene->mNumMeshes;
	this->mModelInfo.numMaterials = scene->mNumMaterials;
	this->mModelInfo.numAnimations = scene->mNumAnimations;
	this->mModelInfo.numTextures = scene->mNumTextures;

	// Ex
	this->mModelInfo.numLights = scene->mNumLights;
	this->mModelInfo.numCameras = scene->mNumCameras;

	// アニメーションをチェック
	checkAnimation(scene);

	// ルートノードから処理を始める
	processNode(scene->mRootNode, scene);

	return S_OK;
}

//*****************************************************************************
//
// ノード処理
//
//*****************************************************************************
void Model::processNode(aiNode* node, const aiScene* scene)
{
	// メッシュノード処理
	for (unsigned int count = 0; count < node->mNumMeshes; count++)
	{
		// sceneのmMeshesは本当のメッシュデータ、一歩でnodeのmMesherはメッシュのインデックス
		aiMesh* aiMesh = scene->mMeshes[node->mMeshes[count]];
		this->mMeshes.push_back(new Mesh(aiMesh, this->mBones, scene, this->mPath, this));

		//cout << node->mTransformation.a1 << ", " << node->mTransformation.a2 << ", " << node->mTransformation.a3 << ", " << node->mTransformation.a4 << endl;
		//cout << node->mTransformation.b1 << ", " << node->mTransformation.b2 << ", " << node->mTransformation.b3 << ", " << node->mTransformation.b4 << endl;
		//cout << node->mTransformation.c1 << ", " << node->mTransformation.c2 << ", " << node->mTransformation.c3 << ", " << node->mTransformation.c4 << endl;
		//cout << node->mTransformation.d1 << ", " << node->mTransformation.d2 << ", " << node->mTransformation.d3 << ", " << node->mTransformation.d4 << endl;
	}

	// 子供ノードを同じように処理する
	for (unsigned int count = 0; count < node->mNumChildren; count++)
	{
		processNode(node->mChildren[count], scene);
	}
}

//*****************************************************************************
//
// 骨あるかどうかをチェック
//
//*****************************************************************************
void Model::checkBone(aiMesh* mesh)
{

}

//*****************************************************************************
//
// モデルはアニメーションを含めてるかどうかをチェック
//
//*****************************************************************************
void Model::checkAnimation(const aiScene* scene)
{
	for (unsigned int count = 0; count < scene->mNumAnimations; count++)
	{
		// アニメーションを解析して保存
		aiAnimation* animation = scene->mAnimations[count];
		this->mAnimationes.push_back(new Animation(animation));
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
	//this->mAnimationes[this->mCurAnimation]->updateBoneTransforms(timeInSeconds, this->mBones, this->mTransforms);
}


//*****************************************************************************
//
// モデルを描画
//
//*****************************************************************************
void Model::drawModel(Shader* shader, bool isOutline)
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
		it->drawModel(shader, isOutline);
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