#include "Player.h"
#include "DxLib.h"
#include "Pad.h"
#include "Game.h"
#include "Scene/TutorialScene.h"
#include "Scene/Stage1Scene.h"
#include "Scene/Stage2Scene.h"
#include "ShotBeam.h"

#include <cmath>

//Player�Ŏg�p����萔
namespace
{
	//�ړ����x
	constexpr float kSpeed = 5.0f;

	//�L�����N�^�[�̃T�C�Y
	constexpr int kWidth = 64;
	constexpr int kHeight = 64;

	//�L�����N�^�[�̃A�j���[�V����
	constexpr int kUseFrame[] = { 1,2,1 };

	//�A�j���[�V����1�R�}�̃t���[����
	constexpr int kAnimFrameNum = 8;

	//�A�j���[�V����1�T�C�N���̃t���[����
	constexpr int kAnimFrameCycle = _countof(kUseFrame) * kAnimFrameNum;

	//Shot�̔��ˊԊu
	constexpr int kBeamFrame = 20;
}

Player::Player(TutorialScene* pTuScene) :
	//������
	m_pTuScene(pTuScene),
	m_handle(-1),
	m_pos(Game::kScreenWidth * 0.5, Game::kScreenHeight * 0.75),
	m_dir(kDirRight),
	m_walkAnimFrame(0),
	m_beamFrame(0)
{
}

Player::Player(Stage1Scene* S1Scene) :
	//������
	m_pS1Scene(S1Scene),
	m_handle(-1),
	m_pos(Game::kScreenWidth * 0.5, Game::kScreenHeight * 0.75),
	m_dir(kDirRight),
	m_walkAnimFrame(0),
	m_beamFrame(0)
{
}

Player::Player(Stage2Scene* S2Scene) :
	//������
	m_pS2Scene(S2Scene),
	m_handle(-1),
	m_pos(Game::kScreenWidth * 0.5, Game::kScreenHeight * 0.75),
	m_dir(kDirRight),
	m_walkAnimFrame(0),
	m_beamFrame(0)

{
}

Player::~Player()
{
}

void Player::Init()
{
	
}

//�`���[�g���A���V�[���ł̍X�V����
void Player::TuUpdate()
{
	//pad�̏\���L�[���g�p����Player���ړ�������
	int pad = GetJoypadInputState(DX_INPUT_KEY_PAD1);


	/* (pad & PAD_INPUT_UP) == 0 �̌���*/
	//0000 0000 0000 0000 0000 0000 0000 0000�@��{
	//0000 0000 0000 0000 0000 0000 0000 1000�@��L�[�������ꂽ�Ƃ�

	//�ړ����Ă��邩�ǂ���
	bool isMove = false;	

	//�ړ��ʂ����悤�ɂ���
	Vec2 move{ 0.0f,0.0f };
	
	//A�������͍�����͂��Ă���Ƃ�
	if (((pad & PAD_INPUT_LEFT) | (pad & PAD_INPUT_4)) != 0)
	{
		//Player�����������悤�ɂ���
		m_dir = kDirLeft;

		//�ړ����Ă��邩
		isMove = true;

		//��ʔ����ɍs���Ȃ��悤�ɂ���
		if (m_pos.x <= kWidth / 2 - 10)
		{
			m_pos.x = kWidth / 2 - 10;
		}
		else
		{
			//���Ɉړ�����
			move.x -= kSpeed;
		}
	}

	//D�������͉E����͂��Ă���Ƃ�
	if (((pad & PAD_INPUT_RIGHT) | (pad & PAD_INPUT_6)) != 0)
	{
		//Player���E�������悤�ɂ���
		m_dir = kDirRight;

		//�ړ����Ă��邩
		isMove = true;

		//��ʔ����ɍs���Ȃ��悤�ɂ���
		if (m_pos.x >= Game::kScreenWidth - kWidth / 2 + 10)
		{
			m_pos.x = Game::kScreenWidth - kWidth / 2 + 10;
		}
		else
		{
			//�E�Ɉړ�����
			move.x += kSpeed;
		}
	}

	//�΂߈ړ��̏ꍇ�����������ňړ�����悤�ɂ���

	//�x�N�g���̐��K��
	move.normalize();

	//�x�N�g���̒�����kspeed�ɂ���
	move *= kSpeed;

	//���W�ƃx�N�g���̑����Z
	m_pos += move;

	//���S���W���w�肵�ē����蔻���Rect�𐶐�����.
	m_colRect.SetCenter(m_pos.x, m_pos.y + 15, kWidth - 35, kHeight - 5);

	//Player���ړ����Ă��鎞�ɃA�j���[�V�������J�n������
	if (isMove)
	{
		//�����A�j���[�V�����t���[���J�E���g���Z
		m_walkAnimFrame++;
		//�����A�j���[�V�����t���[���J�E���g��
		if (m_walkAnimFrame >= kAnimFrameCycle)
		{
			//�����A�j���[�V�����t���[���J�E���g�����Z�b�g����
			m_walkAnimFrame = 0;
		}
	}
	else
	{
		//�����A�j���[�V�����t���[���J�E���g��1�R�}�̃t���[���J�E���g�ɍ��킹��
		m_walkAnimFrame = kAnimFrameNum;
	}

	//�V���b�g�̃t���[���J�E���g�̉��Z
	m_beamFrame++;
	//Shot�̔��˃t���[���J�E���g�����ˊԊu���������Ƃ�
	if (m_beamFrame >= kBeamFrame)
	{
		//Shot�̃��������m��
		ShotBeam* m_pShot = new ShotBeam;
		//Shot��Scene���`���[�g���A���ɐݒ肷��
		m_pShot->SetTutorial(m_pTuScene);
		//�v���C���[�̈ʒu����ݒ肷��
		m_pShot->SetPlayer(this);
		//Shot���X�^�[�g������
		m_pShot->Start(GetPos());
		//�ȍ~�X�V�⃁�����̉����SceneMain�ɔC����
		m_pTuScene->AddShot(m_pShot);
		//Shot�̔��˃t���[���J�E���g�����Z�b�g����
		m_beamFrame = 0;
	}
}

