#include "stdafx.h"
#include "MapChip.h"
#include "Mirror.h"
 #include "GameCamera.h"
#include"GameOverProd.h"
//#include "tkEngine/sound/tkSoundSource.h"

MapChip::MapChip()
{
}


MapChip::~MapChip()
{
}
void MapChip::OnDestroy() {
	//�������[���h����폜�B
	PhysicsWorld().RemoveRigidBody(m_rigidBody);
	DeleteGO(m_PressDead);
}
void MapChip::Init(
	const wchar_t* modelFilePath,
	CVector3 pos,
	CVector3 scale,
	CQuaternion rotation
) {
	m_skinModelData.Load(modelFilePath);
	m_skinModel.Init(m_skinModelData);
	m_skinModel.SetShadowReceiverFlag(true);
	m_position = pos;
	m_scale = scale;
	m_rotation = rotation;

	//���b�V���R���C�_�[���쐬�B
	m_meshCollider.CreateFromSkinModel(m_skinModel, nullptr);
	//���̂̏����쐬�B
	RigidBodyInfo rbInfo;
	rbInfo.pos = m_position;
	rbInfo.rot = m_rotation;
	rbInfo.collider = &m_meshCollider;
	rbInfo.mass = 0.0f;							//���ʂ�0�ɂ���Ɠ����Ȃ����̂ɂȂ�B
												//�w�i�Ȃǂ̓����Ȃ��I�u�W�F�N�g��0��ݒ肷��Ƃ悢�B
	m_rigidBody.Create(rbInfo);					//�쐬���������g���č��̂��쐬����B
	//m_rigidBody.GetBody()->setUserIndex(enCollisionAttr_Obstacle);
	PhysicsWorld().AddRigidBody(m_rigidBody);	//�쐬�������̂𕨗����[���h�ɒǉ�����B
	m_rigidBody.GetBody()->setUserIndex(enCollisionAttr_Wall);
}
bool MapChip::Start()
{
	m_player = FindGO<Player>("Player");
	m_camera = FindGO<GameCamera>("gamecamera");
	//�f�B�U�����O�̋��������߂�W��
	m_skinModel.SetDitheringCoefficient(1.0f);
	return true;
}
void MapChip::Update()
{
	if (m_overprod==nullptr)
	{
		if (m_player->GetProd() != NULL) {
			m_overprod = FindGO<GameOverProd>("Prod");
		}
	}
	if (m_mirror == NULL) {
		m_mirror = FindGO<Mirror>("Mirror");
	}
	if (m_mirror->GetIsMirror() == true) {						//�~���[���g�p���Ȃ�I�u�W�F�N�g�������t���O���O�ɂ���
		//m_mirror->_alphaflag = 0;
		m_skinModel.SetDiscardMirror(false);
	}
	else {
		//m_mirror->_alphaflag = 1;
		m_skinModel.SetDiscardMirror(true);
	}
	//m_skinModel.SetDiscardMirror(m_mirror->_alphaflag);
	CVector3 ditheringPos = CVector3::Zero;
	CVector3 Pos = m_camera->GetSpringCamera().GetPosition();
	CVector3 diff = m_player->GetPosition() - Pos;
	diff.Normalize();
	ditheringPos.x = Pos.x + diff.x * 20.0f;
	ditheringPos.y = Pos.y + diff.y * 20.0f;
	ditheringPos.z = Pos.z + diff.z * 20.0f;
	if (m_player->GetLifeCount() < 5) {
		//�f�B�U�����O���g�p���邽�߂̃t���O��n��
		m_skinModel.SetDithering(true);
		//�f�B�U�����O���g�p����Ƃ��̊�_�ƂȂ���W��n��
		m_skinModel.SetDitheringPos(ditheringPos);
	}
	else if (m_player->GetLifeCount()==5) {
		m_skinModel.SetDeadFlag(true);
		if (m_camera->GetFlag() == 2)
		{
			m_skinModel.SubtructDitherCoefficient(0.02f);
		}
		//�f�B�U�����O���g�p���邽�߂̃t���O��n��
		m_skinModel.SetDithering(true);
		//�f�B�U�����O���g�p����Ƃ��̊�_�ƂȂ���W��n��
		m_skinModel.SetDitheringPos(m_player->GetPosition());
		//������
		if (m_skinModel.GetditherRate()<=0.0
			&&m_overprod->GetStep()==m_overprod->GetDiser())
		{
			m_PressDead = NewGO<prefab::CSoundSource>(0);
			m_PressDead->Init("sound/Motion-Pop01.wav");
			m_PressDead->SetVolume(2.0);
			m_PressDead->Play(false);
			m_overprod->SetDeadStep();
		}
	}
	else {
		m_skinModel.SetDeadFlag(false);
		//m_skinModel.SetDithering(false);
	}
	m_skinModel.Update(m_position, m_rotation, m_scale);
}
void MapChip::Render(CRenderContext& rc)
{
	
	m_skinModel.Draw(rc,
		MainCamera().GetViewMatrix(),
		MainCamera().GetProjectionMatrix(),
		m_mirror->GetMirrorViewMatrix(),
		m_mirror->GetMirrorProjectionMatrix());
}
