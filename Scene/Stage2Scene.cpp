#include "Stage2Scene.h"
#include "SceneManager.h"
#include "GameOverScene.h"
#include "GameClearScene.h"
#include "TitleScene.h"
#include "DxLib.h"
#include "../Player.h"
#include "../UFO.h"
#include "../Pad.h"
#include "../Rect.h"
#include "../Rocket.h"
#include "../Game.h"
#include "../Bg.h"
#include "../Input.h"

//�o�ꂷ��G
//#include "EnemyBase.h"
#include "../Enemy/EnemyLeft.h"
#include "../Enemy/EnemyRight.h"

//�o�ꂷ��V���b�g
#include "../ShotBeam.h"

#include <cassert>

namespace
{
	//��x�ɓo��ł���ő�̐�.
	constexpr int kEnemyMax = 8;
	//���t���[�����ɓG���o�ꂷ�邩.
	constexpr int kEnemyInterval = 90;

	//��ʓ��Ɉ�x�ɏo�Ă���e�̍ő吔.
	constexpr int kShotMax = 256;

	//��ʂ����C�v����̂ɂ�����t���[����.
	constexpr int kWipeFrame = 30;
}

Stage2Scene::Stage2Scene(SceneManager& manager) : Scene(manager),
m_enemyInterval(0),
m_shakeFrame(0),
m_wipeFrame(0),
m_toNear(Game::kScreenWidth, Game::kScreenHeight),
m_downEnemyCount(0),
m_damageFlag(false),
m_lifeCount(0),
m_gameOverFlag(false),
IsGround(false)
{
	//�Q�[����ʕ`���̐���.
	//��ʃT�C�Y�Ɠ����傫���̃O���t�B�b�N�f�[�^���쐬����.
	m_gameScreenHandle = MakeScreen(Game::kScreenWidth, Game::kScreenHeight, true);

	//�O���t�B�b�N�̃��[�h.
	m_playerHandle = LoadGraph("data/player.png");
	assert(m_playerHandle != -1);
	m_leftEnemyHandle = LoadGraph("data/Leftenemy.png");
	assert(m_leftEnemyHandle != -1);
	m_rightEnemyHandle = LoadGraph("data/Rightenemy.png");
	assert(m_rightEnemyHandle != -1);
	m_bgHandle = LoadGraph("data/Bg.png");
	assert(m_bgHandle != -1);
	m_shotHandle = LoadGraph("data/Shot.png");
	assert(m_shotHandle != -1);
	m_ufoHandle = LoadGraph("data/UFO.png");
	assert(m_ufoHandle != -1);
	m_rocketHandle = LoadGraph("data/Rocket.png");
	assert(m_rocketHandle != -1);
	m_life1Handle = LoadGraph("data/Life.png");
	assert(m_life1Handle != -1);
	m_life2Handle = LoadGraph("data/Life.png");
	assert(m_life2Handle != -1);
	m_life3Handle = LoadGraph("data/Life.png");
	assert(m_life3Handle != -1);
	m_AnimHandle = LoadGraph("data/explosion.png");
	assert(m_AnimHandle != -1);



	//�v���C���[�̃������m��.
	m_pPlayer = new Player{ this };
	m_pPlayer->SetHandle(m_playerHandle);	//Player�ɃO���t�B�b�N�n���h����n��

	m_pUfo = new UFO{ this };
	m_pUfo->SetHandle(m_ufoHandle);
	m_pUfo->SetAnimHandle(m_AnimHandle);

	m_pBg = new Bg{};
	m_pBg->SetHandle(m_bgHandle);

	m_pRocket = new Rocket{ this };
	m_pRocket->SetHandle(m_rocketHandle);
	//�G�̏���.
	//m_pEnemy(vector)�������Ȃ���΃T�C�Y��0
	//resize�֐���kEnemyMax�����f�[�^��ۑ��ł���悤�ɂ���
	m_pEnemy.resize(kEnemyMax);

	//�����̓R���X�g���N�^�Ń��������m�ۂ���
	//�f�X�g���N�^�ŉ�����Ă�
	//�����_����EnemyLeft,EnemyRight,EnemyToPlayer���m�ۂ�����
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
	m_pBeam.resize(kShotMax);
	for (int i = 0; i < m_pBeam.size(); i++)
	{
		m_pBeam[i] = nullptr;	//���g�p
	}

	//m_pShot = new ShotBeam;
	////SceneMain�̊֐����g�������̂Ń|�C���^��n���Ă���
	////this�Ŏ��g�̃|�C���^���擾�\
	//m_pShot->SetMain(this);
}

