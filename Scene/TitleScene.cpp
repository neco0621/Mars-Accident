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
	constexpr int kAnimWidth = 48;
	constexpr int kAnimHeight = 48;
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
	BackScroll(areaX, m_bgHandle, 640, 480);
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
	//通常描画
	DrawString(Game::kScreenWidth / 2 - 24, Game::kScreenHeight * 0.25, "MarsAccident", 0xffffff);
	DrawString(Game::kScreenWidth / 2, Game::kScreenHeight * 0.75, "START", 0xffffff);

	//フェード暗幕
	int alpha = 255 * (float)frame_ / 60.0f;
	SetDrawBlendMode(DX_BLENDMODE_MULA, alpha);
	DrawBox(0, 0, 1280, 720, 0x000000, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

void TitleScene::NormalDraw()
{
	DrawString(Game::kScreenWidth / 2 - 24, Game::kScreenHeight * 0.25, "MarsAccident", 0xffffff);
	DrawString(Game::kScreenWidth / 2, Game::kScreenHeight * 0.75, "START", 0xffffff);
	int index = AnimFrame / kAnimInterval;
	int srcX = (index % kRow) * kAnimWidth;
	int srcY = (index / kLine) * kAnimHeight;

	DrawRectRotaGraph(static_cast<int>(100), static_cast<int>(100),
		srcX, srcY, kAnimWidth, kAnimHeight,
		1.0, 0.0,
		m_animHandle, true, false);
}

void TitleScene::BackScroll(const int t_areaX, const int tD_graph, const int t_winWidth, const int t_winHeight)
{
	DrawRectGraph(0, 0, t_areaX, 0, t_winWidth, t_winHeight, tD_graph, false);
	DrawRectGraph(t_winWidth - t_areaX, 0, 0, 0, t_areaX, t_winHeight, tD_graph, false);
}

TitleScene::TitleScene(SceneManager& manager) : Scene(manager),
frame_(0),
m_bgHandle(-1),
areaX(0),
speed(20),
AnimFrame(0)
{
	m_bgHandle = LoadGraph("data/Title.bmp");
	m_animHandle = LoadGraph("data/Moon.png");
	assert(m_bgHandle >= 0);
	frame_ = 60;
	updateFunc_ = &TitleScene::FadeInUpdate;
	drawFunc_ = &TitleScene::FadeDraw;
}

TitleScene::~TitleScene()
{
	DeleteGraph(m_bgHandle);
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
	DrawGraph(0,0,m_bgHandle,true);
	(this->*drawFunc_)();
}
