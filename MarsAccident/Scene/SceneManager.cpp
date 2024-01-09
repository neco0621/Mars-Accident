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
	if (scenes_.empty()) {//ƒŠƒXƒg‚ª‹ó‚Á‚Û‚¾‚Á‚½‚ç“ü‚ê‘Ö‚¦‚é‚Ì‚Å‚Í‚È‚­
		scenes_.push_back(nextScene);//––”ö‚É’Ç‰Á‚·‚é
	}
	else {
		scenes_.back() = nextScene;//‚·‚Å‚É1‚ÂˆÈã‚ ‚Á‚½‚ç––”ö‚Ì‚à‚Ì‚ğ“ü‚ê‘Ö‚¦‚é
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
