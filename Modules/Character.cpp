//*****************************************************************************
//
// キャラクターベース処理 [Character.cpp]
//
// Author : LIAO HANCHEN
//
//*****************************************************************************
#include "Character.h"

//*****************************************************************************
//
// コンストラクタ
//
//*****************************************************************************
Character::Character()
{
	// クラスポインタ
	this->message = new DebugMessage;
	this->check = new BoundingBox;
	this->space = new BoundingBox;
	this->player.shipBody = new Model;
	this->player.shipCannon = new Model;

	InitCharacter();
}

//*****************************************************************************
//
// 初期化
//
//*****************************************************************************
void Character::InitCharacter()
{
	this->upVector = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	this->lookVector = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
	this->rightVector = D3DXVECTOR3(1.0f, 0.0f, 0.0f);

	this->pos = D3DXVECTOR3(0.0f, 0.5f, 0.0f);
	this->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	this->scl = D3DXVECTOR3(1.0f, 1.0f, 1.0f);

	this->waveAngle = 0.0f;
	this->speed = 0.0f;

	this->HP = MAX_HP;

	this->leftTime = 3.0f;
	this->leftShooting = false;
	this->rightTime = 3.0f;
	this->rightShooting = false;

	this->isBorder = false;

	this->leverLevel = LL_STOP;
}

//*****************************************************************************
//
// デストラクタ
//
//*****************************************************************************
Character::~Character()
{
	RELEASE_CLASS_POINT(this->message);
	RELEASE_CLASS_POINT(this->check);
	RELEASE_CLASS_POINT(this->space);

	RELEASE_CLASS_ARRY_POINT(this->player.shipBody);
	RELEASE_CLASS_ARRY_POINT(this->player.shipCannon);
}

//*****************************************************************************
//
// 座標をメッセージに渡して、画面に描画する
//
//*****************************************************************************
void Character::PosToMessageAndMessageDraw(int row)
{
	D3DXVECTOR3 temp;
	temp.x = lightMatrix._41;
	temp.y = lightMatrix._42;
	temp.z = lightMatrix._43;
	
	D3DXVECTOR3 temp2;
	temp2.x = leftTime;
	temp2.y = rightTime;
	temp2.z = D3DXToDegree(rot.y);

	//this->message->DrawPosMessage("Light", temp, D3DXVECTOR2(0, float((row + 0) * 18)));
	//this->message->DrawPosMessage("time", temp2, D3DXVECTOR2(0, float((row + 0) * 18)));
	this->message->DrawPosMessage("look", this->lookVector, D3DXVECTOR2(0, float((row + 0) * 18)));
	this->message->DrawPosMessage("right", this->rightVector, D3DXVECTOR2(0, float((row + 1) * 18)));
}

//*****************************************************************************
//
// キャラクターの描画
//
//*****************************************************************************
void Character::Draw(CelShader* celShader, D3DXMATRIX* VPMatrix)
{
	// メッシュを描画する
	this->player.shipBody->DrawModel(celShader, &this->worldMatrix, VPMatrix, &this->lightMatrix, &this->normalMatrix, MT_ship);
	this->player.shipCannon->DrawModel(celShader, &this->worldMatrix, VPMatrix, &this->lightMatrix, &this->normalMatrix, MT_ship);
}

//*****************************************************************************
//
// キャラクター移動
//
//*****************************************************************************
void Character::Move()
{
	
}