void Player::Update()
{
	//pad�̏\���L�[���g�p����Player���ړ�������
	int pad = GetJoypadInputState(DX_INPUT_KEY_PAD1);


	/* (pad & PAD_INPUT_UP) == 0 �̌���*/
	//0000 0000 0000 0000 0000 0000 0000 0000�@��{
	//0000 0000 0000 0000 0000 0000 0000 1000�@��L�[�������ꂽ�Ƃ�

	bool isMove = false;	//�ړ����Ă��邩�ǂ���

	//�ړ��ʂ����悤�ɂ���
	Vec2 move{ 0.0f,0.0f };
	//A�������͍�����͂��Ă���Ƃ�
	if (((pad & PAD_INPUT_LEFT) | (pad & PAD_INPUT_4)) != 0)
	{
		//Player�����������悤�ɂ���
		m_dir = kDirLeft;
		//�����Ă��邩�ǂ���
		isMove = true;
		//Player����ʊO�ɍs���Ȃ��悤�ɂ���
		if (m_pos.x <= kWidth / 2 - 10)
		{
			m_pos.x = kWidth / 2 - 10;
		}
		else
		{
			//���Ɉړ�����
			move.x -= kSpeed;
		}		
	}
	//D�������͉E����͂��Ă���Ƃ�
	if (((pad & PAD_INPUT_RIGHT) | (pad & PAD_INPUT_6)) != 0)
	{
		//Player���E�������悤�ɂ��Ă���
		m_dir = kDirRight;
		//�����Ă��邩�ǂ���
		isMove = true;
		//Player����ʊO�ɍs���Ȃ��悤�ɂ���
		if (m_pos.x >= Game::kScreenWidth - kWidth / 2 + 10)
		{
			m_pos.x = Game::kScreenWidth - kWidth / 2 + 10;
		}
		else
		{
			//�E�Ɉړ�����
			move.x += kSpeed;
		}		
	}

	//�΂߈ړ��̏ꍇ�����������ňړ�����悤�ɂ���

	//�x�N�g���̐��K��
	move.normalize();

	//�x�N�g���̒�����kspeed�ɂ���
	move *= kSpeed;

	//���W�ƃx�N�g���̑����Z
	m_pos += move;

	//���S���W���w�肵�ē����蔻���Rect�𐶐�����.
	m_colRect.SetCenter(m_pos.x, m_pos.y + 15, kWidth - 35, kHeight - 5);

	//Player���ړ����Ă��鎞�ɃA�j���[�V�������J�n������
	if (isMove)
	{
		//�����A�j���[�V����
		m_walkAnimFrame++;
		if (m_walkAnimFrame >= kAnimFrameCycle)
		{
			m_walkAnimFrame = 0;
		}
	}
	else
	{
		m_walkAnimFrame = kAnimFrameNum;
	}

	//�V���b�g
	m_beamFrame++;
	if (m_beamFrame >= kBeamFrame)
	{
		ShotBeam* m_pShot = new ShotBeam;
		m_pShot->SetS1(m_pS1Scene);
		m_pShot->SetPlayer(this);
		m_pShot->Start(GetPos());
		//�ȍ~�X�V�⃁�����̉����SceneMain�ɔC����
		m_pS1Scene->AddShot(m_pShot);
	
		m_beamFrame = 0;		
	}
}

