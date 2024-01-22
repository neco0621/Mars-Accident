#include <DxLib.h>
#include <cassert>
#include "GameOverScene.h"
#include "GameClearScene.h"
#include "../Input.h"
#include "SceneManager.h"
#include "TitleScene.h"
#include "../Game.h"

GameClearScene::GameClearScene(SceneManager& mgr) : Scene(mgr)
{
	m_updateFunc = &GameClearScene::FadeInUpdate;
	m_drawFunc = &GameClearScene::FadeDraw;
	frame_ = 60;
}

GameClearScene::~GameClearScene()
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
	DrawString(Game::kScreenWidth / 2, Game::kScreenHeight * 0.25, "GameClear", 0xffffff);

	int alpha = static_cast<int>(255 * (static_cast<float>(frame_) / 60.0f));
	SetDrawBlendMode(DX_BLENDMODE_MULA, alpha);
	DrawBox(0, 0, Game::kScreenWidth, Game::kScreenWidth, 0x000000, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

void GameClearScene::NormalDraw()
{
	DrawString(Game::kScreenWidth / 2, Game::kScreenHeight * 0.25, "GameClear", 0xffffff);

}
