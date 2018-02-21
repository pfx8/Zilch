//*****************************************************************************
//
// スカイボックス処理 [SkyBox.cpp]
//
// Author : リョウ　カンシン
//
//*****************************************************************************
#include "SkyBox.h"

//*****************************************************************************
//
// コンストラクタ
//
//*****************************************************************************
SkyBox::SkyBox()
{
	// 初期化
	this->vertexBuffer = NULL;
	this->indexBuffer = NULL;
	this->vertexDecl = NULL;

	this->tex = NULL;

	this->length = 0.0f;
	this->pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}

//*****************************************************************************
//
// デストラクタ
//
//*****************************************************************************
SkyBox::~SkyBox()
{
	RELEASE_POINT(this->vertexBuffer);
	RELEASE_POINT(this->indexBuffer);
	RELEASE_POINT(this->vertexDecl);

	RELEASE_POINT(this->tex);
}

//*****************************************************************************
//
// スカイボックスを初期化
//
//*****************************************************************************
HRESULT SkyBox::InitSkyBox(float length)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	{// 頂点設計
		D3DVERTEXELEMENT9 boundingBoxDecl[] =	// 頂点データのレイアウトを定義
		{
			{ 0, 0,  D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION },
			{ 0, 12, D3DDECLTYPE_FLOAT2, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD },
			D3DDECL_END()
		};
		pDevice->CreateVertexDeclaration(boundingBoxDecl, &this->vertexDecl);

		// オブジェクトの頂点バッファを生成
		if (FAILED(pDevice->CreateVertexBuffer(16 * sizeof(SKYBOXVERTEX), D3DUSAGE_WRITEONLY, 0, D3DPOOL_DEFAULT, &this->vertexBuffer, NULL)))
		{
			std::cout << "[Error] 頂点バッファが生成できない!" << std::endl;	// エラーメッセージ
			return E_FAIL;
		}

		// 頂点作成
		SKYBOXVERTEX vertex[] =
		{
			// 前
			{ D3DXVECTOR3(-length / 2, length / 2, length / 2), D3DXVECTOR2(0.0f, 0.0f) },
			{ D3DXVECTOR3( length / 2, length / 2, length / 2), D3DXVECTOR2(0.25f, 0.0f) },
			{ D3DXVECTOR3(-length / 2, 0.0f,       length / 2), D3DXVECTOR2(0.0f, 1.0f) },
			{ D3DXVECTOR3( length / 2, 0.0f,       length / 2), D3DXVECTOR2(0.25f, 1.0f) },

			// 右
			{ D3DXVECTOR3(length / 2, length / 2,  length / 2), D3DXVECTOR2(0.25f, 0.0f) },
			{ D3DXVECTOR3(length / 2, length / 2, -length / 2), D3DXVECTOR2(0.5f, 0.0f) },
			{ D3DXVECTOR3(length / 2, 0.0f,        length / 2), D3DXVECTOR2(0.25f, 1.0f) },
			{ D3DXVECTOR3(length / 2, 0.0f,       -length / 2), D3DXVECTOR2(0.5f, 1.0f) },

			// 後ろ
			{ D3DXVECTOR3( length / 2, length / 2, -length / 2), D3DXVECTOR2(0.5f, 0.0f) },
			{ D3DXVECTOR3(-length / 2, length / 2, -length / 2), D3DXVECTOR2(0.75f, 0.0f) },
			{ D3DXVECTOR3( length / 2, 0.0f,       -length / 2), D3DXVECTOR2(0.5f, 1.0f) },
			{ D3DXVECTOR3(-length / 2, 0.0f,       -length / 2), D3DXVECTOR2(0.75f, 1.0f) },

			// 左
			{ D3DXVECTOR3(-length / 2, length / 2, -length / 2), D3DXVECTOR2(0.75f, 0.0f) },
			{ D3DXVECTOR3(-length / 2, length / 2,  length / 2), D3DXVECTOR2(1.0f, 0.0f) },
			{ D3DXVECTOR3(-length / 2, 0.0f,       -length / 2), D3DXVECTOR2(0.75f, 1.0f) },
			{ D3DXVECTOR3(-length / 2, 0.0f,        length / 2), D3DXVECTOR2(1.0f, 1.0f) },

			//// 上
			//{ D3DXVECTOR3( length / 2, length / 2,  length / 2), D3DXVECTOR2(0.8f, 0.0f) },
			//{ D3DXVECTOR3(-length / 2, length / 2,  length / 2), D3DXVECTOR2(1.0f, 0.0f) },
			//{ D3DXVECTOR3( length / 2, length / 2, -length / 2), D3DXVECTOR2(0.8f, 1.0f) },
			//{ D3DXVECTOR3(-length / 2, length / 2, -length / 2), D3DXVECTOR2(1.0f, 1.0f) },


		};

		VOID* vertexBuffer;	// 頂点バッファポインタ作成

		// 頂点データの範囲をロックして頂点バッファメモリへのポインタを取得する
		if (FAILED(this->vertexBuffer->Lock(0, 0, (void**)&vertexBuffer, 0)))
		{
			std::cout << "[Error] 頂点バッファがロックできない!" << std::endl;	// エラーメッセージ
			return E_FAIL;
		}
		memcpy(vertexBuffer, vertex, sizeof(vertex));	// 作成された頂点を臨時ポインタの中に入れる
		this->vertexBuffer->Unlock();					// 頂点データをアンロックする
	}

	{// インデックス設計
		//オブジェクトの頂点インデックスバッファを生成
		if (FAILED(pDevice->CreateIndexBuffer(24 * sizeof(WORD), 0, D3DFMT_INDEX16, D3DPOOL_DEFAULT, &this->indexBuffer, NULL)))
		{
			std::cout << "[Error] 頂点インデクスが生成できない!" << std::endl;	// エラーメッセージ
			return E_FAIL;
		}

		WORD* vertexIndex = NULL;	// イデックスの中身を埋める
		this->indexBuffer->Lock(0, 0, (void**)&vertexIndex, 0);	// インデックス データのある一定範囲をロックし、そのインデックス バッファー メモリーへのポインターを取得する

		// 前
		vertexIndex[0] = 0, vertexIndex[1] = 1, vertexIndex[2] = 2;
		vertexIndex[3] = 1, vertexIndex[4] = 2, vertexIndex[5] = 3;

		// 右
		vertexIndex[6] = 4, vertexIndex[7] = 5, vertexIndex[8] = 6;
		vertexIndex[9] = 5, vertexIndex[10] = 6, vertexIndex[11] = 7;

		// 後ろ
		vertexIndex[12] = 8, vertexIndex[13] = 9, vertexIndex[14] = 10;
		vertexIndex[15] = 9, vertexIndex[16] = 10, vertexIndex[17] = 11;

		// 左
		vertexIndex[18] = 12, vertexIndex[19] = 13, vertexIndex[20] = 14;
		vertexIndex[21] = 13, vertexIndex[22] = 14, vertexIndex[23] = 15;

		//// 上
		//vertexIndex[24] = 16, vertexIndex[25] = 17, vertexIndex[26] = 18;
		//vertexIndex[27] = 17, vertexIndex[28] = 18, vertexIndex[29] = 19;

		// インデックス データのロックを解除する
		this->indexBuffer->Unlock();
	}

	return S_OK;
}

