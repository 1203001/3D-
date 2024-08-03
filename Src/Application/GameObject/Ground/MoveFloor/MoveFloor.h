#pragma once

class MoveFloor :public KdGameObject
{

public:

	MoveFloor() {}
	~MoveFloor()override {}

	void Init()override;
	void Update()override;
	void DrawLit()override;

private:

	std::shared_ptr<KdModelData> m_spModel;

	Math::Vector3 m_pos;

	float m_move = 0.0f;
	float m_speed = 0.1f;

};

