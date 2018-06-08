#include "stdafx.h"
#include "testGameCamera.h"


testGameCamera::testGameCamera()
{
}


testGameCamera::~testGameCamera()
{
}
bool testGameCamera::Start()
{
	m_toCameraPos.Set(0.0f, 15.0f, 50.0f);
	/*m_springCamera.SetPosition({ 0.0f,15.0f,50.0f });
	m_springCamera.SetTarget({ 0.0f,15.0f,0.0f });*/
	//�~���[�̃C���X�^���X��T��
	m_mirror = FindGO<Mirror>("Mirror");
	//springCamera.SetTarget(m_mirror->m_position);
	MainCamera().SetNear(1.0f);
	MainCamera().SetFar(1000.0f);
	MainCamera().SetPosition({ 0.0f, 25.0f, 70.0f });
	MainCamera().SetTarget({ 0.0f,15.0f,0.0f });
	//�΂˃J�����̏�����
	m_springCamera.Init(
		MainCamera(),
		1000.0f,
		true,
		5.0f
	);
	return true;
};
void testGameCamera::Update()
{
	
	CVector3 toCameraPos = CVector3::Zero;
	toCameraPos = m_springCamera.GetPosition() - m_springCamera.GetTarget();
	float height = toCameraPos.y;
	toCameraPos.y = 0.0f;
	float toCameraPosLen = toCameraPos.Length();
	toCameraPos.Normalize();
	CVector3 target = m_mirror->GetPosition();
	target.y += 15.0f;
	CVector3 toNewCameraPos = CVector3::Zero;
	toNewCameraPos = m_springCamera.GetPosition() - target;
	toNewCameraPos.y = 0.0f;
	float toNewCameraPosLen = toNewCameraPos.Length();
	toNewCameraPos.Normalize();

	//������Ƃ��ǔ�
	float weight = 0.8f;
	toNewCameraPos = toNewCameraPos * weight + toCameraPos * (1.0f - weight);
	toNewCameraPos.Normalize();
	toNewCameraPos.x *= toCameraPosLen;
	toNewCameraPos.y *= toCameraPosLen;
	toNewCameraPos.z *= toCameraPosLen;
	toNewCameraPos.y = height;
	CVector3 pos = target + toNewCameraPos;
	m_springCamera.SetTarget(target);
	m_springCamera.SetPosition(pos);
	CVector3 toCameraPosOld = toNewCameraPos;
	//�p�b�h�̓��͂��g���ăJ��������
	float x = Pad(0).GetRStickXF();
	float y = Pad(0).GetRStickYF();
	//Y������̉�]
	CQuaternion qRot;
	qRot.SetRotationDeg(CVector3::AxisY, 2.0f*x);
	qRot.Multiply(toNewCameraPos);
	//x������̉�]
	CVector3 axisX;
	axisX.Cross(CVector3::AxisY, toNewCameraPos);
	axisX.Normalize();
	//�C�ӂ̎��ɉ�]������
	qRot.SetRotationDeg(axisX, 2.0f*y);
	qRot.Multiply(toNewCameraPos);
	//�J�����̉�]�̏����ݒ�
	CVector3 toPosDir = toNewCameraPos;
	toPosDir.Normalize();
	if (toPosDir.y < -0.5f) {
		//�J�����̏�𐧌�
		toNewCameraPos = toCameraPosOld;
	}
	else if (toPosDir.y > 0.8f) {
		//�J�����̉��𐧌�
		toNewCameraPos = toCameraPosOld;
	}
	pos = CVector3::Zero;
	//���_���v�Z����
	if (!(x == 0 && y == 0)) {
		pos = target + toNewCameraPos;
		m_springCamera.SetTarget(target);
		m_springCamera.SetPosition(pos);
	}

	m_springCamera.Update();
}