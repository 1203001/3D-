#pragma once

class Cleaner;

class NormalEnemyAttack :public KdGameObject
{

public:

	NormalEnemyAttack(){}
	~NormalEnemyAttack()override{}

	void Init()override;
	void Update()override;
	void DrawLit()override;

	void InHale();

	void SetPram(Math::Vector3 _playerpos, Math::Vector3 _enemypos);

	void SetCleaner(std::shared_ptr<Cleaner> _cleaner)
	{
		m_wpcleaner = _cleaner;
	}

	

private:

	std::shared_ptr<KdModelData> m_spModel = nullptr;
	Math::Vector3 m_pos = {};

	Math::Vector3 m_playerpos = {};				//プレイヤー座標
	//Math::Vector3 m_enemypos = {};				//敵座標

	std::weak_ptr<Cleaner> m_wpcleaner;		//掃除機クラス

	const float m_speed = 0.1f;				//攻撃スピード

	//const float m_speed = 0.05f;			//ベクトルのスピード

	float m_attackangle = 0;				//プレイヤーと敵①攻撃の角度
	const float m_range = 10.0f;			//吸い込み距離
	float m_endrange = 3.0f;				//この距離以内になると吸い込み完了


};
