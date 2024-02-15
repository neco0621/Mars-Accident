#pragma once
#include <vector>
#include "../Rect.h"
#include "../Vec2.h"
#include "Scene.h"

class Player;
class UFO;
class Rocket;
class Bg;
class EnemyBase;
class ShotBeam;
class Bg;

class Stage1Scene : public Scene
{
public:
	Stage1Scene(SceneManager& mgr);
	virtual ~Stage1Scene();

	void Init();
	void End();

	void Update(Input& input);

	void Draw();

	//����̍��W�����ԋ߂��ɂ���G�̍��W��Ԃ��֐�
	Vec2 GetNearEnemyPos(Vec2 pos);
	//�V���b�g��ǉ�����
	//�o�^�ł��Ȃ������ꍇ��false��Ԃ�
	//�o�^�ł��Ȃ������ꍇ�͓�����pShot�������
	bool AddShot(ShotBeam* pBeam);

	void ShakeScreen(int a, int b);
	void CreateAnimation();

	Vec2 m_toNear;
	Vec2 pos;
private:
	int handle_ = 0;
	int frame_ = 0;

	//��ԑJ�ڗp�����o�֐��|�C���^�̐錾
	using UpdateFunc_t = void (Stage1Scene::*)(Input&);
	using DrawFunc_t = void (Stage1Scene::*)();
	UpdateFunc_t updateFunc_ = nullptr;
	DrawFunc_t drawFunc_ = nullptr;

private:
	//�G�L�����N�^�[�̐���
	void CreateEnemyLeft();
	void CreateEnemyRight();

private:
	//�O���t�B�b�N�̃n���h��
	int m_gameScreenHandle; //�Q�[�����

	//Player�̃n���h��
	int m_playerHandle;
	//�G�̃O���t�B�b�N
	int m_leftEnemyHandle;
	int m_rightEnemyHandle;
	//���P�b�g�̗̑͂̃n���h��
	int m_life1Handle;
	int m_life2Handle;
	int m_life3Handle;
	//�w�i�̃n���h��
	int m_bgHandle;
	//Shot�̃n���h��
	int m_shotHandle;
	//���P�b�g�̃n���h��
	int m_rocketHandle;
	//UFO�̃n���h��
	int m_ufoHandle;
	//�A�j���[�V�����̃n���h��
	int m_AnimHandle;
	//��ʗh��̃n���h��
	int m_shakeHandle;
	//UFO�̃_���[�W���̃n���h��
	int m_hitHandle;
	//���P�b�g�̃_���[�W���̃n���h��
	int m_damageHandle;
	//�Q�[���N���A���̉��̃n���h��
	int m_clearHandle;
	//�G�l�~�[���j���̃A�j���[�V�����n���h��
	int m_enemyEXP;
	//�|�����G�̐�
	int m_downEnemyCount;
	//���݂̃��P�b�g�̗̑�
	int m_lifeCount;
	//�G�l�~�[���j���̃T�E���h�n���h��
	int m_destoryEnemy;
	//��ʗh��̃T�C�Y
	int m_shakeSize;
	//��ʗh��̃t���[��
	int m_shakeFrame;
	//Start�p�̃^�C�g���{�^��
	int StartTitle;
	//�A�j���[�V�����̃t���[��
	int m_animFrame;
	//Bgm�n���h��
	int m_bgm;
	//
	int m_gameover;
	//
	int m_clearSE;
	//
	int CheckSE;

	//
	bool m_damageFlag;
	//
	bool m_gameOverFlag;
	//
	bool IsGround;
	//
	bool m_isShake;
	//
	bool StartFlag;
	//
	bool m_clearFlag;

public:
	//
	bool AnimFlag;

	
	//�v���C���[
	Player* m_pPlayer;

	//UFO
	UFO* m_pUfo;

	//�w�i
	Bg* m_pBg;

	//���P�b�g
	Rocket* m_pRocket;

	//Shot
	std::vector<ShotBeam*> m_pBeam;

	//�G
	std::vector<EnemyBase*> m_pEnemy;	//�z��̃T�C�Y�͎��s���Ɍ��߂�(����̓R���X�g���N�^)
	//EnemyBase* m_pEnemy[16];   �����܂ł̏�����

	//�A�j���[�V����
	std::vector<Stage1Scene*> m_pAnimation;

	//Rect
	Rect m_pRect;

	//��ʃ��C�v����
	int m_wipeFrame;

	//�G�̓o��Ԋu
	int m_enemyInterval;
};