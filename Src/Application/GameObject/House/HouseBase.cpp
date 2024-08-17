#include "HouseBase.h"

void HouseBase::Init()
{

}

void HouseBase::Update()
{

}

void HouseBase::DrawLit()
{
	KdShaderManager::Instance().m_StandardShader.DrawModel(*m_spModel, m_mWorld);
}