//*****************************************************************************
//
// キャラクター更新
//
//*****************************************************************************
void Character::Update(float rot)
{
	// プレーヤー操作 
	bool isButton = false;
	isButton = (GetKeyboardTrigger(DIK_W) || IsButtonTriggered(0, LEFT_STICK_UP));
	if (isButton)	// 前に進む
	{
		if (this->leverLevel == LL_STOP)
		{
			this->ChangeLever(LL_FRONT);
		}
		else if(this->leverLevel == LL_BACK)
		{
			this->ChangeLever(LL_STOP);
		}	
	}

	isButton = (GetKeyboardTrigger(DIK_S) || IsButtonTriggered(0, LEFT_STICK_DOWN));
	if (isButton)	// 後ろに進む
	{
		if (this->leverLevel == LL_STOP)
		{
			this->ChangeLever(LL_BACK);
		}
		else if(this->leverLevel == LL_FRONT)
		{
			this->ChangeLever(LL_STOP);
		}
	}

	isButton = (GetKeyboardPress(DIK_A) || IsButtonPressed(0, LEFT_STICK_LEFT));
	if (isButton)	// 左回転
	{
		// 更新キャラクターをカメラの回転角度0.05
		this->RotationVecUp(-0.5f / 180.0f * D3DX_PI);
	}

	isButton = (GetKeyboardPress(DIK_D) || IsButtonPressed(0, LEFT_STICK_RIGHT));
	if (isButton)	// 右回転
	{
		// 更新キャラクターをカメラの回転角度
		this->RotationVecUp(0.5f / 180.0f * D3DX_PI);
	}

	// テスト、HP減り
	if (GetKeyboardTrigger(DIK_P))
	{
		this->HP -= 1;
	}

	// 波に合わせて揺れる
	this->waveAngle = rot;
	if (this->waveAngle > D3DX_PI * 2.0f)
		this->waveAngle = 0.0f;
	this->pos.y = 0.5 + 0.8 * sinf(this->waveAngle);


	// 移動範囲をチェック
	if (CheckMapBorder() == false)
	{
		// ボーダーに触ってなければ
		
		// スビード
		switch (leverLevel)
		{
		case LL_FRONT:
			this->speed += 0.0003f;
			if (this->speed >= MAX_FRONT_SPEED_COEFFICIENT)
				this->speed = MAX_FRONT_SPEED_COEFFICIENT;
			break;
		case LL_STOP:
			if (this->speed > 0)
			{
				this->speed -= 0.0001f;
				if (this->speed <= 0)
					this->speed = 0;
			}
			else if (this->speed < 0)
			{
				this->speed += 0.0003f;
				if (this->speed >= 0)
					this->speed = 0;
			}
			else
			{
				this->speed = 0.0f;
			}
			break;
		case LL_BACK:
			this->speed -= 0.0001f;
			if (this->speed <= MAX_BACK_SPEED_COEFFICIENT)
				this->speed = MAX_BACK_SPEED_COEFFICIENT;
			break;
		default:
			break;
		}

		// 移動
		MoveAlongVecLook(this->speed);
	}

	// ワールド変換
	SetWorldMatrix();

	// 発射更新
	if (this->leftShooting == true)
	{
		leftTime -= 3.0f / 180.0f;
		if (leftTime <= 0)
		{
			leftTime = 3;
			leftShooting = false;
		}
	}

	if (this->rightShooting == true)
	{
		rightTime -= 3.0f / 180.0f;
		if (rightTime <= 0)
		{
			rightTime = 3;
			rightShooting = false;
		}
	}
}

//*****************************************************************************
//
// マップから出るかどうかをチェック
//
//*****************************************************************************
bool Character::CheckMapBorder()
{
	D3DXVECTOR3 temp = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	temp = this->pos + this->check->size;

	D3DXVECTOR3 temp2 = D3DXVECTOR3(0.0f, 0.0f, 0.0f); // 軸正方
	
	// 内積 > 0, 0 < 角度 < 90 || 270 < 角度 < 360
	// 内積 < 0, 90 < 角度 < 270

	temp2 = D3DXVECTOR3(0.0f, 0.0f, 1.0f); // Z軸
	if (temp.x >= 1100)
	{
		if (D3DXVec3Dot(&this->lookVector, &temp2) > 0)
		{
			this->pos += temp2 * this->speed;
			this->isBorder = true;
			this->borderStatus = BS_dotplus;

			return true;
		}
		else if(D3DXVec3Dot(&this->lookVector, &temp2) < 0)
		{
			this->pos -= temp2 * this->speed;
			this->isBorder = true;
			this->borderStatus = BS_dotMinus;

			return true;
		}
		else
		{
			return false;
		}
	}

	if (temp.x <= -1100)
	{
		if (D3DXVec3Dot(&this->lookVector, &temp2) > 0)
		{
			this->pos += temp2 * this->speed;
			this->isBorder = true;
			this->borderStatus = BS_dotplus;

			return true;
		}
		else if(D3DXVec3Dot(&this->lookVector, &temp2) < 0)
		{
			this->pos -= temp2 * this->speed;
			this->isBorder = true;
			this->borderStatus = BS_dotMinus;

			return true;
		}
		else
		{
			return false;
		}
	}

	temp2 = D3DXVECTOR3(1.0f, 0.0f, 0.0f); // X軸
	if (temp.z >= 1250)
	{
		if (D3DXVec3Dot(&this->lookVector, &temp2) > 0)
		{
			this->pos += temp2 * this->speed;
			this->isBorder = true;

			return true;
		}
		else
		{
			this->pos -= temp2 * this->speed;
			this->isBorder = true;

			return true;
		}
	}

	if (temp.z <= -1250)
	{
		if (D3DXVec3Dot(&this->lookVector, &temp2) > 0)
		{
			this->pos += temp2 * this->speed;
			this->isBorder = true;

			return true;
		}
		else
		{
			this->pos -= temp2 * this->speed;
			this->isBorder = true;

			return true;
		}
	}

	return false;
}

