#pragma once

#include "tkEngine/physics/tkMeshCollider.h"
#include "tkEngine/physics/tkRigidBody.h"

class Player;
class GameCamera;
class GameOverProd;

class MapChip : public IGameObject
{
public:

	MapChip();
	~MapChip();
	void Init(
		const wchar_t* modelFilePath,
		CVector3 pos,
		CVector3 scale,
		CQuaternion rotation
	);
	bool Start();
	void Update();
	void Render(CRenderContext& rc);
	void OnDestroy();
	const CSkinModel& GetSkinModel() {
		return m_skinModel;
	}
private:
	//////////////////////////////////////////////////
	// �������烁���o�ϐ��B
	//////////////////////////////////////////////////
	CSkinModelData m_skinModelData;		//!<�X�L�����f���f�[�^�B
	CSkinModel m_skinModel;				//!<�X�L�����f���B
	CVector3 m_position;				//!<���W�B
	CVector3 m_scale;					//!<�g��B
	CQuaternion m_rotation;				//!<��]�B
	CMeshCollider m_meshCollider;		//!<���b�V���R���C�_�[�B
	CRigidBody m_rigidBody;				//!<���́B
	Mirror* m_mirror = NULL;
	Player* m_player = NULL;
	GameCamera* m_camera = NULL;
	prefab::CSoundSource* m_PressDead = nullptr;
	GameOverProd* m_overprod=nullptr;
};