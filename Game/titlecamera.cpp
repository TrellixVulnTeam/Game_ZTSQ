#include "stdafx.h"
#include "titlecamera.h"
//#include "TitlePlayer.h"

titlecamera::titlecamera()
{
}


titlecamera::~titlecamera()
{
}

bool titlecamera::Start()
{
	//m_toCameraPos.Set(0.0f, 1000.0f, 3000.0f);
	MainCamera().SetPosition({ 0.0f,0.0f, -40.0f });
	MainCamera().SetTarget({ 0.0f,0.0f, 0.0f });
	//MainCamera().SetTarget({ 0.0f,0.0f,0.0f });
	/*MainCamera(). SetNear(1.0f);
	MainCamera().SetFar(5000.0f);*/
	
	//tplayer = FindGO<TitlePlayer>("TitlePlayer");
	
	return true;
}



void titlecamera::Update()

{
	//���C���J�����ɒ����_�Ǝ��_��ݒ肷��B

	CVector3 target = CVector3::Zero;
	//target = tplayer -> m_position;
	CVector3 pos = { 0.0f,0.0f, -40.0f };
	
	MainCamera().SetTarget(target);
	MainCamera().SetPosition(pos);

	//���s���e�̐ݒ�

	MainCamera().SetUpdateProjMatrixFunc(CCamera::enUpdateProjMatrixFunc_Ortho);
	MainCamera().SetWidth(64);
	MainCamera().SetHeight(36);

	//�J�����̍X�V�B
	MainCamera().Update();
}