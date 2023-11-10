#pragma once
#include "Vec2.h"
#include "Rect.h"

class GamePlayingScene;
class ShotBeam;
class UFO
{
public:
	UFO(GamePlayingScene* pGame);
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

private:
	GamePlayingScene* m_pGame;
	ShotBeam* m_pBeam;

	int m_handle;	//�O���t�B�b�N�̃n���h��



	//�ڐG�������̔���
	bool m_boundFlag;

	//�\���ʒu
	Vec2 m_pos;

	//Beam�̍��W
	Vec2 m_beamPos;

	//�����蔻��p�̋�`
	Rect m_colRect;
};

