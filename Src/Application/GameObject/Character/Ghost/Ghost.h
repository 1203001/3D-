#pragma once

class TPSCamera;
class Cleaner;

class Ghost :public KdGameObject
{
public:
	Ghost(){}
	~Ghost()override{}

	void Init()override;
	void Update()override;
	void PostUpdate()override;
	void DrawLit()override;
	void CSVLoader(std::string a_filePath);

	const float GetAngle() const { return m_angle; }

	void SetPos(Math::Vector3 _pos) { m_pos = _pos; }

	//カメラをセット
	void SetCamera(std::shared_ptr<TPSCamera> _camera)
	{
		m_wpcamera = _camera;
	}

	//掃除機をセット
	void SetCleaner(std::shared_ptr<Cleaner> _cleaner)
	{
		m_wpcleaner = _cleaner;
	}


private:
	std::shared_ptr<KdModelWork> m_spModel		= nullptr;
	std::shared_ptr<KdAnimator>	m_spAnimator	= nullptr;

	std::vector<std::vector<int>> m_data;

	std::weak_ptr<Cleaner> m_wpcleaner;			//掃除機クラス

	float m_angle = 0;

	Math::Vector3 m_pos = {};

	bool m_isAttack = false;

	bool m_isTPS = false;

	std::weak_ptr<TPSCamera> m_wpcamera;

	const float m_speed = 0.05f;				//ベクトルのスピード

	//エフェクシア
	bool m_iswind = true;
	const int m_windTime = 60;
	int m_windframe = 0;

	std::weak_ptr<KdEffekseerObject> m_wpwind;

};

