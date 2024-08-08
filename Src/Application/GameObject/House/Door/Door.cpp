#include "Door.h"
#include"../../Character/Ghost/Ghost.h"
#include"../../../main.h"

void Door::Init()
{

	m_spModel = std::make_shared<KdModelWork>();
	m_spModel->SetModelData("Asset/Models/House/Door/door.gltf");

	m_spkeyTex = std::make_shared<KdTexture>();
	m_spkeyTex->Load("Asset/Textures/UI/Key/Zkey.png");

	//初期のアニメーションをセットする
	m_spAnimator = std::make_shared<KdAnimator>();

	m_pCollider = std::make_unique<KdCollider>();
	m_pCollider->RegisterCollisionShape("Door", m_spModel, KdCollider::TypeGround);

	Math::Matrix _scaleMat = Math::Matrix::CreateScale({ 3.1f,3.0f,3.5f });
	Math::Matrix _rotYMat = Math::Matrix::CreateRotationY(DirectX::XMConvertToRadians(270.0f));
	Math::Matrix _transMat = Math::Matrix::CreateTranslation(m_pos);

	m_mWorld = _scaleMat * _rotYMat * _transMat;

}

void Door::Update()
{

	std::shared_ptr<Ghost> _ghost = m_wpghost.lock();

	if (_ghost)
	{

		DoorAngle();

		
		m_isdoor = false;	//ドアを開けれないようにする

		if (m_angle < 90.0f)
		{
			Math::Vector3 _ghostPos = _ghost->GetPos();

			Math::Vector3 _vec = m_pos - _ghostPos;
			//Math::Vector3 _vec = _ghostPos - m_pos;
			//_vec.Normalize();

			if (_vec.Length() < 8.0f)
			{
				m_isdoor = true;	//ドアを開けれるようにする


			}

		}

	}



	if (GetAsyncKeyState('Z') & 0x8000)
	{
		if (m_spAnimator->IsAnimationEnd())
		{
			if (m_isdoor)
			{
				if (!m_isopen)
				{
					m_isopen = true;
					m_spAnimator->SetAnimation(m_spModel->GetData()->GetAnimation("CloseDoor"), false);
				}
				else if (m_isopen)
				{
					m_isopen = false;
					m_spAnimator->SetAnimation(m_spModel->GetData()->GetAnimation("OpenDoor"), false);
				}
			}
		}
	}

	

}

void Door::PostUpdate()
{
	//アニメーションの更新
	if (!m_spAnimator->IsAnimationEnd())
	{
		m_spAnimator->AdvanceTime(m_spModel->WorkNodes());
		m_spModel->CalcNodeMatrices();
	}
}

void Door::DrawLit()
{
	//ドア画像
	KdShaderManager::Instance().m_StandardShader.DrawModel(*m_spModel, m_mWorld);
}

void Door::DrawSprite()
{
	if (m_isdoor)
	{
		KdShaderManager::Instance().m_spriteShader.DrawTex(m_spkeyTex, -200, 100);
	}
}

void Door::DoorAngle()
{
	std::shared_ptr<Ghost> _ghost = m_wpghost.lock();

	if (_ghost)
	{
		//プレイヤー座標
		Math::Vector3 _playerPos = _ghost->GetPos();

		//プレイヤーの角度
		float _playerangle = _ghost->GetAngle();

		//プレイヤーの前方ベクトル
		Math::Vector3 _playervec = _ghost->GetMatrix().Backward();
		_playervec.Normalize();

		//今キャラが向いている方向
		//①キャラの回転行列を作成
		//Math::Matrix _nowRotMat = Math::Matrix::CreateRotationY(DirectX::XMConvertToRadians(_playerangle));
		////②現在の方向を求める
		//Math::Vector3 _nowVec = Math::Vector3::TransformNormal(Math::Vector3(0, 0, 1), _nowRotMat);
		//_nowVec.Normalize();

		//プレイヤーとゴミのベクトル
		Math::Vector3 _doorVec = m_pos - _playerPos;
		//Math::Vector3 _doorvec = _playerPos - m_pos;
		_doorVec.Normalize();

		//ベクトルの内積値から角度を算出
		//float _dot = _nowVec.Dot(_doorVec);	//内積値を算出
		float _dot = _playervec.Dot(_doorVec);	//内積値を算出

		_dot = std::clamp(_dot, -1.0f, 1.0f);

		m_angle = DirectX::XMConvertToDegrees(acos(_dot));

		//printfと同じように使うことができる
		//Application::Instance().m_log.AddLog("m_angle=%.2f \n", m_angle);

		int a = 0;

	}
}
