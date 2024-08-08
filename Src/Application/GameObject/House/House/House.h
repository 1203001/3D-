#pragma once

class House :public KdGameObject
{

public:

	House() {}
	~House()override {}

	void Init()override;
	void Update()override;
	void DrawLit()override;

private:

	std::shared_ptr<KdModelData> m_spModel;

	Math::Vector3 m_pos = { -50,0,0 };

	float m_move = 0.0f;
	float m_speed = 0.1f;

};

