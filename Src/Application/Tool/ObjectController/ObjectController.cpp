#include "ObjectController.h"
#include"../../main.h"
#include"../../Scene/SceneManager.h"
#include"../../GameObject/Camera/TPSCamera/TPSCamera.h"

#include"../TestImGui.h"
#include"../CSV/HouseCSV/HouseCSV.h"

#include"../../GameObject/Character/Ghost/Ghost.h"
#include"../../GameObject/Character/Cleaner/Cleaner.h"
#include"../../GameObject/House/Door/Door.h"
#include"../../GameObject/House/Wall/Wall.h"


void ObjectController::Init()
{

	CSVLoder();

	
}

void ObjectController::Update()
{

	if (!m_isbegincreate)
	{
		m_isbegincreate = true;

		for (auto& _data : m_dataList)
		{
			if (_data.m_type == "WallObject")
			{
				std::shared_ptr<Wall> _wall;
				_wall = std::make_shared<Wall>();
				_wall->Init();
				SceneManager::Instance().AddObject(_wall);

				//今何個目か
				m_count.m_wallcount++;

				//大きさ
				Math::Matrix _scaleMat = Math::Matrix::CreateScale(_data.m_scale);

				//角度
				Math::Matrix _rotX = Math::Matrix::CreateRotationX(DirectX::XMConvertToRadians(_data.m_angle.x));
				Math::Matrix _rotY = Math::Matrix::CreateRotationY(DirectX::XMConvertToRadians(_data.m_angle.y));
				Math::Matrix _rotZ = Math::Matrix::CreateRotationZ(DirectX::XMConvertToRadians(_data.m_angle.z));
				//座標
				Math::Matrix _transMat = Math::Matrix::CreateTranslation(_data.m_pos);

				Math::Matrix _Mat = _scaleMat * _rotX * _rotY * _rotZ * _transMat;

				_wall->SetMatrix(_Mat);

				//名前
				_wall->SetObjectName(_data.m_name);


			}
		}

	}


	std::shared_ptr<const TPSCamera> _spCamera = m_wpCamera.lock();

	//カメラがあるか
	if (!_spCamera)return;

	//クリックしたら選んだオブジェクトをセットする
	//if (GetAsyncKeyState(VK_RBUTTON) & 0x8000)
	//{
	//	//マウス座標の取得
	//	POINT _mousePos;
	//	GetCursorPos(&_mousePos);
	//	ScreenToClient(Application::Instance().GetWindowHandle(), &_mousePos);

	//	Math::Vector3 _cameraPos = _spCamera->GetPos();
	//	Math::Vector3 _rayDir = Math::Vector3::Zero;
	//	float		  _rayRange = 100.0f;

	//	//レイの方向
	//	_spCamera->GetCamera()->GenerateRayInfoFromClientPos(_mousePos, _cameraPos,_rayDir,_rayRange);

	//	Math::Vector3 _endRayPos = _cameraPos + (_rayDir * _rayRange);

	//	KdCollider::RayInfo _rayInfo(KdCollider::TypeGround, _cameraPos, _endRayPos);

	//	//当たり判定結果
	//	std::list<KdCollider::CollisionResult> _resultList;

	//	//当たったオブジェクトのリスト
	//	std::vector<std::weak_ptr<KdGameObject>> _hitObjList;

	//	//当たり判定
	//	for (auto& _obj : SceneManager::Instance().GetObjList())
	//	{
	//		if (_obj->Intersects(_rayInfo, &_resultList))
	//		{
	//			_hitObjList.push_back(_obj);
	//		}
	//	}

	//	//一番近いオブジェクトを探す
	//	float _maxOverLap = 0;
	//	int _cnt = 0;

	//	for (auto& _ret : _resultList)
	//	{
	//		if (_ret.m_overlapDistance > _maxOverLap)
	//		{
	//			_maxOverLap = _ret.m_overlapDistance;
	//			m_wpTargetobject = _hitObjList[_cnt];
	//			TestImGui::Instance().SetPos(m_wpTargetobject.lock()->GetPos());
	//		}
	//		_cnt++;
	//	}

	//}


	//対象のオブジェクト
	std::shared_ptr<KdGameObject> _spTargetObject = m_wpTargetobject.lock();
	if (_spTargetObject)
	{
		//大きさ
		Math::Matrix _scaleMat = TestImGui::Instance().GetScaleMatrix();

		//角度
		Math::Matrix _rotX = TestImGui::Instance().GetRotationXMatrix();
		Math::Matrix _rotY = TestImGui::Instance().GetRotationYMatrix();
		Math::Matrix _rotZ = TestImGui::Instance().GetRotationZMatrix();

		//座標
		Math::Matrix _transMat = Math::Matrix::CreateTranslation(TestImGui::Instance().GetPos());

		Math::Matrix _Mat =_scaleMat * _rotX * _rotY * _rotZ * _transMat;

		_spTargetObject->SetMatrix(_Mat);

		

	}
	


}

