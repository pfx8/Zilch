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
	const aiScene* scene = new aiScene();
	scene = import.ReadFile(path, aiProcessPreset_TargetRealtime_Quality | aiProcess_FixInfacingNormals | aiProcess_ConvertToLeftHanded);

	if (!scene || !scene->mRootNode)
	{
		cout << "[Error] Assimp::" << import.GetErrorString() << endl;
		return E_FAIL;
	}

	// グローバル空間逆行列を計算
	this->mGlobalInverseTransform = scene->mRootNode->mTransformation[0];
	D3DXMatrixInverse(&this->mGlobalInverseTransform, NULL, &this->mGlobalInverseTransform);

	// aiAnimationから自作アニメーションまで変更
	// 各アニメーションファイルにアニメーションは一つしかない
	if (scene->mNumAnimations == 1)
	{
		this->mName = scene->mAnimations[0]->mName.C_Str();
		this->mDuration = scene->mAnimations[0]->mDuration;
		this->mTicksPerSecond = scene->mAnimations[0]->mTicksPerSecond;
	}
	else
	{
		cout << "[Error] Dosen't have animations " << endl;
		return E_FAIL;
	}

	// AnimationChannelを保存
	for (unsigned int count {0}; count < scene->mAnimations[0]->mNumChannels; count++)
	{
		// まずはチャンネルを取得
		aiNodeAnim* channel {scene->mAnimations[0]->mChannels[count]};
		AnimationChannel* animationChannel {new AnimationChannel()};
		animationChannel->mBoneName = scene->mAnimations[0]->mChannels[count]->mNodeName.C_Str();

		// 頂点座標
		for (unsigned int i {0}; i < scene->mAnimations[0]->mChannels[count]->mNumPositionKeys; i++)
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
		for (unsigned int i {0}; i < scene->mAnimations[0]->mChannels[count]->mNumRotationKeys; i++)
		{
			struct QuaternionKey quaternionKey;

			quaternionKey.time = scene->mAnimations[0]->mChannels[count]->mRotationKeys[i].mTime;
			// 四元数を取得
			quaternionKey.value.x = scene->mAnimations[0]->mChannels[count]->mRotationKeys[i].mValue.x;
			quaternionKey.value.y = scene->mAnimations[0]->mChannels[count]->mRotationKeys[i].mValue.y;
			quaternionKey.value.z = scene->mAnimations[0]->mChannels[count]->mRotationKeys[i].mValue.z;
			quaternionKey.value.w = scene->mAnimations[0]->mChannels[count]->mRotationKeys[i].mValue.w;

			// AnimationChannelに頂点データを入れる
			animationChannel->mRotkeys.push_back(quaternionKey);
		}

		// 拡大縮小
		for (unsigned int i {0}; i < scene->mAnimations[0]->mChannels[count]->mNumScalingKeys; i++)
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

	// ルートノードから処理を始める
	Node* node {new Node(scene->mRootNode->mName.C_Str())};
	node->mParent = nullptr;
	processNode(node, scene->mRootNode, scene);

	return S_OK;
}

//*****************************************************************************
//
// 骨ノードをトラバース
//
//*****************************************************************************
void Animation::traverseBoneNode(Node* node, unsigned int level)
{
	string space;

	for (unsigned count = 0; count < level; count++)
	{
		if (count == level - 1)
		{
			space += "|";
		}
		space += "  ";
	}

	for (auto it : node->mChildren)
	{
		traverseBoneNode(it, level + 1);
	}
}

//*****************************************************************************
//
// ノード処理
//
// アニメーションの情報を自分作ったAnimationChannelに入れる
//
//*****************************************************************************
void Animation::processNode(Node* node, aiNode* aiNode, const aiScene* scene)
{
	// offset行列を保存
	node->mTransform = aiNode->mTransformation[0];

	// 子供ノードを処理
	for (unsigned int count {0}; count < aiNode->mNumChildren; count++)
	{
		// 子供ノードを作る
		Node* cNode {new Node(aiNode->mChildren[count]->mName.C_Str())};
		cNode->mParent = node;
		node->mChildren.push_back(cNode);

		processNode(cNode, aiNode->mChildren[count], scene);
	}

	this->mNode.push_back(node);
}

