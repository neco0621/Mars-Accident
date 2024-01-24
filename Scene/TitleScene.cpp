#include<DxLib.h>
#include "../Input.h"
#include "../Game.h"
#include "SceneManager.h"
#include "TitleScene.h"
//次のシーンのクラスをインクルードしておく
#include "Stage1Scene.h"
#include <cassert>


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
	if (CheckHitKey(KEY_INPUT_A))
	{
		areaX -= speed;
		if (areaX < 0)
		{
			areaX = 640;
		}
	}
	if (CheckHitKey(KEY_INPUT_D))
	{
		areaX += speed;
		if (areaX > 640)
		{
			areaX = 0;
		}
	}
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
	for (int i = 0; i < 64; i++)
	{
		DrawRectGraph(100,100, i,i,i*64,i*64,m_moon,true);
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
areaX(0),
speed(20)
{
	m_bgHandle = LoadGraph("data/Title.bmp");
	m_moon = LoadGraph("data/Moon.png");
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
