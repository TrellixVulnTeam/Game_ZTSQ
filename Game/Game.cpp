#include "stdafx.h"
#include "Game.h"
#include "Fade.h"
#include "Title.h"
#include"Level.h"
#include"background.h"
#include"Goal.h"
#include"Player.h"
#include"Torokko.h"
#include"GameCamera.h"
#include "Mirror.h"



Game::Game()
{
}


Game::~Game()
{
}
void Game::OnDestroy()
{
	DeleteGO(m_skinModelRender);
	DeleteGO(m_background);
	DeleteGO(m_player);
	DeleteGO(m_torokko);
	DeleteGO(m_gamecamera);
	DeleteGO(m_mirror);
	DeleteGO(m_goal);
}
bool Game::Start()
{
	//�g���b�R�쐬
	m_torokko = NewGO<Torokko>(0, "Trokko");
	//�v���C���[�쐬
	m_player=NewGO<Player>(0,"Player");
	//�J�����쐬
	m_gamecamera = NewGO<GameCamera>(0, "gamecamera");
	//�S�[���쐬
	m_goal = NewGO<Goal>(0, "Goal");
	//background�쐬
	m_background=NewGO<background>(0, "background");
	//�~���[�쐬
	m_mirror = NewGO<Mirror>(0, "Mirror");
	
	m_fade = FindGO<Fade>("Fade");
	m_fade->StartFadeIn();
	m_state = enState_FadeIn;

	//���x�����\�z����B
	m_level.Build(L"level/protobj1.tks");
	m_level.Build(L"level/protobj2.tks");
	m_level.Build(L"level/protobj3.tks");
	
	return true;
}
void Game::Update()
{
	switch (m_state) {
	case enState_FadeIn:
		GraphicsEngine().GetTonemap().Reset();
		if (!m_fade->IsFade()) {
			m_state = enState_InGame;
		}
		break;
	case enState_InGame: {
		m_waitTimer += GameTime().GetFrameDeltaTime();
		if (m_waitTimer < 0.1f) {
			//�Q�[�����J�n����0.1�b�o�߂���܂Ńg�[���}�b�v�̖��Ï����͂��Ȃ�
			GraphicsEngine().GetTonemap().Reset();
		}
	}
		 break;
	}
	if (m_isWaitFadeout)
	{
		if (!m_fade->IsFade()) {
			NewGO<Title>(0, nullptr);
			DeleteGO(this);
		}
	}
	else {
		if (Pad(0).IsTrigger(enButtonStart)) {
			m_isWaitFadeout = true;
			m_fade->StartFadeOut();
		}
	}
}
void Game::Render(CRenderContext& rc)
{
	(void)rc;
}