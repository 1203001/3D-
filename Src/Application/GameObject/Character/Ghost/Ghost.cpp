#include"Ghost.h"
#include"../../../main.h"
#include"../../Camera/TPSCamera/TPSCamera.h"

#include"../Cleaner/Cleaner.h"

#include"../../../Scene/SceneManager.h"


void Ghost::Init()
{
	m_spModel = std::make_shared<KdModelWork>();
	m_spModel->SetModelData("Asset/Models/GhostAnimation/Ghost.gltf");

	//初期のアニメーションをセットする
	m_spAnimator = std::make_shared<KdAnimator>();
	m_spAnimator->SetAnimation(m_spModel->GetData()->GetAnimation("GhostArmature|ghost_idle"),true);

	//m_pCollider = std::make_unique<KdCollider>();
	//m_pCollider->RegisterCollisionShape("Ghost", m_spModel, KdCollider::TypeGround);

	m_pDebugWire = std::make_unique<KdDebugWireFrame>();



}

void Ghost::Update()
{
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


	Math::Matrix rotMat;
	if (m_isTPS == true)
	{
		//TPS(背面カメラ)
		moveVec.Normalize();

		rotMat = camRotYMat;

	}
	else
	{
		//TPV
		//移動（回転処理）
		m_isAttack = false;
		if (moveFlg == true)
		{
			m_isAttack = true;

			//正規化（長さを１にする）
			moveVec.Normalize();

			//今キャラが向いている方向
			//①キャラの回転行列を作成
			Math::Matrix nowRotMat = Math::Matrix::CreateRotationY(DirectX::XMConvertToRadians(m_angle));
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

		//回転行列
		rotMat = Math::Matrix::CreateRotationY(DirectX::XMConvertToRadians(m_angle));

	}


	//おばけと掃除機のベクトルを求める
	/*std::shared_ptr<Cleaner> _cleaner = m_wpcleaner.lock();
	if (_cleaner)
	{
		Math::Vector3 _cleanerPos = _cleaner->GetPos();
		_cleanerPos.y += 0.3f;

		Math::Vector3 _vec = _cleanerPos - m_pos;

		if (_vec.Length() > m_speed)
		{
			_vec.Normalize();

			m_pos += _vec * m_speed;
		}

	}*/

	//座標行列
	Math::Matrix _scaleMat = Math::Matrix::CreateScale(3.0f);
	m_pos += moveVec * 0.1f;
	Math::Matrix transMat = Math::Matrix::CreateTranslation(m_pos);
	//SRT
	m_mWorld = _scaleMat * rotMat * transMat;

	//printfと同じように使うことができる
	//Application::Instance().m_log.AddLog("m_angle=%.2f ang=%.2f\n", m_angle, ang);

	//一時的に見やすくするためのポイントライト
	KdShaderManager::Instance().WorkAmbientController().AddPointLight({ 10,10,10 }, 15, m_pos);

}

void Ghost::PostUpdate()
{
	
	//アニメーションの更新
	m_spAnimator->AdvanceTime(m_spModel->WorkNodes(),0.5f);
	m_spModel->CalcNodeMatrices();

	//早期リターン
	if (m_isAttack == false)return;
	KdCollider::SphereInfo atksphere;
	//球判定用の変数を作成
	//球の中心点を設定
	atksphere.m_sphere.Center = m_pos;
	atksphere.m_sphere.Center.y += 0.5f;

	//球の半径を設定
	atksphere.m_sphere.Radius = 2.0f;
	//当たり判定をしたいタイプを設定
	atksphere.m_type = KdCollider::TypeDamage;

	//デバック用
	//m_pDebugWire->AddDebugSphere(atksphere.m_sphere.Center, atksphere.m_sphere.Radius);


	//当たり判定！！！！！！！！！！！！！！！！！！！
	for (auto& obj : SceneManager::Instance().GetObjList())
	{
		//当たり判定
		if (obj->Intersects(atksphere, nullptr))
		{
			//敵確定
			obj->OnHit();
			//OnHit();

		}
	}

	

}

void Ghost::DrawLit()
{
	Math::Color _color = { 1.0f,1.0f,1.0f,1.0f };
	KdShaderManager::Instance().m_StandardShader.DrawModel(*m_spModel, m_mWorld, _color);
}




