#include "ObjectController.h"
#include"../../main.h"
#include"../../Scene/SceneManager.h"
#include"../../GameObject/Camera/TPSCamera/TPSCamera.h"
#include"../TestImGui.h"

#include"../../GameObject/Character/Ghost/Ghost.h"
#include"../../GameObject/Character/Cleaner/Cleaner.h"
#include"../../GameObject/House/Door/Door.h"

void ObjectController::Update()
{

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

void ObjectController::CreateObject(Object _object)
{

	switch (_object)
	{
	case Object::Ghost:
	{
		std::shared_ptr<Ghost> _ghost = std::make_shared<Ghost>();
		_ghost = std::make_shared<Ghost>();
		_ghost->Init();
		SceneManager::Instance().AddObject(_ghost);
		m_wpTargetobject = _ghost;
		break;
	}
	case Object::Cleaner:
	{
		std::shared_ptr<Cleaner> _cleaner = std::make_shared<Cleaner>();
		_cleaner->Init();
		SceneManager::Instance().AddObject(_cleaner);
		m_wpTargetobject = _cleaner;
		break;
	}
	case Object::Door:
	{
		std::shared_ptr<Door> _door = std::make_shared<Door>();
		_door->Init();
		SceneManager::Instance().AddObject(_door);
		m_wpTargetobject = _door;
		break;
	}
	}

}

void ObjectController::Confirm()
{
	//対象のオブジェクト
	if (!m_wpTargetobject.expired())
	{
		m_wpTargetobject.reset();
	}
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
