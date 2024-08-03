#include "MoveFloor.h"

void MoveFloor::Init()
{
	m_spModel = std::make_shared<KdModelData>();
	m_spModel->Load("Asset/Models/House/House/house.gltf");

	m_pos = { -50,0,0 };


	Math::Matrix _scaleMat = Math::Matrix::CreateScale(3.0f);
	Math::Matrix _transMat = Math::Matrix::CreateTranslation(m_pos);
	m_mWorld = _scaleMat * _transMat;

}

void MoveFloor::Update()
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

void MoveFloor::DrawLit()
{
	KdShaderManager::Instance().m_StandardShader.DrawModel(*m_spModel, m_mWorld);
}
