#pragma once

class Cleaner :public KdGameObject
{

public:

	Cleaner(){}
	~Cleaner()override{}

	void Init()override;
	void Update()override;
	void PostUpdate()override;
	void DrawLit()override;

private:
	
	std::shared_ptr<KdModelWork> m_spModel		= nullptr;		//掃除機
	std::shared_ptr<KdAnimator>	m_spAnimator	= nullptr;		//アニメーション


};