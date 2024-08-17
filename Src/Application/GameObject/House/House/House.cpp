#include "House.h"

void House::Init()
{
	m_objectType = KdGameObject::House;
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

	

	

}

void House::DrawLit()
{
	KdShaderManager::Instance().m_StandardShader.DrawModel(*m_spModel, m_mWorld);


	KdDirect3D::Instance().CreateBlendState

}
