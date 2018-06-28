#include "stdafx.h"
#include "Enemybace.h"


Enemybace::Enemybace()
{
}


Enemybace::~Enemybace()
{
	//for (auto& ChipData : m_enemyDataList) {
	//	delete ChipData;
	//}
	//m_enemyMap.erase(m_enemyMap.begin(),m_enemyMap.end());
	//for(enemyMap)
}
void Enemybace::OnDestroy()
{

	//m_enemyMapChip.erase(m_enemyMapChip.begin(),m_enemyMapChip.end());
}
void Enemybace::Build(const wchar_t* fileDataPath) {
	//�X�P���g�����p���Ĕz�u
	CSkeleton skelton;
	skelton.Load(fileDataPath);
	int numMapChip = skelton.GetNumBones();
	for (int i = 1; i < numMapChip; i++)
	{
		CBone*bone = skelton.GetBone(i);
		//�{�[������g�嗦�A���s�ړ��A��]���擾����B
		CVector3 position,scale;
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
		//for()
		// std::wstring modelFilePath = boneName;
		swprintf(modelDataFilePath, L"modelData/%s.cmo",boneName);
		//modelFilePath = modelDataFilePath;
		LevelData* ChipData = new LevelData;
		ChipData->numMapChip = numMapChip;
		ChipData->Pos = position;
		ChipData->scale = scale;
		ChipData->Rotation = rotation;
		ChipData->modelFilePath = modelDataFilePath;
		m_enemyDataList.emplace_back(ChipData);
		//Enemybace *enemyChip = /*SetInstance()*/NewGO<Enemybace>(0);
		//enemyChip->Init(modelDataFilePath, position, CVector3::One, rotation);
	/*	auto it = FindEnemyMapChip(modelDataFilePath);
		if (it == EndEnemyMapChip()) {
			SetEnemyMapChip(modelDataFilePath, enemyChip);
		}*/
		//m_enemyBallList.emplace_back(enemyChip);
	}
}

//void Enemybace::CharaConCreate(float r, float height, float gravity, CVector3 Pos,
//	CCharacterController::ColliderType type) {
//	m_charaCon.Init(
//		r,
//		height,
//		gravity,
//		Pos,
//		type);
//}
//void Enemybace::Create()
//{
//	LevelData* level = new LevelData();
//	level = GetDataList().front();
//
//	//std::vector<LevelData*> it = GetDataList();
//	int num = level->numMapChip;
//	for (int i = 1; i < num; i++) {
//		EnemyBall* m_enemy = NewGO<EnemyBall>(0, "EnemyBall");
//		m_enemy->Init(level->modelFilePath.c_str(), level->Pos, level->Rotation, level->scale);
//		//m_enemyBallList.emplace_back(m_enemy);
//	}
//	delete level;
//}
////���x���쐬
//void Enemybace::Build(const wchar_t* fileDataPath) {
//	//�X�P���g�����p���Ĕz�u
//	CSkeleton skelton;
//	skelton.Load(fileDataPath);
//	int numMapChip = skelton.GetNumBones();
//	for (int i = 1; i < numMapChip; i++)
//	{
//		CBone*bone = skelton.GetBone(i);
//		//�{�[������g�嗦�A���s�ړ��A��]���擾����B
//		CVector3 position, scale;
//		CQuaternion rotation;
//		bone->CalcWorldTRS(position, rotation, scale);
//		//���␳������B
//		float t = position.y;
//		position.y = position.z;
//		position.z = -t;
//		t = rotation.y;
//		rotation.y = rotation.z;
//		rotation.z = -t;
//		//�{�[�������烂�f���f�[�^�̃t�@�C���p�X���쐬����B
//		const wchar_t* boneName = bone->GetName();
//		wchar_t modelDataFilePath[256];
//		swprintf(modelDataFilePath, L"modelData/%s.cmo", boneName);
//		Enemybace* enemyChip = NewGO<Enemybace>(0);
//		enemyChip->Init(modelDataFilePath, position, CVector3::One, rotation);
//		auto it = m_enemyChipMap.find(boneName);
//		if (it == m_enemyChipMap.end()) {
//			m_enemyChipMap.insert({ boneName,enemyChip });
//		}
//		//m_enemyChipMap.push_back(enemyChip);
//	}
//}
//void Enemybace::Init(
//	const wchar_t* modelFilePath,
//	CVector3 pos,
//	CVector3 scale,
//	CQuaternion rotation
//) {
//	m_skinModelData.Load(modelFilePath);
//	m_skinModel.Init(m_skinModelData);
//	m_skinModel.SetShadowReceiverFlag(true);
//	SetPosition(pos);
//	SetScale(scale);
//	SetRotation(rotation);
//	//m_position = pos;
//	//m_scale = scale;
//	//m_rotation = rotation;
//
//	//���b�V���R���C�_�[���쐬�B
//	m_meshCollider.CreateFromSkinModel(m_skinModel, nullptr);
//	//���̂̏����쐬�B
//	RigidBodyInfo rbInfo;
//	rbInfo.pos = GetPosition();
//	rbInfo.rot = GetRotation();
//	rbInfo.collider = &m_meshCollider;
//	rbInfo.mass = 0.0f;							//���ʂ�0�ɂ���Ɠ����Ȃ����̂ɂȂ�B
//												//�w�i�Ȃǂ̓����Ȃ��I�u�W�F�N�g��0��ݒ肷��Ƃ悢�B
//	m_rigidBody.Create(rbInfo);					//�쐬���������g���č��̂��쐬����B
//	m_rigidBody.GetBody()->setUserIndex(enCollisionAttr_Obstacle);
//	PhysicsWorld().AddRigidBody(m_rigidBody);	//�쐬�������̂𕨗����[���h�ɒǉ�����B
//}
//bool Enemybace::Start()
//{
//	return true;
//}
//void Enemybace::Update()
//{
//	//m_skinModel.Update(m_position, m_rotation, m_scale);
//}
//void Enemybace::Render(CRenderContext& rc)
//{
//	//m_skinModel.Draw(rc,
//	//	MainCamera().GetViewMatrix(),
//	//	MainCamera().GetProjectionMatrix(),
//	//	CMatrix::Identity,
//	//	CMatrix::Identity
//	//);
//}