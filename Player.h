#pragma once
#include <vector>
#include "Vec2.h"
#include "Rect.h"

class TutorialScene;
class Stage1Scene;
class Stage2Scene;
class ShotBeam;
class Player
{
public:
	//�����Ă������
	enum Dir
	{
		kDirRight,	//�E	= 2
		kDirLeft,	//��	= 1
	};

public:
	Player(TutorialScene* pTuScene);
	Player(Stage1Scene* S1Scene);
	Player(Stage2Scene* S2Scene);
	~Player();

	void Init();
	void TuUpdate();
	void Update();
	void S2Update();
	void Draw();

	//�����o�[�ϐ��ɃA�N�Z�X����
	void SetHandle(int handle) { m_handle = handle; }
	//�v���C���[�̌��݈ʒu���擾����
	Vec2 GetPos() const { return m_pos; }
	//�v���C���[�̓����蔻����擾����
	Rect GetColRect() const {return m_colRect; }

	//�\���ʒu
	Vec2 m_pos;

private:
	TutorialScene* m_pTuScene;
	Stage1Scene* m_pS1Scene;
	Stage2Scene* m_pS2Scene;

	std::vector<ShotBeam> m_pBeam;

	int m_handle;	//�O���t�B�b�N�̃n���h��

	//�����蔻��p�̋�`
	Rect m_colRect;

	//�����Ă������
	Dir m_dir;

	//�����A�j���[�V����
	int m_walkAnimFrame;

	//���@�̏�̔��˃t���[���J�E���g
	int m_beamFrame;
};
