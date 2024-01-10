#pragma once
#include "Vec2.h"
#include "Rect.h"
#include <vector>

class SceneMain;
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

	void SetMain(SceneMain* pMain) { m_pMain = pMain; }
	void SetPlayer(Player* pPlayer) { m_pPlayer = pPlayer; }


	bool isExist() const { return m_isExist; }

	//�����蔻��̋�`���擾����
	Rect GetColRect() const { return m_colRect; }
	
	bool shotFlag[ShotMax];
	bool prevShotFlag;
	float m_radius;
	int m_handle;
	float m_centerX;
	float m_centerY;
	//�����蔻��̋�`
	Rect m_colRect;
	//�\���ʒu
	Vec2 m_pos;
	//�ړ���	1�t���[��������̈ړ��x�N�g��������
	Vec2 m_vec;
	float m_pSpeed;
	float m_pMove;
	bool MoveFlag;
	// �V���b�g�̐����Ă��鎞�ԃJ�E���^
	int shotLifeCounter;
protected:
	//SceneMain�̊֐����Ăяo�����߂Ƀ|�C���^���o���Ă���
	SceneMain* m_pMain;
	//�V���b�g���������v���C���[�̃|�C���^���o���Ă���
	Player* m_pPlayer;
	//
	UFO* m_pUfo;

	bool m_isExist;	//���݂��邩�t���O(�g�p�����ǂ���)

private:
	//�c����\�����邽�߂ɉߋ��̈ʒu���o���Ă���
	std::vector<Vec2>  m_posLog;
};

