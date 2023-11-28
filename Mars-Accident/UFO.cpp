#include "UFO.h"
#include "DxLib.h"
#include "Pad.h"
#include "Game.h"
#include "Scene/GamePlayingScene.h"
#include "Shot/ShotBeam.h"

#include <cmath>

namespace
{
	//UFOの表示位置
	constexpr float kPosX = Game::kScreenWidth / 2;
	constexpr float kPosY = Game::kScreenHeight / 4;

	//UFOのサイズ
	constexpr int kWidth = 32;
	constexpr int kHeight = 32;

	//UFOの半径
	constexpr float kRadius = 40;
}

UFO::UFO(GamePlayingScene* pGame) :
	m_pGame(pGame),
	m_pBeam(0),
	m_handle(-1),
	m_pos(kPosX, kPosY),
	m_boundFlag(false),
	m_radius(kRadius)
{
}

UFO::~UFO()
{
}

void UFO::Init()
{
}

void UFO::Update()
{
	//当たり判定の更新
	m_colRect.SetCenter(m_pos.x, m_pos.y, kWidth, kHeight);
}

void UFO::Draw()
{
	DrawCircle(m_pos.x, m_pos.y, m_radius, GetColor(255, 255, 0), true);
#ifdef _DEBUG
	//当たり判定の表示
	m_colRect.Draw(GetColor(0, 0, 255), false);
#endif
}


