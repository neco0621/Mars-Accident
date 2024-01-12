#pragma once
#include "StageBase.h"
#include <vector>
#include "../Rect.h"
#include "../Vec2.h"

class UFO;
class Rocket;
class Bg;
class EnemyBase;
class ShotBeam;
class Bg;

class Stage1 : public StageBase
{
public:
	Stage1(StageManager& manager);
	virtual ~Stage1();

	virtual void Init() override;
	virtual void Update() override;
	virtual void Draw() override;
	//特定の座標から一番近くにいる敵の座標を返す関数
	Vec2 GetNearEnemyPos(Vec2 pos);
	//ショットを追加する
	//登録できなかった場合はfalseを返す
	//登録できなかった場合は内部でpShot解放する
	bool AddShot(ShotBeam* pBeam);

	Vec2 m_toNear;

private:
	int handle_ = 0;
	int frame_ = 0;

	//更新メンバ関数ポインタ
	void (Stage1::* updateFunc_)(Input& input);
	//描画メンバ関数ポインタ
	using DrawFunc_t = void (Stage1::*) ();
	DrawFunc_t drawFunc_;
	void FadeInUpdate(Input& input);	//フェードイン状態
	void NormalUpdate(Input& input);	//通常状態
	void FadeOutUpdate(Input& input);	//フェードアウト状態

	//描画関数
	void FadeDraw();	//フェード中描画
	void NormalDraw();	//非フェード描画

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
	int m_rocketHandle;

	

	UFO* m_pUfo;

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
	int m_shakeFrame;
};

