#pragma once

class Player;
class GameCamera;
class GameOverProd:public IGameObject
{
public:
	GameOverProd();
	~GameOverProd();
	bool Start();
	void Update();
	enum Product {
		MoveCamera,				//�������̃J�����ړ�����
		Diser,					//�������̃f�B�U�W��
		Dead,
		
	};
	Product m_step;
	Player*m_pl = nullptr;
	GameCamera*m_camera = nullptr;
};

