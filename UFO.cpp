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

	//UFOの動くスピード
	constexpr float kSpeed = 3.0f;

	// アニメーション間隔
	constexpr int kAnimInterval = 3;
	// 高さ・幅
	constexpr int kAnimWidth = 100;
	constexpr int kAnimHeight = 100;
	// 縦横数
	constexpr int kRow = 10;
	constexpr int kLine = 8;
	// アニメーション数
	constexpr int kAnimNum = 71;
}

UFO::UFO(TutorialScene* pTuScene) :
	m_pTuScene(pTuScene),
	m_handle(-1),
	m_pos(kPosX, kPosY),
	m_boundFlag(false),
	m_radius(kRadius),
	m_vec(0, kSpeed),
	m_MoveFlag(false),
	isJump(true),
	KnockBack(false),
	AnimFlag(false),
	JumpPower(10),
	m_tq(Game::kScreenHeight * 0.75f),
	m_animHnadle(-1),
	m_soundHandle(-1),
	AnimPosX(0),
	m_angle(0),
	m_pS1Scene(nullptr),
	m_pS2Scene(nullptr),
	m_animFrame(0)
{
	m_soundHandle = LoadSoundMem(L"data/Sound/UFO.mp3");
}

UFO::UFO(Stage1Scene* pS1Scene) :
	m_pS1Scene(pS1Scene),
	m_handle(-1),
	m_pos(kPosX, kPosY),
	m_boundFlag(false),
	m_radius(kRadius),
	m_vec(0,kSpeed),
	m_MoveFlag(false),
	isJump(true),
	KnockBack(false),
	AnimFlag(false),
	JumpPower(10),
	m_tq(Game::kScreenHeight * 0.75f),
	m_animHnadle(-1),
	m_soundHandle(-1),
	AnimPosX(0),
	m_angle(0),
	m_pS2Scene(nullptr),
	m_animFrame(0),
	m_pTuScene(nullptr)
{
	m_soundHandle = LoadSoundMem(L"data/Sound/UFO.mp3");
}

UFO::UFO(Stage2Scene* pS2Scene) :
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
	m_animFrame(0),
	m_soundHandle(-1),
	AnimFlag(false),
	m_angle(0),
	m_pS1Scene(nullptr),
	m_pTuScene(nullptr)
{
	m_soundHandle = LoadSoundMem(L"data/Sound/UFO.mp3");
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
	//UFOが地面についていない時
	if (isJump)
	{
		m_pos.y -= JumpPower;
		// 落下量調整
		if (JumpPower > -MaxGravity) 
		{	 
			JumpPower -= Gravity / 2;
		}
		// 地面についた時
		if (m_pos.y >= m_tq - m_radius / 2)
		{
			PlaySoundMem(m_soundHandle, DX_PLAYTYPE_BACK);
			m_pos.y = m_tq - m_radius / 2;
			JumpPower = 20;
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
	//UFOを回転させながら描画
	DrawRotaGraph(static_cast<int>(m_pos.x), static_cast<int>(m_pos.y),
		1.0, DX_PI_F / 180.0 * m_angle,
		m_handle, true);
#ifdef _DEBUG
	m_colRect.DrawC(GetColor(255, 0, 0), false);
#endif 

	//アニメーションの再生
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