//*****************************************************************************
//
// �L�����N�^�[�x�[�X���� [Character.h]
//
// Author : LIAO HANCHEN
//
//*****************************************************************************
#ifndef _CHARACTER_H_
#define _CHARACTER_H_

#include <map>

#include "Model.h"
#include "Sound.h"
#include "BoundingBox.h"
#include "..\Engine.h"
#include "..\DebugMessage.h"
#include "..\Shader\CelShader.h"


// �ړ��@= lookVector * SPEED_COEFFICIENT
#define MAX_BACK_SPEED_COEFFICIENT	(-0.28f)
#define MAX_FRONT_SPEED_COEFFICIENT	(0.38f)

#define MAX_HP						(3)

#define BULLET_TIME					(3.0f)

struct PlayerModel
{
	Model*			shipBody;
	Model*			shipCannon;
};

typedef enum
{
	LL_BACK = -1,	// [-1]���
	LL_STOP,		// [0]��~
	LL_FRONT,		// [1]�O�i
}LEVER_LEVEL;

enum Border_Status
{
	BS_dotMinus,
	BS_dotplus,
};

//*****************************************************************************
//
// �N���X�錾
//
//*****************************************************************************
class Character
{
private:
	bool			CheckMapBorder();	// �}�b�v����o�邩�ǂ������`�F�b�N

public:
	D3DXMATRIX		worldMatrix;	// ���[���h�ϊ��}�g���b�N�X
	D3DXMATRIX		lightMatrix;	// ���C�g�}�g���b�N�X
	D3DXMATRIX		normalMatrix;	// ���C�g�}�g���b�N�X

	LEVER_LEVEL		leverLevel;		// �D�̃��o�[����
	double			speed;			// �X�s�[�h�Ɋւ���{��
	DebugMessage*	message;		// Debug���b�Z�[�W
	float			waveAngle;		// �h��W��

	// �x�N�g��
	D3DXVECTOR3		upVector;		// �J�����̏�����x�N�g��
	D3DXVECTOR3		lookVector;		// �J�����̒��������x�N�g��
	D3DXVECTOR3		rightVector;	// �J�����̉E�����x�N�g��

	// �Œ葮��
	D3DXVECTOR3		pos;			// �ʒu
	D3DXVECTOR3		rot;			// ��]
	D3DXVECTOR3		scl;			// �g��k��

	PlayerModel		player;			// �v���[���[���f���W��
	BoundingBox*	check;			// �_���[�W�p
	BoundingBox*	space;			// ��ԗp
	
	int				HP;

	float			leftTime;
	bool			leftShooting;
	float			rightTime;
	bool			rightShooting;

	bool			isBorder;
	Border_Status	borderStatus;

	Character();
	~Character();

	D3DXVECTOR3  MoveAlongVecLook(float speedCoefficient);	// ���������ɉ����Ĉړ�
	void PosToMessageAndMessageDraw(int row);	// ���W�����b�Z�[�W�ɓn���āA��ʂɕ`�悷��
	void SetWorldMatrix();						// ���[���h�ϊ���
	void ChangeLever(LEVER_LEVEL level);		// ���o�[�̑���ɂ���ăX�s�[�h��ς��
	bool CheckHitBB(Character* Object);			// �����蔻��
	void RotationVecUp(float angle);			// ������̃x�N�g���ɂ��ĉ�]

	virtual void Update(float rot);						// �L�����N�^�[�X�V
	virtual void Draw(CelShader* celShader, D3DXMATRIX* VPMatrix);	// �L�����N�^�[�̕`��

	void InitCharacter();

	void Move();								// �L�����N�^�[�ړ�
};
#endif // !_CHARACTER_H_

