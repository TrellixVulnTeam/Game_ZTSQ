#include "stdafx.h"
#include "EnemyBall.h"
#include "Player.h"
#include "Goal.h"
#include "Mirror.h"
#include "tkEngine/sound/tkSoundSource.h"

#include "tkEngine/tkEnginePreCompile.h"
//#include "tkEngine/character/tkCharacterController.h"
#include "tkEngine/Physics/tkCollisionAttr.h"
#include "tkEngine/tkEngine.h"



		//�Փ˂����Ƃ��ɌĂ΂��֐��I�u�W�F�N�g(�n�ʗp)
		struct SweepResultGround : public btCollisionWorld::ConvexResultCallback
		{
			bool isHit = false;									//�Փ˃t���O�B
			CVector3 hitPos = CVector3(0.0f, -FLT_MAX, 0.0f);	//�Փ˓_�B
			CVector3 startPos = CVector3::Zero;					//���C�̎n�_�B
			CVector3 hitNormal = CVector3::Zero;				//�Փ˓_�̖@���B
			btCollisionObject* me = nullptr;					//�������g�B�������g�Ƃ̏Փ˂����O���邽�߂̃����o�B
			float dist = FLT_MAX;								//�Փ˓_�܂ł̋����B��ԋ߂��Փ˓_�����߂邽�߁BFLT_MAX�͒P���x�̕��������_����肤��ő�̒l�B
			int ignoreCollisionAttr;				//��������R���W���������̃r�b�g�p�^�[���B
			Mirror* m_mirror = nullptr;
			//�Փ˂����Ƃ��ɌĂ΂��R�[���o�b�N�֐��B
			virtual	btScalar	addSingleResult(btCollisionWorld::LocalConvexResult& convexResult, bool normalInWorldSpace)
			{
				if (convexResult.m_hitCollisionObject == me
					|| convexResult.m_hitCollisionObject->getUserIndex() == enCollisionAttr_Character
					) {
					//�����ɏՓ˂����Bor �L�����N�^�����̃R���W�����ƏՓ˂����B
					return 0.0f;
				}
					//�Փ˓_�̖@�������������Ă���B
					CVector3 hitNormalTmp = *(CVector3*)&convexResult.m_hitNormalLocal;
					//������Ɩ@���̂Ȃ��p�x�����߂�B
					float angle = hitNormalTmp.Dot(CVector3::Up);
					angle = fabsf(acosf(angle));
					if (angle < CMath::PI * 0.3f		//�n�ʂ̌X�΂�54�x��菬�����̂Œn�ʂƂ݂Ȃ��B
						|| convexResult.m_hitCollisionObject->getUserIndex() == enCollisionAttr_Ground //�������̓R���W�����������n�ʂƎw�肳��Ă���B
						) {
						//�Փ˂��Ă���B
						isHit = true;
						CVector3 hitPosTmp = *(CVector3*)&convexResult.m_hitPointLocal;
						//�Փ˓_�̋��������߂�B�B
						CVector3 vDist;
						vDist.Subtract(hitPosTmp, startPos);
						float distTmp = vDist.Length();
						if (dist > distTmp) {
							//���̏Փ˓_�̕����߂��̂ŁA�ŋߖT�̏Փ˓_���X�V����B
							hitPos = hitPosTmp;
							hitNormal = *(CVector3*)&convexResult.m_hitNormalLocal;
							dist = distTmp;
						}
					}
					return 0.0f;
			}
		};
		//�Փ˂����Ƃ��ɌĂ΂��֐��I�u�W�F�N�g(�Ǘp)
		struct SweepResultWall : public btCollisionWorld::ConvexResultCallback
		{
			bool isHit = false;						//�Փ˃t���O�B
			CVector3 hitPos = CVector3::Zero;		//�Փ˓_�B
			CVector3 startPos = CVector3::Zero;		//���C�̎n�_�B
			float dist = FLT_MAX;					//�Փ˓_�܂ł̋����B��ԋ߂��Փ˓_�����߂邽�߁BFLT_MAX�͒P���x�̕��������_����肤��ő�̒l�B
			CVector3 hitNormal = CVector3::Zero;	//�Փ˓_�̖@���B
			btCollisionObject* me = nullptr;		//�������g�B�������g�Ƃ̏Փ˂����O���邽�߂̃����o�B
			int ignoreCollisionAttr;				//��������R���W���������̃r�b�g�p�^�[���B
			Player* pl = nullptr;
			Mirror* m_mirror = nullptr;
			//�Փ˂����Ƃ��ɌĂ΂��R�[���o�b�N�֐��B
			virtual	btScalar	addSingleResult(btCollisionWorld::LocalConvexResult& convexResult, bool normalInWorldSpace)
			{
	/*			if (ignoreCollisionAttr & (1 << convexResult.m_hitCollisionObject->getUserIndex())) {
					return 0.0f;
				}*/
				if (convexResult.m_hitCollisionObject == me
					/*|| (convexResult.m_hitCollisionObject->getUserIndex() == enCollisionAttr_Obstacle)*/
					)
				{
					//�����ɏՓ˂����Bor ��Q���ɏՓ˂����B
					//toro->dameflag = 0;
					return 0.0f;
				}
				//�Փ˓_�̖@�������������Ă���B
				CVector3 hitNormalTmp;
				hitNormalTmp.Set(convexResult.m_hitNormalLocal);
				//������ƏՓ˓_�̖@���̂Ȃ��p�x�����߂�B
				float angle = fabsf(acosf(hitNormalTmp.Dot(CVector3::Up)));
				if (angle >= CMath::PI * 0.3f		//�n�ʂ̌X�΂�54�x�ȏ�Ȃ̂ŕǂƂ݂Ȃ��B
					|| convexResult.m_hitCollisionObject->getUserIndex() == enCollisionAttr_Character	//�������̓R���W�����������L�����N�^�Ȃ̂ŕǂƂ݂Ȃ��B
					) {
					isHit = true;
					pl->SetDamageFlag(1);
					CVector3 hitPosTmp;
					hitPosTmp.Set(convexResult.m_hitPointLocal);
					//��_�Ƃ̋����𒲂ׂ�B
					CVector3 vDist;
					vDist.Subtract(hitPosTmp, startPos);
					vDist.y = 0.0f;
					float distTmp = vDist.Length();
					if (distTmp < dist) {
						//���̏Փ˓_�̕����߂��̂ŁA�ŋߖT�̏Փ˓_���X�V����B
						hitPos = hitPosTmp;
						dist = distTmp;
						hitNormal = hitNormalTmp;
					}
				}
				return 0.0f;
			}
		};

	EnemyBall::EnemyBall()
	{
	}
	EnemyBall::~EnemyBall()
	{
		//PhysicsWorld().RemoveRigidBody(m_rigidBody);
		for (auto& m_enemy : m_enemyBallList)
		{
			//PhysicsWorld().RemoveRigidBody(*m_enemy->m_charaCon.GetRigidBody());

			PhysicsWorld().RemoveRigidBody(m_enemy->m_rigidBody);
			DeleteGO(m_enemy);
		}
	}
	//void EnemyBall::OnDestroy() {
	//
	//	//m_charaCon.RemoveRigidBoby();
	//}
	//���x���쐬
	//void EnemyBall::Build(const wchar_t* fileDataPath) {
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
	//		EnemyBall* enemyChip = NewGO<EnemyBall>(0);
	//		enemyChip->Init(modelDataFilePath, position, CVector3::One, rotation);
	//		auto it = FindEnemyMapChip(modelDataFilePath);
			//if (it == EndEnemyMapChip()) {
	//			SetEnemyMapChip(modelDataFilePath, enemyChip);
	//		}
	//		//m_enemyBallList.emplace_back(enemyChip);
	//	}
	//}
	void EnemyBall::Create()
	{
		LevelData* level = new LevelData();
		level = GetDataList().front();

		//std::vector<LevelData*> it = GetDataList();
		int num = level->numMapChip;
		for (int i = 1; i < num; i++) {
			EnemyBall* m_enemy = NewGO<EnemyBall>(0);
			m_enemy->Init(level->modelFilePath.c_str(), level->Pos, level->Rotation, CVector3::One);
			m_enemyBallList.emplace_back(m_enemy);
		}
		delete level;
	}
	void EnemyBall::Init(const wchar_t* modelFilePath,
		CVector3 pos,
		CQuaternion rotation,
		CVector3 scale)/*std::vector<LevelData*> m_enemyDataList) */
	{
		//	while (it != GetDataList().end()) {
		//if (itr != GetDataList().end()) {
			/*CSkinModelData m_skinModelData;*/
		//wchar_t modelDataFilePath[256];
		//swprintf(modelDataFilePath, L"modelData/%s.cmo", modelFilePath);
		m_skinModelData.Load(modelFilePath);
		m_skinModel.Init(m_skinModelData);
		m_skinModel.SetShadowReceiverFlag(true);
		m_startPosition = pos;
		m_position = pos;
		m_rotation = rotation;
		m_scale = scale;
		//�R���C�_�[���쐬�B
		m_radius = 2.3f;
		m_collider.Create(m_radius);
		//���̂̏����쐬�B
		RigidBodyInfo rbInfo;
		rbInfo.pos = m_position;
		rbInfo.rot = m_rotation;
		rbInfo.collider = &m_collider;
		rbInfo.mass = 30.0f;						//���ʂ�0�ɂ���Ɠ����Ȃ����̂ɂȂ�B
													//�w�i�Ȃǂ̓����Ȃ��I�u�W�F�N�g��0��ݒ肷��Ƃ悢�B
		m_rigidBody.Create(rbInfo);					//�쐬���������g���č��̂��쐬����B
		btTransform& trans = m_rigidBody.GetBody()->getWorldTransform();
		//���̂̈ʒu���X�V�B
		trans.setOrigin(btVector3(pos.x, pos.y, pos.z));


		m_rigidBody.GetBody()->setUserIndex(enCollisionAttr_throughEnemy);
		m_rigidBody.GetBody()->setCollisionFlags(btCollisionObject::CF_CHARACTER_OBJECT);
		PhysicsWorld().AddRigidBody(m_rigidBody);	//�쐬�������̂𕨗����[���h�ɒǉ�����B
		//CharaConCreate(r, 0.0f, -220.0f, m_position, m_collidertype);
		//m_charaCon.Init(
		//	r,			//���a
		//	0.0f,			//����
		//	-220,			//�d��
		//	m_position,
		//	m_collidertype	//�R���C�_�[�̃^�C�v
		//);
		m_skinModel.Update(m_position, m_rotation, m_scale);
		//}
				//it->numMapChip;
		//	}
		//it->numMapChip;
	}
	//void EnemyBall::Init(
	//	const wchar_t* modelFilePath,
	//	CVector3 pos,
	//	CVector3 scale,
	//	CQuaternion rotation) {
	//	m_skinModelData.Load(modelFilePath);
	//	m_skinModel.Init(m_skinModelData);
	//	m_skinModel.SetShadowReceiverFlag(true);
	//	m_position = pos;
	//	m_scale = scale;
	//	m_rotation = rotation;

	//}
	bool EnemyBall::Start()
	{
		m_player = FindGO<Player>("Player");
		m_goal = FindGO<Goal>("Goal");

		CVector3 plPos = m_player->GetPosition();
		diff = plPos - m_position;
		//	m_enemySound = NewGO<prefab::CSoundSource>(0);
		//	m_enemySound->Init("sound/Rock.wav", true);
		//	m_enemySound->SetPosition(m_position);
		//	m_enemySound->SetVolume(3.0);
		//	m_enemySound->Play(true);
			//m_charaCon.Init(
			//	r,			//���a
			//	0.0f,			//����
			//	-220,			//�d��
			//	m_position,
			//	m_collidertype	//�R���C�_�[�̃^�C�v
			//);
		return true;
	}
	void EnemyBall::Update()
	{
		m_moveSpeed.y -= 98.0f * GameTime().GetFrameDeltaTime();
		//for (int i = 1; i < it->numMapChip; i++) {
			if (m_isHitWall == true) {
		CVector3 plPos = m_player->GetPosition();
		diff = plPos - m_position;
		}
		diff.y = 0.0f;							//Y���͕K�v�Ȃ��̂�
		//if (diff.Length() > 10.0f) {						//��������苗���ȓ��Ȃ�ǂ�������

//	m_enemySound->SetPosition(m_position);

	//if (m_charaCon.IsHitWall() == true) {
	//	CVector3 plPos = m_player->GetPosition();
	//	diff = plPos - m_position;
	//}
	//diff.y = 0.0f;							//Y���͕K�v�Ȃ��̂�
	////if (diff.Length() > 10.0f) {						//��������苗���ȓ��Ȃ�ǂ�������

		diff.Normalize();
		//�v���C���[�̈ړ����x�����肵���璲������----------------------------------
		m_moveSpeed.x = diff.x * 20.0f;
		m_moveSpeed.z = diff.z * 20.0f;
		//--------------------------------------------------------------------------	
		m_axisX.Cross(diff, up);
		m_axisX.Normalize();
		CQuaternion qRot;
		qRot.SetRotationDeg(m_axisX, -(CMath::PI * (r * 2.0f) / m_moveSpeed.Length()));
		m_rotation.Multiply(qRot);
		//}
		/*if (diff.Length() <= 10.0f) {
			m_moveSpeed.x = OldDiff.x * 20.0f;
			m_moveSpeed.z = OldDiff.z * 20.0f;
		}*/
		//m_position = m_charaCon.Execute(GameTime().GetFrameDeltaTime(), m_moveSpeed, m_collidertype);
		m_position = Physics(m_moveSpeed, GameTime().GetFrameDeltaTime());

		m_skinModel.Update(m_position, m_rotation, m_scale);
		//}
	}
	void EnemyBall::Render(CRenderContext& rc)
	{
		//if (m_goal == 0)
		//{
			//if (m_mirror == NULL) {
			//	m_mirror = FindGO<Mirror>("Mirror");
			//}
			//if (m_mirror->GetIsMirror() == true) {						//�~���[���g�p���Ȃ�I�u�W�F�N�g�������t���O���O�ɂ���
			//	m_skinModel.SetDiscardMirror(false);
			//}
			//else {
			//	m_skinModel.SetDiscardMirror(true);
			//}
		m_skinModel.Draw(rc,
			MainCamera().GetViewMatrix(),
			MainCamera().GetProjectionMatrix(),
			CMatrix::Identity,
			CMatrix::Identity
		);
		//}
	}
	const CVector3& EnemyBall::Physics(CVector3& moveSpeed, float DeltaTime)
	{
		if (m_player == nullptr)
		{
			m_player = FindGO<Player>("Player");
		}
		//���̈ړ���ƂȂ���W���v�Z����B
		CVector3 nextPosition = m_startPosition;
		//���x���炱�̃t���[���ł̈ړ��ʂ����߂�B�I�C���[�ϕ��B
		CVector3 addPos = moveSpeed;
		addPos.Scale(DeltaTime);
		nextPosition.Add(addPos);
		addPos.Subtract(nextPosition, m_startPosition);
		CVector3 originalXZDir = addPos;
		originalXZDir.y = 0.0f;
		originalXZDir.Normalize();
		//XZ���ʂł̏Փˌ��o�ƏՓˉ������s���B
		{
			int loopCount = 0;
			while (true) {
				//���݂̍��W���玟�̈ړ���֌������x�N�g�������߂�B
				CVector3 addPos;
				addPos.Subtract(nextPosition, m_startPosition);
				CVector3 addPosXZ = addPos;
				addPosXZ.y = 0.0f;
				if (addPosXZ.Length() < FLT_EPSILON) {
					//XZ���ʂœ������Ȃ��̂Œ��ׂ�K�v�Ȃ��B
					//FLT_EPSILON��1���傫���A�ŏ��̒l�Ƃ̍�����\���萔�B
					//�ƂĂ��������l�̂��Ƃł��B
					break;
				}
				CVector3 posTmp = m_startPosition;
				//���C���쐬�B
				btTransform start, end;
				//���R���C�_�[�̒��S���W + ����*0.1�̍��W��posTmp�ɋ��߂�B
				//CVector3 posTmp = m_position;
				posTmp.y += m_startPosition.y * 0.1f;
				//���C���쐬�B
				//btTransform start, end;
				start.setIdentity();
				end.setIdentity();
				//�n�_�͋��R���C�_�[�̒��S���W + 0.2�̍��W��posTmp�ɋ��߂�B
				start.setOrigin(btVector3(posTmp.x, posTmp.y, posTmp.z));
				//�I�_�͎��̈ړ���BXZ���ʂł̏Փ˂𒲂ׂ�̂ŁAy��posTmp.y��ݒ肷��B
				end.setOrigin(btVector3(nextPosition.x, posTmp.y, nextPosition.z));

				SweepResultWall callback;
				callback.me = m_rigidBody.GetBody();
				callback.startPos = posTmp;
				callback.pl = m_player;
				//callback.ignoreCollisionAttr = m_ignoreCollisionAttrs;
				//�Փˌ��o�B
				PhysicsWorld().ConvexSweepTest((const btConvexShape*)m_collider.GetBody(), start, end, callback);

				//�ǂɓ������Ă��Ȃ����
				m_isHitWall = false;
				if (callback.isHit) {
					//���������B
					//�ǁB
					m_isHitWall = true;
					CVector3 vT0, vT1;
					//XZ���ʏ�ł̈ړ���̍��W��vT0�ɁA��_�̍��W��vT1�ɐݒ肷��B
					vT0.Set(nextPosition.x, 0.0f, nextPosition.z);
					vT1.Set(callback.hitPos.x, 0.0f, callback.hitPos.z);
					//�߂荞�݂��������Ă���ړ��x�N�g�������߂�B
					CVector3 vMerikomi;
					vMerikomi.Subtract(vT0, vT1);
					//XZ���ʂł̏Փ˂����ǂ̖@�������߂�B�B
					CVector3 hitNormalXZ = callback.hitNormal;
					hitNormalXZ.y = 0.0f;
					hitNormalXZ.Normalize();
					//�߂荞�݃x�N�g����ǂ̖@���Ɏˉe����B
					float fT0 = hitNormalXZ.Dot(vMerikomi);
					//�����߂��Ԃ��x�N�g�������߂�B
					//�����Ԃ��x�N�g���͕ǂ̖@���Ɏˉe���ꂽ�߂荞�݃x�N�g��+���a�B
					CVector3 vOffset;
					vOffset = hitNormalXZ;
					vOffset.Scale(-fT0 + m_radius);
					nextPosition.Add(vOffset);
					CVector3 currentDir;
					currentDir.Subtract(nextPosition, m_startPosition);
					currentDir.y = 0.0f;
					currentDir.Normalize();
					if (currentDir.Dot(originalXZDir) < 0.0f) {
						//�p�ɓ��������̃L�����N�^�̐U����h�~���邽�߂ɁA
						//�ړ��悪�t�����ɂȂ�����ړ����L�����Z������B
						nextPosition.x = m_startPosition.x;
						nextPosition.z = m_startPosition.z;
						break;
					}
				}
				else {
					//�ǂ��Ƃ�������Ȃ��̂ŏI���B
					break;
				}
				loopCount++;
				if (loopCount == 5) {
					break;
				}
			}
		}
	
		//XZ�̈ړ��͊m��B
		m_startPosition.x = nextPosition.x;
		m_startPosition.z = nextPosition.z;

		{
			CVector3 addPos;
			addPos.Subtract(nextPosition, m_position);

			m_startPosition = nextPosition;	//�ړ��̉��m��B
										//���C���쐬����B
			btTransform start, end;
			start.setIdentity();
			end.setIdentity();
			//�n�_�̓J�v�Z���R���C�_�[�̒��S�B
			start.setOrigin(btVector3(m_startPosition.x, m_startPosition.y, m_startPosition.z));

			//�I�_�͒n�ʏ�ɂ��Ȃ��ꍇ��1m��������B
			//�n�ʏ�ɂ��Ȃ��ăW�����v�ŏ㏸���̏ꍇ�͏㏸�ʂ�0.01�{��������B
			//�n�ʏ�ɂ��Ȃ��č~�����̏ꍇ�͂��̂܂ܗ�����𒲂ׂ�B
			CVector3 endPos;
			endPos.Set(start.getOrigin());
			if (m_isOnGround == false) {
				if (addPos.y > 0.0f) {
					//�W�����v���Ƃ��ŏ㏸���B
					//�㏸���ł�XZ�Ɉړ��������ʂ߂荞��ł���\��������̂ŉ��𒲂ׂ�B
					endPos.y -= addPos.y * 0.01f;
				}
				else {
					//�������Ă���ꍇ�͂��̂܂܉��𒲂ׂ�B
					endPos.y += addPos.y;
				}
			}
			else {
				//�n�ʏ�ɂ��Ȃ��ꍇ��1m��������B
				endPos.y -= 1.0f;
			}
			end.setOrigin(btVector3(endPos.x, endPos.y, endPos.z));
			SweepResultGround callback;
			callback.me = m_rigidBody.GetBody();
			callback.startPos.Set(start.getOrigin());
			if (fabsf(endPos.y - callback.startPos.y) > FLT_EPSILON) {
				PhysicsWorld().ConvexSweepTest((const btConvexShape*)m_collider.GetBody(), start, end, callback);
			}
			if (callback.isHit)
			{
				//���������B
				moveSpeed.y = 0.0f;
				m_isJump = false;
				m_isOnGround = true;
				nextPosition.y = callback.hitPos.y + m_radius;
			}
			else {
				//�n�ʏ�ɂ��Ȃ��B
				m_isOnGround = false;

			}
		}
		//�ړ��m��
		m_startPosition = nextPosition;
		btRigidBody* btBody = m_rigidBody.GetBody();
		//���̂𓮂����B
		btBody->setActivationState(DISABLE_DEACTIVATION);
		btTransform& trans = btBody->getWorldTransform();
		//���̂̈ʒu���X�V�B
		trans.setOrigin(btVector3(m_startPosition.x, m_startPosition.y, m_startPosition.z));
		//@todo ���Ή��B trans.setRotation(btQuaternion(rotation.x, rotation.y, rotation.z));
		return m_startPosition;
	}
