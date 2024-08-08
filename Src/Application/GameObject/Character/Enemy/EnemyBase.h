#pragma once

class EnemyBase :public KdGameObject
{

public:

	EnemyBase(){}
	~EnemyBase()override{}

	virtual void Init()override;
	virtual void Update()override;
	virtual void DrawLit()override;

	void SetTarget(const std::shared_ptr<KdGameObject>& target);

protected:

	std::shared_ptr<KdModelWork> m_spModel = nullptr;
	std::weak_ptr<KdGameObject>	m_wpTarget;

	Math::Vector3 m_pos = {};

};

