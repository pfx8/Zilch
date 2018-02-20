//*****************************************************************************
//
// 座標変換済み頂点で2D板ポリゴンを描画 [ScreenPolygon.cpp]
//
// Author : LIAO HANCHEN
//
//*****************************************************************************
#include "ScreenPolygon.h"

//*****************************************************************************
//
// コンストラクタ
//
//*****************************************************************************
ScreenPolygon::ScreenPolygon()
{
	this->vertexDecl = NULL;
	this->indexBuffer = NULL;

	this->UIminiMapVertexBuffer = NULL;
	this->UIminiMapTexture = NULL;
	this->UIminiMapPlayerVertexBuffer = NULL;
	this->UIminiMapPlayerTexture = NULL;
	this->UIminiMapEnemyVertexBuffer = NULL;
	this->UIminiMapEnemyTexture = NULL;
	this->UIleftVertexBuffer = NULL;
	this->UIleftTexture = NULL;

	this->HP = 3;
	this->UIHPVertexBuffer[0] = NULL;
	this->UIHPVertexBuffer[1] = NULL;
	this->UIHPVertexBuffer[2] = NULL;
	this->UIHPTexture = NULL;

	this->UIpanVertexBuffer = NULL;
	this->UIpanTexture = NULL;
	this->UIzenVertexBuffer = NULL;
	this->UIzenTexture = NULL;
	this->UIstopVertexBuffer = NULL;
	this->UIstopTexture = NULL;
	this->UIgouVertexBuffer = NULL;
	this->UIgouTexture = NULL;

	this->UIleftVertexBuffer = NULL;
	this->UIleftTexture = NULL;
	this->UIrightVertexBuffer = NULL;
	this->UIrightTexture = NULL;
	this->leftShooting = 0.0f;
	this->rightShooting = 0.0f;

	// シェーダーを初期化
	this->RHWshader = new RHWShader;
	this->RHWshader->InitShader();

	// リソース管理を初期化
	this->resourcesManager = new ResourcesManager;
	this->resourcesManager->LoadTexture("UIminimap", &this->UIminiMapTexture);
	this->resourcesManager->LoadTexture("UIplayer", &this->UIminiMapPlayerTexture);
	this->resourcesManager->LoadTexture("UIenemy", &this->UIminiMapEnemyTexture);

	this->resourcesManager->LoadTexture("UIhp", &this->UIHPTexture);

	this->resourcesManager->LoadTexture("UIpan", &this->UIpanTexture);
	this->resourcesManager->LoadTexture("UIzen", &this->UIzenTexture);
	this->resourcesManager->LoadTexture("UIstop", &this->UIstopTexture);
	this->resourcesManager->LoadTexture("UIgou", &this->UIgouTexture);

	this->resourcesManager->LoadTexture("UIleft", &this->UIleftTexture);
	this->resourcesManager->LoadTexture("UIright", &this->UIrightTexture);

	MakeVertexDecl();
	MakeIndex();

	// 各頂点を作成
	MakeVertex(D3DXVECTOR2(SCREEN_WIDTH - MINIMAP_SIZE, SCREEN_HEIGHT - MINIMAP_SIZE), D3DXVECTOR2(MINIMAP_SIZE, MINIMAP_SIZE), &this->UIminiMapVertexBuffer);

	MakeVertex(D3DXVECTOR2(30, 30), D3DXVECTOR2(64, 80), &this->UIHPVertexBuffer[0]);
	MakeVertex(D3DXVECTOR2(114, 30), D3DXVECTOR2(64, 80), &this->UIHPVertexBuffer[1]);
	MakeVertex(D3DXVECTOR2(198, 30), D3DXVECTOR2(64, 80), &this->UIHPVertexBuffer[2]);

	MakeVertex(D3DXVECTOR2(0, SCREEN_HEIGHT - 360), D3DXVECTOR2(360, 360), &this->UIpanVertexBuffer);
	MakeVertex(D3DXVECTOR2(122, SCREEN_HEIGHT - 180 - 80), D3DXVECTOR2(120, 60), &this->UIzenVertexBuffer);
	MakeVertex(D3DXVECTOR2(152, SCREEN_HEIGHT - 130 - 80), D3DXVECTOR2(60, 60), &this->UIstopVertexBuffer);
	MakeVertex(D3DXVECTOR2(122, SCREEN_HEIGHT - 75 - 80), D3DXVECTOR2(120, 60), &this->UIgouVertexBuffer);

	MakeVertex(D3DXVECTOR2(SCREEN_WIDTH - 90, 50), D3DXVECTOR2(50, 50), &this->UIrightVertexBuffer);
	MakeVertex(D3DXVECTOR2(SCREEN_WIDTH - 160, 50), D3DXVECTOR2(50, 50), &this->UIleftVertexBuffer);
}

