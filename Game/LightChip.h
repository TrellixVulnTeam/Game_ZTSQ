#pragma once
#include "tkEngine/light/tkDirectionLight.h"
#include "tkEngine/light/tkPointLight.h"
class LightChip : public IGameObject
{
public:
	LightChip();
	~LightChip();
	void ptLightInit(
		const wchar_t* modelFilePath,
		int number,
		CVector3 pos,				//���W
		CVector3 color,				//�J���[
		int distancedecay				//����
	);
	void dirLightInit(
		const wchar_t* modelFilePath,
		int number,
		CQuaternion rotation,
		CVector3 color
		);
	prefab::CDirectionLight* GetdirLight(int num);
	prefab::CPointLight* GetptLight(int num);

	bool Start() override;
	void Update();
	void OnDestroy();

	//�����o�ϐ�
	//std::list<prefab::CPointLight*> m_pointLightList;		//�|�C���g���C�g�̃��X�g
	//std::list<prefab::CDirectionLight*>	m_directionLightList;	//�f�B���N�V�������C�g�̃��X�g
	std::map<int,prefab::CPointLight*> m_ptLightMap;
	std::map<int, prefab::CDirectionLight*> m_dirLightMap;
};

