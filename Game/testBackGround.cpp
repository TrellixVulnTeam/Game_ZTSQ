#include "stdafx.h"
#include "testBackGround.h"
#include "Mirror.h"

testBackGround::testBackGround()
{
}


testBackGround::~testBackGround()
{
}
void testBackGround::OnDestroy()
{
	//�������[���h����폜
	PhysicsWorld().RemoveRigidBody(m_rigidBody);
}
bool testBackGround::Start()
{
	m_skinModelData.Load(L"modelData/testGround.cmo");
	m_skinModel.Init(m_skinModelData);
	m_skinModel.SetShadowReceiverFlag(true);
	//���b�V���R���C�_�[���쐬
	m_meshCollider.CreateFromSkinModel(m_skinModel, nullptr);
	//���̂̏��
	RigidBodyInfo rbInfo;
	rbInfo.pos = CVector3::Zero;
	rbInfo.rot = CQuaternion::Identity;
	rbInfo.collider = &m_meshCollider;
	rbInfo.mass = 0.0f;

	m_rigidBody.Create(rbInfo);
	PhysicsWorld().AddRigidBody(m_rigidBody);
	return true;
}
void testBackGround::Update()
{
	m_skinModel.Update(m_position, CQuaternion::Identity,m_scale);
}
void testBackGround::Render(CRenderContext& rc)
{
	if (m_mirror == NULL) {
		m_mirror = FindGO<Mirror>("Mirror");
	}
	m_mirror->alphaflag = 1;
	m_skinModel.Draw(
		rc, 
		MainCamera().GetViewMatrix(), 
		MainCamera().GetProjectionMatrix(),
		CMatrix::Identity,
		CMatrix::Identity,
		m_mirror->alphaflag);
}