//*****************************************************************************
//
// 上方向のベクトルにして回転
//
//*****************************************************************************
void Character::RotationVecUp(float angle)
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

	// test
	this->rightVector = -this->rightVector;
}

//*****************************************************************************
//
// レバーの操作によってスピードを変わる
//
//*****************************************************************************
void Character::ChangeLever(LEVER_LEVEL level)
{
	this->leverLevel = level;

	// コンソールに出すメッセージ
	switch (this->leverLevel)
	{
	case LL_FRONT:
		std::cout << "前" << std::endl; break;
	case LL_STOP:
		std::cout << "停" << std::endl; break;
	case LL_BACK:
		std::cout << "後" << std::endl; break;
	default:
		break;
	}

}

//*****************************************************************************
//
// 注視方向に沿って移動
//
//*****************************************************************************
D3DXVECTOR3 Character::MoveAlongVecLook(float speedCoefficient)
{
	this->pos += this->lookVector * speedCoefficient;

	return this->lookVector * speedCoefficient;
}

//*****************************************************************************
//
// ワールド変換を設定
//
//*****************************************************************************
void Character::SetWorldMatrix()
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

	// ライトマトリックス
	D3DXMATRIX mtxLightTranslate;
	D3DXMatrixIdentity(&this->lightMatrix);

	D3DXMatrixTranslation(&mtxLightTranslate, 0, this->pos.y, 0);
	D3DXMatrixMultiply(&this->lightMatrix, &this->lightMatrix, &mtxLightTranslate);

	//// ノーマルマトリックス
	//D3DXMATRIX mtxRotNormal, mtxTranslateNormal;
	//D3DXMatrixIdentity(&this->normalMatrix);

	//D3DXMatrixRotationYawPitchRoll(&mtxRotNormal, this->rot.y, this->rot.x, this->rot.z);
	//D3DXMatrixMultiply(&this->normalMatrix, &this->normalMatrix, &mtxRotNormal);

	/*D3DXMatrixTranslation(&mtxTranslateNormal, this->pos.x, this->pos.y, this->pos.z);
	D3DXMatrixMultiply(&this->normalMatrix, &this->normalMatrix, &mtxTranslateNormal);*/

	D3DXMatrixRotationYawPitchRoll(&mtxLightTranslate, this->rot.y, 0, 0);
	D3DXMatrixMultiply(&this->lightMatrix, &this->lightMatrix, &mtxLightTranslate);
}

//*****************************************************************************
//
// 当たり判定
//
//*****************************************************************************
bool Character::CheckHitBB(Character* Object)
{
	D3DXVECTOR3 ObjectPos = Object->pos;
	D3DXVECTOR3 ObjectSize = Object->check->size;

	if (
		this->pos.x + this->check->size.x / 2 > ObjectPos.x - ObjectSize.x / 2 &&
		this->pos.x - this->check->size.x / 2 < ObjectPos.x + ObjectSize.x / 2 &&
		this->pos.y - this->check->size.y / 2 < ObjectPos.y + ObjectSize.y / 2 &&
		this->pos.y + this->check->size.y / 2 > ObjectPos.y - ObjectSize.y / 2 &&
		this->pos.z + this->check->size.z / 2 > ObjectPos.z - ObjectSize.z / 2 &&
		this->pos.z - this->check->size.z / 2 < ObjectPos.z + ObjectSize.z / 2
		)
	{
		return true;
	}
	else
	{
		return false;
	}
}