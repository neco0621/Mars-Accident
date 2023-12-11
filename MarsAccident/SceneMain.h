#pragma once
#include <vector>
#include "Rect.h"
#include "Vec2.h"

struct CIRCLE
{
	float x;
	float y;
	float r;
};

class Player;
class UFO;
class Bg;
class EnemyBase;
class ShotBeam;
class Bg;

class SceneMain
{
public:
	SceneMain();
	virtual ~SceneMain();

	void Init();
	void End();

	void Update();
	void Draw();

	//特定の座標から一番近くにいる敵の座標を返す関数
	Vec2 GetNearEnemyPos(Vec2 pos);
	//ショットを追加する
	//登録できなかった場合はfalseを返す
	//登録できなかった場合は内部でpShot解放する
	bool AddShot(ShotBeam* pBeam);

	Vec2 m_toNear;

private:
	//敵キャラクターの生成
	void CreateEnemyLeft();
	void CreateEnemyRight();

private:
	//グラフィックのハンドル
	int m_gameScreenHandle; //ゲーム画面

	//グラフィックのハンドル
	int m_playerHandle;
	int m_enemyHandle;
	int m_bgHandle;

	

	//プレイヤー
	Player* m_pPlayer;

	UFO* m_pUfo;

	Bg* m_pBg;

	std::vector<ShotBeam*> m_pBeam;

	//敵
	std::vector<EnemyBase*> m_pEnemy;	//配列のサイズは実行時に決める(今回はコンストラクタ)
	//EnemyBase* m_pEnemy[16];   ←今までの書き方


	Rect m_pRect;

	//画面ワイプ処理
	int m_wipeFrame;

	//敵の登場間隔
	int m_enemyInterval;

	//ダメージを受けたときの画面揺れ演出
	int m_shakeFrame;
};