#include "Rocket.h"
#include "Game.h"

namespace
{
	constexpr float KPosX = Game::kScreenWidth / 2;
	constexpr float KPosY = (Game::kScreenHeight - (Game::kScreenHeight / 4));
}

Rocket::Rocket(SceneMain* pMain) :
	m_handle(-1),
	m_pos(KPosX,KPosY)
{
}

Rocket::~Rocket()
{
}

void Rocket::Init()
{
}

void Rocket::Update()
{
}

void Rocket::Draw()
{
	//DrawGraph(m_pos.x,m_pos.y,m_handle,false);

#ifdef _DEBUG
	//“–‚½‚è”»’è‚Ì•\Ž¦
	m_colRect.Draw(GetColor(0, 0, 255), false);
#endif
}
