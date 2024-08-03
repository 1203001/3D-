#include "Cleaner.h"

void Cleaner::Init()
{
	m_spModel = std::make_shared<KdModelWork>();
	m_spModel->SetModelData("Asset/Models/CleanerAnimation/cleaner.gltf");

	//初期のアニメーションをセットする
	m_spAnimator = std::make_shared<KdAnimator>();

	Math::Matrix _scaleMat = Math::Matrix::CreateScale(3.0f);
	Math::Matrix _transMat = Math::Matrix::CreateTranslation(3, 0, 0);
	m_mWorld = _scaleMat * _transMat;

	m_pCollider = std::make_unique<KdCollider>();
	m_pCollider->RegisterCollisionShape("Cleaner", m_spModel, KdCollider::TypeGround);


}

void Cleaner::Update()
{

	if (GetAsyncKeyState('Q') & 0x8000)
	{
		if (m_spAnimator->IsAnimationEnd())
		{
			m_spAnimator->SetAnimation(m_spModel->GetData()->GetAnimation("Attack"), false);
		}
	}


}

void Cleaner::PostUpdate()
{
	//アニメーションの更新
	if (!m_spAnimator->IsAnimationEnd())
	{
		m_spAnimator->AdvanceTime(m_spModel->WorkNodes());
		m_spModel->CalcNodeMatrices();
	}

}

void Cleaner::DrawLit()
{
	KdShaderManager::Instance().m_StandardShader.DrawModel(*m_spModel, m_mWorld);
}
