#include "stdafx.h"
#include "GameCamera.h"
#include "Goal.h"

GameCamera::GameCamera()
{
}


GameCamera::~GameCamera()
{
}

bool GameCamera::Start()
{
	m_player = FindGO<Player>("Player");
	m_goal = FindGO<Goal>("Goal");
	//�J�����̃j�A�N���b�v�ƃt�@�[�N���b�v��ݒ肷��B
	MainCamera().SetTarget({ 0.0f,-5.0f, -5.0f });
	MainCamera().SetNear(1.0f);
	MainCamera().SetFar(1000.0f);
	MainCamera().SetPosition({ 0.0f,-5.0f, -25.0f });
	
	//�΂˃J�����̏������B
	m_springCamera.Init(
		MainCamera(),		//�΂˃J�����̏������s���J�������w�肷��B
		500.0f,			//�J�����̈ړ����x�̍ő�l�B
		false,				//�J�����ƒn�`�Ƃ̂����蔻�����邩�ǂ����̃t���O�Btrue���Ƃ����蔻����s���B
		5.0f				//�J�����ɐݒ肳��鋅�̃R���W�����̔��a�B��R������true�̎��ɗL���ɂȂ�B
	);
	return true;
}
void GameCamera::Update()
{
	if (m_goal->gflag != 1) {							//�S�[�����Ă��Ȃ��Ȃ�
		m_player = FindGO<Player>("Player");
		CVector3 toCameraPos = CVector3::Zero;
		toCameraPos = m_springCamera.GetPosition() - m_springCamera.GetTarget();
		float height = toCameraPos.y;
		toCameraPos.y = 0.0f;
		float toCameraPosLen = toCameraPos.Length();
		toCameraPos.Normalize();
		CVector3 target = m_player->m_position;
		target.y += 10.0f;
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
	}
	if (m_goal->gflag == 1) {					//�S�[���p�J����
		CVector3 target;
		target.x = m_player->m_rot.m[2][0] * 10.0f + m_player->m_position.x;
		//m_player->m_rot.m[2][1];
		target.z = m_player->m_rot.m[2][2] * 10.0f + m_player->m_position.z;
		target.y = 10.0f;
		CVector3 toCameraPos;
		toCameraPos = m_springCamera.GetPosition() - m_springCamera.GetTarget();
		toCameraPos.y = 0.0f;
		float toCameraPoslen;
		toCameraPoslen = toCameraPos.Length();
		CVector3 playerposX;
		playerposX.Cross(CVector3::AxisY, m_player->m_position);
		playerposX.Normalize();
		playerposX.x *= -toCameraPoslen;
		playerposX.z *= -toCameraPoslen;
		CVector3 pos;
		pos = target + playerposX;
		m_springCamera.SetTarget(target);
		m_springCamera.SetPosition(pos);
	}
	////�o�l�J�����̍X�V�B
	m_springCamera.Update();
}