Stage2Scene::~Stage2Scene()
{
	//MakeScreen�Ő��������O���t�B�b�N���폜����
	DeleteGraph(m_gameScreenHandle);
	//����������O���t�B�b�N���폜
	DeleteGraph(m_bgHandle);
	DeleteGraph(m_playerHandle);
	DeleteGraph(m_leftEnemyHandle);
	DeleteGraph(m_rightEnemyHandle);
	DeleteGraph(m_AnimHandle);

	//�v���C���[�̃��������.
	delete m_pPlayer;
	m_pPlayer = nullptr;
	//UFO�̃������J��.
	delete m_pUfo;
	m_pUfo = nullptr;

	delete m_pBg;
	m_pBg = nullptr;

	delete m_pRocket;
	m_pRocket = nullptr;


	//���������m�ۂ���Ă���G��T���ĉ�����Ă���
	for (int i = 0; i < m_pEnemy.size(); i++)
	{
		//nullptr�ȊO�̂��̂������Ă���Ƃ������Ƃ͂����ɂ̓|�C���^�������Ă���
		if (m_pEnemy[i] != nullptr)
		{
			//�G�̃��������.
			delete m_pEnemy[i];
			m_pEnemy[i] = nullptr;
		}
	}
	for (int i = 0; i < m_pBeam.size(); i++)
	{
		if (m_pBeam[i])
		{
			//nullptr�ł͂Ȃ��ꍇ
			//�r�[���̃��������
			delete m_pBeam[i];
			m_pBeam[i] = nullptr;
		}
	}
}

void Stage2Scene::Init()
{
	assert(m_pPlayer);	//m_pPlayer == nullptr �̏ꍇ�~�܂�

	m_pPlayer->Init();
	m_pUfo->Init();
	m_pRocket->Init();
}

void Stage2Scene::End()
{

}

