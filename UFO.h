#pragma once
#include "Vec2.h"
#include "Rect.h"

class TutorialScene;
class Stage1Scene;
class Stage2Scene;
class UFO
{
public:
	UFO(TutorialScene* pTuScene);
	UFO(Stage1Scene* pS1Scene);
	UFO(Stage2Scene* pS2Scene);
	~UFO();

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
	TutorialScene* m_pTuScene;
	Stage1Scene* m_pS1Scene;
	Stage2Scene* m_pS2Scene;

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
	float Gravity = 1.0f;
	float MaxGravity = 10.0f;
	float m_angle;
	float m_tq;
	
	bool KnockBack;
	bool isJump;
	bool m_MoveFlag;
	bool AnimFlag;

	int m_animFrame;
	float AnimPosX;
	int m_ufoS2Max;
	int m_soundHandle;

};

