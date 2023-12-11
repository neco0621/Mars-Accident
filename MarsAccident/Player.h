#pragma once
#include <vector>
#include "Vec2.h"
#include "Rect.h"

class SceneMain;
class ShotBeam;
class Player
{
public:
	//向いている方向
	enum Dir
	{
		kDirDown,	//下	= 0
		kDirLeft,	//左	= 1
		kDirRight,	//右	= 2
		kDirUp,		//上	= 3
	};

public:
	Player(SceneMain* pMain);
	~Player();

	void Init();
	void Update();
	void Draw();

	//メンバー変数にアクセスする
	void SetHandle(int handle) { m_handle = handle; }
	//プレイヤーの現在位置を取得する
	Vec2 GetPos() const { return m_pos; }
	//プレイヤーの当たり判定を取得する
	Rect GetColRect() const;

	//プレイヤーがダメージを受けた
	void OnDamage();

private:
	SceneMain* m_pMain;

	std::vector<ShotBeam> m_pBeam;

	int m_handle;	//グラフィックのハンドル

	//表示位置
	Vec2 m_pos;

	//当たり判定用の矩形
	Rect m_colRect;

	//向いている方向
	Dir m_dir;

	//歩きアニメーション
	int m_walkAnimFrame;

	//魔法の杖の発射フレームカウント
	int m_beamFrame;

	//ダメージを受けてからのフレーム数
	//当たった時にフレーム数を設定して
	//毎フレーム減らしていく
	int m_damageFrame;
};
