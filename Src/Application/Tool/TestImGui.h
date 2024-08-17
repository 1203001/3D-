#pragma once

class ObjectController;

class TestImGui 
{

public:

	void Draw();

	const Math::Vector3 GetPos()const { return m_pos; }
	void SetPos(Math::Vector3 _pos) { m_pos = _pos; }

	const Math::Vector3 GetAngle()const { return m_angle; }
	const Math::Vector3 GetScale()const { return m_scale; }

	void SetObjectController(std::shared_ptr<ObjectController> _objectcontroller)
	{
		m_wpObjectController = _objectcontroller;
	}

	const Math::Matrix GetRotationXMatrix() const
	{
		return Math::Matrix::CreateRotationX(
			DirectX::XMConvertToRadians(m_angle.x));
	}

	const Math::Matrix GetRotationYMatrix() const
	{
		return Math::Matrix::CreateRotationY(
			DirectX::XMConvertToRadians(m_angle.y));
	}

	const Math::Matrix GetRotationZMatrix() const
	{
		return Math::Matrix::CreateRotationZ(
			DirectX::XMConvertToRadians(m_angle.z));
	}

	const Math::Matrix GetScaleMatrix() const
	{
		return Math::Matrix::CreateScale(m_scale);
	}


private:

	Math::Vector3 m_pos = {};				//座標
	Math::Vector3 m_angle = {};				//角度
	Math::Vector3 m_scale = {1.0f,1.0f,1.0f};				//大きさ

	std::weak_ptr<ObjectController> m_wpObjectController;

//=====================================================
// シングルトンパターン
//=====================================================
private:

	TestImGui() {}

public:
	static TestImGui& Instance() {
		static TestImGui Instance;
		return Instance;
	}
};


