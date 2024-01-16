#include "Player.h"
#include "DxLib.h"
#include "Pad.h"
#include "Game.h"
#include "Scene/Stage1Scene.h"
#include "ShotBeam.h"

#include <cmath>

//Playerで使用する定数
namespace
{
	//移動速度
	constexpr float kSpeed = 5.0f;

	//キャラクターのサイズ
	constexpr int kWidth = 32;
	constexpr int kHeight = 32;

	//キャラクターのアニメーション
	constexpr int kUseFrame[] = { 0,1,2,1 };

	//アニメーション1コマのフレーム数
	constexpr int kAnimFrameNum = 8;

	//アニメーション1サイクルのフレーム数
	constexpr int kAnimFrameCycle = _countof(kUseFrame) * kAnimFrameNum;

	//ダメージ演出フレーム数
	constexpr int kDamageFrame = 60;

	//魔法の杖の発射間隔
	constexpr int kBeamFrame = 30;
}

Player::Player(Stage1Scene* S1Scene) :
	m_pS1Scene(S1Scene),
	m_handle(-1),
	m_pos(Game::kScreenWidth * 0.5, Game::kScreenHeight * 0.75),
	m_dir(kDirDown),
	m_walkAnimFrame(0),
	m_beamFrame(0),
	m_damageFrame(0)
{
}

Player::~Player()
{
}

void Player::Init()
{
}

void Player::Update()
{
	//ダメージ演出の進行
	m_damageFrame--;
	if (m_damageFrame < 0) m_damageFrame = 0;

	//padの十字キーを使用してプレイヤーを移動させる
	int pad = GetJoypadInputState(DX_INPUT_KEY_PAD1);

	/* (pad & PAD_INPUT_UP) == 0 の原理*/
	//0000 0000 0000 0000 0000 0000 0000 0000　基本
	//0000 0000 0000 0000 0000 0000 0000 1000　上キーが押されたとき

	bool isMove = false;	//移動しているかどうか

	//移動量を持つようにする
	Vec2 move{ 0.0f,0.0f };
	if ((pad & PAD_INPUT_LEFT) != 0)
	{
		//m_pos.x -= kSpeed;
		move.x -= kSpeed;
		m_dir = kDirLeft;
		isMove = true;
	}
	if ((pad & PAD_INPUT_RIGHT) != 0)
	{
		//m_pos.x += kSpeed;
		move.x += kSpeed;
		m_dir = kDirRight;
		isMove = true;
	}

	if (m_pos.x < kWidth / 2)
	{
		m_pos.x = kWidth / 2;
	}
	if (m_pos.x > Game::kScreenWidth - kWidth / 2)
	{
		m_pos.x = Game::kScreenWidth - kWidth / 2;
	}

	//斜め移動の場合も同じ速さで移動するようにする

	//ベクトルの正規化
	move.normalize();

	//ベクトルの長さをkspeedにする
	move *= kSpeed;

	//座標とベクトルの足し算
	m_pos += move;

	//当たり判定の更新
	m_colRect.SetCenter(m_pos.x, m_pos.y, kWidth, kHeight);

	if (isMove)
	{
		//歩きアニメーション
		m_walkAnimFrame++;
		if (m_walkAnimFrame >= kAnimFrameCycle)
		{
			m_walkAnimFrame = 0;
		}
	}
	else
	{
		m_walkAnimFrame = kAnimFrameNum;
	}

	//ショット
	//m_beamFrame++;
	//if (m_beamFrame >= kBeamFrame)
	//{
	if (CheckHitKey(KEY_INPUT_SPACE))
	{
		ShotBeam* m_pShot = new ShotBeam;
		m_pShot->SetMain(m_pS1Scene);
		m_pShot->SetPlayer(this);
		m_pShot->Start(GetPos());
		//以降更新やメモリの解放はSceneMainに任せる
		m_pS1Scene->AddShot(m_pShot);
	}
		//m_beamFrame = 0;
		
	//}
}

void Player::Draw()
{
	//ダメージ演出   2フレーム間隔で表示非表示切り替え
	//0:表示される
	//1:表示される
	//2:非表示
	//3:非表示
	//4:表示
	//%4 することで01230123...に変換する
	if (m_damageFrame % 4 >= 2) return;


	int animFrame = m_walkAnimFrame / kAnimFrameNum;

	int srcX = kWidth * kUseFrame[animFrame];
	int srcY = kHeight * m_dir;

	//DrawRectGraph(static_cast<int>(m_pos.x), static_cast<int>(m_pos.y),
		//srcX, srcY, kWidth, kHeight, m_handle, true);

	//DXライブラリにはリファレンスページに書かれてない関数が多数存在する
	//DxLib.hを確認してそれっぽい関数を探したり検索したりしてみよう
	DrawRectRotaGraph(static_cast<int>(m_pos.x), static_cast<int>(m_pos.y),
		srcX, srcY, kWidth, kHeight,
		1.0, 0.0,
		m_handle, true, false);

#ifdef _DEBUG
	//当たり判定の表示
	m_colRect.Draw(GetColor(0, 0, 255), false);
#endif
}

void Player::OnDamage()
{
	//ダメージ演出中は再度ダメージを食らわない
	if (m_damageFrame > 0)	return;
	//演出フレーム数を設定する
	m_damageFrame = kDamageFrame;
}
