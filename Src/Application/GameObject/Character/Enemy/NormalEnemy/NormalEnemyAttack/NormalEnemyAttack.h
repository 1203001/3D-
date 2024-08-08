#pragma once

class NormalEnemyAttack :public KdGameObject
{

public:

	NormalEnemyAttack(){}
	~NormalEnemyAttack()override{}

	void Init()override;
	void Update()override;
	void DrawLit()override;

	void SetPram(Math::Vector3 _playerpos, Math::Vector3 _enemypos);

private:

	std::shared_ptr<KdModelData> m_spModel = nullptr;
	Math::Vector3 m_pos = {};

	Math::Vector3 m_playerpos = {};				//プレイヤー座標
	//Math::Vector3 m_enemypos = {};				//敵座標

	const float m_speed = 0.1f;				//攻撃スピード

};
