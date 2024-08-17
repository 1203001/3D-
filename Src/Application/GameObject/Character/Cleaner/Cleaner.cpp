#include "Cleaner.h"
#include"../../Camera/TPSCamera/TPSCamera.h"
#include"../../House/Gomi/Gomi.h"
#include"../../../Scene/SceneManager.h"

void Cleaner::Init()
{
	m_spModel = std::make_shared<KdModelWork>();
	m_spModel->SetModelData("Asset/Models/CleanerAnimation/cleaner.gltf");
	
	//初期のアニメーションをセットする
	m_spAnimator = std::make_shared<KdAnimator>();

	Math::Matrix _scaleMat = Math::Matrix::CreateScale(3.0f);
	Math::Matrix _transMat = Math::Matrix::CreateTranslation(m_pos);
	m_mWorld = _scaleMat * _transMat;

	m_pCollider = std::make_unique<KdCollider>();
	m_pCollider->RegisterCollisionShape("Cleaner", m_spModel, KdCollider::TypeGround);

	//デバッグ用
	m_pDebugWire = std::make_unique<KdDebugWireFrame>();
}

void Cleaner::Update()
{
	//攻撃
	if (GetAsyncKeyState('Q') & 0x8000)
	{
		if (m_spAnimator->IsAnimationEnd())
		{
			if (!m_isinhale)
			{
				m_spAnimator->SetAnimation(m_spModel->GetData()->GetAnimation("Attack"), false);
			}
		}
	}

	//吸い込む構え
	if (GetAsyncKeyState('E') & 0x8000)
	{
		if (m_spAnimator->IsAnimationEnd())
		{
			if (!m_isinhale)
			{
				m_isinhale = true;
				m_spAnimator->SetAnimation(m_spModel->GetData()->GetAnimation("Inhale"), false);
			}
		}
	}

	//吸い込み終了
	if (GetAsyncKeyState('R') & 0x8000)
	{
		if (m_spAnimator->IsAnimationEnd())
		{
			if (m_isinhale)
			{
				m_isinhale = false;
				m_spAnimator->SetAnimation(m_spModel->GetData()->GetAnimation("EndInhale"), false);
			}
		}
	}

	

	m_pos = GetPos();
	m_movevec = {};

	//カメラのY回転行列を取得
	Math::Matrix camRotYMat;
	if (m_wpcamera.expired() == false)
	{
		camRotYMat = m_wpcamera.lock()->GetRotationYMatrix();
	}

	bool moveFlg = false;	//移動している状態かどうか

	if (GetAsyncKeyState('W') & 0x8000)
	{
		m_movevec += Math::Vector3::TransformNormal({ 0,0,1 }, camRotYMat);
		moveFlg = true;

	}
	if (GetAsyncKeyState('A') & 0x8000)
	{
		m_movevec += Math::Vector3::TransformNormal({ -1,0,0 }, camRotYMat);
		moveFlg = true;
	}
	if (GetAsyncKeyState('S') & 0x8000)
	{
		m_movevec += Math::Vector3::TransformNormal({ 0,0,-1 }, camRotYMat);
		moveFlg = true;
	}
	if (GetAsyncKeyState('D') & 0x8000)
	{
		m_movevec += Math::Vector3::TransformNormal({ 1,0,0 }, camRotYMat);
		moveFlg = true;
	}

	//TPV
	//移動（回転処理）
	if (moveFlg == true)
	{

		//正規化（長さを１にする）
		m_movevec.Normalize();

		//今キャラが向いている方向
		//①キャラの回転行列を作成														
		Math::Matrix nowRotMat = Math::Matrix::CreateRotationY(DirectX::XMConvertToRadians(m_angle));
		//②現在の方向を求める
		Math::Vector3 nowVec = Math::Vector3::TransformNormal(Math::Vector3(0, 0, 1), nowRotMat);
		nowVec.Normalize();

		//向きたい方向
		Math::Vector3 toVec = m_movevec;
		toVec.Normalize();

		//内積を使って回転する角度を求める
		//ベクトルA*ベクトルB*コサインθ(ベクトルAとベクトルBのなす角）
		//		1	*	1	*コサインθ
		float d = nowVec.Dot(toVec);
		//dの中にはコサインθが入っている

		//丸め誤差の都合上「１」を超える可能性があるためクランプ（遮断）する
		//丸め誤差...小数点以下を省略した際に生じる誤差
		d = std::clamp(d, -1.0f, 1.0f);

		//角度求める（でも残念ながらラジアン角）
		float ang = DirectX::XMConvertToDegrees(acos(d));

		//内積から角度を求めて少しでも角度が変わったら
		//ゆっくり回転するようにする
		if (ang >= 0.1f)
		{
			if (ang > 5)
			{
				ang = 5.0f;
			}

			//外積を求める（どっちに回転するのか調べる）
			Math::Vector3 c = toVec.Cross(nowVec);
			if (c.y >= 0)
			{
				//右回転
				m_angle -= ang;
				if (m_angle < 0)
				{
					m_angle += 360;
				}
			}
			else
			{
				//左回転
				m_angle += ang;
				if (m_angle >= 360.0f)
				{
					m_angle -= 360;
				}
			}

		}
	}


	//回転行列																		↓座標補正
	//Math::Matrix _rotMat = Math::Matrix::CreateRotationY(DirectX::XMConvertToRadians(m_angle));

	//m_pos += m_movevec * 0.1f;

	//Math::Matrix _scaleMat = Math::Matrix::CreateScale(3.0f);
	//Math::Matrix _transMat = Math::Matrix::CreateTranslation(m_pos);
	//m_mWorld = _scaleMat * _rotMat * _transMat;


	if (m_isinhale)
	{

		Math::Vector3 _effectpos = m_pos;
		_effectpos.y += 2;


		if (m_effectframe <= 0)
		{

			//吸い込みエフェクトを次いつ出すか
			m_effectframe = m_EffectTime;


			//吸い込みエフェクト
			m_wpinhale = KdEffekseerManager::GetInstance().Play("smoke.efkefc", _effectpos, { 0.0f,0.0f,0.0f }, 1.0f, 1.0f, false);


		}

		m_effectframe--;

		if (m_wpinhale.expired() == false)
		{
			m_wpinhale.lock()->SetPos(_effectpos);
			m_wpinhale.lock()->SetRotation({ 0.0f,1.0f,0.0f }, DirectX::XMConvertToRadians(m_angle));

		}


	}
	else
	{
		KdEffekseerManager::GetInstance().StopAllEffect();
		m_effectframe = 0;
	}

	//プレイヤーの座標更新
	m_pos += m_movevec * 0.1f;
	m_pos.y += m_gravity;

	Sphere();

	
}

