#pragma once
#include "Vec2.h"

//��`�̍��W���Ǘ�����N���X
class Rect
{
public:
	Rect();
	virtual ~Rect();

	//�`��
	void Draw(unsigned int Color, bool isFill);
	void DrawC(unsigned int Color, bool isFill);

	//������W�ƕ��������w��
	void SetLT(float left, float top, float width, float height);
	//���S���W�ƕ��������w��
	void SetCenter(float x, float y, float width, float height);
	//���S���W�Ɣ��a���w��
	void SetRadius(float x, float y, float radius);

	//�Q�[���ɂ���Ă͒��S���W�Ŏw�肵���葫���̍��W�Ŏw�肷��
	//set�֐����������ق����֗���������Ȃ�

	//�K�v�ȏ����擾����
	float GetWidth() const;		//��
	float GetHeight() const;	//����
	Vec2 GetCenter() const;		//���S���W

	//��`���m�̓����蔻��
	bool BoxCollision(const Rect& rect);
	//�~���m�̓����蔻��
	bool CirCleCollision(const Rect& rect);

private:
	float m_left;	//�����X���W
	float m_top;	//�����Y���W
	float m_right;	//�E���X���W
	float m_bottom;	//�E���Y���W

	float m_centerX;	//���S��X���W
	float m_centerY;	//���S��Y���W
	float m_radius;		//���a

};

