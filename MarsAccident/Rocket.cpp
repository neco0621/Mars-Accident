#include "Rocket.h"
#include "Game.h"

namespace
{
	constexpr float KPosX = Game::kScreenWidth * 0.5f;
	constexpr float KPosY = Game::kScreenHeight * 0.75f;

	constexpr float kWidth = 40.0f;
	constexpr float kHeight = 96.0f;

	constexpr float kRadius = 10.0f;

	constexpr int kLife = 3;

	constexpr int kDecrease = 1;
}

Rocket::Rocket(SceneMain* pMain) :
	m_handle(-1),
	m_pos(KPosX,KPosY),
	m_radius(kRadius),
	m_life(kLife)
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
	//ìñÇΩÇËîªíËÇÃçXêV
	m_colRect.SetCenter(m_pos.x, m_pos.y - 30, kWidth, kHeight);
}

void Rocket::Draw()
{
	DrawBox(m_pos.x - 20, m_pos.y - 80, m_pos.x + 20, m_pos.y + 16, 0x0000ff,true);
	DrawCircle(m_pos.x, m_pos.y - 120, m_radius, 0xff0000, true);
	DrawCircle(m_pos.x + 30, m_pos.y - 120, m_radius, 0xff0000, true);
	DrawCircle(m_pos.x - 30, m_pos.y - 120, m_radius, 0xff0000, true);

#ifdef _DEBUG
	//ìñÇΩÇËîªíËÇÃï\é¶
	m_colRect.Draw(GetColor(255, 0, 0), false);
#endif
}

void Rocket::LifeDecrease()
{
	m_life -= kDecrease;
}
