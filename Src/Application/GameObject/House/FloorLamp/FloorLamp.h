#pragma once

class Candle :public KdGameObject
{
public:

	Candle(){}
	~Candle()override{}

	void Init()override;
	void Update()override;
	void DrawLit()override;

private:

	std::shared_ptr<KdModelData> m_spModel;
	Math::Vector3 m_pos = {};

};

