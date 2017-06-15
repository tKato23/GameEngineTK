//	�w�b�_�t�@�C���̃C���N���[�h
#include "Enemy.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

Enemy::Enemy()
{
	Initialize();
}

//	����������
void Enemy::Initialize()
{
	//	���@�p�[�c�̓ǂݍ���
	m_Obj.resize(PARTS_NUM);

	m_Obj[PARTS_FOOT].LoadModelFile(L"Resources\\Foot.cmo");
	m_Obj[PARTS_BODY].LoadModelFile(L"Resources\\Body.cmo");
	m_Obj[PARTS_HEAD].LoadModelFile(L"Resources\\head.cmo");
	m_Obj[PARTS_ARM].LoadModelFile(L"Resources\\Arm.cmo");
	m_Obj[PARTS_GUN].LoadModelFile(L"Resources\\Gun.cmo");

	//	�e�q�֌W�̍\�z(�q�p�[�c�ɐe��ݒ�)
	m_Obj[PARTS_BODY].SetObjParent(&m_Obj[PARTS_FOOT]);
	m_Obj[PARTS_HEAD].SetObjParent(&m_Obj[PARTS_BODY]);
	m_Obj[PARTS_ARM].SetObjParent(&m_Obj[PARTS_BODY]);
	m_Obj[PARTS_GUN].SetObjParent(&m_Obj[PARTS_ARM]);

	//	�q�p�[�c�̐e����̃I�t�Z�b�g(���W�̂���)���Z�b�g
	m_Obj[PARTS_BODY].SetPosition(Vector3(0, 0.3f, 0));
	m_Obj[PARTS_HEAD].SetPosition(Vector3(0, 0.3f, 0));
	m_Obj[PARTS_ARM].SetPosition(Vector3(0.5f, 0.3f, -0.4f));
	m_Obj[PARTS_GUN].SetPosition(Vector3(0, 0.0f, -0.2));

	//	�^�C�}�[�̏�����
	m_Timer = 0;
	m_DistAngle = 0;

	//	�����ʒu������
	Vector3 pos;

	pos.x = rand() % 10;
	pos.z = rand() % 10;

	SetEnemyPosition(pos);
}


//	�X�V����
void Enemy::EnemyUpdate()
{

	m_Timer--;
	if (m_Timer < 0)
	{
		m_Timer = 60;

		//	�ڕW�p�������_���ɒ��I
		//	-0.5�`+0.5�̗���
		float rnd = (float)rand() / RAND_MAX - 0.5f;
		//	-90�`+90�̗���
		rnd *= 180.0f;
		rnd = XMConvertToRadians(rnd);

		m_DistAngle += rnd;
	}

	{
		//	���@�̊p�x����]
		Vector3 rot = getEnemyRot();

		//	���̊p�x�ƖڕW�p�x�̍�
		float angle = m_DistAngle - rot.y;
		if (angle > XM_PI)
		{
			angle -= XM_2PI;
		}
		if (angle < -XM_PI)
		{
			angle += XM_2PI;
		}
		//	���
		rot.y += angle * 0.01f;

		SetEnemyRotation(rot);
	}
	//	�@�̂̕����ɐi��
	//	�ړ��x�N�g��
	Vector3 moveV(0.0f, 0.0f, -0.1f);

	float angle = m_Obj[PARTS_FOOT].GetRotation().y;
	Matrix rotmat = Matrix::CreateRotationY(angle);
	moveV = Vector3::TransformNormal(moveV, rotmat);

	//	���@�̍��W���ړ�
	Vector3 pos = m_Obj[0].GetPosition();
	//head_pos += moveV;
	m_Obj[0].SetPosition(pos + moveV);


	for (std::vector<Obj3d>::iterator it = m_Obj.begin(); it != m_Obj.end(); it++)
	{
		it->Update();
	}
	
}

//	�`�揈��
void Enemy::EnemyDraw()
{
	for (std::vector<Obj3d>::iterator it = m_Obj.begin(); it != m_Obj.end(); it++)
	{
		it->Draw();
	}
}

//	�G�̍��W���擾
DirectX::SimpleMath::Vector3 Enemy::getEnemyPos()
{
	return m_Obj[0].GetPosition();
}

//	�G�̉�]�p���擾
DirectX::SimpleMath::Vector3 Enemy::getEnemyRot()
{
	return m_Obj[0].GetRotation();
}

void Enemy::SetEnemyPosition(const Vector3& pos)
{
	m_Obj[0].SetPosition(pos);
}

void Enemy::SetEnemyRotation(Vector3 rot)
{
	m_Obj[0].SetRotation(rot);
}


