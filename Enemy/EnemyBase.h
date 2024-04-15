#pragma once
#include "../Vec2.h"
#include "../Rect.h"



//プロトタイプ宣言
class TutorialScene;
class Stage1Scene;
class Stage2Scene;

//敵の継承クラス
//継承元となるクラスを基底クラスと呼ぶ
class EnemyBase
{
public:

	EnemyBase();
	virtual ~EnemyBase();

	virtual void Init();
	virtual void Update();
	virtual void S2Update();
	virtual void Draw();

	//メンバー変数にアクセスする
	void SetHandle(int handle) { m_handle = handle; }
	void SetAnimHandle(int animHandle) { m_animHandle = animHandle; }

	//生存フラグ
	bool isExist() const { return m_isExist; }
	//位置の取得
	Vec2 GetPos() const { return m_pos; }
	//当たり判定の矩形を取得する
	Rect GetColRect() const { return m_colRect; }

	//敵キャラクターをスタートさせる
	virtual void Start() = 0;

	//中心位置
	float m_centerX;
	float m_centerY;
	
	//半径
	float m_radius;

	//画面の4分の3の位置
	float m_tq;

	//表示位置
	Vec2 m_pos;

	//チュートリアルシーン
	TutorialScene* m_pTuScene;
	//ステージ1シーン
	Stage1Scene* m_pS1Scene;
	//ステージ2シーン
	Stage2Scene* m_pS2Scene;

protected:
	//m_posを左上に、m_handleのグラフィックサイズを幅高さにした
	//当たり判定を設定する
	virtual void UpdateCollision();

	//グラフィックのハンドル
	int m_handle;

	//アニメーションのハンドル
	int m_animHandle;

	//存在するかフラグ(使用中かどうか)
	bool m_isExist;


	//当たり判定の矩形
	Rect m_colRect;

	//移動量	1フレーム当たりの移動ベクトルを入れる
	Vec2 m_vec;
};