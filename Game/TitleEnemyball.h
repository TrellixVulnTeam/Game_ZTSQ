#pragma once
class TitleEnemyball : public IGameObject

{
public:
	TitleEnemyball();
	~TitleEnemyball();
	bool Start();
	void Update();
	void Render(CRenderContext& rc);

private:
	CSkinModel m_skinModel;			//�X�L�����f���B
	CSkinModelData m_skinModelData;	//�X�L�����f���f�[�^�B
	CVector3 m_position = CVector3::Zero;
	CVector3 m_scale = CVector3::One;
	CQuaternion m_rotation = CQuaternion::Identity;
};

