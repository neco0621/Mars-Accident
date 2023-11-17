#pragma once
#include "Scene.h"
#include "../Vec2.h"
#include <vector>

class Player;
class EnemyBase;
class ShotBase;

class GamePlayingScene : public Scene
{
private:
	float fps = 0.0f;
	int m_playerHandle = 0;
	int m_enemyHandle = 0;
	int frame_ = 0;

	//��ԑJ�ڗp�����o�֐��|�C���^�̐錾
	using UpdateFunc_t = void (GamePlayingScene::*)(Input&);
	using DrawFunc_t = void (GamePlayingScene::*)();

	UpdateFunc_t updateFunc_ = nullptr;
	DrawFunc_t drawFunc_ = nullptr;

	//�v���C���[
	Player* m_pPlayer;

	//UFO
	UFO* m_pUfo;

	//�X�V�֐�
	void FadeInUpdate(Input& input);
	void NormalUpdate(Input& input);
	void FadeOutUpdate(Input& input);

	//�`��֐�
	void FadeDraw();
	void NormalDraw();

public:
	GamePlayingScene(SceneManager& mgr);
	~GamePlayingScene();
	void Init();
	void Update(Input& input);
	void Draw();

	//�V���b�g��ǉ�����
	//�o�^�ł��Ȃ������ꍇ��false��Ԃ�
	//�o�^�ł��Ȃ������ꍇ�͓�����pShot�������
	bool AddShot(ShotBase* pShot);

private:
	//�G�L�����N�^�[�̐���
	void CreateEnemyLeft();
	void CreateEnemyRight();

	//�G
	std::vector<EnemyBase*> m_pEnemy;	//�z��̃T�C�Y�͎��s���Ɍ��߂�(����̓R���X�g���N�^)
	//EnemyBase* m_pEnemy[16];   <-���܂ł̏�����

	std::vector<ShotBase*> m_pShot;

	//�G�̓o��Ԋu
	int m_enemyInterval;
};

