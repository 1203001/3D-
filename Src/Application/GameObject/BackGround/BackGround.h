#pragma once

class BackGround :public KdGameObject
{
public:
	BackGround() { Init(); }
	~BackGround()override {};

	void DrawUnLit()override;
	void Init()     override;

	void SetPos(Math::Vector3 _pos) { m_pos = _pos; }

private:
	std::shared_ptr<KdModelData>     m_spModel = nullptr;
	Math::Vector3                    m_pos = Math::Vector3::Zero;
};

