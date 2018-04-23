#pragma once
#include "tkEngine/character/tkCharacterController.h"
class Mirror;
class Goal;
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
	float scale;										//�����̊g�嗦
	int scalefg = 0;									//�����g��t���O
	float count = 1;									//�����J�E���^�[
	int flag = 1;										
	int MoveFlag = 0;									//�X�^�[�g���̉����̃t���O
	int dameflag = 0;									//�_���[�W�t���O
	int lifecount = 0;									//���C�t�J�E���^
	int nlcount = 0;									//���G�J�E���^
	CMatrix m_rot;
	CVector3 diff;
	float posl;
	CSkinModelData m_skinModelData;						//�X�L�����f���f�[�^�B
	CSkinModel m_skinModel;								//�X�L�����f���B
	CSkinModelData m_skinModelData1;					//�_���[�W1�f�[�^	
	CSkinModel m_skinModel1;							//�_���[�W1���f��	
	CSkinModelData m_skinModelData2;					//�_���[�W2�f�[�^
	CSkinModel m_skinModel2;							//�_���[�W2���f��
	CSkinModelData m_skinModelData3;					//�_���[�W3�f�[�^
	CSkinModel m_skinModel3;							//�_���[�W3���f��
	CSkinModelData m_skinModelData4;					//�_���[�W4�f�[�^
	CSkinModel m_skinModel4;							//�_���[�W4���f��
	
	CVector3 m_position = CVector3::Zero;				//���W�B
	CCharacterController m_charaCon;					//�L�����N�^�[�R���g���[���[�B
	CVector3 m_moveSpeed = CVector3::Zero;				//�ړ����x�B
	CQuaternion qRot = CQuaternion::Identity;
	CQuaternion m_rotation = CQuaternion::Identity;		//��]
	CVector3 m_gpos = CVector3::Zero;
	CFont m_font;
	Mirror* m_mirror = NULL;
	Goal* m_goal = nullptr;
};

