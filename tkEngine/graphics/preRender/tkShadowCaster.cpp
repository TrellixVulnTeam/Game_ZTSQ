/*!
 * @brief	シャドウキャスター。
 */
#include "tkEngine/tkEnginePreCompile.h"
#include "tkEngine/graphics/preRender/tkShadowCaster.h"
#include "Game/Mirror.h"
namespace tkEngine{

////////////////////////////////////////////////////////////////
// シャドウキャスター(スキンモデル版)
////////////////////////////////////////////////////////////////
	CShadowCaster_SkinModel::CShadowCaster_SkinModel() :
		m_skinModel(nullptr)
	{
	}
	CShadowCaster_SkinModel::~CShadowCaster_SkinModel()
	{
	}
	void CShadowCaster_SkinModel::Create(CSkinModel* model)
	{
		m_skinModel = model;
	}
	void CShadowCaster_SkinModel::Render(CRenderContext& renderContext, const CMatrix& mLVP)
	{
		if (!m_skinModel) {
			return;
		}
		if (m_mirror == NULL)
		{
			m_mirror = FindGO<Mirror>("Mirror");
		}
		//今井 引数を追加した
		m_skinModel->Draw(renderContext, 
			mLVP, 
			CMatrix::Identity,
			CMatrix::Identity, 
			CMatrix::Identity);
	}
}