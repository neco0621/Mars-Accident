#pragma once
#include <memory>
#include <list>

class Input;
class Scene;
/// <summary>
/// 各シーンの遷移と捜査をコントロールするクラス
/// </summary>
class SceneManager
{
private:
	//アスタリスクを外すことはできない
	//外してしまうと実体を作ってしまい
	//場所が固定化され、切り替えができない
	std::list<std::shared_ptr<Scene>>scenes_;
public:
	~SceneManager();
	void Init();

	/// <summary>
	/// 持っているシーンのUpdate関数を呼び出す
	/// </summary>
	/// <param name="input">入力クラス</param>
	void Update(Input& input);
	/// <summary>
	/// 持っているシーンの描画Draw関数で呼び出す
	/// </summary>
	void Draw();

	/// <summary>
	/// 現在先頭で実行中のシーンを引数で指定されたシーンに切り替える
	/// </summary>
	/// <param name="nextScene">次のシーン</param>
	void ChangeScene(std::shared_ptr<Scene> nextScene);
	/// <summary>
	/// 現在のシーンの上に乗っけます
	/// </summary>
	/// <param name="nextScene">上に乗っけたいシーン</param>
	void PushScene(std::shared_ptr<Scene> nextScene);
	/// <summary>
	/// 現在の先頭シーンにポップします
	/// </summary>
	void PopScene();
};

