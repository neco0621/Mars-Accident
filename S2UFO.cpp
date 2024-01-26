#include "S2UFO.h"
#include "DxLib.h"
#include "Pad.h"
#include "Game.h"
#include "Rect.h"
#include "Scene/Stage1Scene.h"
#include "ShotBeam.h"

#define PI 3.14
#define AnimExpDivX 10
#define AnimExpDivY 8
#define AnimExpWidth 100
#define AnimExpHeight 100
#include <cmath>

namespace
{
	//UFO�̕\���ʒu
	constexpr float kPosX = Game::kScreenWidth / 2 - 100;
	constexpr float kPosY = Game::kScreenHeight / 4;

	//UFO�̃T�C�Y
	constexpr float kWidth = 40;
	constexpr float kHeight = 40;

	//UFO�̔��a
	constexpr float kRadius = 40;

	constexpr float kSpeed = 3.0f;

	// �A�j���[�V�����Ԋu
	constexpr int kAnimInterval = 3;
	// �����E��
	constexpr int kAnimWidth = 100;
	constexpr int kAnimHeight = 100;
	// �c����
	constexpr int kRow = 10;
	constexpr int kLine = 8;
	// �A�j���[�V������
	constexpr int kAnimNum = 71;

	constexpr int kS2UfoMax = 2;
}

S2UFO::S2UFO(Stage2Scene* pS2Scene) :
	m_pS2Scene(pS2Scene),
	m_handle(-1),
	m_pos(kPosX, kPosY),
	m_boundFlag(false),
	m_radius(kRadius),
	m_vec(0, kSpeed),
	m_MoveFlag(false),
	isJump(true),
	KnockBack(false),
	JumpPower(10),
	m_tq(Game::kScreenHeight * 0.75f),
	m_animHnadle(-1),
	AnimPosX(0),
	m_ufoS2Max(kS2UfoMax),
	m_animFrame(0)
{
}

S2UFO::~S2UFO()
{
}

void S2UFO::Init()
{
	m_colRect.SetCenter(m_pos.x, m_pos.y, kWidth, kHeight);
	//m_pAnimation->AnimationStart(m_pAnimation, 1000, 500);
}

void S2UFO::Update()
{
	if (isJump)
	{
		m_pos.y -= JumpPower;
		// �����ʒ���
		if (JumpPower > -MaxGravity)
		{
			JumpPower -= Gravity;
		}
		// �n�ʂɂ�����
		if (m_pos.y >= m_tq - m_radius / 2)
		{
			//m_pAnimation->DrawAnimation(m_pAnimation->AnimExpl);
			m_pos.y = m_tq - m_radius / 2;
			JumpPower = 30;
			AnimPosX = m_pos.x;
			AnimFlag = true;
		}
	}

	if (AnimFlag == true)
	{
		m_animFrame = (m_animFrame + 1) % (kAnimNum * kAnimInterval);
		m_animFrame++;
	}

	if (m_animFrame >= 120)
	{
		AnimFlag = false;
		m_animFrame = 0;
	}


	if (m_pos.x >= Game::kScreenWidth - m_radius)
	{
		m_MoveFlag = false;
	}
	else if (m_pos.x <= 0 + m_radius)
	{
		m_MoveFlag = true;
	}

	if (m_MoveFlag == false)
	{
		m_pos.x -= kSpeed;
		m_angle--;
	}
	else if (m_MoveFlag == true)
	{
		m_pos.x += kSpeed;
		m_angle++;
	}
	//�����蔻��̍X�V
	m_colRect.SetRadius(m_pos.x, m_pos.y, m_radius);

}

void S2UFO::Draw()
{
#ifdef DEBUG
	DrawFormatString(8, 56, GetColor(255, 255, 255),"%f", m_angle);
	m_colRect.DrawC(GetColor(255, 0, 0), false);
#endif 
	

	DrawRotaGraph(static_cast<int>(m_pos.x), static_cast<int>(m_pos.y),
		1.0, DX_PI_F / 180.0 * m_angle,
		m_handle, true);

	if (AnimFlag == true)
	{
		int index = m_animFrame / kAnimInterval;
		int srcX = (index % kRow) * kAnimWidth;
		int srcY = (index / kLine) * kAnimHeight;

		DrawRectRotaGraph(static_cast<int>(AnimPosX), static_cast<int>(m_tq + 25),
			srcX, srcY, kAnimWidth, kAnimHeight,
			1.0, 0.0,
			m_animHnadle, true, false);
	}
}