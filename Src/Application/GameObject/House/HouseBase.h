#pragma once

class HouseBase :public KdGameObject
{

public:

	HouseBase(){}
	~HouseBase()override{}

	virtual void Init()override;
	virtual void Update()override;
	virtual void DrawLit()override;

protected:

	std::shared_ptr<KdModelData> m_spModel;
	Math::Vector3 m_pos = {};

};


