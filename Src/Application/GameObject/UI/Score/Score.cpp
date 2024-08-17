#include "Score.h"

void Score::Init()
{
	//1画像
	m_spscoreTex = std::make_shared<KdTexture>();
	m_spscoreTex->Load("Asset/Textures/UI/Score/score.png");


}

void Score::Update()
{
	

}

void Score::DrawSprite()
{
	//スコア画像
	Math::Color _onecolor = { 1.0f,1.0f,1.0f,1.0f };
	Math::Rectangle _onerc = { 0 + m_oneplace * 30,0,30,52 };
	KdShaderManager::Instance().m_spriteShader.DrawTex(m_spscoreTex, 300, 200,_onerc.width,_onerc.height,&_onerc,&_onecolor);

	if (m_tenplace > 0 || m_hundredplace > 0)
	{
		Math::Color _tencolor = { 1.0f,1.0f,1.0f,1.0f };
		Math::Rectangle _tenrc = { 0 + m_tenplace * 30,0,30,52 };
		KdShaderManager::Instance().m_spriteShader.DrawTex(m_spscoreTex, 240, 200, _tenrc.width, _tenrc.height, &_tenrc, &_tencolor);
	}

	if (m_hundredplace > 0)
	{
		Math::Color _hundredcolor = { 1.0f,1.0f,1.0f,1.0f };
		Math::Rectangle _hundredrc = { 0 + m_hundredplace * 30,0,30,52 };
		KdShaderManager::Instance().m_spriteShader.DrawTex(m_spscoreTex, 180, 200, _hundredrc.width, _hundredrc.height, &_hundredrc, &_hundredcolor);
	}


}

void Score::SetScore(int _score)
{
	//100までいったらreturn
	if (m_hundredplace > 0)return;

	//スコア加算(清潔度UP)
	m_score += _score;

	//1の位
	m_oneplace = m_score % 10;
	
	//10の位
	m_tenplace = m_score / 10;

	//100の位
	if (m_score >= 100)
	{
		m_oneplace = 0;
		m_tenplace = 0;
		m_hundredplace = 1;
	}

}
