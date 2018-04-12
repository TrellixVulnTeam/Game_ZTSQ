#pragma once
#include "tkEngine/character/tkCharacterController.h"

class Torokko:public IGameObject
{
public:
	Torokko();
	~Torokko();
	void Update();
	void Render(CRenderContext& rc);
	void PostRender(CRenderContext& rc)override;
	bool Start();
	//�A�j���[�V�������������B
	void InitAnimation();
	//�A�j���[�V��������B
	void AnimationControl();
	//�ړ������B
	void Move();
	void Rotation();

	//�����o�ϐ�
	float x;
	float count = 1;
	int flag = 1;
	int MoveFlag = 0;									//�X�^�[�g���̉����̃t���O
	int dameflag = 0;									//�_���[�W�t���O
	float scale;
	int scalefg = 0;
	CMatrix m_rot;
	CVector3 diff;
	float posl;
	CSkinModelData m_skinModelData;						//�X�L�����f���f�[�^�B
	CSkinModel m_skinModel;								//�X�L�����f���B
	CSkinModelData m_skinModelData1;					//�_���[�W1�f�[�^	
	CSkinModel m_skinModel1;								
	CSkinModelData m_skinModelData2;
	CSkinModel m_skinModel2;
	CSkinModelData m_skinModelData3;
	CSkinModel m_skinModel3;
	CSkinModelData m_skinModelData4;
	CSkinModel m_skinModel4;
	
	CVector3 m_position = CVector3::Zero;				//���W�B
	CCharacterController m_charaCon;					//�L�����N�^�[�R���g���[���[�B
	CVector3 m_moveSpeed = CVector3::Zero;				//�ړ����x�B
	CQuaternion qRot = CQuaternion::Identity;
	CQuaternion m_rotation = CQuaternion::Identity;		//��]
	CVector3 m_gpos = CVector3::Zero;
	CFont m_font;
	Mirror* m_mirror = NULL;
};

