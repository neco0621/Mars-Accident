#include "Pad.h"
#include "DxLib.h"

namespace
{
	//前のフレームのパッドの押し下げ状態
	int lastPad = 0;

	//このフレームのパッドの押し下げ状態
	int nowPad = 0;
}

namespace Pad
{
	void Update()
	{
		//前のフレームに取得したパッド情報を一つ古い情報にする
		lastPad = nowPad;
		//現在のパッドの情報を取得する
		nowPad = GetJoypadInputState(DX_INPUT_KEY_PAD1);
	}

	bool IsPress(int key)
	{
		return (nowPad & key);
	}

	bool IsTrigger(int key)
	{
		bool isNow = (nowPad & key);	//このフレーム
		bool isLast = (lastPad & key);	//前のフレーム
		//		return !isLast && isNow;	//これでいいけど理解しにくいのでわかりやすくしたのが↓

		if (isNow &&	//このフレームに押されていて 
			!isLast)	//前回のフレームに押されていない
		{
			return true;
		}
		return false;
	}

	bool IsRelase(int key)
	{
		bool isNow = (nowPad & key);	//このフレーム
		bool isLast = (lastPad & key);	//前のフレーム

		//return isLast && !isNow;	//これでいいけど理解しにくいのでわかりやすくしたのが↓

		if (!isNow &&	//このフレームは押されていなくて
			isLast)		//前回のフレームには押されていた
		{
			return true;
		}
		return false;
	}

	bool IsRepeat(int key, int& frame, int RepeatFrame)
	{
		if (IsTrigger(key)) return true;

		if (IsPress(key))
		{
			frame++;

			if (RepeatFrame <= frame)
			{
				frame = 0;
				return true;
			}
		}
		else
		{
			frame = 0;
		}
		return false;
	}
}