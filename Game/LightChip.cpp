#include "stdafx.h"
#include "LightChip.h"
#include "tkEngine/light/tkDirectionLight.h"
#include "tkEngine/light/tkPointLight.h"

LightChip::LightChip()
{
}


LightChip::~LightChip()
{
}
void LightChip::OnDestroy()
{
	for (auto ptLight : m_pointLightList)
	{
		DeleteGO(ptLight);
	}
}
void LightChip::Init(
	const wchar_t* modelDataFilePath,
	CVector3 pos,				//���W
	CVector3 color,				//�J���[
	int distancedecay		//��������
) {
	prefab::CPointLight* ptLight = NewGO<prefab::CPointLight>(0);
	//�|�C���g���C�g�̍��W���w��
	ptLight->SetPosition(pos);
	//���C�g�̕�����ݒ�
	ptLight->SetColor(color);
	//�|�C���g���C�g�̌����p�����[�^��ݒ�
	CVector3 attn = CVector3::Zero;
	attn.x = distancedecay;
	attn.y = 1.0f;
	ptLight->SetAttn(attn);
	//�|�C���g���C�g�̃��X�g�ɐς�
	m_pointLightList.push_back(ptLight);
}
bool LightChip::Start()
{
	return true;
}
void LightChip::Update()
{
	//�|�C���g���C�g�̍��W��ύX
	CVector3 addmove;
	addmove = CVector3::Zero;
	/*for (auto& pt : m_pointLightList)
	{
		CVector3 pos = pt->GetPosition();
		addmove.z = -10.0f;
		pos = pos + addmove;
		pt->SetPosition(pos);
	}*/
}