//*****************************************************************************
//
// デストラクタ
//
//*****************************************************************************
ScreenPolygon::~ScreenPolygon()
{
	RELEASE_POINT(this->vertexDecl);
	RELEASE_POINT(this->indexBuffer);
	
	RELEASE_POINT(this->UIminiMapVertexBuffer);
	RELEASE_POINT(this->UIminiMapTexture);
	RELEASE_POINT(this->UIHPVertexBuffer[0]);
	RELEASE_POINT(this->UIHPVertexBuffer[1]); 
	RELEASE_POINT(this->UIHPVertexBuffer[2]);
	RELEASE_POINT(this->UIHPTexture);
	RELEASE_POINT(this->UIleftVertexBuffer);
	RELEASE_POINT(this->UIleftTexture);

	RELEASE_CLASS_POINT(this->resourcesManager);
}

//*****************************************************************************
//
// 頂点宣言
//
//*****************************************************************************
void ScreenPolygon::MakeVertexDecl()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 頂点シェーダー宣言
	{
		D3DVERTEXELEMENT9 planeDecl[] =		// 頂点データのレイアウトを定義
		{
			{ 0, 0, D3DDECLTYPE_FLOAT2, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITIONT, 0 },
			{ 0, 8, D3DDECLTYPE_FLOAT2, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD , 0 },
			D3DDECL_END()
		};
		pDevice->CreateVertexDeclaration(planeDecl, &this->vertexDecl);
	}
}

//*****************************************************************************
//
// 頂点作成
//
//*****************************************************************************
HRESULT ScreenPolygon::MakeVertex(D3DXVECTOR2 pos, D3DXVECTOR2 size, LPDIRECT3DVERTEXBUFFER9* vertexBufferPoint)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 頂点バッファ作成
	if (FAILED(pDevice->CreateVertexBuffer(4 * sizeof(VERTEX_2D), D3DUSAGE_WRITEONLY, 0, D3DPOOL_MANAGED, vertexBufferPoint, NULL)))
	{
		std::cout << "[Error] 頂点バッファが生成できない!" << std::endl;	// エラーメッセージ
		return E_FAIL;
	}

	VERTEX_2D* VertexBuffer;

	// 頂点データの範囲をロックし、頂点バッファ メモリへのポインタを取得する
	(*vertexBufferPoint)->Lock(0, 0, (void**)&VertexBuffer, 0);

	// 頂点座標の設定
	VertexBuffer[0].position = D3DXVECTOR2(pos.x, pos.y);
	VertexBuffer[1].position = D3DXVECTOR2(pos.x + size.x, pos.y);
	VertexBuffer[2].position = D3DXVECTOR2(pos.x, pos.y + size.y);
	VertexBuffer[3].position = D3DXVECTOR2(pos.x + size.x, pos.y + size.y);

	// テクスチャ1座標の設定
	VertexBuffer[0].texturePosition = D3DXVECTOR2(0.0f, 0.0f);
	VertexBuffer[1].texturePosition = D3DXVECTOR2(1.0f, 0.0f);
	VertexBuffer[2].texturePosition = D3DXVECTOR2(0.0f, 1.0f);
	VertexBuffer[3].texturePosition = D3DXVECTOR2(1.0f, 1.0f);

	// 頂点データをアンロックする
	(*vertexBufferPoint)->Unlock();

	return S_OK;
}

