#pragma once
#include"MapChip.h"
class Level
{
public:
	Level();
	~Level();

	//レベル構成
	void Build(const wchar_t*levelDataFilePath);
	std::list<MapChip*> GetMapList() {
		return m_mapChipList;
	}
private:
	//メンバ変数
	std::list<MapChip*>m_mapChipList;		//マップチップのリスト
};

