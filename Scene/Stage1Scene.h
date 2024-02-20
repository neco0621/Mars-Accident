#pragma once
#include <vector>
#include "../Rect.h"
#include "../Vec2.h"
#include "Scene.h"

//プロトタイプ宣言
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

	//画面揺れ
	void ShakeScreen(int a, int b);
	//アニメーション生成
	void CreateAnimation();

	//一番近い敵の位置
	Vec2 m_toNear;
	//現在位置
	Vec2 pos;
private:

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
	int m_gameScreenHandle;			//ゲーム画面

	//グラフィックのハンドル
	int m_playerHandle;				//プレイヤー
	int m_leftEnemyHandle;			//敵
	int m_rightEnemyHandle;			//敵
	int m_life1Handle;				//宇宙船の体力
	int m_life2Handle;				//宇宙船の体力
	int m_life3Handle;				//宇宙船の体力
	int m_bgHandle;					//背景
	int m_shotHandle;				//弾
	int m_rocketHandle;				//ロケット
	int m_ufoHandle;				//UFO
	int m_AnimHandle;				//アニメーション
	int m_shakeHandle;				//画面揺れ
	int m_hitHandle;				//宇宙船と敵の衝突時
	int m_clearHandle;				//ゲームクリアの文字
	int LeftHandle;					//Aキー
	int LeftArrowHandle;			//左の矢印
	int RightHandle;				//Dキー
	int RightArrowHandle;			//右の矢印
	int StartTitle;					//スタートのタイトル文字
	int m_enemyEXP;					//敵の爆発アニメーション			

	int m_downEnemyCount;			//敵の撃破数カウント
	int m_lifeCount;				//宇宙船の残り体力カウント
	int m_shakeSize;				//画面揺れのサイズ
	int m_shakeFrame;				//画面揺れフレーム
	int m_animFrame;				//アニメーションのフレーム
	
	int m_bgm;						//BGM
	int m_destoryEnemy;				//敵撃破時の音声
	int m_gameover;					//ゲームオーバー時のSE
	int m_clearSE;					//ゲームクリア時のSE
	int CheckSE;					//決定時のSE
	int m_damageHandle;				//宇宙船と敵の衝突時の音声

	bool m_damageFlag;				//ダメージを受けたかどうかのフラグ
	bool IsGround;					//地面についているかどうかのフラグ
	bool m_isShake;					//画面揺れを行っているかのハンドル
	bool StartFlag;					//ゲームスタートフラグ
	bool m_clearFlag;				//ゲームクリアフラグ
	bool m_gameOverFlag;			//ゲームオーバー時のフラグ

public:
	bool AnimFlag;					//アニメーション開始フラグ
	
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
	
	//アニメーション
	std::vector<Stage1Scene*> m_pAnimation;

	//当たり判定
	Rect m_pRect;

	//画面ワイプ処理
	int m_wipeFrame;

	//敵の登場間隔
	int m_enemyInterval;
};