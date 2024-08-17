#pragma once

class HouseCSV :public KdGameObject
{
public:

	HouseCSV() {}
	~HouseCSV() { CSVWriter(); }

	void Init()override;
	void Update()override;
	void Draw();

	void CreateObject();
	void Confirm();
	

	void CSVLoder();
	void CSVWriter();



private:

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

	std::vector<Data> m_dataList;

	Count m_count;

	//動かすオブジェクト
	std::weak_ptr<KdGameObject> m_wpTargetobject;


};

