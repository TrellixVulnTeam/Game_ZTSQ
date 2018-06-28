#include "stdafx.h"
#include "GameCamera.h"
#include "Goal.h"
#include "ResultScene.h"

GameCamera::GameCamera()
{
}


GameCamera::~GameCamera()
{
}

bool GameCamera::Start()
{
	testScene = FindGO<ResultScene>("Result");
	m_player = FindGO<Player>("Player");
	m_goal = FindGO<Goal>("Goal");
	//�J�����̃j�A�N���b�v�ƃt�@�[�N���b�v��ݒ肷��B
	MainCamera().SetTarget(m_player->GetPosition()/*{ 0.0f,-5.0f, -5.0f }*/);
	MainCamera().SetNear(1.0f);
	MainCamera().SetFar(1000.0f);
	CVector3 CamPos=CVector3::Zero;
	CamPos=m_player->GetPosition();
	CamPos.z -= 25.0f;
	//�J�����̃|�W�V����
	MainCamera().SetPosition(CamPos/*{ 0.0f,-5.0f, -25.0f }*/);
	
	//�΂˃J�����̏������B
	m_springCamera.Init(
		MainCamera(),		//�΂˃J�����̏������s���J�������w�肷��B
		500.0f,			//�J�����̈ړ����x�̍ő�l�B
		true,				//�J�����ƒn�`�Ƃ̂����蔻�����邩�ǂ����̃t���O�Btrue���Ƃ����蔻����s���B
		1.0f				//�J�����ɐݒ肳��鋅�̃R���W�����̔��a�B��R������true�̎��ɗL���ɂȂ�B
	);
	MainCamera().SetUpdateProjMatrixFunc(CCamera::enUpdateProjMatrixFunc_Perspective);
	return true;
}
void GameCamera::Update()
{
	if (m_goal->GetGoalFlag() == 0 && testScene->GetResultFlag() == false/*&& m_player->PressFlag == 0*/) {							//�S�[�����Ă��Ȃ��Ȃ�
		//m_player = FindGO<Player>("Player");
		CVector3 toCameraPos = CVector3::Zero;
		toCameraPos = m_springCamera.GetPosition() - m_springCamera.GetTarget();
		float height = toCameraPos.y;
		toCameraPos.y = 0.0f;
		float toCameraPosLen = toCameraPos.Length();
		toCameraPos.Normalize();
		CVector3 target = m_player->GetPosition();
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

		m_rot.MakeRotationFromQuaternion(qRot);

		//���_���v�Z����
		if (!(x == 0 && y == 0)) {
			pos = target + toNewCameraPos;
			m_springCamera.SetTarget(target);
			m_springCamera.SetPosition(pos);
		}
	}
	if (m_goal->GetGoalFlag()==1 ) {					//�S�[���p�J����
	//if(testScene->GetResultFlag() == true){
	//�΂˃J�����̏������B
		if (ClearCameraFlag == false) {
			m_springCamera.Init(
				MainCamera(),		//�΂˃J�����̏������s���J�������w�肷��B
				500.0f,			//�J�����̈ړ����x�̍ő�l�B
				false,				//�J�����ƒn�`�Ƃ̂����蔻�����邩�ǂ����̃t���O�Btrue���Ƃ����蔻����s���B
				0.0f				//�J�����ɐݒ肳��鋅�̃R���W�����̔��a�B��R������true�̎��ɗL���ɂȂ�B
			);
			ClearCameraFlag = true;
		}
		m_player->Result();

		float toPoslen = 2.5f; //�^�[�Q�b�g�̏ꏊ�����߂邽�߂̒���
		CVector3 ForwordPos = CVector3::Zero;
		ForwordPos.x = m_player->GetMatrix().m[2][0]/* + m_player->GetPosition().x*/;
		ForwordPos.y = 0.0f;
		ForwordPos.z = m_player->GetMatrix().m[2][2]/* + m_player->GetPosition().z*/;
		CVector3 target = CVector3::Zero;
		target.Cross(CVector3::Up,ForwordPos);
		target.x = -target.x;
		target.y = -target.y;
		target.z = -target.z;
		target.Normalize();
		target.x *= toPoslen;
		target.y = 0.0f;
		target.z *= toPoslen;

		float toCameraPoslen = 9.5f;//�J�����̈ʒu�����߂邽�߂̒���
		//ForwordPos.Normalize();
		ForwordPos.x *= toCameraPoslen;
		ForwordPos.y = 4.0f;
		ForwordPos.z *= toCameraPoslen;
		CVector3 pos = CVector3::Zero;
		pos = target + ForwordPos + m_player->GetPosition();
		target.y = 3.0f;
		target.x = target.x+m_player->GetPosition().x;
		target.z = target.z+m_player->GetPosition().z;

		m_springCamera.SetTarget(target);
		m_springCamera.SetPosition(pos);
		m_springCamera.SetDampingRate(2.0f);
		//m_springCamera.SetFar(20.0f);
		m_springCamera.SetViewAngle(CMath::DegToRad(40.0f));
	}

	if (m_player->GetPressFlag() == 1 && testScene->GetResultFlag() == false)
	{
		if (Flag == 0) {
			CVector3 target = m_player->GetPosition();
			m_springCamera.SetTarget(target);
			CQuaternion qRot;
			qRot.SetRotationDeg(CVector3::AxisY, 150.0f);
			CVector3 toPos = m_springCamera.GetPosition() - m_springCamera.GetTarget();
			toPos.y = 0.0f;
			toPos.Normalize();
			qRot.Multiply(toPos);

			toPos *= 20.0f;
			CVector3 pos = target + toPos;
			pos.y = 20.0f;
			m_springCamera.SetPosition(pos);
			Flag = 1;
		}
		if (//m_springCamera.GetMoveSpeed().x <= 0.2
			/*&&*/ m_springCamera.GetMoveSpeed().y <= 0.2
			/*&& m_springCamera.GetMoveSpeed().z <= 0.2*/)
		{
			Flag = 2;
		}
	}
	//�o�l�J�����̍X�V�B
	m_springCamera.Update();
}