void ObjectController::CSVLoder()
{
	std::ifstream _ifs("Asset/Data/CSV/house.csv");//ファイルを操作する変数
	if (!_ifs.is_open())//ファイルが開けるかどうか
	{
		return;
	}

	std::string _lineString;//ファイルから読み取った1文字列

	//①ファイルから１文字列ずつ読み取る
	while (std::getline(_ifs, _lineString))
	{
		std::istringstream _iss(_lineString);//文字列を操作する変数
		std::string _commaString;		   //コンマ区切りにした文字列
		int _cnt = 0;						//何列目かを数える
		bool _emptyFlg = true;
		Data _data;


		//②文字列をコンマ区切りにする
		while (std::getline(_iss, _commaString, ','))
		{
			_emptyFlg = false;
			switch (_cnt)
			{
			case 0:
				_data.m_type = _commaString;
				break;
			case 1:
				_data.m_name = _commaString;
				break;
			case 2:
				_data.m_pos.x = std::stof(_commaString);
				break;
			case 3:
				_data.m_pos.y = std::stof(_commaString);
				break;
			case 4:
				_data.m_pos.z = std::stof(_commaString);
				break;
			case 5:
				_data.m_angle.x = std::stof(_commaString);
				break;
			case 6:
				_data.m_angle.y = std::stof(_commaString);
				break;
			case 7:
				_data.m_angle.z = std::stof(_commaString);
				break;
			case 8:
				_data.m_scale.x = std::stof(_commaString);
				break;
			case 9:
				_data.m_scale.y = std::stof(_commaString);
				break;
			case 10:
				_data.m_scale.z = std::stof(_commaString);
				break;
			default:
				break;
			}

			_cnt++;

		}

		m_dataList.push_back(_data);

	}

	_ifs.close();
}

void ObjectController::CSVWriter()
{
	std::ofstream ofs("Asset/Data/CSV/house.csv");


	for (auto& _data : m_dataList)
	{
		ofs << _data.m_type << ",";

		ofs << _data.m_name << ",";

		ofs << _data.m_pos.x << "," << _data.m_pos.y << "," << _data.m_pos.z << ",";

		ofs << _data.m_angle.x << "," << _data.m_angle.y << "," << _data.m_angle.z << ",";

		ofs << _data.m_scale.x << "," << _data.m_scale.y << "," << _data.m_scale.z << std::endl;

	}
}

void ObjectController::CreateObject(Object _object)
{

	switch (_object)
	{
	case Object::WallObject:
	{
		std::shared_ptr<Wall> _wall = std::make_shared<Wall>();
		_wall->Init();
		SceneManager::Instance().AddObject(_wall);
		m_wpTargetobject = _wall;
	}
	}

}

void ObjectController::Confirm()
{
	//対象のオブジェクト
	Data _data;

	std::shared_ptr<KdGameObject> _spTargetObject = m_wpTargetobject.lock();
	if (_spTargetObject)
	{
		//新規
		if (_spTargetObject->GetObjectName() == "None")
		{
			
			switch (_spTargetObject->GetObjectType())
			{
			case WallObject:
				_data.m_type = "WallObject";
				m_count.m_wallcount++;
				_data.m_name = _data.m_type + std::to_string(m_count.m_wallcount);
				break;
			}

			_spTargetObject->SetObjectName(_data.m_name);
			_data.m_pos = TestImGui::Instance().GetPos();
			_data.m_angle = TestImGui::Instance().GetAngle();
			_data.m_scale = TestImGui::Instance().GetScale();

			m_dataList.push_back(_data);


		}
		else
		{
			//上書き
			int num = 0;
			for (int i = 0; m_dataList.size(); i++)
			{
				if (_data.m_name == _spTargetObject->GetObjectName())
				{
					break;
				}

				num++;

			}

			m_dataList[num].m_pos = TestImGui::Instance().GetPos();
			m_dataList[num].m_angle = TestImGui::Instance().GetAngle();
			m_dataList[num].m_scale = TestImGui::Instance().GetScale();

		}

	}

	m_wpTargetobject.reset();

}

void ObjectController::Save()
{
	CSVWriter();
}

void ObjectController::DeleteObject()
{
	//対象のオブジェクト
	std::shared_ptr<KdGameObject> _spTargetObject = m_wpTargetobject.lock();
	if (_spTargetObject)
	{
		_spTargetObject->SetExpired(true);
		
	}
}
