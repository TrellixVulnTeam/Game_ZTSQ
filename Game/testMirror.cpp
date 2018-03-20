#include "stdafx.h"
#include "testMirror.h"


testMirror::testMirror()
{
}


testMirror::~testMirror()
{
}
bool testMirror::Start()
{
	m_skinModelData.Load(L"modelData/unityChan.cmo");
	m_skinModel.Init(m_skinModelData);
	//�L�����N�^�[�R���g���[���[�̏�����
	m_charaCon.Init(
		3.0f,
		7.0f,
		m_position
	);
	/*m_target = { 0.0f,0.0f,5.0f };
	CVector3 toPos;
	toPos = m_target - m_position;
	toPosLen = toPos.Length();*/
	return true;
}
void testMirror::Update()
{
	m_moveSpeed.y += -20.0f;
	float lStick_x = Pad(0).GetLStickXF();
	float lStick_y = Pad(0).GetLStickYF();
	//�J�����̑O�����ƉE�������擾
	CVector3 cameraForward = MainCamera().GetForward();
	CVector3 cameraRight = MainCamera().GetRight();
	cameraForward.y = 0.0f;
	cameraForward.Normalize();
	cameraRight.y = 0.0f;
	cameraRight.Normalize();
	m_moveSpeed.x = 0.0f;
	m_moveSpeed.z = 0.0f;
	m_moveSpeed += cameraForward * lStick_y * 50.0f;
	m_moveSpeed += cameraRight * lStick_x * 50.0f;
	//�L�����N�^�[��C�ӂ̕����Ɍ������邽�߂̕ϐ�
	float angle = 0;
	angle = atan2f(m_moveSpeed.x, m_moveSpeed.z);
	if (!(lStick_x == 0 && lStick_y == 0)) {
		m_rotation.SetRotation(CVector3::AxisY, angle);
	}
	
	m_position = m_charaCon.Execute(GameTime().GetFrameDeltaTime(), m_moveSpeed);
	
	
	m_skinModel.Update(m_position, m_rotation, m_scale);
}
CMatrix g_mirrorViewMatrix;
CMatrix g_mirrorProjectionMatrix;
void testMirror::Render(CRenderContext& rc)
{
	CMatrix axis = CMatrix::Identity;									//�v���C���[�̔C�ӂ̎�����̉�]�s����쐬
	axis.MakeRotationFromQuaternion(m_rotation);

	m_target.x = m_position.x + axis.m[2][0] * 10.0f;		//�v���C���[�̒����_��ݒ�
	m_target.y = m_position.y + axis.m[2][1] * 10.0f;
	m_target.z = m_position.z + axis.m[2][2] * 10.0f;

	CVector3 cameraPos = m_position;
	cameraPos.x += axis.m[2][0] * 2.0f;
	cameraPos.y += 50.0f;
	cameraPos.z += axis.m[2][2] * 2.0f;

	m_mirrorViewMatrix.MakeLookAt(m_position, m_target, { 0.0f,1.0f,0.0f });
	m_mirrorProjectionMatrix.MakeProjectionMatrix(CMath::PI * 0.3f, 1.0f, 0.1f, 10000.0f);
	g_mirrorViewMatrix = m_mirrorViewMatrix;
	g_mirrorProjectionMatrix = m_mirrorProjectionMatrix;
	m_skinModel.Draw(rc, MainCamera().GetViewMatrix(), MainCamera().GetProjectionMatrix(),m_mirrorViewMatrix,m_mirrorProjectionMatrix);
}