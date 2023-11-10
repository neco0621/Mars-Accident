#include "GamePlayingScene.h"
#include "PauseScene.h"
#include "GameOverScene.h"
#include "SceneManager.h"
#include "../Input.h"
#include "../Player.h"
#include "../UFO.h"

//�o�ꂷ��G
//#include "EnemyBase.h"
#include "../Enemy/EnemyLeft.h"
#include "../Enemy/EnemyRight.h"

//�o�ꂷ��V���b�g
#include "../Shot/ShotBeam.h"

#include <cassert>
#include <DxLib.h>

namespace
{
	//��x�ɓo��ł���ő�̐�
	constexpr int kEnemyMax = 10;

	//���t���[�����ɓG���o�ꂷ�邩
	constexpr int kEnemyInterval = 60;

	//��ʓ��Ɉ�x�ɏo�Ă���e�̍ő吔
	constexpr int kShotMax = 256;
}


void GamePlayingScene::FadeInUpdate(Input& input)
{
	frame_--;
	if (frame_ <= 0)
	{
		updateFunc_ = &GamePlayingScene::NormalUpdate;
		drawFunc_ = &GamePlayingScene::NormalDraw;
	}
}

void GamePlayingScene::NormalUpdate(Input& input)
{
	if (input.IsTriggered("OK"))
	{
		updateFunc_ = &GamePlayingScene::FadeOutUpdate;
		drawFunc_ = &GamePlayingScene::FadeDraw;
	}
	else if (input.IsTriggered("pause"))
	{
		manager_.PushScene(std::make_shared<PauseScene>(manager_));
	}
}

void GamePlayingScene::FadeOutUpdate(Input& input)
{
	frame_++;
	if (frame_ >= 60)
	{
		manager_.ChangeScene(std::make_shared<GameOverScene>(manager_));
	}
}

