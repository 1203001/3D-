#include "Gomi.h"
#include"../../Character/Cleaner/Cleaner.h"
#include"../../../Scene/SceneManager.h"

#include"../../../main.h"

void Gomi::Init()
{
	m_spModel = std::make_shared<KdModelData>();
	m_spModel->Load("Asset/Models/House/Gomi/can.gltf");

	Math::Matrix _scaleMat = Math::Matrix::CreateScale(1.0f);
	Math::Matrix _transMat = Math::Matrix::CreateTranslation(m_pos);
	m_mWorld = _scaleMat * _transMat;

	//デバッグ用
	m_pDebugWire = std::make_unique<KdDebugWireFrame>();
}

void Gomi::Update()
{

	InHale();	//吸い込み処理


	std::shared_ptr<Cleaner> _cleaner = m_wpcleaner.lock();

	if (_cleaner)
	{

		Math::Vector3 _cleanerPos = _cleaner->GetPos();

		//一時的な座標補正(山本先生の授業を受けたら変える場所)
		_cleanerPos.y += 2.0f;

		Math::Vector3 _Vec = _cleanerPos - m_pos;

		//掃除機が吸い込む体制かつ掃除機がゴミの方向を向いているかつ一定以内にいるとき
		if (_cleaner->GetInHale()&& m_gomiangle < 25.0f && _Vec.Length() < m_range)
		{

			//ゴミの状態
			m_SituationType = TypeSuikomi;

			if (_Vec.Length() < m_endrange)
			{
			
				//吸ったときのエフェクトの位置
				Math::Vector3 _endsmokePos = m_pos;
				_endsmokePos.y += 2.0f;

				//吸ったときのエフェクト
				KdEffekseerManager::GetInstance().Play("endsmoke.efkefc", _endsmokePos, { 0.0f,0.0f,0.0f }, 0.5f, 1.0f, false);


				m_isExpired = true;

			}
			else
			{
				
				_Vec.Normalize();

				m_pos += _Vec * m_speed;

			}


		}
		else if(m_SituationType==TypeSuikomi)
		{
			//ゴミの状態
			m_SituationType = TypeNotSuikomi;
		}
		
		
	}

	if (m_SituationType == TypeNotSuikomi)
	{
		if (m_pos.y > m_hitPosY)
		{
			//ゴミの状態
			m_SituationType = TypeAir;
			
			m_gravity = 0.1f;
			

		}
	}

	//重力処理
	if (m_SituationType == TypeAir)
	{
		m_pos.y -= m_gravity;
		m_gravity += m_gravityPow;
	}

	Math::Matrix _scaleMat = Math::Matrix::CreateScale(1.0f);
	Math::Matrix _transMat = Math::Matrix::CreateTranslation(m_pos);
	m_mWorld = _scaleMat * _transMat;

	Sphere();

}

void Gomi::DrawLit()
{

	KdShaderManager::Instance().ChangeRasterizerState(KdRasterizerState::CullNone);

	//ゴミ画像
	KdShaderManager::Instance().m_StandardShader.DrawModel(*m_spModel, m_mWorld);


	KdShaderManager::Instance().ChangeRasterizerState(KdRasterizerState::CullBack);

}

void Gomi::InHale()
{
	std::shared_ptr<Cleaner> _cleaner = m_wpcleaner.lock();

	if (_cleaner)
	{

		//プレイヤー座標
		Math::Vector3 _playerPos = _cleaner->GetPos();

		//プレイヤーの前方ベクトル
		Math::Vector3 _playervec = _cleaner->GetMatrix().Backward();
		_playervec.Normalize();


		//ゴミ座標
		Math::Vector3 _gomiPos = m_pos;

		//プレイヤーとゴミのベクトル
		Math::Vector3 _gomivec = _gomiPos - _playerPos;
		_gomivec.Normalize();

		//ベクトルの内積値から角度を算出
		float _dot = _playervec.Dot(_gomivec);	//内積値を算出

		_dot = std::clamp(_dot, -1.0f, 1.0f);

		//内積値で取得したcos値から２つのベクトルの角度を算出
		m_gomiangle = DirectX::XMConvertToDegrees(acos(_dot));


		//printfと同じように使うことができる
		//Application::Instance().m_log.AddLog("m_angle=%.2f \n", m_angle);

	}
		

	
}

void Gomi::Sphere()
{

	//==============================================================
	//球判定
	//==============================================================

	//球判定用の変数を作成
	KdCollider::SphereInfo sphere;
	//球の中心点を設定
	sphere.m_sphere.Center = m_pos + Math::Vector3(0, 0.5f, 0.2f);
	/*sphere.m_sphere.Center = m_pos;
	sphere.m_sphere.Center.y += 0.5f;*/

	//球の半径を設定
	sphere.m_sphere.Radius = 0.6f;
	//当たり判定をしたいタイプを設定
	sphere.m_type = KdCollider::TypeGround;

	//デバック用
	m_pDebugWire->AddDebugSphere(sphere.m_sphere.Center, sphere.m_sphere.Radius);

	//球に当たったオブジェクトの情報を格納
	std::list<KdCollider::CollisionResult> retSphereList;

	//当たり判定！！！！！！！！！！！！！！！！！！！
	for (auto& obj : SceneManager::Instance().GetObjList())
	{
		//自分だったら処理を飛ばす
		if (obj.get() == this)
		{
			continue;
		}

		obj->Intersects(sphere, &retSphereList);
	}

	//球に当たったリストから一番近いオブジェクトを検出
	float maxOverLap = 0;			//はみ出た球の長さ
	Math::Vector3 hitDir;	//当たった方向
	bool isHit = false;			//当たっていたらtrue
	for (auto& ret : retSphereList)
	{
		//球にめりこんで、オーバーした長さが一番長いものを探す
		if (maxOverLap < ret.m_overlapDistance)
		{
			maxOverLap = ret.m_overlapDistance;
			hitDir = ret.m_hitDir;
			isHit = true;

			//値保存
			m_hitPosY = ret.m_hitPos.y;

		}
	}

	if (isHit)
	{

		//ゴミの状態
		if (m_SituationType == TypeAir && m_gravity > m_endgravity)
		{
			
			m_gravity *= -1;
			m_gravity += m_endgravity;
			
		}
		else
		{
			m_SituationType = TypeGround;
			//重力を無くす
			m_gravity = 0;
		}

		

		//zへの押し返し無効
		hitDir.z = 0;
		//正規化(長さを1にする)
		//方向は絶対長さ１
		hitDir.Normalize();

		//地面に当たっている
		m_pos += hitDir * maxOverLap;
	}


}

