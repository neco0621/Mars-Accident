#include "UFO.h"
#include "DxLib.h"
#include "Pad.h"
#include "Game.h"
#include "Rect.h"
#include "Scene/SceneMain.h"
#include "ShotBeam.h"

#include <cmath>
#define g 9.8

namespace
{
	//UFO�̕\���ʒu
	constexpr float kPosX = Game::kScreenWidth / 2;
	constexpr float kPosY = Game::kScreenHeight / 4;

	//UFO�̃T�C�Y
	constexpr float kWidth = 40;
	constexpr float kHeight = 40;

	//UFO�̔��a
	constexpr float kRadius = 40;

	constexpr float kSpeed = 3.0f;
}

UFO::UFO(SceneMain* pMain) :
	m_pMain(pMain),
	m_pBeam(0),
	m_handle(-1),
	m_pos(kPosX, kPosY),
	m_boundFlag(false),
	m_radius(kRadius),
	m_vec(0,kSpeed),
	m_MoveFlag(false),
	isJump(true)
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
	if (isJump) {
		m_pos.y -= JumpPower ;
		// �����ʒ���
		if (JumpPower > -MaxGravity) 
		{
			JumpPower -= Gravity;
		}
		// �n�ʂɂ�����
		if (m_pos.y >= (Game::kScreenHeight - Game::kScreenHeight / 4) - m_radius)
		{
			m_pos.y = (Game::kScreenHeight - Game::kScreenHeight / 4) - m_radius;
			isJump = false;			
		}
	}
	if (!isJump)
	{
		m_pos.y -= JumpPower;
		// �����ʒ���
		if (JumpPower < MaxGravity) 
		{
			JumpPower += Gravity;
		}
		// �n�ʂɂ�����
		if (m_pos.y < Game::kScreenHeight * 0.25)
		{
			isJump = true;
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
	}
	else if (m_MoveFlag == true)
	{
		m_pos.x -= kSpeed;
	}
	//�����蔻��̍X�V
	m_colRect.SetRadius(m_pos.x, m_pos.y, m_radius);
}

void UFO::Draw()
{
	DrawCircle(m_pos.x, m_pos.y, m_radius, GetColor(255, 255, 0), true);
	DrawFormatString(8, 56, GetColor(255, 255, 255),
		"UFO�̍��W(%.2f, %.2f)", m_pos.x, m_pos.y);
	//�����蔻��̕\��
	m_colRect.DrawC(GetColor(255, 0, 0), false);
}


