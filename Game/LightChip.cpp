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
	/*for (auto ptLight : m_pointLightList)
	{
		DeleteGO(ptLight);
	}
	for (auto dirLight : m_directionLightList);*/
}
void LightChip::ptLightInit(
	const wchar_t* modelDataFilePath,
	int number,
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
	auto it = m_ptLightMap.find(number);
	if (it == m_ptLightMap.end()) {
		m_ptLightMap.insert({ number,ptLight });
	}

	//m_pointLightList.push_back(ptLight);
}
void LightChip::dirLightInit(
	const wchar_t* modelFilePath,
	int number,
	CQuaternion rotation,
	CVector3 color
	) {
	prefab::CDirectionLight* dirLight;
	dirLight = NewGO<prefab::CDirectionLight>(0);
	CVector3 direction;
	CMatrix rot;
	//�N�H�[�^�j�I������I�C���[�p�𒊏o
	rot.MakeRotationFromQuaternion(rotation);
	float sinX;
	sinX = rot.m[2][1];
	if (!(fabsf(sinX) == 1)) {
		direction.x = asinf(rot.m[2][1]);
		direction.y = atan2f(-rot.m[2][0], rot.m[2][2]);
		direction.z = atan2f(-rot.m[0][1], rot.m[1][1]);
	}
	else if (sinX == 1) {
		direction.x = CMath::PI / 2.0f;
		direction.y = 0.0f;
		direction.z = atan2f(rot.m[1][0],rot.m[0][0]);
	}
	else if (sinX == -1) {
		direction.x = -CMath::PI / 2.0f;
		direction.y = 0.0f;
		direction.z = atan2f(rot.m[1][0], rot.m[0][0]);
	}
	//direction = Multiply(CVector4 rotation);
	//���C�g�̕�����ݒ�
	dirLight->SetDirection(direction);
	//���C�g�̐F��ݒ�
	dirLight->SetColor(color);
	GraphicsEngine().GetShadowMap().SetLightDirection({ 0.0,-1.0f,0.0f });
	auto it = m_dirLightMap.find(number);
	if (it == m_dirLightMap.end()) {
		m_dirLightMap.insert({ number,dirLight });
	}
	//m_directionLightList.push_back(dirLight);
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
	//���C�g�̒������@---------------------------------------------
	//auto it = m_ptLightMap.find(00);
	//prefab::CPointLight* pt;
	////���C�g�̃i���o�[�͂O�O�`�@�n�܂�
	//pt = GetptLight(00);
	//pt->SetColor({ 0.0f,0.0f,0.0f,1.0f });
	//--------------------------------------------------------------
	/*for (auto& pt : m_pointLightList)
	{
		CVector3 pos = pt->GetPosition();
		addmove.z = -10.0f;
		pos = pos + addmove;
		pt->SetPosition(pos);
	}*/
}
prefab::CPointLight* LightChip::GetptLight(int num)
{
	auto it = m_ptLightMap.find(num);
	if (it == m_ptLightMap.end()) {
		return NULL;
	}	
	return it->second;
}
prefab::CDirectionLight* LightChip::GetdirLight(int num)
{
	auto it = m_dirLightMap.find(num);
	if (it == m_dirLightMap.end()) {
		return NULL;
	}
	return it->second;
}