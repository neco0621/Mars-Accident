#pragma once
#include "Vec2.h"
#include "Rect.h"

class Stage1Scene;
class Stage2Scene;
class ShotBeam;
class UFO
{
public:
	UFO(Stage1Scene* pS1Scene);
	UFO(Stage2Scene* pS2Scene);
	~UFO();

	void Init();
	void Update();
	void Draw();
	void S2Draw();
	void ShakeScreen();

	//�����o�[�ϐ��ɃA�N�Z�X����
	void SetHandle(int handle) { m_handle = handle; }
	void SetAnimHandle(int AnimHandle) { m_animHnadle = AnimHandle; }
	//UFO�̌��݈ʒu���擾����
	Vec2 GetPos() const { return m_pos; }
	//UFO�̓����蔻����擾����
	Rect GetColRect() const { return m_colRect; }

	//�����蔻��p�̋�`
	Rect m_colRect;

	//�\���ʒu
	Vec2 m_pos;
	//���a
	float m_radius;
private:
	Stage1Scene* m_pS1Scene;
	Stage2Scene* m_pS2Scene;
	ShotBeam* m_pBeam;

	int m_handle;	//�O���t�B�b�N�̃n���h��
	int m_animHnadle;
	//�ڐG�������̔���
	bool m_boundFlag;

	//Beam�̍��W
	Vec2 m_beamPos;
public:
	//�ړ���	1�t���[��������̈ړ��x�N�g��������
	Vec2 m_vec;
	float JumpPower;
	bool isJump;
	float Gravity = 1.0f;
	float MaxGravity = 10.0f;
	bool KnockBack;
	float m_angle;

	float m_tq;

	bool m_MoveFlag;
};