void Stage2Scene::Update(Input& input)
{
	Rect ufoRect = m_pUfo->GetColRect();
	Rect playerRect = m_pPlayer->GetColRect();
	m_pPlayer->S2Update();
	m_pUfo->Update();
	m_pRocket->Update();

	if (ufoRect.DistanceCollision(playerRect))
	{
		m_gameOverFlag = true;
	}
	for (int i = 0; i < m_pBeam.size(); i++)
	{
		//nullptr�Ȃ珈���͍s��Ȃ�
		if (m_pBeam[i])
		{
			m_pBeam[i]->Update();
			//��ʊO�ɏo���烁�������
			if (!m_pBeam[i]->isExist())
			{
				//�r�[���̃��������.
				delete m_pBeam[i];
				m_pBeam[i] = nullptr;
			}
			else
			{
				Rect shotRect = m_pBeam[i]->GetColRect();
				if (shotRect.CirCleCollision(ufoRect))
				{
					m_pUfo->JumpPower = 10;
					//�^�[�Q�b�g�ʒu.
					//�e�̔��ˈʒu�����ԋ߂��ɂ���G�̍��W���擾����
					//SceneMain�Ɏ��������֐��𗘗p����
					const Vec2 target = GetNearEnemyPos(m_pBeam[i]->m_pos);
					//���ˈʒu����^�[�Q�b�g�Ɍ������x�N�g��
					Vec2 toTarget = target - m_pBeam[i]->m_pos;
					//���K���@totarget���M�𐳋K��(������1��)
					toTarget.normalize();
					//�e�̑��x��kSpeed��
					m_pBeam[i]->m_vec = toTarget * m_pBeam[i]->m_pSpeed;
					m_pBeam[i]->MoveFlag = true;
				}

			}
		}
	}
	for (int i = 0; i < m_pEnemy.size(); i++)
	{
		if (m_pEnemy[i])	//nullptr�ł͂Ȃ��`�F�b�N
		{
			Rect enemyRect = m_pEnemy[i]->GetColRect();
			for (int a = 0; a < m_pBeam.size(); a++)
			{
				//nullptr�Ȃ珈���͍s��Ȃ�
				if (!m_pBeam[a])		continue;
				//��ʊO�ɏo���烁�������
				Rect shotRect = m_pBeam[a]->GetColRect();
				if (shotRect.CirCleCollision(enemyRect))
				{
					delete m_pBeam[a];
					m_pBeam[a] = nullptr;

					//���������������
					delete m_pEnemy[i];
					m_pEnemy[i] = nullptr;	//�g���Ă��Ȃ��Ƃ킩��悤��
					m_downEnemyCount++;
				}
				Rect ufoRect = m_pUfo->GetColRect();
				if (ufoRect.CirCleCollision(enemyRect))
				{
					//���������������
					delete m_pEnemy[i];
					m_pEnemy[i] = nullptr;	//�g���Ă��Ȃ��Ƃ킩��悤��
				}
				Rect rocketRect = m_pRocket->GetColRect();
				if (enemyRect.DistanceCollision(rocketRect))
				{
					////���������������
					delete m_pEnemy[i];
					m_pEnemy[i] = nullptr;
					m_damageFlag = true;
				}
			}
		}
	}

	for (int i = 0; i < m_pEnemy.size(); i++)
	{
		if (m_pEnemy[i])	//nullptr�ł͂Ȃ��`�F�b�N
		{
			m_pEnemy[i]->Update();
			Rect enemyRect = m_pEnemy[i]->GetColRect();
			//�g�p�ς݂̓G�L�����N�^���폜����K�v������
			if (!m_pEnemy[i]->isExist())
			{
				//���������������
				delete m_pEnemy[i];
				m_pEnemy[i] = nullptr;	//�g���Ă��Ȃ��Ƃ킩��悤��
			}
		}
	}
	//���C�v����
	m_wipeFrame++;
	if (m_wipeFrame > kWipeFrame)	m_wipeFrame = kWipeFrame;



	//�G�L�����N�^�[��o�ꂳ����
	//kEnemyInterval�t���[���o�߂��邲�ƂɃ����_���ɓG��o�ꂳ����
	m_enemyInterval++;
	if (m_enemyInterval >= kEnemyInterval)
	{
		m_enemyInterval = 0;

		//�����_���ɓG��I��
		switch (GetRand(2))		//0 or 1 or 2
		{
		case 0:		//Left
			CreateEnemyLeft();

			break;
		case 1:		//Right
			CreateEnemyRight();

			break;
		}
	}

	//��ʗh��t���[���̃J�E���g�_�E��
	m_shakeFrame--;

	if (m_pUfo->m_pos.y >= m_pUfo->m_tq - m_pUfo->m_radius / 2)
	{
		IsGround = true;
	}

	if (m_downEnemyCount == 25)
	{
		manager_.ChangeScene(std::make_shared<GameClearScene>(manager_));
		return;
	}

	if (m_damageFlag == true)
	{
		m_lifeCount++;
		m_pRocket->LifeDecrease();
		m_damageFlag = false;
	}

	if (m_lifeCount == 1)
	{
		DeleteGraph(m_life3Handle);
	}
	else if (m_lifeCount == 2)
	{
		DeleteGraph(m_life2Handle);
	}
	else if (m_lifeCount == 3)
	{
		DeleteGraph(m_life1Handle);
	}

	if (m_pRocket->m_life <= 0)
	{
		m_gameOverFlag = true;
	}

	if (m_gameOverFlag == true)
	{
		manager_.ChangeScene(std::make_shared<GameOverScene>(manager_));
		return;
	}
}

