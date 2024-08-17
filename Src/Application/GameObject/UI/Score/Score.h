#pragma once

class Score :public KdGameObject
{

public:

	Score(){}
	~Score()override{}

	void Init()override;
	void Update()override;
	void DrawSprite()override;

	void SetScore(int _score);


private:

	std::shared_ptr<KdTexture> m_spscoreTex;	//スコア画像

	int m_score = 0;							//スコアが何点入ったか(清潔度がどれくらいたまったか)
	int m_oneplace = 0;							//1の位
	int m_tenplace = 0;							//10の位
	int m_hundredplace = 0;						//100の位


};



