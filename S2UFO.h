#pragma once
#include "Vec2.h"
#include "Rect.h"

class Stage1Scene;
class Stage2Scene;
class Animation;
class Graphic;
class S2UFO
{
public:
	S2UFO(Stage2Scene* pS2Scene);
	~S2UFO();

	void Init();
	void Update();
	void Draw();

	//�����o�[�ϐ��ɃA�N�Z�X����
	void SetHandle(int handle) { m_handle = handle; }
	void SetAnimHandle(int AnimHandle) { m_animHnadle = AnimHandle; }
	void Start();
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
	Stage2Scene* m_pS2Scene;
	//Animation* m_pAnimation;
	Graphic* graphic;

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

	int m_animFrame;
	bool AnimFlag;
	int AnimPosX;

	int m_ufoS2Max;
	int m_soundHandle;
};

