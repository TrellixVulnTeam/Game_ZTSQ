#pragma once

#include "testMapChip.h"

class testLevel
{
public:
	testLevel();
	~testLevel();
	//���x���̍\�z
	void Build(const wchar_t* levelDataFilePath);

	//�����o�ϐ�
	std::list<testMapChip*> m_mapChipList;		//�}�b�v�`�b�v
};