//*****************************************************************************
//
// アニメーションキーフレームによって骨の変更行列を更新
//
//*****************************************************************************
void Animation::updateBoneTransforms(float timeInSeconds, vector<Bone*>& bones, vector<D3DXMATRIX>& transforms)
{
	// 親行列を用意して正規化する
	D3DXMATRIX matrix;
	D3DXMatrixIdentity(&matrix);

	// 現在アニメーションの時間を計算
	timeInSeconds = timeInSeconds - this->mLastStartTime;

	// 現在アニメーションの時間とアニメーション全体の時間と剰余を計算
	// その結果は今のアニメーションのフレームができる
	float animationTime {fmodf(timeInSeconds * this->mTicksPerSecond, this->mDuration)};

	// 各骨を更新行列を計算、ルートノードから
	processBoneTransforms(animationTime, *(this->mNode.end()-1), bones, matrix);

	// test data
	/*unsigned int count = 1;
	for (auto it : bones)
	{
		cout << "<Test><Bones><No." << count << "> : " << it->mFinaTransform._11 << ", " << it->mFinaTransform._12 << endl;
		count++;
	}
	cout << endl;*/

}

//*****************************************************************************
//
// キーフレームで各ノード(骨)の変換行列を計算処理
//
//*****************************************************************************
void Animation::processBoneTransforms(float animationTime, Node* node, vector<Bone*>& bones, D3DXMATRIX& parentTransform)
{
	// ノードの変更行列を取得
	D3DXMATRIX nodeTransform {node->mTransform};

	// ノードが骨ならば、対応してるchannelを取得
	AnimationChannel* channel {nullptr};

	// このノードに骨があれば
	for (auto it : this->mAnimationChannels)
	{
		if (node->mName == it->mBoneName)
		{
			channel = it;
		}
	}

	// このノードに骨があれば、キーフレームによって骨の変更行列を計算
	if (channel)
	{
		// スケーリングを補間し、スケーリング変換行列を生成
		D3DXVECTOR3 scl;
		calcInterpolatedScl(scl, animationTime, channel);
		D3DXMATRIX sclMat;
		D3DXMatrixScaling(&sclMat, scl.x, scl.y, scl.z);

		// 回転を補間して回転変換行列を生成
		D3DXQUATERNION rot;
		calcInterpolatedRot(rot, animationTime, channel);
		// 四元数から行列に変更
		D3DXMATRIX rotMat;
		D3DXMatrixRotationQuaternion(&rotMat, &rot);

		// 移動を補間し、移動変換行列を生成
		D3DXVECTOR3 pos;
		calcInterpolatedPos(pos, animationTime, channel);
		D3DXMATRIX posMat;
		D3DXMatrixTranslation(&posMat, pos.x, pos.y, pos.z);

		// ノードの最終変換行列を計算
		nodeTransform = posMat * rotMat * sclMat;
	}

	D3DXMATRIX globalTransform {parentTransform * nodeTransform};

	// 骨の最終変更行列を更新
	for (auto& it : bones)
	{
		if (node->mName == it->mName)
		{
			it->mFinaTransform = this->mGlobalInverseTransform * globalTransform * it->mOffset;
		}
	}

	// 次のノード処理
	for (unsigned int count {0}; count < node->mChildren.size(); count++)
	{
		processBoneTransforms(animationTime, node->mChildren.at(count), bones, globalTransform);
	}
}

//*****************************************************************************
//
// 拡大縮小行列計算
//
//*****************************************************************************
void Animation::calcInterpolatedScl(D3DXVECTOR3& scl, float animationTime, AnimationChannel* channel)
{
	// キーフレームは一つになるのはアニメーションがないわけ、補間計算はいらない
	if (channel->mSclKeys.size() == 1)
	{
		scl = channel->mSclKeys.at(0).value;
		return;
	}

	// 現時点でキーフレームインデックスと次のフレームインデックスを取得
	unsigned int scalingIndex {FindRot(animationTime, channel)};
	unsigned int nextScalingIndex {scalingIndex + 1};

	// もしアニメーションが終わったら
	assert(nextScalingIndex < channel->mSclKeys.size());

	// 補間時間と補間因子を計算
	float deltaTime {channel->mSclKeys.at(nextScalingIndex).time - channel->mSclKeys.at(scalingIndex).time};
	float factor {(animationTime - channel->mSclKeys.at(scalingIndex).time) / deltaTime};

	// もし補間因子が正解値ならば(ちゃんと補間できるかどうかの判断)
	assert(factor >= 0.0f && factor <= 1.0f);

	// 補間値を計算
	D3DXVECTOR3 startScaling {channel->mSclKeys.at(scalingIndex).value};
	D3DXVECTOR3 endScaling {channel->mSclKeys.at(nextScalingIndex).value};
	D3DXVECTOR3 temp {endScaling - startScaling};
	scl = startScaling + factor * temp;
}

