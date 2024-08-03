#include "Ground.h"

void Ground::Init()
{
	m_model = std::make_shared<KdModelData>();
	m_model->Load("Asset/Models/Ground/Ground.gltf");
	//m_model->Load("Asset/Models/Map/Map.gltf");

	Math::Matrix scaleMat;
	scaleMat = Math::Matrix::CreateScale(100);
	m_mWorld = scaleMat;

}

void Ground::DrawLit()
{
	//KdShaderManager::Instance().m_StandardShader.DrawModel(*m_model,m_mWorld);
}
