#pragma once
#include"../HouseBase.h"

class MoveFloor :public HouseBase
{

public:

	MoveFloor(){}
	~MoveFloor()override{}

	void Init()override;
	void Update()override;
	void DrawLit()override;

private:

	Math::Vector3 m_move = {};
	float m_speed = 0.1f;
	int m_moveframe = 0;

};

