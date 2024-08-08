#include "House.h"

void House::Init()
{
	m_spModel = std::make_shared<KdModelData>();
	m_spModel->Load("Asset/Models/House/House/house.gltf");

	m_pCollider = std::make_unique<KdCollider>();
	m_pCollider->RegisterCollisionShape("House", m_spModel, KdCollider::TypeGround);

	Math::Matrix _scaleMat = Math::Matrix::CreateScale(3.0f);
	Math::Matrix _transMat = Math::Matrix::CreateTranslation(m_pos);
	m_mWorld = _scaleMat * _transMat;

}

void House::Update()
{

	////一定数動いたら反対側に動かす
	//if (m_move > 5.0f)
	//{
	//	m_move = 0.0f;
	//	m_speed *= -1;
	//}

	//m_move += 0.1f;

	//m_pos.x += m_speed;

	

}

void House::DrawLit()
{
	KdShaderManager::Instance().m_StandardShader.DrawModel(*m_spModel, m_mWorld);
}
