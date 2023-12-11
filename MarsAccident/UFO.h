#pragma once
#include "Vec2.h"
#include "Rect.h"

class SceneMain;
class ShotBeam;
class UFO
{
public:
	UFO(SceneMain* pMain);
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
	ShotBeam* m_pBeam;

	int m_handle;	//�O���t�B�b�N�̃n���h��
	
	//�ڐG�������̔���
	bool m_boundFlag;	

	//Beam�̍��W
	Vec2 m_beamPos;
public:
	//�ړ���	1�t���[��������̈ړ��x�N�g��������
	Vec2 m_vec;

	double F, a;//�͂Ɖ����x
	double v = 0;//���x
	double m = 1.0;//����
	double k = 0.5;//�΂˒萔
	double c = 2.5;//�S���W��
	double dt = 0.1;//���ԕω�

	bool m_MoveFlag;
};

