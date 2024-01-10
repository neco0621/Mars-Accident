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
	m_left = left;			//左上のX座標
	m_top = top;			//左上のY座標
	m_right = left + width;	//右下のX座標
	m_bottom = top + height;//右下のY座標
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
	assert(m_right >= m_left);	//左右の座標の入れ替わりチェック

	return m_right - m_left;
}

float Rect::GetHeight() const
{
	assert(m_bottom >= m_top);	//上下の座標の入れ替わりチェック

	return m_bottom - m_top;
}

Vec2 Rect::GetCenter() const
{
	//中心座標
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
	//絶対に当たらないパターンをはじいていく
	if (m_left > rect.m_right)	return false;
	if (m_top > rect.m_bottom)	return false;
	if (m_right < rect.m_left)	return false;
	if (m_bottom < rect.m_top)	return false;

	//当たらないパターン以外は当たっている
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
		// 左
		if (m_centerX < rect.m_left)
		{
			// 左上
			if ((m_centerY < rect.m_top))
			{
				if ((DistanceSqrf(rect.m_left, rect.m_top, m_centerX, m_centerY) >= dl))
				{
					nResult = false;
				}
			}
			else
			{
				// 左下
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
			// 右
			if (m_centerX > rect.m_right)
			{
				// 右上
				if ((m_centerY < rect.m_top))
				{
					if ((DistanceSqrf(rect.m_right, rect.m_top, m_centerX, m_centerY) >= dl))
					{
						nResult = false;
					}
				}
				else
				{
					// 右下
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
