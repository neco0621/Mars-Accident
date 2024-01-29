#pragma once
#include "../Vec2.h"
#include "../Rect.h"

//�G�̌p���N���X
//�p�����ƂȂ�N���X�����N���X�ƌĂ�

class Stage1Scene;
class Stage2Scene;
class EnemyBase
{
public:
	EnemyBase();
	virtual ~EnemyBase();

	virtual void Init();
	virtual void Update();
	virtual void Draw();

	//�����o�[�ϐ��ɃA�N�Z�X����
	void SetHandle(int handle) { m_handle = handle; }
	void SetAnimHandle(int animHandle) { m_animHandle = animHandle; }

	bool isExist() const { return m_isExist; }
	//�ʒu�̎擾
	Vec2 GetPos() const { return m_pos; }
	//�����蔻��̋�`���擾����
	Rect GetColRect() const { return m_colRect; }

	//�G�L�����N�^�[���X�^�[�g������
	virtual void Start() = 0;

	float m_centerX;
	float m_centerY;
	float m_radius;
	float m_tq;

	//�\���ʒu
	Vec2 m_pos;
	Stage1Scene* m_pS1Scene;

	int m_animFrame;
	bool enemyEXPFlag;
protected:
	//m_pos������ɁAm_handle�̃O���t�B�b�N�T�C�Y�𕝍����ɂ���
	//�����蔻���ݒ肷��
	virtual void UpdateCollision();
	
	//private:	//�p���悩����Q�Ƃł��Ȃ�
protected:	//�p���悩��Q�Ƃł���
	int m_handle;	//�O���t�B�b�N�̃n���h��
	int m_animHandle;

	bool m_isExist;	//���݂��邩�t���O(�g�p�����ǂ���)


	//�����蔻��̋�`
	Rect m_colRect;

	//�ړ���	1�t���[��������̈ړ��x�N�g��������
	Vec2 m_vec;
};