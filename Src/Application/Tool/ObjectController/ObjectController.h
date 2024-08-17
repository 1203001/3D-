#pragma once

class TPSCamera;

class ObjectController :public KdGameObject
{
public:
	
	ObjectController(){}
	~ObjectController()override{}

	void Init()override;
	void Update()override;

	void CSVLoder();
	void CSVWriter();

	enum class Object
	{
		Ghost,
		Cleaner,
		Door,
		WallObject,
	};

	void SetCamera(const std::shared_ptr<TPSCamera>& _spCamera)	//カメラをセット
	{
		m_wpCamera = _spCamera;
	}

	void CreateObject(Object _object);				//オブジェクトを作成
	void Confirm();									//座標確定
	void Save();									//セーブ
	void DeleteObject();							//選んだオブジェクトを削除

private:

	//動かすオブジェクト
	std::weak_ptr<KdGameObject> m_wpTargetobject;

	//カメラ
	std::weak_ptr<TPSCamera> m_wpCamera;


	struct Data
	{
		std::string m_type;			//オブジェクトのタイプ
		std::string m_name;			//オブジェクトの名前
		Math::Vector3 m_pos;		//座標
		Math::Vector3 m_angle;		//角度
		Math::Vector3 m_scale;		//大きさ
	};

	struct Count
	{
		int m_wallcount = 0;			//壁クラスが何個目か
	};

	std::vector<Data> m_dataList;		//CSVに書くものを保存

	Count m_count;						//そのオブジェクトが何個目かを確認

	bool m_isbegincreate = false;		//初めの一回だけオブジェクトを生成



};

