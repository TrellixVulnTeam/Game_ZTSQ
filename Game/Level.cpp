#include "stdafx.h"
#include "Level.h"
#include "MapChip.h"


Level::Level()
{
}


Level::~Level()
{
	for (auto& mapChip : m_mapChipList) {
		DeleteGO(mapChip);
	}
}

//���x���쐬
void Level::Build(const wchar_t*levelDataaFilePath) {
	//�X�P���g�����p���Ĕz�u
	CSkeleton skelton;
	skelton.Load(levelDataaFilePath);
	int numMapChip = skelton.GetNumBones();
	for (int i = 1; i < numMapChip; i++)
	{
		CBone*bone = skelton.GetBone(i);
		//�{�[������g�嗦�A���s�ړ��A��]���擾����B
		CVector3 position, scale;
		CQuaternion rotation;
		bone->CalcWorldTRS(position, rotation, scale);
		//���␳������B
		float t = position.y;
		position.y = position.z;
		position.z = -t;
		t = rotation.y;
		rotation.y = rotation.z;
		rotation.z = -t;
		//�{�[�������烂�f���f�[�^�̃t�@�C���p�X���쐬����B
		const wchar_t* boneName = bone->GetName();
		wchar_t modelDataFilePath[256];
		swprintf(modelDataFilePath, L"modelData/%s.cmo", boneName);
		MapChip* mapChip = NewGO<MapChip>(0);
		mapChip->Init(modelDataFilePath, position, CVector3::One, rotation);
		m_mapChipList.push_back(mapChip);
	}
}