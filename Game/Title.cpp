#include "stdafx.h"
#include "Title.h"
#include "Fade.h"
#include "Game.h"
#include "testGame.h"
#include"tkEngine/graphics/tkPresetRenderState.h"
#include "TitlePlayer.h"
#include "titlecamera.h"
#include "Mirror.h"
#include "Player.h"
#include "TitleEnemyball.h"
#include "TitleStar.h"
#include "Titlemirror.h"
#include"tkEngine/light/tkDirectionLight.h"
#include "tkEngine/sound/tkSoundSource.h"

Title::Title()
{
}


Title::~Title()
{
	DeleteGO(m_Stitle);
}
void Title::OnDestroy()
{
	/*DeleteGO(m_titletorokko);
	DeleteGO(m_titlecamera);*/
	DeleteGO(m_mirror);
	//DeleteGO(m_player);
	DeleteGO(m_titlecamera);
	DeleteGO(m_titleplayer);
	DeleteGO(m_titleenemyball);
	DeleteGO(m_titlestar);
	DeleteGO(dirLight);
	DeleteGO(m_titlemirror);
}
bool Title::Start()
{
	m_Stitle = NewGO<prefab::CSoundSource>(0);
	m_Stitle->Init("sound/title1.wav");
	m_Stitle->Play(true);
	dirLight = NewGO<prefab::CDirectionLight>(0);
	//���C�g�̕�����ݒ�
	dirLight->SetDirection({ 0.707f,-0.707f,0.0f });
	//���C�g�̐F��ݒ�
	dirLight->SetColor({ 10.0f,10.0f,10.0f,1.0f });
	GraphicsEngine().GetShadowMap().SetLightDirection({ 0.0,-1.0f,0.0f });
	
	m_titleplayer = NewGO<TitlePlayer>(0, "TitlePlayer");
	//m_mirror = NewGO<Mirror>(0, "Mirror");
	m_titlecamera = NewGO<titlecamera>(0, "titlecamera");
	m_titleenemyball = NewGO<TitleEnemyball>(0, "TitleEnemyball");
	m_titlestar = NewGO<TitleStar>(0, "TitleStar");
	m_titlemirror = NewGO<Titlemirror>(0, "Titlemirror");
	m_texture.CreateFromDDSTextureFromFile(L"sprite/title.dds");
	m_sprite.Init(m_texture, 1280, 720);
	m_fade = FindGO<Fade>("Fade");
	m_fade->StartFadeIn();
	return true;
}
void Title::Update()
{
	//////���C���J�����ɒ����_�Ǝ��_��ݒ肷��B
	//CVector3 target = { 0,0,0 };
	//CVector3 pos = { 0,0,-50 };
	//MainCamera().SetTarget(target);
	//MainCamera().SetPosition(pos);

	////�J�����̍X�V�B
	//MainCamera().Update();

	if (m_isWaitFadeout) {
		m_Stitle->SetVolume(1.0);
		if (!m_fade->IsFade()) {
			NewGO<Game>(0, "Game");
			DeleteGO(this);
		}
	}
	else {
		if (Pad(0).IsTrigger(enButtonStart)) {
			m_isWaitFadeout = true;
			m_fade->StartFadeOut();
		}
	}
	///////////////////////////////////////////////////////////////////////////////////////
	//�e�X�g
	if (GetAsyncKeyState(VK_SPACE)) {
		NewGO<testGame>(0, "testGame");				//�������̃e�X�g�p�A��ŏ���
		DeleteGO(this);
	}
	///////////////////////////////////////////////////////////////////////////////////////
	/*if (m_titlecamera == nullptr && m_titletorokko == nullptr) {
		m_titlecamera = NewGO<titlecamera>(0, "titlecamera");
		m_titletorokko = NewGO<titletorokko>(0, "titletorokko");
	}*/
	
	//m_sprite.Update(CVector3::Zero, CQuaternion::Identity, CVector3::One);
	//m_skinModel.Update(m_position, m_rotation, CVector3::One);
}
void Title::Render(CRenderContext& rc)
{
	//(void)rc;
	rc.OMSetDepthStencilState(DepthStencilState::spriteRender, 0);
	m_sprite.Draw(rc, MainCamera2D().GetViewMatrix(), MainCamera2D().GetProjectionMatrix());
	rc.OMSetDepthStencilState(DepthStencilState::SceneRender, 0);
/*
	int alphaflag = 0;
	m_skinModel.Draw(rc,
		MainCamera().GetViewMatrix(),
		MainCamera().GetProjectionMatrix(),
		CMatrix::Identity,
		CMatrix::Identity,
		alphaflag);*/
	
}