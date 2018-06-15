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

	int GetDiser() {
		return Diser;
	}
	int GetStep() {
		return m_step;
	}
	void SetDeadStep() {
		m_step=Dead;
	}
private:
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
	void SetProduct(Product product) {
		m_step = product;
	}
	prefab::CSoundSource* m_animeSound = nullptr;
	int soundf = 0;
};

