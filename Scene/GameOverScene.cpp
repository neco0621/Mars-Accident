#include <DxLib.h>
#include <cassert>
#include "GameOverScene.h"
#include "../Input.h"
#include "SceneManager.h"
#include "TitleScene.h"
#include "Stage1Scene.h"
#include "../Game.h"

GameOverScene::GameOverScene(SceneManager& mgr) : Scene(mgr),
m_gameOver(-1),
m_titleBack(-1),
m_bg(-1),
m_bgm(-1),
m_retry(-1)
{
	m_updateFunc = &GameOverScene::FadeInUpdate;
	m_drawFunc = &GameOverScene::FadeDraw;
	frame_ = 60;

	m_gameOver = LoadGraph("data/GameOver.png");
	m_titleBack = LoadGraph("data/TitleBack.png");
	m_bg = LoadGraph("data/GameOverBg.png");
	m_bgm = LoadSoundMem("data/Sound/GameOverBgm.mp3");
	m_retry = LoadGraph("data/Retry.png");

	PlaySoundMem(m_bgm, DX_PLAYTYPE_LOOP);
}

GameOverScene::~GameOverScene()
{
	StopSoundMem(m_bgm);
	DeleteSoundMem(m_bgm);
}

void GameOverScene::Init()
{
}

void GameOverScene::Update(Input& input)
{
	(this->*m_updateFunc)(input);
}

void GameOverScene::Draw()
{
	(this->*m_drawFunc)();
}

void GameOverScene::FadeInUpdate(Input&)
{
	frame_--;
	if (frame_ <= 0)
	{
		m_updateFunc = &GameOverScene::NormalUpdate;
		m_drawFunc = &GameOverScene::NormalDraw;
	}
}

void GameOverScene::NormalUpdate(Input& input)
{
	if (input.IsTriggered("OK"))
	{
		m_updateFunc = &GameOverScene::FadeOutUpdate;
		m_drawFunc = &GameOverScene::FadeDraw;
	}

	if (CheckHitKey(KEY_INPUT_R))
	{
		manager_.ChangeScene(std::make_shared<Stage1Scene>(manager_));
	}
}

void GameOverScene::FadeOutUpdate(Input&)
{
	frame_++;
	if (60 <= frame_)
	{
		manager_.ChangeScene(std::make_shared<TitleScene>(manager_));
	}
}

void GameOverScene::FadeDraw()
{
	DrawGraph(0,0,m_bg,true);
	DrawGraph(Game::kScreenWidth / 2 - 225, Game::kScreenHeight * 0.25 - 127, m_gameOver, true);
	DrawGraph(Game::kScreenWidth / 2 - 225, Game::kScreenHeight * 0.75 - 127, m_titleBack, true);
	//DrawFormatString(Game::kScreenWidth / 2 - 250, Game::kScreenHeight * 0.75 + 64 ,GetColor(255,0,0),"SPACEでリトライ");
	DrawGraph(Game::kScreenWidth / 2 - 235, Game::kScreenHeight * 0.75 - 10, m_retry, true);
	int alpha = static_cast<int>(255 * (static_cast<float>(frame_) / 60.0f));
	SetDrawBlendMode(DX_BLENDMODE_MULA, alpha);
	DrawBox(0, 0, Game::kScreenWidth, Game::kScreenWidth, 0x000000, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

void GameOverScene::NormalDraw()
{
	DrawGraph(0, 0, m_bg, true);
	DrawGraph(Game::kScreenWidth / 2 - 225, Game::kScreenHeight * 0.25 - 127, m_gameOver, true);
	DrawGraph(Game::kScreenWidth / 2 - 225, Game::kScreenHeight * 0.75 - 127, m_titleBack, true);
	DrawGraph(Game::kScreenWidth / 2 - 235, Game::kScreenHeight * 0.75 - 10, m_retry, true);
	//DrawFormatString(Game::kScreenWidth / 2 - 250, Game::kScreenHeight * 0.75 + 64, GetColor(255, 0, 0), "SPACEでリトライ");
}
