#pragma once
#include "Enemybace.h"
//#include "tkEngine/physics/tkRigidBody.h"
//#include "tkEngine/physics/tkSphereCollider.h"
#include "tkEngine/character/tkCharacterController.h"
class Player;
class Goal;

class EnemyBall : public Enemybace
{
public:
	EnemyBall();
	~EnemyBall();

	bool Start();
	void Update();
	void Render(CRenderContext& rc);
	void Build(const wchar_t* fileDataPath);
	void Init(
		const wchar_t* modelFilePath,
		CVector3 pos,
		CVector3 scale,
		CQuaternion rotation
	);	
private:
	//�����o�ϐ�
	CSkinModel m_skinModel;
	CSkinModelData m_skinModelData;
	CVector3 m_position = {-100.0f,28.0f,0.0f };
	CVector3 m_moveSpeed = CVector3::Zero;
	CVector3 up = CVector3::Up;							//�����
	CVector3 m_axisX;									//�C�ӂ̉�]��
	CVector3 m_scale = CVector3::One;
	CQuaternion m_rotation = CQuaternion::Identity;
	Player* m_player = nullptr;
	Goal* m_goal = nullptr;
	CVector3 diff = CVector3::Zero;
	//CSphereCollider m_collider;
	//CRigidBody m_rigidBody;
	CCharacterController m_charaCon;
	CCharacterController::ColliderType m_collidertype = CCharacterController::Sphere;
	float r = 20.0f;									//���a
	Mirror* m_mirror = NULL;
	//std::map<wchar_t,EnemyBall*> m_enemyMapChip
	prefab::CSoundSource* m_enemySound = nullptr;
};


