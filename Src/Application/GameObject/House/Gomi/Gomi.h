#pragma once

class Cleaner;

class Gomi :public KdGameObject
{
public:

	Gomi(){}
	~Gomi()override{}

	void Init()override;
	void Update()override;
	void DrawLit()override;

	void Inhale();			//掃除機の吸い込み処理

	const Math::Vector3 GetPos() { return m_pos; }

	//掃除機をセットする
	void SetCleaner(std::shared_ptr<Cleaner> _cleaner)
	{
		m_wpcleaner = _cleaner;
	}

private:

	std::shared_ptr<KdModelData> m_spModel = nullptr;
	Math::Vector3 m_pos = { 0,0,5 };

	std::weak_ptr<Cleaner> m_wpcleaner;


	const float m_speed = 0.05f;	//ベクトルのスピード

	float m_angle = 0;				//プレイヤーとゴミの角度

	const float m_range = 5.0f;

};

