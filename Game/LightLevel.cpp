#define _CRT_NON_CONFORMING_SWPRINTFS
#include "stdafx.h"
#include "LightLevel.h"
#include "LightChip.h"
#include "tkEngine/util/tkLocData.h"
#include <locale.h>

LightLevel::LightLevel()
{
}


LightLevel::~LightLevel()
{
	for (auto& pointLig : m_ptLightList) {
		DeleteGO(pointLig);
	}
	/*for (auto& directionLig : m_dirLightList) {
		DeleteGO(directionLig);
	}*/
}

//���C�g�̍쐬
//lightDataFilePath�@�ǂݍ��ރ��C�g�f�[�^�̃t�@�C���p�X
void LightLevel::ptLightBuild(const wchar_t* lightDataFilePath)
{
	CLocData ligLoc;
	ligLoc.Load(lightDataFilePath);
	const wchar_t* boneName;
	wchar_t modelDataFilePath[256];
	for (int i = 0; i < ligLoc.GetNumObject(); i++) {
		boneName = ligLoc.GetObjectName(i);
		swprintf(modelDataFilePath,boneName);
		int j = 0;
		int count = 0;
		int DiscoveryCnt = 0;			//�w�肵�������𔭌�����
		while (modelDataFilePath[count] != NULL)
		{
			if (modelDataFilePath[count] == '[') {
				count++;
				while (modelDataFilePath[count] != ']') {
					degit[j] = modelDataFilePath[count];
					count++;
					j++;
				}
			}
			if (modelDataFilePath[count] == ']')
			{
				DiscoveryCnt++;
			}
			if (DiscoveryCnt == 1) {
				for (int i = 0; i < j; i++) {
					lightnum = _wtoi(degit);
				}
			}
			if (DiscoveryCnt == 2) {
				for (int i = 0; i < j; i++) {
					color.x = _wtoi(degit);
				}
			}
			if (DiscoveryCnt == 3) {
				for (int i = 0; i < j; i++) {
					color.y = _wtoi(degit);
				}
			}
			if (DiscoveryCnt == 4) {
				for (int i = 0; i < j; i++) {
					color.z = _wtoi(degit);
				}
			}
			if (DiscoveryCnt == 5) {
				for (int i = 0; i < j; i++) {
					distanceDecay = _wtoi(degit);
				}
			}
			count++;
			j = 0;
		}
	 pointLig = NewGO<LightChip>(0, "LightChip");
		pointLig->ptLightInit(lightDataFilePath,lightnum,ligLoc.GetObjectPosition(i),color,distanceDecay);
		m_ptLightList.push_back(pointLig);
	}
	//size_t wLen = 0;
	//char string[256];
	////�\�t�g�Ŏg�p���錾�����{��ɐݒ�
	//setlocale(LC_ALL, "japanese");
	////wchar�^��char�^�ɕϊ�
	//wcstombs_s(&wLen, string, 255, lightDataFilePath, _TRUNCATE);
	//�z�u�f�[�^�Ƃ��ăX�P���g���g�p
	//CSkeleton skeleton;
	//skeleton.Load(lightDataFilePath);
	//int numLight = skeleton.GetNumBones();
	//for (int i = 1; i < numLight; i++) {
	//	CBone* bone = skeleton.GetBone(i);
	//	//�{�[�����畽�s�ړ��A��]���擾
	//	CVector3 position, scale;
	//	CQuaternion rotation;
	//	bone->CalcWorldTRS(position, rotation, scale);
	//	//3dsMax�Ǝ����Ⴄ�̂ŁA�␳������
	//	float w = position.y;
	//	position.y = position.x;
	//	position.z = -w;

	//	w = rotation.y;
	//	rotation.y = rotation.z;
	//	rotation.z = -w;
	//	rotation.SetRotationDeg(CVector3::AxisY, 90.0f);
	//	//�{�[�������烂�f���f�[�^�̃t�@�C���p�X���쐬
	//	const wchar_t* boneName = bone->GetName();
	//	wchar_t modelDataFilePath[256];
	//	swprintf(modelDataFilePath, L"modelData/%s.cmo", boneName);
	//	int j = 0;
	//	int count = 0;
	//	int DiscoveryCnt = 0;			//�w�肵�������𔭌�����
	//	while (modelDataFilePath[count] != NULL)
	//	{
	//		if (modelDataFilePath[count] == '[') {
	//			count++;
	//			while (modelDataFilePath[count] != ']') {
	//				degit[j] = modelDataFilePath[count];
	//				count++;
	//				j++;
	//			}
	//		}
	//		if (modelDataFilePath[count] == ']')
	//		{
	//			DiscoveryCnt++;
	//		}
	//		if (DiscoveryCnt == 1) {
	//			for (int i = 0; i < j; i++) {
	//				lightnum = _wtoi(degit);
	//			}
	//		}
	//		if (DiscoveryCnt == 2) {
	//			for (int i = 0; i < j; i++) {
	//				color.x = _wtoi(degit);
	//			}
	//		}
	//		if (DiscoveryCnt == 3) {
	//			for (int i = 0; i < j; i++) {
	//				color.y = _wtoi(degit);
	//			}
	//		}
	//		if (DiscoveryCnt == 4) {
	//			for (int i = 0; i < j; i++) {
	//				color.z = _wtoi(degit);
	//			}
	//		}
	//		if (DiscoveryCnt == 5) {
	//			for (int i = 0; i < j; i++) {
	//				distanceDecay = _wtoi(degit);
	//			}
	//		}
	//		count++;
	//		j = 0;
	//	}
	//	LightChip* lightChip = NewGO<LightChip>(0, "LightChip");
	//	lightChip->ptLightInit(modelDataFilePath, position, color,distanceDecay);
	//	m_ptLightList.push_back(lightChip);
	//}
}
void LightLevel::dirLightBuild(const wchar_t* dirlightDataFilePath)
{
	CLocData ligLoc;
	ligLoc.Load(dirlightDataFilePath);
	const wchar_t* boneName;
	wchar_t modelDataFilePath[256];
	for (int i = 0; i < ligLoc.GetNumObject(); i++) {
		boneName = ligLoc.GetObjectName(i);
		swprintf(modelDataFilePath, boneName);
		int j = 0;
		int count = 0;
		int DiscoveryCnt = 0;			//�w�肵�������𔭌�����
		while (modelDataFilePath[count] != NULL)
		{
			if (modelDataFilePath[count] == '[') {
				count++;
				while (modelDataFilePath[count] != ']') {
					degit[j] = modelDataFilePath[count];
					count++;
					j++;
				}
			}
			if (modelDataFilePath[count] == ']')
			{
				DiscoveryCnt++;
			}
			if (DiscoveryCnt == 1) {
				for (int i = 0; i < j; i++) {
					lightnum = _wtoi(degit);
				}
			}
			if (DiscoveryCnt == 2) {
				for (int i = 0; i < j; i++) {
					color.x = _wtoi(degit);
				}
			}
			if (DiscoveryCnt == 3) {
				for (int i = 0; i < j; i++) {
					color.y = _wtoi(degit);
				}
			}
			if (DiscoveryCnt == 4) {
				for (int i = 0; i < j; i++) {
					color.z = _wtoi(degit);
				}
			}
			count++;
			j = 0;
		}
		LightChip* directionLig = NewGO<LightChip>(0, "LightChip");
		directionLig->dirLightInit(dirlightDataFilePath,lightnum,ligLoc.GetObjectRotation(i), color);
		//m_dirLightList.push_back(directionLig);
	}
}