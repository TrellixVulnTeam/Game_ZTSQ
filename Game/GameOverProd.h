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
	enum Product{
		MoveCamera,				//�������̃J�����ړ�����
		Diser,					//�������̃f�B�U�W��
		Dead,
		
	};
private:
	Product m_step;
	Player*m_pl = nullptr;
	GameCamera*m_camera = nullptr;
public:
	Product GetStep() {
		return m_step;
	}
	void SetProduct(Product product) {
		m_step = product;
	}
};

