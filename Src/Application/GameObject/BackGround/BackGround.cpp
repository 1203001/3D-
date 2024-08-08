#include "BackGround.h"

void BackGround::DrawUnLit()
{
	KdShaderManager::Instance().ChangeRasterizerState(KdRasterizerState::CullNone);

	KdShaderManager::Instance().m_StandardShader.DrawModel(*m_spModel, m_mWorld);

	KdShaderManager::Instance().ChangeRasterizerState(KdRasterizerState::CullBack);
}

void BackGround::Init()
{
	m_spModel = std::make_shared<KdModelData>();
	m_spModel->Load("Asset/Models/SkyBox/skyBox.gltf");

	m_pos = { 30.0f,100.0f,0.0f };

	Math::Matrix Scale = Math::Matrix::CreateScale(600.0f);
	Math::Matrix Trans = Math::Matrix::CreateTranslation(m_pos);
	m_mWorld = Scale * Trans;
}