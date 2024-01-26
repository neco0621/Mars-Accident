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
	void ChangeGameOverScene();

	//����̍��W�����ԋ߂��ɂ���G�̍��W��Ԃ��֐�
	Vec2 GetNearEnemyPos(Vec2 pos);
	//�V���b�g��ǉ�����
	//�o�^�ł��Ȃ������ꍇ��false��Ԃ�
	//�o�^�ł��Ȃ������ꍇ�͓�����pShot�������
	bool AddShot(ShotBeam* pBeam);

	Vec2 m_toNear;

private:
	int handle_ = 0;
	int frame_ = 0;

	//��ԑJ�ڗp�����o�֐��|�C���^�̐錾
	using UpdateFunc_t = void (Stage2Scene::*)(Input&);
	using DrawFunc_t = void (Stage2Scene::*)();
	UpdateFunc_t updateFunc_ = nullptr;
	DrawFunc_t drawFunc_ = nullptr;

private:
	//�G�L�����N�^�[�̐���
	void CreateEnemyLeft();
	void CreateEnemyRight();

private:
	//�O���t�B�b�N�̃n���h��
	int m_gameScreenHandle; //�Q�[�����

	//�O���t�B�b�N�̃n���h��
	int m_playerHandle;
	int m_leftEnemyHandle;
	int m_rightEnemyHandle;
	int m_life1Handle;
	int m_life2Handle;
	int m_life3Handle;
	int m_bgHandle;
	int m_shotHandle;
	int m_rocketHandle;
	int m_ufoHandle;
	int m_AnimHandle;
	int m_downEnemyCount;
	int m_lifeCount;

	bool m_damageFlag;
	bool m_gameOverFlag;
	bool IsGround;




	//�v���C���[
	Player* m_pPlayer;

	UFO* m_pUfo;
	S2UFO* m_pS2ufo;

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
	int m_shakeFrame;
};