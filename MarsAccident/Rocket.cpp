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
	DrawBox(m_pos.x - 20,m_pos.y - 80,m_pos.x + 20, m_pos.y + 16, 0x0000ff,true);
	DrawCircle(m_pos.x, m_pos.y - 120, 10, 0xff0000, true);
	DrawCircle(m_pos.x + 30, m_pos.y - 120,10, 0xff0000, true);
	DrawCircle(m_pos.x - 30, m_pos.y - 120,10, 0xff0000, true);

#ifdef _DEBUG
	//“–‚½‚è”»’è‚Ì•\Ž¦
	m_colRect.Draw(GetColor(0, 0, 255), false);
#endif
}
