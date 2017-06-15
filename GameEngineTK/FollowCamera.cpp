//	�w�b�_�t�@�C���̃C���N���[�h
#include "FollowCamera.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

//	�ÓI�����o�ϐ��̏�����
const float FollowCamera::CAMERA_DISTANCE = 5.0f;

//	�R���X�g���N�^
FollowCamera::FollowCamera(int width, int height)
	:Camera(width, height)
{
	//	����������
	m_targetPos = Vector3::Zero;
	m_targetAngle = 0.0f;
	m_keyboard = nullptr;
	m_isFPS = false;
	m_player = nullptr;
}

//	�X�V
void FollowCamera::Update()
{
	//	�L�[�{�[�h�̏�ԊG��擾
	Keyboard::State keystate = m_keyboard->GetState();
	m_keyboardTracker.Update(keystate);

	if (m_keyboardTracker.IsKeyPressed(Keyboard::Keyboard::C))
	{
		m_isFPS = !m_isFPS;
	}

	if (m_player)
	{
		SetTargetPos(m_player->getPlayerPos());
		SetTargetAngle(m_player->getPlayerRot().y);
	}

	//	�J�������_���W�A�Q�Ɠ_���W
	Vector3 eyepos, refpos;
	if(m_isFPS == true)
	{//	FPS�J�����̏���
		Vector3 position;
		//	�Q�Ɠ_���W���v�Z
		position = m_targetPos + Vector3(0, 0.2f, 0);
		//	���@����J�������W�ւ̍���
		Vector3 cameraV(0, 0, -CAMERA_DISTANCE);
		//	���@�̌��ɉ�荞�ނ��߂̉�]�s��
		Matrix rotmat = Matrix::CreateRotationY(m_targetAngle);
		//	�J�����ւ̃x�N�g������]
		cameraV = Vector3::TransformNormal(cameraV, rotmat);
		//	������Ɛi�񂾈ʒu�����_���W
		eyepos = position + cameraV * 0.1f;
		//	������i�񂾈ʒu���Q�Ɠ_���W
		refpos = position + cameraV;
	}
	else
	{//	TPS�J�����̏���
	 //	�Q�Ɠ_���W���v�Z
		refpos = m_targetPos + Vector3(0, 2, 0);
		//	���@����J�������W�ւ̍���
		Vector3 cameraV(0, 0, CAMERA_DISTANCE);
		//	���@�̌��ɉ�荞�ނ��߂̉�]�s��
		Matrix rotmat = Matrix::CreateRotationY(m_targetAngle);
		//	�J�����ւ̃x�N�g������]
		cameraV = Vector3::TransformNormal(cameraV, rotmat);
		//	�J�������W���v�Z
		eyepos = refpos + cameraV;


		//	���_�����݈ʒu�����Ԃ���
		eyepos = m_eyepos + (eyepos - m_eyepos) * 0.05f;
		//	�Q�Ɠ_�����݈ʒu�����Ԃ���
		refpos = m_refpos + (refpos - m_refpos) * 0.2f;

		this->SetEyePos(eyepos);
		this->SetRefPos(refpos);
	}

	//	FPS�J������؂��Ē�_�J�����ɐ؂�ւ�
	
	////	���_�����݈ʒu�����Ԃ���
	//eyepos = m_eyepos + (eyepos - m_eyepos) * 0.05f;
	////	�Q�Ɠ_�����݈ʒu�����Ԃ���
	//refpos = m_refpos + (refpos - m_refpos) * 0.2f;

	//this->SetEyePos(eyepos);
	//this->SetRefPos(refpos);

	//	���N���X�̍X�V
	Camera::Update();
}

void FollowCamera::SetTargetPos(const DirectX::SimpleMath::Vector3 & targetPos)
{
	m_targetPos = targetPos;
}

void FollowCamera::SetTargetAngle(float targetAngle)
{
	m_targetAngle = targetAngle;
}

//	�L�[�{�[�h���Z�b�g
void FollowCamera::SetKeyboard(DirectX::Keyboard * keyboard)
{
	m_keyboard = keyboard;
}


