#pragma once

class Suikomi :public KdGameObject
{

public:

	Suikomi(){}
	~Suikomi()override{}

	void Init()override;
	void Update()override;
	void Inhale();

private:

	Math::Vector3 m_pos = { 0,0,5 };

	std::weak_ptr<Cleaner> m_wpcleaner;


	const float m_speed = 0.05f;	//ベクトルのスピード

	float m_angle = 0;				//プレイヤーとゴミの角度

	const float m_range = 5.0f;

};

