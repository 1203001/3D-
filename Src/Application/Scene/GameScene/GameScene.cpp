#include "GameScene.h"
#include"../SceneManager.h"
#include"../../main.h"

#include"../../GameObject/Camera/TPSCamera/TPSCamera.h"

#include"../../GameObject/Character/Ghost/Ghost.h"
#include"../../GameObject/Character/Cleaner/Cleaner.h"

#include"../../GameObject/Ground/Ground.h"
#include"../../GameObject/Ground/MoveFloor/MoveFloor.h"
#include"../../GameObject/BackGround/BackGround.h"
#include"../../GameObject/House/FloorLamp/FloorLamp.h"

#include"../../Tool/ObjectController/ObjectController.h"
#include"../../Tool/TestImGui.h"

void GameScene::Event()
{
	//printfと同じように使うことができる
	Application::Instance().m_log.AddLog("ObjListSize:%d\n",m_objList.size());


	//被写界深度	   ↓ピントの位置
	//m_camera->SetFocus(5, 3, 8);
	//					　↑手前と奥のぼかし距離

	//ブルーム															↓閾値
	//KdShaderManager::Instance().m_postProcessShader.SetBrightThreshold(0.7f);

}

void GameScene::Init()
{


	//平行光（ディレクショナルライト）									↓方向		↓色RGB
	//KdShaderManager::Instance().WorkAmbientController().SetDirLight({ 0,-1,0.1f }, { 3,3,3 });

	//環境光（アンビエントライト）										↓色RGBA　デフォルト0.3
	KdShaderManager::Instance().WorkAmbientController().SetAmbientLight({ 1.0f,1.0f,1.0f,0.5f });


	////フォグ（霧）
	//KdShaderManager::Instance().WorkAmbientController().SetFogEnable(true, false);
	////距離フォグ														↓色	　↓密度
	//KdShaderManager::Instance().WorkAmbientController().SetDistanceFog({ 0.5f,0.5f,0.5f }, 0.03f);
	//高さフォグ														↓色	↓上の上限・下の上限・カメラとの距離
	//KdShaderManager::Instance().WorkAmbientController().SetheightFog({ 0.5f,0.5f,0.5f }, 0, -2, 0);


	//マップエディタ的な
	std::shared_ptr<ObjectController> _objectcontroller = std::make_shared<ObjectController>();
	_objectcontroller->Init();
	m_objList.push_back(_objectcontroller);

	//デバックウィンドウにオブジェクトコントローラーを渡す
	TestImGui::Instance().SetObjectController(_objectcontroller);

	//スカイボックス
	//std::shared_ptr<BackGround> _background = std::make_shared<BackGround>();
	//m_objList.push_back(_background);

	//地面
	/*std::shared_ptr<Ground> ground;
	ground = std::make_shared<Ground>();
	ground->Init();
	m_objList.push_back(ground);*/

	//動く床
	std::shared_ptr<MoveFloor> _movefloor;
	_movefloor = std::make_shared<MoveFloor>();
	_movefloor->Init();
	m_objList.push_back(_movefloor);

	//キャンドル
	std::shared_ptr<Candle> _candle;
	_candle = std::make_shared<Candle>();
	_candle->Init();
	m_objList.push_back(_candle);

	//おばけ
	std::shared_ptr<Ghost> _ghost;
	_ghost = std::make_shared<Ghost>();
	_ghost->Init();
	m_objList.push_back(_ghost);

	//掃除機
	std::shared_ptr<Cleaner> _cleaner;
	_cleaner = std::make_shared<Cleaner>();
	_cleaner->Init();
	m_objList.push_back(_cleaner);

	//カメラ追加
	std::shared_ptr<TPSCamera> camera;
	camera = std::make_shared<TPSCamera>();
	camera->Init();
	m_objList.push_back(camera);
	
	//カメラに戦車をセット
	camera->SetTarget(_ghost);
	
	//戦車にカメラをセット
	_ghost->SetCamera(camera);

	//おばけにクリーナーをセットする
	_ghost->SetCleaner(_cleaner);

	//ImGuiの値をコントールするためにカメラをセット
	_objectcontroller->SetCamera(camera);

}