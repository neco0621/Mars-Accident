#include "SceneManager.h"
#include "SceneManager.h"

#include "Scene.h"

SceneManager::~SceneManager()
{

}

void SceneManager::Update(Input& input)
{
	//––”ö‚Ì‚İÀs
	scenes_.back()->Update(input);
}

void SceneManager::Draw()
{
	//æ“ª‚©‚ç‡‚É•`‰æ
	//ÅŒã‚ÉÏ‚ñ‚¾‚à‚Ì‚ªÅŒã‚É•`‰æ‚³‚ê‚é
	for (auto& scene : scenes_)
	{
		scene->Draw();
	}
}

void SceneManager::ChangeScene(std::shared_ptr<Scene> nextScene)
{
	if (scenes_.empty())//ƒŠƒXƒg‚ª‹ó‚Á‚Û‚¾‚Á‚½‚ç“ü‚ê‘Ö‚¦‚¸‚É
	{
		scenes_.push_back(nextScene);//––”ö‚É’Ç‰Á
	}
	else
	{
		scenes_.back() = nextScene;//Šù‚Éˆê‚ÂˆÈã‚ ‚ê‚Î––”ö‚ğ
	}
}

void SceneManager::PushScene(std::shared_ptr<Scene> scene)
{
	scenes_.push_back(scene);
}

void SceneManager::popScene()
{
	scenes_.pop_back();
}