void GamePlayingScene::FadeDraw()
{
	int alpha = 255 * static_cast<float>(frame_) / 60.0f;
	SetDrawBlendMode(DX_BLENDMODE_MULA, alpha);
	DrawBox(0, 0, 640, 480, 0x000000, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

void GamePlayingScene::NormalDraw()
{
	m_pPlayer->Draw();
	for (int i = 0; i < m_pShot.size(); i++)
	{
		if (!m_pShot[i])		continue;
		m_pShot[i]->Draw();
	}

	for (int i = 0; i < m_pEnemy.size(); i++)
	{
		if (m_pEnemy[i])	//nullptr�ł͂Ȃ��`�F�b�N
		{
			m_pEnemy[i]->Draw();
		}
	}
	Vec2 playerPos = m_pPlayer->GetPos();
	DrawCircle(320, 120, 10, GetColor(255, 255, 0), true);
	DrawFormatString(8, 24, GetColor(255, 255, 255),
		L"�v���C���[�̍��W(%.2f, %.2f)", playerPos.x, playerPos.y);
	DrawFormatString(10, 10, 0xffffff, L"fps=%2.2f", fps);
}

GamePlayingScene::GamePlayingScene(SceneManager& mgr) : Scene(mgr)
{
	m_playerHandle = LoadGraph(L"./img/player.png");
	assert(m_playerHandle != -1);
	m_enemyHandle = LoadGraph(L"./img/enemy.png");
	assert(m_enemyHandle != -1);
	updateFunc_ = &GamePlayingScene::FadeInUpdate;
	drawFunc_ = &GamePlayingScene::FadeDraw;
	frame_ = 60;
	m_enemyInterval = 0;

	//�v���C���[�̃������m��
	m_pPlayer = new Player{ this };
	m_pPlayer->SetHandle(m_playerHandle);	//Player�ɃO���t�B�b�N�n���h����n��

	//�G�̏���
	//m_pEnemy(vector)�������Ȃ���΃T�C�Y��0
	//resize�֐���kEnemyMax�����f�[�^��ۑ��ł���悤�ɂ���
	m_pEnemy.resize(kEnemyMax);

	//�����̓R���X�g���N�^�Ń��������m�ۂ���
	//�f�X�g���N�^�ŉ�����Ă�
	//�����_����EnemyLeft,EnemyRight���m�ۂ�����
	//�ǂꂩ�킩��Ȃ��̂ł��炩���ߊm�ۂ��邱�Ƃ��ł��Ȃ�
	//�����I�Ƀ��������m�ۂ���@Update()���ɕK�v�ɉ�����

	//������Ԃł̓��������m�ۂ��Ă��Ȃ����Ƃ��킩��悤�ɂ��Ă���
	//���g�p��Ԃɂ���@nullptr�����Ă���
	//size()�Ō��ݎg�p�\�ȗv�f�����擾�\
	for (int i = 0; i < m_pEnemy.size(); i++)
	{
		m_pEnemy[i] = nullptr;

		//m_pEnemy�̂Ȃ��ɂ�Left,Right,ToPlayer�̂ǂꂩ������
		//�����_�ł͂ǂꂪ����̂�����ł��Ȃ�
	}

	//�V���b�g�̏���
	m_pShot.resize(kShotMax);
	for (int i = 0; i < m_pShot.size(); i++)
	{
		m_pShot[i] = nullptr;	//���g�p
	}
}

GamePlayingScene::~GamePlayingScene()
{
	//����������O���t�B�b�N���폜
	DeleteGraph(m_playerHandle);
	DeleteGraph(m_enemyHandle);

	//�v���C���[�̃��������
	delete m_pPlayer;
	m_pPlayer = nullptr;
	//���������m�ۂ���Ă���G��T���ĉ�����Ă���
	for (int i = 0; i < m_pEnemy.size(); i++)
	{
		//nullptr�ȊO�̂��̂������Ă���Ƃ������Ƃ͂����ɂ̓|�C���^�������Ă���
		if (m_pEnemy[i] != nullptr)
		{
			delete m_pEnemy[i];
			m_pEnemy[i] = nullptr;
		}
	}
	for (int i = 0; i < m_pShot.size(); i++)
	{
		if (m_pShot[i])
		{
			//nullptr�ł͂Ȃ��ꍇ
			delete m_pShot[i];
			m_pShot[i] = nullptr;
		}
	}
}

void GamePlayingScene::Init()
{
	assert(m_pPlayer);	//m_pPlayer == nullptr �̏ꍇ�~�܂�

	m_pPlayer->Init();
}

void GamePlayingScene::Update(Input& input)
{
	m_pPlayer->Update();

	for (int i = 0; i < m_pShot.size(); i++)
	{
		//nullptr�Ȃ珈���͍s��Ȃ�
		if (!m_pShot[i])		continue;

		m_pShot[i]->Update();
		//��ʊO�ɏo���烁�������
		if (!m_pShot[i]->isExist())
		{
			delete m_pShot[i];
			m_pShot[i] = nullptr;
		}
	}

	Rect playerRect = m_pPlayer->GetColRect();

	for (int i = 0; i < m_pEnemy.size(); i++)
	{
		if (m_pEnemy[i])	//nullptr�ł͂Ȃ��`�F�b�N
		{
			m_pEnemy[i]->Update();

			//�g�p�ς݂̓G�L�����N�^���폜����K�v������
			if (!m_pEnemy[i]->isExist())
			{
				//���������������
				delete m_pEnemy[i];
				m_pEnemy[i] = nullptr;	//�g���Ă��Ȃ��Ƃ킩��悤��
			}
		}

	}
	//�G�L�����N�^�[��o�ꂳ����
	//kEnemyInterval�t���[���o�߂��邲�ƂɃ����_���ɓG��o�ꂳ����
	m_enemyInterval++;
	if (m_enemyInterval >= kEnemyInterval)
	{
		m_enemyInterval = 0;

		//�����_���ɓG��I��
		switch (GetRand(1))		//0 or 1 
		{
		case 0:		//Left
			CreateEnemyLeft();

			break;
		case 1:		//Right
			CreateEnemyRight();

			break;
		default:	assert(false);		//break�Ȃ�
		}
	}

	fps = GetFPS();
	(this->*updateFunc_)(input);
}

void GamePlayingScene::Draw()
{
	(this->*drawFunc_)();
}

bool GamePlayingScene::AddShot(ShotBase* pShot)
{
	for (int i = 0; i < m_pShot.size(); i++)
	{
		//�g�p���Ȃ玟�̃`�F�b�N��
		if (m_pShot[i])	continue;

		//�����ɗ����Ƃ������Ƃ�m_pShot[i] == nullptr
		m_pShot[i] = pShot;
		//�o�^������I��
		return true;
	}

	//�����ɗ����A�Ƃ������Ƃ�m_pShot�Ƀ|�C���^��o�^�ł��Ȃ�����
	delete pShot;
	return false;
}

void GamePlayingScene::CreateEnemyLeft()
{
	//�g���Ă��Ȃ�����T���Ă����ɃA�h���X��ۑ�����
	for (int i = 0; i < m_pEnemy.size(); i++)
	{
		if (!m_pEnemy[i])	//nullptr�ł��邱�Ƃ��`�F�b�N����
		{
			m_pEnemy[i] = new EnemyLeft;
			m_pEnemy[i]->Init();
			m_pEnemy[i]->SetHandle(m_enemyHandle);
			m_pEnemy[i]->Start();
			return;	//���������m�ۂ�����ȍ~�̓`�F�b�N���Ȃ�
		}
	}
}

void GamePlayingScene::CreateEnemyRight()
{
	//�g���Ă��Ȃ�����T���Ă����ɃA�h���X��ۑ�����
	for (int i = 0; i < m_pEnemy.size(); i++)
	{
		if (!m_pEnemy[i])	//nullptr�ł��邱�Ƃ��`�F�b�N����
		{
			m_pEnemy[i] = new EnemyRight;
			m_pEnemy[i]->Init();
			m_pEnemy[i]->SetHandle(m_enemyHandle);
			m_pEnemy[i]->Start();
			return;	//���������m�ۂ�����ȍ~�̓`�F�b�N���Ȃ�
		}
	}
}
