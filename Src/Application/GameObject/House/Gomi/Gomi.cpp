#include "Gomi.h"
#include"../../Character/Cleaner/Cleaner.h"
#include"../../../main.h"

void Gomi::Init()
{
	m_spModel = std::make_shared<KdModelData>();
	m_spModel->Load("Asset/Models/House/Gomi/can.gltf");

	Math::Matrix _scaleMat = Math::Matrix::CreateScale(1.0f);
	Math::Matrix _transMat = Math::Matrix::CreateTranslation(m_pos);
	m_mWorld = _scaleMat * _transMat;

}

void Gomi::Update()
{

	std::shared_ptr<Cleaner> _cleaner = m_wpcleaner.lock();

	if(_cleaner)
	{
		Inhale();


		if (_cleaner->GetInHale())
		{

			if (m_angle < 90.0f)
			{
				Math::Vector3 _cleanerPos = _cleaner->GetPos();

				Math::Vector3 _Vec = _cleanerPos - m_pos;


				if (_Vec.Length() > m_range)
				{
					_Vec.Normalize();

					m_pos += _Vec * m_speed;
				}
				else
				{
					m_isExpired = true;
				}

			}
		}

	}

	Math::Matrix _scaleMat = Math::Matrix::CreateScale(1.0f);
	Math::Matrix _transMat = Math::Matrix::CreateTranslation(m_pos);
	m_mWorld = _scaleMat * _transMat;

}

void Gomi::DrawLit()
{

	KdShaderManager::Instance().ChangeRasterizerState(KdRasterizerState::CullNone);

	//ゴミ画像
	KdShaderManager::Instance().m_StandardShader.DrawModel(*m_spModel, m_mWorld);


	KdShaderManager::Instance().ChangeRasterizerState(KdRasterizerState::CullBack);

}

void Gomi::Inhale()
{
	std::shared_ptr<Cleaner> _cleaner = m_wpcleaner.lock();

	if (_cleaner)
	{
		//プレイヤー座標
		Math::Vector3 _playerPos = _cleaner->GetPos();

		//プレイヤーの前方ベクトル
		Math::Vector3 _playervec = _cleaner->GetMatrix().Forward();
		_playervec.Normalize();

		//プレイヤーとゴミのベクトル
		Math::Vector3 _gomivec = m_pos - _playerPos;
		_gomivec.Normalize();

		//ベクトルの内積値から角度を算出
		float _dot = _playervec.Dot(_gomivec);	//内積値を算出
		
		_dot = std::clamp(_dot, -1.0f, 1.0f);

		//内積値で取得したcos値から２つのベクトルの角度を算出
		m_angle = DirectX::XMConvertToDegrees(acos(_dot));


		//printfと同じように使うことができる
		//Application::Instance().m_log.AddLog("m_angle=%.2f \n", m_angle);

	}

}
