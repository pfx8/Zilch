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
// モデルを描画する(CelShader)
//
//*****************************************************************************
void Model::DrawModel(CelShader* celShader, D3DXMATRIX* worldMatrix, D3DXMATRIX* VPMatrix, 
	D3DXMATRIX* lightMatrix, D3DXMATRIX* normalMatrix, Model_Type modelType)
{
	// テクニックを設定
	celShader->effectPoint->SetTechnique(celShader->celShaderHandle);

	// 変更行列を渡す
	celShader->effectPoint->SetMatrix(celShader->WMatrixHandle, worldMatrix);
	celShader->effectPoint->SetMatrix(celShader->VPMatrixHandle, VPMatrix);

	celShader->effectPoint->SetValue("lightMatrix", lightMatrix, sizeof(D3DXMATRIX));
	//celShader->effectPoint->SetValue("normalMatrix", normalMatrix, sizeof(D3DXMATRIX*));

	// Obj種類番号を渡す
	celShader->effectPoint->SetInt(celShader->typeHandle, modelType);

	// テクスチャを渡す
	celShader->effectPoint->SetTexture("tex", this->meshTexturePoint);

	UINT passNum = 0;
	celShader->effectPoint->Begin(&passNum, 0);
	for (int count = 0; count < passNum; count++)
	{
		celShader->effectPoint->BeginPass(count);

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

		celShader->effectPoint->EndPass();
	}
	celShader->effectPoint->End();
}