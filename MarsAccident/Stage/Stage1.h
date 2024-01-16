#pragma once
#include "StageBase.h"
#include <vector>
#include "../Rect.h"
#include "../Vec2.h"

class UFO;
class Rocket;
class Bg;
class EnemyBase;
class ShotBeam;
class Bg;

class Stage1 : public StageBase
{
public:
	Stage1(StageManager& manager);
	virtual ~Stage1();

	virtual void Init() override;
	virtual void Update() override;
	virtual void Draw() override;
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

	//�X�V�����o�֐��|�C���^
	void (Stage1::* updateFunc_)(Input& input);
	//�`�惁���o�֐��|�C���^
	using DrawFunc_t = void (Stage1::*) ();
	DrawFunc_t drawFunc_;
	void FadeInUpdate(Input& input);	//�t�F�[�h�C�����
	void NormalUpdate(Input& input);	//�ʏ���
	void FadeOutUpdate(Input& input);	//�t�F�[�h�A�E�g���

	//�`��֐�
	void FadeDraw();	//�t�F�[�h���`��
	void NormalDraw();	//��t�F�[�h�`��

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
	int m_rocketHandle;

	

	UFO* m_pUfo;

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

