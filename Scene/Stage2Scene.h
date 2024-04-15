#pragma once
#include <vector>
#include "../Rect.h"
#include "../Vec2.h"
#include "Scene.h"



class Player;
class UFO;
class S2UFO;
class Rocket;
class Bg;
class EnemyBase;
class ShotBeam;
class Bg;

class Stage2Scene : public Scene
{
public:
	Stage2Scene(SceneManager& mgr);
	virtual ~Stage2Scene();

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

	//画面揺れの関数
	void ShakeScreen(int a, int b);

	//最も近い敵の座標
	Vec2 m_toNear;
	//現在座標
	Vec2 pos;
private:

	//状態遷移用メンバ関数ポインタの宣言
	using UpdateFunc_t = void (Stage2Scene::*)(Input&);
	using DrawFunc_t = void (Stage2Scene::*)();
	UpdateFunc_t updateFunc_ = nullptr;
	DrawFunc_t drawFunc_ = nullptr;

	//敵キャラクターの生成
	void CreateEnemyLeft();
	void CreateEnemyRight();

	//グラフィックのハンドル
	int m_gameScreenHandle;			//ゲーム画面
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
	int m_shakeHandle;				//画面揺れ
	int m_startTitle;				//スタートボタン

	//アニメーションのハンドル
	int m_AnimHandle;				//爆発アニメーション		
	int m_enemyEXP;					//敵の爆発アニメーション

	//音声のハンドル
	int m_bgm;						//BGM
	int m_hitHandle;				//UFOと弾の衝突時のSE
	int m_damageHandle;				//宇宙船と敵の衝突時のSE
	int m_gameover;					//ゲームオーバー時のSE
	int m_destoryEnemy;				//敵撃破時のSE
	int m_clearSE;					//ステージクリア時のSE
	int CheckSE;					//決定ボタンを押したときのSE

	//その他
	int m_downEnemyCount;			//倒した敵の数
	int m_lifeCount;				//宇宙船の体力
	int m_shakeSize;				//画面の揺れ幅
	int m_shakeFrame;				//画面が揺れている秒数
	int m_animFrame;				//アニメーションの再生時間
	int frame_ = 0;					//フェイドのフレーム
	
	//フラグ
	bool m_damageFlag;
	bool m_gameOverFlag;			//ゲームオーバーになったかどうかのフラグ
	bool IsGround;					//地面に接しているかのフラグ
	bool m_isShake;					//画面揺れを実行するフラグ
	bool StartFlag;					//ゲームの処理開始フラグ
	bool AnimFlag;					//アニメーションを再生するフラグ

	//プレイヤー
	Player* m_pPlayer;

	//UFO
	UFO* m_pUfo;

	//2ステージのみのUFO
	S2UFO* m_pS2ufo;

	//背景
	Bg* m_pBg;

	Rocket* m_pRocket;

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
	int m_S2shakeFrame;
};