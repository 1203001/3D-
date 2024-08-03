#include "FloorLamp.h"

void Candle::Init()
{
	m_spModel = std::make_shared<KdModelData>();
	m_spModel->Load("Asset/Models/House/FloorLamp/FloorLamp.gltf");

	Math::Matrix _scaleMat = Math::Matrix::CreateScale(4.0f);
	Math::Matrix _transMat = Math::Matrix::CreateTranslation(m_pos);
	m_mWorld = _scaleMat * _transMat;

}

void Candle::Update()
{
	//ポイントライト
	KdShaderManager::Instance().WorkAmbientController().AddPointLight({ 1,1,1 }, 10, m_pos);
}

void Candle::DrawLit()
{
	KdShaderManager::Instance().m_StandardShader.DrawModel(*m_spModel, m_mWorld);
}
