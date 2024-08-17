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

	void Sphere();

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

	enum SituationType
	{
		TypeGround		= 1 << 0, 						//地面にいるとき
		TypeAir			= 1 << 1,						//空中にいるとき
		TypeSuikomi		= 1 << 2,						//掃除機に吸い込まれているとき
		TypeNotSuikomi	= 1<< 3							//掃除機に吸い込まれていたけど吸い込まれなくなった時
	};

	UINT m_SituationType = TypeGround;

	const float m_speed = 0.05f;		//ベクトルのスピード

	float m_gomiangle = 0;				//プレイヤーとゴミの角度

	const float m_range = 12.0f;		//吸い込み距離
	float m_endrange = 4.0f;			//この距離以内になると吸い込み完了

	float m_gravity = 0.1f;				//重力
	const float m_gravityPow = 0.01;	//重力をどれくらい動かすか
	const float m_endgravity = 0.05f;	//この値までいくと重力を止める

	float m_hitPosY = 0;				//スフィアで当たったY座標を保存

};

