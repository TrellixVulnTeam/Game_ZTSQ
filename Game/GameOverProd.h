#pragma once

class Player;

class GameOverProd:public IGameObject
{
public:
	GameOverProd();
	~GameOverProd();
	bool Start();
	void Update();
	enum Product{
		MoveCamera,				//�������̃J�����ړ�����
		Diser,					//�������̃f�B�U�W��
		
	};
	Product m_step;
	Player*m_pl = nullptr;
};

