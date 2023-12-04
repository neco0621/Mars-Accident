#include "UFO.h"
#include "DxLib.h"
#include "Pad.h"
#include "Game.h"
#include "Rect.h"
#include "Scene/GamePlayingScene.h"
#include "Shot/ShotBeam.h"

#include <cmath>

namespace
{
	//UFO�̕\���ʒu
	constexpr float kPosX = Game::kScreenWidth / 2;
	constexpr float kPosY = Game::kScreenHeight / 4;

	//UFO�̃T�C�Y
	constexpr int kWidth = 40;
	constexpr int kHeight = 40;

	//UFO�̔��a
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
	//�����蔻��̍X�V
	m_colRect.SetRadius(m_pos.x,m_pos.y,m_radius);
}

void UFO::Draw()
{
	DrawCircle(m_pos.x, m_pos.y, m_radius, GetColor(255, 255, 0), true);
	//�����蔻��̕\��
	m_colRect.DrawC(GetColor(255, 0, 0), false);
}


