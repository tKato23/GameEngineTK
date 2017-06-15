//	���d�C���N���[�h�̖h�~
#pragma once

//	�w�b�_�t�@�C���̃C���N���[�h
#include <d3d11_1.h>
#include <SimpleMath.h>
#include <Keyboard.h>
#include <vector>
#include "Obj3d.h"

//	�v���C���[�N���X
class Player :public Obj3d
{
private:
	//	���@�p�[�c
	enum PARTS
	{
		PARTS_FOOT,		//	��
		PARTS_BODY,		//	��
		PARTS_HEAD,		//	��
		PARTS_ARM,		//	�r
		PARTS_GUN,		//	�e

		PARTS_NUM
	};

	//	�v���C���[�̃p�[�c
	std::vector<Obj3d> m_Obj;

	//	���@�̃��[���h�s��
	DirectX::SimpleMath::Matrix head_world;

	//	�d�͂������邽�߂̃����o�ϐ�
	float m_height;

	//	�e�ۂ̑��x�x�N�g��
	DirectX::SimpleMath::Vector3 m_BulletVel;

	bool m_FireFlag;

public:

	void Initialize();									//	����������

	void PlayerUpdate(DirectX::Keyboard::State key, DirectX::Keyboard::KeyboardStateTracker tracker);	//	�X�V����
	void PlayerDraw();									//	�`�揈��

	//	�e�ۂ𔭎�
	void FireBullet();
	//	�e�ۂ��đ���(���Z�b�g�j
	void ResetBullet();

	DirectX::SimpleMath::Vector3 getPlayerPos();		//	�v���C���[�̍��W���擾
	DirectX::SimpleMath::Vector3 getPlayerRot();		//	�v���C���[�̉�]�p���擾


};

