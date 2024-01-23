#include "Animation.h"

Animation AnimExpl;	//爆発アニメーション

//読込・ハンドル生成
BOOL Animation_Init(VOID)
{
	//爆発アニメーション
	AnimExpl = LoadAnimation(
		LoadGraphic(					//アニメーション画像読み込み
			GraphicPathTitleAnimExpl,	//アニメーション画像パス
			(m_pUfo->m_pos.x,m_pUfo->m_pos.y),						//右上から
			GraAlignTopR),
		AnimExplDivX,					//アニメーション横分割数
		AnimExplDivY					//アニメーション縦分割数
	); if (AnimExpl.Handle[0] == -1) { return FALSE; }
}

//後始末
VOID Animation_End(VOID)
{
	DeleteAnimation(AnimExpl);

	return;
}


//読込エラーメッセージ
VOID AnimationLoadErrMessage(const char* path)
{
	//エラー用文字列
	char ErrStr[AnimationPathstrMax];

	//エラー用文字列の内容を空にする
	for (int i = 0; i < AnimationPathstrMax; i++) { ErrStr[i] = '\0'; }

	//エラー内容を連結して生成
	sprintf_s(ErrStr, sizeof(ErrStr), "%s%s", path, AnimationLoadErrCap);

	//パスが間違っているなどでインストールできない場合はエラー
	MessageBox(
		GetMainWindowHandle(),		//ウィンドウハンドル
		ErrStr,						//エラー内容
		AnimationLoadErrTitle,		//エラータイトル
		MB_OK);						//OKボタンのみ

	return;
}

//アニメーション読み込み
Animation LoadAnimation(Graphic graphic, int XNum, int YNum)
{
	Animation animation;

	//読み込んだ画像の情報を引き継ぐ
	animation.g = graphic;

	//画像の分割数設定
	animation.a.DivX = XNum;
	animation.a.DivY = YNum;

	//画像の幅と高さを再計算
	animation.g.c.Width = animation.g.c.Width / XNum;
	animation.g.c.Height = animation.g.c.Height / YNum;

	//アニメーションのハンドル配列を動的確保
	animation.Handle
		= (int*)			//int型のポインタに型変換
		calloc(				//メモリを動的確保して値をゼロで初期化
			XNum * YNum		//確保する要素の個数
			, sizeof(int)	//確保する要素のデータ型
	);

	//アニメーションを分割してメモリに読込
	LoadDivGraph(
		graphic.c.Path,			//アニメーションのパス
		(XNum * YNum),			//分割総数
		XNum, YNum,				//|(横)分割数、-(縦)分割数
		animation.g.c.Width,	//分割した1枚の幅
		animation.g.c.Height,	//分割した1枚の高さ
		animation.Handle		//連続したハンドル配列の先頭
	);

	//読み込みエラー
	if (animation.Handle == NULL || animation.Handle[0] == -1)
	{
		AnimationLoadErrMessage(graphic.c.Path);
	}

	//メモリに読み込んだ画像はサイズを知りたいだけなので用済み
	//※graphicのhandleは消去される
	DeleteGraphic(graphic);

	//ハンドルの要素数を初期化
	animation.a.NowHandleIndex = 0;

	//最初のアニメーションの要素数をセット
	animation.g.Handle = animation.Handle[animation.a.NowHandleIndex];

	return animation;
}

//描画
VOID DrawAnimation(Animation* animation)
{
	//画像描画
	DrawGraphic(&animation->g);

	//アニメーション中ならコマを進める
	if (animation->a.IsAnimStractFlg == TRUE)
	{
		if (animation->a.FrameByFrameCnt < animation->a.DivY - 1)
		{
			animation->a.FrameByFrameCnt++;
		}
		else
		{
			//コマを進めている部分(-1をしないと配列を超える)
			if (animation->a.NowHandleIndex < animation->a.DivX * animation->a.DivY)
			{
				animation->a.NowHandleIndex++;
			}
			else
			{
				animation->a.NowHandleIndex = 0;
			}

			//アニメーションの要素数をセット
			animation->g.Handle = animation->Handle[animation->a.NowHandleIndex];

			//コマ送り初期化
			animation->a.FrameByFrameCnt = 0;
		}

		//アニメーション時間カウントアップ
		animation->a.FrameByFrameCnt++;

		//アニメーションが無限継続ではない時
		if (animation->a.FrameMax != AnimationInfinity)
		{
			//アニメーションが一回のみならアニメーションの時間を無視
			if (animation->a.FrameMax != AnimationOnce)
			{
				//アニメーション時間が終わりならばアニメーション終了
				if (animation->a.FrameCnt > animation->a.FrameMax)
				{
					animation->a.IsAnimStractFlg = FALSE;	//アニメーション開始フラグOFF
					animation->g.c.IsDraw = FALSE;			//アニメーション描画フラグOFF
				}
			}

			//アニメーションのコマの最後ならばアニメーション終了(-1をしないと配列を超える)
			if (animation->a.NowHandleIndex >= animation->a.DivX * animation->a.DivY - 1)
			{
				animation->a.IsAnimStractFlg = FALSE;	//アニメーション開始フラグOFF
				animation->g.c.IsDraw = FALSE;			//アニメーション描画フラグOFF
			}
		}
	}

	return;
}

//解放
VOID DeleteAnimation(Animation animation)
{
	//政情に読み込むことができていれば
	if (animation.Handle != NULL && animation.Handle[0] != -1)
	{
		//メモリから解放
		for (int i = 0; i < animation.a.DivX * animation.a.DivY; i++)
		{
			DeleteGraph(animation.Handle[i]);
		}

		//動的確保したメモリも開放
		free(animation.Handle);
	}

	//2回以上のfreeを防ぎプログラムのクラッシュ防止
	animation.Handle = NULL;

	return;
}

VOID AnimationStart(Animation* animation, int MillTime, int MillInterval)
{
	//アニメーションの秒数を初期化
	animation->a.FrameCnt = 0;

	//アニメーションの継続時間を計算
	if (MillTime == AnimationInfinity)
	{
		//もしアニメーションが無限継続なら、実際のMAX時間を計算させない
		animation->a.FrameMax = AnimationInfinity;
	}
	else if (MillTime == AnimationOnce)
	{
		//もしアニメーションが一回のみなら、実際のMAX時間を計算させない
		animation->a.FrameMax = AnimationOnce;
	}
	else
	{
		animation->a.FrameMax = (MillTime / 1000.0f) * GameFPS;
	}

	//アニメーションの間隔を初期化
	animation->a.FrameByFrameCnt = 0;
	animation->a.FrameByFrameMax = (MillInterval / 1000.0f) * GameFPS;

	//ハンドルの要素数も初期化
	animation->a.NowHandleIndex = 0;

	//最初のアニメーションの要素数をセット
	animation->g.Handle = animation->Handle[animation->a.NowHandleIndex];

	//アニメーションの開始フラグON
	animation->a.IsAnimStractFlg = TRUE;

	//アニメーション描画フラグOn
	animation->g.c.IsDraw = TRUE;

	return;
}
