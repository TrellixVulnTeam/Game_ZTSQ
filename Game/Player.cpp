#include "stdafx.h"
#include "Player.h"
#include"Mirror.h"
#include"Game.h"
#include"Goal.h"
#include"GameOverProd.h"
#include"Game.h"
//#include"tkEngine/bulletPhysics/src/LinearMath/btConvexHull.h"
#include"tkEngine/DirectXTK/Inc/SimpleMath.h"
Player::Player()
{
}


Player::~Player()
{
	DeleteGO(m_Prod);
}

bool Player::Start() {
	//���f���f�[�^�̃��[�h
	m_skinModelData.Load(L"modelData/FemaleMage.cmo");
	m_skinModel.Init(m_skinModelData);
	////�@���}�b�v�ƃX�y�L�����}�b�v�����[�h
	//m_specularMap.CreateFromDDSTextureFromFile(L"sprite/utc_spec.dds");
	//m_normalMap.CreateFromDDSTextureFromFile(L"sprite/utc_normal.dds");
	//m_skinModel.FindMaterial([&](auto material) {
	//	material->SetNormalMap(m_normalMap.GetBody());
	//	//material->SetSpecularMap(m_specularMap.GetBody());
	//});
	m_animClip[enAnimationClip_walk].Load(L"animData/walk.tka");
	for (auto& animClip : m_animClip) {
		animClip.SetLoopFlag(true);
	}
	m_animation.Init(m_skinModel, m_animClip,enAnimationClip_num);
	m_animation.Play(enAnimationClip_walk, 0.2f);
	m_rotation.Multiply(m_rotation);
	//hp�e�N�X�`��
	m_htexture.CreateFromDDSTextureFromFile(L"sprite/hp.dds");
	m_hsprite.Init(m_htexture, 460, 40);
	//hpd�e�N�X�`��
	m_hdtexture.CreateFromDDSTextureFromFile(L"sprite/hpd.dds");
	m_hdsprite.Init(m_hdtexture, 460, 40);
	//hp bar�e�N�X�`��
	m_hbtexture.CreateFromDDSTextureFromFile(L"sprite/hpmp_bar.dds");
	m_hbsprite.Init(m_hbtexture, 490, 70);
	m_position.y = -1.5;
	//����������
	m_sen = m_position;
	m_charaCon.Init(
		2.0,		//���a
		1.0f,		//����
		-220,
		m_position,	//�����ʒu
		m_collidertype
	);
	m_position = { 0.0f,0.0f,0.0f };
	flag = 0;
	count = 0;
	scale = 3.0f;
	m_gpos = m_position;
	m_game=FindGO<Game>("Game");
	m_mirror = FindGO<Mirror>("Mirror");
	m_goal = FindGO<Goal>("Goal");
	m_skinModel.Update(m_position, m_rotation,CVector3::One);
	m_skinModel.SetShadowCasterFlag(true);
	return true;
}
void Player::Move()
{
	//���X�e�B�b�N�̓��͗ʂ��󂯎��B
	float lStick_x = Pad(0).GetLStickXF();
	float lStick_y = Pad(0).GetLStickYF();
	//�J�����̑O�������ƉE�������擾�B
	CVector3 cameraForward = MainCamera().GetForward();
	CVector3 cameraRight = MainCamera().GetRight();
	//XZ���ʂł̑O�������A�E�����ɕϊ�����B
	cameraForward.y = 0.0f;
	cameraForward.Normalize();
	cameraRight.y = 0.0f;
	cameraRight.Normalize();
	//XZ�����̈ړ����x���N���A�B
	/*m_moveSpeed.x = 0.0f;
	m_moveSpeed.z = 0.0f;*/
	cameraForward *=lStick_y * 200.0f*GameTime().GetFrameDeltaTime();	//�������ւ̈ړ����x�����B	
	cameraRight *= lStick_x * 200.0f*GameTime().GetFrameDeltaTime();	//�E�����ւ̈ړ����x�����Z�B
	
	if (Pad(0).IsTrigger(enButtonA) && m_charaCon.IsOnGround() == true) {
		m_moveSpeed.y += 98.0f;
	}
	//���C
	CVector3 masa = m_moveSpeed;
	if (m_charaCon.IsJump()) {
		//�W�����v��
		masa *= -1.0f;
	}
	else {
		//���̑�
		masa *= -3.0f;
	}

	m_moveSpeed.x += masa.x * GameTime().GetFrameDeltaTime();
	m_moveSpeed.z += masa.z * GameTime().GetFrameDeltaTime();

	m_moveSpeed += cameraForward;
	m_moveSpeed += cameraRight;
	
	m_rot.MakeRotationFromQuaternion(m_rotation);
	m_position = m_charaCon.Execute(GameTime().GetFrameDeltaTime(), m_moveSpeed, m_collidertype);
}

