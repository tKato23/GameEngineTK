//	�w�b�_�t�@�C���̃C���N���[�h
#include "Player.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

//	����������
void Player::Initialize()
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

	//	�ϐ��̏�����
	m_height = 0.0f;

	//	�e�ۗp�t���O
	m_FireFlag = false;
}


//	�X�V����
void Player::PlayerUpdate(DirectX::Keyboard::State key, DirectX::Keyboard::KeyboardStateTracker tracker)
{
	//	�p�[�c�M�~�b�N
	{

		//float angle = m_Obj[PARTS_ARM].GetRotation().z;
		//m_Obj[PARTS_ARM].SetRotation(Vector3(0, 0, angle + 0.03f));

		float pos = m_Obj[PARTS_ARM].GetPosition().z;
		m_Obj[PARTS_ARM].SetPosition(Vector3(0.5f, 0.3f, pos - 0.5f));

		m_Obj[PARTS_FOOT].SetPosition(
			Vector3(m_Obj[PARTS_FOOT].GetPosition().x,
				m_height,
				m_Obj[PARTS_FOOT].GetPosition().z));
	}

	//	�@�̂ɏd�͂�������
	m_height -= 0.05f;

	//	�n�ʂ��ђʂ��Ȃ��悤�ɂ���
	if (m_height <= 0)
	{
		m_height = 0;
	}

	//	�����񏈗�
	if (key.A)
	{
		//	���@�̊p�x����]
		//head_rot += 0.03f;
		float angle = m_Obj[0].GetRotation().y;
		m_Obj[0].SetRotation(Vector3(0, angle + 0.03f, 0));
	}

	//	�����񏈗�
	if (key.D)
	{
		//	���@�̊p�x����]
		//head_rot += -0.03f;
		float angle = m_Obj[0].GetRotation().y;
		m_Obj[0].SetRotation(Vector3(0, angle - 0.03f, 0));
	}

	//	�O�i����
	if (key.W)
	{
		//	�ړ��x�N�g��
		Vector3 moveV(0.0f, 0.0f, -0.1f);

		Matrix world;

		//	�ړ��x�N�g�������@�̊p�x����]������
		moveV = Vector3::TransformNormal(moveV, world);

		float angle = m_Obj[0].GetRotation().y;

		Matrix rotmat = Matrix::CreateRotationY(angle);
		moveV = Vector3::TransformNormal(moveV, rotmat);

		//	���@�̍��W���ړ�
		Vector3 pos = m_Obj[0].GetPosition();
		//head_pos += moveV;
		m_Obj[0].SetPosition(pos + moveV);

		//	�@�̂�O�X������
		m_Obj[PARTS_FOOT].SetRotation(Vector3(
			-0.4f,
			m_Obj[PARTS_FOOT].GetRotation().y,
			m_Obj[PARTS_FOOT].GetRotation().z)
		);
	}
	//	�O�X�p����߂�
	else
	{
		//	
		m_Obj[PARTS_FOOT].SetRotation(
			Vector3(0.0f,
				m_Obj[PARTS_FOOT].GetRotation().y,
				m_Obj[PARTS_FOOT].GetRotation().z)
		);
	}


	//	��ޏ���
	if (key.S)
	{
		//	�ړ��x�N�g��
		Vector3 moveV(0.0f, 0.0f, 0.1f);

		Matrix world;

		//	�ړ��x�N�g�������@�̊p�x����]������
		moveV = Vector3::TransformNormal(moveV, world );

		float angle = m_Obj[0].GetRotation().y;

		Matrix rotmat = Matrix::CreateRotationY(angle);
		moveV = Vector3::TransformNormal(moveV, rotmat);

		//	���@�̍��W���ړ�
		Vector3 pos = m_Obj[0].GetPosition();
		//head_pos += moveV;
		m_Obj[0].SetPosition(pos + moveV);
	}

	//	F�L�[�������ꂽ��r�����
	if (key.F)
	{
		float pos = m_Obj[PARTS_ARM].GetPosition().z;
		m_Obj[PARTS_ARM].SetPosition(Vector3(0.5f, 0.3f, pos - 0.5f));
	}
	else
	{
		m_Obj[PARTS_ARM].SetPosition(Vector3(0.5f, 0.3f, -0.4f));
	}

	//	�X�y�[�X�L�[�������ꂽ��㏸�������s��
	//if (key.Space)
	//{
	//	m_height += 0.3f;

	//	float pos = m_Obj[PARTS_FOOT].GetPosition().z;
	//	m_Obj[PARTS_FOOT].SetPosition(
	//		Vector3(m_Obj[PARTS_FOOT].GetPosition().x,
	//			m_height,
	//			m_Obj[PARTS_FOOT].GetPosition().z));

	//	//	���̍����𒴂��Ȃ��悤�ɂ���
	//	if (m_Obj[PARTS_FOOT].GetPosition().y >= 20.0f)
	//	{
	//		m_height = 20.0f;
	//	}
	//}

	//	���剻(Enter�L�[)
	if (tracker.IsKeyPressed(Keyboard::Keys::Enter))
	{
		if (m_Obj[1].GetScale() == Vector3(2.0f, 2.0f, 2.0f))
		{
			for (int i = 0; i < PARTS_NUM; i++)
			{
				m_Obj[i].SetScale(Vector3(1.0f, 1.0f, 1.0f));

			}
		}
		else
		{
			for (int i = 0; i < PARTS_NUM; i++)
			{
				m_Obj[i].SetScale(Vector3(2.0f, 2.0f, 2.0f));
			}
		}
	}

	if (m_FireFlag)
	{
		//	�e�ۃp�[�c�̑O�i����
		{
			//	�e�ۃp�[�c�̍��W���ړ�
			Vector3 pos = m_Obj[PARTS_GUN].GetPosition();
			m_Obj[PARTS_GUN].SetPosition(pos + m_BulletVel);
		}
	}

	if (tracker.IsKeyPressed(Keyboard::Keys::Space))
	{
		if (!m_FireFlag)
		{
			FireBullet();
		}
		else
		{
			ResetBullet();
		}
	}

	for (std::vector<Obj3d>::iterator it = m_Obj.begin(); it != m_Obj.end(); it++)
	{
		it->Update();
	}
}

