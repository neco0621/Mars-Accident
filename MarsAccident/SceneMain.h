#pragma once
#include <vector>
#include "Rect.h"
#include "Vec2.h"

struct CIRCLE
{
	float x;
	float y;
	float r;
};

class Player;
class UFO;
class Bg;
class EnemyBase;
class ShotBeam;
class Bg;

class SceneMain
{
public:
	SceneMain();
	virtual ~SceneMain();

	void Init();
	void End();

	void Update();
	void Draw();

	//����̍��W�����ԋ߂��ɂ���G�̍��W��Ԃ��֐�
	Vec2 GetNearEnemyPos(Vec2 pos);
	//�V���b�g��ǉ�����
	//�o�^�ł��Ȃ������ꍇ��false��Ԃ�
	//�o�^�ł��Ȃ������ꍇ�͓�����pShot�������
	bool AddShot(ShotBeam* pBeam);

	Vec2 m_toNear;

private:
	//�G�L�����N�^�[�̐���
	void CreateEnemyLeft();
	void CreateEnemyRight();

private:
	//�O���t�B�b�N�̃n���h��
	int m_gameScreenHandle; //�Q�[�����

	//�O���t�B�b�N�̃n���h��
	int m_playerHandle;
	int m_enemyHandle;
	int m_bgHandle;

	

	//�v���C���[
	Player* m_pPlayer;

	UFO* m_pUfo;

	Bg* m_pBg;

	std::vector<ShotBeam*> m_pBeam;

	//�G
	std::vector<EnemyBase*> m_pEnemy;	//�z��̃T�C�Y�͎��s���Ɍ��߂�(����̓R���X�g���N�^)
	//EnemyBase* m_pEnemy[16];   �����܂ł̏�����


	Rect m_pRect;

	//��ʃ��C�v����
	int m_wipeFrame;

	//�G�̓o��Ԋu
	int m_enemyInterval;

	//�_���[�W���󂯂��Ƃ��̉�ʗh�ꉉ�o
	int m_shakeFrame;
};