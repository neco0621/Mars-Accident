#include "SceneManager.h"
#include "Scene.h"

SceneManager::~SceneManager()
{
}

void SceneManager::Init()
{
	//現在進行中のシーンのInit()処理
	for (auto& scene : scenes_) {
		scene->Init();
	}
}

void SceneManager::Update(Input& input)
{
	//現在進行中のシーンのUpdate()処理
	scenes_.back()->Update(input);
}

void SceneManager::Draw()
{
	//現在進行中のDraw処理
	for (auto& scene : scenes_) {
		scene->Draw();
	}
}

void SceneManager::ChangeScene(std::shared_ptr<Scene> nextScene)
{
	if (scenes_.empty()) {
		//リストが空っぽだったら入れ替えるのではなく
		scenes_.push_back(nextScene);//末尾に追加する
	}
	else {
		scenes_.back() = nextScene;//すでに1つ以上あったら末尾のものを入れ替える
	}

}

void SceneManager::PushScene(std::shared_ptr<Scene> scene)
{
	scenes_.push_back(scene);
}

void SceneManager::PopScene()
{
	scenes_.pop_back();
}