//*****************************************************************************
//
// 回転頂点作成
//
//*****************************************************************************
HRESULT ScreenPolygon::MakeTransVertex(D3DXVECTOR2 pos, D3DXVECTOR2 size, LPDIRECT3DVERTEXBUFFER9* vertexBufferPoint, float rot)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 頂点バッファ作成
	if (FAILED(pDevice->CreateVertexBuffer(4 * sizeof(VERTEX_2D), D3DUSAGE_WRITEONLY, 0, D3DPOOL_MANAGED, vertexBufferPoint, NULL)))
	{
		std::cout << "[Error] 頂点バッファが生成できない!" << std::endl;	// エラーメッセージ
		return E_FAIL;
	}

	VERTEX_2D* VertexBuffer;
	D3DXMATRIX trans;
	D3DXVECTOR2 rotationCenter = D3DXVECTOR2(182, 620);
	D3DXMatrixTransformation2D(&trans, 0, 0, 0, &rotationCenter, rot, 0);

	// 頂点データの範囲をロックし、頂点バッファ メモリへのポインタを取得する
	(*vertexBufferPoint)->Lock(0, 0, (void**)&VertexBuffer, 0);

	// 頂点座標の設定
	VertexBuffer[0].position = D3DXVECTOR2(pos.x, pos.y);
	D3DXVec2TransformCoord(&VertexBuffer[0].position, &VertexBuffer[0].position, &trans);
	VertexBuffer[1].position = D3DXVECTOR2(pos.x + size.x, pos.y);
	D3DXVec2TransformCoord(&VertexBuffer[1].position, &VertexBuffer[1].position, &trans);
	VertexBuffer[2].position = D3DXVECTOR2(pos.x, pos.y + size.y);
	D3DXVec2TransformCoord(&VertexBuffer[2].position, &VertexBuffer[2].position, &trans);
	VertexBuffer[3].position = D3DXVECTOR2(pos.x + size.x, pos.y + size.y);
	D3DXVec2TransformCoord(&VertexBuffer[3].position, &VertexBuffer[3].position, &trans);

	// テクスチャ1座標の設定
	VertexBuffer[0].texturePosition = D3DXVECTOR2(0.0f, 0.0f);
	VertexBuffer[1].texturePosition = D3DXVECTOR2(1.0f, 0.0f);
	VertexBuffer[2].texturePosition = D3DXVECTOR2(0.0f, 1.0f);
	VertexBuffer[3].texturePosition = D3DXVECTOR2(1.0f, 1.0f);

	// 頂点データをアンロックする
	(*vertexBufferPoint)->Unlock();

	return S_OK;
}

//*****************************************************************************
//
// 更新する
//
//*****************************************************************************
void ScreenPolygon::Update(Character* player, Character* enemy)
{
	this->HP = player->HP;
	this->level = player->leverLevel;
	this->leftShooting = player->leftTime;
	this->rightShooting = player->rightTime;

	D3DXVECTOR2 miniMapCenter = D3DXVECTOR2(SCREEN_WIDTH - MINIMAP_SIZE / 2, SCREEN_HEIGHT - MINIMAP_SIZE / 2);
	float mapSize = 17.0f * 150;

	D3DXVECTOR2 miniMapPlayer = miniMapCenter + D3DXVECTOR2(MINIMAP_SIZE * player->pos.x / mapSize, -1 * MINIMAP_SIZE * player->pos.z / mapSize);
	MakeVertex(miniMapPlayer, D3DXVECTOR2(20, 20), &this->UIminiMapPlayerVertexBuffer);

	/*for (int count = 0; count < 5; count++)
	{
		D3DXVECTOR2 miniMapEnemy = miniMapCenter + D3DXVECTOR2(MINIMAP_SIZE * enemy[count].pos.x / mapSize, -1 * MINIMAP_SIZE * enemy[count].pos.z / mapSize);
		MakeVertex(miniMapEnemy, D3DXVECTOR2(20, 20), &this->UIminiMapEnemyVertexBuffer);
	}*/

	D3DXVECTOR2 miniMapEnemy = miniMapCenter + D3DXVECTOR2(MINIMAP_SIZE * enemy->pos.x / mapSize, -1 * MINIMAP_SIZE * enemy->pos.z / mapSize);
	MakeVertex(miniMapEnemy, D3DXVECTOR2(20, 20), &this->UIminiMapEnemyVertexBuffer);
	
	// プレーヤーの方向により角度を更新
	MakeTransVertex(D3DXVECTOR2(122, SCREEN_HEIGHT - 180 - 80), D3DXVECTOR2(120, 60), &this->UIzenVertexBuffer, player->rot.y);
	MakeTransVertex(D3DXVECTOR2(152, SCREEN_HEIGHT - 130 - 80), D3DXVECTOR2(60, 60), &this->UIstopVertexBuffer, player->rot.y);
	MakeTransVertex(D3DXVECTOR2(122, SCREEN_HEIGHT - 75 - 80), D3DXVECTOR2(120, 60), &this->UIgouVertexBuffer, player->rot.y);
}

