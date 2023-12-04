#pragma once
#include "Vec2.h"

//矩形の座標を管理するクラス
class Rect
{
public:
	Rect();
	virtual ~Rect();

	//描画
	void Draw(unsigned int Color, bool isFill);
	void DrawC(unsigned int Color, bool isFill);

	//左上座標と幅高さを指定
	void SetLT(float left, float top, float width, float height);
	//中心座標と幅高さを指定
	void SetCenter(float x, float y, float width, float height);
	//中心座標と半径を指定
	void SetRadius(float x, float y, float radius);

	//ゲームによっては中心座標で指定したり足元の座標で指定する
	//set関数があったほうが便利かもしれない

	//必要な情報を取得する
	float GetWidth() const;		//幅
	float GetHeight() const;	//高さ
	Vec2 GetCenter() const;		//中心座標

	//矩形同士の当たり判定
	bool BoxCollision(const Rect& rect);
	//円同士の当たり判定
	bool CirCleCollision(const Rect& rect);

private:
	float m_left;	//左上のX座標
	float m_top;	//左上のY座標
	float m_right;	//右上のX座標
	float m_bottom;	//右上のY座標

	float m_centerX;	//中心のX座標
	float m_centerY;	//中心のY座標
	float m_radius;		//半径

};

