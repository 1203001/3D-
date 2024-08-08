#include "NormalEnemyAttack.h"

void NormalEnemyAttack::Init()
{

	m_spModel = std::make_shared<KdModelData>();
	m_spModel->Load("Asset/Models/House/Gomi/can.gltf");

	m_pos = { -2,3,5 };
	Math::Matrix _transMat = Math::Matrix::CreateTranslation(m_pos);

	m_mWorld = _transMat;

}

void NormalEnemyAttack::Update()
{

	Math::Vector3 _attackVec = m_playerpos - m_pos;


	if (_attackVec.Length() > m_speed)
	{
		_attackVec.Normalize();

		m_pos += _attackVec * m_speed;
	}
	else
	{
		//m_isExpired = true;
	}


	Math::Matrix _transMat = Math::Matrix::CreateTranslation(m_pos);
	m_mWorld = _transMat;

}

void NormalEnemyAttack::DrawLit()
{

	KdShaderManager::Instance().ChangeRasterizerState(KdRasterizerState::CullNone);

	//ゴミ画像
	KdShaderManager::Instance().m_StandardShader.DrawModel(*m_spModel, m_mWorld);

	KdShaderManager::Instance().ChangeRasterizerState(KdRasterizerState::CullBack);

}

void NormalEnemyAttack::SetPram(Math::Vector3 _playerpos, Math::Vector3 _enemypos)
{
	//座標セット
	m_playerpos = _playerpos;
	m_pos = _enemypos;

	m_playerpos.y += 0.2f;		//座標補正(床に埋まらないように)

}
