#include <DxLib.h>
#include <cassert>
#include "GameOverScene.h"
#include "../Input.h"
#include "SceneManager.h"
#include "TitleScene.h"
#include "../Game.h"

GameOverScene::GameOverScene(SceneManager& mgr) : Scene(mgr)
{
	m_updateFunc = &GameOverScene::FadeInUpdate;
	m_drawFunc = &GameOverScene::FadeDraw;
	frame_ = 60;
}

GameOverScene::~GameOverScene()
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
	DrawString(Game::kScreenWidth / 2, Game::kScreenHeight * 0.25, "GameOver", 0xffffff);
	
	int alpha = static_cast<int>(255 * (static_cast<float>(frame_) / 60.0f));
	SetDrawBlendMode(DX_BLENDMODE_MULA, alpha);
	DrawBox(0, 0, Game::kScreenWidth, Game::kScreenWidth, 0x000000, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

void GameOverScene::NormalDraw()
{
	DrawString(Game::kScreenWidth / 2, Game::kScreenHeight * 0.25, "GameOver", 0xffffff);
}
