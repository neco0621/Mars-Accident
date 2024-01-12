#include <DxLib.h>
#include <cassert>
#include "SceneMain.h"
#include "GameOverScene.h"
#include "../Input.h"
#include "SceneManager.h"
#include "TitleScene.h"
#include "../Game.h"
#include "../Stage/StageBase.h"
#include "../Stage/StageManager.h"
#include "../Stage/Stage1.h"
#include "../Stage/Stage2.h"
#include "../Stage/Stage3.h"


SceneMain::SceneMain(SceneManager& manager) : Scene(manager)
{
	m_updateFunc = &SceneMain::FadeInUpdate;
	m_drawFunc = &SceneMain::FadeDraw;
	frame_ = 60;
}

SceneMain::~SceneMain()
{
	
}

void SceneMain::Init()
{
	//SceneŠJŽn
	SceneManager manager;
	manager.ChangeScene(std::make_shared<TitleScene>(manager));
}

void SceneMain::Update(Input& input)
{

	manager.Update(input);
	manager.Draw();
}

void SceneMain::Draw()
{
	(this->*m_drawFunc)();
}

void SceneMain::FadeInUpdate(Input&)
{
	frame_--;
	if (frame_ <= 0)
	{
		m_updateFunc = &SceneMain::NormalUpdate;
		m_drawFunc = &SceneMain::NormalDraw;
	}
}

void SceneMain::NormalUpdate(Input& input)
{
	if (input.IsTriggered("OK"))
	{
		m_updateFunc = &SceneMain::FadeOutUpdate;
		m_drawFunc = &SceneMain::FadeDraw;
	}
}

void SceneMain::FadeOutUpdate(Input&)
{
	frame_++;
	if (60 <= frame_)
	{
		manager_.ChangeScene(std::make_shared<TitleScene>(manager_));
	}
}

void SceneMain::FadeDraw()
{
	int alpha = static_cast<int>(255 * (static_cast<float>(frame_) / 60.0f));
	SetDrawBlendMode(DX_BLENDMODE_MULA, alpha);
	DrawBox(0, 0, Game::kScreenWidth, Game::kScreenWidth, 0x000000, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

void SceneMain::NormalDraw()
{
}