void Cleaner::PostUpdate()
{

	Math::Matrix _movefloorMat = Math::Matrix::CreateTranslation(m_beforfloorPos);

	//動く床に当たっていた時の処理
	if (m_ishitmovefloor)
	{
		//動く床の動く前の逆行列
		Math::Matrix _inverseMatrix = DirectX::XMMatrixInverse(nullptr, _movefloorMat);

		//動く床から見たプレイヤーの座標行列
		Math::Matrix _playerMat = Math::Matrix::CreateTranslation(m_pos) * _inverseMatrix;

		//動く床の動いた後の行列
		Math::Matrix _afterMoveGroundMat = Math::Matrix::CreateTranslation(m_wpgameobject.lock()->GetMatrix().Translation());

		//座標を確定
		m_pos = _afterMoveGroundMat.Translation() + _playerMat.Translation();
	}


	Math::Matrix _rotMat = Math::Matrix::CreateRotationY(DirectX::XMConvertToRadians(m_angle));

	

	Math::Matrix _scaleMat = Math::Matrix::CreateScale(3.0f);
	Math::Matrix _transMat = Math::Matrix::CreateTranslation(m_pos);
	m_mWorld = _scaleMat * _rotMat * _transMat;

	//アニメーションの更新
	if (!m_spAnimator->IsAnimationEnd())
	{
		m_spAnimator->AdvanceTime(m_spModel->WorkNodes());
		m_spModel->CalcNodeMatrices();
	}

}

void Cleaner::DrawLit()
{
	KdShaderManager::Instance().m_StandardShader.DrawModel(*m_spModel, m_mWorld);
}

void Cleaner::Sphere()
{
	//==============================================================
	//球判定
	//==============================================================

	//球判定用の変数を作成
	KdCollider::SphereInfo sphere;
	//球の中心点を設定
	sphere.m_sphere.Center = m_pos + Math::Vector3(0, 0.3f, 0);
	
	//球の半径を設定
	sphere.m_sphere.Radius = 0.5f;
	//当たり判定をしたいタイプを設定
	sphere.m_type = KdCollider::TypeGround;

	//デバック用
	m_pDebugWire->AddDebugSphere(sphere.m_sphere.Center, sphere.m_sphere.Radius);

	//球に当たったオブジェクトの情報を格納
	std::list<KdCollider::CollisionResult> retSphereList;
	std::vector<std::weak_ptr<KdGameObject>> _gameobject;

	//当たり判定！！！！！！！！！！！！！！！！！！！
	for (auto& obj : SceneManager::Instance().GetObjList())
	{


		if (obj->GetObjectType() == KdGameObject::Movefloor || obj->GetObjectType() == KdGameObject::House)
		{
			//当たり判定
			if (obj->Intersects(sphere, &retSphereList))
			{
				_gameobject.push_back(obj);

			}
		}
	}

	//球に当たったリストから一番近いオブジェクトを検出
	float maxOverLap = 0;			//はみ出た球の長さ
	Math::Vector3 hitDir;	//当たった方向
	bool isHit = false;			//当たっていたらtrue
	int _cnt = 0;

	for (auto& ret : retSphereList)
	{
		//球にめりこんで、オーバーした長さが一番長いものを探す
		if (maxOverLap < ret.m_overlapDistance)
		{
			maxOverLap = ret.m_overlapDistance;
			hitDir = ret.m_hitDir;
			isHit = true;
			m_wpgameobject = _gameobject[_cnt];
		}

		_cnt++;

	}

	if (isHit)
	{
		//zへの押し返し無効
		hitDir.z = 0;
		//正規化(長さを1にする)
		//方向は絶対長さ１
		hitDir.Normalize();

		//動く前の座標
		m_beforfloorPos = m_wpgameobject.lock()->GetPos();

		//動く床に当たっているときtrueにする
		m_ishitmovefloor = true;

		//地面に当たっている
		m_pos += hitDir * maxOverLap;
	}
	else
	{
		m_ishitmovefloor = false;
	}

}

