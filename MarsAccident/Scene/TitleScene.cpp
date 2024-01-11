#include<DxLib.h>
#include "../Input.h"
#include "../Game.h"
#include "SceneManager.h"
#include "TitleScene.h"
//���̃V�[���̃N���X���C���N���[�h���Ă���
#include "SceneMain.h"
#include <cassert>


void TitleScene::FadeInUpdate(Input& input)
{
	frame_--;
	if (frame_ <= 0) {//�J�ڏ���
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
}

void TitleScene::FadeOutUpdate(Input& input)
{
	frame_++;
	if (frame_ >= 60) {
		manager_.ChangeScene(std::make_shared<SceneMain>(manager_));
	}
}

void TitleScene::FadeDraw()
{
	//�ʏ�`��
	DrawString(Game::kScreenWidth / 2 - 24, Game::kScreenHeight / 4, "MarsAccident", 0xffffff);
	DrawString(Game::kScreenWidth / 2, Game::kScreenHeight - (Game::kScreenHeight / 4), "START", 0xffffff);

	//�t�F�[�h�Ö�
	int alpha = 255 * (float)frame_ / 60.0f;
	SetDrawBlendMode(DX_BLENDMODE_MULA, alpha);
	DrawBox(0, 0, 1280, 720, 0x000000, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

void TitleScene::NormalDraw()
{
	DrawString(Game::kScreenWidth / 2 - 24, Game::kScreenHeight / 4, "MarsAccident", 0xffffff);
	DrawString(Game::kScreenWidth / 2, Game::kScreenHeight - (Game::kScreenHeight / 4), "START", 0xffffff);
}

TitleScene::TitleScene(SceneManager& manager) : Scene(manager)
{
	//handle_ = LoadGraph("data/img/title.png");
	assert(handle_ >= 0);
	frame_ = 60;
	updateFunc_ = &TitleScene::FadeInUpdate;
	drawFunc_ = &TitleScene::FadeDraw;
}

TitleScene::~TitleScene()
{
	DeleteGraph(handle_);
}

void TitleScene::Update(Input& input)
{
	(this->*updateFunc_)(input);
}

void TitleScene::Draw()
{
	(this->*drawFunc_)();
}