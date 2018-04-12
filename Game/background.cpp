#include "stdafx.h"
#include "background.h"
#include"Mirror.h"

background::background()
{
}


background::~background()
{
}

void background::OnDestroy()
{
	//�������[���h����폜�B
	PhysicsWorld().RemoveRigidBody(m_rigidBody);
}
bool background::Start()
{
	//���f�������[�h�B
	m_skinModelData.Load(L"modelData/protbackground2.cmo");
	m_skinModel.Init(m_skinModelData);
	//���b�V���R���C�_�[���쐬�B
	m_meshCollider.CreateFromSkinModel(m_skinModel, nullptr);
	//���̂̏����쐬�B
	RigidBodyInfo rbInfo;
	rbInfo.pos = CVector3::Zero;
	rbInfo.rot = CQuaternion::Identity;
	rbInfo.collider = &m_meshCollider;
	rbInfo.mass = 0.0f;							//���ʂ�0�ɂ���Ɠ����Ȃ����̂ɂȂ�B
												//�w�i�Ȃǂ̓����Ȃ��I�u�W�F�N�g��0��ݒ肷��Ƃ悢�B
	m_rigidBody.Create(rbInfo);					//�쐬���������g���č��̂��쐬����B
	PhysicsWorld().AddRigidBody(m_rigidBody);	//�쐬�������̂𕨗����[���h�ɒǉ�����B
	return true;
}
void background::Update()
{
	m_skinModel.Update(CVector3::Zero, CQuaternion::Identity, CVector3::One);
}
void background::Render(CRenderContext& rc)
{
	if (m_mirror == NULL) {
		m_mirror = FindGO<Mirror>("Mirror");
	}
	m_mirror->alphaflag = 1;
	m_skinModel.Draw(rc,
		MainCamera().GetViewMatrix(),
		MainCamera().GetProjectionMatrix(),
		CMatrix::Identity,
		CMatrix::Identity,
		m_mirror->alphaflag);
}