//*****************************************************************************
//
// 今のキーフレーム番号を戻す(拡大縮小)
//
//*****************************************************************************
unsigned int Animation::FindScl(float animationTime, AnimationChannel* channel)
{
	unsigned int count{0};
	for (vector<VertexKey>::iterator it = channel->mSclKeys.begin(); it != (channel->mSclKeys.end() - 1); it++)
	{
		// フレームを確定そして戻す
		if (animationTime < (it + 1)->time)
		{
			return count;
		}
		count++;
	}

	// アニメーションが終わったら0を戻る
	return 0;
}

//*****************************************************************************
//
// 回転行列計算
//
//*****************************************************************************
void Animation::calcInterpolatedRot(D3DXQUATERNION& rot, float animationTime, AnimationChannel* channel)
{
	// キーフレームは一つになるのはアニメーションがないわけ、補間計算はいらない
	if (channel->mRotkeys.size() == 1) 
	{
		rot = channel->mRotkeys.at(0).value;
		return;
	}

	// 現時点でキーフレームインデックスと次のフレームインデックスを取得
	unsigned int rotationIndex {FindRot(animationTime, channel)};
	unsigned int nextRotationIndex {rotationIndex + 1};

	// もしアニメーションが終わったら
	assert(nextRotationIndex < channel->mRotkeys.size());

	// 補間時間と補間因子を計算
	float deltaTime {channel->mRotkeys.at(nextRotationIndex).time - channel->mRotkeys.at(rotationIndex).time};
	float factor {(animationTime - channel->mRotkeys.at(rotationIndex).time) / deltaTime};

	// もし補間因子が正解値ならば(ちゃんと補間できるかどうかの判断)
	assert(factor >= 0.0f && factor <= 1.0f);

	// 補間四元数を計算
	D3DXQUATERNION& startRotationQ {channel->mRotkeys.at(rotationIndex).value};
	D3DXQUATERNION& endRotationQ {channel->mRotkeys.at(nextRotationIndex).value};
	D3DXQuaternionSlerp(&rot, &startRotationQ, &endRotationQ, factor);
	
	// 四元数を正規化
	D3DXQuaternionNormalize(&rot, &rot);
}

//*****************************************************************************
//
// 今のキーフレーム番号を戻す(回転)
//
//*****************************************************************************
unsigned int Animation::FindRot(float animationTime, AnimationChannel* channel)
{
	unsigned int count {0};
	for (vector<QuaternionKey>::iterator it = channel->mRotkeys.begin(); it != (channel->mRotkeys.end() - 1); it++)
	{
		// フレームを確定
		if (animationTime < (it + 1)->time)
		{
			return count;
		}
		count++;
	}

	// アニメーションが終わったら0を戻る
	return 0;
}

//*****************************************************************************
//
// 移動行列計算
//
//*****************************************************************************
void Animation::calcInterpolatedPos(D3DXVECTOR3& pos, float animationTime, AnimationChannel* channel)
{
	// キーフレームは一つになるのはアニメーションがないわけ、補間計算はいらない
	if (channel->mPosKeys.size() == 1)
	{
		pos = channel->mPosKeys.at(0).value;
		return;
	}

	// 現時点でキーフレームインデックスと次のフレームインデックスを取得
	unsigned int positionIndex {FindRot(animationTime, channel)};
	unsigned int nextPositionIndex {positionIndex + 1};

	// もしアニメーションが終わったら
	assert(nextPositionIndex < channel->mPosKeys.size());

	// 補間時間と補間因子を計算
	float deltaTime {channel->mPosKeys.at(nextPositionIndex).time - channel->mPosKeys.at(positionIndex).time};
	float factor {(animationTime - channel->mPosKeys.at(positionIndex).time) / deltaTime};

	// もし補間因子が正解値ならば(ちゃんと補間できるかどうかの判断)
	assert(factor >= 0.0f && factor <= 1.0f);

	// 補間値を計算
	D3DXVECTOR3& startPosition {channel->mPosKeys.at(positionIndex).value};
	D3DXVECTOR3& endPosition {channel->mPosKeys.at(nextPositionIndex).value};
	D3DXVECTOR3 temp{endPosition - startPosition};
	pos = startPosition + factor * temp;
}

//*****************************************************************************
//
// 今のキーフレーム番号を戻す(移動)
//
//*****************************************************************************
unsigned int Animation::FindPos(float animationTime, AnimationChannel* channel)
{
	unsigned int count {0};
	for (vector<VertexKey>::iterator it = channel->mPosKeys.begin(); it != (channel->mPosKeys.end() - 1); it++)
	{
		// フレームを確定
		if (animationTime < (it + 1)->time)
		{
			return count;
		}
		count++;
	}

	// アニメーションが終わったら0を戻る
	return 0;
}