#pragma once
class TitlePlayer;

class Titlemirror : public IGameObject
{
public:
	Titlemirror();
	~Titlemirror();
	bool Start();
	void Update();
	void Render(CRenderContext& rc);

private:
	CSkinModel m_skinModel;			//�X�L�����f���B
	CSkinModelData m_skinModelData;	//�X�L�����f���f�[�^�B
	CVector3 m_position = CVector3::Zero;
	CQuaternion m_rotation = CQuaternion::Identity;
	TitlePlayer* pl = nullptr;
};

