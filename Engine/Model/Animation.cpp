//*****************************************************************************
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

	if (!scene || !scene->mRootNode)
	{
		cout << "[Error] Assimp::" << import.GetErrorString() << endl;
		return E_FAIL;
	}


	// グローバル空間逆行列を計算
	this->mGlobalInverseTransform = scene->mRootNode->mTransformation[0];
	D3DXMatrixInverse(&this->mGlobalInverseTransform, NULL, &this->mGlobalInverseTransform);

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
// アニメーションの情報を自分作ったAnimationChannelに入れる
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
void Animation::processBoneTransforms(float timeInSeconds, vector<Bone*>& bones, vector<D3DXMATRIX>& transforms)
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
	processAnimationTransforms(animationTime, this->mAiScene->mRootNode, bones, matrix);
}

//*****************************************************************************
//
// 時間によって骨の変換行列を計算処理
//
//*****************************************************************************
void Animation::processAnimationTransforms(float animationTime, const aiNode* node, vector<Bone*>& bones, D3DXMATRIX& parentTransform)
{
	// ノードの名前を取得
	string nodeName = node->mName.C_Str();
	// シーンのアニメーションを取得
	aiAnimation* animation = this->mAiScene->mAnimations[0];
	// ノードの変更行列を取得
	D3DXMATRIX nodeTransform = node->mTransformation[0];

	// 今のノードが骨ならば骨の変換行列処理をする
	// そうではないと、ノード変更行列だけを計算
	aiNodeAnim* nodeAnim = findNodeAnim(animation, nodeName);

	if (nodeAnim)
	{
		// スケーリングを補間し、スケーリング変換行列を生成
		//aiVector3D scl;
		//calcInterpolatedScl(scl, animationTime, nodeAnim);
		//D3DXMATRIX sclMat;

		// 回転を補間して回転変換行列を生成
		aiQuaternion rot;
		calcInterpolatedRot(rot, animationTime, nodeAnim);
		// 四元数から行列に変更
		D3DXMATRIX rotMat = rot.GetMatrix()[0];

		// 移動を補間し、移動変換行列を生成
		aiVector3D pos;
		calcInterpolatedPos(pos, animationTime, nodeAnim);
		D3DXMATRIX posMat;
		D3DXMatrixTranslation(&posMat, pos.x, pos.y, pos.z);

		// ノードの最終変換行列を計算
		D3DXMatrixMultiply(&nodeTransform, &posMat, &rotMat);
		//nodeTransform = posMat * rotMat/* * sclMat*/;
	}

	D3DXMATRIX globalTransform = parentTransform * nodeTransform;

	// 骨の最終変更行列を更新
	for (auto& it : bones)
	{
		if (nodeName == it->mName)
		{
			it->mFinaTransform = this->mGlobalInverseTransform * globalTransform * it->mOffset;
		}
	}

	// 子ノード処理
	for (unsigned int count = 0; count < node->mNumChildren; count++)
	{
		processAnimationTransforms(animationTime, node->mChildren[count], bones, globalTransform);
	}
}

//*****************************************************************************
//
// 
//
//*****************************************************************************
aiNodeAnim* Animation::findNodeAnim(aiAnimation* animation, string nodeName)
{
	for (unsigned int count = 0; count < animation->mNumChannels; count++)
	{
		// ノードの名前が骨対応してるならばaiNodeAnimationを戻る
		if (animation->mChannels[count]->mNodeName.C_Str() == nodeName)
		{
			return animation->mChannels[count];
		}
	}

	// ノードの名前が骨対応してないならば
	return nullptr;
}

//*****************************************************************************
//
// 
//
//*****************************************************************************
void Animation::calcInterpolatedScl(aiVector3D& scl, float animationTime, aiNodeAnim* nodeAnim)
{
	// キーフレームは一つになるのはアニメーションがないわけ、補間計算はいらない
	if (nodeAnim->mNumScalingKeys == 1)
	{
		scl = nodeAnim->mScalingKeys[0].mValue;
		return;
	}

	// 現時点でキーフレームインデックスと次のフレームインデックスを取得
	unsigned int scalingIndex = FindRot(animationTime, nodeAnim);
	unsigned int nextScalingIndex = (scalingIndex + 1);

	// もしアニメーションが終わったら
	assert(nextScalingIndex < nodeAnim->mNumScalingKeys);

	// 補間時間と補間因子を計算
	float deltaTime = nodeAnim->mScalingKeys[nextScalingIndex].mTime - nodeAnim->mScalingKeys[scalingIndex].mTime;
	float factor = (animationTime - (float)nodeAnim->mScalingKeys[scalingIndex].mTime) / deltaTime;

	// もし補間因子が正解値ならば(ちゃんと補間できるかどうかの判断)
	assert(factor >= 0.0f && factor <= 1.0f);

	// 補間値を計算
	const aiVector3D& startScaling = nodeAnim->mScalingKeys[scalingIndex].mValue;
	const aiVector3D& endScaling = nodeAnim->mScalingKeys[nextScalingIndex].mValue;
	aiVector3D temp = endScaling - startScaling;
	scl = startScaling + factor * temp;
}

