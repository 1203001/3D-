#include "EnemyBase.h"

void EnemyBase::Init()
{

}

void EnemyBase::Update()
{

}

void EnemyBase::DrawLit()
{
	KdShaderManager::Instance().m_StandardShader.DrawModel(*m_spModel, m_mWorld);
}

void EnemyBase::SetTarget(const std::shared_ptr<KdGameObject>& target)
{
	if (!target) { return; }

	m_wpTarget = target;
}
