#pragma once
#include "Vec2.h"
#include "Rect.h"

class SceneMain;
class StageBase;
class ShotBeam;
class UFO
{
public:
	UFO(SceneMain* pMain);
	UFO(StageBase* pSBase);
	~UFO();

	void Init();
	void Update();
	void Draw();

	//�����o�[�ϐ��ɃA�N�Z�X����
	void SetHandle(int handle) { m_handle = handle; }
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
	SceneMain* m_pMain;
	StageBase* m_pSBase;
	ShotBeam* m_pBeam;

	int m_handle;	//�O���t�B�b�N�̃n���h��
	
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

	float m_tq;

	bool m_MoveFlag;
};

