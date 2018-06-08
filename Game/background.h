#pragma once

//CMeshCollider��CRigidBody���g�p�������ꍇ�͉��L�̃w�b�_�[�t�@�C�����C���N���[�h����K�v������B
#include "tkEngine/physics/tkMeshCollider.h"
#include "tkEngine/physics/tkRigidBody.h"

class background : public IGameObject
{
public:
	/////////////////////////////////////////////////////
	// �����o�֐��ȂǁB
	/////////////////////////////////////////////////////
	background();
	~background();
	void Update();
	void Render(CRenderContext& rc);
	bool Start();
	void OnDestroy();
private:
	/////////////////////////////////////////////////////
	// �����o�ϐ��ȂǁB
	/////////////////////////////////////////////////////
	CSkinModelData m_skinModelData;	//�X�L�����f���f�[�^�B
	CSkinModel m_skinModel;			//�X�L�����f���B
	CSkinModelData m_skinModelData1;	//�S�[���ǃX�L�����f���f�[�^�B
	CSkinModel m_skinModel1;			//�S�[���ǃX�L�����f���B
	CVector3 m_position = CVector3::Zero;	//���W�B
	CMeshCollider m_meshCollider;	//���b�V���R���C�_�[�B
	CRigidBody m_rigidBody;			//���́B
	Mirror* m_mirror = NULL;
};

