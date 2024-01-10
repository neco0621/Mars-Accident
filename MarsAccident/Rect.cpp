#include "Rect.h"
#include <DxLib.h>
#include<cmath>
#include <cassert>

Rect::Rect() :
	m_left(0.0f),
	m_top(0.0f),
	m_right(0.0f),
	m_bottom(0.0f)
{
}

Rect::~Rect()
{
}

void Rect::Draw(unsigned int color, bool isFill)
{
	DrawBox(static_cast<int> (m_left), static_cast<int>(m_top), static_cast<int> (m_right), static_cast<int>(m_bottom), color, isFill);
}

void Rect::DrawC(unsigned int color, bool isFill)
{
	DrawCircle(static_cast<int> (m_centerX), static_cast<int>(m_centerY), static_cast<int> (m_radius), color, isFill);
}

void Rect::SetLT(float left, float top, float width, float height)
{
	m_left = left;			//�����X���W
	m_top = top;			//�����Y���W
	m_right = left + width;	//�E����X���W
	m_bottom = top + height;//�E����Y���W
}

void Rect::SetCenter(float x, float y, float width, float height)
{
	m_left = x - width / 2;
	m_top = y - height / 2;
	m_right = x + width / 2;
	m_bottom = y + height / 2;
}


void Rect::SetRadius(float x, float y, float radius)
{
	m_centerX = x;
	m_centerY = y;
	m_radius = radius;
}

float Rect::GetWidth() const
{
	assert(m_right >= m_left);	//���E�̍��W�̓���ւ��`�F�b�N

	return m_right - m_left;
}

float Rect::GetHeight() const
{
	assert(m_bottom >= m_top);	//�㉺�̍��W�̓���ւ��`�F�b�N

	return m_bottom - m_top;
}

Vec2 Rect::GetCenter() const
{
	//���S���W
	float x = 0.0f;
	float y = 0.0f;

	x = (m_right + m_left) / 2;
	y = (m_top + m_bottom) / 2;

	return Vec2{ x,y };
}

float Rect::DistanceSqrf(const float t_x1, const float t_y1, const float t_x2, const float t_y2)
{
	float dx = t_x2 - t_x1;
	float dy = t_y2 - t_y1;

	return (dx * dx) + (dy * dy);
}

bool Rect::BoxCollision(const Rect& rect)
{
	//��΂ɓ�����Ȃ��p�^�[�����͂����Ă���
	if (m_left > rect.m_right)	return false;
	if (m_top > rect.m_bottom)	return false;
	if (m_right < rect.m_left)	return false;
	if (m_bottom < rect.m_top)	return false;

	//������Ȃ��p�^�[���ȊO�͓������Ă���
	return true;
}

bool Rect::CirCleCollision(const Rect& rect)
{
	float dx = m_centerX - rect.m_centerX;
	float dy = m_centerY - rect.m_centerY;
	float dr = dx * dx + dy * dy;

	float ar = m_radius + rect.m_radius;
	float dl = ar * ar;
	if (dr <= dl)
	{
		return true;
	}
	return false;
}


bool Rect::DistanceCollision(const Rect& rect)
{
	bool nResult = false;
	if ((m_centerX > rect.m_left - m_radius) &&
		(m_centerX < rect.m_right + m_radius) &&
		(m_centerY > rect.m_top - m_radius) &&
		(m_centerY < rect.m_bottom + m_radius))
	{
		nResult = true;                                                                                          
		float dl = m_radius * m_radius;
		// ��
		if (m_centerX < rect.m_left)
		{
			// ����
			if ((m_centerY < rect.m_top))
			{
				if ((DistanceSqrf(rect.m_left, rect.m_top, m_centerX, m_centerY) >= dl))
				{
					nResult = false;
				}
			}
			else
			{
				// ����
				if ((m_centerY > rect.m_bottom))
				{
					if ((DistanceSqrf(rect.m_left, rect.m_bottom, m_centerX, m_centerY) >= dl))
					{
						nResult = false;
					}
				}
			}
		}
		else
		{
			// �E
			if (m_centerX > rect.m_right)
			{
				// �E��
				if ((m_centerY < rect.m_top))
				{
					if ((DistanceSqrf(rect.m_right, rect.m_top, m_centerX, m_centerY) >= dl))
					{
						nResult = false;
					}
				}
				else
				{
					// �E��
					if ((m_centerY > rect.m_bottom))
					{
						if ((DistanceSqrf(rect.m_right, rect.m_bottom, m_centerX, m_centerY) >= dl))
						{
							nResult = false;
						}
					}
				}
			}
		}
	}

	return true;
}
