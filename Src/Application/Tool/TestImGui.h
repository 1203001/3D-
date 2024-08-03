#pragma once

class ObjectController;

class TestImGui 
{

public:

	void Draw();

	const Math::Vector3 GetPos()const { return m_pos; }
	void SetPos(Math::Vector3 _pos) { m_pos = _pos; }

	void SetObjectController(std::shared_ptr<ObjectController> _objectcontroller)
	{
		m_wpObjectController = _objectcontroller;
	}

private:

	Math::Vector3 m_pos = {};
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


