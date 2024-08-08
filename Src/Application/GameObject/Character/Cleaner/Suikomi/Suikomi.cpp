#include "Suikomi.h"
#include"../Cleaner.h"

void Suikomi::Init()
{

}

void Suikomi::Update()
{

}

void Suikomi::Inhale()
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
