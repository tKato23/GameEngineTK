/// <summary>
/// 3D�I�u�W�F�N�g�̃N���X
/// </summary>

#pragma once

//	�w�b�_�t�@�C���̃C���N���[�h
#include <windows.h>
#include <wrl/client.h>
#include <d3d11_1.h>
#include <Effects.h>
#include <CommonStates.h>
#include <SimpleMath.h>
#include <Model.h>

#include "Camera.h"

#include <map>

class Obj3d
{
public:
	//	�ÓI�����o�֐�
	static void InitializeStatic(
		Microsoft::WRL::ComPtr<ID3D11Device>            d3dDevice,
		Microsoft::WRL::ComPtr<ID3D11DeviceContext>     d3dContext,
		Camera* camera);

private:
	//	�ÓI�����o�ϐ�

	//	�f�o�C�X
	static Microsoft::WRL::ComPtr<ID3D11Device>            m_d3dDevice;

	//	�f�o�C�X�R���e�L�X�g
	static Microsoft::WRL::ComPtr<ID3D11DeviceContext>     m_d3dContext;

	//	�J����
	static Camera* m_Camera;

	//	�ėp�X�e�[�g�ݒ�
	static std::unique_ptr<DirectX::CommonStates> m_states;

	//	�G�t�F�N�g�t�@�N�g��
	static std::unique_ptr<DirectX::EffectFactory> m_factory;


	// �ǂݍ��ݍς݃��f���R���e�i
	static std::map<std::wstring, std::unique_ptr<DirectX::Model>> s_modelarray;

public:
	//	�R���X�g���N�^
	Obj3d();

	//	�X�V
	void Update();
	//	�`��
	void Draw();

	// �t�@�C�����烂�f����ǂݍ���
	void LoadModelFile(const wchar_t*filename = nullptr);

	//	setter

	//	�X�P�[�����O(XYZ)
	void SetScale(const DirectX::SimpleMath::Vector3& scale) { m_scale = scale; }
	//	��]�p(XYZ)
	void SetRotation(const DirectX::SimpleMath::Vector3& rot) { m_rotation = rot; m_UseQuaternion = false; }
	//	��]�p(�N�H�[�^�j�I��)
	void SetRotationQ(const DirectX::SimpleMath::Quaternion& rot) { m_rotationQ = rot; m_UseQuaternion = true; }
	//	���s�ړ�(XYZ)
	void SetPosition(const DirectX::SimpleMath::Vector3& pos) { m_translation = pos; }
	//	�e��3D�I�u�W�F�N�g
	void SetObjParent(Obj3d* ObjParent) { m_ObjParent = ObjParent; }

	//	getter
	//	�X�P�[�����O(XYZ)
	const DirectX::SimpleMath::Vector3& GetScale() { return m_scale; }
	//	��]�p(XYZ)
	const DirectX::SimpleMath::Vector3& GetRotation() { return m_rotation; }
	//	���s�ړ�(XYZ)
	const DirectX::SimpleMath::Vector3& GetPosition() { return m_translation; }

	//	���[���h�s��
	const DirectX::SimpleMath::Matrix& GetWorld() { return m_world; }

private:
	//	�����o�ϐ�

	// ���f���f�[�^�ւ̃|�C���^
	const DirectX::Model* m_pModel;
	//	�X�P�[�����O(XYZ)
	DirectX::SimpleMath::Vector3 m_scale;
	//	��]�p(XYZ�I�C���[�p)
	DirectX::SimpleMath::Vector3 m_rotation;

	//	��]�p(�N�H�[�^�j�I���j
	DirectX::SimpleMath::Quaternion m_rotationQ;

	//	���s�ړ�(XYZ)
	DirectX::SimpleMath::Vector3 m_translation;
	//	���[���h�s��
	DirectX::SimpleMath::Matrix m_world;
	//	�e��Obj3D�ւ̃|�C���^
	Obj3d* m_ObjParent;
	//	��]���N�H�[�^�j�I���ň����t���O
	bool m_UseQuaternion;
};