//*****************************************************************************
//
// インデックス作成
//
//*****************************************************************************
HRESULT ScreenPolygon::MakeIndex()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	if (FAILED(pDevice->CreateIndexBuffer(6 * sizeof(WORD), 0, D3DFMT_INDEX16, D3DPOOL_DEFAULT, &this->indexBuffer, NULL)))
	{
		std::cout << "[Error] 頂点インデクスが生成できない!" << std::endl;	// エラーメッセージ
		return E_FAIL;
	}

	WORD* vertexIndex = NULL;		// イデックスの中身を埋める

	this->indexBuffer->Lock(0, 0, (void**)&vertexIndex, 0);	// インデックス データのある一定範囲をロックし、そのインデックス バッファー メモリーへのポインターを取得する

	vertexIndex[0] = 0, vertexIndex[1] = 1, vertexIndex[2] = 2;
	vertexIndex[3] = 2, vertexIndex[4] = 1, vertexIndex[5] = 3;

	this->indexBuffer->Unlock();	// インデックス データのロックを解除する

	return S_OK;
}

//*****************************************************************************
//
// UIを描画する
//
//*****************************************************************************
void ScreenPolygon::Draw()
{
	// minimap
	DrawObject(this->UIminiMapVertexBuffer, this->UIminiMapTexture);
	DrawObject(this->UIminiMapPlayerVertexBuffer, this->UIminiMapPlayerTexture);
	DrawObject(this->UIminiMapEnemyVertexBuffer, this->UIminiMapEnemyTexture);

	// HP
	int i = 0;
	while (i < 3)
	{
		DrawObject(this->UIHPVertexBuffer[i], this->UIHPTexture);
		if ((i + 1) == this->HP)
			break;
		else
			i++;
	}

	DrawObject(this->UIpanVertexBuffer, this->UIpanTexture);

	// 船の状態
	DrawObject(this->UIzenVertexBuffer, this->UIzenTexture, LL_FRONT);
	DrawObject(this->UIstopVertexBuffer, this->UIstopTexture, LL_STOP);
	DrawObject(this->UIgouVertexBuffer, this->UIgouTexture, LL_BACK);

	// 操作ボタン
	DrawObject(this->UIleftVertexBuffer, this->UIleftTexture, 9, (leftShooting / 3.0f), true);
	DrawObject(this->UIrightVertexBuffer, this->UIrightTexture, 9, (rightShooting / 3.0f), true);
}

//*****************************************************************************
//
// 動的なものを描画する
//
// level ... -1後退 0停止 1前進 2普通(デフォルト)
//
//*****************************************************************************
void ScreenPolygon::DrawObject(LPDIRECT3DVERTEXBUFFER9 vertexBuffer, LPDIRECT3DTEXTURE9 titleTexture, int level, float alpha, bool needa)
{
	PDIRECT3DDEVICE9 pDevice = GetDevice();

	// テクニックを設定
	this->RHWshader->effectPoint->SetTechnique(this->RHWshader->RHWShaderHandle);

	// テクスチャの設定
	this->RHWshader->effectPoint->SetTexture(this->RHWshader->textureHandle, titleTexture);

	if (this->level == level)
	{
		// 船の状態を設定(動的な)
		int temp = 1;
		this->RHWshader->effectPoint->SetValue("type", &temp, sizeof(int));
	}
	else if (needa == true)
	{
		// 変化なしのもの(静的な)
		int temp = 2;
		this->RHWshader->effectPoint->SetValue("type", &temp, sizeof(int));
		// アルファ値を設定
		this->RHWshader->effectPoint->SetValue("alpha", &alpha, sizeof(float));
	}
	else
	{
		// 変化なしのもの(静的な)
		int temp = 0;
		this->RHWshader->effectPoint->SetValue("type", &temp, sizeof(int));
	}

	// 描画
	UINT passNum = 0;
	this->RHWshader->effectPoint->Begin(&passNum, 0);
	// 各パスを実行する
	for (int count = 0; count < passNum; count++)
	{
		this->RHWshader->effectPoint->BeginPass(0);

		pDevice->SetVertexDeclaration(this->vertexDecl);						// 頂点宣言を設定
		pDevice->SetStreamSource(0, vertexBuffer, 0, sizeof(VERTEX_2D));		// 頂点バッファをデバイスのデータストリームにバイナリ
		pDevice->SetIndices(this->indexBuffer);									// 頂点インデックスバッファを設定
		pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 4, 0, 2);		// ポリゴンの描画

		this->RHWshader->effectPoint->EndPass();
	}
	this->RHWshader->effectPoint->End();
}