//*****************************************************************************
//
// 
//
//*****************************************************************************
void Animation::calcInterpolatedRot(aiQuaternion& rot, float animationTime, aiNodeAnim* nodeAnim)
{
	// キーフレームは一つになるのはアニメーションがないわけ、補間計算はいらない
	if (nodeAnim->mNumRotationKeys == 1) 
	{
		rot = nodeAnim->mRotationKeys[0].mValue;
		return;
	}

	// 現時点でキーフレームインデックスと次のフレームインデックスを取得
	unsigned int rotationIndex = FindRot(animationTime, nodeAnim);
	unsigned int nextRotationIndex = (rotationIndex + 1);

	// もしアニメーションが終わったら
	assert(nextRotationIndex < nodeAnim->mNumRotationKeys);

	// 補間時間と補間因子を計算
	float deltaTime = nodeAnim->mRotationKeys[nextRotationIndex].mTime - nodeAnim->mRotationKeys[rotationIndex].mTime;
	float factor = (animationTime - (float)nodeAnim->mRotationKeys[rotationIndex].mTime) / deltaTime;

	// もし補間因子が正解値ならば(ちゃんと補間できるかどうかの判断)
	assert(factor >= 0.0f && factor <= 1.0f);

	// 補間四元数を計算
	const aiQuaternion& startRotationQ = nodeAnim->mRotationKeys[rotationIndex].mValue;
	const aiQuaternion& endRotationQ = nodeAnim->mRotationKeys[nextRotationIndex].mValue;
	aiQuaternion::Interpolate(rot, startRotationQ, endRotationQ, factor);
	
	// 四元数を正規化
	rot = rot.Normalize();
}

//*****************************************************************************
//
// 
//
//*****************************************************************************
void Animation::calcInterpolatedPos(aiVector3D& pos, float animationTime, aiNodeAnim* nodeAnim)
{
	// キーフレームは一つになるのはアニメーションがないわけ、補間計算はいらない
	if (nodeAnim->mNumPositionKeys == 1)
	{
		pos = nodeAnim->mPosKeys[0].mValue;
		return;
	}

	// 現時点でキーフレームインデックスと次のフレームインデックスを取得
	unsigned int positionIndex = FindRot(animationTime, nodeAnim);
	unsigned int nextPositionIndex = (positionIndex + 1);

	// もしアニメーションが終わったら
	assert(nextPositionIndex < nodeAnim->mNumPositionKeys);

	// 補間時間と補間因子を計算
	float deltaTime = nodeAnim->mPosKeys[nextPositionIndex].mTime - nodeAnim->mPosKeys[positionIndex].mTime;
	float factor = (animationTime - (float)nodeAnim->mPosKeys[positionIndex].mTime) / deltaTime;

	// もし補間因子が正解値ならば(ちゃんと補間できるかどうかの判断)
	assert(factor >= 0.0f && factor <= 1.0f);

	// 補間値を計算
	const aiVector3D& startPosition = nodeAnim->mPosKeys[positionIndex].mValue;
	const aiVector3D& endPosition = nodeAnim->mPosKeys[nextPositionIndex].mValue;
	aiVector3D temp = endPosition - startPosition;
	pos = startPosition + factor * temp;
}

//*****************************************************************************
//
// 
//
//*****************************************************************************
unsigned int Animation::FindScl(float animationTime, aiNodeAnim* nodeAnim)
{
	// もし拡大縮小キーフレームがあれば
	assert(nodeAnim->mNumScalingKeys > 0);

	for (unsigned count = 0; count < nodeAnim->mNumScalingKeys - 1; count++)
	{
		if (animationTime < (float)nodeAnim->mScalingKeys[count + 1].mTime)
		{
			// animationTimeに対応してキーフレームインデックスを戻す
			return count;
		}
	}

	// アニメーションが終わったら0を戻る
	return 0;
}

//*****************************************************************************
//
// 
//
//*****************************************************************************
unsigned int Animation::FindRot(float animationTime, aiNodeAnim* nodeAnim)
{
	// もし回転キーフレームがあれば
	assert(nodeAnim->mNumRotationKeys > 0);

	for (unsigned count = 0; count < nodeAnim->mNumRotationKeys - 1; count++) 
	{
		if (animationTime < (float)nodeAnim->mRotationKeys[count + 1].mTime) 
		{
			// animationTimeに対応してキーフレームインデックスを戻す
			return count;
		}
	}

	// アニメーションが終わったら0を戻る
	return 0;
}

//*****************************************************************************
//
// 
//
//*****************************************************************************
unsigned int Animation::FindPos(float animationTime, aiNodeAnim* nodeAnim)
{
	// もし移動キーフレームがあれば
	assert(nodeAnim->mNumPositionKeys > 0);

	for (unsigned count = 0; count < nodeAnim->mNumPositionKeys - 1; count++)
	{
		if (animationTime < (float)nodeAnim->mPosKeys[count + 1].mTime)
		{
			// animationTimeに対応してキーフレームインデックスを戻す
			return count;
		}
	}

	// アニメーションが終わったら0を戻る
	return 0;
}