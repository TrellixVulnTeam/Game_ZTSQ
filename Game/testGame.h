#pragma once

#include "tkEngine/graphics/effect/tkEffect.h"

class Fade;
class Mirror;
class testGameCamera;
class testBackGround;

class testGame : public IGameObject
{
public:
	testGame();
	~testGame();
	bool Start();
	void Update();
	void Render(CRenderContext& rc);
	void OnDestroy();
	prefab::CSkinModelRender* m_skinModelRender = nullptr;	//�X�L�����f�������_���[�B
	CAnimationClip m_animClip[1];							//�A�j���[�V�����N���b�v�B
	CAnimation m_animation;
	CVector3 m_pos = CVector3::Zero;
private:
	enum EnState {
		enState_FadeIn, //�t�F�[�h�C����
		enState_InGame, //�C���Q�[����
	};
	EnState m_state = enState_FadeIn;
	Fade* m_fade = nullptr;
	bool m_isWaitFadeout = false;
	float m_waitTimer = 0.0f;
	Mirror* m_mirror = nullptr;
	testGameCamera* m_gameCamera = nullptr;
	testBackGround* m_background = nullptr;
};

