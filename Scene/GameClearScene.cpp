#include "GameOverScene.h"
#include "GameClearScene.h"
#include "SceneManager.h"
#include "TitleScene.h"
#include "../Input.h"
#include "../Game.h"

#include <DxLib.h>
#include <cassert>

namespace
{
	//�t�F�[�h�Ɋւ���t���[�����̏����l
	constexpr int kFrame			= 60;
	//X���̒���
	constexpr int kWidthAdjustment	= 225;
	//Y���̒���
	constexpr int kHeightAdjustment = 127;
}

GameClearScene::GameClearScene(SceneManager& mgr) : Scene(mgr),
//������
m_clearSE(0),
m_bgm(0),
m_bg(-1),
m_gameClear(-1),
m_titleBack(-1),
m_widthAdjustment(kWidthAdjustment),
m_heightAdjustment(kHeightAdjustment)
{
	//m_updateFunc�̒��g��FadeInUpdate
	m_updateFunc = &GameClearScene::FadeInUpdate;
	m_drawFunc = &GameClearScene::FadeDraw;
	//�t�F�[�h�Ɋւ���t���[�����̏����l��kFrame(60)�ɐݒ�
	frame_ = kFrame;
	
	//�Q�[���N���A�̕����\���̃O���t�B�b�N�����[�h
	m_gameClear = LoadGraph("data/GameClear.png");
	//�w�i�̃O���t�B�b�N�����[�h
	m_bg = LoadGraph("data/GameClearBg.png");
	//�^�C�g���֖߂�̃{�^���̃n���h���̃��[�h
	m_titleBack = LoadGraph("data/TitleBack.png");
	//�Q�[���N���A���̃T�E���h�����[�h
	m_clearSE = LoadSoundMem("data/Sound/ClearSE.mp3");
	//BGM�̃T�E���h�����[�h
	m_bgm = LoadSoundMem("data/Sound/ClearSceneBgm.mp3");

	//BGM�̍Đ�
	PlaySoundMem(m_bgm, DX_PLAYTYPE_LOOP);
}

GameClearScene::~GameClearScene()
{
	//BGM���~�߂�
	StopSoundMem(m_bgm);

	//����������O���t�B�b�N���폜
	DeleteGraph(m_gameClear);
	DeleteGraph(m_bg);
	DeleteGraph(m_titleBack);

	//����������T�E���h���폜
	DeleteSoundMem(m_bgm);
	DeleteSoundMem(m_clearSE);
}

void GameClearScene::Init()
{
}

void GameClearScene::Update(Input& input)
{
	//FadeInUpdate���Ăяo��
	(this->*m_updateFunc)(input);
}

void GameClearScene::Draw()
{
	//FadeDraw���Ăяo��
	(this->*m_drawFunc)();
}

void GameClearScene::FadeInUpdate(Input&)
{
	//�t�F�C�h�Ɋւ���t���[���������X�ɉ�����
	frame_--;
	//frame_��0�ȉ��ɂȂ�����
	if (frame_ <= 0)
	{
		//m_updateFunc�̒��g��NormalUpdate�ɕς���
		m_updateFunc = &GameClearScene::NormalUpdate;
		//m_drawFunc�̒��g��NormalDraw�ɕς���
		m_drawFunc = &GameClearScene::NormalDraw;
	}
}

void GameClearScene::NormalUpdate(Input& input)
{
	//OK�L�[(Enter�L�[)�������ꂽ�Ƃ�
	if (input.IsTriggered("OK"))
	{
		//m_updateFunc�̒��g��FadeOutUpdate�ɕς���
		m_updateFunc = &GameClearScene::FadeOutUpdate;
		//m_drawFunc�̒��g��FadeDraw�ɕς���
		m_drawFunc = &GameClearScene::FadeDraw;
	}
}

void GameClearScene::FadeOutUpdate(Input&)
{
	//�t�F�C�h�Ɋւ���t���[���������X�ɏグ��
	frame_++;
	//frame_��kFrame(60)�ȏ�ɂȂ�����
	if (kFrame <= frame_)
	{
		//�^�C�g���V�[���ɕς���
		manager_.ChangeScene(std::make_shared<TitleScene>(manager_));
	}
}

void GameClearScene::FadeDraw()
{
	//�w�i�̕`��
	DrawGraph(0,0,m_bg,true);
	//�Q�[���N���A�{�^���̕`��
	DrawGraph(Game::kScreenWidth / 2 - m_widthAdjustment,
		Game::kScreenHeight * 0.25 - m_heightAdjustment, m_gameClear, true);
	//�^�C�g���֖߂�̃{�^���`��
	DrawGraph(Game::kScreenWidth / 2 - m_widthAdjustment,
		Game::kScreenHeight * 0.75 - m_heightAdjustment, m_titleBack, true);
	//Fade���̈Ö��̕`��
	int alpha = static_cast<int>(255 * (static_cast<float>(frame_) / 60.0f));
	SetDrawBlendMode(DX_BLENDMODE_MULA, alpha);
	DrawBox(0, 0, Game::kScreenWidth, Game::kScreenWidth, 0x000000, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

void GameClearScene::NormalDraw()
{
	//�w�i�̕`��
	DrawGraph(0, 0, m_bg, true);
	//�Q�[���N���A�{�^���̕`��
	DrawGraph(Game::kScreenWidth / 2 - m_widthAdjustment, 
		Game::kScreenHeight * 0.25 - m_heightAdjustment, m_gameClear, true);
	//�^�C�g���֖߂�̃{�^���`��
	DrawGraph(Game::kScreenWidth / 2 - m_widthAdjustment, 
		Game::kScreenHeight * 0.75 - m_heightAdjustment, m_titleBack, true);
}
// <a href = "https://jp.freepik.com/free-vector/pixel-art-mystical-background_29019077.htm#query=pixel%20art&position=0&from_view=keyword&track=ais&uuid=acea7397-7e5c-4d2b-8020-153b3f30c072">����ҁFpikisuperstar< / a>�^�o�T�FFreepik