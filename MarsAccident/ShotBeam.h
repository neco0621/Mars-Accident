#pragma once
#include "Vec2.h"
#include "Rect.h"
#include <vector>

class Stage1Scene;
class UFO;
class Player;
class Input;

namespace
{
	constexpr int ShotMax = 20;		
}
class ShotBeam
{
public:
	ShotBeam();
	virtual ~ShotBeam();

	virtual void Init();
	virtual void Update();
	virtual void Draw();

	//�e���X�^�[�g������
	virtual void Start(Vec2 pos);

	void SetMain(Stage1Scene* pS1Scene) { m_pS1Scene = pS1Scene; }
	void SetPlayer(Player* pPlayer) { m_pPlayer = pPlayer; }
	void SetHandle(int handle) { m_handle = handle; }


	bool isExist() const { return m_isExist; }

	//�����蔻��̋�`���擾����
	Rect GetColRect() const { return m_colRect; }
	

	int m_radius;
	int m_handle;
	float m_centerX;
	float m_centerY;
	//�����蔻��̋�`
	Rect m_colRect;
	//�\���ʒu
	Vec2 m_pos;
	Vec2 m_z;
	//�ړ���	1�t���[��������̈ړ��x�N�g��������
	Vec2 m_vec;
	float m_pSpeed;
	float m_pMove;
	bool MoveFlag;
protected:
	//SceneMain�̊֐����Ăяo�����߂Ƀ|�C���^���o���Ă���
	Stage1Scene* m_pS1Scene;
	//�V���b�g���������v���C���[�̃|�C���^���o���Ă���
	Player* m_pPlayer;
	//
	UFO* m_pUfo;

	bool m_isExist;	//���݂��邩�t���O(�g�p�����ǂ���)

private:
	//�c����\�����邽�߂ɉߋ��̈ʒu���o���Ă���
	std::vector<Vec2>  m_posLog;
};

