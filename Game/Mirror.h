#pragma once
#include "tkEngine/character/tkCharacterController.h"
using namespace tkEngine;

class Player;

class Mirror : public tkEngine::IGameObject
{
public:
	Mirror();
	~Mirror();
	bool Start();
	void Rotation();
	void Update();
	void Render(CRenderContext& rc);
	void PostRender(CRenderContext& rc);
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
	CVector3 m_mirtarget = CVector3::Zero;
	CQuaternion m_rotation=CQuaternion::Identity;
	CQuaternion m_rotation1 = CQuaternion::Identity;//�ۊ�
	CVector3 mirrormaefront = CVector3::Zero;

	CSprite m_mpsprite;									//�X�v���C�g
	CShaderResourceView m_mptexture;					//�~���[MP�e�N�X�`���B
	CSprite m_mpbsprite;									//�X�v���C�g
	CQuaternion m_mprotation = CQuaternion::Identity;
	CShaderResourceView m_mpbtexture;					//�~���[MPbar�e�N�X�`���B
	CSprite m_msprite;									//�X�v���C�g
	CQuaternion m_mpbrotation = CQuaternion::Identity;
	CShaderResourceView m_mtexture;						//�~���[Mirror�e�N�X�`���B
	float mpscale=1.0;
	int fl = 0;//�ۊǃt���O
	int mpflag = 0;
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
	Player* pl = NULL;
	float angle = 0;
};

