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
Model::Model()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 数値を初期化
	this->upVector = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	this->lookVector = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
	this->rightVector = D3DXVECTOR3(1.0f, 0.0f, 0.0f);
	this->pos = D3DXVECTOR3(0.0f, 0.5f, 0.0f);
	this->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	this->scl = D3DXVECTOR3(1.0f, 1.0f, 1.0f);

	// ポインタ
	this->meshPoint = NULL;
	this->meshTexturePoint = NULL;

	// クラスポインタ
	this->material = new Material();

	// 頂点宣言
	D3DVERTEXELEMENT9 planeDecl[] =		// 頂点データのレイアウトを定義
	{
		{ 0,  0, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0 },
		{ 0, 12, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_NORMAL, 0 },
		{ 0, 24, D3DDECLTYPE_FLOAT2, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 0 },
		D3DDECL_END()
	};
	pDevice->CreateVertexDeclaration(planeDecl, &this->vertexDecl);
}

//*****************************************************************************
//
// デストラクタ
//
//*****************************************************************************
Model::~Model()
{
	// ポインタ
	RELEASE_POINT(this->meshPoint);
	RELEASE_CLASS_POINT(this->meshTexturePoint);

	// クラスポインタ
	RELEASE_CLASS_POINT(this->material);
}

//*****************************************************************************
//
// 上方向のベクトルにして回転
//
//*****************************************************************************
void Model::RotationVecUp(float angle)
{
	// 角度を記録する
	this->rot.y += angle;

	if (this->rot.y >= D3DXToRadian(360.0f))
	{
		this->rot.y = 0.0f;
	}
	if (this->rot.y <= D3DXToRadian(-360.0f))
	{
		this->rot.y = 0.0f;
	}

	D3DXMATRIX rotMatrix;
	D3DXMatrixRotationAxis(&rotMatrix, &this->upVector, angle);					// 回転行列を作る
	D3DXVec3TransformCoord(&this->lookVector, &this->lookVector, &rotMatrix);	// カメラの新しい座標を計算する

	D3DXVec3Normalize(&this->lookVector, &this->lookVector);
	D3DXVec3Cross(&this->rightVector, &this->lookVector, &this->upVector);
	D3DXVec3Normalize(&this->rightVector, &this->rightVector);
	D3DXVec3Cross(&this->upVector, &this->rightVector, &this->lookVector);
	D3DXVec3Normalize(&this->upVector, &this->upVector);

	// OGL -> DX
	this->rightVector = -this->rightVector;
}

//*****************************************************************************
//
// ワールド変換を設定
//
//*****************************************************************************
void Model::SetWorldMatrix()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	D3DXMATRIX mtxScl, mtxRot, mtxTranslate;

	// ワールドマトリックスの初期化
	D3DXMatrixIdentity(&this->worldMatrix);

	// スケールを反映
	D3DXMatrixScaling(&mtxScl, this->scl.x, this->scl.y, this->scl.z);
	D3DXMatrixMultiply(&this->worldMatrix, &this->worldMatrix, &mtxScl);

	// 回転を反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, this->rot.y, this->rot.x, this->rot.z);
	D3DXMatrixMultiply(&this->worldMatrix, &this->worldMatrix, &mtxRot);

	// 移動を反映
	D3DXMatrixTranslation(&mtxTranslate, this->pos.x, this->pos.y, this->pos.z);
	D3DXMatrixMultiply(&this->worldMatrix, &this->worldMatrix, &mtxTranslate);
}

//*****************************************************************************
//
// 状態更新
//
//*****************************************************************************
void Model::Update()
{

}

//*****************************************************************************
//
// モデルを描画する(CelShader)
//
//*****************************************************************************
void Model::Draw(CelShader* celShader, D3DXMATRIX* VPMatrix)
{
	// テクニックを設定
	celShader->effect->SetTechnique(celShader->celShaderHandle);

	// 変更行列を渡す
	celShader->effect->SetMatrix(celShader->WMatrixHandle, &this->worldMatrix);
	celShader->effect->SetMatrix(celShader->VPMatrixHandle, VPMatrix);

	// テクスチャを渡す
	celShader->effect->SetTexture("tex", this->meshTexturePoint);

	UINT passNum = 0;
	celShader->effect->Begin(&passNum, 0);
	for (int count = 0; count < passNum; count++)
	{
		celShader->effect->BeginPass(count);

		LPDIRECT3DDEVICE9 pDevice = GetDevice();
		DWORD materialNum = this->material->materialNum;				// マテリアル数を取得

		IDirect3DVertexBuffer9* vertexBuffer = NULL;
		this->meshPoint->GetVertexBuffer(&vertexBuffer);				// メッシュ頂点を取得
		IDirect3DIndexBuffer9* indexBuffer = NULL;
		this->meshPoint->GetIndexBuffer(&indexBuffer);					// メッシュ頂点インデックスバッファを取得

		this->meshPoint->GetAttributeTable(NULL, &materialNum);			// メッシュの属性テーブルに格納されているエントリの数を取得

		D3DXATTRIBUTERANGE* attributes = NULL;							// メッシュの属性テーブルを作る
		attributes = new D3DXATTRIBUTERANGE[materialNum];				// エントリ数によって、属性テーブル配列メモリを作り
		this->meshPoint->GetAttributeTable(attributes, &materialNum);	// メッシュの属性テーブルを取得

		pDevice->SetVertexDeclaration(this->vertexDecl);				// 頂点宣言を設定
		pDevice->SetStreamSource(0, vertexBuffer, 0, 32);				// sizeof(POSITION, NORMAL, UV)
		pDevice->SetIndices(indexBuffer);

		// 描画
		for (DWORD count = 0; count < materialNum; count++)
		{
			if (attributes[count].FaceCount)
			{
				//DWORD matNum = attributes[count].AttribId;			// マテリアル数を取得
				//celShader->this->effectPoint->SetTexture(celShader->this->texture1Handle, this->meshTexturePoint[matNum]);	// テクスチャを設定
				//pDevice->SetTexture(0, this->meshTexturePoint[matNum]);	// テクスチャを設定

				// モデルを描画する
				pDevice->DrawIndexedPrimitive(
					D3DPT_TRIANGLELIST,
					0,
					attributes[count].VertexStart,
					attributes[count].VertexCount,
					attributes[count].FaceStart * 3,
					attributes[count].FaceCount);
			}
		}

		RELEASE_POINT(vertexBuffer);
		RELEASE_POINT(indexBuffer);

		delete[] attributes;

		celShader->effect->EndPass();
	}
	celShader->effect->End();
}