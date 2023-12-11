#pragma once
#include <vector>
#include "Vec2.h"
#include "Rect.h"

class SceneMain;
class ShotBeam;
class Player
{
public:
	//�����Ă������
	enum Dir
	{
		kDirDown,	//��	= 0
		kDirLeft,	//��	= 1
		kDirRight,	//�E	= 2
		kDirUp,		//��	= 3
	};

public:
	Player(SceneMain* pMain);
	~Player();

	void Init();
	void Update();
	void Draw();

	//�����o�[�ϐ��ɃA�N�Z�X����
	void SetHandle(int handle) { m_handle = handle; }
	//�v���C���[�̌��݈ʒu���擾����
	Vec2 GetPos() const { return m_pos; }
	//�v���C���[�̓����蔻����擾����
	Rect GetColRect() const;

	//�v���C���[���_���[�W���󂯂�
	void OnDamage();

private:
	SceneMain* m_pMain;

	std::vector<ShotBeam> m_pBeam;

	int m_handle;	//�O���t�B�b�N�̃n���h��

	//�\���ʒu
	Vec2 m_pos;

	//�����蔻��p�̋�`
	Rect m_colRect;

	//�����Ă������
	Dir m_dir;

	//�����A�j���[�V����
	int m_walkAnimFrame;

	//���@�̏�̔��˃t���[���J�E���g
	int m_beamFrame;

	//�_���[�W���󂯂Ă���̃t���[����
	//�����������Ƀt���[������ݒ肵��
	//���t���[�����炵�Ă���
	int m_damageFrame;
};