void Stage2Scene::Draw()
{
	//�o�b�N�o�b�t�@�ɒ��ڏ������ނ̂ł͂Ȃ��A
	//�����Ő��������O���t�B�b�N�f�[�^�ɑ΂��ď������݂��s��
	SetDrawScreen(m_gameScreenHandle);

	//�`���X�N���[�����N���A����
	ClearDrawScreen();

	m_pBg->Draw();
	DrawGraph(Game::kScreenWidth / 2 - 96, Game::kScreenHeight / 2, m_life1Handle, true);
	DrawGraph(Game::kScreenWidth / 2 - 32, Game::kScreenHeight / 2, m_life2Handle, true);
	DrawGraph(Game::kScreenWidth / 2 + 32, Game::kScreenHeight / 2, m_life3Handle, true);
	DrawBox(0, Game::kScreenHeight * 0.75 + 32, Game::kScreenWidth, Game::kScreenHeight, 0x84331F, true);
	m_pRocket->Draw();
	m_pPlayer->Draw();
	m_pUfo->S2Draw();

	for (int i = 0; i < m_pBeam.size(); i++)
	{
		if (!m_pBeam[i])		continue;
		m_pBeam[i]->Draw();
	}
	if (IsGround)
	{
		SetDrawScreen(DX_SCREEN_BACK);

		int x = GetRand(kWipeFrame) - static_cast<int>(kWipeFrame * 2);
		int y = GetRand(kWipeFrame) - static_cast<int>(kWipeFrame * 2);
		DrawGraph(x, y, m_gameScreenHandle, true);
		int Count = 0;
		Count++;
		if (Count < 120)
		{
			IsGround = false;
		}
	}


	for (int i = 0; i < m_pEnemy.size(); i++)
	{
		if (m_pEnemy[i])	//nullptr�ł͂Ȃ��`�F�b�N
		{
			m_pEnemy[i]->Draw();
		}
	}

	//�e�̐���\������
	int shotNum = 0;
	for (int i = 0; i < m_pBeam.size(); i++)
	{
		if (m_pBeam[i]) shotNum++;
	}

	int enemyNum = 0;
	for (int i = 0; i < m_pEnemy.size(); i++)
	{
		if (m_pEnemy[i]) enemyNum++;
	}

#ifdef _DEBUG
	//�v���C���[�̈ʒu���f�o�b�O�\������
	Vec2 playerPos = m_pPlayer->GetPos();
	DrawFormatString(8, 24, GetColor(255, 255, 255),
		"�v���C���[�̍��W(%.2f, %.2f)", playerPos.x, playerPos.y);
	DrawFormatString(8, 40, GetColor(255, 255, 255), "ShotNum%d", shotNum);
	DrawFormatString(8, 72, GetColor(255, 255, 255), "EnemyNum%d", enemyNum);
	DrawFormatString(8, 88, GetColor(255, 255, 255), "�c�胉�C�t%d", m_pRocket->m_life);
	DrawFormatString(8, 104, GetColor(255, 255, 255), "�|�����G�̐�%d", m_downEnemyCount);
#endif
	//�o�b�N�o�b�t�@�ɏ������ސݒ�ɖ߂��Ă���
	SetDrawScreen(DX_SCREEN_BACK);

	//�Q�[����ʂ��o�b�N�o�b�t�@�ɕ`�悷��
	int screenX = 0;
	int screenY = 0;
	if (m_shakeFrame > 0)
	{
		//��ʗh��
		screenX = GetRand(8) - 4;
		screenY = GetRand(8) - 4;
	}

	//m_wipeFrame����`�悷��͈͂��v�Z����
	//m_wipeFrame�Q�[���J�n����0,
	//���t���[�����Z�����kWipeFrame(30)�܂ŕω�����
	//wipeRate��m_wipeFrame�̕ω��ɍ��킹��0.0->1.0�ɕω�����
	float wipeRate = static_cast<float>(m_wipeFrame) / static_cast<float>(kWipeFrame);
	int wipeHeight = Game::kScreenHeight * wipeRate;

	/*DrawRectGraph(screenX,screenY,
		0,0,Game::kScreenWidth, wipeHeight,
		m_gameScreenHandle, true, false);*/

		//offset�̒l��wipe�̐i�s�ɍ��킹��320->0�ɕω���������

		//0->320�ɕω�������̂͂킩��₷��  320*wipeRate

	int offset = 320 * (1.0f - wipeRate);

	//��ʂ̏ォ��1���C�����`����s���Ă���
	for (int y = 0; y < Game::kScreenHeight; y++)
	{
		int x = sinf(y * 0.05f) * offset;
		DrawRectGraph(x, y,
			0, y, Game::kScreenWidth, 1,
			m_gameScreenHandle, true, false);
	}
}

