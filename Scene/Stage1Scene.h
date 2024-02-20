#pragma once
#include <vector>
#include "../Rect.h"
#include "../Vec2.h"
#include "Scene.h"

//�v���g�^�C�v�錾
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

	//��ʗh��
	void ShakeScreen(int a, int b);
	//�A�j���[�V��������
	void CreateAnimation();

	//��ԋ߂��G�̈ʒu
	Vec2 m_toNear;
	//���݈ʒu
	Vec2 pos;
private:

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
	int m_gameScreenHandle;			//�Q�[�����

	//�O���t�B�b�N�̃n���h��
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
	int m_AnimHandle;				//�A�j���[�V����
	int m_shakeHandle;				//��ʗh��
	int m_hitHandle;				//�F���D�ƓG�̏Փˎ�
	int m_clearHandle;				//�Q�[���N���A�̕���
	int LeftHandle;					//A�L�[
	int LeftArrowHandle;			//���̖��
	int RightHandle;				//D�L�[
	int RightArrowHandle;			//�E�̖��
	int StartTitle;					//�X�^�[�g�̃^�C�g������
	int m_enemyEXP;					//�G�̔����A�j���[�V����			

	int m_downEnemyCount;			//�G�̌��j���J�E���g
	int m_lifeCount;				//�F���D�̎c��̗̓J�E���g
	int m_shakeSize;				//��ʗh��̃T�C�Y
	int m_shakeFrame;				//��ʗh��t���[��
	int m_animFrame;				//�A�j���[�V�����̃t���[��
	
	int m_bgm;						//BGM
	int m_destoryEnemy;				//�G���j���̉���
	int m_gameover;					//�Q�[���I�[�o�[����SE
	int m_clearSE;					//�Q�[���N���A����SE
	int CheckSE;					//���莞��SE
	int m_damageHandle;				//�F���D�ƓG�̏Փˎ��̉���

	bool m_damageFlag;				//�_���[�W���󂯂����ǂ����̃t���O
	bool IsGround;					//�n�ʂɂ��Ă��邩�ǂ����̃t���O
	bool m_isShake;					//��ʗh����s���Ă��邩�̃n���h��
	bool StartFlag;					//�Q�[���X�^�[�g�t���O
	bool m_clearFlag;				//�Q�[���N���A�t���O
	bool m_gameOverFlag;			//�Q�[���I�[�o�[���̃t���O

public:
	bool AnimFlag;					//�A�j���[�V�����J�n�t���O
	
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
	
	//�A�j���[�V����
	std::vector<Stage1Scene*> m_pAnimation;

	//�����蔻��
	Rect m_pRect;

	//��ʃ��C�v����
	int m_wipeFrame;

	//�G�̓o��Ԋu
	int m_enemyInterval;
};