void Player::Rotation() {

	m_rot.MakeRotationFromQuaternion(m_rotation);
	/*m_position.x = m_rot.m[2][0] * plposlen + toro->m_position.x;
	m_position.y = m_rot.m[2][1] * plposlen + toro->m_position.y;
	m_position.z = m_rot.m[2][2] * plposlen + toro->m_position.z;
	m_rotation.x = toro->m_rotation.x;
	m_rotation.y = toro->m_rotation.y;
	m_rotation.z = toro->m_rotation.z;
	m_rotation.w = toro->m_rotation.w;*/
	if (fabsf(m_moveSpeed.x) < 0.001f
		&& fabsf(m_moveSpeed.z) < 0.001f) {
		return;
	}
	//atan2��tan�Ƃ̒l���p�x(���W�A���P��)�ɕϊ����Ă����֐��B
	//m_moveSpeed.x / m_moveSpeed.z�̌��ʂ�tan�ƂɂȂ�B
	//atan2���g�p���āA�p�x�����߂Ă���B
	//���ꂪ��]�p�x�ɂȂ�B
	//	float angle = atan2(m_moveSpeed.x, m_moveSpeed.z);
	//atan���Ԃ��Ă���p�x�̓��W�A���P�ʂȂ̂�
	//SetRotationDeg�ł͂Ȃ�SetRotation���g�p����B
	//m_rotation.SetRotation(CVector3::AxisY, angle);

	//m_skinModel.Update(m_position, m_rotation, CVector3::One);
	float angle = atan2(m_moveSpeed.x, m_moveSpeed.z);
	m_rotation.SetRotation(CVector3::AxisY, angle);
}

