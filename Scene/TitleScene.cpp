#include<DxLib.h>
#include "../Input.h"
#include "../Game.h"
#include "SceneManager.h"
#include "TitleScene.h"
//次のシーンのクラスをインクルードしておく
#include "TutorialScene.h"
#include "Stage1Scene.h"
#include <cassert>


namespace
{
	// アニメーション間隔
	constexpr int kAnimInterval = 3;
	// 高さ・幅
	constexpr int kAnimWidth = 400;
	constexpr int kAnimHeight = 400;
	// 縦横数
	constexpr int kRow = 8;
	constexpr int kLine = 8;
	// アニメーション数
	constexpr int kAnimNum = 60;

	constexpr int kShakeSize = 10;
}

void TitleScene::FadeInUpdate(Input& input)
{
	frame_--;
	if (frame_ <= 0) {//遷移条件
		updateFunc_ = &TitleScene::NormalUpdate;
		drawFunc_ = &TitleScene::NormalDraw;
	}
}

void TitleScene::NormalUpdate(Input& input)
{
	if (input.IsTriggered("OK"))
	{
		PlaySoundMem(CheckSE,DX_PLAYTYPE_BACK);
		updateFunc_ = &TitleScene::FadeOutUpdate;
		drawFunc_ = &TitleScene::FadeDraw;
		DeleteGraph(m_titleButton);
		DeleteGraph(m_titleHandle);
	}

	m_bgFrame--;
	AnimFrame = (AnimFrame + 1) % (kAnimNum * kAnimInterval);
	
	if (m_isShake)
	{
		m_shakeFrame--;

		if (m_shakeFrame < 0)
		{
			m_isShake = false;
		}
	}
	m_loopFrame++;
}

void TitleScene::FadeOutUpdate(Input& input)
{
	frame_++;
	if (frame_ >= 60) {
		manager_.ChangeScene(std::make_shared<TutorialScene>(manager_));
	}
}

void TitleScene::FadeDraw()
{
	/*int index = AnimFrame / kAnimInterval;
	int srcX = (index % kRow) * kAnimWidth;
	int srcY = (index / kLine) * kAnimHeight;
	DrawRectRotaGraph(static_cast<int>(Game::kScreenWidth / 2), static_cast<int>(Game::kScreenHeight / 2),
		srcX, srcY, kAnimWidth, kAnimHeight,
		1.0, 0.0,
		m_animHandle, true, false);*/
	//フェード暗幕
	int alpha = 255 * (float)frame_ / 60.0f;
	SetDrawBlendMode(DX_BLENDMODE_MULA, alpha);
	DrawBox(0, 0, 1280, 720, 0x000000, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	//通常描画
	DrawGraph(Game::kScreenWidth / 2 - 225, Game::kScreenHeight * 0.25, m_titleHandle, true);
	DrawGraph(Game::kScreenWidth / 2 - 225, Game::kScreenHeight * 0.75 - 125, m_titleButton, true);

	ShakeScreen(frame_, kShakeSize);
}

void TitleScene::NormalDraw()
{	
	/*int index = AnimFrame / kAnimInterval;
	int srcX = (index % kRow) * kAnimWidth;
	int srcY = (index / kLine) * kAnimHeight;
	DrawRectRotaGraph(static_cast<int>(Game::kScreenWidth / 2), static_cast<int>(Game::kScreenHeight / 2),
		srcX, srcY, kAnimWidth, kAnimHeight,
		1.0, 0.0,
		m_animHandle, true, false);*/
	
	if (m_isShake)
	{
		SetDrawScreen(m_shakeHandle);
		ClearDrawScreen();
	}
	DrawGraph(Game::kScreenWidth / 2 - 225, Game::kScreenHeight * 0.25, m_titleHandle, true);
	DrawGraph(Game::kScreenWidth / 2 - 225, Game::kScreenHeight * 0.75 - 125, m_titleButton, true);	

	if (m_isShake)
	{
		SetDrawScreen(DX_SCREEN_BACK);

		int x = GetRand(m_shakeSize) - static_cast<int>(m_shakeSize * 0.5f);
		int y = GetRand(m_shakeSize) - static_cast<int>(m_shakeSize * 0.5f);
		DrawGraph(x, y, m_shakeHandle, true);
	}
	if (m_loopFrame > 120)
	{
		ShakeScreen(frame_, kShakeSize);
		m_loopFrame = 0;
	}
}

void TitleScene::BackScroll(const int t_areaX, const int tD_graph, const int t_winWidth, const int t_winHeight)
{
	DrawRectGraph(0, 0, t_areaX, 0, t_winWidth, t_winHeight, tD_graph, false);
	DrawRectGraph(t_winWidth - t_areaX, 0, 0, 0, t_areaX, t_winHeight, tD_graph, false);
}

TitleScene::TitleScene(SceneManager& manager) : Scene(manager),
frame_(0),
m_bgHandle(-1),
m_titleHandle(-1),
m_animHandle(-1),
areaX(0),
speed(20),
AnimFrame(0),
m_bgFrame(1),
m_bgPosX(0),
m_shakeHandle(-1),
m_shakeFrame(0),
m_shakeSize(kShakeSize),
m_loopFrame(0),
m_bgm(-1),
CheckSE(-1),
m_isShake(false)
{
	m_shakeHandle = MakeScreen(Game::kScreenWidth, Game::kScreenHeight);
	m_bgHandle = LoadGraph("data/Title.png");
	assert(m_bgHandle != -1);
	m_animHandle = LoadGraph("data/Moon.png");
	assert(m_animHandle != -1);
	m_titleHandle = LoadGraph("data/Icon.png");
	assert(m_bgHandle != -1);
	m_titleButton = LoadGraph("data/StartButton.png");
	assert(m_titleButton != -1);
	m_bgm = LoadSoundMem("data/Sound/TitleBGM.mp3");
	assert(m_bgm != -1);
	CheckSE = LoadSoundMem("data/Sound/Check.mp3");
	assert(CheckSE != -1);

	frame_ = 60;
	updateFunc_ = &TitleScene::FadeInUpdate;
	drawFunc_ = &TitleScene::FadeDraw;
	PlaySoundMem(m_bgm, DX_PLAYTYPE_LOOP);
	ChangeVolumeSoundMem(100, m_bgm);
}

TitleScene::~TitleScene()
{
	DeleteGraph(m_bgHandle);
	DeleteGraph(m_animHandle);
	DeleteGraph(m_titleHandle);
	DeleteGraph(m_shakeHandle);
	StopSoundMem(m_bgm);
}

void TitleScene::Init()
{
}

void TitleScene::Update(Input& input)
{
	(this->*updateFunc_)(input);
}

void TitleScene::Draw()
{
	DrawGraph(m_bgPosX, 0, m_bgHandle, true);	
	(this->*drawFunc_)();
}

void TitleScene::ShakeScreen(int frame, int size = kShakeSize)
{
	m_shakeFrame = frame_;
	m_isShake = true;
	m_shakeSize = size;
}