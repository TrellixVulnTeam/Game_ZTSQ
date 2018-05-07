#pragma once
class LightChip : public IGameObject
{
public:
	LightChip();
	~LightChip();
	void ptLightInit(
		const wchar_t* modelFilePath,
		CVector3 pos,				//���W
		CVector3 color,				//�J���[
		int distancedecay				//����
	);
	void dirLightInit(
		const wchar_t* modelFilePath,
		CVector3 color
		);
	bool Start() override;
	void Update();
	void OnDestroy();

	//�����o�ϐ�
	std::vector<prefab::CPointLight*> m_pointLightList;		//�|�C���g���C�g�̃��X�g
	std::vector<prefab::CDirectionLight*>	m_directionLightList;	//�f�B���N�V�������C�g�̃��X�g
};

