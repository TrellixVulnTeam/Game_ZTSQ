#pragma once
class titlecamera;

class TitlePlayer : public IGameObject 
{
public:
	TitlePlayer();
	~TitlePlayer();
	bool Start();
	void Update();
	void Render(CRenderContext& rc);
	bool GetMoveFlag(){
		return Flag;
	}
	CVector3 GetPosition(){
		return m_position;
	}
private:
	bool Flag = false; // �ړ��̊Ǘ�
	CSkinModel m_skinModel;			//�X�L�����f���B
	CSkinModelData m_skinModelData;	//�X�L�����f���f�[�^�B
	CSkinModel m_skinModelmirror;
	CSkinModelData m_skinModelmirrorData;
	CVector3 m_position = CVector3::Zero;
	CQuaternion m_rotation = CQuaternion::Identity;
	CVector3 m_positionmirror = CVector3::Zero;
	titlecamera* m_taitlecamera = nullptr;
};

