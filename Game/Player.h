#pragma once


class Player:public IGameObject
{
public:
	Player();
	~Player();

	void Update();
	void Render(CRenderContext& rc);
	bool Start();
	//�A�j���[�V�������������B
	void InitAnimation();
	//�A�j���[�V��������B
	void AnimationControl();
	//�ړ������B
	void Move();
	void Turn();
	void Rotation();
	
	//�����o�ϐ�
	CMatrix m_rot;
	CSkinModel m_skinModel;								//�X�L�����f���B
	CSkinModelData m_skinModelData;						//�X�L�����f���f�[�^�B
	CVector3 m_position = CVector3::Zero;				//���W�B
	CVector3 diff = CVector3::Zero;
	CQuaternion qRot = CQuaternion::Identity;
	CQuaternion m_rotation = CQuaternion::Identity;		//��]
	CQuaternion m_rotation2 = CQuaternion::Identity;		//��]
	float plposlen;
	float angle;
};
