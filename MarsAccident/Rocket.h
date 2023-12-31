#pragma once
#include "Vec2.h"
#include "Rect.h"

class SceneMain;
class ShotBeam;
class Rocket
{
public:
	Rocket(SceneMain* pMain);
	~Rocket();

	void Init();
	void Update();
	void Draw();

	//メンバー変数にアクセスする
	void SetHandle(int handle) { m_handle = handle; }
	//UFOの現在位置を取得する
	Vec2 GetPos() const { return m_pos; }
	//UFOの当たり判定を取得する
	Rect GetColRect() const { return m_colRect; }

	//当たり判定用の矩形
	Rect m_colRect;

	//表示位置
	Vec2 m_pos;
	//半径
	float m_radius;
private:
	SceneMain* m_pMain;
	ShotBeam* m_pBeam;

	int m_handle;	//グラフィックのハンドル

	//Beamの座標
	Vec2 m_beamPos;

};

