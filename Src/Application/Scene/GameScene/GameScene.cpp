#include "GameScene.h"
#include"../SceneManager.h"
#include"../../main.h"

#include"../../GameObject/Camera/TPSCamera/TPSCamera.h"

#include"../../GameObject/Character/Ghost/Ghost.h"
#include"../../GameObject/Character/Cleaner/Cleaner.h"

#include"../../GameObject/Character/Enemy/NormalEnemy/NormalEnemy.h"
#include"../../GameObject/Character/Enemy/NormalEnemy/NormalEnemyAttack/NormalEnemyAttack.h"

#include"../../GameObject/Ground/Ground.h"
#include"../../GameObject/BackGround/BackGround.h"

#include"../../GameObject/House/House/House.h"
#include"../../GameObject/House/FloorLamp/FloorLamp.h"
#include"../../GameObject/House/Gomi/Gomi.h"
#include"../../GameObject/House/Door/Door.h"

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
	std::shared_ptr<House> _house;
	_house = std::make_shared<House>();
	_house->Init();
	m_objList.push_back(_house);

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

	//敵①
	std::shared_ptr<NormalEnemy> _normalenemy;
	_normalenemy = std::make_shared<NormalEnemy>();
	_normalenemy->Init();
	m_objList.push_back(_normalenemy);

	//掃除機
	std::shared_ptr<Cleaner> _cleaner;
	_cleaner = std::make_shared<Cleaner>();
	_cleaner->Init();
	m_objList.push_back(_cleaner);

	//ゴミ
	std::shared_ptr<Gomi> _gomi;
	_gomi = std::make_shared<Gomi>();
	_gomi->Init();
	m_objList.push_back(_gomi);

	//ドア
	std::shared_ptr<Door> _door;
	_door = std::make_shared<Door>();
	_door->Init();
	m_objList.push_back(_door);

	//カメラ追加
	std::shared_ptr<TPSCamera> _camera;
	_camera = std::make_shared<TPSCamera>();
	_camera->Init();
	_camera->RegistHitObject(_house);
	m_objList.push_back(_camera);
	
	//カメラにおばけをセット
	_camera->SetTarget(_ghost);
	
	//おばけにカメラをセット
	_ghost->SetCamera(_camera);

	//掃除機クラスにカメラをセット
	_cleaner->SetCamera(_camera);

	//おばけにクリーナーをセットする
	_ghost->SetCleaner(_cleaner);

	//敵①クラスにおばけ(プレイヤー)をセットする
	_normalenemy->SetTarget(_ghost);

	//ゴミクラスに掃除機クラスをセットする
	_gomi->SetCleaner(_cleaner);

	//ドアクラスにおばけクラスをセットする
	_door->SetGhost(_ghost);

	//ImGuiの値をコントールするためにカメラをセット
	_objectcontroller->SetCamera(_camera);

}