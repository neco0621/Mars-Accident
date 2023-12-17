#include "SceneMain.h"
#include "DxLib.h"
#include "Player.h"
#include "UFO.h"
#include "Pad.h"
#include "Rect.h"
#include "Rocket.h"
#include "Game.h"
#include "Bg.h"

//�o�ꂷ��G
//#include "EnemyBase.h"
#include "EnemyLeft.h"
#include "EnemyRight.h"

//�o�ꂷ��V���b�g
#include "ShotBeam.h"

#include <cassert>

namespace
{
	//��x�ɓo��ł���ő�̐�.
	constexpr int kEnemyMax = 64;
	//���t���[�����ɓG���o�ꂷ�邩.
	constexpr int kEnemyInterval = 60;

	//��ʓ��Ɉ�x�ɏo�Ă���e�̍ő吔.
	constexpr int kShotMax = 256;

	//��ʂ����C�v����̂ɂ�����t���[����.
	constexpr int kWipeFrame = 30;
}

SceneMain::SceneMain() :
	m_enemyInterval(0),
	m_shakeFrame(0),
	m_wipeFrame(0),
	m_toNear(Game::kScreenWidth,Game::kScreenHeight)
{
	//�Q�[����ʕ`���̐���.
	//��ʃT�C�Y�Ɠ����傫���̃O���t�B�b�N�f�[�^���쐬����.
	m_gameScreenHandle = MakeScreen(Game::kScreenWidth, Game::kScreenHeight, true);

	//�O���t�B�b�N�̃��[�h.
	m_playerHandle = LoadGraph("data/player.png");
	assert(m_playerHandle != -1);
	m_enemyHandle = LoadGraph("data/enemy.png");
	assert(m_enemyHandle != -1);
	m_bgHandle = LoadGraph("data/Bg.png");
	assert(m_bgHandle != -1);
	m_rocketHandle = LoadGraph("data/Rocket.png");
	assert(m_bgHandle != -1);

	//�v���C���[�̃������m��.
	m_pPlayer = new Player{ this };
	m_pPlayer->SetHandle(m_playerHandle);	//Player�ɃO���t�B�b�N�n���h����n��

	m_pUfo = new UFO{ this };


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

SceneMain::~SceneMain()
{
	//MakeScreen�Ő��������O���t�B�b�N���폜����
	DeleteGraph(m_gameScreenHandle);
	//����������O���t�B�b�N���폜
	DeleteGraph(m_bgHandle);
	DeleteGraph(m_playerHandle);
	DeleteGraph(m_enemyHandle);
	DeleteGraph(m_rocketHandle);

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

void SceneMain::Init()
{
	assert(m_pPlayer);	//m_pPlayer == nullptr �̏ꍇ�~�܂�

	m_pPlayer->Init();
	m_pUfo->Init();
}

void SceneMain::End()
{

}

void SceneMain::Update()
{
	Rect ufoRect = m_pUfo->GetColRect();
	Rect playerRect = m_pPlayer->GetColRect();
	
	for (int i = 0; i < m_pBeam.size(); i++)
	{
		//nullptr�Ȃ珈���͍s��Ȃ�
		if (!m_pBeam[i])		continue;

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
				m_pUfo->m_pos.y -=  (m_pUfo->v * m_pUfo->dt) ;//���x������W
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
	m_pPlayer->Update();
	m_pUfo->Update();
	
	

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
	
}

void SceneMain::Draw()
{
	//�o�b�N�o�b�t�@�ɒ��ڏ������ނ̂ł͂Ȃ��A
	//�����Ő��������O���t�B�b�N�f�[�^�ɑ΂��ď������݂��s��
	SetDrawScreen(m_gameScreenHandle);

	//�`���X�N���[�����N���A����
	ClearDrawScreen();

	m_pBg->Draw();
	m_pPlayer->Draw();
	m_pUfo->Draw();
	m_pRocket->Draw();

	for (int i = 0; i < m_pBeam.size(); i++)
	{
		if (!m_pBeam[i])		continue;
		m_pBeam[i]->Draw();
	}

	for (int i = 0; i < m_pEnemy.size(); i++)
	{
		if (m_pEnemy[i])	//nullptr�ł͂Ȃ��`�F�b�N
		{
			m_pEnemy[i]->Draw();
		}
	}

	

	//�v���C���[�̈ʒu���f�o�b�O�\������
	Vec2 playerPos = m_pPlayer->GetPos();
	DrawFormatString(8, 24, GetColor(255, 255, 255),
		"�v���C���[�̍��W(%.2f, %.2f)", playerPos.x, playerPos.y);

	//�e�̐���\������
	int shotNum = 0;
	for (int i = 0; i < m_pBeam.size(); i++)
	{
		if (m_pBeam[i]) shotNum++;
	}
	DrawFormatString(8, 40, GetColor(255, 255, 255), "ShotNum%d", shotNum);

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

Vec2 SceneMain::GetNearEnemyPos(Vec2 pos) 
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
		//�`�F�b�N����G�Ƃ̋���
		Vec2 toEnemy = m_pEnemy[i]->GetPos();	//pos����`�F�b�N���̓G�Ɍ������x�N�g��
		//���܂Ń`�F�b�N�������ň�ԋ߂��G�Ƃ̋���
		if (toEnemy.sqLength() < m_toNear.sqLength())
		{
			m_toNear = toEnemy;	//pos����b���ʂ̍��W�Ɍ������x�N�g��
		}
	}
	//���ׂĂ̓G�̃`�F�b�N���s�����̂ł�������ʂŊm��
	return m_toNear;
}

bool SceneMain::AddShot(ShotBeam* pBeam)
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

void SceneMain::CreateEnemyLeft()
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

void SceneMain::CreateEnemyRight()
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