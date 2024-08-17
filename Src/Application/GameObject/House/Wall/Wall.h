#pragma once

#include"../HouseBase.h"

class Wall :public HouseBase
{

public:

	Wall() {}
	~Wall()override {}

	void Init()override;
	void Update()override;
	void DrawLit()override;

private:

	Math::Vector3 m_move = {};

};