//	�`�揈��
void Player::PlayerDraw()
{
	for (std::vector<Obj3d>::iterator it = m_Obj.begin(); it != m_Obj.end(); it++)
	{
		it->Draw();
	}
}

void Player::FireBullet()
{
	if (!m_FireFlag)
	{
		//	���˂���p�[�c�̃��[���h�s����擾
		Matrix worldm = m_Obj[PARTS_GUN].GetWorld();

		//	���o�����������܂��Ă����ϐ�
		Vector3 scale;			//	���[���h�X�P�[�����O
		Quaternion rotation;	//	���[���h��]
		Vector3 translation;	//	���[���h���W

		//	���[���h�s�񂩂�e�v�f�𒊏o
		worldm.Decompose(scale, rotation, translation);

		//	�e�p�[�c���番���A�Ɨ�������
		m_Obj[PARTS_GUN].SetObjParent(nullptr);
		m_Obj[PARTS_GUN].SetScale(scale);
		m_Obj[PARTS_GUN].SetRotationQ(rotation);
		m_Obj[PARTS_GUN].SetPosition(translation);

		//	�e�ۃp�[�c�̑��x��ݒ�
		m_BulletVel = Vector3(0, 0, -0.1f);
		//	�p�[�c�̌����ɍ��킹�đ��x�x�N�g������]
		m_BulletVel = Vector3::Transform(m_BulletVel, rotation);

		m_FireFlag = true;
	}
}

void Player::ResetBullet()
{
	if (m_FireFlag)
	{
		m_Obj[PARTS_GUN].SetObjParent(&m_Obj[PARTS_ARM]);

		m_Obj[PARTS_GUN].SetScale(Vector3(1, 1, 1));
		m_Obj[PARTS_GUN].SetRotation(Vector3(0, 0, 0));
		m_Obj[PARTS_GUN].SetPosition(Vector3(0, 0.0f, -0.2));

		m_FireFlag = false;
	}
}

//	�v���C���[�̍��W���擾
DirectX::SimpleMath::Vector3 Player::getPlayerPos()
{
	return m_Obj[PARTS_FOOT].GetPosition();
}

//	�v���C���[�̉�]�p���擾
DirectX::SimpleMath::Vector3 Player::getPlayerRot()
{
	return m_Obj[PARTS_FOOT].GetRotation();
}


