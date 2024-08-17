#pragma once

class Cleaner;
class Score;

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

	void SetScore(std::shared_ptr<Score> _score)
	{
		m_wpscore = _score;
	}

	

private:

	std::shared_ptr<KdModelData> m_spModel = nullptr;
	Math::Vector3 m_pos = {};

	Math::Vector3 m_playerpos = {};				//プレイヤー座標

	std::weak_ptr<Cleaner> m_wpcleaner;		//掃除機クラス
	std::weak_ptr<Score> m_wpscore;			//スコアクラス

	const float m_speed = 0.1f;				//攻撃スピード

	float m_attackangle = 0;				//プレイヤーと敵①攻撃の角度
	const float m_range = 12.0f;			//吸い込み距離
	float m_endrange = 4.0f;				//この距離以内になると吸い込み完了


};
