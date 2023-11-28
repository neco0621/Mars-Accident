#include "UFO.h"
#include "DxLib.h"
#include "Pad.h"
#include "Game.h"
#include "Scene/GamePlayingScene.h"
#include "Shot/ShotBeam.h"

#include <cmath>

namespace
{
	//UFO�̕\���ʒu
	constexpr float kPosX = Game::kScreenWidth / 2;
	constexpr float kPosY = Game::kScreenHeight / 4;

	//UFO�̃T�C�Y
	constexpr int kWidth = 32;
	constexpr int kHeight = 32;

	//UFO�̔��a
	constexpr float kRadius = 10;
}

UFO::UFO(GamePlayingScene* pGame) :
	m_pGame(pGame),
	m_pBeam(0),
	m_handle(-1),
	m_pos(kPosX, kPosY),
	m_boundFlag(false)
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
	m_colRect.SetCenter(m_pos.x, m_pos.y, kWidth, kHeight);
}

void UFO::Draw()
{
	DrawCircle(320, 120, 10, GetColor(255, 255, 0), true);
#ifdef _DEBUG
	//�����蔻��̕\��
	m_colRect.Draw(GetColor(0, 0, 255), false);
#endif
}


