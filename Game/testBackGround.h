#pragma once

#include "tkEngine/physics/tkMeshCollider.h"
#include "tkEngine/physics/tkrigidBody.h"

class testBackGround : public IGameObject
{
public:
	testBackGround();
	~testBackGround();
	bool Start();
	void Update();
	void Render(CRenderContext& rc);
	void OnDestroy();
	//メンバ変数
	CSkinModelData m_skinModelData;
	CSkinModel m_skinModel;
	CVector3 m_position = CVector3::Zero;
	CVector3 m_scale = CVector3::One;
	CMeshCollider m_meshCollider;
	CRigidBody m_rigidBody;
	Mirror* m_mirror = NULL;
};

