#pragma once
class  Player;
class Goal :public IGameObject
{
public:
	Goal();
	~Goal();
	bool Start();
	void Update();
	void Render(CRenderContext& rc);
	CVector3 m_goalpos = CVector3::Zero;				//���W�B
	CVector3 m_goalpos1 = CVector3::Zero;				//���W�B
	Player*player = nullptr;
	int gflag = 0;										//�S�[���t���O
};

