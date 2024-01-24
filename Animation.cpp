//#include "Animation.h"
//
//Animation* AnimExpl;	//爆発アニメーション
//
//Animation::Animation()
//{
//}
//
//Animation::~Animation()
//{
//}
//
////読込・ハンドル生成
//BOOL Animation::Animation_Init()
//{
//	//爆発アニメーション
//	AnimExpl = LoadAnimation(
//		g.LoadGraphic(					//アニメーション画像読み込み
//			GraphicPathTitleAnimExpl,	//アニメーション画像パス
//			(m_pUfo->m_pos.x, m_pUfo->m_pos.y),						//右上から
//			GraAlignTopR),
//		AnimExplDivX,					//アニメーション横分割数
//		AnimExplDivY					//アニメーション縦分割数
//	);
//	if (AnimExpl->Handle[0] == -1) { return FALSE; }
//	return 0;
//}
//
////後始末
//void Animation::Animation_End()
//{
//	DeleteAnimation(*AnimExpl);
//
//	return;
//}
//
////読み込みエラーメッセージ
//void Animation::AnimationLoadErrMessage(const char* path)
//{
//	//エラー用文字列
//	char ErrStr[AnimationPathstrMax];
//
//	//エラー用文字列の内容を空にする
//	for (int i = 0; i < AnimationPathstrMax; i++) { ErrStr[i] = '\0'; }
//
//	//エラー内容を連結して生成
//	sprintf_s(ErrStr, sizeof(ErrStr), "%s%s", path, AnimationLoadErrCap);
//
//	//パスが間違っているなどでインストールできない場合はエラー
//	MessageBox(
//		GetMainWindowHandle(),		//ウィンドウハンドル
//		ErrStr,						//エラー内容
//		AnimationLoadErrTitle,		//エラータイトル
//		MB_OK);						//OKボタンのみ
//
//	return;
//}
//
////アニメーション読み込み
//Animation* Animation::LoadAnimation(Graphic graphic, int XNum, int YNum)
//{
//	Animation animation;
//
//	//読み込んだ画像の情報を引き継ぐ
//	animation.g = graphic;
//
//	//画像の分割数設定
//	animation.DivX = XNum;
//	animation.DivY = YNum;
//
//	//画像の幅と高さを再計算
//	animation.g.Width = animation.g.Width / XNum;
//	animation.g.Height = animation.g.Height / YNum;
//
//	//アニメーションのハンドル配列を動的確保
//	animation.Handle
//		= (int*)			//int型のポインタに型変換
//		calloc(				//メモリを動的確保して値をゼロで初期化
//			XNum * YNum		//確保する要素の個数
//			, sizeof(int)	//確保する要素のデータ型
//		);
//
//	//アニメーションを分割してメモリに読込
//	LoadDivGraph(
//		graphic.Path,			//アニメーションのパス
//		(XNum * YNum),			//分割総数
//		XNum, YNum,				//|(横)分割数、-(縦)分割数
//		animation.g.Width,	//分割した1枚の幅
//		animation.g.Height,	//分割した1枚の高さ
//		animation.Handle		//連続したハンドル配列の先頭
//	);
//
//	//読み込みエラー
//	if (animation.Handle == NULL || animation.Handle[0] == -1)
//	{
//		AnimationLoadErrMessage(graphic.Path);
//	}
//
//	//メモリに読み込んだ画像はサイズを知りたいだけなので用済み
//	//※graphicのhandleは消去される
//	g.DeleteGraphic(graphic);
//
//	//ハンドルの要素数を初期化
//	animation.NowHandleIndex = 0;
//
//	//最初のアニメーションの要素数をセット
//	animation.g.Handle = animation.Handle[animation.NowHandleIndex];
//	return &animation;
//}
//
////描画
//void Animation::DrawAnimation(Animation* animation)
//{
//	//画像描画
//	g.DrawGraphic(&animation->g);
//
//	//アニメーション中ならコマを進める
//	if (animation->IsAnimStractFlg == TRUE)
//	{
//		if (animation->FrameByFrameCnt < animation->DivY - 1)
//		{
//			animation->FrameByFrameCnt++;
//		}
//		else
//		{
//			//コマを進めている部分(-1をしないと配列を超える)
//			if (animation->NowHandleIndex < animation->DivX * animation->DivY)
//			{
//				animation->NowHandleIndex++;
//			}
//			else
//			{
//				animation->NowHandleIndex = 0;
//			}
//
//			//アニメーションの要素数をセット
//			animation->g.Handle = animation->Handle[animation->NowHandleIndex];
//
//			//コマ送り初期化
//			animation->FrameByFrameCnt = 0;
//		}
//
//		//アニメーション時間カウントアップ
//		animation->FrameByFrameCnt++;
//
//		//アニメーションが無限継続ではない時
//		if (animation->FrameMax != AnimationInfinity)
//		{
//			//アニメーションが一回のみならアニメーションの時間を無視
//			if (animation->FrameMax != AnimationOnce)
//			{
//				//アニメーション時間が終わりならばアニメーション終了
//				if (animation->FrameCnt > animation->FrameMax)
//				{
//					animation->IsAnimStractFlg = FALSE;	//アニメーション開始フラグOFF
//					animation->g.IsDraw = FALSE;			//アニメーション描画フラグOFF
//				}
//			}
//
//			//アニメーションのコマの最後ならばアニメーション終了(-1をしないと配列を超える)
//			if (animation->NowHandleIndex >= animation->DivX * animation->DivY - 1)
//			{
//				animation->IsAnimStractFlg = FALSE;	//アニメーション開始フラグOFF
//				animation->g.IsDraw = FALSE;			//アニメーション描画フラグOFF
//			}
//		}
//	}
//
//	return;
//}
//
////解放
//Animation* Animation::DeleteAnimation(Animation animation)
//{
//	//政情に読み込むことができていれば
//	if (animation.Handle != NULL && animation.Handle[0] != -1)
//	{
//		//メモリから解放
//		for (int i = 0; i < animation.DivX * animation.DivY; i++)
//		{
//			DeleteGraph(animation.Handle[i]);
//		}
//
//		//動的確保したメモリも開放
//		free(animation.Handle);
//	}
//
//	//2回以上のfreeを防ぎプログラムのクラッシュ防止
//	animation.Handle = NULL;
//	return &animation;
//}
//
//void Animation::AnimationStart(Animation* animation, int MillTime, int MillInterval)
//{
//	//アニメーションの秒数を初期化
//	animation->FrameCnt = 0;
//
//	//アニメーションの継続時間を計算
//	if (MillTime == AnimationInfinity)
//	{
//		//もしアニメーションが無限継続なら、実際のMAX時間を計算させない
//		animation->FrameMax = AnimationInfinity;
//	}
//	else if (MillTime == AnimationOnce)
//	{
//		//もしアニメーションが一回のみなら、実際のMAX時間を計算させない
//		animation->FrameMax = AnimationOnce;
//	}
//	else
//	{
//		animation->FrameMax = (MillTime / 1000.0f) * GameFPS;
//	}
//
//	//アニメーションの間隔を初期化
//	animation->FrameByFrameCnt = 0;
//	animation->FrameByFrameMax = (MillInterval / 1000.0f) * GameFPS;
//
//	//ハンドルの要素数も初期化
//	animation->NowHandleIndex = 0;
//
//	//最初のアニメーションの要素数をセット
//	animation->g.Handle = animation->Handle[animation->NowHandleIndex];
//
//	//アニメーションの開始フラグON
//	animation->IsAnimStractFlg = TRUE;
//
//	//アニメーション描画フラグOn
//	animation->g.IsDraw = TRUE;
//
//	return;
//}