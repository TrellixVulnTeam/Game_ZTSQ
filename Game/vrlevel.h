#pragma once
#include"vrMapChip.h"
class vrlevel
{
public:
	vrlevel();
	~vrlevel();

	//���x���\��
	void Build(const wchar_t*levelDataFilePath);

	//�����o�ϐ�
	std::list<vrMapChip*>m_mapChipList;		//�}�b�v�`�b�v�̃��X�g
};