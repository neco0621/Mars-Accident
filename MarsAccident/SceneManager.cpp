#include "SceneManager.h"
#include "Scene.h"

SceneManager::~SceneManager()
{
}

void SceneManager::Update(Input& input)
{
	scenes_.back()->Update(input);
}

void SceneManager::Draw()
{
	for (auto& scene : scenes_) {
		scene->Draw();
	}
}

void SceneManager::ChangeScene(std::shared_ptr<Scene> nextScene)
{
	if (scenes_.empty()) {//リストが空っぽだったら入れ替えるのではなく
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
