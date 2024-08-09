#include "NormalEnemyAttack.h"
#include"../../../Cleaner/Cleaner.h"
#include"../../../../../main.h"

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

	InHale();

	Math::Vector3 _attackVec = m_playerpos - m_pos;

	std::shared_ptr<Cleaner> _cleaner = m_wpcleaner.lock();

	if (_cleaner)
	{

		Math::Vector3 _cleanerPos = _cleaner->GetPos();

		Math::Vector3 _Vec = _cleanerPos - m_pos;

		//掃除機が吸い込む体制かつ掃除機がゴミの方向を向いているかつ一定以内にいるとき
		if (_cleaner->GetInHale() && m_attackangle < 90.0f && _Vec.Length() < m_range)
		{
			if (_Vec.Length() < m_endrange)
			{
				m_isExpired = true;

			}
			else
			{
				_Vec.Normalize();

				m_pos += _Vec * m_speed;

			}


		}
		else
		{
			if (_attackVec.Length() > m_speed)
			{
				_attackVec.Normalize();

				m_pos += _attackVec * m_speed;
			}
			else
			{
				//m_isExpired = true;
			}
		}

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

void NormalEnemyAttack::InHale()
{
	std::shared_ptr<Cleaner> _cleaner = m_wpcleaner.lock();

	if (_cleaner)
	{

		//プレイヤー座標
		Math::Vector3 _playerPos = _cleaner->GetPos();

		//プレイヤーの前方ベクトル
		Math::Vector3 _playervec = _cleaner->GetMatrix().Forward();
		_playervec.Normalize();

		//敵①攻撃座標
		Math::Vector3 _attackPos = m_pos;

		//プレイヤーと敵①攻撃のベクトル
		Math::Vector3 _attackvec = _attackPos - _playerPos;
		_attackvec.Normalize();

		//ベクトルの内積値から角度を算出
		float _dot = _playervec.Dot(_attackvec);	//内積値を算出

		_dot = std::clamp(_dot, -1.0f, 1.0f);

		//内積値で取得したcos値から２つのベクトルの角度を算出
		m_attackangle = DirectX::XMConvertToDegrees(acos(_dot));


		//printfと同じように使うことができる
		Application::Instance().m_log.AddLog("m_angle=%.2f \n", m_attackangle);



	}
}

void NormalEnemyAttack::SetPram(Math::Vector3 _playerpos, Math::Vector3 _enemypos)
{
	//座標セット
	m_playerpos = _playerpos;
	m_pos = _enemypos;

	m_playerpos.y += 0.2f;		//座標補正(床に埋まらないように)

}
