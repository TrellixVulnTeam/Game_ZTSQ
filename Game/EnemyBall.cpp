#include "stdafx.h"
#include "EnemyBall.h"
#include "Player.h"
#include "Goal.h"
#include"Mirror.h"

EnemyBall::EnemyBall()
{
}
EnemyBall::~EnemyBall()
{
}
bool EnemyBall::Start() 
{
	m_player = FindGO<Player>("Player");
	m_goal = FindGO<Goal>("Goal");
	m_skinModelData.Load(L"modelData/EnemyBall.cmo");
	m_skinModel.Init(m_skinModelData);
	//CapsuleType type

	m_charaCon.Init(
		r,			//���a
		0.0f,			//����
		-220,			//�d��
		m_position,
		m_collidertype	//�R���C�_�[�̃^�C�v
	);
	diff = m_player->m_position - m_position;
	return true;
}
void EnemyBall::Update()
{
	CVector3 scale = CVector3::One;
	//CVector3 scale = { 0.15f,0.15f,0.15f };
	if (m_charaCon.IsHitWall() == true) {
		diff = m_player->m_position - m_position;
	}
	diff.y = 0.0f;							//Y���͕K�v�Ȃ��̂�
	//if (diff.Length() > 10.0f) {						//��������苗���ȓ��Ȃ�ǂ�������
		diff.Normalize();
	//�v���C���[�̈ړ����x�����肵���璲������----------------------------------
		m_moveSpeed.x = diff.x * 20.0f;				
		m_moveSpeed.z = diff.z * 20.0f;
	//--------------------------------------------------------------------------	
		m_axisX.Cross(diff, up);
		m_axisX.Normalize();
		CQuaternion qRot;
		qRot.SetRotationDeg(m_axisX,-(CMath::PI * (r * 2.0f)/m_moveSpeed.Length()));
		m_rotation.Multiply(qRot);
	//}
	/*if (diff.Length() <= 10.0f) {
		m_moveSpeed.x = OldDiff.x * 20.0f;
		m_moveSpeed.z = OldDiff.z * 20.0f;
	}*/
	m_position = m_charaCon.Execute(GameTime().GetFrameDeltaTime(), m_moveSpeed,m_collidertype);
	m_skinModel.Update(m_position, m_rotation, scale);
}
void EnemyBall::Render(CRenderContext& rc)
{
	
	{
		if (m_mirror == NULL) {
			m_mirror = FindGO<Mirror>("Mirror");
		}
		if (m_mirror->m_isMirror == true) {						//�~���[���g�p���Ȃ�I�u�W�F�N�g�������t���O���O�ɂ���
			m_mirror->_alphaflag = 0;
		}
		else {
			m_mirror->_alphaflag = 1;
		}
		m_skinModel.SetDiscardMirror(m_mirror->_alphaflag);
		m_skinModel.Draw(rc,
			MainCamera().GetViewMatrix(),
			MainCamera().GetProjectionMatrix(),
			CMatrix::Identity,
			CMatrix::Identity
		);
	}
}
