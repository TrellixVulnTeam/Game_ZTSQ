#pragma once
#include"MapChip.h"
class Level
{
public:
	Level();
	~Level();

	//���x���\��
	void Build(const wchar_t*levelDataFilePath);
	std::list<MapChip*> GetMapList() {
		return m_mapChipList;
	}
private:
	//�����o�ϐ�
	std::list<MapChip*>m_mapChipList;		//�}�b�v�`�b�v�̃��X�g
};

