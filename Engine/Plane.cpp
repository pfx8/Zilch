//*****************************************************************************
//
// 平面処理[Plane.cpp]
//
// Author : LIAO HANCHEN
//
//*****************************************************************************
#include "Plane.h"

//*****************************************************************************
//
// コンストラクタ
//
//*****************************************************************************
Plane::Plane()
{

	this->pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	this->vertexBuffer = NULL;
	this->indexBuffer = NULL;
	this->tex = NULL;
	this->normalMap = NULL;
}

//*****************************************************************************
//
// デストラクタ
//
//*****************************************************************************
Plane::~Plane()
{
	// ポインタ
	RELEASE_POINT(this->vertexBuffer);
	RELEASE_POINT(this->indexBuffer);
	RELEASE_POINT(this->tex);
	RELEASE_POINT(this->normalMap);
}

//*****************************************************************************
//
// 座標を設定
//
//*****************************************************************************
HRESULT Plane::InitPlane(D3DXVECTOR3 pos, D3DXVECTOR2 planeSize, D3DXVECTOR2 planeNum)
{
	this->pos = pos;	// 位置
	this->planeNum = planeNum;
	this->planeSize = planeSize;

	MakeVertexDecl(this->planeSize, this->planeNum);	// 頂点宣言(shader)

	return S_OK;
}

//*****************************************************************************
//
// 頂点宣言(Shader)
//
//*****************************************************************************
HRESULT Plane::MakeVertexDecl(D3DXVECTOR2 planeSize, D3DXVECTOR2 planeNum)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	this->vertexNum = (planeNum.x + 1) * (planeNum.y + 1);	// 総頂点数
	this->polygonNum = planeNum.x * planeNum.y * 2 + (planeNum.y - 1) * 4;		// ポリゴン数
	this->indexNum = (planeNum.x + 1) * 2 * planeNum.y + (planeNum.y - 1) * 2;	// インデックス数

	// 頂点シェーダー宣言
	{
		D3DVERTEXELEMENT9 planeDecl[] =		// 頂点データのレイアウトを定義
		{
			{ 0,  0, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0 },
			{ 0, 12, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_NORMAL,   0 },
			{ 0, 24, D3DDECLTYPE_FLOAT2, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 0 },
			{ 0, 32, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TANGENT,  0 },
			D3DDECL_END()
		};
		pDevice->CreateVertexDeclaration(planeDecl, &this->vertexDecl);
	}

	// 頂点バッファ作成
	{
		if (FAILED(pDevice->CreateVertexBuffer(this->vertexNum * sizeof(PLANEVERTEX), D3DUSAGE_WRITEONLY, 0, D3DPOOL_MANAGED, &this->vertexBuffer, NULL)))
		{
			cout << "[Error] Make <Plane> vertex buffer ... fail!" << endl;	// エラーメッセージ
			return E_FAIL;
		}

		PLANEVERTEX* VertexBuffer;

		// 頂点データの範囲をロックし、頂点バッファ メモリへのポインタを取得する
		this->vertexBuffer->Lock(0, 0, (void**)&VertexBuffer, 0);

		// 頂点バッファの中身を埋める
		for (int numY = 0; numY < (planeNum.y + 1); numY++)
		{
			for (int numX = 0; numX < (planeNum.x + 1); numX++)
			{
				VertexBuffer[numY * (int(planeNum.x) + 1) + numX].position.x = -(planeNum.x / 2.0f) * planeSize.x + numX * planeSize.x;
				VertexBuffer[numY * (int(planeNum.x) + 1) + numX].position.y = 0;
				VertexBuffer[numY * (int(planeNum.x) + 1) + numX].position.z = (planeNum.y / 2.0f) * planeSize.y - numY * planeSize.y;

				VertexBuffer[numY * (int(planeNum.x) + 1) + numX].normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

				VertexBuffer[numY * (int(planeNum.x) + 1) + numX].mTextures.x = numX * 1.0f;
				VertexBuffer[numY * (int(planeNum.x) + 1) + numX].mTextures.y = numY * 1.0f;

				if (VertexBuffer[numY * (int(planeNum.x) + 1) + numX].position.x = 0)
				{
					// YZ平面
					VertexBuffer[numY * (int(planeNum.x) + 1) + numX].tangent = D3DXVECTOR3(0, 0, 1);
				}
				else if (VertexBuffer[numY * (int(planeNum.x) + 1) + numX].position.y = 0)
				{
					// ZX平面
					VertexBuffer[numY * (int(planeNum.x) + 1) + numX].tangent = D3DXVECTOR3(1, 0, 0);

				}
				else if (VertexBuffer[numY * (int(planeNum.x) + 1) + numX].position.z = 0)
				{
					// XY平面
					VertexBuffer[numY * (int(planeNum.x) + 1) + numX].tangent = D3DXVECTOR3(0, 1, 0);
				}
				
			}
		}

		// 頂点データをアンロックする
		this->vertexBuffer->Unlock();
	}

	// 頂点インデックスバッファ作成
	{
		if (FAILED(pDevice->CreateIndexBuffer(this->indexNum * sizeof(WORD), 0, D3DFMT_INDEX16, D3DPOOL_DEFAULT, &this->indexBuffer, NULL)))
		{
			cout << "[Error] Make <Plane> vertex index buffer ... fail!" << endl;	// エラーメッセージ
			return E_FAIL;
		}

		WORD* vertexIndex = NULL;		// イデックスの中身を埋める

		this->indexBuffer->Lock(0, 0, (void**)&vertexIndex, 0);	// インデックス データのある一定範囲をロックし、そのインデックス バッファー メモリーへのポインターを取得する

		int index = 0;
		for (int numY = 0; numY < planeNum.y; numY++)
		{
			if (numY > 0)
			{// 縮退ポリゴンのためのダブりの設定
				vertexIndex[index] = (numY + 1) * (planeNum.x + 1);
				index++;
			}

			for (int nCntVtxX = 0; nCntVtxX < (planeNum.x + 1); nCntVtxX++)
			{
				vertexIndex[index] = (numY + 1) * (planeNum.x + 1) + nCntVtxX;
				index++;
				vertexIndex[index] = numY * (planeNum.x + 1) + nCntVtxX;
				index++;
			}

			if (numY < (planeNum.y - 1))
			{// 縮退ポリゴンのためのダブりの設定
				vertexIndex[index] = numY * (planeNum.x + 1) + planeNum.x;
				index++;
			}
		}

		this->indexBuffer->Unlock();	// インデックス データのロックを解除する
	}

	return S_OK;
}