void Player::S2Update()
{

	//pad�̏\���L�[���g�p����Player���ړ�������
	int pad = GetJoypadInputState(DX_INPUT_KEY_PAD1);


	/* (pad & PAD_INPUT_UP) == 0 �̌���*/
	//0000 0000 0000 0000 0000 0000 0000 0000�@��{
	//0000 0000 0000 0000 0000 0000 0000 1000�@��L�[�������ꂽ�Ƃ�

	//�ړ����Ă��邩�ǂ���
	bool isMove = false;	

	//�ړ��ʂ����悤�ɂ���
	Vec2 move{ 0.0f,0.0f };
	if (((pad & PAD_INPUT_LEFT) | (pad & PAD_INPUT_4)) != 0)
	{
		//m_pos.x -= kSpeed;
		move.x -= kSpeed;
		m_dir = kDirLeft;
		isMove = true;
	}
	if (((pad & PAD_INPUT_RIGHT) | (pad & PAD_INPUT_6)) != 0)
	{
		//m_pos.x += kSpeed;
		move.x += kSpeed;
		m_dir = kDirRight;
		isMove = true;
	}

	if (m_pos.x < kWidth / 2 - 20)
	{
		m_pos.x = kWidth / 2 - 20;
	}
	if (m_pos.x > Game::kScreenWidth - kWidth / 2 + 20)
	{
		m_pos.x = Game::kScreenWidth - kWidth / 2 + 20;
	}

	//�΂߈ړ��̏ꍇ�����������ňړ�����悤�ɂ���

	//�x�N�g���̐��K��
	move.normalize();

	//�x�N�g���̒�����kspeed�ɂ���
	move *= kSpeed;

	//���W�ƃx�N�g���̑����Z
	m_pos += move;

	//���S���W���w�肵�ē����蔻���Rect�𐶐�����.
	m_colRect.SetCenter(m_pos.x, m_pos.y + 15, kWidth - 35, kHeight - 5);

	if (isMove)
	{
		//�����A�j���[�V����
		m_walkAnimFrame++;
		if (m_walkAnimFrame >= kAnimFrameCycle)
		{
			m_walkAnimFrame = 0;
		}
	}
	else
	{
		m_walkAnimFrame = kAnimFrameNum;
	}

	//�V���b�g
	m_beamFrame++;
	if (m_beamFrame >= kBeamFrame)
	{
		ShotBeam* m_pShot = new ShotBeam;
		m_pShot->SetS2(m_pS2Scene);
		m_pShot->SetPlayer(this);
		m_pShot->Start(GetPos());
		//�ȍ~�X�V�⃁�����̉����SceneMain�ɔC����
		m_pS2Scene->AddShot(m_pShot);

		m_beamFrame = 0;
	}
}

void Player::Draw()
{
	int animFrame = m_walkAnimFrame / kAnimFrameNum;

	int srcX = kWidth * kUseFrame[animFrame];
	int srcY = kHeight * m_dir;

	//DrawRectGraph(static_cast<int>(m_pos.x), static_cast<int>(m_pos.y),
		//srcX, srcY, kWidth, kHeight, m_handle, true);

	//DX���C�u�����ɂ̓��t�@�����X�y�[�W�ɏ�����ĂȂ��֐����������݂���
	//DxLib.h���m�F���Ă�����ۂ��֐���T�����茟�������肵�Ă݂悤
	DrawRectRotaGraph(static_cast<int>(m_pos.x), static_cast<int>(m_pos.y + 10),
		srcX, srcY, kWidth, kHeight,
		1.0, 0.0,
		m_handle, true, false);

#ifdef _DEBUG
	//�����蔻��̕\��
	m_colRect.Draw(GetColor(0, 0, 255), false);
#endif
}
