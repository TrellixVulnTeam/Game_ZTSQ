#include "stdafx.h"
#include "TitleStar.h"
#include "TitlePlayer.h"

TitleStar::TitleStar()
{
}



TitleStar::~TitleStar()
{
}

bool TitleStar::Start()
{
	pl = FindGO<TitlePlayer>("TitlePlayer");
	//���f�������[�h(��)
	m_skinModelDatastar.Load(L"modelData/star.cmo");
	m_skinModelstar.Init(m_skinModelDatastar);
	//���f�����[�h(��)
	m_skinModelDatabrock.Load(L"modelData/rock.cmo");
	m_skinModelbrock.Init(m_skinModelDatabrock);
	//���[�̏����ʒu
	m_positionstar.y = -18.0f;
	m_positionstar.x = -10.0f;
	//��̏����ʒu
	m_positionbrock.y = -18.0f;
	m_positionbrock.x = -40.0f;
	
	return true;
}

void TitleStar::Update()
{
	//m_positionbrock.x += 0.2f;
	//if (pl->Flag == 1) {
	//	//��
	//	m_skinModelbrock.Update(m_positionbrock, CQuaternion::Identity, CVector3::One);
	//	//��
	//	m_skinModelstar.Update(m_positionstar, m_rotationstar, CVector3::One);
	//}
	if (pl->Flag == 1) {
		if (m_positionbrock.x < -20) {
			m_positionbrock.x += 0.1f;
		}
		m_skinModelbrock.Update(m_positionbrock, CQuaternion::Identity, CVector3::One);
	}
}

void TitleStar::Render(CRenderContext& rc)
{
	if (pl->Flag == 1 && (pl-> m_position.x > -10 || pl->m_position.x < -25)) 
		{
		////����`��
		//m_skinModelstar.Draw(rc,
		//	MainCamera().GetViewMatrix(),
		//	MainCamera().GetProjectionMatrix(),
		//	CMatrix::Identity,
		//	CMatrix::Identity,
		//	0
		//);
		
		//���`��
		m_skinModelbrock.Draw(rc,
			MainCamera().GetViewMatrix(),
			MainCamera().GetProjectionMatrix(),
			CMatrix::Identity,
			CMatrix::Identity
		);
	}
}