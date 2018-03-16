#include "stdafx.h"
#include "Title.h"
#include "Fade.h"
#include "Game.h"
#include "testGame.h"


Title::Title()
{
}


Title::~Title()
{
}
bool Title::Start()
{
	m_texture.CreateFromDDSTextureFromFile(L"sprite/title.dds");
	m_sprite.Init(m_texture,1280,720/* GraphicsEngine().Get2DSpaceScreenWidth(), GraphicsEngine().Get2DSpaceScreenHeight()*/);
	m_fade = FindGO<Fade>("Fade");
	m_fade->StartFadeIn();
	return true;
}
void Title::Update()
{
	if (m_isWaitFadeout) {
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
}
void Title::PostRender(CRenderContext& rc)
{
	m_sprite.Draw(rc, MainCamera2D().GetViewMatrix(), MainCamera2D().GetProjectionMatrix());
}