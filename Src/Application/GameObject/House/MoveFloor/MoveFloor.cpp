#include "MoveFloor.h"

void MoveFloor::Init()
{

	m_objectType = KdGameObject::Movefloor;

	m_spModel = std::make_shared<KdModelData>();
	m_spModel->Load("Asset/Models/House/MoveFloor/movefloor.gltf");

	m_pos = { 3.0f,0.0f,3.0f };

	Math::Matrix _scaleMat = Math::Matrix::CreateScale(3.0f);
	Math::Matrix _transMat = Math::Matrix::CreateTranslation(m_pos);
	m_mWorld = _scaleMat * _transMat;

	m_pCollider = std::make_unique<KdCollider>();
	m_pCollider->RegisterCollisionShape("MoveFloor", m_spModel, KdCollider::TypeGround);

}

void MoveFloor::Update()
{

	//一定数動いたら反対側に動かす
	if (m_move.y > 5.0f)
	{
		m_move.y = 0;
		m_speed *= -1;
		m_moveframe = 60;
	}
	else if (m_move.y < 0.0f)
	{
		m_move.y = 0;
		m_speed *= -1;
		m_moveframe = 60;
	}

	if (m_moveframe <= 0)
	{
		m_move.y += 0.1f;
		m_pos.x += m_speed;
		m_pos.y += m_speed;

	}

	m_moveframe--;


	Math::Matrix _scaleMat = Math::Matrix::CreateScale(3.0f);
	Math::Matrix _transMat = Math::Matrix::CreateTranslation(m_pos);
	m_mWorld = _scaleMat * _transMat;

}

void MoveFloor::DrawLit()
{
	HouseBase::DrawLit();
}
