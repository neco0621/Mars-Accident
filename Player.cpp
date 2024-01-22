#include "Player.h"
#include "DxLib.h"
#include "Pad.h"
#include "Game.h"
#include "Scene/Stage1Scene.h"
#include "Scene/Stage2Scene.h"
#include "ShotBeam.h"

#include <cmath>

//Playerで使用する定数
namespace
{
	//移動速度
	constexpr float kSpeed = 5.0f;

	//キャラクターのサイズ
	constexpr int kWidth = 64;
	constexpr int kHeight = 64;

	//キャラクターのアニメーション
	constexpr int kUseFrame[] = { 1,2,1 };

	//アニメーション1コマのフレーム数
	constexpr int kAnimFrameNum = 8;

	//アニメーション1サイクルのフレーム数
	constexpr int kAnimFrameCycle = _countof(kUseFrame) * kAnimFrameNum;

	//魔法の杖の発射間隔
	constexpr int kBeamFrame = 10;
}

Player::Player(Stage1Scene* S1Scene) :
	m_pS1Scene(S1Scene),
	m_handle(-1),
	m_pos(Game::kScreenWidth * 0.5, Game::kScreenHeight * 0.75),
	m_dir(kDirRight),
	m_walkAnimFrame(0),
	m_beamFrame(0)
{
}

Player::Player(Stage2Scene* S2Scene) :
	m_pS2Scene(S2Scene),
	m_handle(-1),
	m_pos(Game::kScreenWidth * 0.5, Game::kScreenHeight * 0.75),
	m_dir(kDirRight),
	m_walkAnimFrame(0),
	m_beamFrame(0)

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

	//中心座標を指定して当たり判定のRectを生成する.
	m_colRect.SetCenter(m_pos.x, m_pos.y, kWidth - 20, kHeight);

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
	m_beamFrame++;
	if (m_beamFrame >= kBeamFrame)
	{
		ShotBeam* m_pShot = new ShotBeam;
		m_pShot->SetS1(m_pS1Scene);
		m_pShot->SetS2(m_pS2Scene);
		m_pShot->SetPlayer(this);
		m_pShot->Start(GetPos());
		//以降更新やメモリの解放はSceneMainに任せる
		m_pS1Scene->AddShot(m_pShot);
	
		m_beamFrame = 0;		
	}
}

void Player::S2Update()
{

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

	//中心座標を指定して当たり判定のRectを生成する.
	m_colRect.SetCenter(m_pos.x, m_pos.y, kWidth - 20, kHeight);

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
	m_beamFrame++;
	if (m_beamFrame >= kBeamFrame)
	{
		ShotBeam* m_pShot = new ShotBeam;
		m_pShot->SetS1(m_pS1Scene);
		m_pShot->SetS2(m_pS2Scene);
		m_pShot->SetPlayer(this);
		m_pShot->Start(GetPos());
		//以降更新やメモリの解放はSceneMainに任せる
		m_pS2Scene->AddShot(m_pShot);

		m_beamFrame = 0;
	}
}

void Player::Draw()
{
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
