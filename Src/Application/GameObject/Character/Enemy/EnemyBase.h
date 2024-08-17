#pragma once

class Cleaner;
class Score;


class EnemyBase :public KdGameObject
{

public:

	EnemyBase(){}
	~EnemyBase()override{}

	virtual void Init()override;
	virtual void Update()override;
	virtual void DrawLit()override;

	void SetTarget(const std::shared_ptr<KdGameObject>& target);

	void SetCleaner(std::shared_ptr<Cleaner> _cleaner)
	{
		m_wpcleaner = _cleaner;
	}

	void SetScore(std::shared_ptr<Score> _score)
	{
		m_wpscore = _score;
	}

protected:

	std::shared_ptr<KdModelWork> m_spModel = nullptr;
	Math::Vector3 m_pos = {};


	std::weak_ptr<KdGameObject>	m_wpTarget;
	std::weak_ptr<Cleaner> m_wpcleaner;		//掃除機クラス
	std::weak_ptr<Score> m_wpscore;			//スコアクラス


};

