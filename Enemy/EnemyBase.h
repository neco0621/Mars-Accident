#pragma once
#include "../Vec2.h"
#include "../Rect.h"



//�v���g�^�C�v�錾
class TutorialScene;
class Stage1Scene;
class Stage2Scene;

//�G�̌p���N���X
//�p�����ƂȂ�N���X�����N���X�ƌĂ�
class EnemyBase
{
public:

	EnemyBase();
	virtual ~EnemyBase();

	virtual void Init();
	virtual void Update();
	virtual void S2Update();
	virtual void Draw();

	//�����o�[�ϐ��ɃA�N�Z�X����
	void SetHandle(int handle) { m_handle = handle; }
	void SetAnimHandle(int animHandle) { m_animHandle = animHandle; }

	//�����t���O
	bool isExist() const { return m_isExist; }
	//�ʒu�̎擾
	Vec2 GetPos() const { return m_pos; }
	//�����蔻��̋�`���擾����
	Rect GetColRect() const { return m_colRect; }

	//�G�L�����N�^�[���X�^�[�g������
	virtual void Start() = 0;

	//���S�ʒu
	float m_centerX;
	float m_centerY;
	
	//���a
	float m_radius;

	//��ʂ�4����3�̈ʒu
	float m_tq;

	//�\���ʒu
	Vec2 m_pos;

	//�`���[�g���A���V�[��
	TutorialScene* m_pTuScene;
	//�X�e�[�W1�V�[��
	Stage1Scene* m_pS1Scene;
	//�X�e�[�W2�V�[��
	Stage2Scene* m_pS2Scene;

protected:
	//m_pos������ɁAm_handle�̃O���t�B�b�N�T�C�Y�𕝍����ɂ���
	//�����蔻���ݒ肷��
	virtual void UpdateCollision();

	//�O���t�B�b�N�̃n���h��
	int m_handle;

	//�A�j���[�V�����̃n���h��
	int m_animHandle;

	//���݂��邩�t���O(�g�p�����ǂ���)
	bool m_isExist;


	//�����蔻��̋�`
	Rect m_colRect;

	//�ړ���	1�t���[��������̈ړ��x�N�g��������
	Vec2 m_vec;
};