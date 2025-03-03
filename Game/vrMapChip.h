#pragma once

#include "tkEngine/physics/tkMeshCollider.h"
#include "tkEngine/physics/tkRigidBody.h"
class Player;
class GameCamera;

class vrMapChip : public IGameObject
{
public:
	vrMapChip();
	~vrMapChip();
	void Init(
			const wchar_t* modelFilePath,
			CVector3 pos,
			CVector3 scale,
			CQuaternion rotation
		);
		bool Start();
		void Update();
		void Render(CRenderContext& rc);
		void OnDestroy();
		//////////////////////////////////////////////////
		// ここからメンバ変数。
		//////////////////////////////////////////////////
		CSkinModelData m_skinModelData;		//!<スキンモデルデータ。
		CSkinModel m_skinModel;				//!<スキンモデル。
		CVector3 m_position;				//!<座標。
		CVector3 m_scale;					//!<拡大。
		CQuaternion m_rotation;				//!<回転。
		CMeshCollider m_meshCollider;		//!<メッシュコライダー。
		CRigidBody m_rigidBody;				//!<剛体。
		Mirror* m_mirror = NULL;
		Player* m_player = NULL;
		GameCamera* m_camera = NULL;
	};

