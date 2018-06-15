#pragma once
#include "Level.h"
#include "vrlevel.h"
#include "LightLevel.h"
#include "tkEngine/graphics/effect/tkEffect.h"
#include "EnemyBall.h"

class Fade;
class background;
class Player;
//class Torokko;
class GameCamera;
class Mirror;
class Goal;
class ResultScene;
//class EnemyBall;
class GameOverProd;

class Game : public IGameObject
{
public:
	Game();
	~Game();
	bool Start();
	void Update();
	void Render(CRenderContext& rc);
	void OnDestroy();
	Level m_level;
private:
	enum EnState {
		enState_FadeIn, //�t�F�[�h�C����
		enState_InGame, //�C���Q�[����
	};
	EnState m_state = enState_FadeIn;
	Fade* m_fade = nullptr;
	bool m_isWaitFadeout = false;
	float m_waitTimer = 0.0f;

	LightLevel m_ptLight;
	LightLevel m_dirLight;

	vrlevel m_vrlevel;
	prefab::CDirectionLight* dirLight;

	CVector3 m_position= { 30.0f, 10.0f, 0.0f };
	int GameOverFlag = 0;
	Player*m_player = nullptr;
	background*m_background = nullptr;
	GameCamera*m_gamecamera = nullptr;
	Mirror* m_mirror = nullptr;
	Goal*m_goal = nullptr;
	ResultScene* m_result = nullptr;
	Player*m_pl = nullptr;
	GameOverProd* m_Prod = nullptr;
	//EnemyBall enemyLevel;
	prefab::CSkinModelRender* m_skinModelRender = nullptr;	//�X�L�����f�������_���[�B
	CAnimationClip m_animClip[1];							//�A�j���[�V�����N���b�v�B
	CAnimation m_animation;
	CVector3 m_pos = CVector3::Zero;

	float ChangeFlag = 0;
};