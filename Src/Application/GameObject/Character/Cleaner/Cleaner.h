#pragma once

class TPSCamera;
class Gomi;

class Cleaner :public KdGameObject
{

public:

	Cleaner(){}
	~Cleaner()override{}

	void Init()override;
	void Update()override;
	void PostUpdate()override;
	void DrawLit()override;


	const Math::Vector3 GetPos() const { return m_pos; }		//座標を他のクラスに渡す
	const bool GetInHale() const {return m_isinhale;}			//ゴミを吸い込むか

	//カメラをセット
	void SetCamera(std::shared_ptr<TPSCamera> _camera)
	{
		m_wpcamera = _camera;
	}

	//ゴミクラスをセットする
	/*void SetGomi(std::shared_ptr<Gomi> _gomi)
	{
		m_wpgomi = _gomi;
	}*/

private:
	
	std::shared_ptr<KdModelWork> m_spModel		= nullptr;		//掃除機
	std::shared_ptr<KdAnimator>	m_spAnimator	= nullptr;		//アニメーション

	std::weak_ptr<TPSCamera> m_wpcamera;

	Math::Vector3 m_pos = { -2,0,-5 };//プレイヤーの座標

	bool m_isinhale = false;

	float m_angle = 180;

//	std::weak_ptr<Gomi> m_wpgomi;	//ゴミクラスを保存


};