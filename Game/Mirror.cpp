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
	//�X�e�B�b�N�̓���
	CVector3 rStick = CVector3::Zero;
	rStick.x = Pad(0).GetRStickXF();
	rStick.y = -Pad(0).GetRStickYF();
	rStick.z = 0.0f;
	rStick = rStick * 10.0f;

	//��]�̏��
	if (angleX > 50.0f)
	{
		angleX = 50.0f;
	}
	if (angleX < -50.0f)
	{
		angleX = -50.0f;
	}
	if (angleY > 50.0f)
	{
		angleY = 50.0f;
	}
	if (angleY < -50.0f)
	{
		angleY = -50.0f;
	}
	angleX += rStick.x;
	angleY += rStick.y;
	CQuaternion qRot = CQuaternion::Identity;
	if (angleX <= 50.0f && angleX >= -50.0f) {
		qRot.SetRotationDeg(CVector3::AxisY, rStick.x);
		m_rotation.Multiply(qRot);
	}
	if (angleY <= 50.0f && angleY >= -50.0f) {
		qRot.SetRotationDeg(CVector3::AxisX,rStick.y);
		m_rotation.Multiply(qRot);
	}

	//��]�s��̍쐬
	CMatrix forwardMatrix;
	forwardMatrix.MakeRotationFromQuaternion(qRot);

	//���̑O����
	CVector3 target=CVector3::Zero;
	target = { forwardMatrix.m[2][0],forwardMatrix.m[2][1] ,forwardMatrix.m[2][2] };
	
	//�J�����s��̍쐬
	CMatrix mirrorCamera;
	CVector3 up = { 0.0f,1.0f,0.0f };
	mirrorCamera.MakeLookAt(m_position, target, up);

	m_skinModel.Update(m_position, m_rotation, CVector3::One);
}
void Mirror::Render(CRenderContext& rc)
{
	m_skinModel.Draw(rc, MainCamera().GetViewMatrix(), MainCamera().GetProjectionMatrix(),CMatrix::Identity, CMatrix::Identity);
}