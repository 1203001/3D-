#pragma once

class TPSCamera;
class Gomi;
class MoveFloor;

class Cleaner :public KdGameObject
{

public:

	Cleaner(){}
	~Cleaner()override{}

	void Init()override;
	void Update()override;
	void PostUpdate()override;
	void DrawLit()override;

	void Sphere();

	const Math::Vector3 GetPos() const { return m_pos; }		//座標を他のクラスに渡す
	const bool GetInHale() const {return m_isinhale;}			//ゴミを吸い込むか

	//カメラをセット
	void SetCamera(std::shared_ptr<TPSCamera> _camera)
	{
		m_wpcamera = _camera;
	}

	

private:
	
	std::shared_ptr<KdModelWork> m_spModel		= nullptr;		//掃除機
	std::shared_ptr<KdAnimator>	m_spAnimator	= nullptr;		//アニメーション

	std::weak_ptr<TPSCamera> m_wpcamera;						//カメラをセット
	std::weak_ptr<KdEffekseerObject> m_wpinhale;				//エフェクシアの中身を保存
	std::weak_ptr<KdGameObject> m_wpgameobject;					//当たったものを保持

	Math::Vector3 m_pos = { -2,1,-5 };//プレイヤーの座標
	Math::Vector3 m_movevec = {};	  //プレイヤーの動く方向

	bool m_isinhale = false;

	float m_angle = 0;

	const int m_EffectTime = 40;			//吸い込みエフェクトを再描画を何フレーム後にするか
	int m_effectframe = 0;					//吸い込みエフェクトを描画して何フレーム経ったか

	//動く床
	Math::Vector3 m_beforfloorPos = {};		//動く床の動く前の座標
	Math::Vector3 m_afterfloorPos = {};		//動く床の動いた後の座標
	bool m_ishitmovefloor = false;			//動く床に当たっているか

	const float m_gravity = -0.1f;

};