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
	for (auto dirLight : m_directionLightList);
}
void LightChip::ptLightInit(
	const wchar_t* modelDataFilePath,
	CVector3 pos,				//���W
	CVector3 color,				//�J���[
	int distancedecay		//��������
) {
	prefab::CPointLight* ptLight = NewGO<prefab::CPointLight>(0);
	//�|�C���g���C�g�̍��W���w��
	ptLight->SetPosition(pos);
	//���C�g�̃J���[��ݒ�
	ptLight->SetColor(color);
	//�|�C���g���C�g�̌����p�����[�^��ݒ�
	CVector3 attn = CVector3::Zero;
	attn.x = distancedecay;
	attn.y = 1.0f;
	ptLight->SetAttn(attn);
	//�|�C���g���C�g�̃��X�g�ɐς�
	m_pointLightList.push_back(ptLight);
}
void LightChip::dirLightInit(
	const wchar_t* modelFilePath,
	CVector3 color
	) {
	prefab::CDirectionLight* dirLight;
	dirLight = NewGO<prefab::CDirectionLight>(0);
	//���C�g�̕�����ݒ�
	dirLight->SetDirection({ 0.707f,-0.707f,0.0f });
	//���C�g�̐F��ݒ�
	dirLight->SetColor(color);
	GraphicsEngine().GetShadowMap().SetLightDirection({ 0.0,-1.0f,0.0f });
	m_directionLightList.push_back(dirLight);
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