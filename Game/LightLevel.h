#pragma once
#include "LightChip.h"

class LightLevel : public IGameObject
{
public:
	LightLevel();
	~LightLevel();
	/*
	�|�C���g���C�g�\��
	ptlig_[���C�g�ԍ�]_[���C�g��r�����̋���]_[���C�g��g�����̋���]_[���C�g��b�����̋���]_[��������]
	*/
	void ptLightBuild(const wchar_t* lightDataFilePath);
/*
	�f�B���N�V�������C�g�\��
		dlig_[���C�g�ԍ�]_[���C�g��r�����̋���]_[���C�g��g�����̋���]_[���C�g��b�����̋���]
	*/
	void dirLightBuild(const wchar_t* dirlightDataFilePath);
private:
	//�����o�ϐ�
	wchar_t degit[32];
	int lightnum;							//���C�g�i���o�[
	CVector3 color = CVector3::Zero;		//�J���[
	int distanceDecay;						//��������
	LightChip* pointLig;
	std::list<LightChip*> m_ptLightList;	//�|�C���g���C�g�̃��X�g
	std::list<LightChip*> m_dirLightList;	//�f�B���N�V�������C�g�̃��X�g
};