//*****************************************************************************
//
// 更新
//
//*****************************************************************************
void Plane::update()
{
	// 行列更新
	SetWorldMatrix();

	if (GetKeyboardTrigger(DIK_F1))
	{
		renderStatus = RS_withoutLight;
	}
	if (GetKeyboardTrigger(DIK_F2))
	{
		renderStatus = RS_withLight;
	}
	if (GetKeyboardTrigger(DIK_F3))
	{
		renderStatus = RS_withNormalMap;
	}
}

//*****************************************************************************
//
// ワールド変換
//
//*****************************************************************************
void Plane::SetWorldMatrix()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxScl, mtxRot, mtxTranslate;

	// ワールドマトリックスを初期化する
	D3DXMatrixIdentity(&this->wMatrix);

	// 平行移動を反映
	D3DXMatrixTranslation(&mtxTranslate, this->pos.x, this->pos.y, this->pos.z);
	D3DXMatrixMultiply(&this->wMatrix, &this->wMatrix, &mtxTranslate);
}

//*****************************************************************************
//
// テクスチャを描画する
//
//*****************************************************************************
void Plane::draw(Shader* mShader, Camera* camera)
{
	PDIRECT3DDEVICE9 pDevice = GetDevice();

	// テクニックを設定
	switch (renderStatus)
	{
	case RS_withoutLight:
		renderStatus = RS_withoutLight;
		mShader->mEffect->SetTechnique("render_without_light");
		break;

	case RS_withLight:
		renderStatus = RS_withLight;
		mShader->mEffect->SetTechnique("render_with_light");

		// カメラ位置の設定
		mShader->mEffect->SetValue("cameraPos", &camera->posEye, sizeof(D3DXVECTOR3));
		break;

	case RS_withNormalMap:
		renderStatus = RS_withNormalMap;
		mShader->mEffect->SetTechnique("render_with_normalMap");

		// カメラ位置の設定
		mShader->mEffect->SetValue("cameraPos", &camera->posEye, sizeof(D3DXVECTOR3));
		// ノーマルマップを設定
		mShader->mEffect->SetTexture("normalMap", this->normalMap);
		break;
	}

	// ワールド変換、ビューイング変換、プロジェクション変換マトリックス
	mShader->mEffect->SetMatrix("wMat", &this->wMatrix);
	mShader->mEffect->SetMatrix("vMat", &camera->vMatrix);
	mShader->mEffect->SetMatrix("pMat", &camera->pMatrix);

	// テクスチャの設定
	mShader->mEffect->SetTexture("tex", this->tex);

	// 描画
	UINT passNum = 0;
	mShader->mEffect->Begin(&passNum, 0);
	// 各パスを実行する
	for (unsigned int count = 0; count < passNum; count++)
	{
		mShader->mEffect->BeginPass(count);
		
		pDevice->SetVertexDeclaration(this->vertexDecl);							// 頂点宣言を設定
		pDevice->SetStreamSource(0, this->vertexBuffer, 0, sizeof(PLANEVERTEX));	// 頂点バッファをデバイスのデータストリームにバイナリ
		pDevice->SetIndices(this->indexBuffer);										// 頂点インデックスバッファを設定
		pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, this->vertexNum, 0, this->polygonNum);	// ポリゴンの描画

		mShader->mEffect->EndPass();
	}
	mShader->mEffect->End();
}