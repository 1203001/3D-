#pragma once

class Ghost;

class Door :public KdGameObject
{
public:

	Door(){}
	~Door()override{}

	void Init()override;
	void Update()override;
	void PostUpdate()override;
	void DrawLit()override;
	void DrawSprite()override;

	void DoorAngle();			//ドアの開け閉めができる角度を求める関数

	//おばけをセットする
	void SetGhost(std::shared_ptr<Ghost> _ghost)
	{
		m_wpghost = _ghost;
	}

private:

	std::shared_ptr<KdModelWork> m_spModel		= nullptr;	//ドア画像
	std::shared_ptr<KdAnimator>	m_spAnimator	= nullptr;	//ドアアニメーション
	std::shared_ptr<KdTexture> m_spkeyTex		= nullptr;	//キー画像

	Math::Vector3 m_pos = { -10.5f,0.0f,-28.5f };

	//おばけクラスをセット
	std::weak_ptr<Ghost> m_wpghost;

	float m_angle = 0;				//プレイヤーとドアの角度

	bool m_isopen = false;			//ドアを開けるか閉めるか
	bool m_isdoor = false;			//ドアを開けれる距離にいるか

};

