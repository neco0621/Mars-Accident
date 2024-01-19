#include "Rocket.h"
#include "Game.h"

namespace
{
	constexpr float KPosX = Game::kScreenWidth * 0.5f;
	constexpr float KPosY = Game::kScreenHeight * 0.75f;

	constexpr float kWidth = 80.0f;
	constexpr float kHeight = 130.0f;

	constexpr float kRadius = 10.0f;

	constexpr int kLife = 3;

	constexpr int kDecrease = 1;
}

Rocket::Rocket(Stage1Scene* pS1Scene) :
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
	//当たり判定の更新
	m_colRect.SetCenter(m_pos.x, m_pos.y - kHeight / 4, kWidth, kHeight);

}

void Rocket::Draw()
{
	DrawRotaGraph(static_cast<int>(m_pos.x), static_cast<int>(m_pos.y) - kHeight / 4,
		1.0, 0.0,
		m_handle, true, false);

#ifdef _DEBUG
	//当たり判定の表示
	m_colRect.Draw(GetColor(255, 0, 0), false);
#endif
}

void Rocket::LifeDecrease()
{
	m_life -= kDecrease;
}
