#pragma once

class TPSCamera;

class ObjectController :public KdGameObject
{
public:
	
	ObjectController(){}
	~ObjectController()override{}

	void Update();

	enum class Object
	{
		Ghost,
		Cleaner,
		Door,
	};

	void SetCamera(const std::shared_ptr<TPSCamera>& _spCamera)	//カメラをセット
	{
		m_wpCamera = _spCamera;
	}

	void CreateObject(Object _object);				//オブジェクトを作成
	void Confirm();									//座標確定
	void DeleteObject();							//選んだオブジェクトを削除

private:

	//動かすオブジェクト
	std::weak_ptr<KdGameObject> m_wpTargetobject;

	//カメラ
	std::weak_ptr<TPSCamera> m_wpCamera;

};

