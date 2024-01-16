#pragma once
#include "Vec2.h"
#include "Rect.h"

class Stage1Scene;
class ShotBeam;
class Rocket
{
public:
	Rocket(Stage1Scene* pS1Scene);
	~Rocket();

	void Init();
	void Update();
	void Draw();

	//�����o�[�ϐ��ɃA�N�Z�X����
	void SetHandle(int handle) { m_handle = handle; }

	void LifeDecrease();
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

	int m_life;
private:
	Stage1Scene* m_pS1Scene;
	ShotBeam* m_pBeam;

	int m_handle;	//�O���t�B�b�N�̃n���h��

	//Beam�̍��W
	Vec2 m_beamPos;

};