//*****************************************************************************
//
// ワールド変換
//
//*****************************************************************************
void SkyBox::SetWorldMatrix()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	D3DXMATRIX mtxTranslate;

	// ワールドマトリックスを初期化する
	D3DXMatrixIdentity(&this->worldMatrix);

	// 平行移動を反映
	D3DXMatrixTranslation(&mtxTranslate, this->pos.x, this->pos.y, this->pos.z);
	D3DXMatrixMultiply(&this->worldMatrix, &this->worldMatrix, &mtxTranslate);
}

//*****************************************************************************
//
// スカイボックスを描画
//
//*****************************************************************************
void SkyBox::Draw(Shader* shader, D3DXMATRIX* vMatrix, D3DXMATRIX* pMatrix)
{
	PDIRECT3DDEVICE9 pDevice = GetDevice();

	// テクニックを設定
	shader->technique = shader->effect->GetTechniqueByName("defaultRender");
	shader->effect->SetTechnique(shader->technique);

	// ワールド変換、ビューイング変換、プロジェクション変換マトリックス
	shader->effect->SetValue("wMat", &this->worldMatrix, sizeof(D3DXMATRIX));
	shader->effect->SetValue("vMat", vMatrix, sizeof(D3DXMATRIX));
	shader->effect->SetValue("pMat", pMatrix, sizeof(D3DXMATRIX));

	// テクスチャの設定
	shader->effect->SetValue("tex", &this->tex, sizeof(LPDIRECT3DTEXTURE9));

	// 描画
	UINT passNum = 0;
	shader->effect->Begin(&passNum, 0);
	// 各パスを実行する
	for (int count = 0; count < passNum; count++)
	{
		shader->effect->BeginPass(0);

		pDevice->SetVertexDeclaration(this->vertexDecl);							// 頂点宣言を設定
		pDevice->SetStreamSource(0, this->vertexBuffer, 0, sizeof(SKYBOXVERTEX));	// 頂点バッファをデバイスのデータストリームにバイナリ
		pDevice->SetIndices(this->indexBuffer);										// 頂点イデックスの設定
		pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 17, 0, 16);			// バウンディングボックスの描画

		shader->effect->EndPass();
	}
	shader->effect->End();
}