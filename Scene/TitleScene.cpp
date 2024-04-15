#include<DxLib.h>
#include "../Input.h"
#include "../Game.h"
#include "SceneManager.h"
#include "TitleScene.h"
//���̃V�[���̃N���X���C���N���[�h���Ă���
#include "TutorialScene.h"
#include "Stage1Scene.h"
#include <cassert>


namespace
{
	// �A�j���[�V�����Ԋu
	constexpr int kAnimInterval = 3;
	// �����E��
	constexpr int kAnimWidth = 400;
	constexpr int kAnimHeight = 400;
	// �c����
	constexpr int kRow = 8;
	constexpr int kLine = 8;
	// �A�j���[�V������
	constexpr int kAnimNum = 60;
	//��ʗh��̃T�C�Y
	constexpr int kShakeSize = 10;
	//X���W�ׂ̍����ʒu����
	constexpr int kAdjustmentWidth = 225;
	//Y���W�ׂ̍����ʒu����
	constexpr int kAdjustmentHeight = 125;
}

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
	//Enter�������ꂽ�Ƃ�
	if (input.IsTriggered("OK"))
	{
		//���莞�̃T�E���h�𗬂�
		PlaySoundMem(CheckSE,DX_PLAYTYPE_BACK);

		//FadeUpdate��FadeDraw���Ă�
		updateFunc_ = &TitleScene::FadeOutUpdate;
		drawFunc_ = &TitleScene::FadeDraw;
		
		//�A�C�R���ƌ���{�^���̍폜
		DeleteGraph(m_titleButton);
		DeleteGraph(m_titleHandle);
	}

	m_bgFrame--;
	AnimFrame = (AnimFrame + 1) % (kAnimNum * kAnimInterval);
	
	if (m_isShake)
	{
		m_shakeFrame--;

		if (m_shakeFrame < 0)
		{
			m_isShake = false;
		}
	}
	m_loopFrame++;
}

void TitleScene::FadeOutUpdate(Input& input)
{
	frame_++;
	if (frame_ >= 60) {
		//���̃V�[���Ɉړ�����
		manager_.ChangeScene(std::make_shared<TutorialScene>(manager_));
	}
}

void TitleScene::FadeDraw()
{
	//�t�F�[�h�Ö�
	int alpha = 255 * (float)frame_ / 60.0f;
	SetDrawBlendMode(DX_BLENDMODE_MULA, alpha);
	DrawBox(0, 0, 1280, 720, 0x000000, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	//�ʏ�`��
	DrawGraph(Game::kScreenWidth * 0.5f - m_AdjustmentWidth, Game::kScreenHeight * 0.25f, m_titleHandle, true);
	DrawGraph(Game::kScreenWidth * 0.5f - m_AdjustmentWidth, Game::kScreenHeight * 0.75f - m_AdjustmentHeight, m_titleButton, true);
	//��ʗh��̏���
	ShakeScreen(frame_, kShakeSize);
}

void TitleScene::NormalDraw()
{	
	if (m_isShake)
	{
		SetDrawScreen(m_shakeHandle);
		ClearDrawScreen();
	}
	DrawGraph(Game::kScreenWidth * 0.5f - m_AdjustmentWidth, Game::kScreenHeight * 0.25f, m_titleHandle, true);
	DrawGraph(Game::kScreenWidth * 0.5f - m_AdjustmentWidth, Game::kScreenHeight * 0.75f - m_AdjustmentHeight, m_titleButton, true);

	if (m_isShake)
	{
		SetDrawScreen(DX_SCREEN_BACK);

		int x = GetRand(m_shakeSize) - static_cast<int>(m_shakeSize * 0.5f);
		int y = GetRand(m_shakeSize) - static_cast<int>(m_shakeSize * 0.5f);
		DrawGraph(x, y, m_shakeHandle, true);
	}
	if (m_loopFrame > 120)
	{
		ShakeScreen(frame_, kShakeSize);
		m_loopFrame = 0;
	}
}

TitleScene::TitleScene(SceneManager& manager) : Scene(manager),
//������
frame_(0),
m_bgHandle(-1),
m_titleHandle(-1),
AnimFrame(0),
m_bgFrame(1),
m_bgPosX(0),
m_shakeHandle(-1),
m_shakeFrame(0),
m_shakeSize(kShakeSize),
m_loopFrame(0),
m_bgm(-1),
CheckSE(-1),
m_isShake(false),
m_AdjustmentWidth(kAdjustmentWidth),
m_AdjustmentHeight(kAdjustmentHeight)
{
	m_shakeHandle = MakeScreen(Game::kScreenWidth, Game::kScreenHeight);
	m_bgHandle = LoadGraph(L"data/Title.png");
	assert(m_bgHandle != -1);
	m_titleHandle = LoadGraph(L"data/Icon.png");
	assert(m_bgHandle != -1);
	m_titleButton = LoadGraph(L"data/StartButton.png");
	assert(m_titleButton != -1);
	m_bgm = LoadSoundMem(L"data/Sound/TitleBGM.mp3");
	assert(m_bgm != -1);
	CheckSE = LoadSoundMem(L"data/Sound/Check.mp3");
	assert(CheckSE != -1);

	frame_ = 60;
	updateFunc_ = &TitleScene::FadeInUpdate;
	drawFunc_ = &TitleScene::FadeDraw;
	PlaySoundMem(m_bgm, DX_PLAYTYPE_LOOP);
}

TitleScene::~TitleScene()
{
	//�������̊J��
	DeleteGraph(m_bgHandle);
	DeleteGraph(m_titleHandle);
	DeleteGraph(m_shakeHandle);
	StopSoundMem(m_bgm);
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
	DrawGraph(m_bgPosX, 0, m_bgHandle, true);	
	(this->*drawFunc_)();
}

void TitleScene::ShakeScreen(int frame, int size = kShakeSize)
{
	m_shakeFrame = frame_;
	m_isShake = true;
	m_shakeSize = size;
}