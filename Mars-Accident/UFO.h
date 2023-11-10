#pragma once
#include "Vec2.h"
#include "Rect.h"

class GamePlayingScene;
class ShotBeam;
class UFO
{
public:
	UFO(GamePlayingScene* pGame);
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

private:
	GamePlayingScene* m_pGame;
	ShotBeam* m_pBeam;

	int m_handle;	//グラフィックのハンドル



	//接触したかの判定
	bool m_boundFlag;

	//表示位置
	Vec2 m_pos;

	//Beamの座標
	Vec2 m_beamPos;

	//当たり判定用の矩形
	Rect m_colRect;
};