void Player::Dead(CRenderContext& rc) {
	int numMesh = 0;
	auto vStart = m_position;
	vStart.y *= 0.3f;
	auto vEnd = vStart + CVector3(.0f, 0.0f, 20.0f);
	auto fNearPlaneLength = FLT_MAX;		//��ԋ߂����ʂ܂ł̋����B
	auto vNearPlaneNormal = CVector3::Zero; //��ԋ߂����ʂ̖@���B
	bool isHit = false;
	for (auto& mapChip : m_game->m_level.m_mapChipList) {
		const auto& mWorld = mapChip->m_skinModel.GetWorldMatrix();
		mapChip->m_skinModel.FindMesh([&](const auto& mesh) {
			numMesh++;
			ID3D11DeviceContext* deviceContext = GraphicsEngine().GetD3DDeviceContext();
			//���_�o�b�t�@�����b�N
			D3D11_MAPPED_SUBRESOURCE subresource;
			deviceContext->Map(mesh->vertexBuffer.Get(), 0, D3D11_MAP_WRITE_NO_OVERWRITE, 0, &subresource);
			//���_�o�b�t�@�̒�`���擾�B
			D3D11_BUFFER_DESC bufferDesc;
			mesh->vertexBuffer->GetDesc(&bufferDesc);

			//���_�o�b�t�@�̐擪�A�h���X���擾�B
			char* pVertexData = reinterpret_cast<char*>(subresource.pData);
			//�C���f�b�N�X�o�b�t�@�����b�N�B
			deviceContext->Map(mesh->indexBuffer.Get(), 0, D3D11_MAP_WRITE_NO_OVERWRITE, 0, &subresource);
			bufferDesc;
			mesh->indexBuffer->GetDesc(&bufferDesc);
			int stride = 2;
			int indexCount = bufferDesc.ByteWidth / stride;
			//�C���f�b�N�X�o�b�t�@�ɃA�N�Z�X����B
			unsigned short* pIndex = reinterpret_cast<unsigned short*>(subresource.pData);
			int numTri = indexCount / 3;
			for (int triNo = 0; triNo < numTri; triNo++) {
				CVector3* triVertex[3];
				triVertex[0] = (CVector3*)(pVertexData + pIndex[0] * mesh->vertexStride);
				triVertex[1] = (CVector3*)(pVertexData + pIndex[1] * mesh->vertexStride);
				triVertex[2] = (CVector3*)(pVertexData + pIndex[2] * mesh->vertexStride);
				//���̎O�p�`�B
				pIndex += 3;


				//�O�p�`�����閳�����ʂ����߂�B
				//Plane plane;

				//float w;
				CVector3 tri[3];
				tri[0] = *triVertex[0];
				tri[1] = *triVertex[1];
				tri[2] = *triVertex[2];
				//���[���h��Ԃɕϊ��B
				mWorld.Mul(tri[0]);
				mWorld.Mul(tri[1]);
				mWorld.Mul(tri[2]);


				//���ʂ̖@�����v�Z����B
				CVector3 v1, v2, normal;
				v1 = tri[0] - tri[1];
				v2 = tri[2] - tri[1];

				normal.Cross(v1, v2);
				normal.Normalize();

				//�O�p�`�̒��_���烌�C�̎n�_�ւ̃x�N�g�����v�Z����B
				CVector3 vertToStart = vStart - tri[0];
				//�O�p�`�̒��_���烌�C�̏I�_�ւ̃x�N�g�����v�Z����B
				CVector3 vertToEnd = vEnd - tri[0];
				float d1 = normal.Dot(vertToStart);
				float d2 = normal.Dot(vertToEnd);

				int a = 0;
				if (d1 * d2 < 0.0f) {

					//��_�����߂�B
					auto absD1 = fabsf(d1);
					auto absD2 = fabsf(d2);
					auto rayLengthInNormal = absD1 + absD2;
					auto crossPoint = (vStart * absD1 / rayLengthInNormal)
						+ (vEnd * absD2 / rayLengthInNormal);
					//�������ʂƏՓ˂����̂ŁA���͎O�p�`�̓��O������s���B
					auto vert0ToCrossPoint = crossPoint - tri[0];
					vert0ToCrossPoint.Normalize();
					auto vert1ToCrossPoint = crossPoint - tri[1];
					vert1ToCrossPoint.Normalize();
					auto vert2ToCrossPoint = crossPoint - tri[2];
					vert2ToCrossPoint.Normalize();

					auto vert0ToVert1 = tri[1] - tri[0];
					vert0ToVert1.Normalize();

					auto vert1ToVert2 = tri[2] - tri[1];
					vert1ToVert2.Normalize();

					auto vert2ToVert0 = tri[0] - tri[2];
					vert2ToVert0.Normalize();

					CVector3 vWork[3];
					vWork[0].Cross(vert0ToVert1, vert0ToCrossPoint);
					vWork[0].Normalize();

					vWork[1].Cross(vert1ToVert2, vert1ToCrossPoint);
					vWork[1].Normalize();

					vWork[2].Cross(vert2ToVert0, vert2ToCrossPoint);
					vWork[2].Normalize();

					if (vWork[0].Dot(vWork[1]) > 0.0f && vWork[0].Dot(vWork[2]) > 0.0f) {
						//��_�͎O�p�`�̓����ɂ���B
						isHit = true;
						auto diff = vStart - crossPoint;
						auto len = diff.LengthSq();
						if (len < fNearPlaneLength) {
							//���̕��ʂ̂ق����߂��̂ŁA�����Ɩ@�����X�V����B
							fNearPlaneLength = len;
							vNearPlaneNormal = normal;
						}
					}
				}
			}
			//�C���f�b�N�X�o�b�t�@���A�����b�N�B
			deviceContext->Unmap(mesh->indexBuffer.Get(), 0);

			//���_�o�b�t�@���A�����b�N
			deviceContext->Unmap(mesh->vertexBuffer.Get(), 0);
		});
	}
	if (isHit == true) {
		auto vRayDir = vEnd - vStart;
		vRayDir.Normalize();
		if (vRayDir.Dot(vNearPlaneNormal) > 0.0f) {
			Dcount++;
			//�������b�V���̓����ɂ���H
		}
		//��������
		if (Pad(0).IsTrigger(enButtonX)) {
			//toro->lifecount = 5;
			PressFlag = 1;
		}
	}
}

