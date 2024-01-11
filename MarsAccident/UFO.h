#pragma once
#include "Vec2.h"
#include "Rect.h"

class SceneMain;
class ShotBeam;
class UFO
{
public:
	UFO(SceneMain* pMain);
	~UFO();

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
	
	//接触したかの判定
	bool m_boundFlag;	

	//Beamの座標
	Vec2 m_beamPos;
public:
	//移動量	1フレーム当たりの移動ベクトルを入れる
	Vec2 m_vec;

	float JumpPower;
	bool isJump;
	float Gravity = 1.0f;
	float MaxGravity = 4.9f;

	bool m_MoveFlag;
};

