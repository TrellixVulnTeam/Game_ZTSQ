#include "stdafx.h"
#include "Mirror.h"


Mirror::Mirror()
{
}

Mirror::~Mirror()
{
}
bool Mirror::Start()
{
	m_skinModelData.Load(L"modelData/mirror.cmo");
	m_skinModel.Init(m_skinModelData);

	return true;
}
void Mirror::Update()
{
	//�N�H�[�^�j�I����������
	CQuaternion qRot = CQuaternion::Identity;
	
	//��]����
	CVector3 stick;
	stick.x = -Pad(0).GetRStickXF();
	stick.y = Pad(0).GetRStickYF();
	stick.z = 0.0f;
	stick = stick * 10;

	//���
	if (m_anglex >50.0f)
	{
		m_anglex = 50.0f;
	}
	if (m_anglex < -50.0f)
	{
		m_anglex = -50.0f;
	}
	if (m_angley >50.0f)
	{
		m_angley = 50.0f;
	}
	if (m_angley < -50.0f)
	{
		m_angley = -50.0f;
	}
	m_anglex += stick.x;
	
	//���Z
	if (m_anglex <= 50 && m_anglex >= -50) {
		qRot.SetRotationDeg(CVector3::AxisY, stick.x);
		
		m_rotation.Multiply(qRot);
	}
	m_angley += stick.y;
	if (m_angley <= 50 && m_angley >= -50) {
		qRot.SetRotationDeg(CVector3::AxisX, stick.y);
	
		m_rotation.Multiply(qRot);
	}

	//���[���h�s��X�V
	m_skinModel.Update(m_position, m_rotation, CVector3::One);
}
void Mirror::Render(CRenderContext& rc)
{
	m_skinModel.Draw(rc, MainCamera().GetViewMatrix(), MainCamera().GetProjectionMatrix());
}