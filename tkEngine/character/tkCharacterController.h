/*!
 * @brief	�L�����N�^�R���g���[���[�B
 */

#pragma once
class Mirror;
class Player;

#include "tkEngine/Physics/tkSphereCollider.h"
#include "tkEngine/Physics/tkCapsuleCollider.h"
#include "tkEngine/Physics/tkRigidBody.h"

namespace tkEngine{
	/*!
	 * @brief	�L�����N�^�R���g���[���[�B
	 */
	class CCharacterController{
	public:
		CCharacterController() {

		}
		~CCharacterController()
		{
			RemoveRigidBoby();
		}
		enum ColliderType {
			Capsule,				//�J�v�Z���R���C�_�[
			Sphere					//���R���C�_�[
		};
		/*!
		 * @brief	�������B
		 *@param[in]	radius		�J�v�Z���R���C�_�[�̔��a�B
		 *@param[in]	height		�J�v�Z���R���C�_�[�̍����B
		 *@param[in]	gravity		�d�́B
		 *@param[in]	position	�����ʒu�B
		 *@param[in]	type		�R���C�_�[�̎�ށB
		 */
		void Init(float radius, float height,float gravity, const CVector3& position ,ColliderType type);
		/*!
		 * @brief	���s�B
		 *@param[in]	deltaTime		�o�ߎ��ԁB�P�ʂ͕b�B
		 *@param[in, out]	moveSpeed		�ړ����x�B�����ŏd�͉������v�Z����A���̌��ʂ�moveSpeed�ɔ��f����܂��B
		 *@return �ړ���̃L�����N�^�[�̍��W�B
		 */
		const CVector3& Execute(float deltaTime, CVector3& moveSpeed,ColliderType type);
		/*!
		 * @brief	���W���擾�B
		 */
		const CVector3& GetPosition() const
		{
			return m_position;
		}
		/*!
		 * @brief	���W��ݒ�B
		 */
		void SetPosition(const CVector3& pos)
		{
			m_position = pos;
		}
		
		/*!
		 * @brief	�W�����v������B
		 */
		void Jump( )
		{
			m_isJump = true;
			m_isOnGround = false;
		}
		/*!
		 * @brief	�W�����v��������
		 */
		bool IsJump() const
		{
			return m_isJump;
		}
		/*!
		* @brief	�n�ʏ�ɂ��邩����B
		*/
		bool IsOnGround() const
		{
			return m_isOnGround;
		}
		/*!
		* @brief	�ǂɓ������Ă��邩����B
		*/
		bool IsHitWall() const
		{
			return m_isHitWall;
		}
		/*!
		* @brief	�R���C�_�[���擾�B
		*/
		CCapsuleCollider* GetCollider()
		{
			return &m_collider;
		}
		/*!
		* @brief	�d�͂��擾�B
		*/
		void SetGravity(float gravity)
		{
			m_gravity = gravity;
		}
		/*!
		* @brief	���̂��擾�B
		*/
		CRigidBody* GetRigidBody()
		{
			return &m_rigidBody;
		}
		/*!
		* @brief	���̂𕨗��G���W������폜�B�B
		*/
		void RemoveRigidBoby();

		//int flag = 0;
		void AddIgnoreCollisionAttr(EnCollisionAttr attr)
		{
			m_ignoreCollisionAttrs |= 1 << attr;
		}
		/*void RemoveIgnoreCollisionAttr(EnCollisionAttr attr)
		{
			m_ignoreCollisionAttrs ~= (m_ignoreCollisionAttrs & 1 << attr);
		}*/
	private:
		CVector3 			m_position = CVector3::Zero;	//���W�B
		bool 				m_isJump = false;				//�W�����v���H
		bool				m_isOnGround = true;			//�n�ʂ̏�ɂ���H
		bool				m_isHitWall = true;
		CCapsuleCollider	m_collider;						//�R���C�_�[�B
		float				m_radius = 0.0f;
		float				m_height = 0.0f;		
		CSphereCollider		m_sphereCollider;
		CRigidBody			m_rigidBody;					//���́B
		int					m_ignoreCollisionAttrs = 2;		//�r�b�g�������Ă��鑮���̃R���W�����Ƃ̂����蔻��𖳎�����B
		float				m_gravity = -9.8f;
		Player* m_player = nullptr;
		Mirror* m_mirror = nullptr;
	};
}