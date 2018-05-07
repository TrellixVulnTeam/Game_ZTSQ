#pragma once
class LightChip : public IGameObject
{
public:
	LightChip();
	~LightChip();
	void Init(
		const wchar_t* modelFilePath,
		CVector3 pos,				//���W
		CVector3 color,				//�J���[
		int distancedecay				//����
		);
	bool Start() override;
	void Update();
	void OnDestroy();
	void InitPointLight();			//�|�C���g���C�g�̏�����

	//�����o�ϐ�
	std::vector<prefab::CPointLight*> m_pointLightList;		//�|�C���g���C�g�̃��X�g
};

