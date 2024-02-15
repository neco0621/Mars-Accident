#pragma once
#include <vector>
#include "../Rect.h"
#include "../Vec2.h"
#include "Scene.h"

class Player;
class UFO;
class Rocket;
class Bg;
class EnemyBase;
class ShotBeam;
class Bg;

class Stage1Scene : public Scene
{
public:
	Stage1Scene(SceneManager& mgr);
	virtual ~Stage1Scene();

	void Init();
	void End();

	void Update(Input& input);

	void Draw();

	//特定の座標から一番近くにいる敵の座標を返す関数
	Vec2 GetNearEnemyPos(Vec2 pos);
	//ショットを追加する
	//登録できなかった場合はfalseを返す
	//登録できなかった場合は内部でpShot解放する
	bool AddShot(ShotBeam* pBeam);

	void ShakeScreen(int a, int b);
	void CreateAnimation();

	Vec2 m_toNear;
	Vec2 pos;
private:
	int handle_ = 0;
	int frame_ = 0;

	//状態遷移用メンバ関数ポインタの宣言
	using UpdateFunc_t = void (Stage1Scene::*)(Input&);
	using DrawFunc_t = void (Stage1Scene::*)();
	UpdateFunc_t updateFunc_ = nullptr;
	DrawFunc_t drawFunc_ = nullptr;

private:
	//敵キャラクターの生成
	void CreateEnemyLeft();
	void CreateEnemyRight();

private:
	//グラフィックのハンドル
	int m_gameScreenHandle; //ゲーム画面

	//Playerのハンドル
	int m_playerHandle;
	//敵のグラフィック
	int m_leftEnemyHandle;
	int m_rightEnemyHandle;
	//ロケットの体力のハンドル
	int m_life1Handle;
	int m_life2Handle;
	int m_life3Handle;
	//背景のハンドル
	int m_bgHandle;
	//Shotのハンドル
	int m_shotHandle;
	//ロケットのハンドル
	int m_rocketHandle;
	//UFOのハンドル
	int m_ufoHandle;
	//アニメーションのハンドル
	int m_AnimHandle;
	//画面揺れのハンドル
	int m_shakeHandle;
	//UFOのダメージ音のハンドル
	int m_hitHandle;
	//ロケットのダメージ音のハンドル
	int m_damageHandle;
	//ゲームクリア時の音のハンドル
	int m_clearHandle;
	//エネミー撃破時のアニメーションハンドル
	int m_enemyEXP;
	//倒した敵の数
	int m_downEnemyCount;
	//現在のロケットの体力
	int m_lifeCount;
	//エネミー撃破時のサウンドハンドル
	int m_destoryEnemy;
	//画面揺れのサイズ
	int m_shakeSize;
	//画面揺れのフレーム
	int m_shakeFrame;
	//Start用のタイトルボタン
	int StartTitle;
	//アニメーションのフレーム
	int m_animFrame;
	//Bgmハンドル
	int m_bgm;
	//
	int m_gameover;
	//
	int m_clearSE;
	//
	int CheckSE;

	//
	bool m_damageFlag;
	//
	bool m_gameOverFlag;
	//
	bool IsGround;
	//
	bool m_isShake;
	//
	bool StartFlag;
	//
	bool m_clearFlag;

public:
	//
	bool AnimFlag;

	
	//プレイヤー
	Player* m_pPlayer;

	//UFO
	UFO* m_pUfo;

	//背景
	Bg* m_pBg;

	//ロケット
	Rocket* m_pRocket;

	//Shot
	std::vector<ShotBeam*> m_pBeam;

	//敵
	std::vector<EnemyBase*> m_pEnemy;	//配列のサイズは実行時に決める(今回はコンストラクタ)
	//EnemyBase* m_pEnemy[16];   ←今までの書き方

	//アニメーション
	std::vector<Stage1Scene*> m_pAnimation;

	//Rect
	Rect m_pRect;

	//画面ワイプ処理
	int m_wipeFrame;

	//敵の登場間隔
	int m_enemyInterval;
};