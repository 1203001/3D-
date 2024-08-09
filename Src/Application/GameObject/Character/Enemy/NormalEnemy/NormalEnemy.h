#pragma once
#include"../EnemyBase.h"

class NormalEnemy :public EnemyBase
{

public:

	NormalEnemy(){}
	~NormalEnemy()override{}

	void Init()		override;
	void Update()	override;
	void DrawLit()	override;


private:



	bool m_isattack = false;
	int m_attackframe = 0;

	const int m_attackstart = 150;

};
