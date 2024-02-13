#include <DxLib.h>
#include <cassert>
#include "GameOverScene.h"
#include "GameClearScene.h"
#include "../Input.h"
#include "SceneManager.h"
#include "TitleScene.h"
#include "../Game.h"

GameClearScene::GameClearScene(SceneManager& mgr) : Scene(mgr),
m_clearSE(0),
m_bgm(0),
m_bg(-1),
m_gameClear(-1),
m_titleBack(-1)
{
	m_updateFunc = &GameClearScene::FadeInUpdate;
	m_drawFunc = &GameClearScene::FadeDraw;
	frame_ = 60;
	
	m_gameClear = LoadGraph("data/GameClear.png");
	m_bg = LoadGraph("data/GameClearBg.png");
	m_clearSE = LoadSoundMem("data/Sound/ClearSE.mp3");
	m_bgm = LoadSoundMem("data/Sound/ClearSceneBgm.mp3");
	m_titleBack = LoadGraph("data/TitleBack.png");

	PlaySoundMem(m_bgm, DX_PLAYTYPE_LOOP);
}

GameClearScene::~GameClearScene()
{
	StopSoundMem(m_bgm);
}

void GameClearScene::Init()
{
}

void GameClearScene::Update(Input& input)
{
	(this->*m_updateFunc)(input);
}

void GameClearScene::Draw()
{
	(this->*m_drawFunc)();
}

void GameClearScene::FadeInUpdate(Input&)
{
	frame_--;
	if (frame_ <= 0)
	{
		m_updateFunc = &GameClearScene::NormalUpdate;
		m_drawFunc = &GameClearScene::NormalDraw;
	}
}

void GameClearScene::NormalUpdate(Input& input)
{
	if (input.IsTriggered("OK"))
	{
		m_updateFunc = &GameClearScene::FadeOutUpdate;
		m_drawFunc = &GameClearScene::FadeDraw;
	}
}

void GameClearScene::FadeOutUpdate(Input&)
{
	frame_++;
	if (60 <= frame_)
	{
		manager_.ChangeScene(std::make_shared<TitleScene>(manager_));
	}
}

void GameClearScene::FadeDraw()
{
	DrawGraph(0,0,m_bg,true);
	DrawGraph(Game::kScreenWidth / 2 - 225, Game::kScreenHeight * 0.25 - 127, m_gameClear, true);
	DrawGraph(Game::kScreenWidth / 2 - 225, Game::kScreenHeight * 0.75 - 127, m_titleBack, true);
	int alpha = static_cast<int>(255 * (static_cast<float>(frame_) / 60.0f));
	SetDrawBlendMode(DX_BLENDMODE_MULA, alpha);
	DrawBox(0, 0, Game::kScreenWidth, Game::kScreenWidth, 0x000000, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

void GameClearScene::NormalDraw()
{
	DrawGraph(0, 0, m_bg, true);
	DrawGraph(Game::kScreenWidth / 2 - 225, Game::kScreenHeight * 0.25 - 127, m_gameClear, true);
	DrawGraph(Game::kScreenWidth / 2 - 225, Game::kScreenHeight * 0.75 - 127, m_titleBack, true);
}
