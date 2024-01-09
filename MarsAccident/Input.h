#pragma once
#include<array>
#include<map>				//ソート(並べ替えしてくれる)map
#include<unordered_map>		//ソートしないmap
#include<string>

enum class InputType {
	keyboard,	//キーボード
	pad			//パッド
	//mouseとかもここに入れて〇
};

using InputTable_t = std::unordered_map<std::string, std::map<InputType, int>>;

class KeyConfigScene;

class Input
{
	friend KeyConfigScene;
	std::vector<std::string> exclusiveKeyConfigCommands_;

private:
	//コマンド名と入力をペアにしたテーブル
	//キーボードの時はkeyboard&KEY_INPUT●●
	//パッドの時はpad&PAD_INPUT●●
	//をチェックする
	InputTable_t commandTable_;

	//コマンドの入力を覚えておく
	std::map < std::string, bool> inputData_;		//現在の入力
	std::map < std::string, bool> lastInputData_;	//直前の入力

	const InputTable_t GetCommandTable()const;
public:
	Input();

	/// <summary>
	/// 入力情報を更新する
	/// </summary>
	void Update();

	/// <summary>
	/// 指定のコマンドが押された瞬間なのか
	/// </summary>
	/// <param name="command">コマンド文字列</param>
	/// <returns> true : 押された瞬間, false : 押されていないか、押しっぱ</returns>
	bool IsTriggered(const char* command)const;
};

