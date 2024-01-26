#include<DxLib.h>
#include "../Input.h"
#include "../Game.h"
#include "SceneManager.h"
#include "TitleScene.h"
//次のシーンのクラスをインクルードしておく
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
		updateFunc_ = &TitleScene::FadeOutUpdate;
		drawFunc_ = &TitleScene::FadeDraw;
	}
	m_bgFrame--;
	//BackScroll(areaX, m_bgHandle, 640, 480);
	AnimFrame = (AnimFrame + 1) % (kAnimNum * kAnimInterval);
}

void TitleScene::FadeOutUpdate(Input& input)
{
	frame_++;
	if (frame_ >= 60) {
		manager_.ChangeScene(std::make_shared<Stage1Scene>(manager_));
	}
}

void TitleScene::FadeDraw()
{
	int index = AnimFrame / kAnimInterval;
	int srcX = (index % kRow) * kAnimWidth;
	int srcY = (index / kLine) * kAnimHeight;
	DrawRectRotaGraph(static_cast<int>(Game::kScreenWidth / 2), static_cast<int>(Game::kScreenHeight / 2),
		srcX, srcY, kAnimWidth, kAnimHeight,
		1.0, 0.0,
		m_animHandle, true, false);
	//フェード暗幕
	int alpha = 255 * (float)frame_ / 60.0f;
	SetDrawBlendMode(DX_BLENDMODE_MULA, alpha);
	DrawBox(0, 0, 1280, 720, 0x000000, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	//通常描画
	DrawGraph(Game::kScreenWidth / 2 -225, Game::kScreenHeight * 0.25, m_titleHandle, true);
	DrawString(Game::kScreenWidth / 2, Game::kScreenHeight * 0.75, "START", 0xffffff);	
}

void TitleScene::NormalDraw()
{
	int index = AnimFrame / kAnimInterval;
	int srcX = (index % kRow) * kAnimWidth;
	int srcY = (index / kLine) * kAnimHeight;

	DrawRectRotaGraph(static_cast<int>(Game::kScreenWidth / 2), static_cast<int>(Game::kScreenHeight / 2),
		srcX, srcY, kAnimWidth, kAnimHeight,
		1.0, 0.0,
		m_animHandle, true, false);
	DrawGraph(Game::kScreenWidth / 2 - 225, Game::kScreenHeight * 0.25, m_titleHandle, true);
	DrawString(Game::kScreenWidth / 2, Game::kScreenHeight * 0.75, "START", 0xffffff);	
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
m_bgPosX(0)
{
	m_bgHandle = LoadGraph("data/Title.png");
	m_animHandle = LoadGraph("data/Moon.png");
	m_titleHandle = LoadGraph("data/Icon.png");
	assert(m_bgHandle >= 0);
	frame_ = 60;
	updateFunc_ = &TitleScene::FadeInUpdate;
	drawFunc_ = &TitleScene::FadeDraw;
}

TitleScene::~TitleScene()
{
	DeleteGraph(m_bgHandle);
	DeleteGraph(m_animHandle);
	DeleteGraph(m_titleHandle);
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
	if(m_bgFrame >)
	DrawGraph(m_bgPosX, 0, m_bgHandle, true);	
	(this->*drawFunc_)();
}
