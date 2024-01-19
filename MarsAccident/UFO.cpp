#include "UFO.h"
#include "DxLib.h"
#include "Pad.h"
#include "Game.h"
#include "Rect.h"
#include "Scene/Stage1Scene.h"
#include "ShotBeam.h"

#define PI 3.14
#include <cmath>

namespace
{
	//UFOの表示位置
	constexpr float kPosX = Game::kScreenWidth / 2;
	constexpr float kPosY = Game::kScreenHeight / 4;

	//UFOのサイズ
	constexpr float kWidth = 40;
	constexpr float kHeight = 40;

	//UFOの半径
	constexpr float kRadius = 40;

	constexpr float kSpeed = 3.0f;

	constexpr int kWipeFrame = 30;
}

UFO::UFO(Stage1Scene* pS1Scene) :
	m_pS1Scene(pS1Scene),
	m_pBeam(0),
	m_handle(-1),
	m_pos(kPosX, kPosY),
	m_boundFlag(false),
	m_radius(kRadius),
	m_vec(0,kSpeed),
	m_MoveFlag(false),
	isJump(true),
	KnockBack(false),
	JumpPower(10),
	m_tq(Game::kScreenHeight * 0.75f)
{
}

UFO::~UFO()
{
}

void UFO::Init()
{
	m_colRect.SetCenter(m_pos.x, m_pos.y, kWidth, kHeight);
}

void UFO::Update()
{
	if (isJump)
	{
		m_pos.y -= JumpPower;
		// 落下量調整
		if (JumpPower > -MaxGravity) 
		{	 
			JumpPower -= Gravity;
		}
		// 地面についた時
		if (m_pos.y >= m_tq - m_radius / 2)
		{
			m_pos.y = m_tq - m_radius / 2;
			JumpPower = 30;
			ShakeScreen();
		}
	}
	
	
	if (m_pos.x >= Game::kScreenWidth - m_radius)
	{
		m_MoveFlag = true;
	}
	else if (m_pos.x <= 0 + m_radius)
	{
		m_MoveFlag = false;
	}

	if (m_MoveFlag == false)
	{
		m_pos.x += kSpeed;
		m_angle++;
	}
	else if (m_MoveFlag == true)
	{
		m_pos.x -= kSpeed;
		m_angle--;
	}
	//当たり判定の更新
	m_colRect.SetRadius(m_pos.x, m_pos.y, m_radius);
	
}

void UFO::Draw()
{
	DrawFormatString(8, 56, GetColor(255, 255, 255),
		"%f",m_angle);
	//当たり判定の表示

	DrawRotaGraph(static_cast<int>(m_pos.x), static_cast<int>(m_pos.y),
		1.0, DX_PI_F / 180.0 * m_angle,
		m_handle, true);
	m_colRect.DrawC(GetColor(255, 0, 0), false);

}

void UFO::ShakeScreen()
{
}