Vec2 Stage2Scene::GetNearEnemyPos(Vec2 pos)
{
	//�G�����Ȃ��ꍇ�͓K���ȍ��W��Ԃ�
	Vec2 result{ 0,0 };
	//�ŏ��̓G�`�F�b�N�ς݃t���O
	bool isFirst = false;


	//��ԋ߂��G�L�����N�^�[�̍��W��result�ɓ����
	for (int i = 0; i < m_pEnemy.size(); i++)
	{
		//�g���Ă��Ȃ��G�̓`�F�b�N���Ȃ�
		if (!m_pEnemy[i])	continue;

		//�����ɂ��Ă��鎞�_��m_pEnemy[i]��nullptr�łȂ����Ƃ͊m��

		//���łɏ����邱�Ƃ��m�肵�Ă���G�̓`�F�b�N���Ȃ�
		if (!m_pEnemy[i]->isExist()) continue;

		//pos ��m_pEnemy[i]�̋������`�F�b�N����

		if (isFirst)
		{
			//1�̖ڂ̓G
			//�����������痣��Ă��悤�Ƃ������_�ł͈�ԋ߂��G
			result = m_pEnemy[i]->GetPos();
			isFirst = false;
		}
		else
		{
			//2�̖ڈȍ~�̓G
			//result�̒��ɂ͈�ԋ߂��G�̍��W�������Ă���

			//���܂Ń`�F�b�N�������ň�ԋ߂��G�Ƃ̋���
			Vec2 toNear = result - pos;	//pos����b���ʂ̍��W�Ɍ������x�N�g��

			//�`�F�b�N����G�Ƃ̋���
			Vec2 toEnemy = m_pEnemy[i]->GetPos() - pos;	//pos����`�F�b�N���̓G�Ɍ������x�N�g��

			//�������y�����邽�ߋ�y���̔�r���s���ꍇ�͋�����2��Ŕ�r���s��
			if (toNear.sqLength() > toEnemy.sqLength())
			{
				//���`�F�b�N���Ă���G�ւ̋������b���ʂ����Z���ꍇ
				//���`�F�b�N���Ă���G���b���ʂ�
				result = m_pEnemy[i]->GetPos();
			}
			//�b���ʂ̕������`�F�b�N���Ă���G���߂��ꍇ�͉������Ȃ�
		}
	}
	//���ׂĂ̓G�̃`�F�b�N���s�����̂ł�������ʂŊm��
	return result;
}

bool Stage2Scene::AddShot(ShotBeam* pBeam)
{
	for (int i = 0; i < m_pBeam.size(); i++)
	{
		//�g�p���Ȃ玟�̃`�F�b�N��
		if (m_pBeam[i])	continue;

		//�����ɗ����Ƃ������Ƃ�m_pShot[i] == nullptr
		m_pBeam[i] = pBeam;
		//�o�^������I��
		return true;
	}

	//�����ɗ����A�Ƃ������Ƃ�m_pShot�Ƀ|�C���^��o�^�ł��Ȃ�����
	delete pBeam;
	return false;
}

void Stage2Scene::CreateEnemyLeft()
{
	//�g���Ă��Ȃ�����T���Ă����ɃA�h���X��ۑ�����
	for (int i = 0; i < m_pEnemy.size(); i++)
	{
		if (!m_pEnemy[i])	//nullptr�ł��邱�Ƃ��`�F�b�N����
		{
			m_pEnemy[i] = new EnemyLeft;
			m_pEnemy[i]->Init();
			m_pEnemy[i]->SetHandle(m_leftEnemyHandle);
			m_pEnemy[i]->Start();
			return;	//���������m�ۂ�����ȍ~�̓`�F�b�N���Ȃ�
		}
	}
}

void Stage2Scene::CreateEnemyRight()
{
	//�g���Ă��Ȃ�����T���Ă����ɃA�h���X��ۑ�����
	for (int i = 0; i < m_pEnemy.size(); i++)
	{
		if (!m_pEnemy[i])	//nullptr�ł��邱�Ƃ��`�F�b�N����
		{
			m_pEnemy[i] = new EnemyRight;
			m_pEnemy[i]->Init();
			m_pEnemy[i]->SetHandle(m_rightEnemyHandle);
			m_pEnemy[i]->Start();
			return;	//���������m�ۂ�����ȍ~�̓`�F�b�N���Ȃ�
		}
	}
}