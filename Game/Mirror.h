#pragma once
#include "tkEngine/character/tkCharacterController.h"
using namespace tkEngine;


class Mirror : public tkEngine::IGameObject
{
public:
	Mirror();
	~Mirror();
	bool Start();
	void Rotation();
	void Update();
	void Render(CRenderContext& rc);
	//�����o�ϐ�
	CMatrix m_rot;
	CMatrix m_mirrorforwardMatrix;
	CVector3 diff = CVector3::Zero;
	float Mirlen;
	CSkinModel m_skinModel;
	CSkinModelData m_skinModelData;
	CVector3 m_position = CVector3::Zero;
	CVector3 m_moveSpeed = CVector3::Zero;
	CVector3 m_target = CVector3::Zero;
	CQuaternion m_rotation=CQuaternion::Identity;
	CQuaternion m_rotation1 = CQuaternion::Identity;//�ۊ�
	int fl = 0;//�ۊǃt���O
	float angleX = 0.0f;
	float angleY = 0.0f;
	//testMirror* m_mirror = NULL;
	CMatrix m_mirrorViewMatrix;
	CMatrix m_mirrorProjectionMatrix;

	//CCharacterController m_charaCon;
	CQuaternion qRot = CQuaternion::Identity;
	CQuaternion qRot2 = CQuaternion::Identity;
	
	int  alphaflag = 1;									//�~���[�Ɏʂ��Ă��镨�̂������t���O
	bool m_isMirror = false;							//�~���[���g�p���Ă��邩�̃t���O

	static Mirror& GetInstance()
	{
		static Mirror* instance = nullptr;
		if (instance == nullptr) {
			instance = new Mirror;
		}
		return *instance;
	}
	float angle = 0;
};

