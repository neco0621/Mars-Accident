#include "Input.h"
#include <DxLib.h>
#include <string>
#include <algorithm>

using namespace std;

const InputTable_t Input::GetCommandTable() const
{
	//キーコンフィグ画面に移動キーを表示させたくないための処理
	InputTable_t ret = commandTable_;
	for (const auto& ex : exclusiveKeyConfigCommands_)
	{
		ret.erase(ex);
	}

	return ret;
}


Input::Input()
{
	commandTable_["OK"] = { {InputType::keyboard, KEY_INPUT_RETURN},
							{InputType::pad,PAD_INPUT_A} };

	commandTable_["pause"] = { {InputType::keyboard, KEY_INPUT_P},
								{InputType::pad, PAD_INPUT_R} };	//スタートボタン

	commandTable_["keyconf"] = { {InputType::keyboard, KEY_INPUT_K},
								{InputType::pad, PAD_INPUT_L} };	//キーコンフィグボタン

	commandTable_["up"] = { {InputType::keyboard, KEY_INPUT_UP},
							{InputType::pad, PAD_INPUT_UP} };	//キーコンフィグボタン

	commandTable_["down"] = { {InputType::keyboard, KEY_INPUT_DOWN},
							{InputType::pad, PAD_INPUT_DOWN} };	//キーコンフィグボタン

	commandTable_["left"] = { {InputType::keyboard, KEY_INPUT_LEFT},
							{InputType::pad, PAD_INPUT_LEFT} };	//キーコンフィグボタン

	commandTable_["right"] = { {InputType::keyboard, KEY_INPUT_RIGHT},
							{InputType::pad, PAD_INPUT_RIGHT} };	//キーコンフィグボタン

	exclusiveKeyConfigCommands_ = { "up","down","left","right" };
}

void Input::Update()
{
	lastInputData_ = inputData_;	//直前入力をコピーしておく(押した瞬間を取得する用)

	//ハードウェア入力チェック
	char keystate[256];
	GetHitKeyStateAll(keystate);//現在のキーボード入力を取得
	int padstate = GetJoypadInputState(DX_INPUT_PAD1);//パッド情報の取得

	//登録された情報とハードの情報を照らし合わせながら
	//inputData_の内容を更新していく
	for (const auto& cmd : commandTable_)
	{
		auto& input = inputData_[cmd.first];//コマンドの名前から入力データを作る

		for (const auto& hardIO : cmd.second)
		{
			//キーボードのチェック
			input = false;
			if (hardIO.first == InputType::keyboard)
			{
				if (keystate[hardIO.second])
				{
					input = true;
					break;
				}
			}
			else if (hardIO.first == InputType::pad)
			{
				if (padstate & hardIO.second)
				{
					input = true;
					break;
				}
			}
		}
	}
}

bool Input::IsTriggered(const char* command) const
{
	auto it = inputData_.find(command);
	if (it == inputData_.end())	//情報がなければfalseを返す
	{
		return false;
	}
	return (inputData_.at(command) && !lastInputData_.at(command));

}