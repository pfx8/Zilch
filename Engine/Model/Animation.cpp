﻿//*****************************************************************************
//
// アニメーション処理 [Animation.cpp]
//
// Author : LIAO HANCHEN
//
//*****************************************************************************
#include "Animation.h"

//*****************************************************************************
//
// コンストラクタ
//
//*****************************************************************************
Animation::Animation(string const &path)
{
	loadAnimation(path);
}

//*****************************************************************************
//
// デストラクタ
//
//*****************************************************************************
Animation::~Animation()
{
	// リリースaiScene

}

//*****************************************************************************
//
// アニメーションを読み込み
//
//*****************************************************************************
HRESULT Animation::loadAnimation(string const &path)
{
	Assimp::Importer import;			// Assimpのインポートを作る
	const aiScene* scene = import.ReadFile(path, aiProcessPreset_TargetRealtime_Quality | aiProcess_FixInfacingNormals | aiProcess_ConvertToLeftHanded);
	this->mAiScene = scene;

	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
	{
		cout << "[Error] Assimp::" << import.GetErrorString() << endl;
		return E_FAIL;
	}

	// aiAnimationから自作アニメーションまで変更
	// 各アニメーションファイルに一つアニメーションしかない
	if (scene->mNumAnimations == 1)
	{
		this->mName = scene->mAnimations[0]->mName.C_Str();
		this->mDuration = scene->mAnimations[0]->mDuration;
		this->mTicksPerSecond = scene->mAnimations[0]->mTicksPerSecond;
		this->mNumChannels = scene->mAnimations[0]->mNumChannels;
	}
	else
	{
		cout << "[Error] Dosen't have animations " << endl;
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
void Animation::processNode(aiNode* node, const aiScene* scene)
{
	// ノードの各アニメーションを処理
	for (unsigned int count = 0; count < this->mNumChannels; count++)
	{
		// まずはチャンネルを取得
		aiNodeAnim* channel = scene->mAnimations[0]->mChannels[count];
		AnimationChannel* animationChannel = new AnimationChannel();
		animationChannel->mBoneName = scene->mAnimations[0]->mChannels[count]->mNodeName.C_Str();

		// 頂点座標
		for (unsigned int i = 0; i < scene->mAnimations[0]->mChannels[count]->mNumPositionKeys; i++)
		{
			struct VertexKey vectorkey;

			// 頂点データを取得
			vectorkey.time = scene->mAnimations[0]->mChannels[count]->mPosKeys[i].mTime;
			vectorkey.value.x = scene->mAnimations[0]->mChannels[count]->mPosKeys[i].mValue.x;
			vectorkey.value.y = scene->mAnimations[0]->mChannels[count]->mPosKeys[i].mValue.y;
			vectorkey.value.z = scene->mAnimations[0]->mChannels[count]->mPosKeys[i].mValue.z;

			// AnimationChannelに頂点データを入れる
			animationChannel->mPosKeys.push_back(vectorkey);
		}

		// 回転
		for (unsigned int i = 0; i < scene->mAnimations[0]->mChannels[count]->mNumRotationKeys; i++)
		{
			struct QuaternionKey quaternionKey;

			quaternionKey.time = scene->mAnimations[0]->mChannels[count]->mRotationKeys[i].mTime;
			// 四元数を取得
			quaternionKey.value.x = scene->mAnimations[0]->mChannels[count]->mRotationKeys[i].mValue.x;
			quaternionKey.value.y = scene->mAnimations[0]->mChannels[count]->mRotationKeys[i].mValue.y;
			quaternionKey.value.z = scene->mAnimations[0]->mChannels[count]->mRotationKeys[i].mValue.z;
			quaternionKey.value.w = scene->mAnimations[0]->mChannels[count]->mRotationKeys[i].mValue.w;
		}

		// 拡大縮小
		for (unsigned int i = 0; i < scene->mAnimations[0]->mChannels[count]->mNumScalingKeys; i++)
		{
			struct VertexKey vectorkey;

			// 拡大縮小のデータを取得
			vectorkey.time = scene->mAnimations[0]->mChannels[count]->mScalingKeys[i].mTime;
			vectorkey.value.x = scene->mAnimations[0]->mChannels[count]->mScalingKeys[i].mValue.x;
			vectorkey.value.y = scene->mAnimations[0]->mChannels[count]->mScalingKeys[i].mValue.y;
			vectorkey.value.z = scene->mAnimations[0]->mChannels[count]->mScalingKeys[i].mValue.z;

			// AnimationChannelに拡大縮小のデータを入れる
			animationChannel->mSclKeys.push_back(vectorkey);
		}

		// AnimationChannelを保存
		mAnimationChannels.push_back(animationChannel);
	}
}

//*****************************************************************************
//
// アニメーション更新
//
//*****************************************************************************
void Animation::processBoneTransform(vector<D3DXMATRIX>& matrixs, float timeInSeconds)
{
	// 親行列を用意して正規化する
	D3DXMATRIX matrix;
	D3DXMatrixIdentity(&matrix);

	// 現在アニメーションの時間を計算
	timeInSeconds = timeInSeconds - this->mLastStartTime;
	// 現在アニメーションの時間とアニメーション全体の時間と剰余を計算
	// その結果は今のアニメーションのフレームができた
	float animationTime = fmodf(timeInSeconds * this->mTicksPerSecond, this->mDuration);

	// 各骨を更新行列を計算
	processAnimationUpdate(animationTime,this->mAiScene->mRootNode, matrix);
}

//*****************************************************************************
//
// 時間によって骨の変換行列を計算処理
//
//*****************************************************************************
void Animation::processAnimationUpdate(float animationTime, const aiNode* node, D3DXMATRIX& parentTransform)
{
	// ノードの名前を取得
	string nodeName = node->mName.C_Str();
	// シーンのアニメーションを取得
	const aiAnimation* animation = this->mAiScene->mAnimations[0];
	// ノードの変更行列を取得
	D3DXMATRIX nodeTransform = node->mTransformation[0];
	// 
	const aiNodeAnim* nodeAnim = findNodeAnim(nodeAnim,nodeName);

	if (nodeAnim)
	{
		// スケーリングを補間し、スケーリング変換行列を生成
		aiVector3D scl;
		calcInterpolatedScl(scl, animationTime, nodeAnim);
		D3DXMATRIX sclMat;

		// 回転を補間して回転変換行列を生成
		aiQuaternion rot;
		calcInterpolatedRot(rot, animationTime, nodeAnim);
		D3DXMATRIX rotMat;

		// 移動を補間し、移動変換行列を生成
		aiVector3D pos;
		calcInterpolatedPos(pos, animationTime, nodeAnim);
		D3DXMATRIX posMat;

		// ノードの最終変換行列を計算
		nodeTransform = posMat * rotMat * sclMat;
	}

	D3DXMATRIX globalTransform = parentTransform * nodeTransform;
}