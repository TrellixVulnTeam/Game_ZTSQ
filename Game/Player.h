#pragma once
#include "tkEngine/character/tkCharacterController.h"

class Torokko;
class Goal;

class Player:public IGameObject
{
public:
	Player();
	~Player();

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
	void Turn();
	void Rotation();
	void Dead();
	
	//�����o�ϐ�
	CMatrix m_rot;
	CSkinModel m_skinModel;								//�X�L�����f���B
	CSkinModelData m_skinModelData;						//�X�L�����f���f�[�^�B
	CShaderResourceView m_specularMap;
	CShaderResourceView m_normalMap;
	CCharacterController m_charaCon;					//�L�����N�^�[�R���g���[���[�B
	CCharacterController::ColliderType m_collidertype = CCharacterController::Capsule;
	CVector3 m_moveSpeed = CVector3::Zero;				//�ړ����x�B
	CSprite m_hsprite;									//�X�v���C�g
	CShaderResourceView m_htexture;						//HP�e�N�X�`���B
	CVector3	m_hposition = CVector3::Zero;			//���W�B
	CSprite m_hdsprite;									//�X�v���C�g
	CShaderResourceView m_hdtexture;					//HP�_���[�W���e�N�X�`���B
	CVector3	m_hpdosition = CVector3::Zero;			//���W�B
	CSprite m_hbsprite;									//�X�v���C�g
	CShaderResourceView m_hbtexture;					//HP bar�e�N�X�`���B
	CVector3	m_hbposition = CVector3::Zero;			//���W�B
	CVector3 m_position = CVector3::Zero;				//���W�B
	CVector3 diff = CVector3::Zero;
	CQuaternion qRot = CQuaternion::Identity;
	CQuaternion m_rotation = CQuaternion::Identity;		//��]
	CQuaternion m_rotation2 = CQuaternion::Identity;		//��]
	CFont m_font;										//����
	CVector3 m_gpos = CVector3::Zero;

	float x;
	float plposlen;
	float angle;
	float hpscale=1;
	float hpdscale=1;
	int lifecount = 0;									//���C�t�J�E���^(���f�������ւ�)
	int dameflag = 0;									//�_���[�W�t���O
	int flag = 0;
	float nlcount = 1;									//���G�J�E���^
	float scale;										//�����̊g�嗦
	int scalefg = 0;									//�����g��t���O
	float count = 1;									//�����J�E���^�[
	Mirror* m_mirror = NULL;
	Torokko*toro = nullptr;
	Goal* m_goal = nullptr;
};