void Player::Update()
{
	if (flag == 1&&m_goal->gflag==0&&m_prodcount==0) {

	//�ړ�
	Move();
	//��]
	Rotation();

	}
	if (dameflag == 1) {
		if (nlcount <= 0) {
			nlcount = 0.01;
		}
		//lifecount��5�ɂȂ�����Q�[���I�[�o�[
		if ((lifecount == 0 && hpscale <= 0.8)
			|| (lifecount == 1 && hpscale <= 0.6)
			|| (lifecount == 2 && hpscale <= 0.4)
			|| (lifecount == 3 && hpscale <= 0.2)
			|| (lifecount == 4 && hpscale <= 0.0))
		{
			lifecount = lifecount + 1;
		}
		dameflag = 0;
	}
		//�Q�b�Ԗ��G
		if (nlcount > 0) {
			nlcount = nlcount + GameTime().GetFrameDeltaTime();
			if (2 <= nlcount) {
				nlcount = 0;
				dameflag = 0;
			}
		}
		if (dameflag == 1) {
			if ((lifecount == 0 && nlcount == 0)
				|| (lifecount == 1 && nlcount == 0)
				|| (lifecount == 2 && nlcount == 0)
				|| (lifecount == 3 && nlcount == 0)
				|| (lifecount == 4 && nlcount == 0))
			{
				hpscale = hpscale - 0.1;
			}

		}
		if (hpdscale > hpscale) {
			hpdscale = hpdscale - 0.01;
			m_hdsprite.Update(m_hpdosition = { -625.0,345.0,0 }, CQuaternion::Identity, CVector3{ hpdscale,1.0,1.0 }, { 0.0,1.0 });
		}

		m_skinModel.Update(m_position, m_rotation, CVector3::One);
		m_hsprite.Update(m_hposition = { -625.0,345.0,0 }, CQuaternion::Identity, CVector3{ hpscale,1.0,1.0 }, { 0.0,1.0 });
		m_hdsprite.Update(m_hpdosition = { -625.0,345.0,0 }, CQuaternion::Identity, CVector3{ hpdscale,1.0,1.0 }, { 0.0,1.0 });
		m_hbsprite.Update(m_hbposition = { -640.0,360.0,0 }, CQuaternion::Identity, CVector3::One, { 0.0,1.0 });
}
void Player::Render(CRenderContext& rc)
{
	//����
	if (Dcount >= 5) {
		if (m_prodcount==0) {
			m_Prod = NewGO<GameOverProd>(0, "Prod");
			m_prodcount = 1;
		}
	}

	if ((flag==1)
		&&(m_mirror->m_isMirror == false)) {
		Dtime += GameTime().GetFrameDeltaTime();
		if (Dtime <= 1.0f) {
			Dead(rc);
		}
	}
 if(m_mirror->m_isMirror == true)
	{
		Dtime = 0.0f;
		Dcount = 0;
	}
	//�v���C���[�`��
	m_skinModel.Draw(rc, 
		MainCamera().GetViewMatrix(), 
		MainCamera().GetProjectionMatrix(),
		CMatrix::Identity,
		CMatrix::Identity
	);	
}
void Player::PostRender(CRenderContext& rc) {
	//�X�^�[�g
	if (flag == 0 && count == 0)
	{
		m_font.Begin(rc);
		m_font.Draw(L"PRESS ANY KEY", { 640.0f, -270.0f }, { 234.0f / 255.0f, 255.0f / 255.0f, 255.0f / 255.0f, 255.0f }, 0.0f, 1.5f);
		m_font.End(rc);
	}
	else if (flag == 0)
	{
		count = count + GameTime().GetFrameDeltaTime();
		if (count >= 0 && count <= 1)
		{
			if (scalefg == 0) {
				scale = 3;
				scalefg = 1;
			}
			m_font.Begin(rc);
			m_font.Draw(L"3", { 640.0f, -270.0f }, { 234.0f / 255.0f, 255.0f / 255.0f, 255.0f / 255.0f, 255.0f }, 0.0f, scale);
			m_font.End(rc);
			scale = scale - count*0.2;
		}
		if (count > 1 && count <= 2)
		{
			if (scalefg == 1) {
				scale = 3;
				scalefg = 0;
			}
			m_font.Begin(rc);
			m_font.Draw(L"2", { 640.0f, -270.0f }, { 234.0f / 255.0f, 255.0f / 255.0f, 255.0f / 255.0f, 255.0f }, 0.0f, scale);
			m_font.End(rc);
			scale = scale - (count - 1)*0.2;
		}
		if (count > 2 && count <= 3)
		{
			if (scalefg == 0) {
				scale = 3;
				scalefg = 1;
			}
			m_font.Begin(rc);
			m_font.Draw(L"1", { 640.0f, -270.0f }, { 234.0f / 255.0f, 255.0f / 255.0f, 255.0f / 255.0f, 255.0f }, 0.0f, scale);
			m_font.End(rc);
			scale = scale - (count - 2)*0.2;
		}
		if (count >3 && count <= 3.3)
		{
			if (scalefg == 1) {
				scale = 1;
				scalefg = 0;
			}
			m_font.Begin(rc);
			m_font.Draw(L"GO!", { 640.0f, -270.0f }, { 234.0f / 255.0f, 255.0f / 255.0f, 255.0f / 255.0f, 255.0f }, 0.0f, scale);
			m_font.End(rc);
			scale = scale + (count - 3) * 3;
		}
		if (count>3.3)
		{
			flag = 1;
		}
	}
	if (Pad(0).IsPressAnyKey()) {

		count = count + GameTime().GetFrameDeltaTime();
	}
	
		if (m_goal->gflag == 0) {
			//HP bar�e�N�X�`���`��
			m_hbsprite.Draw(rc,
				MainCamera2D().GetViewMatrix(),
				MainCamera2D().GetProjectionMatrix());

			//HP�_���[�W���e�N�X�`���`��
			m_hdsprite.Draw(rc,
				MainCamera2D().GetViewMatrix(),
				MainCamera2D().GetProjectionMatrix());
			//HP�e�N�X�`���`��
			m_hsprite.Draw(rc,
				MainCamera2D().GetViewMatrix(),
				MainCamera2D().GetProjectionMatrix());

		}
}