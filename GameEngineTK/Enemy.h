//	���d�C���N���[�h�̖h�~
#pragma once

//	�w�b�_�t�@�C���̃C���N���[�h
#include <d3d11_1.h>
#include <SimpleMath.h>
#include <vector>
#include "Obj3d.h"

//	�G�N���X
class Enemy :public Obj3d
{
private:
	//	�G�p�[�c
	enum PARTS
	{
		PARTS_FOOT,		//	��
		PARTS_BODY,		//	��
		PARTS_HEAD,		//	��
		PARTS_ARM,		//	�r
		PARTS_GUN,		//	�e

		PARTS_NUM
	};

	//	�G�̃p�[�c
	std::vector<Obj3d> m_Obj;

	//	���@�̃��[���h�s��
	DirectX::SimpleMath::Matrix head_world;

	int m_Timer;										//	�^�C�}�[
	//	�ڕW�p�x
	float m_DistAngle;

public:
	Enemy();

	void Initialize();									//	����������

	void EnemyUpdate();									//	�X�V����
	void EnemyDraw();									//	�`�揈��

	DirectX::SimpleMath::Vector3 getEnemyPos();			//	�G�̍��W���擾
	DirectX::SimpleMath::Vector3 getEnemyRot();			//	�G�̉�]�p���擾

	void SetEnemyPosition(const DirectX::SimpleMath::Vector3& pos);	//	�G�̍��W��ݒ�
	void SetEnemyRotation(DirectX::SimpleMath::Vector3 rot);	//	�G�̍��W��ݒ�
};

