#include "NormalEnemy.h"
#include"NormalEnemyAttack/NormalEnemyAttack.h"

#include"../../../../Scene/SceneManager.h"

void NormalEnemy::Init()
{
	m_spModel = std::make_shared<KdModelWork>();
	m_spModel->SetModelData("Asset/Models/GhostAnimation/Ghost.gltf");

	m_pos = { -2.0f,3.0f,10.0f };

	Math::Matrix _scaleMat = Math::Matrix::CreateScale(2.0f);
	Math::Matrix _transMat = Math::Matrix::CreateTranslation(m_pos);

	m_mWorld = _scaleMat * _transMat;

}

void NormalEnemy::Update()
{
	//if (m_wpTarget.expired() == false)
	//{
	//	if (m_isattack)
	//	{
	//		m_isattack = false;

	//		Math::Vector3 _playerpos = m_wpTarget.lock()->GetPos();
	//		std::shared_ptr<Cleaner> _cleaner = m_wpcleaner.lock();
	//		std::shared_ptr<Score> _score = m_wpscore.lock();

	//		//敵①の攻撃
	//		std::shared_ptr<NormalEnemyAttack> _normalenemyattack;
	//		_normalenemyattack = std::make_shared<NormalEnemyAttack>();
	//		_normalenemyattack->Init();
	//		_normalenemyattack->SetPram(_playerpos, m_pos);

	//		if (_cleaner)
	//		{
	//			//敵①攻撃クラスに掃除機クラスをセット
	//			_normalenemyattack->SetCleaner(_cleaner);
	//		}

	//		if (_score)
	//		{
	//			//敵①攻撃クラスにスコアクラスをセット
	//			_normalenemyattack->SetScore(_score);
	//		}


	//		SceneManager::Instance().AddObject(_normalenemyattack);

	//		
	//	}
	//}

	////一定時間たつと攻撃
	//if (m_attackframe > m_attackstart)
	//{
	//	m_attackframe = 0;
	//	m_isattack = true;
	//}

	//m_attackframe++;

}

void NormalEnemy::DrawLit()
{
	EnemyBase::DrawLit();
}
