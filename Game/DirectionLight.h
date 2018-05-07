#pragma once
#include "LightChip.h"

class DirectionLight : public IGameObject
{
public:
	DirectionLight();
	~DirectionLight();
	
	void LightBuild(const wchar_t* lightDataFilePath);

	std::list<LightChip*> m_LightList;
	/*
	�f�B���N�V�������C�g�\��
		dlig_[���C�g�ԍ�]_[���C�g��r�����̋���]_[���C�g��g�����̋���]_[���C�g��b�����̋���]
	*/
	//�����o�ϐ�
	wchar_t degit[32];
	int lightnum;							//���C�g�i���o�[
	CVector3 color = CVector3::Zero;		//�J���[
	int distanceDecay;						//��������
};

