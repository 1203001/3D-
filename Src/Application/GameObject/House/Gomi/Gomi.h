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
	void InHale();


	const Math::Vector3 GetPos() { return m_pos; }

	//掃除機をセットする
	void SetCleaner(std::shared_ptr<Cleaner> _cleaner)
	{
		m_wpcleaner = _cleaner;
	}



private:

	std::shared_ptr<KdModelData> m_spModel = nullptr;
	Math::Vector3 m_pos = { 0,0,5 };

	std::weak_ptr<Cleaner> m_wpcleaner;		//掃除機クラス


	const float m_speed = 0.05f;	//ベクトルのスピード

	float m_gomiangle = 0;				//プレイヤーとゴミの角度

	const float m_range = 10.0f;			//吸い込み距離
	float m_endrange = 3.0f;				//この距離以内になると吸い込み完了


};

