#pragma once
#include "tkEngine/character/tkCharacterController.h"

class Torokko;
class Goal;

class Game;
class GameOverProd;

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
	void Line();
	void Rotation();
	void Dead(CRenderContext& rc);
	
	void SetDamageFlag(int flag) {
		dameflag = flag;
	}
	int GetFlag() {
		return flag;
	}
	void SetLifeCount(int count) {
		lifecount = count;
	}
	int GetLifeCount() {
		return lifecount;
	}
	CVector3 GetPosition() {
		return m_position;
	}
	void SetPosition(CVector3 pos) {
		m_position = pos;
	}
	void SetRotationY(float degree) {
		m_rotation.SetRotationDeg(CVector3::AxisY, degree);
	}
	CVector3 GetGoalPosition() {
		return m_gpos;
	}
	CQuaternion GetRotation() {
		return m_rotation;
	}
	CMatrix GetMatrix() {
		return m_rot;
	}
	int GetPressFlag() {
		return PressFlag;
	}
	GameOverProd *GetProd() {
		return m_Prod;
	}
	int GetProdCount() {
		return m_prodcount;
	}
private:
	void InitPoly();

	struct Spoly
	{
		CVector3 m_triVertex[3];
		CVector3 m_normal;
	};
	int a = 0;
	int poflag = 0;
	std::vector<Spoly> m_polypool;
	std::vector<Spoly>::iterator itr;

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
	CVector3 m_position = { 0.0,10.0,0.0 } /*= CVector3::Zero*/;				//���W�B
	CVector3 diff = CVector3::Zero;
	CQuaternion qRot = CQuaternion::Identity;
	CQuaternion m_rotation = CQuaternion::Identity;		//��]
	CQuaternion m_rotation2 = CQuaternion::Identity;		//��]
	CFont m_font;										//����
	CVector3 m_gpos = CVector3::Zero;
	CVector3 m_cf = CVector3::Zero;
	CVector3 m_sen = CVector3::Zero;					//����
	CSkinModelData m_skinModelData1;						//�X�L�����f���f�[�^�B


	float x;
	float y;
	float plposlen;
	float angle;
	float hpscale = 1;
	float hpdscale = 1;
	int lifecount = 0;									//���C�t�J�E���^(���f�������ւ�)
	int dameflag = 0;									//�_���[�W�t���O
	int flag = 0;
	float nlcount = 1;									//���G�J�E���^
	float scale;										//�����̊g�嗦
	int scalefg = 0;									//�����g��t���O
	float count = 1;									//�����J�E���^�[
	int Dcount = 0;										//�f�b�h�J�E���^�[
	int DEndPosC = 0;									//�f�b�h�G���h�|�W�V�����J�E���^�[
	float Dtime = 0.0f;									//�~���[���g����1�b�ԃ^�C�}�[
	float Windtimer = 0.0f;								//�����Ăяo���^�C�}�[
	float WindCall = 0.0f;								//�����Ăяo������
	int m_prodcount = 0;
	float PressFlag = 0;
	Mirror* m_mirror = NULL;
	Goal* m_goal = nullptr;
	float ChangeFlag = 0;
	/*Game* m_game = nullptr;
	title* m_title = nullptr;*/
	Game*m_game = nullptr;
	GameOverProd* m_Prod = nullptr;
	enum EnAnimationClip {
		enAnimationClip_walk,
		enAnimationClip_num
	};
	CAnimationClip m_animClip[enAnimationClip_num];
	CAnimation m_animation;
	
	prefab::CSoundSource* m_bgm = nullptr;
	prefab::CSoundSource* m_wind = nullptr;
	prefab::CSoundSource* m_animeSound = nullptr;
	double vo = 1.0;
	double winvo = 0.5;
};
