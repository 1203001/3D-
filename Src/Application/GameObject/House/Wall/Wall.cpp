#include "Wall.h"

void Wall::Init()
{

	m_objectType = ObjectType::WallObject;

	m_spModel = std::make_shared<KdModelData>();
	m_spModel->Load("Asset/Models/House/Wall/bigwall.gltf");

	/*Math::Matrix _scaleMat = Math::Matrix::CreateScale(3.0f);
	Math::Matrix _transMat = Math::Matrix::CreateTranslation(0, 0, 0);
	m_mWorld = _scaleMat * _transMat;*/

}

void Wall::Update()
{

}

void Wall::DrawLit()
{
	HouseBase::DrawLit();
}
