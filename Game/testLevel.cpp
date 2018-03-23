#include "stdafx.h"
#include "testLevel.h"
#include "testMapChip.h"

testLevel::testLevel()
{
}


testLevel::~testLevel()
{
	for (auto& testmapChip : m_mapChipList) {
		DeleteGO(testmapChip);
	}
}
//���x���̍쐬
//levelDataFilePath �ǂݍ��ރ��x���f�[�^�̃t�@�C���p�X
void testLevel::Build(const wchar_t* levelDataFilePath)
{
	//����͔z�u�f�[�^�Ƃ��ăX�P���g���𗘗p����
	CSkeleton skeleton;
	skeleton.Load(levelDataFilePath);
	int numMapChip = skeleton.GetNumBones();
	for (int i = 1; i < numMapChip; i++) {
		CBone* bone = skeleton.GetBone(i);
		//�{�[������g�嗦�A���s�ړ��A��]���擾����
		CVector3 position, scale;
		CQuaternion rotation;
		bone->CalcWorldTRS(position, rotation, scale);
		float w = position.y;
		position.y = position.z;
		position.z = -w;

		w = rotation.y;
		rotation.y = rotation.z;
		rotation.z = -w;

		//�{�[�������烂�f���f�[�^�̃t�@�C���p�X���쐬����
		const wchar_t* boneName = bone->GetName();
		wchar_t modelDataFilePath[256];
		swprintf(modelDataFilePath, L"modelData/%s.cmo", boneName);
		testMapChip* testmapChip = NewGO<testMapChip>(0);
		testmapChip->Init(modelDataFilePath, position, CVector3::One, rotation);
		m_mapChipList.push_back(testmapChip);
	}
}

