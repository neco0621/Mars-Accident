#pragma once
#include <vector>
#include "../Rect.h"
#include "../Vec2.h"
#include "Scene.h"



class Player;
class UFO;
class S2UFO;
class Rocket;
class Bg;
class EnemyBase;
class ShotBeam;
class Bg;

class Stage2Scene : public Scene
{
public:
	Stage2Scene(SceneManager& mgr);
	virtual ~Stage2Scene();

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

	//��ʗh��̊֐�
	void ShakeScreen(int a, int b);

	//�ł��߂��G�̍��W
	Vec2 m_toNear;
	//���ݍ��W
	Vec2 pos;
private:

	//��ԑJ�ڗp�����o�֐��|�C���^�̐錾
	using UpdateFunc_t = void (Stage2Scene::*)(Input&);
	using DrawFunc_t = void (Stage2Scene::*)();
	UpdateFunc_t updateFunc_ = nullptr;
	DrawFunc_t drawFunc_ = nullptr;

	//�G�L�����N�^�[�̐���
	void CreateEnemyLeft();
	void CreateEnemyRight();

	//�O���t�B�b�N�̃n���h��
	int m_gameScreenHandle;			//�Q�[�����
	int m_playerHandle;				//�v���C���[
	int m_leftEnemyHandle;			//�G
	int m_rightEnemyHandle;			//�G
	int m_life1Handle;				//�F���D�̗̑�
	int m_life2Handle;				//�F���D�̗̑�
	int m_life3Handle;				//�F���D�̗̑�
	int m_bgHandle;					//�w�i
	int m_shotHandle;				//�e
	int m_rocketHandle;				//���P�b�g
	int m_ufoHandle;				//UFO
	int m_shakeHandle;				//��ʗh��
	int m_startTitle;				//�X�^�[�g�{�^��

	//�A�j���[�V�����̃n���h��
	int m_AnimHandle;				//�����A�j���[�V����		
	int m_enemyEXP;					//�G�̔����A�j���[�V����

	//�����̃n���h��
	int m_bgm;						//BGM
	int m_hitHandle;				//UFO�ƒe�̏Փˎ���SE
	int m_damageHandle;				//�F���D�ƓG�̏Փˎ���SE
	int m_gameover;					//�Q�[���I�[�o�[����SE
	int m_destoryEnemy;				//�G���j����SE
	int m_clearSE;					//�X�e�[�W�N���A����SE
	int CheckSE;					//����{�^�����������Ƃ���SE

	//���̑�
	int m_downEnemyCount;			//�|�����G�̐�
	int m_lifeCount;				//�F���D�̗̑�
	int m_shakeSize;				//��ʂ̗h�ꕝ
	int m_shakeFrame;				//��ʂ��h��Ă���b��
	int m_animFrame;				//�A�j���[�V�����̍Đ�����
	int frame_ = 0;					//�t�F�C�h�̃t���[��
	
	//�t���O
	bool m_damageFlag;
	bool m_gameOverFlag;			//�Q�[���I�[�o�[�ɂȂ������ǂ����̃t���O
	bool IsGround;					//�n�ʂɐڂ��Ă��邩�̃t���O
	bool m_isShake;					//��ʗh������s����t���O
	bool StartFlag;					//�Q�[���̏����J�n�t���O
	bool AnimFlag;					//�A�j���[�V�������Đ�����t���O

	//�v���C���[
	Player* m_pPlayer;

	//UFO
	UFO* m_pUfo;

	//2�X�e�[�W�݂̂�UFO
	S2UFO* m_pS2ufo;

	//�w�i
	Bg* m_pBg;

	Rocket* m_pRocket;

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
	int m_S2shakeFrame;
};