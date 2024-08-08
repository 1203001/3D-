#include "Cleaner.h"
#include"../../Camera/TPSCamera/TPSCamera.h"
#include"../../House/Gomi/Gomi.h"

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

	//カメラのY回転行列を取得
	Math::Matrix camRotYMat;
	if (m_wpcamera.expired() == false)
	{
		camRotYMat = m_wpcamera.lock()->GetRotationYMatrix();
	}

	Math::Vector3 moveVec;	//移動方向を格納
	bool moveFlg = false;	//移動している状態かどうか

	if (GetAsyncKeyState('W') & 0x8000)
	{
		moveVec += Math::Vector3::TransformNormal({ 0,0,1 }, camRotYMat);
		moveFlg = true;

	}
	if (GetAsyncKeyState('A') & 0x8000)
	{
		moveVec += Math::Vector3::TransformNormal({ -1,0,0 }, camRotYMat);
		moveFlg = true;
	}
	if (GetAsyncKeyState('S') & 0x8000)
	{
		moveVec += Math::Vector3::TransformNormal({ 0,0,-1 }, camRotYMat);
		moveFlg = true;
	}
	if (GetAsyncKeyState('D') & 0x8000)
	{
		moveVec += Math::Vector3::TransformNormal({ 1,0,0 }, camRotYMat);
		moveFlg = true;
	}


	Math::Matrix _rotMat;



	//TPV
	//移動（回転処理）
	if (moveFlg == true)
	{

		//正規化（長さを１にする）
		moveVec.Normalize();

		//今キャラが向いている方向
		//①キャラの回転行列を作成																	↓座標補正
		Math::Matrix nowRotMat = Math::Matrix::CreateRotationY(DirectX::XMConvertToRadians(m_angle + 180));
		//②現在の方向を求める
		Math::Vector3 nowVec = Math::Vector3::TransformNormal(Math::Vector3(0, 0, 1), nowRotMat);
		nowVec.Normalize();

		//向きたい方向
		Math::Vector3 toVec = moveVec;
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
	_rotMat = Math::Matrix::CreateRotationY(DirectX::XMConvertToRadians(m_angle));

	m_pos += moveVec * 0.1f;

	Math::Matrix _scaleMat = Math::Matrix::CreateScale(3.0f);
	Math::Matrix _transMat = Math::Matrix::CreateTranslation(m_pos);
	m_mWorld = _scaleMat * _rotMat * _transMat;

}

void Cleaner::PostUpdate()
{
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

